#ifdef TEST

#include "unity.h"
#include "uz_adcLtc2311.h"
#include "test_assert_with_exception.h"
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_private.h" // Required to init an instance
#include "mock_uz_adcLtc2311_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

static uz_adcLtc2311 instance={
    .base_address=TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
};


void setUp(void)
{
    instance.is_ready = false;
}

void tearDown(void)
{
}

// test init function

void test_uz_adcLtc2311_test_init_assert_NULL(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(NULL));
}

void test_uz_adcLtc2311_test_right_pointer_returned_form_init(void)
{
    uz_adcLtc2311* test_ptr=uz_adcLtc2311_init(&instance);
    TEST_ASSERT_EQUAL_PTR(test_ptr,&instance);
}

void test_uz_adcLtc2311_test_double_init(void)
{
    uz_adcLtc2311* test_ptr=uz_adcLtc2311_init(&instance);
    TEST_ASSERT_EQUAL_PTR(test_ptr,&instance);
    TEST_ASSERT_FAIL_ASSERT(test_ptr=uz_adcLtc2311_init(&instance));
}

void test_uz_adcLtc2311_test_base_address_not_zero(void){

    uz_adcLtc2311 test_instance =
    {
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };

    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(&test_instance));
}

void test_uz_adcLtc2311_test_ip_core_frq_not_zero(void){

    uz_adcLtc2311 test_instance =
    {
        .base_address=TEST_BASE_ADDRESS
    };

    TEST_ASSERT_FAIL_ASSERT(uz_adcLtc2311_init(&test_instance));
}

#endif // TEST