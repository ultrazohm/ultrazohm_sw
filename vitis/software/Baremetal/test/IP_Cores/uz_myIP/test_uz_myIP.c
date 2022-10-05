#ifdef TEST

#include "unity.h"

#include "test_assert_with_exception.h"
#include "uz_myIP.h"
#include "mock_uz_myIP_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_myIP_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_myIP");
}

void test_uz_myIP_test_A_times_B_equals_C(void)
{
    struct uz_myIP_config_t config={
        .base_address= TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    uz_myIP_t *instance = uz_myIP_init(config);
    int32_t a = 10;
    int32_t b = 200;
    uz_myIP_hw_write_A_Expect(TEST_BASE_ADDRESS, a);
    uz_myIP_hw_write_B_Expect(TEST_BASE_ADDRESS, b);
    uz_myIP_hw_read_C_ExpectAndReturn(TEST_BASE_ADDRESS, a * b);
    int32_t c = uz_myIP_multiply(instance, a, b);
    TEST_ASSERT_EQUAL_UINT32(a * b, c); 
}

void test_uz_myIP_fail_assert_if_base_address_is_zero(void)
{
    struct uz_myIP_config_t config={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_init(config) );
}

void test_uz_myIP_fail_assert_if_ip_frequency_is_zero(void)
{
    struct uz_myIP_config_t config={
        .base_address=TEST_BASE_ADDRESS
    };
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_init(config) );
}

void test_uz_myIP_fail_assert_if_multiply_is_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_multiply(NULL, 5, 1));
}

#endif // TEST
