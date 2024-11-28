#ifndef _MAIN_H_
#define _MAIN_H_

#include "../simlib.h"
#include "simparameters.h"

typedef double Time;
typedef Fifoqueue_Ptr Buffer_Ptr;


typedef enum {WAITING, TRANSMITTING} Packet_Status;

typedef struct _packet_
{
    double arrive_time;
    double service_time;
    Packet_Status status;
} Packet, *Packet_Ptr;

typedef struct _simulation_run_data_
{
    Server_Ptr server;
    Buffer_Ptr buffer;
    long int blip_counter;
    long int arrival_count;
    long int packets_processed;
    double accumulated_delay;
    double service_rate;
    unsigned random_seed;
    unsigned queue_size;
}   Simulation_Run_Data, *Simulation_Run_Data_Ptr;

int main(void);

#endif

