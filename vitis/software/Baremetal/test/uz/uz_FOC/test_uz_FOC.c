#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_FOC.h"
TEST_FILE("uz_piController.c")
TEST_FILE("uz_signals.c")


uz_PI_Controller_config config_id = {0};
uz_PI_Controller_config config_iq = {0};
uz_PI_Controller_config config_n = {0};
uz_FOC_config config_FOC = {0};
uz_FOC_ActualValues values = {0};
void setUp(void)
{
    config_id.Kp = 6.75f;
    config_id.Ki = 2000.0f;
    config_id.samplingTime_sec = 0.0001f;
    config_id.upper_limit = 10.0f;
    config_id.lower_limit = -10.0f;
    config_iq.Kp = 6.75f;
    config_iq.Ki = 2000.0f;
    config_iq.samplingTime_sec = 0.0001f;
    config_iq.upper_limit = 10.0f;
    config_iq.lower_limit = -10.0f;
    config_n.Kp = 0.00864f,
    config_n.Ki = 0.0864f,
    config_n.samplingTime_sec = 0.0001f;
    config_n.upper_limit = 10.0f;
    config_n.lower_limit = -10.0f;
    config_FOC.iq_ref_Ampere = 1.0;
    config_FOC.id_ref_Ampere = 1.0f;
    config_FOC.n_ref_rpm = 1000.0f;
    config_FOC.FOC_Select = 1U;
    config_FOC.polePairs = 4.0f;
    config_FOC.L_q = 0.00027f;
    config_FOC.L_d = 0.00027f;
    config_FOC.psi_pm = 0.0082;
    config_FOC.Reset = false;
    values.i_d_Ampere = 0.0f;
    values.i_q_Ampere = 0.0f;
    values.is_ready = true;
    values.omega_el_rad_per_sec = 0.0f;
    values.theta_el_rad = 0.0f;
    values.U_zk_Volts = 0.0f;
}

void test_uz_FOC_init_L_d_negative(void){
    setUp();
    config_FOC.L_d = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_L_d_zero(void){
    setUp();
    config_FOC.L_d = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_L_q_negative(void){
    setUp();
    config_FOC.L_q = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_L_q_zero(void){
    setUp();
    config_FOC.L_q = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_psi_pm_negative(void){
    setUp();
    config_FOC.psi_pm = -0.1f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_psi_pm_zero(void){
    setUp();
    config_FOC.psi_pm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_polePairs_negative(void){
    setUp();
    config_FOC.polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_polePairs_zero(void){
    setUp();
    config_FOC.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_FOC_select_too_big(void){
    setUp();
    config_FOC.FOC_Select = 20U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_FOC_select_negative(void){
    setUp();
    config_FOC.FOC_Select = -20U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

void test_uz_FOC_init_FOC_select_zero(void){
    setUp();
    config_FOC.FOC_Select = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_init(config_FOC,config_id, config_iq, config_n));
}

#endif // TEST