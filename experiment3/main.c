#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "output.h"
#include "../trace.h"
#include "simparameters.h"
#include "cleanup.h"
#include "packet_arrival.h"
#include "packet_transmission.h"
#include "main.h"

/*******************************************************************************/

int main(void) {
    /* Get the list of random number generator seeds defined in simparameters.h */
    unsigned random_seed;
    unsigned RANDOM_SEEDS[] = {RANDOM_SEED_LIST, 0};

    Simulation_Run_Ptr simulation_run;
    Simulation_Run_Data data;
    int i, j=0;

    /* Initialize output csv file to store simulation output */
    FILE* output_csv = fopen(OUTPUT_CSV_FILE, "w+");
    fprintf(output_csv, CSV_COLUMN_HEADER);

    /* Do a new simulation_run for each random number generator seed. */
    while ((random_seed = RANDOM_SEEDS[j++]) != 0) {
        /* Set the random generator seed. */
        random_generator_initialize(random_seed);

        /* Create a new simulation_run. This gives a clock and
        eventlist. Clock time is set to zero. */
        simulation_run = (Simulation_Run_Ptr) simulation_run_new();

        /* Add our data definitions to the simulation_run. */
        simulation_run_set_data(simulation_run, (void *) & data);

        /* Initialize simulation_run variables */
        data.blip_counter = 0;
        data.token_arrival_count = 0;
        data.packet_arrival_count = 0;
        data.number_of_tokens_rejected = 0;
        data.number_of_packets_lost = 0;
        data.number_of_packets_transmitted = 0;
        data.bits_transmitted = 0;
        data.random_seed = random_seed;

        /* Initialize token bucket controller */
        data.token_bucket_controller = (Token_Bucket_Controller_Ptr) xmalloc(sizeof(Token_Bucket_Controller));
        data.token_bucket_controller->token_bucket = fifoqueue_new();
        data.token_bucket_controller->data_bucket = fifoqueue_new();

        /* Schedule initial token and packet arrivals*/
        schedule_token_arrival_event(simulation_run, 
            simulation_run_get_time(simulation_run) + T);
        schedule_packet_arrival_event(simulation_run,
            simulation_run_get_time(simulation_run) + exponential_generator((double) 1/PACKET_ARRIVAL_RATE));
        
        /* Execute events until we are finished. */
        while(data.number_of_packets_transmitted < RUNLENGTH) {
            simulation_run_execute_event(simulation_run);
        }

        /* Output results */
        output_results(simulation_run, output_csv);

        /* Clean up memory. */
        cleanup(simulation_run);
    }

    //Close output csv file before finishing simulation
    fclose(output_csv); 
    return 0;
}