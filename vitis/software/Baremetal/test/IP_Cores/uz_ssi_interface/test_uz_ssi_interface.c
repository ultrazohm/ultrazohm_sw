#ifdef TEST

#include "test_assert_with_exception.h"
#include "uz_ssi_interface.h"
#include "mock_uz_ssi_interface_hw.h" // Mock the _hw functions to isolate testing
#include "unity.h"
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U
#define TEST_SSI_CLK_FRQ 2510000U // intentionally not 2.5 MHz. ceil_div function will fix this
#define TEST_SAMPLING_INTERVAL 0.0001f
#define TEST_KP_PLL 628.0f
#define TEST_KI_PLL 98696.0f

struct uz_ssi_interface_config_t config = {
    .base_address = TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    .ssi_clk_frequency_Hz = TEST_SSI_CLK_FRQ, 
    .ssi_encoder_bit_width_single_turn = 19U,
    .ssi_encoder_bit_width_multi_turn = 12U,
    .ssi_encoder_number_of_status_bits = 2U,
    .position_encoding = gray_code,
    .machine_polepairs = 4U,
    .sampling_interval_seconds = TEST_SAMPLING_INTERVAL,
    .kp_pll = TEST_KP_PLL,
    .ki_pll = TEST_KI_PLL,
    .position_mech_offset_si_single_turn = -1.276f
};

struct uz_ssi_interface_outputs_t outputs;



void setUp(void)
{
}

void tearDown(void)
{
}

void test_ceil_div_asserts(void)
{
    TEST_ASSERT_FAIL_ASSERT(ceil_div(1U,0U));
}

void test_uz_ssi_interface_init_asserts(void)
{
    config.base_address = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.base_address = TEST_BASE_ADDRESS;

    config.ip_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;

    config.ssi_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.ssi_clk_frequency_Hz = TEST_SSI_CLK_FRQ;

    config.ssi_encoder_bit_width_single_turn = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.ssi_encoder_bit_width_single_turn = 19U;    

    config.machine_polepairs = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.machine_polepairs = 4U;  

    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_enable_ip(0U, true));

    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_set_mechanical_offset_ssi_single_turn(0U, 0.0f));
}

void test_uz_ssi_interface_set_config_asserts(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_set_config(0U));

    // set each individual bit width to its allowed max value and check if the sum (exceeding 64U) asserts
    config.ssi_encoder_bit_width_multi_turn = 25U;
    config.ssi_encoder_bit_width_single_turn = 25U;
    config.ssi_encoder_number_of_status_bits = 32U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.ssi_encoder_bit_width_multi_turn = 12U;
    config.ssi_encoder_bit_width_single_turn = 19U;
    config.ssi_encoder_number_of_status_bits = 2U;
}

void test_uz_ssi_inteface_set_config(void)
{
    uint32_t expected_clock_divider = 20U;
    uint32_t expected_encoder_bit_width_single_turn = 19U;
    uint32_t expected_encoder_bit_width_multi_turn = 12U;
    uint32_t expected_number_of_status_bits = 2U;
    float expected_sampling_interval = 0.0001f;
    float expected_kp_pll = 628.0f;
    float expected_ki_pll = 98696.0f;
    uint32_t expected_pole_pairs = 4U;
    float expected_mech_offset_si = -1.276f;
    enum position_encoding_t expected_encoding = gray_code;

    uz_ssi_interface_hw_write_ssi_clock_divider_Expect(TEST_BASE_ADDRESS, expected_clock_divider);
    uz_ssi_interface_hw_write_ssi_encoder_bit_width_single_turn_Expect(TEST_BASE_ADDRESS, expected_encoder_bit_width_single_turn);
    uz_ssi_interface_hw_write_ssi_encoder_bit_width_multi_turn_Expect(TEST_BASE_ADDRESS, expected_encoder_bit_width_multi_turn);
    uz_ssi_interface_hw_write_ssi_encoder_number_of_status_bits_Expect(TEST_BASE_ADDRESS, expected_number_of_status_bits);
    uz_ssi_interface_hw_write_position_is_binary_or_gray_code_Expect(TEST_BASE_ADDRESS, expected_encoding);
    uz_ssi_interface_hw_write_pll_parameters_Expect(TEST_BASE_ADDRESS, expected_sampling_interval, expected_kp_pll, expected_ki_pll);
    uz_ssi_interface_hw_write_machine_pole_pairs_Expect(TEST_BASE_ADDRESS, expected_pole_pairs);
    uz_ssi_interface_hw_write_position_mech_offset_si_single_turn_Expect(TEST_BASE_ADDRESS, expected_mech_offset_si);
    uz_ssi_interface_init(config, outputs);
}

#endif // TEST
