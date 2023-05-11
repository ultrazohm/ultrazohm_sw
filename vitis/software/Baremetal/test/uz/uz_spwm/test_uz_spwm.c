#ifdef TEST

#include "unity.h"

#include "uz_spwm.h"
#include "uz_Transformation.h"
#include "uz_space_vector_modulation.h"
#include "uz_signals.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_spwm_abc(void)
{
    uz_3ph_abc_t input = {
        .a = 1.0f,
        .b = 0.0f,
        .c = 0.0f};
    struct uz_DutyCycle_t out = uz_spwm_abc(input, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, out.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.DutyCycle_C);
}

void test_uz_spwm_dq(void)
{
    uz_3ph_dq_t input = {
        .d = 1.0f,
        .q = 0.0f,
        .zero = 0.0f};
    struct uz_DutyCycle_t out = uz_spwm_dq(input, 2.0f, 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, out.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.25f, out.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.25f, out.DutyCycle_C);
}

void test_uz_spwm_abc_6ph(void)
{
    uz_6ph_abc_t input = {
        .a1 = 1.0f,
        .b1 = 0.0f,
        .c1 = 0.0f,
        .a2 = 0.5f,
        .b2 = 0.0f,
        .c2 = 0.0f};
    struct uz_DutyCycle_2x3ph_t out = uz_spwm_abc_6ph(input, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, out.system1.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.system1.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.system1.DutyCycle_C);
    TEST_ASSERT_EQUAL_FLOAT(0.75f, out.system2.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.system2.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.system2.DutyCycle_C);
}

void test_uz_spwm_dq_6ph(void)
{
    uz_6ph_dq_t input = {0};
    input.d = 1.0f;
    input.q = -0.5f;
    struct uz_DutyCycle_2x3ph_t out = uz_spwm_dq_6ph(input, 3.0f, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.8203459f, out.system1.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5047528f, out.system1.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.1749012f, out.system1.DutyCycle_C);
    TEST_ASSERT_EQUAL_FLOAT(0.8726476f, out.system2.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.3177923f, out.system2.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.30956f, out.system2.DutyCycle_C);
}

#endif // TEST
