#ifdef TEST

#include "unity.h"
#include "uz_pmsm_model3ph_dq_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_pmsm_model3ph_dq_hwAddresses.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsm_model3ph_hw_read_torque(void)
{
    float torque_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+torque_Data_uz_pmsm_model3ph,torque_expect);
    float torque_read=uz_pmsm_model3ph_hw_read_torque(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect,torque_read);
}

void test_uz_pmsm_model3ph_hw_read_i_q(void)
{
    float i_q_val=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_q_Data_uz_pmsm_model3ph,i_q_val);
    float readback=uz_pmsm_model3ph_hw_read_i_q(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(i_q_val,readback);
}

void test_uz_pmsm_model3ph_hw_read_i_d(void){
    float i_d_val=13.1f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_d_Data_uz_pmsm_model3ph,i_d_val);
    float readback=uz_pmsm_model3ph_hw_read_i_d(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(i_d_val,readback);
}

void test_uz_pmsm_model3ph_hw_read_theta_el(void){
    float theta_el=13.1f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+theta_el_Data_uz_pmsm_model3ph,theta_el);
    float readback=uz_pmsm_model3ph_hw_read_theta_el(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(theta_el,readback);
}

void test_uz_pmsm_model3ph_hw_write_reset(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+reset_integrators_Data_uz_pmsm_model3ph,true);
    uz_pmsm_model3ph_hw_write_reset(BASE_ADDRESS,true);
}

void test_uz_pmsm_model3ph_hw_write_omega_mech(void){
    float omega_mech=123.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+in_omega_mech_Data_uz_pmsm_model3ph,omega_mech);
    uz_pmsm_model3ph_hw_write_omega_mech(BASE_ADDRESS,omega_mech);
}

void test_uz_pmsm_model3ph_hw_write_v_q(void){
    float v_q_expect=123.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS + v_q_Data_uz_pmsm_model3ph,v_q_expect);
    uz_pmsm_model3ph_hw_write_v_q(BASE_ADDRESS,v_q_expect);
}

void test_uz_pmsm_model3ph_hw_write_v_d(void){
    float v_d_expect=-3.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS + v_d_Data_uz_pmsm_model3ph,v_d_expect);
    uz_pmsm_model3ph_hw_write_v_d(BASE_ADDRESS,v_d_expect);
}

void test_uz_pmsm_model3ph_hw_write_friction_coefficient(void){
    float mu=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+mu_Data_uz_pmsm_model3ph,mu);
    uz_pmsm_model3ph_hw_write_friction_coefficient(BASE_ADDRESS,mu);
}

void test_uz_pmsm_model3ph_hw_write_coulomb_friction(void){
    float m_c=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+M_n0_Data_uz_pmsm_model3ph,m_c);
    uz_pmsm_model3ph_hw_write_coulomb_friction_constant(BASE_ADDRESS,m_c);
}

void test_uz_pmsm_model3ph_hw_write_r1(void){
    float r_1=11.2f;
    uz_axi_write_float_Expect(BASE_ADDRESS+R1_Data_uz_pmsm_model3ph,r_1);
    uz_pmsm_model3ph_hw_write_r_1(BASE_ADDRESS,r_1);
}

void test_uz_pmsm_model3ph_hw_write_poleparis(void){
    float polepairs=3.0f;
    uz_axi_write_float_Expect(BASE_ADDRESS+polepairs_Data_uz_pmsm_model3ph,polepairs);
    uz_pmsm_model3ph_hw_write_polepairs(BASE_ADDRESS,polepairs);
}

void test_uz_pmsm_model3ph_hw_write_psi_pm(void){
    float psi_pm=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+psi_pm_Data_uz_pmsm_model3ph,psi_pm);
    uz_pmsm_model3ph_hw_write_psi_pm(BASE_ADDRESS,psi_pm);
}

void test_uz_pmsm_model3ph_hw_write_L_d(void){
    float L_d=0.003f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_L_d_Data_uz_pmsm_model3ph,1.0f/L_d);
    uz_pmsm_model3ph_hw_write_L_d(BASE_ADDRESS,L_d);
}

void test_uz_pmsm_model3ph_hw_write_L_q(void){
    float L_q=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_L_q_Data_uz_pmsm_model3ph,1.0f/L_q);
    uz_pmsm_model3ph_hw_write_L_q(BASE_ADDRESS,L_q);
}

void test_uz_pmsm_model3ph_hw_read_omega_mech(void){
    float omega_mech_expected=100.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+out_omega_mech_Data_uz_pmsm_model3ph,omega_mech_expected);
    float omega_mech=uz_pmsm_model3ph_hw_read_omega_mech(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expected,omega_mech);
}

void test_uz_pmsm_model3ph_hw_write_simulate_mechanical(void){
    _Bool simulate_mech=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+simulate_mechanical_Data_uz_pmsm_model3ph,simulate_mech);
    uz_pmsm_model3ph_hw_write_simulate_mechanical(BASE_ADDRESS,simulate_mech);
}

void test_uz_pmsm_model3ph_hw_write_inertia(void){
    float inertia=0.00031f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_J_Data_uz_pmsm_model3ph,1.0f/inertia);
    uz_pmsm_model3ph_hw_write_inertia(BASE_ADDRESS,inertia);
}

void test_uz_pmsm_model3ph_hw_write_load_torque(void){
    float load_torque=10.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+load_torque_Data_uz_pmsm_model3ph,load_torque);
    uz_pmsm_model3ph_hw_write_load_torque(BASE_ADDRESS,load_torque);
}

void test_uz_pmsm_model3ph_hw_write_switch_pspl(void){
    bool switch_pspl=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS + use_axi_input_Data_uz_pmsm_model3ph,switch_pspl);
    uz_pmsm_model3ph_hw_write_switch_pspl(BASE_ADDRESS,switch_pspl);
}

void test_uz_pmsm_model3ph_hw_trigger_input_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+inputs_Strobe_uz_pmsm_model3ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+inputs_Strobe_uz_pmsm_model3ph,false);
    uz_pmsm_model3ph_hw_trigger_input_strobe(BASE_ADDRESS);
}

void test_uz_pmsm_model3ph_hw_trigger_output_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+outputs_Strobe_uz_pmsm_model3ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+outputs_Strobe_uz_pmsm_model3ph,false);
    uz_pmsm_model3ph_hw_trigger_output_strobe(BASE_ADDRESS);
}

void test_uz_pmsm_model3ph_hw_trigger_fb_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model3ph,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Strobe_uz_pmsm_model3ph,false);
    uz_pmsm_model3ph_hw_trigger_fb_strobe(BASE_ADDRESS);
}

void test_uz_pmsm_model3ph_hw_read_v_d(void){
    float testvolt=13.1f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model3ph,testvolt);
    float readback=uz_pmsm_model3ph_hw_read_v_d(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(testvolt,readback);
}

void test_uz_pmsm_model3ph_hw_read_v_q(void){
    float testvolt=13.1f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+voltage_input_dq_out_axi_fb_Data_uz_pmsm_model3ph+0x04,testvolt);
    float readback=uz_pmsm_model3ph_hw_read_v_q(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(testvolt,readback);
}

#endif // TEST
