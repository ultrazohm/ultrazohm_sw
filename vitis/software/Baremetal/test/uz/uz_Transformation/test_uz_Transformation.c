#ifdef TEST

#include "unity.h"

#include <math.h>
#include "uz_math_constants.h"
#include "uz_Transformation.h"

uz_3ph_abc_t UVW_system = {0}; 
uz_3ph_dq_t dq_system = {0};
uz_3ph_alphabeta_t alphabeta_system = {0};

uz_6ph_abc_t sixphase_abc = {0};
uz_6ph_alphabeta_t sixphase_alphabeta = {0};

uz_9ph_abc_t ninephase_abc = {0};
uz_9ph_alphabeta_t ninephase_alphabeta = {0};
uz_3ph_alphabeta_t alphabeta_multiphase_test = {0};
uz_3ph_dq_t dq_multiphase_test = {0};

void setUp(void)
{
    UVW_system.a = 0.0f;
    UVW_system.b = 0.0f;
    UVW_system.c = 0.0f;
    dq_system.d = 0.0f;
    dq_system.q = 0.0f;
    dq_system.zero = 0.0f;
    alphabeta_system.alpha = 0.0f;
    alphabeta_system.beta = 0.0f;
    alphabeta_system.gamma = 0.0f;
}

// Testfunctions threephase
void test_uz_dq_Transformation_output_positive_theta(void){
    UVW_system.a = 1.0f;
    UVW_system.b = -(1.0f / 2.0f);
    UVW_system.c = -(1.0f / 2.0f);
    float theta_el_rad = UZ_PIf / 2.0f;
    uz_3ph_dq_t output = uz_transformation_3ph_abc_to_dq(UVW_system, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.0f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.zero);
}

void test_uz_dq_Transformation_output_negative_theta(void){
    UVW_system.a = 1.0f;
    UVW_system.b = -(1.0f / 2.0f);
    UVW_system.c = -(1.0f / 2.0f);
    float theta_el_rad = -1.0f * (UZ_PIf / 2.0f);
    uz_3ph_dq_t output = uz_transformation_3ph_abc_to_dq(UVW_system, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.0f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.zero);
}

void test_uz_inverse_dq_Transformation_output_positive_theta(void){
    dq_system.d = 0.0f;
    dq_system.q = -1.0f;
    float theta_el_rad = UZ_PIf / 2.0f;
    uz_3ph_abc_t output = uz_transformation_3ph_dq_to_abc(dq_system, theta_el_rad);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.a);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.b);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.c);
}

void test_uz_inverse_dq_Transformation_output_negative_theta(void){
    dq_system.d = 0.0f;
    dq_system.q = -1.0f;
    float theta_el_rad = -1.0f * (UZ_PIf / 2.0f);
    uz_3ph_abc_t output = uz_transformation_3ph_dq_to_abc(dq_system, theta_el_rad);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f, output.a);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.b);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.c);
}

void test_uz_clarke_Transformation_output(void){
    UVW_system.a = 1.0f;
    UVW_system.b = -(1.0f / 2.0f);
    UVW_system.c = -(1.0f / 2.0f);
    uz_3ph_alphabeta_t output = uz_transformation_3ph_abc_to_alphabeta(UVW_system);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.alpha);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.gamma);
    UVW_system.a = sqrtf(3.0f) / 2.0f;
    UVW_system.b = 0.0f;
    UVW_system.c = -1.0f * (sqrtf(3.0f) / 2.0f);
    output = uz_transformation_3ph_abc_to_alphabeta(UVW_system);
    TEST_ASSERT_FLOAT_WITHIN(1e-07, 0.8660254, output.alpha);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.gamma);
}

void test_uz_inverse_clarke_Transformation_output(void){
    alphabeta_system.alpha = 1.0f;
    alphabeta_system.beta = 0.0f;
    uz_3ph_abc_t output = uz_transformation_3ph_alphabeta_to_abc(alphabeta_system);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.a);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.b);
    TEST_ASSERT_EQUAL_FLOAT(-0.5f, output.c);
    alphabeta_system.alpha = 0.8660254f;
    alphabeta_system.beta = 0.5f;
    output = uz_transformation_3ph_alphabeta_to_abc(alphabeta_system);
    TEST_ASSERT_EQUAL_FLOAT(sqrtf(3.0f) / 2.0f, output.a);
    TEST_ASSERT_EQUAL_FLOAT(0.f, output.b);
    TEST_ASSERT_EQUAL_FLOAT(-1.0f * (sqrtf(3.0f) / 2.0f), output.c);
}

// Testfunctions sixphase VSD:

