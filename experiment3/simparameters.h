#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/*******************************************************************************/

#define PACKET_ARRIVAL_RATE 1   /* mean arrival rate (packets/s) of data packets */
#define T 1 /* token generation period (a token is generated every T seconds)*/
#define B_T_MAX 10
/* token bucket maximum capacity */
#define B_D_MAX 10
/* data bucket maximum capacity */
#define RUNLENGTH 70000000
#define BLIPRATE 100000

#define OUTPUT_CSV_FILE "results/experiment3a-10-10.csv"
#define CSV_COLUMN_HEADER "random seed, packet arrival rate, T, B_T_MAX, B_D_MAX, packet arrival count, number of packets lost, number of packets transmitted, packet loss rate, average output data rate\n"

/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 400243271, 400307241, 111111, 222222, 333333, 444444, 555555, 666666, 777777, 888888

/*******************************************************************************/

#endif /* simparameters.h */
