#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_CurrentControl.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include "uz_linear_decoupling.h"
#include "uz_static_nonlinear_decoupling.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include <math.h>

struct uz_CurrentControl_config config = {0};
uz_3ph_dq_t i_actual_Ampere = {0};
uz_3ph_dq_t i_reference_Ampere = {0};
uz_3ph_dq_t flux_approx_real = {0};
uz_3ph_dq_t flux_approx_reference = {0};
float factor = 0.0f;    //factor for magnitude optimum
float omega_el_rad_per_sec = 0.0f;
float V_dc_volts = 0.0f;
void setUp(void)
{
    config.config_id.Kp = 6.75f;
    config.config_id.Ki = 2000.0f;
    config.config_id.samplingTime_sec = 0.00001f;
    config.config_id.upper_limit = 10.0f;
    config.config_id.lower_limit = -10.0f;
    config.config_iq.Kp = 6.75f;
    config.config_iq.Ki = 2000.0f;
    config.config_iq.samplingTime_sec = 0.00001f;
    config.config_iq.upper_limit = 10.0f;
    config.config_iq.lower_limit = -10.0f;
    config.Kp_adjustment_flag = false;
    i_actual_Ampere.d = 0.0f;
    i_actual_Ampere.q = 0.0f;
    i_actual_Ampere.zero = 0.0f;
    omega_el_rad_per_sec = 0.0f;
    V_dc_volts = 24.0f;
    config.config_PMSM.Ld_Henry = 0.00027f;
    config.config_PMSM.Lq_Henry = 0.00027f;
    config.config_PMSM.Psi_PM_Vs = 0.0082f;
    config.max_modulation_index = 1.0f / sqrtf(3.0f);
    i_reference_Ampere.d = 1.0f;
    i_reference_Ampere.q = 1.0f;
    i_reference_Ampere.zero = 0.0f;
    flux_approx_real.d = 0.0f;
    flux_approx_real.q = 0.0f;
    factor = 2.0f;    //
    flux_approx_reference.d = 0.0f;
    flux_approx_reference.q = 0.0f;
    config.decoupling_select = linear_decoupling;
}

void test_uz_CurrentControl_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_reset(NULL));
}

void test_uz_CurrentControl_set_flux_approx_NULL(void){
    flux_approx_real.d = 0.00045f;
    flux_approx_real.q = 0.002f;
    flux_approx_reference.d = 0.00045f;
    flux_approx_reference.q = 0.002f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_flux_approx(NULL, flux_approx_real, flux_approx_reference));
}

void test_uz_CurrentControl_set_Kp_id_NULL(void){
    float Kp_id = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_Kp_id(NULL, Kp_id));
}

void test_uz_CurrentControl_set_Kp_id_negative(void){
    float Kp_id = -10.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_Kp_id(instance, Kp_id));
}

void test_uz_CurrentControl_set_Ki_id_negative(void){
    float Ki_id = -10.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_Ki_id(instance, Ki_id));
}

void test_uz_CurrentControl_set_Kp_iq_NULL(void){
    float Kp_iq = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_Kp_iq(NULL, Kp_iq));
}

void test_uz_CurrentControl_set_Kp_iq_negative(void){
    float Kp_iq = -10.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_Kp_iq(instance, Kp_iq));
}

void test_uz_CurrentControl_set_Ki_iq_negative(void){
    float Ki_iq = -10.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_Ki_iq(instance, Ki_iq));
}

void test_uz_CurrentControl_sample_output(void){
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
    float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
	float values_omega[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.756f, 0.588f, 0.461f};
    float uq_out[11]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f, 1.68f, 1.3f, 1.01f, 0.811f, 0.671f, 0.581f}; 
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
}

