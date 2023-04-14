#ifndef UZ_INCREMENTALENCODER_HW_H
#define UZ_INCREMENTALENCODER_HW_H
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"

void uz_incrementalEncoder_hw_reset_ip_core_V26(uint32_t base_address);
void uz_incrementalEncoder_hw_set_Position_Offset_V26(uint32_t base_address, uint32_t increments_offset_position);
void uz_incrementalEncoder_hw_set_timer_fpga_ms_V26(uint32_t base_address, float timer_ms);
void uz_incrementalEncoder_hw_set_pi2_inc_V26(uint32_t base_address, float pi2_inc);
void uz_incrementalEncoder_hw_set_increments_per_turn_mechanical_V26(uint32_t base_address, uint32_t increments_per_turn);
void uz_incrementalEncoder_hw_set_theta_el_Offset_V26(uint32_t base_address, uint32_t increments_offset_theta_el);
void uz_incrementalEncoder_hw_set_increments_per_turn_electric_V26(uint32_t base_address, uint32_t increments_per_turn);
void uz_incrementalEncoder_hw_set_omegaPerOverSample_V26(uint32_t base_address,float omega_per_over_sampl);
void uz_incrementalEncoder_hw_set_speed_timeout_value_V26(uint32_t base_address,uint32_t timeout_ms);
void uz_incrementalEncoder_hw_set_cw_ccw_direction_V26(uint32_t base_address,uint32_t cw_ccw_direction);
void uz_incrementalEncoder_hw_set_d_axis_hit_Offset_V26(uint32_t base_address,uint32_t d_axis_hit_Offset_Value);

//------------------------------------------------------------------------------------------------------------------------

float uz_incrementalEncoder_hw_get_omega_V26(uint32_t base_address);
float uz_incrementalEncoder_hw_get_direction_V26(uint32_t base_address);
float uz_incrementalEncoder_hw_get_theta_electric_V26(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_position_V26(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_counterPerPeriod_V26(uint32_t base_address);
float uz_incrementalEncoder_hw_get_omega_MA_N4_V26(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_position_wOffset_V26(uint32_t base_address);
uint32_t uz_incrementalEncoder_hw_get_Index_found_V26(uint32_t base_address);


#endif // UZ_INCREMENTALENCODER_HW_H
