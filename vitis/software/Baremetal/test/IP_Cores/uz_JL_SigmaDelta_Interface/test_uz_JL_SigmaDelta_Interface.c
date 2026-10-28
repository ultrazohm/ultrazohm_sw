
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
    .switch_cont_disc = false,
    .clk_dutycycle = 0.5f,
    .start_time_us = 123.0f,
    .delay_data_valid = 5,
    .sinc_sample_periods = 3,
    .use_clk_ext = false,
    .sel_pwm_trigger = false,
    .i_ph_max = 1000,
    .i_ph_min = -1000,
    .u_dc_max = 5000,
    .u_dc_min = -500,
    .en_udc = true,
    .en_ph4 = true,
    .en_ocp = true,
};

void setUp(void)
{
    config.base_address = BASE_ADDRESS;
    config.ip_clk_frequency_Hz = IP_FRQ;
    config.dezimation = 500;
    config.clk_ratio = 100;
    config.filt_input_delay = 14;
    config.switch_edge = 1;
    config.switch_cont_disc = false;
    config.clk_dutycycle = 0.5f;
    config.start_time_us = 123.0f;
    config.delay_data_valid = 5;
    config.sinc_sample_periods = 3;
    config.use_clk_ext = false;
    config.sel_pwm_trigger = false;
    config.i_ph_max = 1000;
    config.i_ph_min = -1000;
    config.u_dc_max = 5000;
    config.u_dc_min = -500;
    config.en_udc = true;
    config.en_ph4 = true;
    config.en_ocp = true;
}

void tearDown(void)
{
}

