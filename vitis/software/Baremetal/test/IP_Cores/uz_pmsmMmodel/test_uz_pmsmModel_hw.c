#ifdef TEST

#include "unity.h"
#include "uz_pmsmModel_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_pmsmModel_hwAddresses.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsmModel_hw_read_torque(void)
{
    float torque_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+torque_Data_uz_pmsm_model,torque_expect);
    float torque_read=uz_pmsmModel_hw_read_torque(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect,torque_read);
}

void test_uz_pmsmModel_hw_read_i_q(void)
{
    float i_q_val=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_q_Data_uz_pmsm_model,i_q_val);
    float readback=uz_pmsmModel_hw_read_i_q(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(i_q_val,readback);
}

void test_uz_pmsmModel_hw_read_i_d(void){
    float i_d_val=13.1f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+i_d_Data_uz_pmsm_model,i_d_val);
    float readback=uz_pmsmModel_hw_read_i_d(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(i_d_val,readback);
}

void test_uz_pmsmModel_hw_write_reset(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+reset_integrators_Data_uz_pmsm_model,true);
    uz_pmsmModel_hw_write_reset(BASE_ADDRESS,true);
}

void test_uz_pmsmModel_hw_write_omega_mech(void){
    float omega_mech=123.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+in_omega_mech_Data_uz_pmsm_model,omega_mech);
    uz_pmsmModel_hw_write_omega_mech(BASE_ADDRESS,omega_mech);
}

void test_uz_pmsmModel_hw_write_u_q(void){
    float u_q_expect=123.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+u_q_Data_uz_pmsm_model,u_q_expect);
    uz_pmsmModel_hw_write_u_q(BASE_ADDRESS,u_q_expect);
}

void test_uz_pmsmModel_hw_write_u_d(void){
    float u_d_expect=-3.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+u_d_Data_uz_pmsm_model,u_d_expect);
    uz_pmsmModel_hw_write_u_d(BASE_ADDRESS,u_d_expect);
}

void test_uz_pmsmModel_hw_write_friction_coefficient(void){
    float mu=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+mu_Data_uz_pmsm_model,mu);
    uz_pmsmModel_hw_write_friction_coefficient(BASE_ADDRESS,mu);
}

void test_uz_pmsmModel_hw_write_coulomb_friction(void){
    float m_c=1.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS+M_n0_Data_uz_pmsm_model,m_c);
    uz_pmsmModel_hw_write_coulomb_friction_constant(BASE_ADDRESS,m_c);
}

void test_uz_pmsmModel_hw_write_r1(void){
    float r_1=11.2f;
    uz_axi_write_float_Expect(BASE_ADDRESS+R1_Data_uz_pmsm_model,r_1);
    uz_pmsmModel_hw_write_r_1(BASE_ADDRESS,r_1);
}

void test_uz_pmsmModel_hw_write_poleparis(void){
    float polepairs=3.0f;
    uz_axi_write_float_Expect(BASE_ADDRESS+polepairs_Data_uz_pmsm_model,polepairs);
    uz_pmsmModel_hw_write_polepairs(BASE_ADDRESS,polepairs);
}

void test_uz_pmsmModel_hw_write_psi_pm(void){
    float psi_pm=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+psi_pm_Data_uz_pmsm_model,psi_pm);
    uz_pmsmModel_hw_write_psi_pm(BASE_ADDRESS,psi_pm);
}

void test_uz_pmsmModel_hw_write_L_d(void){
    float L_d=0.003f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_L_d_Data_uz_pmsm_model,1.0f/L_d);
    uz_pmsmModel_hw_write_L_d(BASE_ADDRESS,L_d);
}

void test_uz_pmsmModel_hw_write_L_q(void){
    float L_q=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_L_q_Data_uz_pmsm_model,1.0f/L_q);
    uz_pmsmModel_hw_write_L_q(BASE_ADDRESS,L_q);
}

void test_uz_pmsmModel_hw_read_omega_mech(void){
    float omega_mech_expected=100.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+omega_mech_Data_uz_pmsm_model,omega_mech_expected);
    float omega_mech=uz_pmsmModel_hw_read_omega_mech(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expected,omega_mech);
}

void test_uz_pmsmModel_hw_write_simulate_mechanical(void){
    _Bool simulate_mech=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+simulate_mechanical_Data_uz_pmsm_model,simulate_mech);
    uz_pmsmModel_hw_write_simulate_mechanical(BASE_ADDRESS,simulate_mech);
}

void test_uz_pmsmModel_hw_write_inertia(void){
    float inertia=0.00031f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_J_Data_uz_pmsm_model,1.0f/inertia);
    uz_pmsmModel_hw_write_inertia(BASE_ADDRESS,inertia);
}

void test_uz_pmsmModel_hw_write_load_torque(void){
    float load_torque=10.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+load_torque_Data_uz_pmsm_model,load_torque);
    uz_pmsmModel_hw_write_load_torque(BASE_ADDRESS,load_torque);
}

void test_uz_pmsmModel_hw_write_output_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+output_signals_Strobe_uz_pmsm_model,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+output_signals_Strobe_uz_pmsm_model,false);
    uz_pmsmModel_hw_write_output_strobe(BASE_ADDRESS);
}

void test_uz_pmsmModel_hw_write_input_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+input_signals_Strobe_uz_pmsm_model,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+input_signals_Strobe_uz_pmsm_model,false);
    uz_pmsmModel_hw_write_input_strobe(BASE_ADDRESS);
}

#endif // TEST
