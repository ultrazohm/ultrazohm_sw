#ifdef TEST

#include "unity.h"

#include "test_assert_with_exception.h"
#include "uz_errorhandler.h"
#include "mock_uz_errorhandler_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000Fu
#define TEST_IP_CORE_FRQ 100000000u

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_errorhandler_fail_assert_if_base_address_is_zero(void)
{
    struct uz_errorhandler_config_t config={
        .base_address=0
    };
    TEST_ASSERT_FAIL_ASSERT(uz_errorhandler_init(config) );
}

void test_uz_errorhandler_getError_equals(void)
{
    struct uz_errorhandler_config_t config={
        .base_address= TEST_BASE_ADDRESS
    };
    uz_errorhandler_t *instance = uz_errorhandler_init(config);  
    int32_t c = 200;
    uz_errorhandler_hw_read_ERROR_ExpectAndReturn(TEST_BASE_ADDRESS, c);
    int32_t c_ret = uz_errorhandler_getError(instance);
    TEST_ASSERT_EQUAL_INT32(c_ret, c);
}


void test_uz_errorhandler_fail_assert_if_getError_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_errorhandler_getError(NULL));
}

void test_uz_errorhandler_getMask_equals(void)
{
    struct uz_errorhandler_config_t conf={
        .base_address= TEST_BASE_ADDRESS
    };
    uz_errorhandler_t *instance1 = uz_errorhandler_init(conf);  
    int32_t m = 0x000F00F0;
    uz_errorhandler_hw_read_MASK_ExpectAndReturn(TEST_BASE_ADDRESS, m);
    int32_t m_ret = uz_errorhandler_getMask(instance1);
    TEST_ASSERT_EQUAL_INT32(m_ret, m);
}

void test_uz_errorhandler_fail_assert_if_getMask_called_with_NULL_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_errorhandler_getMask(NULL));
}

#endif // TEST
