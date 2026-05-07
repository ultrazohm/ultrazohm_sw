#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_invModel_PT1_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include "uz_JL_invModel_PT1.h"

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

struct uz_JL_invModel_PT1_config_t config =
    {
        .base_adress = TEST_BASE_ADDRESS,
        .ip_core_frequency_Hz = TEST_IP_CORE_FRQ,
        .gain = 1.0f,
        .time_constant = 1.1f};

void setUp(void)
{
    {
    config.base_adress = TEST_BASE_ADDRESS;
    config.ip_core_frequency_Hz = TEST_IP_CORE_FRQ;
    config.gain = 1.0f;
    config.time_constant = 1.1f;
}
}

void tearDown(void)
{
}

void test_uz_JL_invModel_PT1_correct_init(void)
{
    uz_JL_invModel_PT1_hw_write_time_constant_Expect(TEST_BASE_ADDRESS, 1.0f / config.time_constant);
    uz_JL_invModel_PT1_hw_write_gain_Expect(TEST_BASE_ADDRESS, config.gain);
    uz_JL_invModel_PT1_t *test_instance = uz_JL_invModel_PT1_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_JL_invModel_PT1_init_fal_assert_zero_baseaddress(void)
{
    config.base_adress = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_PT1_init(config));
}

void test_uz_JL_invModel_PT1_init_fail_assert_zero_frq(void)
{
    config.ip_core_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_PT1_init(config));
}

void test_uz_JL_invModel_PT1_reset_integrator(void)
{
    uz_JL_invModel_PT1_hw_write_time_constant_Expect(TEST_BASE_ADDRESS, 1.0f / config.time_constant);
    uz_JL_invModel_PT1_hw_write_gain_Expect(TEST_BASE_ADDRESS, config.gain);
    uz_JL_invModel_PT1_t *instance = uz_JL_invModel_PT1_init(config);
    uz_JL_invModel_PT1_hw_write_reset_Expect(TEST_BASE_ADDRESS, false);
    uz_JL_invModel_PT1_hw_write_reset_Expect(TEST_BASE_ADDRESS, true);
    uz_JL_invModel_PT1_hw_write_reset_Expect(TEST_BASE_ADDRESS, false);
    uz_JL_invModel_PT1_reset_integrator(instance);
}

void test_uz_JL_invModel_PT1_set_input(void)
{
    uz_JL_invModel_PT1_hw_write_time_constant_Expect(TEST_BASE_ADDRESS, 1.0f / config.time_constant);
    uz_JL_invModel_PT1_hw_write_gain_Expect(TEST_BASE_ADDRESS, config.gain);
    uz_JL_invModel_PT1_t *instance = uz_JL_invModel_PT1_init(config);
    float Ualpha = 3.3f;
    float Ubeta = 3.3f;
    uz_JL_invModel_PT1_hw_write_Ualpha_Expect(TEST_BASE_ADDRESS, Ualpha);
    uz_JL_invModel_PT1_hw_write_Ubeta_Expect(TEST_BASE_ADDRESS, Ubeta);
    uz_JL_invModel_PT1_hw_write_Ualpha(TEST_BASE_ADDRESS, Ualpha);
    uz_JL_invModel_PT1_hw_write_Ubeta(TEST_BASE_ADDRESS, Ubeta);
}

void test_uz_JL_invModel_PT1_set_gain(void)
{
    uz_JL_invModel_PT1_hw_write_time_constant_Expect(TEST_BASE_ADDRESS, 1.0f / config.time_constant);
    uz_JL_invModel_PT1_hw_write_gain_Expect(TEST_BASE_ADDRESS, config.gain);
    uz_JL_invModel_PT1_t *instance = uz_JL_invModel_PT1_init(config);
    uz_JL_invModel_PT1_hw_write_gain_StopIgnore();
    float gain = 14.13f;
    uz_JL_invModel_PT1_hw_write_gain_Expect(TEST_BASE_ADDRESS, gain);
    uz_JL_invModel_PT1_set_gain(instance, gain);
}

void test_uz_JL_invModel_PT1_set_time_constant(void)
{
    uz_JL_invModel_PT1_hw_write_time_constant_Expect(TEST_BASE_ADDRESS, 1.0f / config.time_constant);
    uz_JL_invModel_PT1_hw_write_gain_Expect(TEST_BASE_ADDRESS, config.gain);
    uz_JL_invModel_PT1_t *instance = uz_JL_invModel_PT1_init(config);
    uz_JL_invModel_PT1_hw_write_time_constant_StopIgnore();

    float time_constant = 1.3f;
    // the time constant is inverted in the function write_time_constant since the IP-Core expects 1/time_constant in the hardware register
    uz_JL_invModel_PT1_hw_write_time_constant_Expect(TEST_BASE_ADDRESS, (1.0f / time_constant));
    uz_JL_invModel_PT1_set_time_constant(instance, time_constant);
}


#endif // TEST
