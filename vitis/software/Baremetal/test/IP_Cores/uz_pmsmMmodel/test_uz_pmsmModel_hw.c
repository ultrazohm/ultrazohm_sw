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

void test_uz_pmsmModel_hw_write_v_q(void){
    float v_q_expect=123.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS + v_q_Data_uz_pmsm_model,v_q_expect);
    uz_pmsmModel_hw_write_v_q(BASE_ADDRESS,v_q_expect);
}

void test_uz_pmsmModel_hw_write_v_d(void){
    float v_d_expect=-3.1f;
    uz_axi_write_float_Expect(BASE_ADDRESS + v_d_Data_uz_pmsm_model,v_d_expect);
    uz_pmsmModel_hw_write_v_d(BASE_ADDRESS,v_d_expect);
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
    uz_axi_write_float_Expect(BASE_ADDRESS+Ld_Data_uz_pmsm_model,L_d);
    uz_pmsmModel_hw_write_L_d(BASE_ADDRESS,L_d);
}

void test_uz_pmsmModel_hw_write_L_q(void){
    float L_q=0.001f;
    uz_axi_write_float_Expect(BASE_ADDRESS+Lq_Data_uz_pmsm_model,L_q);
    uz_pmsmModel_hw_write_L_q(BASE_ADDRESS,L_q);
}

void test_uz_pmsmModel_hw_read_omega_mech(void){
    float omega_mech_expected=100.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+out_omega_mech_Data_uz_pmsm_model,omega_mech_expected);
    float omega_mech=uz_pmsmModel_hw_read_omega_mech(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expected,omega_mech);
}

void test_uz_pmsmModel_hw_write_simulate_mechanical(void){
    _Bool simulate_mech=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+simulate_mechanical_Data_uz_pmsm_model,simulate_mech);
    uz_pmsmModel_hw_write_simulate_mechanical(BASE_ADDRESS,simulate_mech);
}

void test_uz_pmsmModel_hw_write_simulate_nonlinear(void){
    _Bool simulate_nonlinear=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+simulate_nonlinear_Data_uz_pmsm_model,simulate_nonlinear);
    uz_pmsmModel_hw_write_simulate_nonlinear(BASE_ADDRESS,simulate_nonlinear);
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

void test_uz_pmsmModel_hw_write_ad1(void){
    float ad1=0.03f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad1_Data_uz_pmsm_model,ad1);
    uz_pmsmModel_hw_write_ad1(BASE_ADDRESS,ad1);
}

void test_uz_pmsmModel_hw_write_ad2(void){
    float ad2=0.04f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad2_Data_uz_pmsm_model,ad2);
    uz_pmsmModel_hw_write_ad2(BASE_ADDRESS,ad2);
}

void test_uz_pmsmModel_hw_write_ad3(void){
    float ad3=-16.04f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad3_Data_uz_pmsm_model,ad3);
    uz_pmsmModel_hw_write_ad3(BASE_ADDRESS,ad3);
}

void test_uz_pmsmModel_hw_write_ad4(void){
    float ad4=1.24f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad4_Data_uz_pmsm_model,ad4);
    uz_pmsmModel_hw_write_ad4(BASE_ADDRESS,ad4);
}

void test_uz_pmsmModel_hw_write_ad5(void){
    float ad5=0.06f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad5_Data_uz_pmsm_model,ad5);
    uz_pmsmModel_hw_write_ad5(BASE_ADDRESS,ad5);
}

void test_uz_pmsmModel_hw_write_ad6(void){
    float ad6=-12.24f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad6_Data_uz_pmsm_model,ad6);
    uz_pmsmModel_hw_write_ad6(BASE_ADDRESS,ad6);
}

void test_uz_pmsmModel_hw_write_aq1(void){
    float aq1=0.005f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq1_Data_uz_pmsm_model,aq1);
    uz_pmsmModel_hw_write_aq1(BASE_ADDRESS,aq1);
}

void test_uz_pmsmModel_hw_write_aq2(void){
    float aq2=0.17f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq2_Data_uz_pmsm_model,aq2);
    uz_pmsmModel_hw_write_aq2(BASE_ADDRESS,aq2);
}

void test_uz_pmsmModel_hw_write_aq3(void){
    float aq3=0.926f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq3_Data_uz_pmsm_model,aq3);
    uz_pmsmModel_hw_write_aq3(BASE_ADDRESS,aq3);
}

void test_uz_pmsmModel_hw_write_aq4(void){
    float aq4=0.049f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq4_Data_uz_pmsm_model,aq4);
    uz_pmsmModel_hw_write_aq4(BASE_ADDRESS,aq4);
}

void test_uz_pmsmModel_hw_write_aq5(void){
    float aq5=0.17f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq5_Data_uz_pmsm_model,aq5);
    uz_pmsmModel_hw_write_aq5(BASE_ADDRESS,aq5);
}

