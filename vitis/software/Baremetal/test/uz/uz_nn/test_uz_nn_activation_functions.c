#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_nn_activation_functions.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_nn_activation_functions_linear(void)
{
    float x = 1.1;
    float y = uz_nn_activation_function_linear(x);
    TEST_ASSERT_EQUAL_FLOAT(1.1, y);
    y = uz_nn_activation_function_linear(x * 2);
    TEST_ASSERT_EQUAL_FLOAT(2.2, y);
    y = uz_nn_activation_function_linear(-x * 10);
    TEST_ASSERT_EQUAL_FLOAT(-11.0, y);
}

void test_uz_nn_activation_functions_linear_derivative(void)
{
    float x = 10.1;
    float y = uz_nn_activation_function_linear_derivative(x);
    TEST_ASSERT_EQUAL_FLOAT(1.0, y);
}

void test_uz_nn_activation_functions_relu(void)
{
    float x[5] = {1.1, -1.2, -5.0, 10.0, 10.3};
    float expected[5] = {1.1, 0.0, 0.0, 10.0, 10.3};
    for (size_t i = 0; i < 5; i++)
    {
        float y = uz_nn_activation_function_relu(x[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

void test_uz_nn_activation_functions_relu_derivative(void)
{
    float x[5]        = {1.1, -1.2, -5.0, 10.0, 10.3};
    float expected[5] = {1.0,  0.0,  0.0,  1.0,  1.0};
    for (size_t i = 0; i < 5; i++)
    {
        float y = uz_nn_activation_function_relu_derivative(x[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

void test_uz_nn_activation_functions_leaky_relu(void){
    float x[5]        = {1.1,       -1.2,        -5.0,  10.0, 10.3};
    float expected[5] = {1.1, 0.01*(-1.2), 0.01*(-5.0), 10.0, 10.3};
    float alpha=0.01;
    for (size_t i = 0; i < 5; i++)
    {
        float y = uz_nn_activation_function_leaky_relu(x[i],alpha);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

void test_uz_nn_activation_functions_leaky_relu_derivative(void){
    float x[5]        = {1.1,       -1.2,        -5.0,  10.0, 10.3};
    float alpha=0.01;
    float expected[5] = {1.0, 0.01, 0.01, 1.0, 1.0};
    for (size_t i = 0; i < 5; i++)
    {
        float y = uz_nn_activation_function_leaky_relu_derivative(x[i],alpha);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

#endif // TEST
