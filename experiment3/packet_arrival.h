#ifndef _PACKET_ARRIVAL_H_
#define _PACKET_ARRIVAL_H_

/*******************************************************************************/

/*
 * Function prototypes
 */

long int schedule_token_arrival_event(Simulation_Run_Ptr, Time);
long int schedule_packet_arrival_event(Simulation_Run_Ptr, Time);

void token_arrival_event(Simulation_Run_Ptr, void *);
void packet_arrival_event(Simulation_Run_Ptr, void *);

/*******************************************************************************/

#endif /* packet_arrival.h */
