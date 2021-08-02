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
uz_FOC_ActualValues values = {0};
uz_lin_decoupling_config config_lin_Decoup = {0};
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
    values.i_dq_meas_Ampere.d = 0.0f;
    values.i_dq_meas_Ampere.q = 0.0f;
    values.i_dq_meas_Ampere.zero = 0.0f;
    values.omega_el_rad_per_sec = 0.0f;
    values.U_zk_Volts = 24.0f;
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
        values.i_dq_meas_Ampere.q = values_iq[i];
        values.i_dq_meas_Ampere.d = values_id[i];
        values.omega_el_rad_per_sec = values_omega[i];
        struct uz_dq_t output = uz_FOC_sample(instance, values);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}
#endif // TEST