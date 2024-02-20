#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include "../uz_global_configuration.h"
#include "../uz_parameterid_rc/uz_parameterid_rc.h"
#include "../uz_pmsm_linear/uz_pmsm_linear.h"
#include "../uz_pmsm_linear_rfe/uz_pmsm_linear_rfe.h"
#include "../uz_integrator/uz_integrator.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_CurrentControl/uz_CurrentControl.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_CurrentControl/uz_linear_decoupling.h"
#include "../uz_CurrentControl/uz_space_vector_limitation.h"
#include "../uz_signals/uz_signals.h"

struct uz_parameterid_rc_config_t test_config = {0};
struct uz_CurrentControl_config CC_config = {0};
float R = 0.0307880994f;
float L_d = 30.0e-6f;
float L_q = 50.0e-6f;
float rfe_d= 0.7f;
float rfe_q= 0.7f;
float psi_pm = 7.0e-3f;
float ts = 1.0f / 10000.0f;
float omega_el = 523.598775598299f;


void setUp(void)
{
    test_config.id_ref = 1.0f;
    test_config.iq_ref = 1.0f;
    test_config.n_ref = 1000.0f;
    test_config.wait_time = 0.5f;
    test_config.isr_steptime = (1.0f / 10.0e3f) * 1.0f;
    test_config.sample_time = 0.5f;


     // Configuration of Current Control
    CC_config.config_id.Kp = 0.1f; // nach BO, 0.3 nach Nina, 1.51f nach Bandbreite
    CC_config.config_id.Ki = 55.5f; //nach BO, 230.0f nach Nina , 836.4f nach Bandbreite
    CC_config.config_id.samplingTime_sec = 0.0001f;
    CC_config.config_id.upper_limit = 20.0f;
    CC_config.config_id.lower_limit = -20.0f;
    CC_config.config_iq.Kp = 0.17f; // nach BO, 0.5f nach Nina
    CC_config.config_iq.Ki = 55.5f; // nach BO, 230.0f nach Nina
    CC_config.config_iq.samplingTime_sec = 0.0001f;
    CC_config.config_iq.upper_limit = 20.0f;
    CC_config.config_iq.lower_limit = -20.0f;
    CC_config.config_PMSM.R_ph_Ohm = 0.0307880994f;
    CC_config.config_PMSM.Ld_Henry = 0.00003f;
    CC_config.config_PMSM.Lq_Henry = 0.00005f;
    CC_config.config_PMSM.Psi_PM_Vs = 0.007f;
    CC_config.config_PMSM.polePairs = 5.0f;
    CC_config.config_PMSM.J_kg_m_squared = 0.00001773f;
    CC_config.config_PMSM.I_max_Ampere = 30.0f;
    CC_config.decoupling_select = linear_decoupling;
    CC_config.max_modulation_index = 1.0f / sqrtf(3.0f);
}



void tearDown(void)
{
}

void test_uz_parameterid_rc_init_pointer_not_null(void)
{
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    TEST_ASSERT_NOT_NULL(rc_instance);
}

void test_uz_parameterid_rs_init_equal(void){
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_config_t get_internal_config = uz_parameterid_rc_get_config(rc_instance);

    TEST_ASSERT_EQUAL_FLOAT(test_config.id_ref, get_internal_config.id_ref);
    TEST_ASSERT_EQUAL_FLOAT(test_config.iq_ref, get_internal_config.iq_ref);
}

void test_uz_parameterid_rc_generate_outputs_motor(void){
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_meas_out_t actual_output;
    float c = 500.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rc_generate_outputs(rc_instance, 1.0f, 1.0f, 1.0f, 1.0f, 1000.0f);
    }
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual_output.set_out.id_set);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, actual_output.set_out.iq_set);
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, actual_output.set_out.n_set);
    setUp();
}

