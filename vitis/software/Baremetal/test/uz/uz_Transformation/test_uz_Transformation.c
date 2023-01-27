#ifdef TEST

#include "unity.h"

#include <math.h>
#include "uz_math_constants.h"
#include "uz_Transformation.h"
#include "uz_Transformation.c"

uz_3ph_abc_t UVW_system = {0}; 
uz_3ph_dq_t dq_system = {0};
uz_3ph_alphabeta_t alphabeta_system = {0};

uz_6ph_abc_t sixphase_abc = {0};
uz_6ph_alphabeta_t sixphase_alphabeta = {0};
uz_6ph_dq_t sixphase_dq = {0};

uz_9ph_abc_t ninephase_abc = {0};
uz_9ph_alphabeta_t ninephase_alphabeta = {0};
uz_9ph_dq_t ninephase_dq = {0};

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

// Test helpfunction
void test_uz_complex_rotation(void){
    uz_3ph_alphabeta_t startvalue = {
        .alpha = 111.9f,
        .beta = 31.55f,
        .gamma = -102.0f};
    uz_3ph_alphabeta_t result = {
        .alpha = 71.3f,
        .beta = 10.24f,
        .gamma = -102.0f};
    uz_3ph_alphabeta_t rotated = uz_complex_rotation(startvalue);
    TEST_ASSERT_FLOAT_WITHIN (1e-03,rotated.alpha, result.alpha);
    TEST_ASSERT_FLOAT_WITHIN (1e-03,rotated.beta, result.beta);
    TEST_ASSERT_FLOAT_WITHIN (1e-03,rotated.gamma, result.gamma);
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

void test_uz_6ph_abc_to_dq_transformation_output(void){
    
    sixphase_abc.a1 = 1.0f;
    sixphase_abc.b1 = 2.0f;
    sixphase_abc.c1 = 3.0f;
    sixphase_abc.a2 = 4.0f;
    sixphase_abc.b2 = 5.0f;
    sixphase_abc.c2 = 6.0f;
    float theta_el = 1/8.0f;

    uz_6ph_alphabeta_t alphabeta = uz_transformation_asym30deg_6ph_abc_to_alphabeta(sixphase_abc);
    alphabeta_multiphase_test.alpha = alphabeta.alpha;
    alphabeta_multiphase_test.beta  = alphabeta.beta;
    alphabeta_multiphase_test.gamma = 0.0f;
    uz_3ph_dq_t dq_calc = uz_transformation_3ph_alphabeta_to_dq(alphabeta_multiphase_test, theta_el);

    uz_6ph_dq_t output = uz_transformation_asym30deg_6ph_abc_to_dq(sixphase_abc, theta_el);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, dq_calc.d, output.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, dq_calc.q, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2113f, output.x);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2113f, output.y);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.0000f, output.z1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 5.0000f, output.z2);
}


void test_uz_6ph_dq_to_abc_transformation_output(void){
    sixphase_dq.d = -1.0f;
    sixphase_dq.q = -2.0f;
    sixphase_dq.x = -3.0f;
    sixphase_dq.y = -4.0f;
    sixphase_dq.z1 = -5.0f;
    sixphase_dq.z2 = -6.0f;
    float theta_el = 1/8.0f;

    dq_multiphase_test.d = sixphase_dq.d;
    dq_multiphase_test.q  = sixphase_dq.q;
    dq_multiphase_test.zero = 0.0f;
    uz_3ph_alphabeta_t alphabeta_calc = uz_transformation_3ph_dq_to_alphabeta(dq_multiphase_test, theta_el);

    sixphase_alphabeta.alpha = alphabeta_calc.alpha;
    sixphase_alphabeta.beta = alphabeta_calc.beta;
    sixphase_alphabeta.x = sixphase_dq.x;
    sixphase_alphabeta.y = sixphase_dq.y;
    sixphase_alphabeta.z1 = sixphase_dq.z1;
    sixphase_alphabeta.z2 = sixphase_dq.z2;

    uz_6ph_abc_t abc_vgl = uz_transformation_asym30deg_6ph_alphabeta_to_abc(sixphase_alphabeta);

    uz_6ph_abc_t output = uz_transformation_asym30deg_6ph_dq_to_abc(sixphase_dq, theta_el);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, abc_vgl.a1, output.a1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, abc_vgl.b1, output.b1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, abc_vgl.c1, output.c1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, abc_vgl.a2, output.a2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, abc_vgl.b2, output.b2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, abc_vgl.c2, output.c2);
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

