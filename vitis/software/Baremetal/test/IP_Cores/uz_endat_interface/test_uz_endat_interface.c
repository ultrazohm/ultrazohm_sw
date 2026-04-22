#ifdef TEST

#include "test_assert_with_exception.h"
#include "uz_endat_interface.h"
#include "mock_uz_endat_interface_hw.h" // Mock the _hw functions to isolate testing
#include "unity.h"
#include "uz_math_constants.h"
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U
#define TEST_ENDAT_CLK_FRQ 2510000U // intentionally not 2.5 MHz. ceil_div function will fix this
#define TEST_SAMPLING_INTERVAL 0.0001f
#define TEST_KP_PLL 628.0f
#define TEST_KI_PLL 98696.0f
#define TEST_ENDAT_NUMBER_OF_CRC_BITS 5U

static const struct uz_endat_interface_config_t default_config = {
    .base_address = TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    .endat_clk_frequency_Hz = TEST_ENDAT_CLK_FRQ, 
    .endat_encoder_bit_width_single_turn = 19U,
    .endat_encoder_bit_width_multi_turn = 12U,
    .machine_polepairs = 4U,
    .sampling_interval_seconds = TEST_SAMPLING_INTERVAL,
    .kp_pll = TEST_KP_PLL,
    .ki_pll = TEST_KI_PLL,
    .position_mech_offset_si_single_turn = -1.276f
};

struct uz_endat_interface_config_t config;

void setUp(void)
{
    config = default_config;
}

void tearDown(void)
{
}

static void expect_default_init_writes(void)
{
    uint32_t expected_clock_divider = 20U;
    int32_t expected_mech_offset_ticks = -106473;

    uz_endat_interface_hw_write_endat_clock_divider_Expect(TEST_BASE_ADDRESS, expected_clock_divider);
    uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn_Expect(TEST_BASE_ADDRESS, config.endat_encoder_bit_width_single_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn_Expect(TEST_BASE_ADDRESS, config.endat_encoder_bit_width_multi_turn);
    uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits_Expect(TEST_BASE_ADDRESS, TEST_ENDAT_NUMBER_OF_CRC_BITS);
    uz_endat_interface_hw_write_pll_parameters_Expect(TEST_BASE_ADDRESS, config.sampling_interval_seconds, config.kp_pll, config.ki_pll);
    uz_endat_interface_hw_write_machine_pole_pairs_Expect(TEST_BASE_ADDRESS, config.machine_polepairs);
    uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn_Expect(TEST_BASE_ADDRESS, expected_mech_offset_ticks);
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
    config.endat_encoder_bit_width_single_turn = default_config.endat_encoder_bit_width_single_turn;

    config.machine_polepairs = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config.machine_polepairs = default_config.machine_polepairs;

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_enable_ip(0U, true));

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_set_mechanical_offset_endat_single_turn(0U, 0.0f));

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_set_mode_command(0U, uz_endat_interface_send_position));
}

void test_uz_endat_interface_init_config_limit_asserts(void)
{
    config.endat_clk_frequency_Hz = 30000000U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.endat_clk_frequency_Hz = 99999U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.endat_clk_frequency_Hz = UINT32_MAX;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.endat_encoder_bit_width_single_turn = 32U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.endat_encoder_bit_width_multi_turn = 32U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.endat_encoder_bit_width_single_turn = 31U;
    config.endat_encoder_bit_width_multi_turn = 18U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.endat_encoder_bit_width_single_turn = 31U;
    config.endat_encoder_bit_width_multi_turn = 28U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.machine_polepairs = 256U;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.sampling_interval_seconds = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.sampling_interval_seconds = 0.0156f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.kp_pll = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.kp_pll = 8191.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.ki_pll = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.ki_pll = 262142.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.position_mech_offset_si_single_turn = (2.0f * UZ_PIf) + 0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.position_mech_offset_si_single_turn = (-2.0f * UZ_PIf) - 0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
    config = default_config;

    config.endat_encoder_bit_width_single_turn = 31U;
    config.position_mech_offset_si_single_turn = 2.0f * UZ_PIf;
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_init(config));
}

