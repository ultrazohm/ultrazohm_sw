#ifdef TEST

#include "test_assert_with_exception.h"
#include "unity.h"
#include "uz_speedcontrol.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_signals/uz_signals.h"

struct uz_SpeedControl_config config = {0};
float omega_m_rad_per_sec = 0.0f;
float n_ref_rpm = 1000.0f;
void setUp(void)
{
    config.config_controller.Kp = 0.03456f;
    config.config_controller.Ki = 0.3456f;
    config.config_controller.samplingTime_sec = 0.00001f;
    config.config_controller.upper_limit = 10.0f;
    config.config_controller.lower_limit = -10.0f;
    omega_m_rad_per_sec = 0.0f;
    n_ref_rpm = 1000.0f;
}
void test_uz_SpeedControl_sample_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_sample(NULL, omega_m_rad_per_sec, n_ref_rpm));
}

void test_uz_SpeedControl_reset_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_reset(NULL));
}

void test_uz_SpeedControl_sample_output(void){
    //Values for comparision from simulation
    //Tests, if the output is as expected from the simulation
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, 0.011999f, 0.04947f};
    float torque_expected[5]={3.6191f, 3.6195f, 3.6198f, 3.62f, 3.62f}; 
    float torque = 0.0f;
    for(int i=0;i<5;i++){
        omega_m_rad_per_sec = (values_omega[i] / 4.0f);
        torque = uz_SpeedControl_sample(instance, omega_m_rad_per_sec, n_ref_rpm);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03,torque_expected[i], torque);
    }
}

void test_uz_SpeedControl_sample_output_negative_speed(void){
    //Values for comparision from simulation
    //Tests, if the output is as expected from the simulation
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, -0.011999f, -0.04947f};
    float torque_expected[5]={-3.6191f, -3.6195f, -3.6198f, -3.62f, -3.62f}; 
    n_ref_rpm = -1000.0f;
    float torque = 0.0f;
    for(int i=0;i<5;i++){
        omega_m_rad_per_sec = (values_omega[i] / 4.0f);
       torque = uz_SpeedControl_sample(instance, omega_m_rad_per_sec, n_ref_rpm);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, torque_expected[i], torque);
    }
}

void test_uz_SpeedControl_sample_output_limit(void){
    //Values for comparision from simulation
    //Tests, if the integrated output limitation of the controller works
    n_ref_rpm = 3000.0f;
    float torque = 0.0f;
    config.config_controller.upper_limit = 5.56f;
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
    float torque_expected = 5.56f;
    omega_m_rad_per_sec = 0.0f;
    torque = uz_SpeedControl_sample(instance, omega_m_rad_per_sec, n_ref_rpm);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, torque_expected, torque);
}

void test_uz_SpeedControl_sample_ext_clamping(void){
    //Values for comparision from simulation
    //Tests, if ext_clamping is active, that the integrator doesn't rise
    uz_SpeedControl_t* instance = uz_SpeedControl_init(config);
	float values_omega[5]={0.0f, 0.0f, 0.0f, 0.011999f, 0.04947f};
    float torque_expected[5]={3.6191f, 3.6191f, 3.6191f, 3.6190f, 3.6189f}; 
    float torque = 0.0f;
    uz_SpeedControl_set_ext_clamping(instance, true);
    for(int i=0;i<5;i++){
        omega_m_rad_per_sec = (values_omega[i] / 4.0f);
        uz_SpeedControl_set_ext_clamping(instance, true);
        torque = uz_SpeedControl_sample(instance, omega_m_rad_per_sec, n_ref_rpm);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, torque_expected[i], torque);
    }
}

void test_uz_SpeedControl_set_Ki_assert_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_set_Ki(NULL, 10.0f));
}


void test_uz_SpeedControl_set_Kp_assert_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_set_Ki(NULL, 10.0f));
}

void test_uz_SpeedControl_update_limits_NULL(void){
    float upper_limit = 10.0f;
    float lower_limit = -10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_update_limits(NULL, upper_limit, lower_limit));
}

void test_uz_SpeedControl_set_ext_clamping_assert_NULL(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_SpeedControl_set_ext_clamping(NULL, true));
}

#endif // TEST
