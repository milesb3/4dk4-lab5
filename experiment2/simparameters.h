

/*
 *
 * Simulation of A Single Server Queueing System
 *
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
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

/******************************************************************************/

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/******************************************************************************/

#define SERVICE_RATE 2e4, 4e4, 8e4, 16e4, 32e4,  64e4, 128e4 /* bits per second */
#define QUEUE_SIZE 200 /* packets */
#define ARRIVAL_RATE 100 /*packets per second*/
#define CLOCK_PERIOD 1 /*seconds*/
#define BYTE_LIMIT 20000 /*bytes*/
#define EPSILON 0.00001
#define RUNLENGTH 10e6 /* packets */

/* Comma separated list of random seeds to run. */
#define RANDOM_SEEDS 400243271, 400307241 ,111111 ,222222,333333, 444444, 555555, 666666, 777777, 888888

#define BLIPRATE (RUNLENGTH/10000)

/******************************************************************************/

#endif /* simparameters.h */



