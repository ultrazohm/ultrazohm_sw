#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
TEST_FILE("uz_exp_smooth.c")
#include "uz_exp_smooth.h"

void setUp(void)
{
    
}

void tearDown(void)
{
}

void test_uz_EXP_SMOOTH_output(void) {
    float input_array[20] = {0.0379f,1.1675f,-0.2292f,-1.1343f,0.5059f,1.3563f,-0.2032f,-1.2368f,0.23f,0.9577f,-0.7103f,-1.5429f,0.1174f,1.0406f,-0.6101f,-1.3292f,0.2366f,1.1708f,-0.2176f,-1.0438f};
    float expected_filtered_array[20] = {0.03411f,1.0542f,-0.10086f,-1.031f,0.35221f,1.2559f,-0.057291f,-1.1188f,0.095115f,0.87144f,-0.55213f,-1.4438f,-0.038722f,0.93267f,-0.45582f,-1.2419f,0.088754f,1.0626f,-0.08958f,-0.94838f};
    float filtered_array[20] = {0};
    float alpha = 0.9f;
    UZ_EXP_SMOOTH_t* test_instance = UZ_EXP_SMOOTH_init(alpha);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_EXP_SMOOTH_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-01f, expected_filtered_array[i], filtered_array[i]);
    }
}


void test_uz_exp_smooth_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_exp_smooth");
}

#endif // TEST