static void expect_write_config_to_pl(struct uz_JL_SigmaDelta_Interface_config_t *cfg)
{
    uz_JL_SigmaDelta_Interface_hw_write_clk_ratio_Expect(BASE_ADDRESS, cfg->clk_ratio);
    uz_JL_SigmaDelta_Interface_hw_write_data_delay_Expect(BASE_ADDRESS, cfg->filt_input_delay);
    uz_JL_SigmaDelta_Interface_hw_write_switch_edge_Expect(BASE_ADDRESS, cfg->switch_edge);
    uz_JL_SigmaDelta_Interface_hw_write_switch_cont_disc_Expect(BASE_ADDRESS, cfg->switch_cont_disc);
    uz_JL_SigmaDelta_Interface_hw_write_dezimation_Expect(BASE_ADDRESS, cfg->dezimation);
    uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle_Expect(BASE_ADDRESS, cfg->clk_dutycycle);
    uz_JL_SigmaDelta_Interface_hw_write_start_time_us_Expect(BASE_ADDRESS, cfg->start_time_us);
    uz_JL_SigmaDelta_Interface_hw_write_delay_data_valid_Expect(BASE_ADDRESS, cfg->delay_data_valid);
    uz_JL_SigmaDelta_Interface_hw_write_sinc_sample_periods_Expect(BASE_ADDRESS, cfg->sinc_sample_periods);
    uz_JL_SigmaDelta_Interface_hw_write_use_clk_ext_Expect(BASE_ADDRESS, cfg->use_clk_ext);
    uz_JL_SigmaDelta_Interface_hw_write_sel_pwm_trigger_Expect(BASE_ADDRESS, cfg->sel_pwm_trigger);
    uz_JL_SigmaDelta_Interface_hw_write_i_ph_max_Expect(BASE_ADDRESS, cfg->i_ph_max);
    uz_JL_SigmaDelta_Interface_hw_write_i_ph_min_Expect(BASE_ADDRESS, cfg->i_ph_min);
    uz_JL_SigmaDelta_Interface_hw_write_u_dc_max_Expect(BASE_ADDRESS, cfg->u_dc_max);
    uz_JL_SigmaDelta_Interface_hw_write_u_dc_min_Expect(BASE_ADDRESS, cfg->u_dc_min);
    uz_JL_SigmaDelta_Interface_hw_write_en_udc_Expect(BASE_ADDRESS, cfg->en_udc);
    uz_JL_SigmaDelta_Interface_hw_write_en_ph4_Expect(BASE_ADDRESS, cfg->en_ph4);
    uz_JL_SigmaDelta_Interface_hw_write_en_ocp_Expect(BASE_ADDRESS, cfg->en_ocp);
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

void test_uz_JL_SigmaDelta_Interface_set_switch_cont_disc(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    bool input = true;
    uz_JL_SigmaDelta_Interface_hw_write_switch_cont_disc_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_switch_cont_disc(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_set_clk_dutycycle(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    float input = 0.25f;
    uz_JL_SigmaDelta_Interface_hw_write_clk_dutycycle_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_clk_dutycycle(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_set_delay_data_valid(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uint8_t input = 9;
    uz_JL_SigmaDelta_Interface_hw_write_delay_data_valid_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_delay_data_valid(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_set_sinc_sample_periods(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uint8_t input = 5;
    uz_JL_SigmaDelta_Interface_hw_write_sinc_sample_periods_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_sinc_sample_periods(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_set_use_clk_ext(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    bool input = true;
    uz_JL_SigmaDelta_Interface_hw_write_use_clk_ext_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_use_clk_ext(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_is_data_valid(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uz_JL_SigmaDelta_Interface_hw_read_data_valid_ExpectAndReturn(BASE_ADDRESS, true);
    TEST_ASSERT_TRUE(uz_JL_SigmaDelta_Interface_is_data_valid(instance));
}

void test_uz_JL_SigmaDelta_Interface_get_outputs(void)
{
    // Setup: Initialize the instance
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);
    TEST_ASSERT_NOT_NULL(instance);

    // Test: Get outputs. The driver currently reads only PH1/PH2/PH3; the reads for
    // data_U and data_PH4 are disabled in get_outputs(), so those fields stay 0.
    int32_t PH1_expected = 23456;
    int32_t PH2_expected = 34567;
    int32_t PH3_expected = 45678;

    uz_JL_SigmaDelta_Interface_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_PH1_ExpectAndReturn(BASE_ADDRESS, PH1_expected);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_PH2_ExpectAndReturn(BASE_ADDRESS, PH2_expected);
    uz_JL_SigmaDelta_Interface_hw_read_data_out_PH3_ExpectAndReturn(BASE_ADDRESS, PH3_expected);
    struct uz_JL_SigmaDelta_Interface_output_t output = uz_JL_SigmaDelta_Interface_get_outputs(instance);
    TEST_ASSERT_EQUAL_INT32(0, output.data_U);
    TEST_ASSERT_EQUAL_INT32(PH1_expected, output.data_PH1);
    TEST_ASSERT_EQUAL_INT32(PH2_expected, output.data_PH2);
    TEST_ASSERT_EQUAL_INT32(PH3_expected, output.data_PH3);
    TEST_ASSERT_EQUAL_INT32(0, output.data_PH4);
}

void test_uz_JL_SigmaDelta_Interface_reset_data_valid_cnt(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uz_JL_SigmaDelta_Interface_hw_reset_data_valid_cnt_Expect(BASE_ADDRESS);
    uz_JL_SigmaDelta_Interface_reset_data_valid_cnt(instance);
}

void test_uz_JL_SigmaDelta_Interface_get_data_valid_cnt(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uint8_t expect_val = 7U;
    uz_JL_SigmaDelta_Interface_hw_read_data_valid_cnt_ExpectAndReturn(BASE_ADDRESS, expect_val);
    TEST_ASSERT_EQUAL_UINT8(expect_val, uz_JL_SigmaDelta_Interface_get_data_valid_cnt(instance));
}

void test_uz_JL_SigmaDelta_Interface_set_sel_pwm_trigger(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    bool input = true;
    uz_JL_SigmaDelta_Interface_hw_write_sel_pwm_trigger_Expect(BASE_ADDRESS, input);
    uz_JL_SigmaDelta_Interface_set_sel_pwm_trigger(instance, input);
}

void test_uz_JL_SigmaDelta_Interface_reset_fault(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uz_JL_SigmaDelta_Interface_hw_reset_flt_Expect(BASE_ADDRESS);
    uz_JL_SigmaDelta_Interface_reset_fault(instance);
}

void test_uz_JL_SigmaDelta_Interface_get_fault_none(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uz_JL_SigmaDelta_Interface_hw_read_flt_ps_ExpectAndReturn(BASE_ADDRESS, FAULT_NONE);
    TEST_ASSERT_EQUAL(FAULT_NONE, uz_JL_SigmaDelta_Interface_get_fault(instance));
}

void test_uz_JL_SigmaDelta_Interface_get_fault_single_cause(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    uz_JL_SigmaDelta_Interface_hw_read_flt_ps_ExpectAndReturn(BASE_ADDRESS, FAULT_PH2);
    TEST_ASSERT_EQUAL(FAULT_PH2, uz_JL_SigmaDelta_Interface_get_fault(instance));
}

void test_uz_JL_SigmaDelta_Interface_get_fault_combined_causes(void)
{
    expect_write_config_to_pl(&config);
    uz_JL_SigmaDelta_Interface_t *instance = uz_JL_SigmaDelta_Interface_init(config);

    // FLT_ps is a bit mask, so multiple causes can be active at once.
    uint32_t combined = (uint32_t)FAULT_UDC | (uint32_t)FAULT_PH1 | (uint32_t)FAULT_PH4;
    uz_JL_SigmaDelta_Interface_hw_read_flt_ps_ExpectAndReturn(BASE_ADDRESS, combined);
    enum uz_JL_SigmaDelta_Interface_fault fault = uz_JL_SigmaDelta_Interface_get_fault(instance);
    TEST_ASSERT_EQUAL(combined, (uint32_t)fault);
    TEST_ASSERT_TRUE(((uint32_t)fault & (uint32_t)FAULT_UDC) != 0U);
    TEST_ASSERT_TRUE(((uint32_t)fault & (uint32_t)FAULT_PH1) != 0U);
    TEST_ASSERT_TRUE(((uint32_t)fault & (uint32_t)FAULT_PH4) != 0U);
    TEST_ASSERT_TRUE(((uint32_t)fault & (uint32_t)FAULT_PH2) == 0U);
}

#endif // TEST
