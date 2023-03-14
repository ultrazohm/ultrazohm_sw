#ifdef TEST

#include "unity.h"

#include "uz_PWM_duty_freq_detection.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_PWM_duty_freq_detection_hwAddresses.h"
#include "test_assert_with_exception.h"
#include "mock_uz_PWM_duty_freq_detection_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>

#define TEST_BASE_ADDRESS 0x0000000F
#define TEST_IP_CORE_FRQ 100000000U

// true = enables printf executions that output every result of the test vectors
bool debug_output = false;


struct uz_PWM_duty_freq_detection_config_t test_config = {
    .base_address = TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
    .linear_interpolation_parameters_t.a = 162.35f,
    .linear_interpolation_parameters_t.b = 20.107f      
};

struct uz_PWM_duty_freq_detection_outputs_t test_outputs = {
    .PWMdutyCycNormalized = 0.0f,
    .TempDegreesCelsius = 0.0f, /**< temperature from PWM to degrees celsius */
    .PWMFreq = 0,
    .PWMhightime = 0,
    .PWMlowtime = 0,
};

struct uz_PWM_duty_freq_detection_t {
    bool is_ready;
    struct uz_PWM_duty_freq_detection_config_t config;
    struct uz_PWM_duty_freq_detection_outputs_t outputs;
};   




void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_PWM_duty_freq_detection_successful_init(void)
{
    uz_PWM_duty_freq_detection_t *test_instance = uz_PWM_duty_freq_detection_init(test_config, test_outputs);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_PWM_duty_freq_detection_init_with_zero_base_Address(void)
{
    struct uz_PWM_duty_freq_detection_config_t config={
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .linear_interpolation_parameters_t.a = 162.35f,
        .linear_interpolation_parameters_t.b = 20.107f      
    };
    config.base_address = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(config, test_outputs));
}

void test_uz_PWM_duty_freq_detection_with_zero_ip_clk(void)
{
    struct uz_PWM_duty_freq_detection_config_t config={
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .linear_interpolation_parameters_t.a = 162.35f,
        .linear_interpolation_parameters_t.b = 20.107f      
    };
    config.ip_clk_frequency_Hz = 0;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(config, test_outputs));
}

void test_uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(void)
{
    //create test instance
    uz_PWM_duty_freq_detection_t *test_instance = uz_PWM_duty_freq_detection_init(test_config, test_outputs); 

    float dutycycle_Normalized = 0.065f;
    float temperature_degrees_celsius = 30.6597f;
    float temperature_degrees_celsius_readback = uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(test_instance, dutycycle_Normalized);
    TEST_ASSERT_EQUAL_FLOAT(temperature_degrees_celsius,temperature_degrees_celsius_readback);
}



void test_uz_PWM_duty_freq_detection_update_states(void){
    //create test instance
    uz_PWM_duty_freq_detection_t *test_instance = uz_PWM_duty_freq_detection_init(test_config, test_outputs); 

    struct uz_PWM_duty_freq_detection_outputs_t return_outputs = {
        .PWMdutyCycNormalized = 0.065f,
        .TempDegreesCelsius = 30.6597f, /**< temperature from PWM to degrees celsius */
        .PWMFreq = 0,
        .PWMhightime = 0,
        .PWMlowtime = 0,
    };

    uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized_IgnoreAndReturn(return_outputs.PWMdutyCycNormalized);
    uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks_IgnoreAndReturn(return_outputs.PWMFreq);
    uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks_IgnoreAndReturn(return_outputs.PWMhightime);
    uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks_IgnoreAndReturn(return_outputs.PWMlowtime);

    uz_PWM_duty_freq_detection_update_states(test_instance);

    TEST_ASSERT_EQUAL_FLOAT(return_outputs.TempDegreesCelsius, test_instance->outputs.TempDegreesCelsius);
    TEST_ASSERT_EQUAL_FLOAT(return_outputs.PWMdutyCycNormalized, test_instance->outputs.PWMdutyCycNormalized);
    TEST_ASSERT_EQUAL_INT(return_outputs.PWMFreq, test_instance->outputs.PWMFreq);
    TEST_ASSERT_EQUAL_INT(return_outputs.PWMhightime, test_instance->outputs.PWMhightime);
    TEST_ASSERT_EQUAL_INT(return_outputs.PWMlowtime, test_instance->outputs.PWMlowtime);


}


void test_uz_inverter_adapter_get_outputs(void) {
    //create test instance
    uz_PWM_duty_freq_detection_t *test_instance = uz_PWM_duty_freq_detection_init(test_config, test_outputs); 

    struct uz_PWM_duty_freq_detection_outputs_t return_outputs = {
        .PWMdutyCycNormalized = 0.0f,
        .TempDegreesCelsius = 0.0f, 
        .PWMFreq = 0,
        .PWMhightime = 0,
        .PWMlowtime = 0,
    };

    uz_PWM_duty_freq_detection_hw_get_PWMdutyCycNormalized_IgnoreAndReturn(test_instance->outputs.PWMdutyCycNormalized);
    uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks_IgnoreAndReturn(test_instance->outputs.PWMFreq);
    uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks_IgnoreAndReturn(test_instance->outputs.PWMhightime);
    uz_PWM_duty_freq_detection_hw_get_PWMlowtimeTicks_IgnoreAndReturn(test_instance->outputs.PWMlowtime);
   
    return_outputs = uz_PWM_duty_freq_detection_get_outputs(test_instance);

    TEST_ASSERT_EQUAL_FLOAT(return_outputs.TempDegreesCelsius, test_instance->outputs.TempDegreesCelsius);
    TEST_ASSERT_EQUAL_FLOAT(return_outputs.PWMdutyCycNormalized, test_instance->outputs.PWMdutyCycNormalized);
    TEST_ASSERT_EQUAL_INT(return_outputs.PWMFreq, test_instance->outputs.PWMFreq);
    TEST_ASSERT_EQUAL_INT(return_outputs.PWMhightime, test_instance->outputs.PWMhightime);
    TEST_ASSERT_EQUAL_INT(return_outputs.PWMlowtime, test_instance->outputs.PWMlowtime);


}




#endif // TEST
