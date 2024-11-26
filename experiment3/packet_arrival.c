#include <math.h>
#include <stdio.h>
#include "simparameters.h"
#include "packet_transmission.h"
#include "packet_arrival.h"

/*******************************************************************************/

long int schedule_token_arrival_event(Simulation_Run_Ptr simulation_run, Time event_time) {
  Event event;

  event.description = "Token Arrival";
  event.function = token_arrival_event;
  event.attachment = NULL;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

long int schedule_packet_arrival_event(Simulation_Run_Ptr simulation_run, Time event_time) {
  Event event;

  event.description = "Packet Arrival";
  event.function = packet_arrival_event;
  event.attachment = NULL;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void token_arrival_event(Simulation_Run_Ptr simulation_run, void* dummy_ptr) {
  Time now;
  Simulation_Run_Data_Ptr data;

  now = simulation_run_get_time(simulation_run);

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
  data->token_arrival_count++;

  /* Check if there is room available in the token bucket to accomodate this token */
  if (fifoqueue_size(data->token_bucket_controller->token_bucket) < B_T_MAX) {
    /* Add new token to token bucket */
    Packet_Ptr new_token = (Packet_Ptr) xmalloc(sizeof(Packet));
    new_token->arrive_time = now;
    new_token->type = TOKEN;
    fifoqueue_put(data->token_bucket_controller->token_bucket, new_token);
  } 
  else {
    /* Keep track of the number of rejected tokens */
    data->number_of_tokens_rejected++;
  }

  /* Schedule next token arrival*/
  schedule_token_arrival_event(simulation_run, now + T);
}

/*******************************************************************************/

void packet_arrival_event(Simulation_Run_Ptr simulation_run, void* dummy_ptr) {
  Time now;
  Simulation_Run_Data_Ptr data;

  now = simulation_run_get_time(simulation_run);

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
  data->packet_arrival_count++;

  /* Check if there is room available in the data bucket to accomodate this packet */
  if (fifoqueue_size(data->token_bucket_controller->data_bucket) < B_D_MAX) {
    /* Add new packet to data bucket */
    Packet_Ptr new_packet = (Packet_Ptr) xmalloc(sizeof(Packet));
    new_packet->arrive_time = now;
    new_packet->type = DATA;
    fifoqueue_put(data->token_bucket_controller->data_bucket, new_packet);
  } 
  else {
    /* Keep track of the number of lost packets */
    data->number_of_packets_lost++;
  }

  //Schedule transmission event if data and token available
  if ((fifoqueue_size(data->token_bucket_controller->data_bucket) > 0)
    && (fifoqueue_size(data->token_bucket_controller->token_bucket) > 0)) {
      //Remove next packet to transmit from data bucket
      Packet_Ptr packet = fifoqueue_get(data->token_bucket_controller->data_bucket);

      //Consume one token to send data packet
      fifoqueue_get(data->token_bucket_controller->token_bucket);

      //Schedule transmission event for now
      schedule_transmission_event(simulation_run, now, (void*) packet);
  }
  
  /* Schedule the next data packet arrival */
  schedule_packet_arrival_event(simulation_run, 
		now + exponential_generator((double) 1/PACKET_ARRIVAL_RATE));
}
