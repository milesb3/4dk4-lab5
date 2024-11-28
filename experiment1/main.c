//To contain main code for experiment 1
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "output.h"
#include "cleanup.h"
#include "main.h"
#include "../simlib.h"
#include "packet_arrival.h"
#include "packet_transmission.h"
#include "clock.h"
#include "simparameters.h"

//Initialize simulation loop parameters
int main() {


    unsigned current_queue_size;
    unsigned random_seed;
    unsigned RANDOM_SEEDS_LIST[] = {RANDOM_SEEDS, 0};
    unsigned QUEUE_SIZE_LIST[] = {QUEUE_SIZE, 0};
    double SERVICE_RATE_LIST[] = {SERVICE_RATE, 0};
    double current_rate;
    Simulation_Run_Ptr simulation_run;
    Simulation_Run_Data data;
    int i = 0, j=0, k=0;
    FILE *fptr;
    fptr = fopen("Experiment1B.csv", "w+");
    fprintf(fptr, "SEED, SERVICE_RATE, ARRIVAL_RATE, QUEUE_SIZE, LOSS_RATE, OUTPUT_RATE\n");



    //Loop for various Seeds
    while((random_seed = RANDOM_SEEDS_LIST[i++]) != 0) {
        j=0;
        while((current_queue_size = QUEUE_SIZE_LIST[j++]) != 0) {
            k=0;
            while((current_rate = SERVICE_RATE_LIST[k++]) != 0) {

                //Initialize new seed and a new run
                //
                random_generator_initialize(random_seed);
                simulation_run = (Simulation_Run_Ptr) simulation_run_new();
                simulation_run_set_data(simulation_run, (void*) & data);

                //Initialize data parameters
                data.blip_counter = 0;
                data.arrival_count = 0;
                data.packets_processed = 0;
                data.accumulated_delay = 0;
                data.random_seed = random_seed;
                data.queue_size = current_queue_size;
                data.service_rate = current_rate;
                data.buffer = fifoqueue_new();
                data.server = server_new();

                //Schedule the first packet arrival
                schedule_packet_arrival_event(simulation_run,
                                              simulation_run_get_time(simulation_run) +
                                              exponential_generator((double) 1/ARRIVAL_RATE), data.buffer);
                //Schedule the first clock tick
                schedule_clock_tick_event(simulation_run, 1);

                //Run the Simulation
                while(data.packets_processed < RUNLENGTH) {
                    simulation_run_execute_event(simulation_run);
                }

                //Handle output and file Writing
                output_results(simulation_run);
                Simulation_Run_Data_Ptr sim_data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
                fprintf(fptr, "%d, %.3f, %d, %d, %.5f, %.5f\n",   sim_data->random_seed,
                                        sim_data->service_rate,
                                        ARRIVAL_RATE,
                                        sim_data->queue_size,
                                        (double)sim_data->packets_processed/sim_data->arrival_count,
                                        (double)RUNLENGTH/simulation_run_get_time(simulation_run));

                //Handle Cleanup
                cleanup(simulation_run);
            }
        }
    }
    fclose(fptr);
    getchar();
    return 0;
}