void test_uz_pmsmModel_hw_write_aq6(void){
    float aq6=0.918f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq6_Data_uz_pmsm_model,aq6);
    uz_pmsmModel_hw_write_aq6(BASE_ADDRESS,aq6);
}

void test_uz_pmsmModel_hw_write_reciprocal_F1G1(void){
    float F1G1=0.005f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_F1G1_Data_uz_pmsm_model,1.0f/F1G1);
    uz_pmsmModel_hw_write_reciprocal_F1G1(BASE_ADDRESS,F1G1);
}

void test_uz_pmsmModel_hw_write_reciprocal_F2G2(void){
    float F2G2=0.17f;
    uz_axi_write_float_Expect(BASE_ADDRESS+reciprocal_F2G2_Data_uz_pmsm_model,1.0f/F2G2);
    uz_pmsmModel_hw_write_reciprocal_F2G2(BASE_ADDRESS,F2G2);
}

//FittingParameter that are calculated in driver

//Multiply
void test_uz_pmsmModel_hw_write_ad4_mul_ad5(void){
    float ad4=0.11f;
    float ad5=0.12f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad4_mul_ad5_Data_uz_pmsm_model,ad4*ad5);
    uz_pmsmModel_hw_write_ad4_mul_ad5(BASE_ADDRESS,ad4,ad5);
}

void test_uz_pmsmModel_hw_write_ad1_mul_ad2(void){
    float ad1=0.13f;
    float ad2=0.14f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad1_mul_ad2_Data_uz_pmsm_model,ad1*ad2);
    uz_pmsmModel_hw_write_ad1_mul_ad2(BASE_ADDRESS,ad1,ad2);
}

void test_uz_pmsmModel_hw_write_aq4_mul_aq5(void){
    float aq4=0.15f;
    float aq5=0.16f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq4_mul_aq5_Data_uz_pmsm_model,aq4*aq5);
    uz_pmsmModel_hw_write_aq4_mul_aq5(BASE_ADDRESS,aq4,aq5);
}

void test_uz_pmsmModel_hw_write_aq1_mul_aq2(void){
    float aq1=0.17f;
    float aq2=0.18f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq1_mul_aq2_Data_uz_pmsm_model,aq1*aq2);
    uz_pmsmModel_hw_write_aq1_mul_aq2(BASE_ADDRESS,aq1,aq2);
}

//Divide

void test_uz_pmsmModel_hw_write_aq4_div_aq5(void){
    float aq4=0.21f;
    float aq5=0.22f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq4_div_aq5_Data_uz_pmsm_model,aq4/aq5);
    uz_pmsmModel_hw_write_aq4_div_aq5(BASE_ADDRESS,aq4,aq5);
}

void test_uz_pmsmModel_hw_write_aq1_div_aq2(void){
    float aq1=0.23f;
    float aq2=0.24f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq1_div_aq2_Data_uz_pmsm_model,aq1/aq2);
    uz_pmsmModel_hw_write_aq1_div_aq2(BASE_ADDRESS,aq1,aq2);
}

void test_uz_pmsmModel_hw_write_ad4_div_ad5(void){
    float ad4=0.25f;
    float ad5=0.26f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad4_div_ad5_Data_uz_pmsm_model,ad4/ad5);
    uz_pmsmModel_hw_write_ad4_div_ad5(BASE_ADDRESS,ad4,ad5);
}

void test_uz_pmsmModel_hw_write_ad1_div_ad2(void){
    float ad1=0.27f;
    float ad2=0.28f;
    uz_axi_write_float_Expect(BASE_ADDRESS+ad1_div_ad2_Data_uz_pmsm_model,ad1/ad2);
    uz_pmsmModel_hw_write_ad1_div_ad2(BASE_ADDRESS,ad1,ad2);
}

void test_uz_pmsmModel_hw_write_aq3_min_aq6(void){
    float aq3=0.45f;
    float aq6=0.46f;
    uz_axi_write_float_Expect(BASE_ADDRESS+aq3_min_aq6_Data_uz_pmsm_model,0.5f*(aq3-aq6));
    uz_pmsmModel_hw_write_aq3_min_aq6(BASE_ADDRESS,aq3,aq6);
}

//strobes
void test_uz_pmsmModel_hw_trigger_input_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+inputs_Strobe_uz_pmsm_model,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+inputs_Strobe_uz_pmsm_model,false);
    uz_pmsmModel_hw_trigger_input_strobe(BASE_ADDRESS);
}

void test_uz_pmsmModel_hw_trigger_output_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+outputs_Strobe_uz_pmsm_model,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+outputs_Strobe_uz_pmsm_model,false);
    uz_pmsmModel_hw_trigger_output_strobe(BASE_ADDRESS);
}

void test_uz_pmsmModel_hw_trigger_fitting_parameter_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+fitting_parameter_Strobe_uz_pmsm_model,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+fitting_parameter_Strobe_uz_pmsm_model,false);
    uz_pmsmModel_hw_trigger_fitting_parameter_strobe(BASE_ADDRESS);
}








#endif // TEST
