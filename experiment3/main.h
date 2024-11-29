#ifndef _MAIN_H_
#define _MAIN_H_

/**********************************************************************/

#include "../simlib.h"
#include "simparameters.h"

/**********************************************************************/

typedef double Time;
typedef Fifoqueue_Ptr Bucket_Ptr;

/**********************************************************************/

typedef struct _token_bucket_controller_
{
  Bucket_Ptr token_bucket;
  Bucket_Ptr data_bucket;
} Token_Bucket_Controller, * Token_Bucket_Controller_Ptr;

typedef enum{TOKEN, DATA} Packet_Type;

typedef struct _packet_ 
{
  double arrive_time;
  double transmit_time;
  Packet_Type type;
  unsigned int size; //Size of packet in bits for experiment 3b
} Packet, * Packet_Ptr;

typedef struct _simulation_run_data_
{
  long int blip_counter;
  Token_Bucket_Controller_Ptr token_bucket_controller;
  long int packet_arrival_count;
  long int token_arrival_count;
  long int bits_transmitted; //For calculating average output data rate in experiment 3b
  long int number_of_tokens_rejected;
  long int number_of_packets_lost;
  long int number_of_packets_transmitted;
  unsigned random_seed;
} Simulation_Run_Data, * Simulation_Run_Data_Ptr;

/**********************************************************************/

/*
 * Function prototypes
 */

int
main(void);

/**********************************************************************/

#endif /* main.h */






