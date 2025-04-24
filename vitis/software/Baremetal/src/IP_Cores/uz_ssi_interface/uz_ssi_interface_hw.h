#ifndef UZ_SSI_INTERFACE_HW_H
#define UZ_SSI_INTERFACE_HW_H

#include <stdint.h>

void uz_ssi_interface_hw_write_ssi_clock_divider(uint32_t base_address, uint32_t ssi_clk_divider);
void uz_ssi_interface_hw_write_ssi_encoder_bit_width(uint32_t base_address, uint32_t ssi_encoder_bit_width);
void uz_ssi_interface_hw_write_pll_parameters(uint32_t base_address, float sampling_interval, float kp_pll, float ki_pll);
uint32_t uz_ssi_interface_hw_read_position_raw(uint32_t base_address);
float uz_ssi_interface_hw_read_position_si(uint32_t base_address);
float uz_ssi_interface_hw_read_speed_mech_si(uint32_t base_address);

#endif // UZ_SSI_INTERFACE_HW_H
