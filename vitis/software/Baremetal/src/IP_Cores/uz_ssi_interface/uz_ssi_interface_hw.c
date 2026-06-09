#include "uz_ssi_interface_hw.h"
#include "uz_ssi_interface_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_math_constants.h"
#include <limits.h>

#define FRAC_RECIPROCAL_BIT_WIDTH 27
#define FRAC_SAMPLING_INTERVAL 24
#define FRAC_KP_PLL 5
#define FRAC_KI_PLL 0
#define FRAC_POSITION_SI 24
#define FRAC_SPEED_MECH_SI 16
#define FRAC_SPEED_EL_SI 12
#define FRAC_SPEED_MECH_RPM 12
#define SSI_CLOCK_DIVIDER_MIN 20U
#define SSI_CLOCK_DIVIDER_MAX 625U
#define SSI_CLOCK_DIVIDER_FIRST_CLOCK_DELAY_THRESHOLD 100U
#define SSI_ENCODER_BIT_WIDTH_MIN 1U
#define SSI_ENCODER_BIT_WIDTH_MAX 31U
#define SSI_ENCODER_STATUS_BITS_MAX 32U
#define MACHINE_POLEPAIRS_MIN 1U
#define MACHINE_POLEPAIRS_MAX 255U
#define SAMPLING_INTERVAL_MAX_SECONDS 0.0156f
#define KP_PLL_MAX 8191.0f
#define KI_PLL_MAX 262142.0f
#define SAMPLING_DELAY_CLK_TICKS_MAX 100U
#define POSITION_MECH_SI_MAX (2.0f * UZ_PIf)

void uz_ssi_interface_hw_write_ssi_clock_divider(uint32_t base_address, uint32_t ssi_clk_divider) {
    uz_assert_not_zero_uint32(base_address);
    // constraint from RLS encoder datasheet, ssi clock frequency between 80 kHz and 2.5 MHz
    // ssi clock frequency = (100 MHz)/(2.0 * ssi_clk_divider).
    // This results in boundaries between 20 and 625 for the clock divider
    uz_assert(ssi_clk_divider >= SSI_CLOCK_DIVIDER_MIN);
    uz_assert(ssi_clk_divider <= SSI_CLOCK_DIVIDER_MAX);

    // constraint from RLS encoder datasheet, for ssi clock frequency above 500 kHz
    // the first clock pulse has to be delayed after clock goes low
    // Activate feature flag when clock divider is chosen accordingly
    bool delay_first_clock = false;

    if(ssi_clk_divider < SSI_CLOCK_DIVIDER_FIRST_CLOCK_DELAY_THRESHOLD) {
        delay_first_clock = true;
    } else {
        delay_first_clock = false;
    }

    uz_axi_write_bool(base_address + delay_first_clk_on_off_AXI_Data_uz_ssi_interface, delay_first_clock);
    uz_axi_write_uint32(base_address + ssi_clk_divider_AXI_Data_uz_ssi_interface, ssi_clk_divider);
}

void uz_ssi_interface_hw_write_ssi_encoder_bit_width_single_turn(uint32_t base_address, uint32_t ssi_encoder_bit_width_single_turn) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(ssi_encoder_bit_width_single_turn >= SSI_ENCODER_BIT_WIDTH_MIN);
    uz_assert(ssi_encoder_bit_width_single_turn <= SSI_ENCODER_BIT_WIDTH_MAX); // limited by 32-bit AXI parameter interface and shift operations

    uint32_t max_encoder_value_for_bit_width = (1U << ssi_encoder_bit_width_single_turn) - 1U;
    float reciprocal_bit_width_single_turn = 1.0f/((float)(max_encoder_value_for_bit_width));

    uz_axi_write_uint32(base_address + ssi_encoder_bit_width_single_turn_AXI_Data_uz_ssi_interface, ssi_encoder_bit_width_single_turn);
    uz_axi_write_uint32(base_address + reciprocal_bit_width_single_turn_AXI_Data_uz_ssi_interface, uz_convert_float_to_unsigned_fixed(reciprocal_bit_width_single_turn, FRAC_RECIPROCAL_BIT_WIDTH));
}

