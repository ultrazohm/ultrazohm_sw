#ifndef UZ_SSI_INTERFACE_HW_H
#define UZ_SSI_INTERFACE_HW_H

#include <stdint.h>

void uz_ssi_interface_hw_write_ssi_clock_divider(uint32_t base_address, uint32_t ssi_clk_divider);
void uz_ssi_interface_hw_write_ssi_encoder_bit_width(uint32_t base_address, uint32_t ssi_encoder_bit_width);

#endif // UZ_SSI_INTERFACE_HW_H
