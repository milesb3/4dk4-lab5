#include "main.h"

/*******************************************************************************/

#ifndef _PACKET_TRANSMISSION_H_
#define _PACKET_TRANSMISSION_H_

/*******************************************************************************/

/*
 * Function prototypes
 */

void
transmission_event(Simulation_Run_Ptr, void *);

long int
schedule_transmission_event(Simulation_Run_Ptr, Time, void *);

/*******************************************************************************/

#endif /* packet_transmission.h */
