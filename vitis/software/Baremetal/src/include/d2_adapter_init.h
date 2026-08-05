#pragma once

/* Project Wizard BEGIN: D2 includes */
#include "../IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
/* Project Wizard END: D2 includes */

/* Project Wizard BEGIN: D2 prototypes */
struct _DS_Data_;
uz_inverter_adapter_t *initialize_inverter_adapter_d2(void);
void update_inverter_adapter_d2_outputs(struct _DS_Data_ *data);
/* Project Wizard END: D2 prototypes */
