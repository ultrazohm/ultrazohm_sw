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
    .machine_polepairs = 4U,
    .ssi_encoder_bit_width = 19U,
    .sampling_interval_seconds = TEST_SAMPLING_INTERVAL,
    .kp_pll = TEST_KP_PLL,
    .ki_pll = TEST_KI_PLL
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

    config.ssi_encoder_bit_width = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.ssi_encoder_bit_width = 19U;    

    config.machine_polepairs = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_init(config, outputs));
    config.machine_polepairs = 1U;  
}

void test_uz_ssi_interface_set_config_asserts(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_ssi_interface_set_config(0U));
}

void test_uz_ssi_inteface_set_config(void)
{
    uint32_t expected_clock_divider = 20U;
    uint32_t expected_encoder_bit_width = 19U;
    float expected_sampling_interval = 0.0001f;
    float expected_kp_pll = 628.0f;
    float expected_ki_pll = 98696.0f;

    uz_ssi_interface_hw_write_ssi_clock_divider_Expect(TEST_BASE_ADDRESS, expected_clock_divider);
    uz_ssi_interface_hw_write_ssi_encoder_bit_width_Expect(TEST_BASE_ADDRESS, expected_encoder_bit_width);
    uz_ssi_interface_hw_write_pll_parameters_Expect(TEST_BASE_ADDRESS, expected_sampling_interval, expected_kp_pll, expected_ki_pll);
    uz_ssi_interface_init(config, outputs);
}

#endif // TEST
