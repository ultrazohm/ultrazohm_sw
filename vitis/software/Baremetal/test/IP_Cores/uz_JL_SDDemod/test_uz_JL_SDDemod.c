
#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_SDDemod_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include "uz_JL_SDDemod.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_JL_SDDemod_config_t config ={
    .base_address = BASE_ADDRESS,
    .ip_clk_frequency_Hz = IP_FRQ,
    .dezimation_U = 500,
    .dezimation_I = 500,
    .clk_ratio = 100,
    .switch_edge = true,
};

void setUp(void)
{
    config.base_address = BASE_ADDRESS;
    config.ip_clk_frequency_Hz = IP_FRQ;
    config.dezimation_U = 500;
    config.dezimation_I = 500;
    config.clk_ratio = 100;
    config.switch_edge = true;
}

void tearDown(void)
{
}

void test_uz_JL_SDDemod_correct_init(void)
{
    uz_JL_SDDemod_hw_write_dezi_U_Expect(BASE_ADDRESS, config.dezimation_U);
    uz_JL_SDDemod_hw_write_dezi_I_Expect(BASE_ADDRESS, config.dezimation_I);
    uz_JL_SDDemod_hw_write_clk_ratio_Expect(BASE_ADDRESS, config.clk_ratio);
    uz_JL_SDDemod_hw_write_switch_edge_Expect(BASE_ADDRESS, config.switch_edge);
    uz_JL_SDDemod_t *test_instance = uz_JL_SDDemod_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_JL_SDDemod_init_fal_assert_zero_baseaddress(void)
{
    config.base_address = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SDDemod_init(config));
    config.base_address = BASE_ADDRESS;
}

void test_uz_JL_SDDemod_init_fail_assert_zero_frq(void)
{
    config.ip_clk_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SDDemod_init(config));
    config.ip_clk_frequency_Hz = IP_FRQ;
}

void test_uz_JL_SDDemod_set_dezimation(void)
{
    uz_JL_SDDemod_hw_write_dezi_U_Expect(BASE_ADDRESS, config.dezimation_U);
    uz_JL_SDDemod_hw_write_dezi_I_Expect(BASE_ADDRESS, config.dezimation_I);
    uz_JL_SDDemod_hw_write_clk_ratio_Expect(BASE_ADDRESS, config.clk_ratio);
    uz_JL_SDDemod_hw_write_switch_edge_Expect(BASE_ADDRESS, config.switch_edge);
    uz_JL_SDDemod_t *instance = uz_JL_SDDemod_init(config);

    uint16_t input_U = 500;
    uint16_t input_I = 500;
    uz_JL_SDDemod_hw_write_dezi_U_Expect(BASE_ADDRESS, input_U);
    uz_JL_SDDemod_hw_write_dezi_I_Expect(BASE_ADDRESS, input_I);
    uz_JL_SDDemod_set_dezimation(instance, input_U, input_I);
}

void test_uz_JL_SDDemod_set_clk_ratio(void)
{
    uz_JL_SDDemod_hw_write_dezi_U_Expect(BASE_ADDRESS, config.dezimation_U);
    uz_JL_SDDemod_hw_write_dezi_I_Expect(BASE_ADDRESS, config.dezimation_I);
    uz_JL_SDDemod_hw_write_clk_ratio_Expect(BASE_ADDRESS, config.clk_ratio);
    uz_JL_SDDemod_hw_write_switch_edge_Expect(BASE_ADDRESS, config.switch_edge);
    uz_JL_SDDemod_t *instance = uz_JL_SDDemod_init(config);

    uint16_t input = 100;
    uz_JL_SDDemod_hw_write_clk_ratio_Expect(BASE_ADDRESS, input);
    uz_JL_SDDemod_set_clk_ratio(instance, input);
}

void test_uz_JL_SDDemod_set_switch_edge(void)
{
    uz_JL_SDDemod_hw_write_dezi_U_Expect(BASE_ADDRESS, config.dezimation_U);
    uz_JL_SDDemod_hw_write_dezi_I_Expect(BASE_ADDRESS, config.dezimation_I);
    uz_JL_SDDemod_hw_write_clk_ratio_Expect(BASE_ADDRESS, config.clk_ratio);
    uz_JL_SDDemod_hw_write_switch_edge_Expect(BASE_ADDRESS, config.switch_edge);
    uz_JL_SDDemod_t *instance = uz_JL_SDDemod_init(config);

    bool input = false;
    uz_JL_SDDemod_hw_write_switch_edge_Expect(BASE_ADDRESS, input);
    uz_JL_SDDemod_set_switch_edge(instance, input);
}

void test_uz_JL_SDDemod_get_outputs(void)
{
    // Setup: Initialize the instance
    uz_JL_SDDemod_hw_write_dezi_U_Expect(BASE_ADDRESS, config.dezimation_U);
    uz_JL_SDDemod_hw_write_dezi_I_Expect(BASE_ADDRESS, config.dezimation_I);
    uz_JL_SDDemod_hw_write_clk_ratio_Expect(BASE_ADDRESS, config.clk_ratio);
    uz_JL_SDDemod_hw_write_switch_edge_Expect(BASE_ADDRESS, config.switch_edge);
    uz_JL_SDDemod_t *instance = uz_JL_SDDemod_init(config);
    TEST_ASSERT_NOT_NULL(instance);

    // Test: Get outputs
    int32_t U_expected = 12345;
    int32_t PH1_expected = 23456;
    int32_t PH2_expected = 34567;
    int32_t PH3_expected = 45678;
    int32_t PH4_expected = 56789;

    uz_JL_SDDemod_hw_read_data_out_ps_U_ExpectAndReturn(BASE_ADDRESS, U_expected);
    uz_JL_SDDemod_hw_read_data_out_ps_PH1_ExpectAndReturn(BASE_ADDRESS, PH1_expected);
    uz_JL_SDDemod_hw_read_data_out_ps_PH2_ExpectAndReturn(BASE_ADDRESS, PH2_expected);
    uz_JL_SDDemod_hw_read_data_out_ps_PH3_ExpectAndReturn(BASE_ADDRESS, PH3_expected);
    uz_JL_SDDemod_hw_read_data_out_ps_PH4_ExpectAndReturn(BASE_ADDRESS, PH4_expected);
    struct uz_JL_SDDemod_output_t output = uz_JL_SDDemod_get_outputs(instance);
    TEST_ASSERT_EQUAL_INT32(U_expected, output.data_U);
    TEST_ASSERT_EQUAL_INT32(PH1_expected, output.data_PH1);
    TEST_ASSERT_EQUAL_INT32(PH2_expected, output.data_PH2);
    TEST_ASSERT_EQUAL_INT32(PH3_expected, output.data_PH3);
    TEST_ASSERT_EQUAL_INT32(PH4_expected, output.data_PH4);
}

#endif // TEST