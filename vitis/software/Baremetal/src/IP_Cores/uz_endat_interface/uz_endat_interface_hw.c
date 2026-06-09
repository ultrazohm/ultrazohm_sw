#include "uz_endat_interface_hw.h"
#include "uz_endat_interface_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_math_constants.h"

#define FRAC_RECIPROCAL_BIT_WIDTH 27
#define FRAC_SAMPLING_INTERVAL 24
#define FRAC_KP_PLL 5
#define FRAC_KI_PLL 0
#define FRAC_POSITION_SI 24
#define FRAC_SPEED_MECH_SI 16
#define FRAC_SPEED_EL_SI 12
#define FRAC_SPEED_MECH_RPM 12
#define ENDAT_NUMBER_OF_CRC_BITS 5U
#define ENDAT_MODE_COMMAND_SEND_POSITION 7U
#define ENDAT_CLOCK_DIVIDER_MIN 3U
#define ENDAT_CLOCK_DIVIDER_MAX 500U
#define ENDAT_ENCODER_BIT_WIDTH_MIN 1U
#define ENDAT_ENCODER_BIT_WIDTH_MAX 31U
#define MACHINE_POLEPAIRS_MIN 1U
#define MACHINE_POLEPAIRS_MAX 255U
#define SAMPLING_INTERVAL_MAX_SECONDS 0.0156f
#define KP_PLL_MAX 8191.0f
#define KI_PLL_MAX 262142.0f
#define SAMPLING_DELAY_CLK_TICKS_MAX 194U
#define POSITION_MECH_SI_MAX (2.0f * UZ_PIf)

void uz_endat_interface_hw_write_endat_clock_divider(uint32_t base_address, uint32_t endat_clk_divider) {
    uz_assert_not_zero_uint32(base_address);
    // constraint from endat datasheet, endat clock frequency between 100 kHz and 16 MHz
    // endat clock frequency = (100 MHz)/(2.0 * endat_clk_divider).
    // This results in boundaries between 3 and 500 for the clock divider
    uz_assert(endat_clk_divider >= ENDAT_CLOCK_DIVIDER_MIN);
    uz_assert(endat_clk_divider <= ENDAT_CLOCK_DIVIDER_MAX);

    // constraint from endat datasheet, for endat clock frequency 2...8 MHz
    // the first clock pulse has to be delayed after clock goes low for 2 microseconds
    // for 100 m cable length (can be shorter for shorter cables)
    // 2 microseconds are hardcoded into the IP-core, we activate it permanently
    // Activate feature flag when clock divider is chosen accordingly
    bool delay_first_clock = true;

    uz_axi_write_bool(base_address + delay_first_clk_on_off_AXI_Data_uz_endat_interface, delay_first_clock);
    uz_axi_write_uint32(base_address + endat_clk_divider_AXI_Data_uz_endat_interface, endat_clk_divider);
}

void uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn(uint32_t base_address, uint32_t endat_encoder_bit_width_single_turn) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(endat_encoder_bit_width_single_turn >= ENDAT_ENCODER_BIT_WIDTH_MIN);
    uz_assert(endat_encoder_bit_width_single_turn <= ENDAT_ENCODER_BIT_WIDTH_MAX); // limited by 32-bit AXI parameter interface and shift operations

    uint32_t max_encoder_value_for_bit_width = (1U << endat_encoder_bit_width_single_turn) - 1U;
    float reciprocal_bit_width_single_turn = 1.0f/((float)(max_encoder_value_for_bit_width));

    uz_axi_write_uint32(base_address + endat_encoder_bit_width_single_turn_AXI_Data_uz_endat_interface, endat_encoder_bit_width_single_turn);
    uz_axi_write_uint32(base_address + reciprocal_bit_width_single_turn_AXI_Data_uz_endat_interface, uz_convert_float_to_unsigned_fixed(reciprocal_bit_width_single_turn, FRAC_RECIPROCAL_BIT_WIDTH));
}

void uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn(uint32_t base_address, uint32_t endat_encoder_bit_width_multi_turn) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(endat_encoder_bit_width_multi_turn <= ENDAT_ENCODER_BIT_WIDTH_MAX); // limited by 32-bit AXI parameter interface
 
    uz_axi_write_uint32(base_address + endat_encoder_bit_width_multi_turn_AXI_Data_uz_endat_interface, endat_encoder_bit_width_multi_turn);
}

void uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits(uint32_t base_address, uint32_t endat_encoder_number_of_CRC_bits) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(endat_encoder_number_of_CRC_bits == ENDAT_NUMBER_OF_CRC_BITS); // endat specification has 5 CRC bits

    uz_axi_write_uint32(base_address + endat_encoder_number_of_CRC_bits_AXI_Data_uz_endat_interface, endat_encoder_number_of_CRC_bits);
}

void uz_endat_interface_hw_write_endat_mode_command(uint32_t base_address, uint32_t endat_mode_command) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(endat_mode_command == ENDAT_MODE_COMMAND_SEND_POSITION); // only receiving position information is implemented in the IP-core

    uz_axi_write_uint32(base_address + endat_mode_command_in_AXI_Data_uz_endat_interface, endat_mode_command);
}

