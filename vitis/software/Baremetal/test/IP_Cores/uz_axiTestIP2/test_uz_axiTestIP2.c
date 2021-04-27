#ifdef TEST

#include "unity.h"

#include "uz_axiTestIP2.h"
#include "uz_axiTestIP2_private.h"
#include "mock_uz_axiTestIP2_hw.h"

#define TEST_BASE_ADDRESS 0x0000000F
static uz_axiTestIP2 test_instance={
    .base_address=TEST_BASE_ADDRESS  
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_axiTestIP2_multiply_a_times_b(void)
{
    uz_axiTestIP2* myInstancePtr=uz_axiTestIP2_init(&test_instance);
    int a=-10;
    uz_axiTestIP2_hw_write_A_int32_Expect(TEST_BASE_ADDRESS, a);
    int b=10;
    uz_axiTestIP2_hw_write_B_int32_Expect(TEST_BASE_ADDRESS,b);
    uz_axiTestIP2_hw_read_C_int32_ExpectAndReturn(TEST_BASE_ADDRESS,a*b);
    int c=uz_axiTestIP2_multiply(myInstancePtr, a,b);
    TEST_ASSERT_EQUAL_INT(a*b,c);
}  

#endif // TEST
