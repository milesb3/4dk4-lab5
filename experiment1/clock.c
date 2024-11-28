#include <math.h>
#include <stdio.h>
#include "main.h"
#include "packet_transmission.h"
#include "clock.h"
#include "output.h"


long int
schedule_clock_tick_event(Simulation_Run_Ptr simulation_run,
			      double event_time)
{
  Event event;
  event.description = "Clock Tick";
  event.function = clock_tick_event;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}


void
clock_tick_event(Simulation_Run_Ptr simulation_run, void * ptr)
{

    //Retrieve Parameters
    Simulation_Run_Data_Ptr data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
    Buffer_Ptr queue = data->buffer;
    Server_Ptr server = data->server;

    //Send Packet each clock tick if there is some in the queue
    if(queue->size != 0) {
        schedule_end_packet_transmission_event(simulation_run,
                                               simulation_run_get_time(simulation_run)+ (double)1/data->service_rate- (double) EPSILON,
                                               (void *)server);
    }
    double next_tick = simulation_run_get_time(simulation_run) + (double)1/data->service_rate;
    output_progress_msg_to_screen(simulation_run);
    //Schedule next clock tick
    schedule_clock_tick_event(simulation_run, next_tick);
}
