#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_PMSM_config.h"

uz_PMSM_t config = {0};
uz_PMSM_flux_fitting_parameter_config_t fitting_config = {0};
void setUp(void)
{
    config = (uz_PMSM_t){
        .machine_id = 0U,
        .R_ph_Ohm = 0.08f,
        .Ld_Henry = 0.00027f,
        .Lq_Henry = 0.00027f,
        .Psi_PM_Vs = 0.0082f,
        .polePairs = 4.0f,
        .J_kg_m_squared = 0.00001773f,
        .I_max_Ampere = 20.0f,
        .I_rated_Ampere = 10.0f,
        .Torque_rated_Nm = 1.0f,
        .Torque_max_Nm = 2.0f,
        .Torque_min_Nm = -2.0f,
        .speed_rated_rpm = 1000.0f,
        .speed_max_rpm = 2000.0f,
        .speed_min_rpm = -2000.0f,
        .V_dc_nominal_V = 48.0f,
        .I_d_max_A = 10.0f,
        .I_d_min_A = -10.0f,
        .I_q_max_A = 10.0f,
        .I_q_min_A = -10.0f};
    fitting_config.ad1_parameter = 0.026620095524092f;
    fitting_config.ad2_parameter = 0.047133812840564f;
    fitting_config.ad3_parameter = -27.868596691410815f;
    fitting_config.ad4_parameter = 0.026771852823277f;
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
    fitting_config.F2G2_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_config_assert_fails_for_missing_new_fields(void)
{
    struct uz_PMSM_t config_old = {
        .R_ph_Ohm = 0.51f,
        .Ld_Henry = 0.002f,
        .Lq_Henry = 0.002f,
        .Psi_PM_Vs = 0.042f,
        .polePairs = 4.0f,
        .J_kg_m_squared = 0.000108f,
        .I_max_Ampere = 12.0f};
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config_old));
}

void test_uz_PMSM_dummy_machine(void)
{
    struct uz_PMSM_t config_old = {UZ_PMSM_BECKHOFF_AM8141_0J00_000_MEASURED_PSI_DQ_AVERAGED_800_RPM_INIT};
    uz_PMSM_config_assert(config_old);
}

#endif // TEST
