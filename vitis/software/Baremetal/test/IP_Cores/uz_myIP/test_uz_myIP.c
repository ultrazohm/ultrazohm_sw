#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_myIP.h"
#include "uz_myIP_private.h" // Required to init an instance
#include "mock_uz_myIP_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

static uz_myIP instance={
    .base_address=TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_myIP_test_A_times_B_equals_C(void){
    uz_myIP* test_ptr=uz_myIP_init(&instance);
    int32_t a=-10;
    int32_t b=200;
    uz_myIP_hw_write_A_Expect(TEST_BASE_ADDRESS,a);
    uz_myIP_hw_write_B_Expect(TEST_BASE_ADDRESS,b);
    uz_myIP_hw_read_C_ExpectAndReturn(TEST_BASE_ADDRESS,a*b);
    int32_t c=uz_myIP_multiply(test_ptr,a,b);
    TEST_ASSERT_EQUAL_INT32(a*b,c);
}

void test_uz_myIP_no_multiplication_before_initialization_and_no_NULL_pointer_passed(void){
     uz_myIP test_instance_no_init={
        .base_address=TEST_BASE_ADDRESS
     };
    int32_t a=10;
    int32_t b=20;
    uz_myIP_hw_write_A_Ignore();
    uz_myIP_hw_write_B_Ignore();
    uz_myIP_hw_read_C_IgnoreAndReturn(a*b);
    TEST_ASSERT_FAIL_ASSERT(int32_t c=uz_myIP_multiply( &test_instance_no_init,a,b));
    TEST_ASSERT_FAIL_ASSERT(int32_t c=uz_myIP_multiply( NULL,a,b));
}

 void test_uz_myIP_test_ip_frq_not_zero(void){
     uz_myIP test_instance={
        .base_address=TEST_BASE_ADDRESS
     };
     
     TEST_ASSERT_FAIL_ASSERT(uz_myIP* test_ptr=uz_myIP_init(&test_instance));
 }

 void test_uz_myIP_test_base_address_not_zero(void){
     uz_myIP test_instance={
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
     };
     
     TEST_ASSERT_FAIL_ASSERT(uz_myIP* test_ptr=uz_myIP_init(&test_instance));
 }

 void test_uz_myIP_test_double_init(void){
     uz_myIP test_instance={
        .base_address=TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
     };

     uz_myIP* test_ptr=uz_myIP_init(&test_instance);
     TEST_ASSERT_EQUAL_PTR(test_ptr,&test_instance);
     TEST_ASSERT_FAIL_ASSERT(test_ptr=uz_myIP_init(&test_instance));
 }

void test_uz_myIP_test_right_pointer_returned_form_init(void){
    uz_myIP test_instance={
        .base_address=TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ
    };
    
    uz_myIP* test_ptr=uz_myIP_init(&test_instance);
    TEST_ASSERT_EQUAL_PTR(test_ptr,&test_instance);
}

void test_uz_myIP_test_init_assert_NULL(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_myIP_init(NULL));
}

#endif // TEST
