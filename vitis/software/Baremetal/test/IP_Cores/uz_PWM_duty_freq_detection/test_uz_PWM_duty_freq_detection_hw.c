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

void test_uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(0U));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(void) {
    uint32_t expected_return = 1234U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + AXI_period_Data_uz_pwmdutyfreqdetection, expected_return);
    uint32_t actual_return = uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(0U));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(void) {
    uint32_t expected_return = 1234U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + AXI_hightime_Data_uz_pwmdutyfreqdetection, expected_return);
    uint32_t actual_return = uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(0U));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(void) {
    uint32_t expected_return = 1234U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + AXI_lowtime_Data_uz_pwmdutyfreqdetection, expected_return);
    uint32_t actual_return = uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}


#endif