void test_uz_transformation_9ph_alphabeta_to_dq(void){
    ninephase_alphabeta.alpha = 2.0f;
    ninephase_alphabeta.beta = 3.0f;
    ninephase_alphabeta.x1 = 4.3f;
    ninephase_alphabeta.y1 = 4.4f;
    ninephase_alphabeta.x2 = 4.5f;
    ninephase_alphabeta.y2 = 4.6f;
    ninephase_alphabeta.x3 = 4.7f;
    ninephase_alphabeta.y3 = 4.8f;
    ninephase_alphabeta.zero = 4.9f;
    float theta_el_rad = UZ_PIf / 8.0f;
    uz_9ph_dq_t output = uz_transformation_9ph_alphabeta_to_dq(ninephase_alphabeta, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.995809f, output.d);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.006272f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_alphabeta.x1,output.x1);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_alphabeta.y1,output.y1);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_alphabeta.x2,output.x2);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_alphabeta.y2,output.y2);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_alphabeta.x3,output.x3);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_alphabeta.y3,output.y3);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_alphabeta.zero,output.zero);
}

void test_uz_transformation_9ph_dq_to_alphabeta(void){
    ninephase_dq.d = 5.0f;
    ninephase_dq.q = 6.0f;
    ninephase_dq.x1 = 1.1f;
    ninephase_dq.y1 = 1.2f;
    ninephase_dq.x2 = 1.3f;
    ninephase_dq.y2 = 1.4f;
    ninephase_dq.x3 = 1.5f;
    ninephase_dq.y3 = 1.6f;
    ninephase_dq.zero = 1.7f;
    float theta_el_rad = UZ_PIf / 8.0f;
    uz_9ph_alphabeta_t output = uz_transformation_9ph_dq_to_alphabeta(ninephase_dq, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 2.323297f, output.alpha);
    TEST_ASSERT_FLOAT_WITHIN (1e-06, 7.456694f, output.beta);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_dq.x1,output.x1);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_dq.y1,output.y1);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_dq.x2,output.x2);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_dq.y2,output.y2);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_dq.x3,output.x3);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_dq.y3,output.y3);
    TEST_ASSERT_EQUAL_FLOAT(ninephase_dq.zero,output.zero);
}

void test_uz_transformation_9ph_abc_to_dq(void){
    ninephase_abc.a1 = 1.0f;
    ninephase_abc.b1 = 2.0f;
    ninephase_abc.c1 = 3.0f;
    ninephase_abc.a2 = 4.0f;
    ninephase_abc.b2 = 5.0f;
    ninephase_abc.c2 = 6.0f;
    ninephase_abc.a3 = 7.0f;
    ninephase_abc.b3 = 8.0f;
    ninephase_abc.c3 = 9.0f;
    float theta_el_rad = UZ_PIf / 8.0f;
    uz_9ph_dq_t output = uz_transformation_9ph_abc_to_dq(ninephase_abc, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.9831f, output.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.5118f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  0.3333f, output.x1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  7.5056f, output.y1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.0859f, output.x2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2361f, output.y2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -0.2017f, output.x3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  0.0356f, output.y3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  1.6667f, output.zero);
}

void test_uz_transformation_9ph_dq_to_abc(void){
    ninephase_dq.d = 5.0f;
    ninephase_dq.q = 6.0f;
    ninephase_dq.x1 = 1.1f;
    ninephase_dq.y1 = 1.2f;
    ninephase_dq.x2 = 1.3f;
    ninephase_dq.y2 = 1.4f;
    ninephase_dq.x3 = 1.5f;
    ninephase_dq.y3 = 1.6f;
    ninephase_dq.zero = 1.7f;  
    float theta_el_rad = UZ_PIf / 8.0f;  
    uz_9ph_abc_t output = uz_transformation_9ph_dq_to_abc(ninephase_dq, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  7.9233f, output.a1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  6.8692f, output.b1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.3925f, output.c1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  5.6551f, output.a2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  1.8092f, output.b2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -7.7966f, output.c2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  5.7464f, output.a3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,  6.3384f, output.b3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -5.5171f, output.c3);
}

void test_vsd_transformation_and_inverse(void){
    ninephase_abc.a1 = 1.0f;
    ninephase_abc.b1 = 2.0f;
    ninephase_abc.c1 = 3.0f;
    ninephase_abc.a2 = 4.0f;
    ninephase_abc.b2 = 5.0f;
    ninephase_abc.c2 = 6.0f;
    ninephase_abc.a3 = 7.0f;
    ninephase_abc.b3 = 8.0f;
    ninephase_abc.c3 = 9.0f;
    uz_9ph_alphabeta_t output_alphabeta = uz_transformation_9ph_abc_to_alphabeta(ninephase_abc);
    uz_9ph_abc_t output = uz_transformation_9ph_alphabeta_to_abc(output_alphabeta);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.a1, output.a1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.b1, output.b1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.c1, output.c1);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.a2, output.a2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.b2, output.b2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.c2, output.c2);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.a3, output.a3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.b3, output.b3);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, ninephase_abc.c3, output.c3);
}

