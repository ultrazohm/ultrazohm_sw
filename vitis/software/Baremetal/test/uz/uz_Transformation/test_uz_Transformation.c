#ifdef TEST

#include "unity.h"

#include "uz_Transformation.h"

struct uz_UVW_t UVW_system = {0}; 
void setUp_UVW(void)
{
    UVW_system.U = 0.0f;
    UVW_system.V = 0.0f;
    UVW_system.W = 0.0f;
}

struct uz_dq_t dq_system = {0};
void setUp_dq(void)
{
    dq_system.d = 0.0f;
    dq_system.q = 0.0f;
    dq_system.zero = 0.0f;
}

struct uz_alphabeta_t alphabeta_system = {0};
void setUp_alphabeta(void)
{
    alphabeta_system.alpha = 0.0f;
    alphabeta_system.beta = 0.0f;
    alphabeta_system.gamma = 0.0f;
}

void test_uz_dq_Transformation_output_positive_theta(void){
    setUp_UVW();
    UVW_system.U = 1.0f;
    UVW_system.V = -(1.0f / 2.0f);
    UVW_system.W = -(1.0f / 2.0f);
    float theta_el_rad = M_PI / 2.0f;
    struct uz_dq_t output = uz_dq_transformation(UVW_system, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.0f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.zero);
}

void test_uz_dq_Transformation_output_negative_theta(void){
    setUp_UVW();
    UVW_system.U = 1.0f;
    UVW_system.V = -(1.0f / 2.0f);
    UVW_system.W = -(1.0f / 2.0f);
    float theta_el_rad = -1.0f * (M_PI / 2.0f);
    struct uz_dq_t output = uz_dq_transformation(UVW_system, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.0f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.zero);
}

void test_uz_inverse_dq_Transformation_output_positive_theta(void){
    setUp_dq();
    dq_system.d = 0.0f;
    dq_system.q = -1.0f;
    float theta_el_rad = M_PI / 2.0f;
    struct uz_UVW_t output = uz_dq_inverse_transformation(dq_system, theta_el_rad);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.U);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.V);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.W);
}

void test_uz_inverse_dq_Transformation_output_negative_theta(void){
    setUp_dq();
    dq_system.d = 0.0f;
    dq_system.q = -1.0f;
    float theta_el_rad = -1.0f * (M_PI / 2.0f);
    struct uz_UVW_t output = uz_dq_inverse_transformation(dq_system, theta_el_rad);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, output.U);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.V);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.W);
}

void test_uz_clarke_Transformation_output(void){
    setUp_UVW();
    UVW_system.U = 1.0f;
    UVW_system.V = -(1.0f / 2.0f);
    UVW_system.W = -(1.0f / 2.0f);
    struct uz_alphabeta_t output = uz_clarke_transformation(UVW_system);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.alpha);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.gamma);
    UVW_system.U = sqrtf(3.0f) / 2.0f;
    UVW_system.V = 0.0f;
    UVW_system.W = -1.0f * (sqrtf(3.0f) / 2.0f);
    output = uz_clarke_transformation(UVW_system);
    TEST_ASSERT_FLOAT_WITHIN(1e-07, 0.8660254, output.alpha);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.gamma);

}

void test_uz_inverse_clarke_Transformation_output(void){
    setUp_alphabeta();
    alphabeta_system.alpha = 1.0f;
    alphabeta_system.beta = 0.0f;
    struct uz_UVW_t output = uz_clarke_inverse_transformation(alphabeta_system);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.U);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.V);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.W);
    alphabeta_system.alpha = 0.8660254f;
    alphabeta_system.beta = 0.5f;
    output = uz_clarke_inverse_transformation(alphabeta_system);
    TEST_ASSERT_EQUAL_FLOAT(sqrtf(3.0f) / 2.0f, output.U);
    TEST_ASSERT_EQUAL_FLOAT(0.f, output.V);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f * (sqrtf(3.0f) / 2.0f), output.W);

}
#endif // TEST
