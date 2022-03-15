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
    float x = 1.1f;
    float y = uz_nn_activation_function_linear(x);
    TEST_ASSERT_EQUAL_FLOAT(1.1f, y);
    y = uz_nn_activation_function_linear(x * 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(2.2f, y);
    y = uz_nn_activation_function_linear(-x * 10.0f);
    TEST_ASSERT_EQUAL_FLOAT(-11.0f, y);
}

void test_uz_nn_activation_functions_linear_derivative(void)
{
    float x = 10.1f;
    float y = uz_nn_activation_function_linear_derivative(x);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, y);
}

void test_uz_nn_activation_functions_relu(void)
{
    float x[5] = {1.1f, -1.2f, -5.0f, 10.0f, 10.3f};
    float expected[5] = {1.1f, 0.0f, 0.0f, 10.0f, 10.3f};
    for (uint32_t i = 0U; i < 5U; i++)
    {
        float y = uz_nn_activation_function_relu(x[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

void test_uz_nn_activation_functions_relu_derivative(void)
{
    float x[5] = {1.1f, -1.2f, -5.0f, 10.0f, 10.3f};
    float expected[5] = {1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
    for (uint32_t i = 0U; i < 5U; i++)
    {
        float y = uz_nn_activation_function_relu_derivative(x[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

void test_uz_nn_activation_functions_leaky_relu(void)
{
    float x[5] = {1.1f, -1.2f, -5.0f, 10.0f, 10.3f};
    float expected[5] = {1.1f, 0.01f * (-1.2f), 0.01f * (-5.0f), 10.0f, 10.3f};
    float alpha = 0.01f;
    for (uint32_t i = 0U; i < 5U; i++)
    {
        float y = uz_nn_activation_function_leaky_relu(x[i], alpha);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

void test_uz_nn_activation_functions_leaky_relu_derivative(void)
{
    float x[5] = {1.1f, -1.2f, -5.0f, 10.0f, 10.3f};
    float alpha = 0.01f;
    float expected[5] = {1.0f, 0.01f, 0.01f, 1.0f, 1.0f};
    for (uint32_t i = 0U; i < 5U; i++)
    {
        float y = uz_nn_activation_function_leaky_relu_derivative(x[i], alpha);
        TEST_ASSERT_EQUAL_FLOAT(expected[i], y);
    }
}

void test_uz_nn_activation_functions_sigmoid(void)
{
    float input[3] = {0.0f, 1.0f, -1.0f};
    float expected_output[3] = {0.5f, 0.7310586f, 0.2689414f}; // Pre-calculated values with Matlab and single-precision
    for (uint32_t i = 0U; i < 3U; i++)
    {
        float y = uz_nn_activation_function_sigmoid_logistic(input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected_output[i], y);
    }
}

void test_uz_nn_activation_funcions_sigmoid_derivative(void)
{
    float input[3] = {0.0f, 1.0f, -1.0f};
    float expected_output[3] = {0.2500000f, 0.1966120f, 0.1966119f};
    for (uint32_t i = 0U; i < 3U; i++)
    {
        float y = uz_nn_activation_function_sigmoid_logistic_derivative(input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected_output[i], y);
    }
}

void test_uz_nn_activation_functions_sigmoid2(void)
{
    float input[3] = {0.0f, 1.0f, -1.0f};
    float expected_output[3] = {0.5f, 0.7310586f, 0.2689414f}; // Pre-calculated values with Matlab and single-precision
    for (uint32_t i = 0U; i < 3U; i++)
    {
        float y = uz_nn_activation_function_sigmoid2_logistic(input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected_output[i], y);
    }
}

void test_uz_nn_activation_funcions_sigmoid2_derivative(void)
{
    float input[3] = {0.0f, 1.0f, -1.0f};
    float expected_output[3] = {0.2500000f, 0.1966120f, 0.1966119f};
    for (uint32_t i = 0U; i < 3U; i++)
    {
        float y = uz_nn_activation_function_sigmoid2_logistic_derivative(input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected_output[i], y);
    }
}

void test_uz_nn_activation_functoins_tanh(void)
{
    float input[3] = {0.0f, 1.0f, -1.0f};
    float expected_output[3] = {0.0f, 0.7615942f, -0.7615942f};
    for (uint32_t i = 0U; i < 3U; i++)
    {
        float y = uz_nn_activation_function_tanh(input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected_output[i], y);
    }
}

void test_uz_nn_activation_functoins_tanh_derivative(void)
{
    float input[3] = {0.0f, 1.0f, -1.0f};
    float expected_output[3] = {1.0f, 0.4199743f, 0.4199743f};
    for (uint32_t i = 0U; i < 3U; i++)
    {
        float y = uz_nn_activation_function_tanh_derivative(input[i]);
        TEST_ASSERT_EQUAL_FLOAT(expected_output[i], y);
    }
}

#endif // TEST
