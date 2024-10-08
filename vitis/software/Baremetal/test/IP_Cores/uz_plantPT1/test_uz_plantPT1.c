#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_plantPT1.h"
#include "mock_uz_plantPT1_hw.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_plantPT1_config_t config =
    {
        .base_address = BASE_ADDRESS,
        .ip_core_frequency_Hz = IP_FRQ,
        .gain = 1.0f,
        .time_constant = 1.1f};

void setUp(void)
{
    config.base_address = BASE_ADDRESS;
    config.ip_core_frequency_Hz = IP_FRQ;
    config.gain = 1.0f;
    config.time_constant = 1.1f;
}

void tearDown(void)
{
}

void test_uz_plantPT1_correct_init(void)
{
    uz_plantPT1_hw_write_time_constant_Expect(BASE_ADDRESS, 1.0f / config.time_constant);
    uz_plantPT1_hw_write_gain_Expect(BASE_ADDRESS, config.gain);
    uz_plantPT1_t *test_instance = uz_plantPT1_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_plantPT1_init_fal_assert_zero_baseaddress(void)
{
    config.base_address = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_plantPT1_init(config));
}

void test_uz_plantPT1_init_fail_assert_zero_frq(void)
{
    config.ip_core_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_plantPT1_init(config));
}

void test_uz_plantPT1_reset_integrator(void)
{
    uz_plantPT1_hw_write_time_constant_Expect(BASE_ADDRESS, 1.0f / config.time_constant);
    uz_plantPT1_hw_write_gain_Expect(BASE_ADDRESS, config.gain);
    uz_plantPT1_t *instance = uz_plantPT1_init(config);
    uz_plantPT1_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_plantPT1_hw_write_reset_Expect(BASE_ADDRESS, true);
    uz_plantPT1_hw_write_reset_Expect(BASE_ADDRESS, false);
    uz_plantPT1_reset_integrator(instance);
}

void test_uz_plantPT1_set_input(void)
{
    uz_plantPT1_hw_write_time_constant_Expect(BASE_ADDRESS, 1.0f / config.time_constant);
    uz_plantPT1_hw_write_gain_Expect(BASE_ADDRESS, config.gain);
    uz_plantPT1_t *instance = uz_plantPT1_init(config);
    float input_value = 3.3f;
    uz_plantPT1_hw_write_input_Expect(BASE_ADDRESS, input_value);
    uz_plantPT1_set_input(instance, input_value);
}

void test_uz_plantPT1_set_gain(void)
{
    uz_plantPT1_hw_write_time_constant_Expect(BASE_ADDRESS, 1.0f / config.time_constant);
    uz_plantPT1_hw_write_gain_Expect(BASE_ADDRESS, config.gain);
    uz_plantPT1_t *instance = uz_plantPT1_init(config);
    uz_plantPT1_hw_write_gain_StopIgnore();
    float gain = 14.13f;
    uz_plantPT1_hw_write_gain_Expect(BASE_ADDRESS, gain);
    uz_plantPT1_set_gain(instance, gain);
}

void test_uz_plantPT1_set_time_constant(void)
{
    uz_plantPT1_hw_write_time_constant_Expect(BASE_ADDRESS, 1.0f / config.time_constant);
    uz_plantPT1_hw_write_gain_Expect(BASE_ADDRESS, config.gain);
    uz_plantPT1_t *instance = uz_plantPT1_init(config);
    uz_plantPT1_hw_write_time_constant_StopIgnore();

    float time_constant = 1.3f;
    // the time constant is inverted in the function write_time_constant since the IP-Core expects 1/time_constant in the hardware register
    uz_plantPT1_hw_write_time_constant_Expect(BASE_ADDRESS, (1.0f / time_constant));
    uz_plantPT1_set_time_constant(instance, time_constant);
}

void test_uz_plantPT1_read_output(void)
{
    uz_plantPT1_hw_write_time_constant_Expect(BASE_ADDRESS, 1.0f / config.time_constant);
    uz_plantPT1_hw_write_gain_Expect(BASE_ADDRESS, config.gain);
    uz_plantPT1_t *instance = uz_plantPT1_init(config);
    float output_expected = 3.3f;
    uz_plantPT1_hw_read_output_ExpectAndReturn(BASE_ADDRESS, output_expected);
    float output = uz_plantPT1_read_output(instance);
    TEST_ASSERT_EQUAL_FLOAT(output_expected, output);
}

#endif // TEST