void test_uz_parameterid_rc_generate_outputs_calc_u_ind_gen(void){
    test_config.wait_time = 4.0f * test_config.isr_steptime;
    test_config.sample_time = 10.0f * test_config.isr_steptime;
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_meas_out_t actual_output;
    float c = 21.0f; 
    for (int i = 0; i<=c; i++){
        actual_output = uz_parameterid_rc_generate_outputs(rc_instance, 1.0f, 1.0f, 1.0f, 1.0f, 1000.0f);
    }

    float r_s = (1.75e-6f * 1000.0f *  1000.0f + 5.733e-4f *  1000.0f + 28.4648f)/1000.0f;
    float u_ind_dq = 1.0f - r_s * 1.0f;

    TEST_ASSERT_EQUAL_FLOAT(-1.0f* u_ind_dq, actual_output.set_out.id_set);
    TEST_ASSERT_EQUAL_FLOAT(u_ind_dq, actual_output.set_out.iq_set);
    TEST_ASSERT_EQUAL_FLOAT(-1000.0f, actual_output.set_out.n_set);
    setUp();
}

void test_uz_parameterid_rc_generate_outputs_u_ind_gen_mode(void){
    test_config.wait_time = 5.0f * test_config.isr_steptime;
    test_config.sample_time = 5.0f * test_config.isr_steptime;
    test_config.id_ref = 8.6077f;
    test_config.iq_ref = -0.6824f;
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_meas_out_t actual_output2;
    uz_3ph_dq_t vol = {0};
    uz_3ph_dq_t cur = {0};
    uint32_t k = 18U; 
    for (uint32_t i = 0U; i<=k; i++){
            vol.d = 0.4250f;
            vol.q = 3.7790f;
            cur.d = 8.6077f;
            cur.q = -0.6824f;      
            actual_output2 = uz_parameterid_rc_generate_outputs(rc_instance,vol.d ,vol.q ,cur.d ,cur.q , 1000.0f);
    }

    float r_s = (1.75e-6f * 1000.0f *  1000.0f + 5.733e-4f *  1000.0f + 28.4648f)/1000.0f;
    float u_ind_d = -1.0f * (vol.d  - r_s * cur.d);
    float u_ind_q = vol.q - r_s * cur.q;

TEST_ASSERT_FLOAT_WITHIN(1e-3, u_ind_d , actual_output2.set_out.id_set);
TEST_ASSERT_FLOAT_WITHIN(1e-3, u_ind_q, actual_output2.set_out.iq_set);
TEST_ASSERT_EQUAL_FLOAT(-1000.0f, actual_output2.set_out.n_set);
}


void test_uz_parameterid_rc_generate_outputs_calc_rc(void){
    test_config.wait_time = 10.0f * test_config.isr_steptime;
    test_config.sample_time = 100.0f * test_config.isr_steptime;
    test_config.id_ref = 8.6077f;
    test_config.iq_ref = -0.6824f;
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_meas_out_t actual_output2;
    uz_3ph_dq_t vol = {0};
    uz_3ph_dq_t cur = {0};
    uint32_t k = 400U; 
    for (uint32_t i = 0U; i<=k; i++){
        if (i<=122U){
            vol.d = 0.4250f;
            vol.q = 3.7790f;
            cur.d = 8.6077f;
            cur.q = -0.6824f;
            }
        else{
            vol.d = 0.0910f;
            vol.q = 4.1550f;
            cur.d = 8.1509f;
            cur.q = 11.5304f;
            }         
    actual_output2 = uz_parameterid_rc_generate_outputs(rc_instance,vol.d ,vol.q ,cur.d ,cur.q , 1000.0f);
    }

TEST_ASSERT_FLOAT_WITHIN(1e-3, 0.7f, actual_output2.rc_d);
TEST_ASSERT_FLOAT_WITHIN(1e-3, 0.7f, actual_output2.rc_q);
TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output2.set_out.n_set);
}

