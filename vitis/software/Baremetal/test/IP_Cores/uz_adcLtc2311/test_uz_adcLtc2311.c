#ifdef TEST

#include "unity.h"
#include "uz_adcLtc2311.h"
#include "test_assert_with_exception.h"
#include "mock_uz_adcLtc2311_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>
#include <stdbool.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

// test init function

void test_uz_adcLtc2311_test_init_(void)
{
    struct uz_adcLtc2311_config_t config = {
        .base_address=TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    uz_adcLtc2311_init(config);
}

void test_uz_adcLtc2311_init_fail_assert_zero_base_address(void)
{
    struct uz_adcLtc2311_config_t config = {
        .base_address=TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(config));
}

void test_uz_adcLtc2311_init_fail_assert_zero_clock_frequency(void)
{
    struct uz_adcLtc2311_config_t config = {
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(config));
}

// test configure function

void test_uz_adcLtc2311_configure_self_not_null(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_configure(NULL));
}

void test_uz_adcLtc2311_update_conversion_factor(void)
{
    uint32_t master_select = UZ_ADCLTC2311_MASTER1;
    uint32_t channel_select = UZ_ADCLTC2311_CH2;
    int32_t conversion_factor = 10;
    uint32_t cr_return_value = 0x0;
    struct uz_adcLtc2311_config_t config = {
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .base_address = TEST_BASE_ADDRESS
    };
    uz_adcLtc2311_t* instance = uz_adcLtc2311_init(config);
    uz_adcLtc2311_set_master_select(instance, master_select);
    uz_adcLtc2311_set_channel_select(instance, channel_select);
    uz_adcLtc2311_set_conversion_factor(instance, conversion_factor);

    uz_adcLtc2311_hw_write_master_channel_Expect(TEST_BASE_ADDRESS, master_select);
    uz_adcLtc2311_hw_write_channel_Expect(TEST_BASE_ADDRESS,channel_select);
    uz_adcLtc2311_hw_write_value_Expect(TEST_BASE_ADDRESS, conversion_factor);
    uz_adcLtc2311_hw_read_cr_ExpectAndReturn(TEST_BASE_ADDRESS,cr_return_value);
    uz_adcLtc2311_hw_write_cr_Expect(TEST_BASE_ADDRESS, cr_return_value | UZ_ADCLTC2311_CR_CONV_VALUE_VALID);
}
#endif // TEST
