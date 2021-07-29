#ifdef TEST

#include "unity.h"
TEST_FILE("uz_signals.c")
#include "uz_Transformation.h"
#include "test_assert_with_exception.h"
#include "uz_space_vector_limitation.h"

struct uz_dq_t u_dq_ref_Volts = {0};
struct uz_dq_t i_dq_meas_Ampere = {0};
float U_zk_Volts = 0.0f;
float omega_el_rad_per_sec = 0.0f;
bool ext_clamping = false;
void setUp(void)
{
    u_dq_ref_Volts.d = 0.0f;
    u_dq_ref_Volts.q = 0.0f;
    u_dq_ref_Volts.zero = 0.0f;
    i_dq_meas_Ampere.d = 0.0f;
    i_dq_meas_Ampere.q = 0.0f;
    i_dq_meas_Ampere.zero = 0.0f;
    U_zk_Volts = 24.0f;
    omega_el_rad_per_sec = 100.0f;
    ext_clamping = false;
}

void test_uz_FOC_SpaceVector_Limitation_ext_clamping_NULL(void){
    setUp();
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts,U_zk_Volts, omega_el_rad_per_sec, i_dq_meas_Ampere, NULL));
}

void test_uz_FOC_SpaceVector_Limitation_U_zk_negative(void){
    setUp();
    U_zk_Volts = -5.2f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts,U_zk_Volts, omega_el_rad_per_sec, i_dq_meas_Ampere, &ext_clamping));
}

void test_uz_FOC_SpaceVector_Limitation_U_zk_zero(void){
    setUp();
    U_zk_Volts = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts,U_zk_Volts, omega_el_rad_per_sec, i_dq_meas_Ampere, &ext_clamping));
}

void test_uz_FOC_SpaceVector_Limitation_output(void){
    setUp();
    //Values for comparision from simulation
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_omega[11]={0.0f, 0.0f, 0.0f, 0.0f, 0.0121f, 0.0402f, 0.0861f, 0.149f, 0.227f, 0.315f, 0.408f};
    float ud_in[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.46f};
    float uq_in[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.46f};
    float uq_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f}; 
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        omega_el_rad_per_sec = values_omega[i];
        u_dq_ref_Volts.d = ud_in[i];
        u_dq_ref_Volts.q = uq_in[i];
        struct uz_dq_t output = uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts,U_zk_Volts, omega_el_rad_per_sec, i_dq_meas_Ampere, &ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}

void test_uz_FOC_SpaceVector_Limitation_output_transition_to_limit(void){
    setUp();
    //Values for comparision from simulation
    U_zk_Volts = 12.0f;
    float values_iq[11]={1.7f, 1.7f, 1.7f, 1.7f, 1.7f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_omega[11]={825.67f, 825.69f, 825.72f, 825.735f, 825.75f,825.765f, 825.78f, 825.8f, 825.82f, 825.84f, 825.851f};
    float ud_in[11]={-0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f,-0.436f, -0.436f, -0.436f, -0.436f, -0.436f};
    float uq_in[11]={6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.92f};
    float ud_out[11]={-0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f};
    float uq_out[11]={6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f}; 
    float output_ref[11]={false, false, false, false, false, false, false, false, false, false, true};
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        omega_el_rad_per_sec = values_omega[i];
        u_dq_ref_Volts.d = ud_in[i];
        u_dq_ref_Volts.q = uq_in[i];
        struct uz_dq_t output = uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts,U_zk_Volts, omega_el_rad_per_sec, i_dq_meas_Ampere, &ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
        TEST_ASSERT_EQUAL_INT(output_ref[i], ext_clamping);
    }
}

void test_uz_FOC_SpaceVector_Limitation_output_limited(void){
    setUp();
    //Values for comparision from simulation
    U_zk_Volts = 12.0f;
    float values_iq[11]={1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f};
	float values_omega[11]={833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f};
    float ud_in[11]={-0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f,-0.294f, -0.294f, -0.294f, -0.294f, -0.294f};
    float uq_in[11]={11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f};
    float ud_out[11]={-0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f};
    float uq_out[11]={6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f}; 
    float output_ref[11]={true, true, true, true, true, true, true, true, true, true, true};
    for(int i=0;i<11;i++){
        i_dq_meas_Ampere.q = values_iq[i];
        omega_el_rad_per_sec = values_omega[i];
        u_dq_ref_Volts.d = ud_in[i];
        u_dq_ref_Volts.q = uq_in[i];
        struct uz_dq_t output = uz_FOC_SpaceVector_Limitation(u_dq_ref_Volts,U_zk_Volts, omega_el_rad_per_sec, i_dq_meas_Ampere, &ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
        TEST_ASSERT_EQUAL_INT(output_ref[i], ext_clamping);
    }
}

#endif // TEST