void test_uz_parameterid_rc_generate_outputs_simulate_behaviour(void){
    test_config.wait_time = 5000.0f * test_config.isr_steptime;
    test_config.sample_time = 5000.0f * test_config.isr_steptime;
    test_config.id_ref = 5.0f;
    test_config.iq_ref = -5.0f;
    float r_s = (1.75e-6f * 1000.0f *  1000.0f + 5.733e-4f *  1000.0f + 28.4648f)/1000.0f;
    uz_CurrentControl_t* CC_instance = uz_CurrentControl_init(CC_config);
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    uz_pmsm_linear_rfe_t *pmsm = uz_pmsm_linear_rfe_init(R, psi_pm, L_d, L_q, rfe_d, rfe_q, ts);
    struct uz_parameterid_rc_meas_out_t actual_output2;
    uz_3ph_dq_t i_dq_ref_Amps = {0};
    uz_3ph_dq_t v_dq_Volts = {0};
    uz_3ph_dq_t i_dq_Amps = {0};
    float v_DC_Volts = 24.0f;
    uint32_t k = 50000U; 
    for (uint32_t i = 0U; i<=k; i++){

        if(actual_output2.gen){
            i_dq_Amps.d = v_dq_Volts.d - r_s * i_dq_Amps.d;
            i_dq_Amps.q = v_dq_Volts.q - r_s * i_dq_Amps.q;
        }

        v_dq_Volts = uz_CurrentControl_sample(CC_instance, i_dq_ref_Amps, i_dq_Amps, v_DC_Volts, omega_el);   
        i_dq_Amps = uz_pmsm_linear_rfe_step(pmsm, v_dq_Volts, omega_el);
        actual_output2 = uz_parameterid_rc_generate_outputs(rc_instance,v_dq_Volts.d ,v_dq_Volts.q ,i_dq_Amps.d ,i_dq_Amps.q , 1000.0f);
        i_dq_ref_Amps.d = actual_output2.set_out.id_set;
        i_dq_ref_Amps.q = actual_output2.set_out.iq_set;

    }

TEST_ASSERT_FLOAT_WITHIN(0.1, 0.7f, actual_output2.rc_d);
TEST_ASSERT_FLOAT_WITHIN(0.1, 0.7f, actual_output2.rc_q);
TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output2.set_out.n_set);

}

void test_uz_parameterid_rc_generate_outputs_test(void){
    test_config.wait_time = 10.0f * test_config.isr_steptime;
    test_config.sample_time = 100.0f * test_config.isr_steptime;
    test_config.id_ref = 8.6077f;
    test_config.iq_ref = -0.6824f;
    uz_parameterid_rc_t* rc_instance = uz_parameterid_rc_init(test_config);
    struct uz_parameterid_rc_meas_out_t actual_output2;
    uz_3ph_dq_t vol = {0};
    uz_3ph_dq_t cur = {0};
    uint32_t k = 400U; 
    for (uint32_t i = 0U; i<=k; i++){
        if (i<=122U){
            vol.d = 0.4250f;
            vol.q = 3.7790f;
            cur.d = 8.6077f;
            cur.q = -0.6824f;
            }
        else{
            vol.d = 0.0910f;
            vol.q = 4.1550f;
            cur.d = 8.1509f;
            cur.q = 11.5304f;
            }         
    actual_output2 = uz_parameterid_rc_generate_outputs(rc_instance,vol.d ,vol.q ,cur.d ,cur.q , 1000.0f);
    }

    uz_parameterid_rc_reset(rc_instance);
    actual_output2 = uz_parameterid_rc_generate_outputs(rc_instance,vol.d ,vol.q ,cur.d ,cur.q , 1000.0f);
    
TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output2.rc_d);
TEST_ASSERT_EQUAL_FLOAT(0.0f, actual_output2.rc_q);
TEST_ASSERT_EQUAL_FLOAT(-1000.0f, actual_output2.set_out.n_set);
}

#endif // TEST