void test_uz_CurrentControl_sample_abc_output(void) {
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float theta_el_rad = (float)M_PI;
    uz_3ph_abc_t output = uz_CurrentControl_sample_abc(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,-6.75f,output.a);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,-2.4707f,output.b);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,9.2207f,output.c);
    theta_el_rad = (float)M_PI * 1.5f;
    uz_CurrentControl_reset(instance);
    output = uz_CurrentControl_sample_abc(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec, theta_el_rad);
    TEST_ASSERT_FLOAT_WITHIN(1e-02,6.75f,output.a);
    TEST_ASSERT_FLOAT_WITHIN(1e-02,-9.2207f,output.b);
    TEST_ASSERT_FLOAT_WITHIN(1e-02,2.4707f,output.c);
}

void test_uz_CurrentControl_sample_output_SVLimitation_active(void){
    V_dc_volts = 10.0f;
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float values_iq[11]={0.874f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f};
    float values_id[11]={1.0f, 0.998f, 0.997f, 0.996f, 0.995f, 0.995f, 0.994f, 0.994f, 0.994f, 0.994f, 0.993f};
	float values_omega[11]={673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f};
    float ud_out[11]={-0.159f, -0.146f, -0.138f, -0.131f, -0.126f, -0.123f, -0.12f, -0.118f, -0.116f, -0.115f, -0.114f};
    float uq_out[11]={5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f}; 
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
}

void test_uz_CurrentControl_reset(void){
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f};
    float uq_out[5]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f}; 
    for(int i=0;i<5;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
    uz_CurrentControl_reset(instance);
    for(int i=0;i<5;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
}

void test_uz_CurrentControl_set_Kp_and_Ki_id(void){
    //Tests, if the new values are properly written into the CurrentControl instance
    uz_3ph_dq_t output = {0};
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    for(int i=0;i<11;i++){
        output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    }    
    TEST_ASSERT_FLOAT_WITHIN(1e-02f, 6.95f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02f, 6.95f, output.q);
    uz_CurrentControl_set_Kp_id(instance, 0.0f);
    uz_CurrentControl_set_Ki_id(instance, 0.0f);
    uz_CurrentControl_reset(instance);
    for(int i=0;i<5;i++){
        output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02f, 0.0f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02f, 6.83f, output.q);
}

void test_uz_CurrentControl_set_Kp_and_Ki_iq(void){
    //Tests, if the new values are properly written into the CurrentControl instance
    uz_3ph_dq_t output = {0};
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    for(int i=0;i<11;i++){
        output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    }    
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.q);
    uz_CurrentControl_set_Kp_iq(instance, 0.0f);
    uz_CurrentControl_set_Ki_iq(instance, 0.0f);
    uz_CurrentControl_reset(instance);
    for(int i=0;i<5;i++){
        output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.83f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.q);
}

void test_uz_CurrentControl_adjust_Kp_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_adjust_Kp(NULL,i_reference_Ampere,i_actual_Ampere,factor));
}
void test_uz_CurrentControl_adjust_Kp(void){
    //test if the kp adjustment is written properly 
    config.Kp_adjustment_flag = true;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    uz_3ph_dq_t output = {0};
    //Values for comparision from simulation
    flux_approx_real.d = 0.00040f;
    flux_approx_real.q = 0.0019f;
    flux_approx_reference.d = 0.00045f;
    flux_approx_reference.q = 0.002f;
    i_actual_Ampere.d = 0.8f;
    i_actual_Ampere.q = 0.8f; 
    omega_el_rad_per_sec = 500.0f;
    uz_CurrentControl_set_flux_approx(instance,flux_approx_real,flux_approx_reference);
    uz_CurrentControl_adjust_Kp(instance, i_reference_Ampere, i_actual_Ampere, factor);
    output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    TEST_ASSERT_FLOAT_WITHIN(1e-02f, 1.14f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02f, 6.71f, output.q);
    for(int i=0;i<15;i++){
        output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    }  
    TEST_ASSERT_FLOAT_WITHIN(1e-02f, 1.20f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02f, 6.77f, output.q);
}

