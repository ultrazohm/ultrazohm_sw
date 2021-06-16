#ifndef UZ_PLANTPT1_HW_H
#define UZ_PLANTPT1_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_plantPT1_hw_write_reset(uint32_t base_address,bool reset);
float uz_plantPT1_hw_read_output(uint32_t base_address);
void uz_plantPT1_hw_write_time_constant(uint32_t base_address, float time_constant);
void uz_plantPT1_hw_write_gain(uint32_t base_address,float gain);
#endif // UZ_PLANTPT1_HW_H
