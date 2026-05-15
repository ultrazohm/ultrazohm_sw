#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_invModel_ideal_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include "uz_JL_invModel_ideal.h"

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

struct uz_JL_invModel_ideal_config_t config =
    {
        .base_adress = TEST_BASE_ADDRESS,
        .ip_core_frequency_Hz = TEST_IP_CORE_FRQ,
        .Udc = 570.5f
    };

void setUp(void)
{
    {
        config.base_adress = TEST_BASE_ADDRESS;
        config.ip_core_frequency_Hz = TEST_IP_CORE_FRQ;
        config.Udc = 570.5f;
    }
}

void tearDown(void)
{
}

void test_uz_JL_invModel_ideal_correct_init(void)
{
    uz_JL_invModel_ideal_hw_write_Udc_Expect(TEST_BASE_ADDRESS, config.Udc);
    uz_JL_invModel_ideal_t *test_instance = uz_JL_invModel_ideal_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_JL_invModel_ideal_init_fal_assert_zero_baseaddress(void)
{
    config.base_adress = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_ideal_init(config));
}

void test_uz_JL_invModel_ideal_init_fail_assert_zero_frq(void)
{
    config.ip_core_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_invModel_ideal_init(config));
}

void test_uz_JL_invModel_ideal_set_Udc(void)
{
    float Udc = 570.5f;
    uz_JL_invModel_ideal_hw_write_Udc_Expect(TEST_BASE_ADDRESS, Udc);
    uz_JL_invModel_ideal_t *instance = uz_JL_invModel_ideal_init(config);
    uz_JL_invModel_ideal_hw_write_Udc_Expect(TEST_BASE_ADDRESS, Udc);
    uz_JL_invModel_ideal_set_Udc(instance, Udc);
}

void test_uz_JL_invModel_ideal_get_outputs(void)
{
    uz_JL_invModel_ideal_hw_write_Udc_Expect(TEST_BASE_ADDRESS, config.Udc);
    uz_JL_invModel_ideal_t *test_instance = uz_JL_invModel_ideal_init(config);

    uz_JL_invModel_ideal_hw_trigger_output_strobe_Expect(TEST_BASE_ADDRESS);
    uz_JL_invModel_ideal_trigger_output_strobe(test_instance);
    
    float Ua_expect = 6.4f;
    float Ub_expect = 1.1f;
    float Uc_expect = 1.1f;

    // After strobe register was high, current values can be read from AXI
    uz_JL_invModel_ideal_hw_read_out_Ua_ExpectAndReturn(TEST_BASE_ADDRESS, Ua_expect);
    uz_JL_invModel_ideal_hw_read_out_Ub_ExpectAndReturn(TEST_BASE_ADDRESS, Ub_expect);
    uz_JL_invModel_ideal_hw_read_out_Uc_ExpectAndReturn(TEST_BASE_ADDRESS, Uc_expect);

    struct uz_JL_invModel_ideal_output_t out = uz_JL_invModel_ideal_get_outputs(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(Ua_expect, out.Ua);
    TEST_ASSERT_EQUAL_FLOAT(Ub_expect, out.Ub);
    TEST_ASSERT_EQUAL_FLOAT(Uc_expect, out.Uc);
}

#endif // TEST