// test vsd output
void test_uz_6ph_clarke_transformation_output(void){
    
    sixphase_abc.a1 = 1.0f;
    sixphase_abc.b1 = 2.0f;
    sixphase_abc.c1 = 3.0f;
    sixphase_abc.a2 = 4.0f;
    sixphase_abc.b2 = 5.0f;
    sixphase_abc.c2 = 6.0f;

    uz_6ph_alphabeta_t output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(sixphase_abc);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.7877f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.7887f, output.beta);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2113f, output.x);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2113f, output.y);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.0000f, output.z1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 5.0000f, output.z2);
}

// test inverse vsd output
void test_uz_6ph_clarke_inverse_transformation_output(void){
    sixphase_alphabeta.alpha = -1.0f;
    sixphase_alphabeta.beta = -2.0f;
    sixphase_alphabeta.x = -3.0f;
    sixphase_alphabeta.y = -4.0f;
    sixphase_alphabeta.z1 = -5.0f;
    sixphase_alphabeta.z2 = -6.0f;
  
    uz_6ph_abc_t output = uz_transformation_asym30deg_6ph_alphabeta_to_abc(sixphase_alphabeta);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -9.0000, output.a1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -1.2679f, output.b1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -4.7321f, output.c1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -7.2679f, output.a2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -10.7321f, output.b2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 0.0000f, output.c2);
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
    uz_9ph_alphabeta_t output = uz_transformation_9ph_abc_to_alphabeta(ninephase_abc);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.7124f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.8490f, output.beta);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  0.3333f, output.x1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  7.5056f, output.y1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.0859f, output.x2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2361f, output.y2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2017f, output.x3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  0.0356f, output.y3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  1.6667f, output.zero);
}

// test inverse vsd output
void test_uz_9ph_clarke_inverse_transformation_output(void){
    ninephase_alphabeta.alpha = 1.0f;
    ninephase_alphabeta.beta = 2.0f;
    ninephase_alphabeta.x1 = 3.0f;
    ninephase_alphabeta.y1 = 4.0f;
    ninephase_alphabeta.x2 = 5.0f;
    ninephase_alphabeta.y2 = 6.0f;
    ninephase_alphabeta.x3 = 7.0f;
    ninephase_alphabeta.y3 = 8.0f;
    ninephase_alphabeta.zero = 9.0f;    
    uz_9ph_abc_t output = uz_transformation_9ph_alphabeta_to_abc(ninephase_alphabeta);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 25.0000f, output.a1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  8.9641f, output.b1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  2.0359f, output.c1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  2.4084f, output.a2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -9.9640f, output.b2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -4.5521f, output.c2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.3978f, output.a3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 27.9901f, output.b3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  5.2999f, output.c3);
}

// test dq0 positive theta
void test_uz_ab_to_dq_transformation_output_positive_theta(void){
    alphabeta_multiphase_test.alpha = 2.0f;
    alphabeta_multiphase_test.beta  = 3.0f;
    alphabeta_multiphase_test.gamma = 4.0f;
    float theta_el_rad = UZ_PIf / 8.0f;
    uz_3ph_dq_t output = uz_transformation_3ph_alphabeta_to_dq(alphabeta_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.995809f, output.d);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.006272f, output.q);
    TEST_ASSERT_EQUAL_FLOAT (4.0f, output.zero);
}

// test dq0 negative theta
void test_uz_ab_to_dq_transformation_output_negative_theta(void){
    alphabeta_multiphase_test.alpha = 2.0f;
    alphabeta_multiphase_test.beta  = 3.0f;
    alphabeta_multiphase_test.gamma = 4.0f;
    float theta_el_rad = -1 * UZ_PIf / 8.0f;
    uz_3ph_dq_t output = uz_transformation_3ph_alphabeta_to_dq(alphabeta_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 0.699709f, output.d);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 3.537005f, output.q);
    TEST_ASSERT_EQUAL_FLOAT (4.0f, output.zero);
}

// test inverse dq0 positive theta
void test_uz_dq_to_ab_inverse_transformation_positive_theta(void){
    dq_multiphase_test.d = 5.0f;
    dq_multiphase_test.q  = 6.0f;
    dq_multiphase_test.zero = 4.0f;
    float theta_el_rad = UZ_PIf / 8.0f;
    uz_3ph_alphabeta_t output = uz_transformation_3ph_dq_to_alphabeta(dq_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.323297f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 7.456694f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT (4.0f, output.gamma);
}

// test inverse dq0 negative theta
void test_uz_dq_to_ab_inverse_transformation_negative_theta(void){
    dq_multiphase_test.d = 5.0f;
    dq_multiphase_test.q  = 6.0f;
    dq_multiphase_test.zero = 4.0f;
    float theta_el_rad = -1* UZ_PIf / 8.0f;
    uz_3ph_alphabeta_t output = uz_transformation_3ph_dq_to_alphabeta(dq_multiphase_test, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-05, 6.915498f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN (1e-05, 3.62986f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT (4.0f, output.gamma);
}

#endif // TEST
