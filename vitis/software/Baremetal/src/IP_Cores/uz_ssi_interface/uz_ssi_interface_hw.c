#include "uz_ssi_interface_hw.h"
#include "uz_ssi_interface_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_ssi_interface_hw_write_ssi_clock_divider(uint32_t base_address, uint32_t ssi_clk_divider) {
    uz_assert_not_zero(base_address);
    // constraint from RLS encoder datasheet, ssi clock frequency between 0.08 and 2.5 MHz
    // ssi clock frequency = (100 MHz)/(2.0 * ssi_clk_divider).
    // This results in boundaries between 20 and 100 for the clock divider
    uz_assert(ssi_clk_divider >= 20U); 
    uz_assert(ssi_clk_divider <= 625U);
    uz_axi_write_uint32(base_address + ssi_clk_divider_AXI_Data_uz_ssi_interface, ssi_clk_divider);
}

void uz_ssi_interface_hw_write_ssi_encoder_bit_width(uint32_t base_address, uint32_t ssi_encoder_bit_width) {
    uz_assert_not_zero(base_address);
    uz_assert(ssi_encoder_bit_width > 0U);
    uz_assert(ssi_encoder_bit_width <= 32U); // ip core serial data buffer for position is limited to 32 bit
    uz_axi_write_uint32(base_address + ssi_encoder_bit_width_AXI_Data_uz_ssi_interface, ssi_encoder_bit_width);
}

void uz_ssi_interface_hw_write_reciprocal_bit_width(uint32_t base_address, uint32_t ssi_encoder_bit_width) {
    uz_assert_not_zero(base_address);
    uz_assert(ssi_encoder_bit_width > 0U);
    uz_assert(ssi_encoder_bit_width <= 32U); // ip core serial data buffer for position is limited to 32 bit

    //calculate fixed-point fixdt(0,27,27) value and write it via AXI

}