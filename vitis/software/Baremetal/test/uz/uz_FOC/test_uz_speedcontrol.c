#ifdef TEST

#include "test_assert_with_exception.h"
#include "unity.h"
#include "uz_speedcontrol.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"

struct uz_PI_Controller_config config = {0};
float omega_el_rad_per_sec = 0.0f;
float n_ref_rpm = 1000.0f;
float id_ref_Ampere = 1.0f; 
float polePairs = 4.0f;
float V_dc_volts = 24.0f;
bool ext_clamping = false;
struct uz_PMSM_t config_PMSM = {0};
void setUp(void)
{
    config.Kp = 0.00864f;
    config.Ki = 0.0864f;
    config.samplingTime_sec = 0.00001f;
    config.upper_limit = 10.0f;
    config.lower_limit = -10.0f;
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
}
void test_uz_SpeedControl_sample_NULL(void){
    setUp();
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(NULL, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Rph_negative(void){
    setUp();
    config_PMSM.R_ph_Ohm = -0.08f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Rph_zero(void){
    setUp();
    config_PMSM.R_ph_Ohm = 0.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Ld_negative(void){
    setUp();
    config_PMSM.Ld_Henry = -0.08f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Ld_zero(void){
    setUp();
    config_PMSM.Ld_Henry = 0.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Lq_negative(void){
    setUp();
    config_PMSM.Lq_Henry = -0.08f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Lq_zero(void){
    setUp();
    config_PMSM.Lq_Henry = 0.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_Psi_pm(void){
    setUp();
    config_PMSM.Psi_PM_Vs = -0.08f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_polePairs_negative(void){
    setUp();
    config_PMSM.polePairs = -2.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_polePairs_zero(void){
    setUp();
    config_PMSM.polePairs = 0.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_polePairs_decimal_value(void){
    setUp();
    config_PMSM.polePairs = 0.5f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_I_max_negative(void){
    setUp();
     config_PMSM.I_max_Ampere = -5.08f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_I_max_zero(void){
    setUp();
     config_PMSM.I_max_Ampere = 0.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_V_dc_negative(void){
    setUp();
    V_dc_volts = -5.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_assert_V_dc_zero(void){
    setUp();
    V_dc_volts = 0.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping));
}

void test_uz_SpeedControl_reset_NULL(void){
    setUp();
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_reset(NULL));
}

void test_uz_SpeedControl_sample_output(void){
    setUp();
    //Values for comparision from simulation
    //Tests, if the output is as expected from the simulation
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, 0.011999f, 0.04947f};
    float id_out[5]={1.0f, 1.0f,  1.0f,  1.0f,  1.0f};
    float iq_out[5]={3.6191f, 3.6195f, 3.6198f, 3.62f, 3.62f}; 
    for(int i=0;i<5;i++){
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out[i], output.q);
    }
}

void test_uz_SpeedControl_sample_output_limit(void){
    setUp();
    //Values for comparision from simulation
    //Tests, if the integrated output limitation of the controller works
    n_ref_rpm = 3000.0f;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    float id_out = 1.0f;
    float iq_out = 9.9499f;
    omega_el_rad_per_sec = 0.0f;
    struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_ext_clamping(void){
    setUp();
    //Values for comparision from simulation
    //Tests, if ext_clamping is active, that the integrator doesn't rise
    ext_clamping = true;
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, 0.011999f, 0.04947f};
    float id_out[5]={1.0f, 1.0f,  1.0f,  1.0f,  1.0f};
    float iq_out[5]={3.6191f, 3.6191f, 3.6191f, 3.6190f, 3.6189f}; 
    for(int i=0;i<5;i++){
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out[i], output.q);
    }
}

void test_uz_SpeedControl_sample_field_weakening_active(void){
    setUp();
    //Values for comparision from simulation
    //Tests, if the id_fw_current is correct and the iq_output ist correctly limited
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = 0.0f; 
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    float id_out = -4.332f;
    float iq_out = 8.582f;
    omega_el_rad_per_sec = 1675.5f;
    struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_ref(void){
    setUp();
    //Values for comparision from simulation
    //Tests, that the manual id_ref is used, if its lower than id_fw_current
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = -5.0f; 
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    float id_out = -5.0f;
    float iq_out = 8.582f;
    omega_el_rad_per_sec = 1675.5f;
    struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_ref_too_low(void){
    setUp();
    //Values for comparision from simulation
    //Tests, that the manual id_ref is not used, if its lower than -I_max
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = -25.0f; 
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    float id_out = -4.332f;
    float iq_out = 8.582f;
    omega_el_rad_per_sec = 1675.5f;
    struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_positive(void){
    setUp();
    //Values for comparision from simulation
    //Tests, that a positive manual id_ref is used, if FW is off
    n_ref_rpm = 2000.0f;
    id_ref_Ampere = 5.0f; 
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    float id_out = 5.0f;
    omega_el_rad_per_sec = 837.75f;
    struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
}

void test_uz_SpeedControl_sample_field_weakening_manual_id_ref_limit_iq(void){
    setUp();
    //Values for comparision from simulation
    //Tests, that the manual id_ref is not used, if its lower than -I_max
    n_ref_rpm = 7000.0f;
    id_ref_Ampere = 5.0f; 
    uz_PI_Controller* instance = uz_SpeedControl_init(config);
    float id_out = 5.0f;
    float iq_out = 8.66f;
    omega_el_rad_per_sec = 209.44f;
    struct uz_dq_t output = uz_SpeedControl_sample(instance, omega_el_rad_per_sec, n_ref_rpm, V_dc_volts, id_ref_Ampere, config_PMSM, ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, id_out, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, iq_out, output.q);
}
#endif // TEST
