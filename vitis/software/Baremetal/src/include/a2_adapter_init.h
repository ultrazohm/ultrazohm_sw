#pragma once

/* Project Wizard BEGIN: A2 includes */
#include "../IP_Cores/uz_dac_interface/uz_dac_interface.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
/* Project Wizard END: A2 includes */

/* Project Wizard BEGIN: A2 prototypes */
struct _DS_Data_;
uz_dac_interface_t* initialize_dac8831_a2(void);
void update_dac8831_a2_outputs(struct _DS_Data_* data);
/* Project Wizard END: A2 prototypes */
