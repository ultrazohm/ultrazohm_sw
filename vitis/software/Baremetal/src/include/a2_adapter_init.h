#pragma once

/* Project Wizard BEGIN: A2 includes */
#include "../IP_Cores/uz_dac_interface/uz_dac_interface.h"
/* Project Wizard END: A2 includes */

/* Project Wizard BEGIN: A2 prototypes */
uz_dac_interface_t* initialize_dac8831_a2(void);
void update_dac8831_a2_outputs(uz_dac_interface_t* instance);
/* Project Wizard END: A2 prototypes */
