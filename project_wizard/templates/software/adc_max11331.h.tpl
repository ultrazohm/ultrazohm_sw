#include "../IP_Cores/uz_adcMax11331/uz_adcMax11331.h"

uz_adcMax11331_t* initialize_adc_max11331_{{ slot_lower }}(void);
float convert_adc_max11331_{{ slot_lower }}_raw_to_physical_value(int16_t raw_value);
