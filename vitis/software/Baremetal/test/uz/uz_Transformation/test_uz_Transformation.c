#ifdef TEST

#include "unity.h"

#include <math.h>
#include "uz_math_constants.h"
#include "uz_Transformation.h"

uz_UVW_t UVW_system = {0}; 
uz_dq_t dq_system = {0};
uz_alphabeta_t alphabeta_system = {0};

uz_abc_9ph_t ninephase_abc = {0};
uz_alphabeta_9ph_t ninephase_alphabeta = {0};
uz_alphabeta_t alphabeta_multiphase_test = {0};
uz_dq_t dq_multiphase_test = {0};

void setUp(void)
{
    UVW_system.U = 0.0f;
    UVW_system.V = 0.0f;
    UVW_system.W = 0.0f;
    dq_system.d = 0.0f;
    dq_system.q = 0.0f;
    dq_system.zero = 0.0f;
    alphabeta_system.alpha = 0.0f;
    alphabeta_system.beta = 0.0f;
    alphabeta_system.gamma = 0.0f;
}

// Testfunctions threephase
void test_uz_dq_Transformation_output_positive_theta(void){
    UVW_system.U = 1.0f;
    UVW_system.V = -(1.0f / 2.0f);
    UVW_system.W = -(1.0f / 2.0f);
    float theta_el_rad = UZ_PIf / 2.0f;
    uz_dq_t output = uz_dq_transformation(UVW_system, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.0f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.zero);
}

void test_uz_dq_Transformation_output_negative_theta(void){
    UVW_system.U = 1.0f;
    UVW_system.V = -(1.0f / 2.0f);
    UVW_system.W = -(1.0f / 2.0f);
    float theta_el_rad = -1.0f * (UZ_PIf / 2.0f);
    uz_dq_t output = uz_dq_transformation(UVW_system, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.0f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.zero);
}

void test_uz_inverse_dq_Transformation_output_positive_theta(void){
    dq_system.d = 0.0f;
    dq_system.q = -1.0f;
    float theta_el_rad = UZ_PIf / 2.0f;
    uz_UVW_t output = uz_dq_inverse_transformation(dq_system, theta_el_rad);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.U);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.V);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.W);
}

void test_uz_inverse_dq_Transformation_output_negative_theta(void){
    dq_system.d = 0.0f;
    dq_system.q = -1.0f;
    float theta_el_rad = -1.0f * (UZ_PIf / 2.0f);
    uz_UVW_t output = uz_dq_inverse_transformation(dq_system, theta_el_rad);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, output.U);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.V);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.W);
}

void test_uz_clarke_Transformation_output(void){
    UVW_system.U = 1.0f;
    UVW_system.V = -(1.0f / 2.0f);
    UVW_system.W = -(1.0f / 2.0f);
    uz_alphabeta_t output = uz_clarke_transformation(UVW_system);
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
    alphabeta_system.alpha = 1.0f;
    alphabeta_system.beta = 0.0f;
    uz_UVW_t output = uz_clarke_inverse_transformation(alphabeta_system);
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

// Testfunctions ninephase

// test vsd output
void test_uz_9ph_clarke_transformation_output(void){
    
    ninephase_abc.a1 = 1.0f;
    ninephase_abc.b1 = 2.0f;
    ninephase_abc.c1 = 3.0f;
    ninephase_abc.a2 = 4.0f;
    ninephase_abc.b2 = 5.0f;
    ninephase_abc.c2 = 6.0f;
    ninephase_abc.a3 = 7.0f;
    ninephase_abc.b3 = 8.0f;
    ninephase_abc.c3 = 9.0f;
    uz_alphabeta_9ph_t output = uz_9ph_clarke_transformation(ninephase_abc);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.7124f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.8490f, output.beta);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  0.3333f, output.o1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  7.5056f, output.o2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.0859f, output.x1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2361f, output.y1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2017f, output.x2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  0.0356f, output.y2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  5.0000f, output.zero);
}

// test inverse vsd output
void test_uz_9ph_clarke_inverse_transformation_output(void){
    ninephase_alphabeta.alpha = -1.0f;
    ninephase_alphabeta.beta = -2.0f;
    ninephase_alphabeta.o1 = -3.0f;
    ninephase_alphabeta.o2 = -4.0f;
    ninephase_alphabeta.x1 = -5.0f;
    ninephase_alphabeta.y1 = -6.0f;
    ninephase_alphabeta.x2 = -7.0f;
    ninephase_alphabeta.y2 = -8.0f;
    ninephase_alphabeta.zero = -9.0f;    
    uz_abc_9ph_t output = uz_9ph_clarke_inverse_transformation(ninephase_alphabeta);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -33.0718f, output.a1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -17.0359f, output.b1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -10.1077f, output.c1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,   5.6634f, output.a2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  18.0358f, output.b2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  12.6239f, output.c2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  -7.6740f, output.a3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -36.0619f, output.b3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -13.3717f, output.c3);
}

// test dq0 positive theta
void test_uz_ab_to_dq_transformation_output_positive_theta(void){
    alphabeta_multiphase_test.alpha = 2.0f;
    alphabeta_multiphase_test.beta  = 3.0f;
    alphabeta_multiphase_test.gamma = 4.0f;
    float theta_el_rad = UZ_PIf / 8.0f;
    uz_dq_t output = uz_ab_to_dq_transformation(alphabeta_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.995809f, output.d);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.006272f, output.q);
    TEST_ASSERT_EQUAL_FLOAT (-999999.0f, output.zero);
}

// test dq0 negative theta
void test_uz_ab_to_dq_transformation_output_negative_theta(void){
    alphabeta_multiphase_test.alpha = 2.0f;
    alphabeta_multiphase_test.beta  = 3.0f;
    alphabeta_multiphase_test.gamma = 4.0f;
    float theta_el_rad = -1 * UZ_PIf / 8.0f;
    uz_dq_t output = uz_ab_to_dq_transformation(alphabeta_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.699709f, output.d);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 3.537005f, output.q);
    TEST_ASSERT_EQUAL_FLOAT (-999999.0f, output.zero);
}

// test inverse dq0 positive theta
void test_uz_dq_to_ab_inverse_transformation_positive_theta(void){
    dq_multiphase_test.d = 5.0f;
    dq_multiphase_test.q  = 6.0f;
    dq_multiphase_test.zero = 4.0f;
    float theta_el_rad = UZ_PIf / 8.0f;
    uz_alphabeta_t output = uz_dq_to_ab_inverse_transformation(dq_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.323297f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 7.456694f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT (-999999.0f, output.gamma);
}

// test inverse dq0 negative theta
void test_uz_dq_to_ab_inverse_transformation_negative_theta(void){
    dq_multiphase_test.d = 5.0f;
    dq_multiphase_test.q  = 6.0f;
    dq_multiphase_test.zero = 4.0f;
    float theta_el_rad = -1* UZ_PIf / 8.0f;
    uz_alphabeta_t output = uz_dq_to_ab_inverse_transformation(dq_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-05, 6.915498f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN (1e-05, 3.62986f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT (-999999.0f, output.gamma);
}

#endif // TEST
