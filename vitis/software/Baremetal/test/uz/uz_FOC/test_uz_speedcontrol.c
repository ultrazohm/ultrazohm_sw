#ifdef TEST

#include "test_assert_with_exception.h"
#include "unity.h"
#include "uz_speedcontrol.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"

struct uz_SpeedControl_config config = {0};
float omega_el_rad_per_sec = 0.0f;
float n_ref_rpm = 1000.0f;
float id_ref_Ampere = 1.0f; 
float polePairs = 4.0f;
float V_dc_volts = 24.0f;
bool ext_clamping = false;
uz_PMSM_t config_PMSM = {0};
void setUp(void)
{
    config.config_controller.Kp = 0.00864f;
    config.config_controller.Ki = 0.0864f;
    config.config_controller.samplingTime_sec = 0.00001f;
    config.config_controller.upper_limit = 10.0f;
    config.config_controller.lower_limit = -10.0f;
    omega_el_rad_per_sec = 0.0f;
    n_ref_rpm = 1000.0f;
    id_ref_Ampere = 1.0f; 
    V_dc_volts = 24.0f;
    ext_clamping = false;
    config_PMSM.R_ph_Ohm = 0.08f;
    config_PMSM.Ld_Henry = 0.00027f;
    config_PMSM.Lq_Henry = 0.00027f;
    config_PMSM.Psi_PM_Vs = 0.0082f;
    config_PMSM.polePairs = 4.0f;
    config_PMSM.I_max_Ampere = 10.0f;
    config.enable_field_weakening = true;
}
void test_uz_SpeedControl_sample_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(NULL, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Rph_negative(void){
    config_PMSM.R_ph_Ohm = -0.08f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Rph_zero(void){
    config_PMSM.R_ph_Ohm = 0.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Ld_negative(void){
    config_PMSM.Ld_Henry = -0.08f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Ld_zero(void){
    config_PMSM.Ld_Henry = 0.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Lq_negative(void){
    config_PMSM.Lq_Henry = -0.08f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Lq_zero(void){
    config_PMSM.Lq_Henry = 0.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Psi_pm(void){
    config_PMSM.Psi_PM_Vs = -0.08f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_polePairs_negative(void){
    config_PMSM.polePairs = -2.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_polePairs_zero(void){
    config_PMSM.polePairs = 0.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_polePairs_decimal_value(void){
    config_PMSM.polePairs = 0.5f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_I_max_negative(void){
    config_PMSM.I_max_Ampere = -5.08f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_I_max_zero(void){
    config_PMSM.I_max_Ampere = 0.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_V_dc_negative(void){
    V_dc_volts = -5.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_V_dc_zero(void){
    V_dc_volts = 0.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_reset(NULL));
}

void test_uz_SpeedControl_sample_output(void){
    //Values for comparision from simulation
    //Tests, if the output is as expected from the simulation
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, 0.011999f, 0.04947f};
    float id_out[5]={1.0f, 1.0f,  1.0f,  1.0f,  1.0f};
    float iq_out[5]={3.6191f, 3.6195f, 3.6198f, 3.62f, 3.62f}; 
    for(int i=0;i<5;i++){
        omega_el_rad_per_sec = values_omega[i];
        uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out[i], output.q);
    }
}

void test_uz_SpeedControl_sample_output_negative_speed(void){
    //Values for comparision from simulation
    //Tests, if the output is as expected from the simulation
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, -0.011999f, -0.04947f};
    float id_out[5]={1.0f, 1.0f,  1.0f,  1.0f,  1.0f};
    float iq_out[5]={-3.6191f, -3.6195f, -3.6198f, -3.62f, -3.62f}; 
    n_ref_rpm = -1000.0f;
    for(int i=0;i<5;i++){
        omega_el_rad_per_sec = values_omega[i];
        uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out[i], output.q);
    }
}

void test_uz_SpeedControl_sample_output_limit(void){
    //Values for comparision from simulation
    //Tests, if the integrated output limitation of the controller works
    n_ref_rpm = 3000.0f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = 1.0f;
    float iq_out = 9.9499f;
    omega_el_rad_per_sec = 0.0f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_ext_clamping(void){
    //Values for comparision from simulation
    //Tests, if ext_clamping is active, that the integrator doesn't rise
    ext_clamping = true;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, 0.011999f, 0.04947f};
    float id_out[5]={1.0f, 1.0f,  1.0f,  1.0f,  1.0f};
    float iq_out[5]={3.6191f, 3.6191f, 3.6191f, 3.6190f, 3.6189f}; 
    for(int i=0;i<5;i++){
        omega_el_rad_per_sec = values_omega[i];
        uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out[i], output.q);
    }
}

void test_uz_SpeedControl_sample_field_weakening_active(void){
    //Values for comparision from simulation
    //Tests, if the id_fw_current is correct and the iq_output ist correctly limited
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = 0.0f; 
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = -4.332f;
    float iq_out = 8.582f;
    omega_el_rad_per_sec = 1675.5f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_active_negative_speed(void){
    //Values for comparision from simulation
    //Tests, if the id_fw_current is correct and the iq_output ist correctly limited
    n_ref_rpm = -7000.0f;
    id_ref_Ampere = 0.0f; 
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = -4.332f;
    float iq_out = -8.582f;
    omega_el_rad_per_sec = -1675.5f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_ref(void){
    //Values for comparision from simulation
    //Tests, that the manual id_ref is used, if its lower than id_fw_current
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = -5.0f; 
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = -5.0f;
    float iq_out = 8.582f;
    omega_el_rad_per_sec = 1675.5f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_ref_too_low(void){
    //Values for comparision from simulation
    //Tests, that the manual id_ref is not used, if its lower than -I_max
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = -25.0f; 
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = -4.332f;
    float iq_out = 8.582f;
    omega_el_rad_per_sec = 1675.5f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_positive(void){
    //Values for comparision from simulation
    //Tests, that a positive manual id_ref is used, if FW is off
    n_ref_rpm = 2000.0f;
    id_ref_Ampere = 5.0f; 
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = 5.0f;
    omega_el_rad_per_sec = 837.75f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_ref_limit_iq(void){
    //Values for comparision from simulation
    //Tests, that the manual id_ref is not used, if its lower than -I_max
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = 5.0f; 
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = 5.0f;
    float iq_out = 8.66f;
    omega_el_rad_per_sec = 209.44f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_disabled(void){
    //Values for comparision from simulation
    //Tests, if the id_fw_current = 0, since fw is disabled
    n_ref_rpm = 3600.0f;
    id_ref_Ampere = 0.0f; 
    config.enable_field_weakening = false;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = 0.0f;
    omega_el_rad_per_sec = 1466.1f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
}

void test_uz_SpeedControl_set_field_weakening_NULL(void){
    bool field_weakening_status = false;
	TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_set_field_weakening(NULL, field_weakening_status));
}

void test_uz_SpeedControl_set_field_weakening_change(void){
    //Values for comparision from simulation
    //Tests, if the enabling/disabling of the fw works
    n_ref_rpm = 3600.0f;
    id_ref_Ampere = 0.0f; 
    config.enable_field_weakening = true;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float id_out = -0.613f;
    omega_el_rad_per_sec = 1466.1f;
    uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
    //Tests, if the disabling works
    uz_SpeedControl_set_field_weakening(instance, false);
    output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, 0.0f, output.d);
    //Tests, if the enabling works
    uz_SpeedControl_set_field_weakening(instance, true);
    output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
    TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
}

void test_uz_SpeedControl_assert_Rph_negative_when_fw_disabled(void){
    config_PMSM.R_ph_Ohm = -0.08f;
    config.enable_field_weakening = false;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_PASS_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

#endif // TEST
