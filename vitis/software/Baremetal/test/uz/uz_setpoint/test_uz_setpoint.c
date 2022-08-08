#ifdef TEST

#include "test_assert_with_exception.h"
#include "unity.h"
#include "uz_setpoint.h"
#include "uz_newton_raphson.h"
#include "../uz_signals/uz_signals.h"

struct uz_SetPoint_config config = {0};
float omega_m_rad_per_sec = 0.0f;
float M_ref_Nm = 0.045f;
float V_DC_Volts = 24.0f;
void setUp(void)
{
    M_ref_Nm = 0.045f;
    config.id_ref_Ampere = 0.0f;
    config.config_PMSM.I_max_Ampere = 15.0f;
    config.config_PMSM.Ld_Henry = 0.0003f;
    config.config_PMSM.Lq_Henry = 0.0003f;
    config.config_PMSM.R_ph_Ohm = 0.1f;
    config.config_PMSM.polePairs = 4.0f;
    config.config_PMSM.Psi_PM_Vs = 0.0075f;
    config.motor_type = SMPMSM;
    config.is_field_weakening_enabled = false;
}

void test_uz_SetPoint_init_assert_Rph_negative(void){
    config.config_PMSM.R_ph_Ohm = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_Rph_zero(void){
    config.config_PMSM.R_ph_Ohm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_Ld_negative(void){
    config.config_PMSM.Ld_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_Ld_zero(void){
    config.config_PMSM.Ld_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_Lq_negative(void){
    config.config_PMSM.Lq_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_Lq_zero(void){
    config.config_PMSM.Lq_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_Psi_pm(void){
    config.config_PMSM.Psi_PM_Vs = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_polePairs_negative(void){
    config.config_PMSM.polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_polePairs_zero(void){
    config.config_PMSM.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_polePairs_decimal_value(void){
    config.config_PMSM.polePairs = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_I_max_negative(void){
    config.config_PMSM.I_max_Ampere = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_I_max_zero(void){
    config.config_PMSM.I_max_Ampere = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_init_assert_Ld_non_equal_Lq_for_IPMSM(void){
    config.motor_type = IPMSM;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_init(config));
}

void test_uz_SetPoint_set_PMSM_config_assert_Rph_negative(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.R_ph_Ohm = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_Rph_zero(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.R_ph_Ohm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_Ld_negative(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.Ld_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_Ld_zero(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.Ld_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_Lq_negative(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.Lq_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_Lq_zero(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.Lq_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_Psi_pm(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.Psi_PM_Vs = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_polePairs_negative(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_polePairs_zero(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_polePairs_decimal_value(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.polePairs = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_I_max_negative(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.I_max_Ampere = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_I_max_zero(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.I_max_Ampere = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_Ld_non_equal_Lq_for_IPMSM(void){
    config.motor_type = IPMSM;
    config.config_PMSM.Lq_Henry = 0.0002f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    config.config_PMSM.Lq_Henry = 0.0003f;
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(instance, config.config_PMSM));
}

void test_uz_SetPoint_set_PMSM_config_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_PMSM_config(NULL, config.config_PMSM));
}

void test_uz_SetPoint_set_field_weakening_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_field_weakening(NULL, true));
}

void test_uz_SetPoint_sample_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_sample(NULL, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts));
}

void test_uz_SetPoint_sample_V_DC_greater_than_zero(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, 0.0f));
}

void test_uz_SetPoint_set_id_ref_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_set_id_ref(NULL, 2.0f));        
}

void test_uz_SetPoint_sample_MTPA_SMPMSM_operation_no_id(void){
    //Results for comparision from simulation
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.d);
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.d);
}

void test_uz_SetPoint_sample_MTPA_SMPMSM_operation_manual_id(void){
    //Results for comparision from simulation
    config.id_ref_Ampere = -1.23f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(-1.23f, output.d);
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(-1.23f, output.d);
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_no_id(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,-0.0133f, output.d);//Since Lq>Ld, id should be negative
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.9986f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,-0.0533f, output.d);//Since Lq>Ld, id should be negative
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_Ld_greater_Lq(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Lq_Henry = 0.0002f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,0.0133f, output.d);//Since Ld>Lq, id should be positive
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.9986f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,0.0533f, output.d);//Since Ld>Lq, id should be positive
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_manual_id(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.id_ref_Ampere = -5.23f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,-5.23f, output.d);
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,-5.23f, output.d);
}

void test_uz_SetPoint_sample_MTPA_SMPMSM_operation_limit_iq_id(void){
    //Results for comparision from simulation

    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 2.0f;
    //Since reference torque is too high, output will be limited. Priority is given to q-current
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 15.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,0.0f, output.d);
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_limit_iq_id(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.id_ref_Ampere = -5.23f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 2.0f;
    //Since reference torque is too high, output will be limited. Priority is given to q-current
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 15.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,0.0f, output.d);
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_M_out(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.config_PMSM.I_max_Ampere = 55.0f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 2.0f;
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 36.9712f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -15.1604f, output.d);
    float M_output = 1.5f * config.config_PMSM.polePairs * output.q *(config.config_PMSM.Psi_PM_Vs + (config.config_PMSM.Ld_Henry - config.config_PMSM.Lq_Henry) * output.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.0f, M_output);
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_negative_M_out(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.config_PMSM.I_max_Ampere = 55.0f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = -2.0f;
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -36.9712f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -15.1604f, output.d);
    float M_output = 1.5f * config.config_PMSM.polePairs * output.q *(config.config_PMSM.Psi_PM_Vs + (config.config_PMSM.Ld_Henry - config.config_PMSM.Lq_Henry) * output.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -2.0f, M_output);
}


void test_uz_SetPoint_sample_MTPA_IPMSM_operation_multiple_instances(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.config_PMSM.I_max_Ampere = 55.0f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 2.0f;
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 36.9712f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -15.1604f, output.d);
    //Checks if multiple instances exist, that the coefficients for newton-algo are different (if different motor-params exist)
    config.config_PMSM.Ld_Henry = 0.00015f;
    uz_SetPoint_t* instance2 = uz_SetPoint_init(config);
    uz_3ph_dq_t output2 = uz_SetPoint_sample(instance2, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 33.3333f, output2.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -16.6667f, output2.d);

}


void test_uz_SetPoint_sample_field_weakening_SMPMSM_operation(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 0.09275f;
    omega_m_rad_per_sec = 418.67f; 
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.061f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.147f, output.d);
    //Negative speed
    M_ref_Nm = -0.09275f;
    omega_m_rad_per_sec = -418.67f; 
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -2.061f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.147f, output.d);  
}

void test_uz_SetPoint_sample_field_weakening_SMPMSM_manual_id(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    config.id_ref_Ampere = 5.0f; //Should be rejected, since its above the id_fw current
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 0.09275f;
    omega_m_rad_per_sec = 418.67f;   
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.061f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.147f, output.d);
    uz_SetPoint_set_id_ref(instance, -10.0f); //Should be accepted, since its below the id_fw current
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.061f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -10.0f, output.d);  
}

void test_uz_SetPoint_sample_field_weakening_IPMSM_operation(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.motor_type = IPMSM;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 0.0853f;
    omega_m_rad_per_sec = 419.0f;
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.8955f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.6457f, output.d);
    //Negative speed
    M_ref_Nm = -0.0853f;
    omega_m_rad_per_sec = -419.0f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -1.8955f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.6457f, output.d);  
}

void test_uz_SetPoint_sample_field_weakening_IPMSM_operation_manual_id(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    config.id_ref_Ampere = 5.0f; //Should be rejected, since its above the id_fw current
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.motor_type = IPMSM;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 0.0853f;
    omega_m_rad_per_sec = 419.0f;
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.8955f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.6457f, output.d);
    uz_SetPoint_set_id_ref(instance, -10.0f); //Should be accepted, since its below the id_fw current
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.8955f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -10.0f, output.d);  
}

void test_uz_SetPoint_get_clamping_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_get_clamping(NULL));
}

#endif // TEST
