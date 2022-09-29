#ifdef TEST

#include "test_assert_with_exception.h"
#include "unity.h"
#include "uz_space_vector_modulation.h"
#include "uz_signals.h"
#include "uz_Transformation.h"

uz_3ph_dq_t input = {0};
float theta_el_rad = 0.0f;
float V_DC_Volts = 24.0f;
void setUp(void)
{
    input.d = 0.0f;
    input.q = 0.0f;
    theta_el_rad = 0.0f;
    V_DC_Volts = 24.0f;
}

void test_uz_Space_Vector_Modulation_0_input(void) {
    struct uz_DutyCycle_t output = uz_Space_Vector_Modulation(input, V_DC_Volts, theta_el_rad);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.DutyCycle_A);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.DutyCycle_B);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.DutyCycle_C);
}

void test_uz_Space_Vector_Modulation_random_input(void) {
    input.d = -0.101298f;
    input.q = 3.22140f;
    theta_el_rad = 596.1446f;
    struct uz_DutyCycle_t output = uz_Space_Vector_Modulation(input, V_DC_Volts, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.61037f, output.DutyCycle_A);
    TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.56348f, output.DutyCycle_B);
    TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.38963f, output.DutyCycle_C);
}
#endif // TEST
