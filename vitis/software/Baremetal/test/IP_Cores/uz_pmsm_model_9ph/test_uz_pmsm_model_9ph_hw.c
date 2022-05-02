#ifdef TEST

#include "unity.h"
#include "uz_pmsm_model_9ph_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_pmsm_model_9ph_hwaddr.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

// Outputs general
void test_uz_pmsm_model_9ph_hw_read_torque(void)
{
    float torque_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+torque_Data_uz_pmsm_model_9ph,torque_expect);
    float torque_read=uz_pmsm_model_9ph_hw_read_torque(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect,torque_read);
}

void test_uz_pmsm_model_9ph_hw_read_omega_mech(void){
    float omega_mech_expected=100.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+out_omega_mech_Data_uz_pmsm_model_9ph,omega_mech_expected);
    float omega_mech=uz_pmsm_model_9ph_hw_read_omega_mech(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expected,omega_mech);
}

void test_uz_pmsm_model_9ph_hw_read_theta_el(void){
    float theta_el_expected=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+out_theta_el_Data_uz_pmsm_model_9ph,theta_el_expected);
    float theta_el=uz_pmsm_model_9ph_hw_read_theta_el(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(theta_el_expected,theta_el);
}

// Outputs currents dq
void test_uz_pmsm_model_9ph_hw_read_i_d(void){
    float i_d_val=13.1f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_d_Data_uz_pmsm_model_9ph,i_d_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_d(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(i_d_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_q(void)
{
    float i_q_val=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_q_Data_uz_pmsm_model_9ph,i_q_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_q(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(i_q_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_z1(void){
    float test_val=12.3f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_z1_Data_uz_pmsm_model_9ph,test_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_z1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(test_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_z2(void){
    float test_val=23.4f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_z2_Data_uz_pmsm_model_9ph,test_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_z2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(test_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_x1(void){
    float test_val=34.5f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_x1_Data_uz_pmsm_model_9ph,test_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_x1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(test_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_y1(void){
    float test_val=45.6f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_y1_Data_uz_pmsm_model_9ph,test_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_y1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(test_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_x2(void){
    float test_val=54.3f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_x2_Data_uz_pmsm_model_9ph,test_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_x2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(test_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_y2(void){
    float test_val=43.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_y2_Data_uz_pmsm_model_9ph,test_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_y2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(test_val,readback);
}

void test_uz_pmsm_model_9ph_hw_read_i_z3(void){
    float test_val=32.1f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_z3_Data_uz_pmsm_model_9ph,test_val);
    float readback=uz_pmsm_model_9ph_hw_read_i_z3(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(test_val,readback);
}

// Inputs general
void test_uz_pmsm_model_9ph_hw_write_load_torque(void){
    float load_torque=10.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+load_torque_Data_uz_pmsm_model_9ph,load_torque);
    uz_pmsm_model_9ph_hw_write_load_torque(BASE_ADDRESS,load_torque);
}

void test_uz_pmsm_model_9ph_hw_write_omega_mech(void){
    float omega_mech=123.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+in_omega_mech_Data_uz_pmsm_model_9ph,omega_mech);
    uz_pmsm_model_9ph_hw_write_omega_mech(BASE_ADDRESS,omega_mech);
}

// Model parameter
void test_uz_pmsm_model_9ph_hw_write_reset(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+Model_Parameter_reset_integrators_Data_uz_pmsm_model_9ph,true);
    uz_pmsm_model_9ph_hw_write_reset(BASE_ADDRESS,true);
}

void test_uz_pmsm_model_9ph_hw_write_simulate_mechanical(void){
    _Bool simulate_mech=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+Model_Parameter_simulate_mechanical_Data_uz_pmsm_model_9ph,simulate_mech);
    uz_pmsm_model_9ph_hw_write_simulate_mechanical(BASE_ADDRESS,simulate_mech);
}

void test_uz_pmsm_model_9ph_hw_write_switch_pspl(void){
    _Bool switch_pspl=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+Model_Parameter_switch_pspl_Data_uz_pmsm_model_9ph,switch_pspl);
    uz_pmsm_model_9ph_hw_write_switch_pspl(BASE_ADDRESS,switch_pspl);
}

void test_uz_pmsm_model_9ph_hw_write_control_dq_abc(void){
    _Bool control_dq_abc=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+Model_Parameter_control_dq_abc_Data_uz_pmsm_model_9ph,control_dq_abc);
    uz_pmsm_model_9ph_hw_write_control_dq_abc(BASE_ADDRESS,control_dq_abc);
}

// Physical parameter
void test_uz_pmsm_model_9ph_hw_write_inertia(void){
    float inertia=0.00031f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_1_J_Data_uz_pmsm_model_9ph,1.0f/inertia);
    uz_pmsm_model_9ph_hw_write_inertia(BASE_ADDRESS,inertia);
}

void test_uz_pmsm_model_9ph_hw_write_friction_coefficient(void){
    float mu=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_mu_Data_uz_pmsm_model_9ph,mu);
    uz_pmsm_model_9ph_hw_write_friction_coefficient(BASE_ADDRESS,mu);
}

void test_uz_pmsm_model_9ph_hw_write_coulomb_friction(void){
    float m_c=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_M_R0_Data_uz_pmsm_model_9ph,m_c);
    uz_pmsm_model_9ph_hw_write_coulomb_friction_constant(BASE_ADDRESS,m_c);
}

void test_uz_pmsm_model_9ph_hw_write_L_d(void){
    float L_d=0.003f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_reciprocal_L_d_Data_uz_pmsm_model_9ph,1.0f/L_d);
    uz_pmsm_model_9ph_hw_write_L_d(BASE_ADDRESS,L_d);
}

void test_uz_pmsm_model_9ph_hw_write_L_q(void){
    float L_q=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_reciprocal_L_q_Data_uz_pmsm_model_9ph,1.0f/L_q);
    uz_pmsm_model_9ph_hw_write_L_q(BASE_ADDRESS,L_q);
}

void test_uz_pmsm_model_9ph_hw_write_r1(void){
    float r_1=11.2f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_R1_Data_uz_pmsm_model_9ph,r_1);
    uz_pmsm_model_9ph_hw_write_r_1(BASE_ADDRESS,r_1);
}

void test_uz_pmsm_model_9ph_hw_write_poleparis(void){
    float polepairs=3.0f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_polepairs_Data_uz_pmsm_model_9ph,polepairs);
    uz_pmsm_model_9ph_hw_write_polepairs(BASE_ADDRESS,polepairs);
}

void test_uz_pmsm_model_9ph_hw_write_psi_pm(void){
    float psi_pm=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_psi_pm_Data_uz_pmsm_model_9ph,psi_pm);
    uz_pmsm_model_9ph_hw_write_psi_pm(BASE_ADDRESS,psi_pm);
}

void test_uz_pmsm_model_9ph_hw_write_L_z1(void){
    float L_test=10.2f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_L_z1_Data_uz_pmsm_model_9ph,1.0f/L_test);
    uz_pmsm_model_9ph_hw_write_L_z1(BASE_ADDRESS,L_test);
}

void test_uz_pmsm_model_9ph_hw_write_L_z2(void){
    float L_test=10.3f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_L_z2_Data_uz_pmsm_model_9ph,1.0f/L_test);
    uz_pmsm_model_9ph_hw_write_L_z2(BASE_ADDRESS,L_test);
}

