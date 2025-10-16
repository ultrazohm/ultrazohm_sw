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
    .ip_clk_frequency_Hz = IP_FRQ,
    .linear_interpolation_parameters_t = {
        .a = 100.0f,
        .b = -50.0f
    }
    };
struct uz_PWM_duty_freq_detection_outputs_t outputs = {
    .PWMdutyCycNormalized = 0.0f,
    .TempDegreesCelsius = 0.0f,
    .PWMFreq = 0U,
    .PWMhightime = 0U,
    .PWMlowtime = 0U
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
    return(uz_PWM_duty_freq_detection_init(configuration,outputs));
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
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(configuration,outputs));
}

void test_uz_PWM_duty_freq_detection_init_ip_clk_frequency_Hz_zero(void)
{
    struct uz_PWM_duty_freq_detection_config_t configuration = config;
    configuration.ip_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_init(configuration,outputs));
}

void test_uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius_assert_self_NULL(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(NULL, 0.5f));
}

void test_uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(void) {
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);
    float dutyCycleNormalized = 0.75f; // Example duty cycle
    float expected_temperature = dutyCycleNormalized * config.linear_interpolation_parameters_t.a + config.linear_interpolation_parameters_t.b;
    float temperature = uz_PWM_duty_freq_detection_PWMdutyCycNormalized_to_DegreesCelsius(test_instance, dutyCycleNormalized);
    TEST_ASSERT_EQUAL_FLOAT(expected_temperature, temperature);
}

void test_uz_PWM_duty_freq_detection_update_states_assert_self_NULL(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_PWM_duty_freq_detection_update_states(NULL));
}

void test_uz_PWM_duty_freq_detection_update_states(void) {
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);

    uint32_t expected_PWMFreq = 2000U;
    uint32_t expected_PWMhightime = 1500U;
    float expected_dutyCycleNormalized = (float)expected_PWMhightime / (float)expected_PWMFreq;
    float expected_temperature = expected_dutyCycleNormalized * config.linear_interpolation_parameters_t.a + config.linear_interpolation_parameters_t.b;

    uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks_ExpectAndReturn(BASE_ADDRESS, expected_PWMFreq);
    uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks_ExpectAndReturn(BASE_ADDRESS, expected_PWMhightime);

    outputs = uz_PWM_duty_freq_detection_get_outputs(test_instance);


    TEST_ASSERT_EQUAL_UINT32(expected_PWMFreq, outputs.PWMFreq);
    TEST_ASSERT_EQUAL_UINT32(expected_PWMhightime, outputs.PWMhightime);
    TEST_ASSERT_EQUAL_FLOAT(expected_dutyCycleNormalized, outputs.PWMdutyCycNormalized);
    TEST_ASSERT_EQUAL_FLOAT(expected_temperature, outputs.TempDegreesCelsius);
}

void test_uz_PWM_duty_freq_detection_get_outputs(void) {
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);

    uint32_t expected_PWMFreq = 2000U;
    uint32_t expected_PWMhightime = 1500U;
    float expected_dutyCycleNormalized = (float)expected_PWMhightime / (float)expected_PWMFreq;
    float expected_temperature = expected_dutyCycleNormalized * config.linear_interpolation_parameters_t.a + config.linear_interpolation_parameters_t.b;

    uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks_ExpectAndReturn(BASE_ADDRESS, expected_PWMFreq);
    uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks_ExpectAndReturn(BASE_ADDRESS, expected_PWMhightime);

    outputs = uz_PWM_duty_freq_detection_get_outputs(test_instance);

    TEST_ASSERT_EQUAL_UINT32(expected_PWMFreq, outputs.PWMFreq);
    TEST_ASSERT_EQUAL_UINT32(expected_PWMhightime, outputs.PWMhightime);
    TEST_ASSERT_EQUAL_FLOAT(expected_dutyCycleNormalized, outputs.PWMdutyCycNormalized);
    TEST_ASSERT_EQUAL_FLOAT(expected_temperature, outputs.TempDegreesCelsius);
}

void test_uz_PWM_duty_freq_detection_get_Temperature(void) {
    uz_PWM_duty_freq_detection_t *test_instance = successful_init(config);

    uint32_t expected_PWMFreq = 2000U;
    uint32_t expected_PWMhightime = 1500U;
    float expected_dutyCycleNormalized = (float)expected_PWMhightime / (float)expected_PWMFreq;
    float expected_temperature = expected_dutyCycleNormalized * config.linear_interpolation_parameters_t.a + config.linear_interpolation_parameters_t.b;

    uz_PWM_duty_freq_detection_hw_get_PWMFreqTicks_ExpectAndReturn(BASE_ADDRESS, expected_PWMFreq);
    uz_PWM_duty_freq_detection_hw_get_PWMhightimeTicks_ExpectAndReturn(BASE_ADDRESS, expected_PWMhightime);

    // First, update the states to ensure the temperature is calculated
    uz_PWM_duty_freq_detection_update_states(test_instance);

    float temperature = uz_PWM_duty_freq_detection_get_Temperature(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected_temperature, temperature);
}


#endif