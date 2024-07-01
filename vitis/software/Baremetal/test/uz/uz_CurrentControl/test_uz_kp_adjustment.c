#ifdef TEST

#include "unity.h"
#include "uz_kp_adjustment.h"
#include "../uz_global_configuration.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "test_assert_with_exception.h"

uz_3ph_dq_t i_reference_Ampere = {0};
uz_3ph_dq_t i_actual_Ampere = {0};
uz_3ph_dq_t flux_reference = {0};
uz_3ph_dq_t flux_actual = {0};
float sample_time = 0.0f; 
float factor = 0.0f;
void setUp(void)
{
    sample_time = 0.00005f; //for Controller Frequency of 20kHz
    factor = 2.0f;
    flux_reference.d = 0.0f;
    flux_reference.q = 0.0f;
    flux_actual.d = 0.0f;
    flux_actual.q = 0.0f;
    i_actual_Ampere.d = 0.0f;
    i_actual_Ampere.q = 0.0f;
    i_reference_Ampere.d = 0.0f;
    i_reference_Ampere.q = 0.0f;
}

void test_uz_CurrentControl_Kp_d_adjustment_actual_ampere_zero(void){  
    //Values for comparision from simulation 
    flux_reference.d = 0.00045f;
    flux_actual.d = 0.00000f;
    i_reference_Ampere.d = 1.0f;
    i_actual_Ampere.d = 0.0f;
    uz_3ph_dq_t result = uz_CurrentControl_kp_adjustment(i_actual_Ampere, i_reference_Ampere, flux_actual, flux_reference, sample_time, factor);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,2.250f,result.d);
} 

void test_uz_CurrentControl_Kp_q_adjustment_actual_ampere_zero(void){
    //Values for comparision from simulation   
    flux_reference.q = 0.0f;
    flux_actual.q = 0.002f;
    i_reference_Ampere.q = 0.0f;
    i_actual_Ampere.q = 1.0f;
    uz_3ph_dq_t result = uz_CurrentControl_kp_adjustment(i_actual_Ampere, i_reference_Ampere, flux_actual, flux_reference, sample_time, factor);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,10.0f,result.q);
} 

void test_uz_CurrentControl_Kp_d_adjustment_actual_ampere_positive(void){  
    //Values for comparision from simulation 
    flux_reference.d = 0.00045f;
    flux_actual.d = 0.00025f;
    i_reference_Ampere.d = 1.0f;
    i_actual_Ampere.d = 0.5f;
    uz_3ph_dq_t result = uz_CurrentControl_kp_adjustment(i_actual_Ampere, i_reference_Ampere, flux_actual, flux_reference, sample_time, factor);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,2.0f,result.d);
} 

void test_uz_CurrentControl_Kp_q_adjustment_actual_ampere_positive(void){   
    //Values for comparision from simulation
    flux_reference.q = 0.002f;
    flux_actual.q = 0.0005f;
    i_reference_Ampere.q = 1.0f;
    i_actual_Ampere.q = 0.5f;
    uz_3ph_dq_t result = uz_CurrentControl_kp_adjustment(i_actual_Ampere, i_reference_Ampere, flux_actual, flux_reference, sample_time, factor);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,15.0f,result.q);
} 

#endif // TEST