#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_CurrentControl.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"
#include "uz_linear_decoupling.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include <math.h>

struct uz_CurrentControl_config config = {0};
uz_3ph_dq_t i_actual_Ampere = {0};
uz_3ph_dq_t i_reference_Ampere = {0};
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
    i_actual_Ampere.d = 0.0f;
    i_actual_Ampere.q = 0.0f;
    i_actual_Ampere.zero = 0.0f;
    omega_el_rad_per_sec = 0.0f;
    V_dc_volts = 24.0f;
    config.config_PMSM.Ld_Henry = 0.00027f;
    config.config_PMSM.Lq_Henry = 0.00027f;
    config.config_PMSM.Psi_PM_Vs = 0.0082f;
    i_reference_Ampere.d = 1.0f;
    i_reference_Ampere.q = 1.0f;
    i_reference_Ampere.zero = 0.0f;
    config.decoupling_select = linear_decoupling;
}

void test_uz_CurrentControl_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_reset(NULL));
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
    //Values for comparision from simulation
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
    //Values for comparision from simulation
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
    //Values for comparision from simulation
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
    //Values for comparision from simulation
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
    //Values for comparision from simulation
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
    //Values for comparision from simulation
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
    //Values for comparision from simulation
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

void test_uz_CurrentControl_generate_DutyCycles_output(void) {
    struct uz_3ph_abc_t UVW = {.a=10.0f, .b=0.0f, .c=-6.0f};
    struct uz_DutyCycle_t output = uz_CurrentControl_generate_DutyCycles(UVW, V_dc_volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f, 0.91667f, output.DutyCycle_U);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f, 0.5f, output.DutyCycle_V);
    TEST_ASSERT_FLOAT_WITHIN(1e-03f, 0.25f, output.DutyCycle_W);
}

void test_uz_CurrentControl_generate_DutyCycles_limit(void) {
    struct uz_3ph_abc_t UVW = {.a = 30.0f, .b = 35.32f, .c = -25.0f};
    struct uz_DutyCycle_t output = uz_CurrentControl_generate_DutyCycles(UVW, V_dc_volts);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.DutyCycle_U);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.DutyCycle_V);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.DutyCycle_W);
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
    //Values for comparision from simulation
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
#endif // TEST