void test_uz_endat_interface_init_writes_config(void)
{
    expect_default_init_writes();
    uz_endat_interface_init(config);
}

void test_uz_endat_interface_getter_asserts(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_position_raw_single_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_position_raw_multi_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_position_multi_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_position_mech_si_single_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_position_el_si_single_turn(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_speed_mech_si(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_speed_el_si(0U));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_get_speed_mech_rpm(0U));
}

void test_uz_endat_interface_getters(void)
{
    uint32_t expected_position_raw_single_turn = 424242U;
    uint32_t expected_position_raw_multi_turn = 42U;
    uint32_t expected_position_multi_turn = 23U;
    float expected_position_mech_si_single_turn = 1.0f;
    float expected_position_el_si_single_turn = 2.0f;
    float expected_speed_mech_si = 3.0f;
    float expected_speed_el_si = 4.0f;
    float expected_speed_mech_rpm = 5.0f;

    expect_default_init_writes();
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

void test_uz_endat_interface_enable_ip(void)
{
    expect_default_init_writes();
    uz_endat_interface_t *instance = uz_endat_interface_init(config);

    uz_endat_interface_hw_write_ip_core_enable_Expect(TEST_BASE_ADDRESS, true);
    uz_endat_interface_enable_ip(instance, true);

    uz_endat_interface_hw_write_ip_core_enable_Expect(TEST_BASE_ADDRESS, false);
    uz_endat_interface_enable_ip(instance, false);
}

void test_uz_endat_interface_set_mode_command(void)
{
    expect_default_init_writes();
    uz_endat_interface_t *instance = uz_endat_interface_init(config);

    uz_endat_interface_hw_write_endat_mode_command_Expect(TEST_BASE_ADDRESS, uz_endat_interface_send_position);
    uz_endat_interface_set_mode_command(instance, uz_endat_interface_send_position);
}

void test_uz_endat_interface_set_mechanical_offset_endat_single_turn(void)
{
    expect_default_init_writes();
    uz_endat_interface_t *instance = uz_endat_interface_init(config);

    uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn_Expect(TEST_BASE_ADDRESS, 0);
    uz_endat_interface_set_mechanical_offset_endat_single_turn(instance, 0.0f);
}

void test_uz_endat_interface_set_mechanical_offset_endat_single_turn_asserts_on_invalid_values(void)
{
    config.endat_encoder_bit_width_single_turn = 31U;
    config.position_mech_offset_si_single_turn = 0.0f;

    uz_endat_interface_hw_write_endat_clock_divider_Expect(TEST_BASE_ADDRESS, 20U);
    uz_endat_interface_hw_write_endat_encoder_bit_width_single_turn_Expect(TEST_BASE_ADDRESS, config.endat_encoder_bit_width_single_turn);
    uz_endat_interface_hw_write_endat_encoder_bit_width_multi_turn_Expect(TEST_BASE_ADDRESS, config.endat_encoder_bit_width_multi_turn);
    uz_endat_interface_hw_write_endat_encoder_number_of_CRC_bits_Expect(TEST_BASE_ADDRESS, TEST_ENDAT_NUMBER_OF_CRC_BITS);
    uz_endat_interface_hw_write_pll_parameters_Expect(TEST_BASE_ADDRESS, config.sampling_interval_seconds, config.kp_pll, config.ki_pll);
    uz_endat_interface_hw_write_machine_pole_pairs_Expect(TEST_BASE_ADDRESS, config.machine_polepairs);
    uz_endat_interface_hw_write_position_mech_offset_ticks_single_turn_Expect(TEST_BASE_ADDRESS, 0);
    uz_endat_interface_t *instance = uz_endat_interface_init(config);

    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_set_mechanical_offset_endat_single_turn(instance, 2.0f * UZ_PIf));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_set_mechanical_offset_endat_single_turn(instance, (2.0f * UZ_PIf) + 0.1f));
    TEST_ASSERT_FAIL_ASSERT(uz_endat_interface_set_mechanical_offset_endat_single_turn(instance, (-2.0f * UZ_PIf) - 0.1f));
}

#endif // TEST
