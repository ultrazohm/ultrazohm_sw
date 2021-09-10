#ifndef UZ_INCREMENTALENCODER_HW_H
#define UZ_INCREMENTALENCODER_HW_H
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"

void uz_incrementalEncoder_hw_set_timer_fpga_ms(uint32_t base_address, uint32_t timer_ms);
void uz_incrementalEncoder_hw_set_pi2_inc(uint32_t base_address, uint32_t pi2_inc);
void uz_incrementalEncoder_hw_set_increments_per_turn_mechanical(uint32_t base_address, uint32_t increments_per_turn);
void uz_incrementalEncoder_hw_set_increments_per_turn_electric(uint32_t base_address, uint32_t increments_per_turn);
void uz_incrementalEncoder_hw_set_omegaPerOverSampl(uint32_t base_address,uint32_t omega_per_over_sampl); 

uint32_t uz_incrementalEncoder_hw_get_omega(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_direction(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_theta_electric(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_position(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_counterPerPeriod(uint32_t base_address);

#endif // UZ_INCREMENTALENCODER_HW_H
