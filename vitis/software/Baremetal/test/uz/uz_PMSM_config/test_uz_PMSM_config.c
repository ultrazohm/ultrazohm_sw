#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_PMSM_config.h"

uz_PMSM_t config = {0};
uz_PMSM_flux_fitting_parameter_config_t fitting_config = {0};
void setUp(void)
{
    config.R_ph_Ohm = 0.08f;
    config.Ld_Henry = 0.00027f;
    config.Lq_Henry = 0.00027f;
    config.Psi_PM_Vs = 0.0082f;
    config.polePairs = 4.0f;
    config.J_kg_m_squared = 0.00001773f;
    config.I_max_Ampere = 20.0f;
    fitting_config.ad1_parameter = 0.026620095524092f;
    fitting_config.ad2_parameter = 0.047133812840564f;
    fitting_config.ad3_parameter = -27.868596691410815f;
    fitting_config.ad4_parameter = 0.026771852823277;
    fitting_config.ad5_parameter = 0.032335709299499f;
    fitting_config.ad6_parameter = -27.939757152811232f;
    fitting_config.aq1_parameter = 0.006639611096337f;
    fitting_config.aq2_parameter = 0.140324092149110f;
    fitting_config.aq3_parameter = 6.036938033671378e-04f;
    fitting_config.aq4_parameter = 0.006818079861355f;
    fitting_config.aq5_parameter = 0.148494853843815f;
    fitting_config.aq6_parameter = 6.202760235239144e-04f;
    fitting_config.F1G1_parameter = -0.005816630245736f;
    fitting_config.F2G2_parameter = 0.294469757399354f;
}


void test_uz_PMSM_config_assert_R_ph(void){
    config.R_ph_Ohm = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.R_ph_Ohm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_Ld(void){
    config.Ld_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.Ld_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_Lq(void){
    config.Lq_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.Lq_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_Psi_PM(void){
    config.Psi_PM_Vs = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_polePairs(void){
    config.polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.polePairs = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_J(void){
    config.J_kg_m_squared = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.J_kg_m_squared = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_I_max(void){
    config.I_max_Ampere = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.I_max_Ampere = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_ad_parameter(void){
    fitting_config.ad1_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad2_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad3_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad4_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad5_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad6_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_config_assert_aq_parameter(void){
    fitting_config.aq1_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq2_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq3_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq4_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq5_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq6_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_config_assert_F1G1_parameter(void){
    fitting_config.F1G1_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_config_assert_F2G2_parameter(void){
    fitting_config.F1G1_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
}

#endif // TEST
