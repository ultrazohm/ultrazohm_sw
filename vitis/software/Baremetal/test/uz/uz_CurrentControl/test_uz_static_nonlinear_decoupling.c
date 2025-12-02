#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_static_nonlinear_decoupling.h"

float omega_el_rad_per_sec = 0.0f;
uz_3ph_dq_t flux_approx = {0};
void setUp(void)
{
    flux_approx.d = 0.0f;
	flux_approx.q = 0.0f;
    omega_el_rad_per_sec = 0.0f;
}

void test_uz_CurrentControl_static_nonlinear_decoupling_output_positive_omega(void){
	//Values for comparision from simulation
	omega_el_rad_per_sec = 714.0f;
	flux_approx.d = 0.016f;
	flux_approx.q = 0.010f;
	uz_3ph_dq_t output = uz_CurrentControl_static_nonlinear_decoupling(flux_approx, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, -7.140f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, 11.424f,output.q);
}

void test_uz_CurrentControl_static_nonlinear_decoupling_output_negative_omega(void){
	//Values for comparision from simulation
	omega_el_rad_per_sec = -714.0f;
	flux_approx.d = 0.016f;
	flux_approx.q = 0.010f;
	uz_3ph_dq_t output = uz_CurrentControl_static_nonlinear_decoupling(flux_approx, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, 7.140f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-03, -11.424f,output.q);
}

void test_uz_CurrentControl_static_nonlinear_decoupling_output_zero(void){
	//Values for comparision from simulation
	omega_el_rad_per_sec = 0.0f;
	flux_approx.d = 0.016f;
	flux_approx.q = 0.010f;
	uz_3ph_dq_t output = uz_CurrentControl_static_nonlinear_decoupling(flux_approx, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.0f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.0f,output.q);
}
#endif // TEST
