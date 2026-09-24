#ifdef TEST

#include "unity.h"

#include "uz_integrator.h"
#include <stdbool.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_integrator_zero_input_zero_output(void)
{
    float input=0.0f;
    float old_value=0.0f;
    bool clamping=false;
    float ts = 1.0f;
    float result = uz_integrator_eulerforward(input, old_value, ts, clamping);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

void test_uz_integrator_zero_to_one(void)
{
    float input = 1.0f;
    float old_value = 0.0f;
    bool clamping = false;
    float ts=1.0f;
    float result = uz_integrator_eulerforward(input, old_value,ts, clamping);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result);
}

void test_uz_integrator_one_to_two(void)
{
    float input = 1.0f;
    float old_value = 1.0f;
    bool clamping = false;
    float ts = 1.0f;
    float result = uz_integrator_eulerforward(input, old_value, ts, clamping);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, result);
}

void test_uz_integrator_clamped(void)
{
    float input = 1.0f;
    float old_value = 1.0f;
    bool clamping = true;
    float ts = 1.0f;
    float result = uz_integrator_eulerforward(input, old_value, ts, clamping);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result);
}

void test_uz_integrator_heun_zero_input_zero_output(void)
{
    float result = uz_integrator_heun(0.0f, 0.0f, 0.0f, 1.0f, false);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

void test_uz_integrator_heun_constant_slope_equals_euler(void)
{
    // Equal start/end derivatives -> trapezoidal average reduces to old + Ts*derivative.
    float result = uz_integrator_heun(1.0f, 1.0f, 0.0f, 1.0f, false);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result);
}

void test_uz_integrator_heun_averages_differing_slopes(void)
{
    // y(k) = old + Ts/2 * (d_old + d_pred) = 0 + 0.5*(0 + 2) = 1
    float result = uz_integrator_heun(0.0f, 2.0f, 0.0f, 1.0f, false);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, result);
}

void test_uz_integrator_heun_respects_old_value_and_sample_time(void)
{
    // y(k) = 5 + 0.5*0.1*(2 + 4) = 5 + 0.3 = 5.3
    float result = uz_integrator_heun(2.0f, 4.0f, 5.0f, 0.1f, false);
    TEST_ASSERT_EQUAL_FLOAT(5.3f, result);
}

void test_uz_integrator_heun_clamped_holds_old_value(void)
{
    float result = uz_integrator_heun(2.0f, 4.0f, 5.0f, 0.1f, true);
    TEST_ASSERT_EQUAL_FLOAT(5.0f, result);
}

#endif // TEST
