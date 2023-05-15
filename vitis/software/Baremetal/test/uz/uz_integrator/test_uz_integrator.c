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
y
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

#endif // TEST
