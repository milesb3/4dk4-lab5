
/*
 * Simulation of the ALOHA Protocol
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/*******************************************************************************/

#define MEAN_ARRIVAL_RATE 2   /* mean arrival rate (packets/s) of data packets */
#define T   /* token generation period (1/T tokens are generated a seconds) */
#define B_T_MAX 5 /* token bucket maximum capacity */
#define B_D_MAX 10  /* data bucket maximum capacity */
#define RUNLENGTH 50000000
#define BLIPRATE 100000

#define OUTPUT_CSV_FILE "experiment3_test.csv"
#define CSV_COLUMN_HEADER "random seed, arrival count, number of packets lost, number of packets transmitted, packet loss rate, average output data rate\n"

/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 400243271, 400307241, 111111, 222222, 333333, 444444, 555555, 666666, 777777, 888888

/*******************************************************************************/

#endif /* simparameters.h */






