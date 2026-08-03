
#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_SigmaDelta_Interface_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include "uz_JL_SigmaDelta_Interface.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_JL_SigmaDelta_Interface_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_clk_frequency_Hz = IP_FRQ,
    .dezimation = 500,
    .clk_ratio = 100,
    .filt_input_delay = 14,
    .switch_edge = 1,
    .dsw_clk_en = true,
    .clk_dutycycle = 0.5f,
};

void setUp(void)
{
    config.base_address = BASE_ADDRESS;
    config.ip_clk_frequency_Hz = IP_FRQ;
    config.dezimation = 500;
    config.clk_ratio = 100;
    config.filt_input_delay = 14;
    config.switch_edge = 1;
    config.dsw_clk_en = true;
    config.clk_dutycycle = 0.5f;
}

void tearDown(void)
{
}

static void expect_write_config_to_pl(struct uz_JL_SigmaDelta_Interface_config_t *cfg)
{
    uz_JL_SigmaDelta_Interface_hw_write_clk_ratio_Expect(BASE_ADDRESS, cfg->clk_ratio);
    uz_JL_SigmaDelta_Interface_hw_write_data_delay_Expect(BASE_ADDRESS, cfg->filt_input_delay);
    uz_JL_SigmaDelta_Interface_hw_write_switch_edge_Expect(BASE_ADDRESS, cfg->switch_edge);
    uz_JL_SigmaDelta_Interface_hw_write_dezimation_Expect(BASE_ADDRESS, cfg->dezimation);
    uz_JL_SigmaDelta_Interface_hw_write_clk_dsw_en_Expect(BASE_ADDRESS, cfg->dsw_clk_en);
    uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle_Expect(BASE_ADDRESS, cfg->clk_dutycycle);
}

void test_uz_JL_SigmaDelta_Interface_correct_init(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *test_instance = uz_JL_SigmaDelta_Interface_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_JL_SigmaDelta_Interface_init_fail_assert_zero_baseaddress(void)
{
    config.base_address = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SigmaDelta_Interface_init(config));
    config.base_address = BASE_ADDRESS;
}

void test_uz_JL_SigmaDelta_Interface_init_fail_assert_zero_frq(void)
{
    config.ip_clk_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SigmaDelta_Interface_init(config));
    config.ip_clk_frequency_Hz = IP_FRQ;
}

void test_uz_JL_SigmaDelta_Interface_init_fail_assert_zero_dezimation(void)
{
    config.dezimation = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SigmaDelta_Interface_init(config));
    config.dezimation = 500U;
}

void test_uz_JL_SigmaDelta_Interface_init_fail_assert_zero_clk_ratio(void)
{
    config.clk_ratio = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SigmaDelta_Interface_init(config));
    config.clk_ratio = 100U;
}

void test_uz_JL_SigmaDelta_Interface_set_data_delay(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uint8_t input = 7;
    uz_JL_SigmaDelta_Interface_hw_write_data_delay_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_data_delay(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_set_switch_edge(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uint8_t input = 2;
    uz_JL_SigmaDelta_Interface_hw_write_switch_edge_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_switch_edge(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_set_dsw_clk_en(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    bool input = false;
    uz_JL_SigmaDelta_Interface_hw_write_clk_dsw_en_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_dsw_clk_en(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_set_clk_dutycycle(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    float input = 0.25f;
    uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_clk_dutycycle(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_get_outputs(void)
{
    // Setup: Initialize the instance
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);
    TEST_ASSERT_NOT_NULL(instance);

    // Test: Get outputs
    int32_t U_expected = 12345;
    int32_t PH1_expected = 23456;
    int32_t PH2_expected = 34567;
    int32_t PH3_expected = 45678;
    int32_t PH4_expected = 56789;

    uz_JL_SigmaDelta_Interface_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_U_ExpectAndReturn(BASE_ADDRESS, U_expected);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_PH1_ExpectAndReturn(BASE_ADDRESS, PH1_expected);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_PH2_ExpectAndReturn(BASE_ADDRESS, PH2_expected);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_PH3_ExpectAndReturn(BASE_ADDRESS, PH3_expected);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_PH4_ExpectAndReturn(BASE_ADDRESS, PH4_expected);
    struct uz_JL_SigmaDelta_Interface_output_t output = uz_JL_SigmaDelta_Interface_get_outputs(instance);
    TEST_ASSERT_EQUAL_INT32(U_expected, output.data_U);
    TEST_ASSERT_EQUAL_INT32(PH1_expected, output.data_PH1);
    TEST_ASSERT_EQUAL_INT32(PH2_expected, output.data_PH2);
    TEST_ASSERT_EQUAL_INT32(PH3_expected, output.data_PH3);
    TEST_ASSERT_EQUAL_INT32(PH4_expected, output.data_PH4);
}

#endif // TEST
