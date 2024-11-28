#include <math.h>
#include <stdio.h>
#include "main.h"
#include "packet_transmission.h"
#include "packet_arrival.h"


long int
schedule_packet_arrival_event(Simulation_Run_Ptr simulation_run,
			      double event_time, Fifoqueue_Ptr buffer)
{
  Event event;

  event.description = "Packet Arrival";
  event.function = packet_arrival_event;
  event.attachment = (void *) buffer;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}


void
packet_arrival_event(Simulation_Run_Ptr simulation_run, void * ptr)
{

    //Initialize the required elements
    Simulation_Run_Data_Ptr data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
    Buffer_Ptr buffer = data->buffer;
    Packet new_packet;
    new_packet.arrive_time = simulation_run_get_time(simulation_run);
    new_packet.service_time = (double) 1/data->service_rate;

    data->arrival_count++;

    //Check if queue is full, if not, add to the queue
    if(buffer->size < data->queue_size) {
        fifoqueue_put(buffer, (void*) &new_packet);
    }

    //Schedule next packet arrival
    schedule_packet_arrival_event(simulation_run,
                                  simulation_run_get_time(simulation_run) + exponential_generator((double)1/ARRIVAL_RATE), data->buffer);
}
