#include "uz_ssi_interface_hw.h"
#include "uz_ssi_interface_hwAddresses.h"
#include "../../uz/uz_AXI.h"

#define FRAC_RECIPROCAL_BIT_WIDTH 27
#define FRAC_SAMPLING_INTERVAL 24
#define FRAC_KP_PLL 5
#define FRAC_KI_PLL 0
#define FRAC_POSITION_SI 24
#define FRAC_SPEED_MECH_SI 16

void uz_ssi_interface_hw_write_ssi_clock_divider(uint32_t base_address, uint32_t ssi_clk_divider) {
    uz_assert_not_zero_uint32(base_address);
    // constraint from RLS encoder datasheet, ssi clock frequency between 80 kHz and 2.5 MHz
    // ssi clock frequency = (100 MHz)/(2.0 * ssi_clk_divider).
    // This results in boundaries between 20 and 625 for the clock divider
    uz_assert(ssi_clk_divider >= 20U); 
    uz_assert(ssi_clk_divider <= 625U);

    // constraint from RLS encoder datasheet, for ssi clock frequency above 500 kHz
    // the first clock pulse has to be delayed after clock goes low
    // Activate feature flag when clock divider is chosen accordingly
    bool delay_first_clock = false;

    if(ssi_clk_divider < 100U) {
        delay_first_clock = true;
    } else {
        delay_first_clock = false;
    }

    uz_axi_write_bool(base_address + delay_first_clk_on_off_AXI_Data_uz_ssi_interface, delay_first_clock);
    uz_axi_write_uint32(base_address + ssi_clk_divider_AXI_Data_uz_ssi_interface, ssi_clk_divider);
}

void uz_ssi_interface_hw_write_ssi_encoder_bit_width(uint32_t base_address, uint32_t ssi_encoder_bit_width) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(ssi_encoder_bit_width > 0U);
    uz_assert(ssi_encoder_bit_width <= 32U); // ip core serial data buffer for position is limited to 32 bit

    uint32_t max_encoder_value_for_bit_width = (1U << ssi_encoder_bit_width) - 1U;
    float reciprocal_bit_width = 1.0f/((float)(max_encoder_value_for_bit_width));

    uz_axi_write_uint32(base_address + ssi_encoder_bit_width_AXI_Data_uz_ssi_interface, ssi_encoder_bit_width);
    uz_axi_write_uint32(base_address + reciprocal_bit_width_AXI_Data_uz_ssi_interface, uz_convert_float_to_unsigned_fixed(reciprocal_bit_width, FRAC_RECIPROCAL_BIT_WIDTH));
}

void uz_ssi_interface_hw_write_pll_parameters(uint32_t base_address, float sampling_interval, float kp_pll, float ki_pll) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(sampling_interval > 0.0f);
    uz_assert(sampling_interval < 0.0156f); // fixed point range of fixdt(0,18,24)
    uz_assert(kp_pll >= 0.0f);
    uz_assert(kp_pll < 8191.0f); // fixed point range of fixdt(0,18,5)
    uz_assert(ki_pll >= 0.0f);
    uz_assert(ki_pll < 262142.0f); // fixed point range of fixdt(0,18,0)

    uint32_t sampling_interval_fp = uz_convert_float_to_unsigned_fixed(sampling_interval, FRAC_SAMPLING_INTERVAL);
    uint32_t kp_pll_fp = uz_convert_float_to_unsigned_fixed(kp_pll, FRAC_KP_PLL);
    uint32_t ki_pll_fp = uz_convert_float_to_unsigned_fixed(ki_pll, FRAC_KI_PLL);

    uz_axi_write_uint32(base_address + t_sample_AXI_Data_uz_ssi_interface, sampling_interval_fp);
    uz_axi_write_uint32(base_address + kp_pll_AXI_Data_uz_ssi_interface, kp_pll_fp);
    uz_axi_write_uint32(base_address + ki_pll_AXI_Data_uz_ssi_interface, ki_pll_fp);
}

uint32_t uz_ssi_interface_hw_read_position_raw(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return uz_axi_read_uint32(base_address + position_raw_AXI_Data_uz_ssi_interface);
}

float uz_ssi_interface_hw_read_position_si(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    uint32_t position_tmp = uz_axi_read_uint32(base_address + position_mech_SI_AXI_Data_uz_ssi_interface);
    return uz_convert_unsigned_fixed_to_float(position_tmp, FRAC_POSITION_SI);
}

float uz_ssi_interface_hw_read_speed_mech_si(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    int32_t speed_mech_tmp = uz_axi_read_int32(base_address + speed_mech_SI_AXI_Data_uz_ssi_interface);
    return uz_convert_sfixed_to_float(speed_mech_tmp, FRAC_SPEED_MECH_SI);
}