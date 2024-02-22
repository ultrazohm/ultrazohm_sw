#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_static_nonlinear_decoupling.h"

uz_3ph_dq_t flux_approx = {0};
float omega_el_rad_per_sec = 0.0f;
void setUp(void)
{
    flux_approx.d = 0.0f;
    flux_approx.q = 0.0f;
    flux_approx.zero = 0.0f;
    omega_el_rad_per_sec = 0.0f;
}

void test_uz_CurrentControl_static_nonlinear_decoupling_output_positive_omega(void){
	//Values for comparision from simulation
	omega_el_rad_per_sec = 714.0f;
    flux_approx.d = 0.0145f;
	flux_approx.q = 0.0050f;
	uz_3ph_dq_t output = uz_CurrentControl_static_nonlinear_decoupling(flux_approx, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, -3.57f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 10.353f,output.q);
}

void test_uz_CurrentControl_static_nonlinear_decoupling_output_negative_omega(void){
	//Values for comparision from simulation
	omega_el_rad_per_sec = -714.0f;
	flux_approx.d = 0.0145f;
	flux_approx.q = 0.0050f;
	uz_3ph_dq_t output = uz_CurrentControl_static_nonlinear_decoupling(flux_approx, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, 3.57f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-02, -10.353f,output.q);
}

void test_uz_CurrentControl_static_nonlinear_decoupling_output_zero(void){
	//Values for comparision from simulation
	omega_el_rad_per_sec = 0.0f;
	flux_approx.d = 0.0145f;
	flux_approx.q = 0.0050f;
	uz_3ph_dq_t output = uz_CurrentControl_static_nonlinear_decoupling(flux_approx, omega_el_rad_per_sec);
	TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.0f,output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-04, 0.0f,output.q);
}
#endif // TEST