void test_uz_CurrentControl_set_PMSM_parameters(void) {
    uz_3ph_dq_t output = { 0 };
    //sets the output of the Pi-Controllers 0
    config.config_id.Ki = 0.0f;
    config.config_id.Kp = 0.0f;
    config.config_iq.Ki = 0.0f;
    config.config_iq.Kp = 0.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);

    //Check outputs from the linear decoupling
    i_actual_Ampere.q = 4.0f;
    i_actual_Ampere.d = 4.0f;
    omega_el_rad_per_sec = 500.0f;
    output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_FLOAT(-0.54f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(4.64f, output.q);
    //Set params of linear decoupling to 0
    config.config_PMSM.Ld_Henry = 0.0001f;
    config.config_PMSM.Lq_Henry = 0.0001f;
    config.config_PMSM.Psi_PM_Vs = 0.0f;
    uz_CurrentControl_set_PMSM_parameters(instance, config.config_PMSM);
    output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    //Check, if the output is changed
    TEST_ASSERT_EQUAL_FLOAT(-0.2f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(0.2f, output.q);
}

void test_uz_CurrentControl_get_ext_clamping_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_get_ext_clamping(NULL));
}

void test_uz_CurrentControl_get_ext_clamping_output(void){
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    i_actual_Ampere.q = 0.0f;
    i_actual_Ampere.d = 0.0f;
    omega_el_rad_per_sec =  0.0f; 
    uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_INT(0,uz_CurrentControl_get_ext_clamping(instance));
    V_dc_volts = 10.0f;
    i_actual_Ampere.q = 0.874f;
    i_actual_Ampere.d = 1.0f;
    omega_el_rad_per_sec =  673.0f; 
    uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_INT(1,uz_CurrentControl_get_ext_clamping(instance));
}

void test_uz_CurrentControl_sample_no_decoupling(void) {
    config.decoupling_select = no_decoupling;
    config.config_PMSM.Ld_Henry = 0.0f;
    config.config_PMSM.Lq_Henry = 0.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
}

void test_uz_CurrentControl_set_decoupling_method(void) {
    config.decoupling_select = no_decoupling;
    config.config_PMSM.Ld_Henry = 0.0f;
    config.config_PMSM.Lq_Henry = 0.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    TEST_ASSERT_PASS_ASSERT(uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec));
    uz_CurrentControl_set_decoupling_method(instance, linear_decoupling);
    //Assertion should trigger now, since for the linear_decoupling Ld/Lq must be greater than 0.0f
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec));
}

void test_uz_CurrentControl_sample_output_PI_Controller_limit_deactivated(void){
    //Values for comparison from simulation
    //Limit of the PI-Controllers are "deactivated" and should not limit the signal
    config.config_id.lower_limit = 0.0f;
    config.config_id.upper_limit = 0.0f;
    config.config_iq.lower_limit = 0.0f;
    config.config_iq.upper_limit = 0.0f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
    float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
	float values_omega[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.756f, 0.588f, 0.461f};
    float uq_out[11]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f, 1.68f, 1.3f, 1.01f, 0.811f, 0.671f, 0.581f}; 
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
}

void test_uz_CurrentControl_max_modulation_index_negative_assert(void){
    config.max_modulation_index = -5.2f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_init(config));
}

void test_uz_CurrentControl_max_modulation_index_zero_assert(void){
    config.max_modulation_index = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_init(config));
}

void test_uz_CurrentControl_set_max_modulation_index_zero_assert(void){
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_max_modulation_index(instance, 0.0f));
}

void test_uz_CurrentControl_set_max_modulation_index_negative_assert(void){
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_max_modulation_index(instance, -10.0f));
}

