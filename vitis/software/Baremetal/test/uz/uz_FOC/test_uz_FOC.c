#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"
TEST_FILE("uz_piController.c")
TEST_FILE("uz_signals.c")
TEST_FILE("uz_linear_decoupling.c")
TEST_FILE("uz_space_vector_limitation.c")


uz_PI_Controller_config config_id = {0};
uz_PI_Controller_config config_iq = {0};
uz_PI_Controller_config config_n = {0};
uz_FOC_config config_FOC = {0};
uz_lin_decoupling_config config_lin_Decoup = {0};
struct uz_dq_t i_dq_meas_Ampere = {0};
float omega_el_rad_per_sec = 0.0f;
float U_zk_Volts = 0.0f;
void setUp(void)
{
    config_id.Kp = 6.75f;
    config_id.Ki = 2000.0f;
    config_id.samplingTime_sec = 0.00001f;
    config_id.upper_limit = 10.0f;
    config_id.lower_limit = -10.0f;
    config_iq.Kp = 6.75f;
    config_iq.Ki = 2000.0f;
    config_iq.samplingTime_sec = 0.00001f;
    config_iq.upper_limit = 10.0f;
    config_iq.lower_limit = -10.0f;
    config_n.Kp = 0.00864f,
    config_n.Ki = 0.0864f,
    config_n.samplingTime_sec = 0.00001f;
    config_n.upper_limit = 10.0f;
    config_n.lower_limit = -10.0f;
    config_FOC.iq_ref_Ampere = 1.0f;
    config_FOC.id_ref_Ampere = 1.0f;
    config_FOC.n_ref_rpm = 1000.0f;
    config_FOC.FOC_Select = 1U;
    config_FOC.polePairs = 4.0f;
    i_dq_meas_Ampere.d = 0.0f;
    i_dq_meas_Ampere.q = 0.0f;
    i_dq_meas_Ampere.zero = 0.0f;
    omega_el_rad_per_sec = 0.0f;
    U_zk_Volts = 24.0f;
    config_lin_Decoup.Ld_Henry = 0.00027f;
    config_lin_Decoup.Lq_Henry = 0.00027f;
    config_lin_Decoup.Psi_PM_Vs = 0.0082f;
}

void test_uz_FOC_init_polePairs_negative(void){
    setUp();
    config_FOC.polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_init_polePairs_zero(void){
    setUp();
    config_FOC.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_init_FOC_select_too_big(void){
    setUp();
    config_FOC.FOC_Select = 20U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_init_FOC_select_negative(void){
    setUp();
    config_FOC.FOC_Select = -20U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_init_FOC_select_zero(void){
    setUp();
    config_FOC.FOC_Select = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_reset_NULL(void){
    setUp();
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_reset(NULL));
}

void test_uz_FOC_set_Kp_n_NULL(void){
    setUp();
    float Kp_n = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_n(NULL, Kp_n));
}

void test_uz_FOC_set_Kp_n_negative(void){
    setUp();
    float Kp_n = -10.0f;
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_n(instance, Kp_n));
}

void test_uz_FOC_set_Ki_n_negative(void){
    setUp();
    float Ki_n = -10.0f;
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Ki_n(instance, Ki_n));
}

void test_uz_FOC_set_Kp_id_NULL(void){
    setUp();
    float Kp_id = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_id(NULL, Kp_id));
}

void test_uz_FOC_set_Kp_id_negative(void){
    setUp();
    float Kp_id = -10.0f;
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_id(instance, Kp_id));
}

void test_uz_FOC_set_Ki_id_negative(void){
    setUp();
    float Ki_id = -10.0f;
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Ki_id(instance, Ki_id));
}

void test_uz_FOC_set_Kp_iq_NULL(void){
    setUp();
    float Kp_iq = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_iq(NULL, Kp_iq));
}

void test_uz_FOC_set_Kp_iq_negative(void){
    setUp();
    float Kp_iq = -10.0f;
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Kp_iq(instance, Kp_iq));
}

void test_uz_FOC_set_Ki_iq_negative(void){
    setUp();
    float Ki_iq = -10.0f;
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_Ki_iq(instance, Ki_iq));
}

void test_uz_FOC_set_id_ref_NULL(void){
    setUp();
    float id_ref = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_id_ref(NULL, id_ref));
}

void test_uz_FOC_set_iq_ref_NULL(void){
    setUp();
    float iq_ref = 10.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_iq_ref(NULL, iq_ref));
}

void test_uz_FOC_set_n_ref_NULL(void){
    setUp();
    float n_ref_rpm = 1000.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_iq_ref(NULL, n_ref_rpm));
}

void test_uz_FOC_set_polePairs_negative(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_polePairs(instance, polePairs));
}

void test_uz_FOC_set_polePairs_zero(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_set_polePairs(instance, polePairs));
}

