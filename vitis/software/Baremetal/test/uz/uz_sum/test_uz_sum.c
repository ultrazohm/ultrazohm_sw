#ifdef TEST

#include "unity.h"

#include "uz_sum.h"
#include "uz_codegen0_ert_rtw/uz_codegen0.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_sum_add_numbers(void)
{
   uz_sum_t* test_instance=uz_sum_init();
    float a=1.1f;
    float b=2.2f;
    float c=3.3f;
    float expected_result=6.6f;

    uz_sum_step(test_instance,a,b,c);
    float result=uz_sum_get_sum(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected_result,result);
    
}

void test_uz_sum_integrate(void)
{
   uz_sum_t* test_instance=uz_sum_init();
    float a=1.1f;
    float b=2.2f;
    float c=3.3f;
    float expected_result=0.00198f;

    // Call step four times with sum=6.6, integration time Ts is 1/10000
    // First call: y(0)=0
    // Second call: y(1)= 1/10000*6.6=0.00066
    // Third call: y(2)=0.00066+0.00066=0.00132
    // Last call: y(3)=0.00132+0.00066=0.00198

    // Step four times - no loop to make it explicit
    uz_sum_step(test_instance,a,b,c);
    uz_sum_step(test_instance,a,b,c);
    uz_sum_step(test_instance,a,b,c);
    uz_sum_step(test_instance,a,b,c);

    float result=uz_sum_get_integral_over_sum(test_instance);
    TEST_ASSERT_EQUAL_FLOAT(expected_result,result);
    
}

#endif // TEST
