#ifdef TEST

#include "unity.h"
#include "../uz_signals/uz_signals.h"
#include "uz_Transformation.h"
#include "test_assert_with_exception.h"
#include "uz_space_vector_limitation.h"

uz_3ph_dq_t v_input_Volts = {0};
uz_3ph_dq_t i_actual_Ampere = {0};
uz_6ph_dq_t v_input_6ph_Volts = {0};
uz_6ph_dq_t i_actual_6ph_Ampere = {0};
float V_dc_volts = 0.0f;
float omega_el_rad_per_sec = 0.0f;
bool ext_clamping = false;
float max_modulation_index = 0.0f;
void setUp(void)
{
    v_input_Volts.d = 0.0f;
    v_input_Volts.q = 0.0f;
    v_input_Volts.zero = 0.0f;
    i_actual_Ampere.d = 0.0f;
    i_actual_Ampere.q = 0.0f;
    i_actual_Ampere.zero = 0.0f;
    V_dc_volts = 24.0f;
    omega_el_rad_per_sec = 100.0f;
    ext_clamping = false;
    max_modulation_index = 1.0f / sqrtf(3.0f);
}

void test_uz_CurrentControl_SpaceVector_Limitation_ext_clamping_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, NULL));
}

void test_uz_CurrentControl_SpaceVector_Limitation_V_dc_negative(void){
    V_dc_volts = -5.2f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping));
}

void test_uz_CurrentControl_SpaceVector_Limitation_V_dc_zero(void){
    V_dc_volts = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping));
}

void test_uz_CurrentControl_SpaceVector_Limitation_output(void){
    //Values for comparision from simulation
    float values_iq[11]={0.0f, 0.249f, 0.436f, 0.577f, 0.682f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_omega[11]={0.0f, 0.0f, 0.0f, 0.0f, 0.0121f, 0.0402f, 0.0861f, 0.149f, 0.227f, 0.315f, 0.408f};
    float ud_in[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.46f};
    float uq_in[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f};
    float ud_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.46f};
    float uq_out[11]={6.75f, 5.09f, 3.84f, 2.9f, 2.2f, 1.67f, 1.28f, 0.98f, 0.76f, 0.59f, 0.47f}; 
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        omega_el_rad_per_sec = values_omega[i];
        v_input_Volts.d = ud_in[i];
        v_input_Volts.q = uq_in[i];
        uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
    }
}

void test_uz_CurrentControl_SpaceVector_Limitation_output_transition_to_limit(void){
    //Values for comparision from simulation
    V_dc_volts = 12.0f;
    float values_iq[11]={1.7f, 1.7f, 1.7f, 1.7f, 1.7f, 0.761f, 0.82f, 0.865f, 0.898f, 0.923f, 0.942f};
	float values_omega[11]={825.67f, 825.69f, 825.72f, 825.735f, 825.75f,825.765f, 825.78f, 825.8f, 825.82f, 825.84f, 825.851f};
    float ud_in[11]={-0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f,-0.436f, -0.436f, -0.436f, -0.436f, -0.436f};
    float uq_in[11]={6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.92f};
    float ud_out[11]={-0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f, -0.436f};
    float uq_out[11]={6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f, 6.91f}; 
    float output_ref[11]={false, false, false, false, false, false, false, false, false, false, true};
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        omega_el_rad_per_sec = values_omega[i];
        v_input_Volts.d = ud_in[i];
        v_input_Volts.q = uq_in[i];
        uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
        TEST_ASSERT_EQUAL_INT(output_ref[i], ext_clamping);
    }
}

void test_uz_CurrentControl_SpaceVector_Limitation_output_limited(void){
    //Values for comparision from simulation
    V_dc_volts = 12.0f;
    float values_iq[11]={1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f, 1.05f};
	float values_omega[11]={833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f, 833.0f};
    float ud_in[11]={-0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f,-0.294f, -0.294f, -0.294f, -0.294f, -0.294f};
    float uq_in[11]={11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f, 11.4f};
    float ud_out[11]={-0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f, -0.294f};
    float uq_out[11]={6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f, 6.92f}; 
    float output_ref[11]={true, true, true, true, true, true, true, true, true, true, true};
    for(int i=0;i<11;i++){
        i_actual_Ampere.q = values_iq[i];
        omega_el_rad_per_sec = values_omega[i];
        v_input_Volts.d = ud_in[i];
        v_input_Volts.q = uq_in[i];
        uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-03, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
        TEST_ASSERT_EQUAL_INT(output_ref[i], ext_clamping);
    }
}

void test_uz_CurrentControl_SpaceVector_Limitation_max_modulation_index_negative(void){
    max_modulation_index = -5.2f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping));
}

void test_uz_CurrentControl_SpaceVector_Limitation_max_modulation_index_zero(void){
    max_modulation_index = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping));
}

void test_uz_CurrentControl_SpaceVector_Limitation_very_low_V_dc_d_axis_prio(void){
    //Tests, that the function still works, if very low values for V_dc are used and the d-axis is prioritized
    //Values for comparision manually calculated
    V_dc_volts = 0.2f;
    i_actual_Ampere.q = 2.0f;
    i_actual_Ampere.d = 1.0f;
    omega_el_rad_per_sec = 100.0f;
    v_input_Volts.d = 5.0f;
    v_input_Volts.q = 8.0f;
    uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.1096966, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.0360555f, output.q);
}

