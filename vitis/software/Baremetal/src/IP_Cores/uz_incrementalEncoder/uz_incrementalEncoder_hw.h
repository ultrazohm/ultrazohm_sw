#ifndef UZ_INCREMENTALENCODER_HW_H
#define UZ_INCREMENTALENCODER_HW_H
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"

void uz_incrementalEncoder_hw_reset_ip_core(uint32_t base_address);
void uz_incrementalEncoder_hw_set_Position_Offset(uint32_t base_address, uint32_t increments_offset_position);
void uz_incrementalEncoder_hw_set_timer_fpga_ms(uint32_t base_address, float timer_ms);
void uz_incrementalEncoder_hw_set_pi2_inc(uint32_t base_address, float pi2_inc);
void uz_incrementalEncoder_hw_set_increments_per_turn_mechanical(uint32_t base_address, uint32_t increments_per_turn);
void uz_incrementalEncoder_hw_set_theta_el_Offset(uint32_t base_address, uint32_t increments_offset_theta_el);
void uz_incrementalEncoder_hw_set_increments_per_turn_electric(uint32_t base_address, uint32_t increments_per_turn);
void uz_incrementalEncoder_hw_set_omegaPerOverSample(uint32_t base_address,float omega_per_over_sampl); 
void uz_incrementalEncoder_hw_set_speed_timeout_value(uint32_t base_address,uint32_t timeout_ms);
void uz_incrementalEncoder_hw_set_cw_ccw_direction(uint32_t base_address,uint32_t cw_ccw_direction);

//------------------------------------------------------------------------------------------------------------------------

float uz_incrementalEncoder_hw_get_omega(uint32_t base_address);
float uz_incrementalEncoder_hw_get_direction(uint32_t base_address);
float uz_incrementalEncoder_hw_get_theta_electric(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_position(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_counterPerPeriod(uint32_t base_address);
float uz_incrementalEncoder_hw_get_omega_MA_N4(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_position_wOffset(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_Index_found(uint32_t base_address);


#endif // UZ_INCREMENTALENCODER_HW_H
