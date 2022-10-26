#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_exp_smooth.h"
TEST_FILE("uz_exp_smooth.c")


void test_uz_EXP_SMOOTH_NULL_pointer(void) {
    float input = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_EXP_SMOOTH_sample(NULL, input));
}

void test_uz_EXP_SMOOTH_output(void) {
    float input_array[20] = {1.365f,-1.6858f,-1.0496f,1.2703f,-0.37669f,-0.13475f,1.8061f,1.86f,1.0611f,0.29813f,1.6637f,-0.01827f,-1.336f,-0.69601f,-0.81426f,0.23319f,-1.7301f,-1.7241f,-1.3329f,1.7898f};
    float expected_filtered_array[20] = {1.365f,0.44974f,-1.4949f,-0.35364f,0.77619f,-0.3041f,0.44752f,1.8223f,1.6204f,0.83224f,0.7078f,1.1591f,-0.41357f,-1.144f,-0.73148f,-0.50002f,-0.35579f,-1.7283f,-1.6067f,-0.39608f};
    float filtered_array[20] = {0};
    float alpha = 0.3f;
    UZ_EXP_SMOOTH_t* test_instance = uz_EXP_SMOOTH_init(alpha);
    for(int i=0;i< (int)(sizeof(input_array) / sizeof(float));i++) {
        filtered_array[i] = uz_EXP_SMOOTH_sample(test_instance, input_array[i]);
        TEST_ASSERT_FLOAT_WITHIN(1e-04f, expected_filtered_array[i], filtered_array[i]);
    }
}

#endif // TEST