void test_uz_CurrentControl_SpaceVector_Limitation_very_low_V_dc_q_axis_prio(void){
    //Tests, that the function still works, if very low values for V_dc are used and the q-axis is prioritized
    //Values for comparision manually calculated
    V_dc_volts = 0.2f;
    i_actual_Ampere.q = 2.0f;
    i_actual_Ampere.d = 1.0f;
    omega_el_rad_per_sec = -100.0f;
    v_input_Volts.d = 5.0f;
    v_input_Volts.q = 8.0f;
    uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.0360555f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.1096966f, output.q);
}

void test_uz_CurrentControl_SpaceVector_Limitation_very_low_V_dc_d_axis_prio_95(void){
    //Tests, that the function still works, if very low values for V_dc are used and the d-axis is prioritized and the prioritized
    //voltage is lower than 95% of U_SV_max
    //Values for comparision manually calculated
    V_dc_volts = 0.2f;
    i_actual_Ampere.q = 2.0f;
    i_actual_Ampere.d = 1.0f;
    omega_el_rad_per_sec = 100.0f;
    v_input_Volts.d = 0.1f;
    v_input_Volts.q = 8.0f;
    uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.1, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.057735f, output.q);
}

void test_uz_CurrentControl_SpaceVector_Limitation_very_low_V_dc_q_axis_prio_95(void){
    //Tests, that the function still works, if very low values for V_dc are used and the q-axis is prioritized and the prioritized
    //voltage is lower than 95% of U_SV_max
    //Values for comparision manually calculated
    V_dc_volts = 0.2f;
    i_actual_Ampere.q = 2.0f;
    i_actual_Ampere.d = 1.0f;
    omega_el_rad_per_sec = -100.0f;
    v_input_Volts.d = 5.0f;
    v_input_Volts.q = 0.1f;
    uz_3ph_dq_t output = uz_CurrentControl_SpaceVector_Limitation(v_input_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_Ampere, &ext_clamping);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.057735f, output.d);
	TEST_ASSERT_FLOAT_WITHIN(1e-05, 0.1, output.q);
}

void test_uz_6ph_Space_Vector_Limitation_ext_clamping_NULL(void){
    TEST_ASSERT_FAIL_ASSERT(uz_6ph_Space_Vector_Limitation(v_input_6ph_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_6ph_Ampere, NULL));
}

void test_uz_6ph_Space_Vector_Limitation_V_dc_negative(void){
    V_dc_volts = -5.2f;
    TEST_ASSERT_FAIL_ASSERT(uz_6ph_Space_Vector_Limitation(v_input_6ph_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_6ph_Ampere, &ext_clamping));
}

void test_uz_6ph_Space_Vector_Limitation_V_dc_zero(void){
    V_dc_volts = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_6ph_Space_Vector_Limitation(v_input_6ph_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_6ph_Ampere, &ext_clamping));
}

void test_uz_6ph_Space_Vector_Limitation_output(void){
    //Values for comparision from simulation
    float ud_in[5]={0.0f, -0.316f, -0.616f, -0.817f, -0.930f};
    float uq_in[5]={0.0f, 0.333f, 0.682f, 0.918f, 1.033f};
    float ux_in[5]={0.0f, 0.300f, 0.592f, 0.785f, 0.886f};
    float uy_in[5]={0.0f, 0.313f, 0.645f, 0.896f, 1.049f};
    float ud_out[5]={0.0f, -0.316f, -0.616f, -0.817f, -0.930f};
    float uq_out[5]={0.0f, 0.333f, 0.682f, 0.918f, 1.033f};
    float ux_out[5]={0.0f, 0.300f, 0.592f, 0.785f, 0.886f};
    float uy_out[5]={0.0f, 0.313f, 0.645f, 0.896f, 1.049f};
    max_modulation_index = 0.5f;
    for(int i=0;i<5;i++){
        i_actual_6ph_Ampere.q = 1.0f;
        omega_el_rad_per_sec = 523.598f;
        v_input_6ph_Volts.d = ud_in[i];
        v_input_6ph_Volts.q = uq_in[i];
        v_input_6ph_Volts.x = ux_in[i];
        v_input_6ph_Volts.y = uy_in[i];
        uz_6ph_dq_t output = uz_6ph_Space_Vector_Limitation(v_input_6ph_Volts,V_dc_volts, max_modulation_index, omega_el_rad_per_sec, i_actual_6ph_Ampere, &ext_clamping);
		TEST_ASSERT_FLOAT_WITHIN(1e-02, ud_out[i], output.d);
	    TEST_ASSERT_FLOAT_WITHIN(1e-02, uq_out[i], output.q);
        TEST_ASSERT_FLOAT_WITHIN(1e-02, ux_out[i], output.x);
        TEST_ASSERT_FLOAT_WITHIN(1e-02, uy_out[i], output.y);
    }
}


#endif // TEST
