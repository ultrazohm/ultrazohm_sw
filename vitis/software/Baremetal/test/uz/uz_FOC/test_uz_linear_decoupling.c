#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_linear_decoupling.h"
#include "uz_Transformation.h"

uz_lin_decoupling_config config = {0};
struct uz_dq_t i_dq_meas_Ampere = {0};
float omega_el_rad_per_sec = 0.0f;
void setUp(void)
{
    config.Ld_Henry = 0.00027f;
    config.Lq_Henry = 0.00027f;
    config.Psi_PM_Vs = 0.0082f;
    i_dq_meas_Ampere.d = 0.0f;
    i_dq_meas_Ampere.q = 0.0f;
    i_dq_meas_Ampere.zero = 0.0f;
    omega_el_rad_per_sec = 0.0f;
}

void test_uz_FOC_linear_decoupling_output_positive_omega(void){
    setUp();
	//Values for comparision from simulation
	omega_el_rad_per_sec = 714.0f;
	i_dq_meas_Ampere.q = 1.0f;
	i_dq_meas_Ampere.d = 1.0f;
	struct uz_dq_t output = uz_FOC_linear_decoupling(config, i_dq_meas_Ampere, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, -0.19f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 6.05f,output.q);
}

void test_uz_FOC_linear_decoupling_output_negative_omega(void){
    setUp();
	//Values for comparision from simulation
	omega_el_rad_per_sec = -714.0f;
	i_dq_meas_Ampere.q = 1.0f;
	i_dq_meas_Ampere.d = 1.0f;
	struct uz_dq_t output = uz_FOC_linear_decoupling(config, i_dq_meas_Ampere, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 0.19f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, -6.05f,output.q);
}

void test_uz_FOC_linear_decoupling_output_zero(void){
    setUp();
	//Values for comparision from simulation
	omega_el_rad_per_sec = 0.0f;
	i_dq_meas_Ampere.q = 1.0f;
	i_dq_meas_Ampere.d = 1.0f;
	struct uz_dq_t output = uz_FOC_linear_decoupling(config, i_dq_meas_Ampere, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.0f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.0f,output.q);
}
#endif // TEST