void test_uz_pmsm_model_9ph_hw_write_L_x1(void){
    float L_test=10.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_L_x1_Data_uz_pmsm_model_9ph,1.0f/L_test);
    uz_pmsm_model_9ph_hw_write_L_x1(BASE_ADDRESS,L_test);
}

void test_uz_pmsm_model_9ph_hw_write_L_y1(void){
    float L_test=10.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_L_y1_Data_uz_pmsm_model_9ph,1.0f/L_test);
    uz_pmsm_model_9ph_hw_write_L_y1(BASE_ADDRESS,L_test);
}

void test_uz_pmsm_model_9ph_hw_write_L_x2(void){
    float L_test=10.6f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_L_x2_Data_uz_pmsm_model_9ph,1.0f/L_test);
    uz_pmsm_model_9ph_hw_write_L_x2(BASE_ADDRESS,L_test);
}

void test_uz_pmsm_model_9ph_hw_write_L_y2(void){
    float L_test=10.7f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_L_y2_Data_uz_pmsm_model_9ph,1.0f/L_test);
    uz_pmsm_model_9ph_hw_write_L_y2(BASE_ADDRESS,L_test);
}

void test_uz_pmsm_model_9ph_hw_write_L_z3(void){
    float L_test=10.8f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Physical_Parameter_L_z3_Data_uz_pmsm_model_9ph,1.0f/L_test);
    uz_pmsm_model_9ph_hw_write_L_z3(BASE_ADDRESS,L_test);
}

// Strobe
void test_uz_pmsm_model_9ph_hw_trigger_output_general_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+output_general_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+output_general_Strobe_uz_pmsm_model_9ph,false);
    uz_pmsm_model_9ph_hw_trigger_output_general_strobe(BASE_ADDRESS);
}

void test_uz_pmsm_model_9ph_hw_trigger_output_currents_dq_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+output_currents_dq_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+output_currents_dq_Strobe_uz_pmsm_model_9ph,false);
    uz_pmsm_model_9ph_hw_trigger_output_currents_dq_strobe(BASE_ADDRESS);
}

void test_uz_pmsm_model_9ph_hw_trigger_input_general_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+inputs_general_Strobe_uz_pmsm_model_9ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+inputs_general_Strobe_uz_pmsm_model_9ph,false);
    uz_pmsm_model_9ph_hw_trigger_input_general_strobe(BASE_ADDRESS);
}

#endif // TEST