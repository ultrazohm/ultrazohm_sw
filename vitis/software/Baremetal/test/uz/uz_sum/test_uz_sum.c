#ifdef TEST

#include "unity.h"

#include "uz_sum.h"

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
    TEST_ASSERT_EQUAL_FLOAT(result,expected_result);
    
}

#endif // TEST
