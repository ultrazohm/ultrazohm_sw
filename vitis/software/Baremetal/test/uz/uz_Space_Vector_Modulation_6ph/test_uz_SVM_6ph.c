#ifdef TEST

#include "unity.h"

#include "uz_Space_Vector_Modulation_6ph.h"
#include "uz_HAL.h"
#include "uz_complex/uz_complex.h"
#include "uz_signals/uz_signals.h"
#include "uz_math_constants.h"
#include "uz_space_vector_modulation.h"
#include "uz_Transformation.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_Space_Vector_Modulation_6ph_1(void)
{
    uz_6ph_alphabeta_t sp = {
        .alpha = -1.6f,
        .beta = -0.6f,
        .x = 0.3f,
        .y = 1.5f,
        .z1 = 0.0f,
        .z2 = 10.0f};
    float udc = 2.872925f;

    struct uz_svm_asym_6ph_CSVPWM24_out out =  uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta(sp, udc);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0486f, out.Duty_Cycle.system1.DutyCycle_A);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.5532f, out.Duty_Cycle.system1.DutyCycle_B);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.9514f, out.Duty_Cycle.system1.DutyCycle_C);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0763f, out.Duty_Cycle.system2.DutyCycle_A);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.9237f, out.Duty_Cycle.system2.DutyCycle_B);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.6943f, out.Duty_Cycle.system2.DutyCycle_C);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.shift_system1);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, out.shift_system2);
    TEST_ASSERT_TRUE(out.limited_alphabeta);
    TEST_ASSERT_TRUE(out.limited_xy);
}

void test_uz_Space_Vector_Modulation_6ph_2(void)
{
    uz_6ph_alphabeta_t sp = {
        .alpha = 1.3f,
        .beta = -0.3f,
        .x = 0.1f,
        .y = 0.02f,
        .z1 = 0.0f,
        .z2 = 10.0f};
    float udc = 2.872925f;

    struct uz_svm_asym_6ph_CSVPWM24_out out =  uz_Space_Vector_Modulation_asym_6ph_CSVPWM24_alphabeta(sp, udc);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.9137f, out.Duty_Cycle.system1.DutyCycle_A);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0863f, out.Duty_Cycle.system1.DutyCycle_B);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.2792f, out.Duty_Cycle.system1.DutyCycle_C);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.8617f, out.Duty_Cycle.system2.DutyCycle_A);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.1383f, out.Duty_Cycle.system2.DutyCycle_B);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.6462f, out.Duty_Cycle.system2.DutyCycle_C);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.shift_system1);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, out.shift_system2);
    TEST_ASSERT_FALSE(out.limited_alphabeta);
    TEST_ASSERT_FALSE(out.limited_xy);
}

#endif // TEST
