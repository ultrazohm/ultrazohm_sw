#pragma once
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

/* Independent of the measurement source and output hardware. */
uz_pmsm_control_t* initialize_dut(float sample_time_s);
