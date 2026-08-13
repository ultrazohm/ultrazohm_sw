#pragma once

/* Project Wizard BEGIN: D5 includes */
#include "../IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
/* Project Wizard END: D5 includes */

/* Project Wizard BEGIN: D5 prototypes */
/** @brief Initialize the incremental-encoder IP connected to D5 channel 1. */
uz_incrementalEncoder_t *initialize_incremental_encoder_d5_1(void);
/** @brief Initialize the incremental-encoder IP connected to D5 channel 2. */
uz_incrementalEncoder_t *initialize_incremental_encoder_d5_2(void);
/** @brief Initialize the incremental-encoder IP connected to D5 channel 3. */
uz_incrementalEncoder_t *initialize_incremental_encoder_d5_3(void);
/* Project Wizard END: D5 prototypes */
