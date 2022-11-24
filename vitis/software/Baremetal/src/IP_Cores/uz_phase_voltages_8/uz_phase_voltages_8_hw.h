#ifndef UZ_PHASE_VOLTAGES_8_HW_H
#define UZ_PHASE_VOLTAGES_8_HW_H

#include "stdint.h"

void uz_phase_voltages_8_set_theta_el_offset(uint32_t base_address, float theta_el_offset);
void uz_phase_voltages_8_set_u_dc_link_voltage(uint32_t base_address, float u_dc_link_voltage);
int32_t uz_phase_voltages_8_get_Index_in(uint32_t base_address);
//void uz_phase_voltages_8_hw_set_done_delay_compensation_AXI(uint32_t base_address, _Bool done_delay_compensation_AXI);

#endif // UZ_PHASE_VOLTAGES_8.HW_H