void uz_ssi_interface_hw_write_ssi_encoder_bit_width_multi_turn(uint32_t base_address, uint32_t ssi_encoder_bit_width_multi_turn) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(ssi_encoder_bit_width_multi_turn <= SSI_ENCODER_BIT_WIDTH_MAX); // limited by 32-bit AXI parameter interface

    uz_axi_write_uint32(base_address + ssi_encoder_bit_width_multi_turn_AXI_Data_uz_ssi_interface, ssi_encoder_bit_width_multi_turn);
}

void uz_ssi_interface_hw_write_ssi_encoder_number_of_status_bits(uint32_t base_address, uint32_t ssi_encoder_number_of_status_bits) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(ssi_encoder_number_of_status_bits <= SSI_ENCODER_STATUS_BITS_MAX); // ip core serial data buffer for status is limited to 32

    uz_axi_write_uint32(base_address + ssi_encoder_number_of_status_bits_AXI_Data_uz_ssi_interface, ssi_encoder_number_of_status_bits);
}

void uz_ssi_interface_hw_write_position_is_binary_or_gray_code(uint32_t base_address, uint32_t position_encoding) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(position_encoding <= 1U);

    uz_axi_write_bool(base_address + pos_is_binary_or_gray_AXI_Data_uz_ssi_interface, (bool)position_encoding);
}

void uz_ssi_interface_hw_write_ip_core_enable(uint32_t base_address, bool ip_core_off_on) {
    uz_assert_not_zero_uint32(base_address);

    uz_axi_write_bool(base_address + ssi_com_enable_AXI_Data_uz_ssi_interface, ip_core_off_on);
}

void uz_ssi_interface_hw_write_pll_parameters(uint32_t base_address, float sampling_interval, float kp_pll, float ki_pll) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(sampling_interval > 0.0f);
    uz_assert(sampling_interval < SAMPLING_INTERVAL_MAX_SECONDS); // fixed point range of fixdt(0,18,24)
    uz_assert(kp_pll >= 0.0f);
    uz_assert(kp_pll < KP_PLL_MAX); // fixed point range of fixdt(0,18,5)
    uz_assert(ki_pll >= 0.0f);
    uz_assert(ki_pll < KI_PLL_MAX); // fixed point range of fixdt(0,18,0)

    uint32_t sampling_interval_fp = uz_convert_float_to_unsigned_fixed(sampling_interval, FRAC_SAMPLING_INTERVAL);
    uint32_t kp_pll_fp = uz_convert_float_to_unsigned_fixed(kp_pll, FRAC_KP_PLL);
    uint32_t ki_pll_fp = uz_convert_float_to_unsigned_fixed(ki_pll, FRAC_KI_PLL);

    uz_axi_write_uint32(base_address + t_sample_AXI_Data_uz_ssi_interface, sampling_interval_fp);
    uz_axi_write_uint32(base_address + kp_pll_AXI_Data_uz_ssi_interface, kp_pll_fp);
    uz_axi_write_uint32(base_address + ki_pll_AXI_Data_uz_ssi_interface, ki_pll_fp);
}

void uz_ssi_interface_hw_write_pll_debug_mode(uint32_t base_address, bool debug_on_off) {
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + debug_off_on_AXI_Data_uz_ssi_interface, debug_on_off);
}

void uz_ssi_interface_hw_write_pll_debug_position(uint32_t base_address, float position_mech_si) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(position_mech_si >= 0.0f);
    uz_assert(position_mech_si <= POSITION_MECH_SI_MAX);

    uz_axi_write_uint32(base_address + position_mech_SI_debug_in_AXI_Data_uz_ssi_interface, uz_convert_float_to_unsigned_fixed(position_mech_si, FRAC_POSITION_SI));
}