void uz_endat_interface_hw_write_ip_core_enable(uint32_t base_address, bool ip_core_off_on) {
    uz_assert_not_zero_uint32(base_address);

    uz_axi_write_bool(base_address + endat_com_enable_AXI_Data_uz_endat_interface, ip_core_off_on);
}

void uz_endat_interface_hw_write_pll_parameters(uint32_t base_address, float sampling_interval, float kp_pll, float ki_pll) {
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

    uz_axi_write_uint32(base_address + t_sample_AXI_Data_uz_endat_interface, sampling_interval_fp);
    uz_axi_write_uint32(base_address + kp_pll_AXI_Data_uz_endat_interface, kp_pll_fp);
    uz_axi_write_uint32(base_address + ki_pll_AXI_Data_uz_endat_interface, ki_pll_fp);
}

void uz_endat_interface_hw_write_pll_debug_mode(uint32_t base_address, bool debug_on_off) {
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address + debug_off_on_AXI_Data_uz_endat_interface, debug_on_off);
}

void uz_endat_interface_hw_write_pll_debug_position(uint32_t base_address, float position_mech_si) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(position_mech_si >= 0.0f);
    uz_assert(position_mech_si <= POSITION_MECH_SI_MAX);

    uz_axi_write_uint32(base_address + position_mech_SI_debug_in_AXI_Data_uz_endat_interface, uz_convert_float_to_unsigned_fixed(position_mech_si, FRAC_POSITION_SI));
}

void uz_endat_interface_hw_write_machine_pole_pairs(uint32_t base_address, uint32_t pole_pairs) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(pole_pairs >= MACHINE_POLEPAIRS_MIN);
    uz_assert(pole_pairs <= MACHINE_POLEPAIRS_MAX); // is uint8_t inside IP core. For higher pole pair numbers, fixed-point data types in subsequent multiplications might have overflow issues

    uz_axi_write_uint32(base_address + machine_polepairs_AXI_Data_uz_endat_interface, pole_pairs);
}

void uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn(uint32_t base_address, int32_t mech_offset_ticks_single_turn) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(mech_offset_ticks_single_turn <= INT32_MAX);
    uz_assert(mech_offset_ticks_single_turn >= -INT32_MAX);
    uz_axi_write_int32(base_address + position_mech_offset_ticks_AXI_Data_uz_endat_interface, mech_offset_ticks_single_turn);
}

void uz_endat_interface_hw_write_sampling_delay_clk_ticks(uint32_t base_address, uint32_t delay_clk_ticks) {
    uz_assert_not_zero_uint32(base_address);
    uz_assert(delay_clk_ticks <= SAMPLING_DELAY_CLK_TICKS_MAX);

    uz_axi_write_uint32(base_address + sampling_delay_clk_ticks_AXI_Data_uz_endat_interface, delay_clk_ticks);
}

uint32_t uz_endat_interface_hw_read_position_raw_single_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return(uz_axi_read_uint32(base_address + position_raw_single_turn_AXI_Data_uz_endat_interface));
}

uint32_t uz_endat_interface_hw_read_position_raw_multi_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return(uz_axi_read_uint32(base_address + position_raw_multi_turn_AXI_Data_uz_endat_interface));
}

uint32_t uz_endat_interface_hw_read_position_multi_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    return(uz_axi_read_uint32(base_address + position_multi_turn_AXI_Data_uz_endat_interface));
}

float uz_endat_interface_hw_read_position_mech_si_single_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    uint32_t position_tmp = uz_axi_read_uint32(base_address + position_mech_SI_single_turn_AXI_Data_uz_endat_interface);
    return(uz_convert_unsigned_fixed_to_float(position_tmp, FRAC_POSITION_SI));
}

float uz_endat_interface_hw_read_position_el_si_single_turn(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    uint32_t position_tmp = uz_axi_read_uint32(base_address + position_el_SI_AXI_Data_uz_endat_interface);
    return(uz_convert_unsigned_fixed_to_float(position_tmp, FRAC_POSITION_SI));
}

float uz_endat_interface_hw_read_speed_mech_si(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    int32_t speed_mech_tmp = uz_axi_read_int32(base_address + speed_mech_SI_AXI_Data_uz_endat_interface);
    return(uz_convert_sfixed_to_float(speed_mech_tmp, FRAC_SPEED_MECH_SI));
}

float uz_endat_interface_hw_read_speed_el_si(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    int32_t speed_el_tmp = uz_axi_read_int32(base_address + speed_el_SI_AXI_Data_uz_endat_interface);
    return(uz_convert_sfixed_to_float(speed_el_tmp, FRAC_SPEED_EL_SI));
}

float uz_endat_interface_hw_read_speed_mech_rpm(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
    int32_t speed_mech_tmp = uz_axi_read_int32(base_address + speed_mech_rpm_AXI_Data_uz_endat_interface);
    return(uz_convert_sfixed_to_float(speed_mech_tmp, FRAC_SPEED_MECH_RPM));
}
