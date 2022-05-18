#ifndef UZ_DAC_INTERFACE_HW_H
#define UZ_DAC_INTERFACE_HW_H

#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_array/uz_array.h"

void uz_dac_interface_hw_write_trigger(uint32_t base_address,bool trigger);
void uz_dac_interface_hw_write_dac1(uint32_t base_address,int32_t dac_value);
void uz_dac_interface_hw_write_dac2(uint32_t base_address,int32_t dac_value);
void uz_dac_interface_hw_write_dac3(uint32_t base_address,int32_t dac_value);
void uz_dac_interface_hw_write_dac4(uint32_t base_address,int32_t dac_value);
void uz_dac_interface_hw_write_dac5(uint32_t base_address,int32_t dac_value);
void uz_dac_interface_hw_write_dac6(uint32_t base_address,int32_t dac_value);
void uz_dac_interface_hw_write_dac7(uint32_t base_address,int32_t dac_value);
void uz_dac_interface_hw_write_dac8(uint32_t base_address,int32_t dac_value);

#endif // UZ_DAC_INTERFACE_HW_H
