#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_pmsm_model9ph_dq_addr.h"
#include "uz_pmsm_model9ph_dq_hw.h"

#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

// Model settings
void test_uz_pmsm_model9ph_hw_write_reset(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+reset_integrators_Data_uz_pmsm_model_9ph_dq,true);
    uz_pmsm_model9ph_hw_write_reset(BASE_ADDRESS,true);
}

void test_uz_pmsm_model9ph_hw_write_simulate_mechanical(void){
    _Bool simulate_mech=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+simulate_mechanical_Data_uz_pmsm_model_9ph_dq,simulate_mech);
    uz_pmsm_model9ph_hw_write_simulate_mechanical(BASE_ADDRESS,simulate_mech);
}

void test_uz_pmsm_model9ph_hw_write_switch_pspl(void){
    _Bool switch_pspl=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+use_axi_input_Data_uz_pmsm_model_9ph_dq,switch_pspl);
    uz_pmsm_model9ph_hw_write_switch_pspl(BASE_ADDRESS,switch_pspl);
}

// General inputs
void test_uz_pmsm_model9ph_hw_write_load_torque(void){
    float load_torque=10.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+load_torque_Data_uz_pmsm_model_9ph_dq,load_torque);
    uz_pmsm_model9ph_hw_write_load_torque(BASE_ADDRESS,load_torque);
}

void test_uz_pmsm_model9ph_hw_write_omega_mech(void){
    float omega_mech=123.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+omega_mech_Data_uz_pmsm_model_9ph_dq,omega_mech);
    uz_pmsm_model9ph_hw_write_omega_mech(BASE_ADDRESS,omega_mech);
}

// General outputs
void test_uz_pmsm_model9ph_hw_read_torque(void)
{
    float torque_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+M_Mi_out_axi_Data_uz_pmsm_model_9ph_dq,torque_expect);
    float torque_read=uz_pmsm_model9ph_hw_read_torque(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect,torque_read);
}

void test_uz_pmsm_model9ph_hw_read_omega_mech(void){
    float omega_mech_expected=100.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+omega_mech_out_axi_Data_uz_pmsm_model_9ph_dq,omega_mech_expected);
    float omega_mech=uz_pmsm_model9ph_hw_read_omega_mech(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expected,omega_mech);
}

void test_uz_pmsm_model9ph_hw_read_theta_el(void){
    float theta_el_expected=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+theta_el_out_axi_Data_uz_pmsm_model_9ph_dq,theta_el_expected);
    float theta_el=uz_pmsm_model9ph_hw_read_theta_el(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(theta_el_expected,theta_el);
}

