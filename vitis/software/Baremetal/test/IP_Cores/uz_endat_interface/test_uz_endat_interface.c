#ifdef TEST

#include "test_assert_with_exception.h"
#include "uz_endat_interface.h"
#include "mock_uz_endat_interface_hw.h" // Mock the _hw functions to isolate testing
#include "unity.h"
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U
#define TEST_ENDAT_CLK_FRQ 2510000U // intentionally not 2.5 MHz. ceil_div function will fix this
#define TEST_SAMPLING_INTERVAL 0.0001f
#define TEST_KP_PLL 628.0f
#define TEST_KI_PLL 98696.0f

struct uz_endat_interface_config_t config = {
    .base_address = TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    .endat_clk_frequency_Hz = TEST_ENDAT_CLK_FRQ, 
    .endat_encoder_bit_width_single_turn = 19U,
    .endat_encoder_bit_width_multi_turn = 12U,
    .endat_encoder_number_of_CRC_bits = 5U,
    .machine_polepairs = 4U,
    .sampling_interval_seconds = TEST_SAMPLING_INTERVAL,
    .kp_pll = TEST_KP_PLL,
    .ki_pll = TEST_KI_PLL,
    .position_mech_offset_si_single_turn = -1.276f
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_endat_interface_init_asserts(void)
{
    config.base_address = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config.base_address = TEST_BASE_ADDRESS;

    config.ip_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;

    config.endat_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config.endat_clk_frequency_Hz = TEST_ENDAT_CLK_FRQ;

    config.endat_encoder_bit_width_single_turn = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config.endat_encoder_bit_width_single_turn = 19U;    

    config.machine_polepairs = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config.machine_polepairs = 4U;  

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_enable_ip(0U, true));

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_set_mechanical_offset_endat_single_turn(0U, 0.0f));
}

void test_uz_endat_interface_set_config_asserts(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_set_config(0U));

    // set each individual bit width to its allowed max value and check if the sum (exceeding 64U) asserts
    config.endat_encoder_bit_width_multi_turn = 25U;
    config.endat_encoder_bit_width_single_turn = 25U;
    config.endat_encoder_number_of_CRC_bits = 25U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config.endat_encoder_bit_width_multi_turn = 12U;
    config.endat_encoder_bit_width_single_turn = 19U;
    config.endat_encoder_number_of_CRC_bits = 5U;
}