void test_9ph_vsd_circular_example(void)
{

    // x=0:0.1:6*pi;
    float theta[189] = {0.0f, 0.100000000000000f, 0.200000000000000f, 0.300000000000000f, 0.400000000000000f, 0.500000000000000f, 0.600000000000000f, 0.700000000000000f, 0.800000000000000f, 0.900000000000000f, 1.0f, 1.10000000000000f, 1.20000000000000f, 1.30000000000000f, 1.40000000000000f, 1.50000000000000f, 1.60000000000000f, 1.70000000000000f, 1.80000000000000f, 1.90000000000000f, 2.0f, 2.10000000000000f, 2.20000000000000f, 2.30000000000000f, 2.40000000000000f, 2.50000000000000f, 2.60000000000000f, 2.70000000000000f, 2.80000000000000f, 2.90000000000000f, 3.0f, 3.10000000000000f, 3.20000000000000f, 3.30000000000000f, 3.40000000000000f, 3.50000000000000f, 3.60000000000000f, 3.70000000000000f, 3.80000000000000f, 3.90000000000000f, 4.0f, 4.10000000000000f, 4.20000000000000f, 4.30000000000000f, 4.40000000000000f, 4.50000000000000f, 4.60000000000000f, 4.70000000000000f, 4.80000000000000f, 4.90000000000000f, 5.0f, 5.10000000000000f, 5.20000000000000f, 5.30000000000000f, 5.40000000000000f, 5.50000000000000f, 5.60000000000000f, 5.70000000000000f, 5.80000000000000f, 5.90000000000000f, 6.0f, 6.10000000000000f, 6.20000000000000f, 6.30000000000000f, 6.40000000000000f, 6.50000000000000f, 6.60000000000000f, 6.70000000000000f, 6.80000000000000f, 6.90000000000000f, 7.0f, 7.10000000000000f, 7.20000000000000f, 7.30000000000000f, 7.40000000000000f, 7.50000000000000f, 7.60000000000000f, 7.70000000000000f, 7.80000000000000f, 7.90000000000000f, 8.0f, 8.10000000000000f, 8.20000000000000f, 8.30000000000000f, 8.40000000000000f, 8.50000000000000f, 8.60000000000000f, 8.70000000000000f, 8.80000000000000f, 8.90000000000000f, 9.0f, 9.10000000000000f, 9.20000000000000f, 9.30000000000000f, 9.40000000000000f, 9.50000000000000f, 9.60000000000000f, 9.70000000000000f, 9.80000000000000f, 9.90000000000000f, 10.0f, 10.1000000000000f, 10.2000000000000f, 10.3000000000000f, 10.4000000000000f, 10.5000000000000f, 10.6000000000000f, 10.7000000000000f, 10.8000000000000f, 10.9000000000000f, 11.0f, 11.1000000000000f, 11.2000000000000f, 11.3000000000000f, 11.4000000000000f, 11.5000000000000f, 11.6000000000000f, 11.7000000000000f, 11.8000000000000f, 11.9000000000000f, 12.0f, 12.1000000000000f, 12.2000000000000f, 12.3000000000000f, 12.4000000000000f, 12.5000000000000f, 12.6000000000000f, 12.7000000000000f, 12.8000000000000f, 12.9000000000000f, 13.0f, 13.1000000000000f, 13.2000000000000f, 13.3000000000000f, 13.4000000000000f, 13.5000000000000f, 13.6000000000000f, 13.7000000000000f, 13.8000000000000f, 13.9000000000000f, 14.0f, 14.1000000000000f, 14.2000000000000f, 14.3000000000000f, 14.4000000000000f, 14.5000000000000f, 14.6000000000000f, 14.7000000000000f, 14.8000000000000f, 14.9000000000000f, 15.0f, 15.1000000000000f, 15.2000000000000f, 15.3000000000000f, 15.4000000000000f, 15.5000000000000f, 15.6000000000000f, 15.7000000000000f, 15.8000000000000f, 15.9000000000000f, 16.0f, 16.1000000000000f, 16.2000000000000f, 16.3000000000000f, 16.4000000000000f, 16.5000000000000f, 16.6000000000000f, 16.7000000000000f, 16.8000000000000f, 16.9000000000000f, 17.0f, 17.1000000000000f, 17.2000000000000f, 17.3000000000000f, 17.4000000000000f, 17.5000000000000f, 17.6000000000000f, 17.7000000000000f, 17.8000000000000f, 17.9000000000000f, 18.0f, 18.1000000000000f, 18.2000000000000f, 18.3000000000000f, 18.4000000000000f, 18.5000000000000f, 18.6000000000000f, 18.7000000000000f, 18.8000000000000f};
    uz_9ph_dq_t dq_value={
        .q=1.0f
    };

    for (size_t i = 0; i < 189; i++)
    {
         uz_9ph_abc_t abc_value = uz_transformation_9ph_dq_to_abc(dq_value, theta[i]);
         uz_9ph_dq_t dq_reverse = uz_transformation_9ph_abc_to_dq(abc_value,theta[i]);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.d,dq_reverse.d);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.q,dq_reverse.q);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.x1,dq_reverse.x1);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.x2,dq_reverse.x2);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.x3,dq_reverse.x3);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.y1,dq_reverse.y1);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.y2,dq_reverse.y2);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.y3,dq_reverse.y3);
         TEST_ASSERT_FLOAT_WITHIN(1e-05, dq_value.zero,dq_reverse.zero);
    }
}
#endif // TEST