void test_uz_FOC_change_control_Method_NULL(void){
    setUp();
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(NULL,config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_FOC_Select_negative(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = -20U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance,config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_FOC_Select_zero(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance,config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_FOC_Select_too_big(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance,config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_same_FOC_Select(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance,config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_sample_output(void){
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
    float values_id[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
	float values_omega[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.756f, 0.588f, 0.461f};
    float uq_out[11]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f, 1.68f, 1.3f, 1.01f, 0.811f, 0.671f, 0.581}; 
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}
//test, if possible, if the new variables ki,iqref etc are written into the self instance

void test_uz_FOC_sample_output_SVLimitation_active(void){
    setUp();
    U_zk_Volts = 10.0f;
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[11]={0.874f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f, 0.871f};
    float values_id[11]={1.0f, 0.998f, 0.997f, 0.996f, 0.995f, 0.995f, 0.994f, 0.994f, 0.994f, 0.994f, 0.993f};
	float values_omega[11]={673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f, 673.0f};
    float ud_out[11]={-0.159f, -0.146f, -0.138f, -0.131f, -0.126f, -0.123f, -0.12f, -0.118f, -0.116f, -0.115f, -0.114f};
    float uq_out[11]={5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77f, 5.77}; 
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}

void test_uz_FOC_reset(void){
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f};
    float uq_out[5]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f}; 
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
    uz_FOC_reset(instance);
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}

void test_uz_FOC_change_control_Method_FOC_select_too_big(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = 5U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance, config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_FOC_select_zero(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance, config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_FOC_select_negative(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = -5U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance, config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_FOC_select_equal_too_old_Selection(void){
    setUp();
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    config_FOC.FOC_Select = 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_change_control_Method(instance, config_FOC, config_id, config_iq, config_n, config_lin_Decoup));
}

void test_uz_FOC_change_control_Method_from_current_to_speed(void){
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f};
    float uq_out[5]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f}; 
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
    config_FOC.FOC_Select = 2U;
    config_FOC.n_ref_rpm = 2000.0f;
    instance = uz_FOC_change_control_Method(instance, config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq2[11]={0.0f, 0.369f, 0.737f, 1.1f, 1.47f, 1.83f, 2.2f, 2.56f, 2.92f, 3.28f, 3.64f};
    float values_id2[11]={0.0f, 0.249f, 0.436f, 0.576f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.924f, 0.942f};
	float values_omega2[11]={0.0f, 0.0f, 0.0f, 0.012f, 0.0495f, 0.125f, 0.249f, 0.428f, 0.663f, 0.953f, 1.29f};
    float ud_out2[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.981f, 0.757f, 0.589f, 0.463f};
    float uq_out2[11]={10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.01f, 10.01f, 10.01f}; 
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq2[i];
        i_dq_meas_Ampere.d = values_id2[i];
        omega_el_rad_per_sec = values_omega2[i];
        struct uz_dq_t output2 = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out2[i], output2.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out2[i], output2.q);
    }
}

void test_uz_FOC_change_control_Method_from_speed_to_current(void){
    setUp();
    //Values for comparision from simulation
    config_FOC.FOC_Select = 2U;
    config_FOC.n_ref_rpm = 2000.0f;
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[11]={0.0f, 0.369f, 0.737f, 1.1f, 1.47f, 1.83f, 2.2f, 2.56f, 2.92f, 3.28f, 3.64f};
    float values_id[11]={0.0f, 0.249f, 0.436f, 0.576f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.924f, 0.942f};
	float values_omega[11]={0.0f, 0.0f, 0.0f, 0.012f, 0.0495f, 0.125f, 0.249f, 0.428f, 0.663f, 0.953f, 1.29f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.981f, 0.757f, 0.589f, 0.463f};
    float uq_out[11]={10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.01f, 10.01f, 10.01f}; 
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
    setUp();
    instance = uz_FOC_change_control_Method(instance, config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq2[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.76f, 0.819f, 0.863f, 0.895f, 0.919f, 0.937f};
    float values_id2[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.899f, 0.924f, 0.943f};
	float values_omega2[11]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f, 0.622f, 1.26f, 2.29f, 3.85f, 6.08f, 9.13f};
    float ud_out2[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.756f, 0.588f, 0.461f};
    float uq_out2[11]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f, 1.68f, 1.3f, 1.01f, 0.811f, 0.671f, 0.581f};
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq2[i];
        i_dq_meas_Ampere.d = values_id2[i];
        omega_el_rad_per_sec = values_omega2[i];
        struct uz_dq_t output2 = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out2[i], output2.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out2[i], output2.q);
    }
}

void test_uz_FOC_set_Kp_and_Ki_n(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    config_FOC.FOC_Select = 2U;
    config_FOC.id_ref_Ampere = 0.0f;
    struct uz_dq_t output = {0};
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    for(int i=0;i<11;i++){
        output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 10.0f, output.q);
    uz_FOC_set_Kp_n(instance, 0.0f);
    uz_FOC_set_Ki_n(instance, 0.0f);
    uz_FOC_reset(instance);
    for(int i=0;i<5;i++){
        output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.q);
}

