
#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_JL_SDDemod_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include "uz_JL_SDDemod.h"

#define BASE_ADDRESS 0x0000000FU
#define IP_FRQ 100000000U

struct uz_JL_SDDemod_config_t config ={
    .base_address = BASE_ADDRESS,
    .ip_clk_frequency_Hz = IP_FRQ,
    .R_axi = 500,
};

void setUp(void)
{
    config.base_address = BASE_ADDRESS;
    config.ip_clk_frequency_Hz = IP_FRQ;
    config.R_axi = 500;
}

void tearDown(void)
{
}

void test_uz_JL_SDDemod_correct_init(void)
{
    uz_JL_SDDemod_hw_write_R_axi_Expect(BASE_ADDRESS, config.R_axi);
    uz_JL_SDDemod_t *test_instance = uz_JL_SDDemod_init(config);
    TEST_ASSERT_NOT_NULL(test_instance);
}

void test_uz_JL_SDDemod_init_fal_assert_zero_baseaddress(void)
{
    config.base_address = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SDDemod_init(config));
    config.base_address = BASE_ADDRESS;
}

void test_uz_JL_SDDemod_init_fail_assert_zero_frq(void)
{
    config.ip_clk_frequency_Hz = 0U; // Set to zero to trigger assertion
    TEST_ASSERT_FAIL_ASSERT(uz_JL_SDDemod_init(config));
    config.ip_clk_frequency_Hz = IP_FRQ;
}

void test_uz_JL_SDDemod_set_Raxi(void)
{
    uz_JL_SDDemod_hw_write_R_axi_Expect(BASE_ADDRESS, config.R_axi);
    uz_JL_SDDemod_t *instance = uz_JL_SDDemod_init(config);

    uint16_t input = 500;
    uz_JL_SDDemod_hw_write_R_axi_Expect(BASE_ADDRESS, input);
    uz_JL_SDDemod_set_Raxi(instance, input);
}

void test_uz_JL_SDDemod_get_outputs(void)
{
    // Setup: Initialize the instance
    uz_JL_SDDemod_hw_write_R_axi_Expect(BASE_ADDRESS, config.R_axi);
    uz_JL_SDDemod_t *instance = uz_JL_SDDemod_init(config);
    TEST_ASSERT_NOT_NULL(instance);

    // Test: Get outputs
    int32_t expected = 12345;
    uz_JL_SDDemod_hw_read_data_ExpectAndReturn(BASE_ADDRESS, expected);
    struct uz_JL_SDDemod_output_t output = uz_JL_SDDemod_get_outputs(instance);
    TEST_ASSERT_EQUAL_INT32(expected, output.data);
}

#endif // TEST