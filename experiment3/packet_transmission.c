#include <stdio.h>
#include <math.h>
#include "trace.h"
#include "output.h"
#include "packet_transmission.h"

/*******************************************************************************/

long int
schedule_transmission_event(Simulation_Run_Ptr simulation_run,
				  Time event_time,
				  void * packet) 
{
  Event event;

  event.description = "Schedule transmission event";
  event.function = transmission_event;
  event.attachment = packet;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void
transmission_event(Simulation_Run_Ptr simulation_run, void * ptr)
{
  Packet_Ptr packet = (Packet_Ptr) ptr;
  Simulation_Run_Data_Ptr data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
  Time now = simulation_run_get_time(simulation_run);

  //Keep track of statistics
  packet->transmit_time = now;
  data->number_of_packets_transmitted++;

  //Free packet
  xfree(packet);

  output_blip_to_screen(simulation_run);

  //Schedule transmission event if data and token available
  if ((fifoqueue_size(data->token_bucket_controller->data_bucket) > 0)
    && (fifoqueue_size(data->token_bucket_controller->token_bucket) > 0)) {
      //Remove next packet to transmit from data bucket
      Packet_Ptr packet = fifoqueue_get(data->token_bucket_controller->data_bucket);

      //Consume one token to send data packet
      xfree(fifoqueue_get(data->token_bucket_controller->token_bucket));

      //Schedule transmission event for now
      schedule_transmission_event(simulation_run, now, (void*) packet);
  }
}
