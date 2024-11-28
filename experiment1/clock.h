

#ifndef _CLOCK_H_
#define _CLOCK_H_

/******************************************************************************/

#include "../simlib.h"

/******************************************************************************/

/*
 * Function prototypes
 */

void
clock_tick_event(Simulation_Run_Ptr,void* );

long
schedule_clock_tick_event(Simulation_Run_Ptr, double );

/******************************************************************************/

#endif