// Voltage input
void test_uz_pmsm_model9ph_hw_write_u_d(void){
    float voltage=0.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x00,voltage);
    uz_pmsm_model9ph_hw_write_u_d(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_q(void){
    float voltage=0.2f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x04,voltage);
    uz_pmsm_model9ph_hw_write_u_q(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_x1(void){
    float voltage=0.3f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x08,voltage);
    uz_pmsm_model9ph_hw_write_u_x1(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_y1(void){
    float voltage=0.14f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x0C,voltage);
    uz_pmsm_model9ph_hw_write_u_y1(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_x2(void){
    float voltage=0.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x10,voltage);
    uz_pmsm_model9ph_hw_write_u_x2(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_y2(void){
    float voltage=0.16f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x14,voltage);
    uz_pmsm_model9ph_hw_write_u_y2(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_x3(void){
    float voltage=0.17f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x18,voltage);
    uz_pmsm_model9ph_hw_write_u_x3(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_y3(void){
    float voltage=0.18f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x1C,voltage);
    uz_pmsm_model9ph_hw_write_u_y3(BASE_ADDRESS,voltage);
}
void test_uz_pmsm_model9ph_hw_write_u_zero(void){
    float voltage=0.19f;
    uz_axi_write_float_Expect(BASE_ADDRESS+voltage_input_dq_axi_Data_uz_pmsm_model_9ph_dq+0x20,voltage);
    uz_pmsm_model9ph_hw_write_u_zero(BASE_ADDRESS,voltage);
}

// Voltage output
void test_uz_pmsm_model9ph_hw_read_u_d(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x00,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_d(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_q(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x04,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_q(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_x1(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x08,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_x1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_y1(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x0C,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_y1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_x2(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x10,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_x2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_y2(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x14,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_y2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_x3(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x18,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_x3(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_y3(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x1C,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_y3(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}
void test_uz_pmsm_model9ph_hw_read_u_zero(void){
    float voltage_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model_9ph_dq+0x20,voltage_expect);
    float voltage_read=uz_pmsm_model9ph_hw_read_u_zero(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(voltage_expect,voltage_read);
}

// Current output
void test_uz_pmsm_model9ph_hw_read_i_d(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x00,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_d(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_q(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x04,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_q(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_x1(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x08,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_x1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_y1(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x0C,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_y1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_x2(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x10,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_x2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_y2(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x14,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_y2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_x3(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x18,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_x3(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_y3(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x1C,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_y3(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}
void test_uz_pmsm_model9ph_hw_read_i_zero(void){
    float current_expect=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+currents_dq_out_axi_Data_uz_pmsm_model_9ph_dq+0x20,current_expect);
    float current_read=uz_pmsm_model9ph_hw_read_i_zero(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(current_expect,current_read);
}

// Parameters
void test_uz_pmsm_model9ph_hw_write_inertia(void){
    float inertia=0.00031f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_1_J_Data_uz_pmsm_model_9ph_dq,1.0f/inertia);
    uz_pmsm_model9ph_hw_write_inertia(BASE_ADDRESS,inertia);
}
void test_uz_pmsm_model9ph_hw_write_friction_coefficient(void){
    float mu=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_mu_Data_uz_pmsm_model_9ph_dq,mu);
    uz_pmsm_model9ph_hw_write_friction_coefficient(BASE_ADDRESS,mu);
}
void test_uz_pmsm_model9ph_hw_write_coulomb_friction(void){
    float m_c=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_M_R0_Data_uz_pmsm_model_9ph_dq,m_c);
    uz_pmsm_model9ph_hw_write_coulomb_friction_constant(BASE_ADDRESS,m_c);
}
void test_uz_pmsm_model9ph_hw_write_L_d(void){
    float L_d=0.003f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_1_L_d_Data_uz_pmsm_model_9ph_dq,1.0f/L_d);
    uz_pmsm_model9ph_hw_write_L_d(BASE_ADDRESS,L_d);
}
void test_uz_pmsm_model9ph_hw_write_L_q(void){
    float L_q=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_1_L_q_Data_uz_pmsm_model_9ph_dq,1.0f/L_q);
    uz_pmsm_model9ph_hw_write_L_q(BASE_ADDRESS,L_q);
}
void test_uz_pmsm_model9ph_hw_write_r1(void){
    float r_1=11.2f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_R_1_Data_uz_pmsm_model_9ph_dq,r_1);
    uz_pmsm_model9ph_hw_write_r_1(BASE_ADDRESS,r_1);
}
void test_uz_pmsm_model9ph_hw_write_poleparis(void){
    float polepairs=3.0f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_polepair_Data_uz_pmsm_model_9ph_dq,polepairs);
    uz_pmsm_model9ph_hw_write_polepairs(BASE_ADDRESS,polepairs);
}
void test_uz_pmsm_model9ph_hw_write_psi_pm(void){
    float psi_pm=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_psi_pm_Data_uz_pmsm_model_9ph_dq,psi_pm);
    uz_pmsm_model9ph_hw_write_psi_pm(BASE_ADDRESS,psi_pm);
}
void test_uz_pmsm_model9ph_hw_write_L_x1(void){
    float L_test=10.2f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_L_x1_Data_uz_pmsm_model_9ph_dq,1.0f/L_test);
    uz_pmsm_model9ph_hw_write_L_x1(BASE_ADDRESS,L_test);
}
void test_uz_pmsm_model9ph_hw_write_L_y1(void){
    float L_test=10.3f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_L_y1_Data_uz_pmsm_model_9ph_dq,1.0f/L_test);
    uz_pmsm_model9ph_hw_write_L_y1(BASE_ADDRESS,L_test);
}
void test_uz_pmsm_model9ph_hw_write_L_x2(void){
    float L_test=10.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_L_x2_Data_uz_pmsm_model_9ph_dq,1.0f/L_test);
    uz_pmsm_model9ph_hw_write_L_x2(BASE_ADDRESS,L_test);
}
void test_uz_pmsm_model9ph_hw_write_L_y2(void){
    float L_test=10.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_L_y2_Data_uz_pmsm_model_9ph_dq,1.0f/L_test);
    uz_pmsm_model9ph_hw_write_L_y2(BASE_ADDRESS,L_test);
}
void test_uz_pmsm_model9ph_hw_write_L_x3(void){
    float L_test=10.6f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_L_x3_Data_uz_pmsm_model_9ph_dq,1.0f/L_test);
    uz_pmsm_model9ph_hw_write_L_x3(BASE_ADDRESS,L_test);
}
void test_uz_pmsm_model9ph_hw_write_L_y3(void){
    float L_test=10.7f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_L_y3_Data_uz_pmsm_model_9ph_dq,1.0f/L_test);
    uz_pmsm_model9ph_hw_write_L_y3(BASE_ADDRESS,L_test);
}
void test_uz_pmsm_model9ph_hw_write_L_zero(void){
    float L_test=10.8f;
    uz_axi_write_float_Expect(BASE_ADDRESS+physical_parameters_L_zero_Data_uz_pmsm_model_9ph_dq,1.0f/L_test);
    uz_pmsm_model9ph_hw_write_L_zero(BASE_ADDRESS,L_test);
}
// Strobe
void test_uz_pmsm_model9ph_trigger_voltage_input_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+voltage_input_dq_axi_Strobe_uz_pmsm_model_9ph_dq,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+voltage_input_dq_axi_Strobe_uz_pmsm_model_9ph_dq,false);
    uz_pmsm_model9ph_trigger_voltage_input_strobe(BASE_ADDRESS);
}
void test_uz_pmsm_model9ph_trigger_voltage_output_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_9ph_dq,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model_9ph_dq,false);
    uz_pmsm_model9ph_trigger_voltage_output_strobe(BASE_ADDRESS);
}
void test_uz_pmsm_model9ph_trigger_current_output_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+currents_dq_out_axi_Strobe_uz_pmsm_model_9ph_dq,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+currents_dq_out_axi_Strobe_uz_pmsm_model_9ph_dq,false);
    uz_pmsm_model9ph_trigger_current_output_strobe(BASE_ADDRESS);
}

#endif // TEST
