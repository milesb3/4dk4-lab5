
#include <stdio.h>
#include "../trace.h"
#include "main.h"
#include "output.h"
#include "packet_transmission.h"


long
schedule_end_packet_transmission_event(Simulation_Run_Ptr simulation_run,
				       double event_time,
				       Packet_Ptr packet)
{
  Event event;

  event.description = "Packet Xmt End";
  event.function = end_packet_transmission_event;
  event.attachment = (void *) packet;
  return simulation_run_schedule_event(simulation_run, event, event_time);
}


void
end_packet_transmission_event(Simulation_Run_Ptr simulation_run, void * packet_ptr)
{
    Simulation_Run_Data_Ptr data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
    Buffer_Ptr queue = data->buffer;


    //End transmission
    Packet_Ptr packet = (Packet_Ptr) packet_ptr;
    data->accumulated_delay =+ simulation_run_get_time(simulation_run) - packet->arrive_time;
    data->packets_processed++;



}