void test_uz_endat_inteface_set_config(void)
{
    uint32_t expected_clock_divider = 20U;
    uint32_t expected_encoder_bit_width_single_turn = 19U;
    uint32_t expected_encoder_bit_width_multi_turn = 12U;
    uint32_t expected_number_of_CRC_bits = 5U;
    float expected_sampling_interval = 0.0001f;
    float expected_kp_pll = 628.0f;
    float expected_ki_pll = 98696.0f;
    uint32_t expected_pole_pairs = 4U;
    int32_t expected_mech_offset_ticks = -106473; //equals the ticks for SI_offset=-1.276f and a 19bit encoder calculated by the uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn function

    uz_endat_interface_hw_write_endat_clock_divider_Expect(TEST_BASE_ADDRESS, expected_clock_divider);
    uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn_Expect(TEST_BASE_ADDRESS, expected_encoder_bit_width_single_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn_Expect(TEST_BASE_ADDRESS, expected_encoder_bit_width_multi_turn);
    uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits_Expect(TEST_BASE_ADDRESS, expected_number_of_CRC_bits);
    uz_endat_interface_hw_write_pll_parameters_Expect(TEST_BASE_ADDRESS, expected_sampling_interval, expected_kp_pll, expected_ki_pll);
    uz_endat_interface_hw_write_machine_pole_pairs_Expect(TEST_BASE_ADDRESS, expected_pole_pairs);
    uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn_Expect(TEST_BASE_ADDRESS, expected_mech_offset_ticks);
    uz_endat_interface_init(config);
}

void test_uz_endat_interface_getters(void)
{
    uint32_t expected_clock_divider = 20U;
    int32_t expected_mech_offset_ticks = -106473;
    uint32_t expected_position_raw_single_turn = 424242U;
    uint32_t expected_position_raw_multi_turn = 42U;
    uint32_t expected_position_multi_turn = 23U;
    float expected_position_mech_si_single_turn = 1.0f;
    float expected_position_el_si_single_turn = 2.0f;
    float expected_speed_mech_si = 3.0f;
    float expected_speed_el_si = 4.0f;
    float expected_speed_mech_rpm = 5.0f;

    uz_endat_interface_hw_write_endat_clock_divider_Expect(TEST_BASE_ADDRESS, expected_clock_divider);
    uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn_Expect(TEST_BASE_ADDRESS, config.endat_encoder_bit_width_single_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn_Expect(TEST_BASE_ADDRESS, config.endat_encoder_bit_width_multi_turn);
    uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits_Expect(TEST_BASE_ADDRESS, config.endat_encoder_number_of_CRC_bits);
    uz_endat_interface_hw_write_pll_parameters_Expect(TEST_BASE_ADDRESS, config.sampling_interval_seconds, config.kp_pll, config.ki_pll);
    uz_endat_interface_hw_write_machine_pole_pairs_Expect(TEST_BASE_ADDRESS, config.machine_polepairs);
    uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn_Expect(TEST_BASE_ADDRESS, expected_mech_offset_ticks);
    uz_endat_interface_t *instance = uz_endat_interface_init(config);

    uz_endat_interface_hw_read_position_raw_single_turn_ExpectAndReturn(TEST_BASE_ADDRESS, expected_position_raw_single_turn);
    TEST_ASSERT_EQUAL_UINT32(expected_position_raw_single_turn, uz_endat_interface_get_position_raw_single_turn(instance));

    uz_endat_interface_hw_read_position_raw_multi_turn_ExpectAndReturn(TEST_BASE_ADDRESS, expected_position_raw_multi_turn);
    TEST_ASSERT_EQUAL_UINT32(expected_position_raw_multi_turn, uz_endat_interface_get_position_raw_multi_turn(instance));

    uz_endat_interface_hw_read_position_multi_turn_ExpectAndReturn(TEST_BASE_ADDRESS, expected_position_multi_turn);
    TEST_ASSERT_EQUAL_UINT32(expected_position_multi_turn, uz_endat_interface_get_position_multi_turn(instance));

    uz_endat_interface_hw_read_position_mech_si_single_turn_ExpectAndReturn(TEST_BASE_ADDRESS, expected_position_mech_si_single_turn);
    TEST_ASSERT_EQUAL_FLOAT(expected_position_mech_si_single_turn, uz_endat_interface_get_position_mech_si_single_turn(instance));

    uz_endat_interface_hw_read_position_el_si_single_turn_ExpectAndReturn(TEST_BASE_ADDRESS, expected_position_el_si_single_turn);
    TEST_ASSERT_EQUAL_FLOAT(expected_position_el_si_single_turn, uz_endat_interface_get_position_el_si_single_turn(instance));

    uz_endat_interface_hw_read_speed_mech_si_ExpectAndReturn(TEST_BASE_ADDRESS, expected_speed_mech_si);
    TEST_ASSERT_EQUAL_FLOAT(expected_speed_mech_si, uz_endat_interface_get_speed_mech_si(instance));

    uz_endat_interface_hw_read_speed_el_si_ExpectAndReturn(TEST_BASE_ADDRESS, expected_speed_el_si);
    TEST_ASSERT_EQUAL_FLOAT(expected_speed_el_si, uz_endat_interface_get_speed_el_si(instance));

    uz_endat_interface_hw_read_speed_mech_rpm_ExpectAndReturn(TEST_BASE_ADDRESS, expected_speed_mech_rpm);
    TEST_ASSERT_EQUAL_FLOAT(expected_speed_mech_rpm, uz_endat_interface_get_speed_mech_rpm(instance));
}

#endif // TEST
