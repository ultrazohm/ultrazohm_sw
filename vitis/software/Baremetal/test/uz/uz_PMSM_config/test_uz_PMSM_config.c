#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_PMSM_config.h"

uz_PMSM_t config = {0};
void setUp(void)
{
    config.R_ph_Ohm = 0.08f;
    config.Ld_Henry = 0.00027f;
    config.Lq_Henry = 0.00027f;
    config.Psi_PM_Vs = 0.0082f;
    config.polePairs = 4.0f;
    config.J_kg_m_squared = 0.00001773f;
    config.I_max_Ampere = 20.0f;
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


//Fitting Parameter config tests

uz_PMSM_flux_fitting_parameter_config_t fitting_config = {0};
void setUp_fitting_parameter(void)
{
    fitting_config.ad1_parameter = 0.030483840951002f;
	fitting_config.ad2_parameter = 0.040244227373267f;
	fitting_config.ad3_parameter = -16.481195185733903f;
	fitting_config.ad4_parameter = 1.296438633344970f;
	fitting_config.ad5_parameter = 6.183163374457993e-04f;
	fitting_config.ad6_parameter = -12.275586044862504f;
	fitting_config.aq1_parameter = 0.004816670542863f;
	fitting_config.aq2_parameter = 0.171595254784258f;
	fitting_config.aq3_parameter = 9.262938633610718e-04f;
	fitting_config.aq4_parameter = 0.005001870975338f;
	fitting_config.aq5_parameter = 0.170521235710151f;
	fitting_config.aq6_parameter = 9.186084507499523e-04f;
	fitting_config.F1G1_parameter = -0.001356794026337f;
	fitting_config.F2G2_parameter = 0.078813850391713f;
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_ad1_parameter(void){
    fitting_config.ad1_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad1_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_ad2_parameter(void){
    fitting_config.ad2_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad2_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_ad3_parameter(void){
    fitting_config.ad3_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad3_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_ad4_parameter(void){
    fitting_config.ad4_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad4_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_ad5_parameter(void){
    fitting_config.ad5_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad5_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_ad6_parameter(void){
    fitting_config.ad6_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.ad6_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_aq1_parameter(void){
    fitting_config.aq1_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq1_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_aq2_parameter(void){
    fitting_config.aq2_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq2_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_aq3_parameter(void){
    fitting_config.aq3_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq3_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_aq4_parameter(void){
    fitting_config.aq4_parameter = 1.02f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq4_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_aq5_parameter(void){
    fitting_config.aq5_parameter = -0.18f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq5_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_aq6_parameter(void){
    fitting_config.aq6_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.aq6_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_F1G1_parameter(void){
    fitting_config.F1G1_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.F1G1_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

void test_uz_PMSM_flux_fitting_parameter_config_assert_F2G2_parameter(void){
    fitting_config.F2G2_parameter = -5.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
    fitting_config.F2G2_parameter = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_flux_fitting_parameter_config_assert(fitting_config));
}

#endif // TEST
