#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/*******************************************************************************/

void
output_blip_to_screen(Simulation_Run_Ptr simulation_run)
{
  double percentagedone;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter++;

  if((data->blip_counter >= BLIPRATE)
     ||
     (data->number_of_packets_transmitted >= RUNLENGTH)) {

    data->blip_counter = 0;

    percentagedone =
      100 * (double) data->number_of_packets_transmitted/RUNLENGTH;

    printf("%3.0f%% ", percentagedone);

    printf("Successfully Xmtted Pkts  = %ld (Arrived Data Pkts = %ld ; Arrived Token Pkts = %ld ; Transmitted Bits = %ld) \r", 
	   data->number_of_packets_transmitted, 
	   data->packet_arrival_count,
     data->token_arrival_count,
     data->bits_transmitted);

    fflush(stdout);
  }
}

/**********************************************************************/

void output_results(Simulation_Run_Ptr this_simulation_run, FILE* outfile)
{
  Simulation_Run_Data_Ptr sim_data = (Simulation_Run_Data_Ptr) simulation_run_data(this_simulation_run);

  printf("\n\n");
  printf("Random Seed = %d \n", sim_data->random_seed);
  printf("Packet Arrival Rate = %.2f \n", PACKET_ARRIVAL_RATE);
  printf("T = %d \n", T);
  printf("B_T_MAX = %d \n", B_T_MAX);
  printf("B_D_MAX = %d \n", B_D_MAX);
  printf("Output statistics are stored in '%s' \n", OUTPUT_CSV_FILE);

  printf("Token Arrivals = %ld \n", sim_data->token_arrival_count);
  printf("Pkt Arrivals = %ld \n", sim_data->packet_arrival_count);

  printf("\n------------------------------------------------------------\n");

  /* Calculate derived statistics */
  double packet_loss_rate = (double) sim_data->number_of_packets_lost / sim_data->packet_arrival_count;
  double output_data_rate = (double) sim_data->bits_transmitted / simulation_run_get_time(this_simulation_run);
  //(from experiment 3a) double output_data_rate = (double) sim_data->number_of_packets_transmitted / simulation_run_get_time(this_simulation_run);

  /* Write results to outfile */
  fprintf(outfile, "%d, %.2f, %d, %d, %d, %ld, %ld, %ld, %.3f, %.3f \n", 
  	sim_data->random_seed,
    PACKET_ARRIVAL_RATE,
    T,
    B_T_MAX,
    B_D_MAX,
    sim_data->packet_arrival_count,
    sim_data->number_of_packets_lost,
    sim_data->number_of_packets_transmitted,
    packet_loss_rate,
    output_data_rate);
}