void test_uz_CurrentControl_set_max_modulation_index_check(void){
    //Values for comparison from simulation
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    i_actual_Ampere.q = 0.0f;
    i_actual_Ampere.d = 0.0f;
    omega_el_rad_per_sec =  0.0f; 
    uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_INT(0,uz_CurrentControl_get_ext_clamping(instance));
    V_dc_volts = 10.0f;
    i_actual_Ampere.q = 0.874f;
    i_actual_Ampere.d = 1.0f;
    omega_el_rad_per_sec =  673.0f; 
    uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_INT(1,uz_CurrentControl_get_ext_clamping(instance));
    //Increase max_modulation_index to arbitrary high value. Therefore the limitation should not be active anymore
    uz_CurrentControl_set_max_modulation_index(instance, 10.0f);
    uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
    TEST_ASSERT_EQUAL_INT(0,uz_CurrentControl_get_ext_clamping(instance));
}

void test_uz_CurrentControl_Kp_d_adjustment_actual_ampere_zero(void){  
    //Values for comparision from simulation 
    config.Kp_adjustment_flag = true;
    config.config_id.samplingTime_sec = 0.0001f;
    config.config_iq.samplingTime_sec = 0.0001f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    flux_approx_reference.d = 0.00045f;
    flux_approx_real.d = 0.00000f;
    i_reference_Ampere.d = 1.0f;
    i_actual_Ampere.d = 0.0f;
    uz_CurrentControl_set_flux_approx(instance,flux_approx_real, flux_approx_reference);
    uz_CurrentControl_adjust_Kp(instance,i_reference_Ampere,i_actual_Ampere,factor);
    float result = uz_CurrentControl_get_Kp_id(instance);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,1.125f,result);
} 

void test_uz_CurrentControl_Kp_q_adjustment_actual_ampere_zero(void){
    //Values for comparision from simulation 
    config.Kp_adjustment_flag = true;
    config.config_iq.samplingTime_sec = 0.0001f;
    config.config_id.samplingTime_sec = 0.0001f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    flux_approx_reference.q = 0.002f;
    flux_approx_real.q = 0.00000f;
    i_reference_Ampere.q = 1.0f;
    i_actual_Ampere.q = 0.0f;
    uz_CurrentControl_set_flux_approx(instance,flux_approx_real, flux_approx_reference);
    uz_CurrentControl_adjust_Kp(instance,i_reference_Ampere,i_actual_Ampere,factor);
    float result = uz_CurrentControl_get_Kp_iq(instance);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,5.0f,result);
} 

void test_uz_CurrentControl_Kp_d_adjustment_actual_ampere_positive(void){  
    //Values for comparision from simulation
    config.Kp_adjustment_flag = true;
    config.config_id.samplingTime_sec = 0.0001f;
    config.config_iq.samplingTime_sec = 0.0001f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    flux_approx_reference.d = 0.00045f;
    flux_approx_real.d = 0.00025f;
    i_reference_Ampere.d = 1.0f;
    i_actual_Ampere.d = 0.5f;
    uz_CurrentControl_set_flux_approx(instance,flux_approx_real, flux_approx_reference);
    uz_CurrentControl_adjust_Kp(instance,i_reference_Ampere,i_actual_Ampere,factor);
    float result = uz_CurrentControl_get_Kp_id(instance);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,1.0f,result);
} 

void test_uz_CurrentControl_Kp_q_adjustment_actual_ampere_positive(void){   
    //Values for comparision from simulation 
    config.Kp_adjustment_flag = true;
    config.config_iq.samplingTime_sec = 0.0001f;
    config.config_id.samplingTime_sec = 0.0001f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    flux_approx_reference.q = 0.002f;
    flux_approx_real.q = 0.0005f;
    i_reference_Ampere.q = 1.0f;
    i_actual_Ampere.q = 0.5f;
    uz_CurrentControl_set_flux_approx(instance,flux_approx_real, flux_approx_reference);
    uz_CurrentControl_adjust_Kp(instance,i_reference_Ampere,i_actual_Ampere,factor);
    float result = uz_CurrentControl_get_Kp_iq(instance);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,7.5f,result);
} 

void test_uz_CurrentControl_get_Kp_id_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_get_Kp_id(NULL));
}

void test_uz_CurrentControl_get_Kp_iq_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_get_Kp_iq(NULL));
}

