#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_PWM_duty_freq_detection.h"
#include "mock_uz_PWM_duty_freq_detection_hw.h"
#include "uz_PWM_duty_freq_detection_hwAddresses.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_PWM_duty_freq_detection_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_clk_frequency_Hz = IP_FRQ
    };

struct linear_interpolation_parameters_t lin_inter_param= {
    .a = 100.0f,
    .b = -50.0f
};

void setUp(void)
{
}       
void tearDown(void)
{
}       

uz_PWM_duty_freq_detection_t *successful_init(struct uz_PWM_duty_freq_detection_config_t configuration);
uz_PWM_duty_freq_detection_t *successful_init(struct uz_PWM_duty_freq_detection_config_t configuration)
{   
    return(uz_PWM_duty_freq_detection_init(configuration));
}

void test_uz_PWM_duty_freq_detection_successful_init(void)
{   
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_PWM_duty_freq_detection_init_base_address_zero(void)
{
    struct uz_PWM_duty_freq_detection_config_t configuration = config;
    configuration.base_address = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(configuration));
}

void test_uz_PWM_duty_freq_detection_init_ip_clk_frequency_Hz_zero(void)
{
    struct uz_PWM_duty_freq_detection_config_t configuration = config;
    configuration.ip_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(configuration));
}

void test_uz_PWM_duty_freq_detection_get_frequency_in_Hz_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_get_frequency_in_Hz(NULL));
}

void test_uz_PWM_duty_freq_detection_get_frequency_in_Hz(void) {
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);
    float expected_freq = 12500.0f;
    float expected_period_ticks = config.ip_clk_frequency_Hz / (uint32_t)expected_freq;
    uz_PWM_duty_freq_detection_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks_ExpectAndReturn(BASE_ADDRESS, expected_period_ticks);
    float output = uz_PWM_duty_freq_detection_get_frequency_in_Hz(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected_freq, output);
}

void test_uz_PWM_duty_freq_detection_get_duty_cycle_normalized_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_get_duty_cycle_normalized(NULL));
}

void test_uz_PWM_duty_freq_detection_get_duty_cycle_normalized(void) {
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);
    float expected_duty_cycle = 0.743f;
    uz_PWM_duty_freq_detection_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks_ExpectAndReturn(BASE_ADDRESS, 10000U);
    uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks_ExpectAndReturn(BASE_ADDRESS, 7430U);
    float output = uz_PWM_duty_freq_detection_get_duty_cycle_normalized(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected_duty_cycle,output);
}

void test_uz_PWM_duty_freq_detection_get_duty_cycle_in_percent_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(NULL));
}

void test_uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(void) {
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);
    float expected_duty_cycle_percent = 74.3f;
    uz_PWM_duty_freq_detection_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks_ExpectAndReturn(BASE_ADDRESS, 10000U);
    uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks_ExpectAndReturn(BASE_ADDRESS, 7430U);
    float output = uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected_duty_cycle_percent, output);
}

void test_uz_PWM_duty_freq_detection_get_Temperature_in_degree_C_assert_negative(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(-1.0f,lin_inter_param));
}

void test_uz_PWM_duty_freq_detection_get_Temperature_in_degree_C_assert_too_high(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(1.1f,lin_inter_param));
}

void test_uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(void) {
    float duty_cycle = 0.678f;
    float expected_temp = duty_cycle* lin_inter_param.a + lin_inter_param.b;
    float output = uz_PWM_duty_freq_detection_get_Temperature_in_degree_C(duty_cycle,lin_inter_param);
    TEST_ASSERT_EQUAL_FLOAT(expected_temp,output);
}

#endif