void test_uz_FOC_set_Kp_and_Ki_id(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    struct uz_dq_t output = {0};
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    for(int i=0;i<11;i++){
        output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }    
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.q);
    uz_FOC_set_Kp_id(instance, 0.0f);
    uz_FOC_set_Ki_id(instance, 0.0f);
    uz_FOC_reset(instance);
    for(int i=0;i<5;i++){
        output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.83f, output.q);
}

void test_uz_FOC_set_Kp_and_Ki_iq(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    struct uz_dq_t output = {0};
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    for(int i=0;i<11;i++){
        output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }    
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.95f, output.q);
    uz_FOC_set_Kp_iq(instance, 0.0f);
    uz_FOC_set_Ki_iq(instance, 0.0f);
    uz_FOC_reset(instance);
    for(int i=0;i<5;i++){
        output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
    }
    TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.83f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.0f, output.q);
}

void test_uz_FOC_set_id_ref(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f};
    float uq_out[5]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f}; 
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
    uz_FOC_set_id_ref(instance, 0.0f);
    uz_FOC_reset(instance);
    float values_iq2[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id2[5]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float values_omega2[5]={0.0f, 0.0f, 0.0f, 0.0f, 0.0121f};
    float ud_out2[5]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float uq_out2[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.21f}; 
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq2[i];
        i_dq_meas_Ampere.d = values_id2[i];
        omega_el_rad_per_sec = values_omega2[i];
        struct uz_dq_t output2 = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out2[i], output2.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out2[i], output2.q);
    }
}

void test_uz_FOC_set_iq_ref(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_id[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
	float values_omega[5]={0.0f, 0.0f, 0.0178f, 0.0876f, 0.264f};
    float ud_out[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f};
    float uq_out[5]={6.75f, 5.09f, 3.84f, 2.91f, 2.21f}; 
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
    uz_FOC_set_iq_ref(instance, 0.0f);
    uz_FOC_reset(instance);
    float values_id2[5]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f};
    float values_iq2[5]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float values_omega2[5]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float uq_out2[5]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float ud_out2[5]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f}; 
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq2[i];
        i_dq_meas_Ampere.d = values_id2[i];
        omega_el_rad_per_sec = values_omega2[i];
        struct uz_dq_t output2 = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out2[i], output2.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out2[i], output2.q);
    }
}

void test_uz_FOC_set_n_ref(void){
    //Tests, if the new values are properly written into the FOC instance
    setUp();
    config_FOC.FOC_Select = 2U;
    config_FOC.id_ref_Ampere = 0.0f;
    config_FOC.n_ref_rpm = 500.0f;
    //Values for comparision from simulation
    uz_FOC* instance = uz_FOC_init(config_FOC, config_id, config_iq, config_n, config_lin_Decoup);
    float values_iq[12]={0.0f, 0.36930f, 0.72709f, 0.99564f, 1.1972f, 1.3485f, 1.4619f, 1.5469f, 1.6105f, 1.65795f, 1.6933f, 1.7194f};
    float values_id[12]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	float values_omega[12]={0.0f, 0.0f, 0.0f, 0.010545f, 0.041861f, 0.10171f, 0.19404f, 0.31847f, 0.47053f, 0.64254f, 0.82482f, 1.0071f};
    float ud_out[12]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.00017f, -0.00025f, -0.00045f, -0.00055};
    float uq_out[12]={10.0f, 9.7230f, 7.3379f, 5.5475f, 4.2028f, 3.1922f, 2.4324f, 1.8606f, 1.4303f, 1.1065f, 0.86317f, 0.68073f}; 
    for(int i=0;i<12;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        i_dq_meas_Ampere.d = values_id[i];
        omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, uq_out[i], output.q);
    }
    //Checks if currents and omega rise faster now
    uz_FOC_set_n_ref(instance,2000.0f);
    uz_FOC_reset(instance);
    float values_id2[6]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float values_iq2[6]={0.0f, 0.36930f, 0.73732f, 1.1041f, 1.46978f, 1.8342f};
	float values_omega2[6]={0.0f, 0.0f, 0.0f, 0.012f, 0.04951f, 0.12525};
    float ud_out2[6]={0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    float uq_out2[6]={10.0f, 10.0f, 10.0f, 10.0f, 10.0f, 10.0f}; 
    for(int i=0;i<5;i++){
        i_dq_meas_Ampere.q = values_iq2[i];
        i_dq_meas_Ampere.d = values_id2[i];
        omega_el_rad_per_sec = values_omega2[i];
        struct uz_dq_t output2 = uz_FOC_sample(instance, i_dq_meas_Ampere, U_zk_Volts, omega_el_rad_per_sec);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, ud_out2[i], output2.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-03, uq_out2[i], output2.q);
    }
}
#endif // TEST