void uz_ssi_interface_hw_write_machine_pole_pairs(uint32_t base_address, uint32_t pole_pairs) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(pole_pairs >= MACHINE_POLEPAIRS_MIN);
    uz_assert(pole_pairs <= MACHINE_POLEPAIRS_MAX); // is uint8_t inside IP core. For higher pole pair numbers, fixed-point data types in subsequent multiplications might have overflow issues

    uz_axi_write_uint32(base_address + machine_polepairs_AXI_Data_uz_ssi_interface, pole_pairs);
}

void uz_ssi_interface_hw_write_position_mech_offset_ticks_single_turn(uint32_t base_address, int32_t mech_offset_ticks_single_turn) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(mech_offset_ticks_single_turn <= INT32_MAX);
    uz_assert(mech_offset_ticks_single_turn >= -INT32_MAX);
    uz_axi_write_int32(base_address + position_mech_offset_ticks_AXI_Data_uz_ssi_interface, mech_offset_ticks_single_turn);
}

void uz_ssi_interface_hw_write_sampling_delay_clk_ticks(uint32_t base_address, uint32_t sampling_delay_clk_ticks) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(sampling_delay_clk_ticks <= SAMPLING_DELAY_CLK_TICKS_MAX); // variable delay in the IP core has a limit of 100 clock ticks for the delay
    uz_axi_write_uint32(base_address + sampling_delay_clk_ticks_AXI_Data_uz_ssi_interface, sampling_delay_clk_ticks);
}

uint32_t uz_ssi_interface_hw_read_position_raw_single_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return(uz_axi_read_uint32(base_address + position_raw_single_turn_AXI_Data_uz_ssi_interface));
}

uint32_t uz_ssi_interface_hw_read_position_raw_multi_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return(uz_axi_read_uint32(base_address + position_raw_multi_turn_AXI_Data_uz_ssi_interface));
}

uint32_t uz_ssi_interface_hw_read_position_multi_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return(uz_axi_read_uint32(base_address + position_multi_turn_AXI_Data_uz_ssi_interface));
}

uint32_t uz_ssi_interface_hw_read_ssi_encoder_status(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return(uz_axi_read_uint32(base_address + status_raw_AXI_Data_uz_ssi_interface));
}

float uz_ssi_interface_hw_read_position_mech_si_single_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    uint32_t position_tmp = uz_axi_read_uint32(base_address + position_mech_SI_single_turn_AXI_Data_uz_ssi_interface);
    return(uz_convert_unsigned_fixed_to_float(position_tmp, FRAC_POSITION_SI));
}

float uz_ssi_interface_hw_read_position_el_si_single_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    uint32_t position_tmp = uz_axi_read_uint32(base_address + position_el_SI_AXI_Data_uz_ssi_interface);
    return(uz_convert_unsigned_fixed_to_float(position_tmp, FRAC_POSITION_SI));
}

float uz_ssi_interface_hw_read_speed_mech_si(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    int32_t speed_mech_tmp = uz_axi_read_int32(base_address + speed_mech_SI_AXI_Data_uz_ssi_interface);
    return(uz_convert_sfixed_to_float(speed_mech_tmp, FRAC_SPEED_MECH_SI));
}

float uz_ssi_interface_hw_read_speed_el_si(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    int32_t speed_el_tmp = uz_axi_read_int32(base_address + speed_el_SI_AXI_Data_uz_ssi_interface);
    return(uz_convert_sfixed_to_float(speed_el_tmp, FRAC_SPEED_EL_SI));
}

float uz_ssi_interface_hw_read_speed_mech_rpm(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    int32_t speed_mech_tmp = uz_axi_read_int32(base_address + speed_mech_rpm_AXI_Data_uz_ssi_interface);
    return(uz_convert_sfixed_to_float(speed_mech_tmp, FRAC_SPEED_MECH_RPM));
}
