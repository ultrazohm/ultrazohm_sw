#ifdef TEST


#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_PWM_duty_freq_detection_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

#include "unity.h"

#include "uz_PWM_duty_freq_detection_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(void){
    uint32_t PWMFreqTicks = 11000;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_period_Data_uz_pwmdutyfreqdetection,PWMFreqTicks);
    uint32_t PWMFreqTicks_readback = uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(PWMFreqTicks,PWMFreqTicks_readback);
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks_with_zero_base_address(void){
    uint32_t PWMFreqTicks = 11000;
    // Tell the test that we do not care how often this function is called
    uz_axi_read_uint32_IgnoreAndReturn(PWMFreqTicks);
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks(0));
}


void test_uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(void){
    uint32_t PWMhightimeTicks = 715;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_hightime_Data_uz_pwmdutyfreqdetection,PWMhightimeTicks);
    uint32_t PWMhightimeTicks_readback = uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(PWMhightimeTicks,PWMhightimeTicks_readback);
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks_zero_base_address(void){
    uint32_t PWMhightimeTicks = 715;
    // Tell the test that we do not care how often this function is called
    uz_axi_read_uint32_IgnoreAndReturn(PWMhightimeTicks);
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks(0));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(void){
    uint32_t PWMlowtimeTicks = 10284;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_lowtime_Data_uz_pwmdutyfreqdetection,PWMlowtimeTicks);
    uint32_t PWMlowtimeTicks_readback = uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(PWMlowtimeTicks,PWMlowtimeTicks_readback);
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks_zero_base_address(void){
    uint32_t PWMlowtimeTicks = 10284;
    // Tell the test that we do not care how often this function is called
    uz_axi_read_uint32_IgnoreAndReturn(PWMlowtimeTicks);
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks(0));
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized(void){
    uint32_t axi_read_tempAsDutyCyc = 139586437; //value in Q31 format
    float tempAsDutyCyc_returnedFloat = 0.065f;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + AXI_dutycyc_Data_uz_pwmdutyfreqdetection, axi_read_tempAsDutyCyc);
    float tempAsDutyCyc_returnedFloat_readback = uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(tempAsDutyCyc_returnedFloat,tempAsDutyCyc_returnedFloat_readback); 
}

void test_uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized_zero_base_address(void){
    uint32_t axi_read_tempAsDutyCyc = 139586437; //value in Q31 format
    // Tell the test that we do not care how often this function is called
    uz_axi_read_uint32_IgnoreAndReturn(axi_read_tempAsDutyCyc);
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized(0));

}


#endif // TEST