void test_uz_CurrentControl_get_Kp_id(void) {
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    uz_CurrentControl_set_Kp_id(instance,2.0f);
    float result = uz_CurrentControl_get_Kp_id(instance);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,2.0f,result);
}

void test_uz_CurrentControl_get_Kp_iq(void) {
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    uz_CurrentControl_set_Kp_iq(instance,3.0f);
    float result = uz_CurrentControl_get_Kp_iq(instance);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,3.0f,result);
}

void test_uz_CurrentControl_set_Kp_adjustment_flag_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_set_Kp_adjustment_flag(NULL, 2.0f));
}

void test_uz_CurrentControl_set_Kp_adjustment_flag(void) {
    //Values for comparision from simulation 
    config.Kp_adjustment_flag = false;
    config.config_iq.samplingTime_sec = 0.0001f;
    config.config_id.samplingTime_sec = 0.0001f;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    flux_approx_reference.q = 0.002f;
    flux_approx_real.q = 0.0005f;
    i_reference_Ampere.q = 1.0f;
    i_actual_Ampere.q = 0.5f;
    //Enable it after init to test if the enabling worked
    uz_CurrentControl_set_Kp_adjustment_flag(instance,true);
    uz_CurrentControl_set_flux_approx(instance,flux_approx_real, flux_approx_reference);
    uz_CurrentControl_adjust_Kp(instance,i_reference_Ampere,i_actual_Ampere,factor);
    float result = uz_CurrentControl_get_Kp_iq(instance);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f,7.5f,result);
}

void test_uz_CurrentControl_tune_magnitude_optimum(void){
    //Values for comparison from simulation
    config.config_PMSM.Ld_Henry = 0.0001f;
    config.config_PMSM.Lq_Henry = 0.0002f;
    config.config_PMSM.R_ph_Ohm = 0.008f;
    config.decoupling_select = no_decoupling;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={0.5f, 0.376f,	0.283f,	0.212f,	0.16f};
    float uq_out[5]={1.0f, 0.751f,	0.565f,	0.424f,	0.319f}; 
    float tau_sigma_sec = 0.0001f;
    uz_CurrentControl_tune_magnitude_optimum(instance, tau_sigma_sec); 
    for(int i=0;i<5;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
}

void test_uz_CurrentControl_tune_symmetric_optimum(void){
    config.config_PMSM.Ld_Henry = 0.0001f;
    config.config_PMSM.Lq_Henry = 0.0002f;
    config.config_PMSM.R_ph_Ohm = 0.008f;
    config.decoupling_select = no_decoupling;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={0.5f,	0.388f,	0.304f, 0.24f, 0.193f};
    float uq_out[5]={1.0f,	0.776f,	0.608f,	0.481f,	0.386f}; 
    float tau_sigma_sec = 0.0001f;
    uz_CurrentControl_tune_symmetric_optimum(instance, tau_sigma_sec);
    uz_CurrentControl_reset(instance);
    for(int i=0;i<5;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
}

void test_uz_CurrentControl_tune_bandwidth(void){
    config.config_PMSM.Ld_Henry = 0.0001f;
    config.config_PMSM.Lq_Henry = 0.0002f;
    config.config_PMSM.R_ph_Ohm = 0.008f;
    config.decoupling_select = no_decoupling;
    uz_CurrentControl_t* instance = uz_CurrentControl_init(config);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={0.25f,	0.188f,	0.141f, 0.106f, 0.08f};
    float uq_out[5]={0.5f, 0.376f, 0.282f, 0.212f, 0.16f}; 
    float bandwidth_rad_per_sec = 2500;
    uz_CurrentControl_tune_bandwidth(instance, bandwidth_rad_per_sec); 
    for(int i=0;i<5;i++){
        i_actual_Ampere.q = values_iq[i];
        i_actual_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        uz_3ph_dq_t output = uz_CurrentControl_sample(instance, i_reference_Ampere, i_actual_Ampere, V_dc_volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02f, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02f, uq_out[i], output.q);
    }
}

#endif // TEST