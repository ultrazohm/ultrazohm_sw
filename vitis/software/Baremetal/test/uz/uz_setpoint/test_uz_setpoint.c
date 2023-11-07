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
uz_3ph_dq_t currents = {0};
void setUp(void)
{
    M_ref_Nm = 0.045f;
    config.config_PMSM.I_max_Ampere = 15.0f;
    config.config_PMSM.Ld_Henry = 0.0003f;
    config.config_PMSM.Lq_Henry = 0.0003f;
    config.config_PMSM.R_ph_Ohm = 0.1f;
    config.config_PMSM.polePairs = 4.0f;
    config.config_PMSM.Psi_PM_Vs = 0.0075f;
    config.motor_type = SMPMSM;
    config.is_field_weakening_enabled = false;
    config.relative_torque_tolerance = 1.0f;
    config.use_case = SP_TorqueControl;
    config.max_modulation_index = 1.0f / sqrtf(3.0f);
    currents.d = 0.0f;
    currents.q = 0.0f;
    omega_m_rad_per_sec = 0.0f;
    V_DC_Volts = 24.0f;
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
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_sample(NULL, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents));
}

void test_uz_SetPoint_sample_V_DC_greater_than_zero(void){
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, 0.0f, currents));
}


void test_uz_SetPoint_sample_MTPA_SMPMSM_operation_no_id(void){
    //Results for comparision from simulation
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.d);
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.d);
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_no_id(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,-0.0133f, output.d);//Since Lq>Ld, id should be negative
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.9986f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,-0.0533f, output.d);//Since Lq>Ld, id should be negative
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_Ld_greater_Lq(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Lq_Henry = 0.0002f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.0f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,0.0133f, output.d);//Since Ld>Lq, id should be positive
    M_ref_Nm = 0.09f;
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.9986f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03,0.0533f, output.d);//Since Ld>Lq, id should be positive
}

void test_uz_SetPoint_sample_MTPA_SMPMSM_operation_limit_iq_id(void){
    //Results for comparision from simulation

    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 2.0f;
    //Since reference torque is too high, output will be limited. Priority is given to q-current
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
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
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 36.9712f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -15.1604f, output.d);
    float M_output = 1.5f * config.config_PMSM.polePairs * output.q *(config.config_PMSM.Psi_PM_Vs + (config.config_PMSM.Ld_Henry - config.config_PMSM.Lq_Henry) * output.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.0f, M_output);
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_check_tolerance(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.R_ph_Ohm = 0.01664f;
    config.config_PMSM.Ld_Henry = 0.00003f;
    config.config_PMSM.Lq_Henry = 0.00005f;
    config.config_PMSM.Psi_PM_Vs = 0.007f;
    config.config_PMSM.polePairs = 5.0f;
    config.config_PMSM.I_max_Ampere = 55.0f;
    config.relative_torque_tolerance = 1e-08f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 10.0f;
    //(fabsf(M_ref_Nm - M_estimated_Nm)) / M_ref_Nm = 9.54e-08
    //Error bigger than relative torque tolerance config->Should assert
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents));
}

void test_uz_SetPoint_sample_MTPA_IPMSM_operation_negative_M_out(void){
    //Results for comparision from simulation
    config.motor_type = IPMSM;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.config_PMSM.I_max_Ampere = 55.0f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = -2.0f;
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
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
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 36.9712f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -15.1604f, output.d);
    //Checks if multiple instances exist, that the coefficients for newton-algo are different (if different motor-params exist)
    config.config_PMSM.Ld_Henry = 0.00015f;
    uz_SetPoint_t* instance2 = uz_SetPoint_init(config);
    uz_3ph_dq_t output2 = uz_SetPoint_sample(instance2, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 33.3333f, output2.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -16.6667f, output2.d);

}


void test_uz_SetPoint_sample_field_weakening_SMPMSM_operation(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 0.105f;
    currents.d = 0.0f;
    currents.q = 0.0f;
    omega_m_rad_per_sec = 490.0f; 
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.333f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -2.7349f, output.d);
    //Negative speed
    M_ref_Nm = -0.105f;
    omega_m_rad_per_sec = -490.0f; 
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -2.333f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -2.7349f, output.d);  
}

void test_uz_SetPoint_sample_field_weakening_IPMSM_operation_negative(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.motor_type = IPMSM;
    currents.d = 0.0f;
    currents.q = 0.0f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 0.1f;
    omega_m_rad_per_sec = 500.6f; 
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.089f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -4.780f, output.d);
    //Negative speed
    M_ref_Nm = -0.1f;
    omega_m_rad_per_sec = -500.6f; 
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -2.089f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -4.780f, output.d);  
}

void test_uz_SetPoint_sample_field_weakening_IPMSM_check_tolerance(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    config.motor_type = IPMSM;
    config.config_PMSM.R_ph_Ohm = 0.01664f;
    config.config_PMSM.Ld_Henry = 0.00003f;
    config.config_PMSM.Lq_Henry = 0.00005f;
    config.config_PMSM.Psi_PM_Vs = 0.007f;
    config.config_PMSM.polePairs = 5.0f;
    config.config_PMSM.I_max_Ampere = 55.0f;
    config.relative_torque_tolerance = 1e-08f;
    currents.d = -6.65f;
    currents.q = 1.9f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    M_ref_Nm = 1.0f;
    omega_m_rad_per_sec = 430.13f;
    //(fabsf(M_ref_Nm - M_estimated_Nm)) / M_ref_Nm = 2.384e-07
    //Error bigger than relative torque tolerance config->Should assert 
    TEST_ASSERT_FAIL_ASSERT(uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents));
}

void test_uz_SetPoint_sample_field_weakening_IPMSM_operation_two_instances(void){
    //Results for comparision from simulation
    config.is_field_weakening_enabled = true;
    config.config_PMSM.Ld_Henry = 0.0002f;
    config.motor_type = IPMSM;
    currents.d = 0.0f;
    currents.q = 0.0f;
    uz_SetPoint_t* instance = uz_SetPoint_init(config);
    //instance2 has different Ld
    config.config_PMSM.Ld_Henry = 0.00015f;
    uz_SetPoint_t* instance2 = uz_SetPoint_init(config);
    M_ref_Nm = 0.1f;
    omega_m_rad_per_sec = 500.6f; 
    uz_3ph_dq_t output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.089f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -4.780f, output.d);
    uz_3ph_dq_t output2 = uz_SetPoint_sample(instance2, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    //instance2 with different Ld should lead to different currents
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 1.972f, output2.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -6.352f, output2.d);
    //recalculating instance1 should lead to no different results than before for output. 
    //No mixup with the coefficient array addresses exist
    output = uz_SetPoint_sample(instance, omega_m_rad_per_sec, M_ref_Nm, V_DC_Volts, currents);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 2.089f, output.q);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, -4.780f, output.d);
}


#endif // TEST
