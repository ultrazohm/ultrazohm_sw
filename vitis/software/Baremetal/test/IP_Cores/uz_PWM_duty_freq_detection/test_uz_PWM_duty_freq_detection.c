#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_PWM_duty_freq_detection.h"
#include "mock_uz_PWM_duty_freq_detection_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_CLOCK_HZ 100000000U

static struct uz_PWM_duty_freq_detection_config_t config = {
    .base_address = BASE_ADDRESS,
    .ip_clk_frequency_Hz = IP_CLOCK_HZ,
};

void setUp(void) {}
void tearDown(void) {}

void test_uz_PWM_duty_freq_detection_rejects_invalid_configuration(void)
{
    struct uz_PWM_duty_freq_detection_config_t invalid = config;
    invalid.base_address = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(invalid));
    invalid = config;
    invalid.ip_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(invalid));
}

void test_uz_PWM_duty_freq_detection_reads_duty_ratio(void)
{
    uz_PWM_duty_freq_detection_t *instance = uz_PWM_duty_freq_detection_init(config);
    uz_PWM_duty_freq_detection_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks_ExpectAndReturn(BASE_ADDRESS, 10000U);
    uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks_ExpectAndReturn(BASE_ADDRESS, 7430U);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-6f, 0.743f, uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(instance));
}

void test_uz_PWM_duty_freq_detection_handles_missing_period(void)
{
    uz_PWM_duty_freq_detection_t *instance = uz_PWM_duty_freq_detection_init(config);
    uz_PWM_duty_freq_detection_hw_trigger_output_strobe_Expect(BASE_ADDRESS);
    uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks_ExpectAndReturn(BASE_ADDRESS, 0U);
    uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks_ExpectAndReturn(BASE_ADDRESS, 0U);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, uz_PWM_duty_freq_detection_get_duty_cycle_in_percent(instance));
}

#endif
