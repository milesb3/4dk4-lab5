#include "simlib.h"
#include "main.h"
#include "simparameters.h"
#include "cleanup.h"

/*******************************************************************************/

void
cleanup (Simulation_Run_Ptr simulation_run)
{
  Simulation_Run_Data_Ptr data;
  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  /* Clean memory allocated to token bucket controller */
  while (fifoqueue_size(data->token_bucket_controller->token_bucket) > 0) {
    xfree(fifoqueue_get(data->token_bucket_controller->token_bucket));
  }

  while (fifoqueue_size(data->token_bucket_controller->data_bucket) > 0) {
    xfree(fifoqueue_get(data->token_bucket_controller->data_bucket));
  }

  xfree(data->token_bucket_controller);

  /* Clean up the simulation_run. */
  simulation_run_free_memory(simulation_run);
}
