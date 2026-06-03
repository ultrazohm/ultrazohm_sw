#pragma once

/* Project Wizard BEGIN: A3 includes */
#include "../IP_Cores/uz_adcMax11331/uz_adcMax11331.h"
/* Project Wizard END: A3 includes */

/* Project Wizard BEGIN: A3 prototypes */
uz_adcMax11331_t* initialize_adc_max11331_a3(void);
float convert_adc_max11331_a3_raw_to_physical_value(int16_t raw_value);
/* Project Wizard END: A3 prototypes */
