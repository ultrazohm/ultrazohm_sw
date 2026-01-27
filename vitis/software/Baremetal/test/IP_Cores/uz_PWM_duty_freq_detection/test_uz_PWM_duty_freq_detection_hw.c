#ifdef TEST

#include "unity.h"
#include "uz_PWM_duty_freq_detection_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_PWM_duty_freq_detection_hwAddresses.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks(0U));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks(void) {
    uint32_t expected_return = 1234U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + AXI_period_Data_uz_pwmdutyfreqdetection, expected_return);
    uint32_t actual_return = uz_PWM_duty_freq_detection_hw_get_PWM_period_ticks(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}

void test_uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks(0U));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks(void) {
    uint32_t expected_return = 1234U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + AXI_hightime_Data_uz_pwmdutyfreqdetection, expected_return);
    uint32_t actual_return = uz_PWM_duty_freq_detection_hw_get_PWM_hightime_ticks(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}

void test_uz_PWM_duty_freq_detection_hw_get_PWM_lowtime_ticks_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWM_lowtime_ticks(0U));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWM_lowtime_ticks(void) {
    uint32_t expected_return = 1234U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + AXI_lowtime_Data_uz_pwmdutyfreqdetection, expected_return);
    uint32_t actual_return = uz_PWM_duty_freq_detection_hw_get_PWM_lowtime_ticks(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}


#endif