#ifndef UZ_DAC_INTERFACE_H
#define UZ_DAC_INTERFACE_H

#include <stdint.h>
#include "../../uz/uz_array/uz_array.h"

typedef struct uz_dac_interface_t uz_dac_interface_t; 

struct uz_dac_interface_config_t{
    uint32_t base_address;
    uint32_t ip_clk_frequency_Hz;
    float conversion_factor[8];
};

uz_dac_interface_t* uz_dac_interface_init(struct uz_dac_interface_config_t config);

void uz_dac_interface_set_ouput_values(uz_dac_interface_t* self,uz_array_float_t* output_values);
void uz_dac_interface_set_ouput_values_unsafe(uz_dac_interface_t* self,uz_array_float_t* output_values);


#endif // UZ_DAC_INTERFACE_H
