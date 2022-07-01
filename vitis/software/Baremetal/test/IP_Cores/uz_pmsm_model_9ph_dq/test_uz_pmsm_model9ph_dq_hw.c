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

// Outputs general
void test_uz_pmsm_model9ph_hw_read_torque(void)
{
    float torque_expect=4.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+M_Mi_axi_Data_uz_pmsm_model9ph_dq,torque_expect);
    float torque_read=uz_pmsm_model9ph_hw_read_torque(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(torque_expect,torque_read);
}

void test_uz_pmsm_model9ph_hw_read_omega_mech(void){
    float omega_mech_expected=100.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+omega_out_axi_Data_uz_pmsm_model9ph_dq,omega_mech_expected);
    float omega_mech=uz_pmsm_model9ph_hw_read_omega_mech(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(omega_mech_expected,omega_mech);
}

void test_uz_pmsm_model9ph_hw_read_theta_el(void){
    float theta_el_expected=10.2f;
    uz_axi_read_float_ExpectAndReturn(BASE_ADDRESS+theta_el_axi_Data_uz_pmsm_model9ph_dq,theta_el_expected);
    float theta_el=uz_pmsm_model9ph_hw_read_theta_el(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(theta_el_expected,theta_el);
}

// Inputs general
void test_uz_pmsm_model9ph_hw_write_load_torque(void){
    float load_torque=10.5f;
    uz_axi_write_float_Expect(BASE_ADDRESS+load_torque_Data_uz_pmsm_model9ph_dq,load_torque);
    uz_pmsm_model9ph_hw_write_load_torque(BASE_ADDRESS,load_torque);
}

void test_uz_pmsm_model9ph_hw_write_omega_mech(void){
    float omega_mech=123.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+omega_mech_Data_uz_pmsm_model9ph_dq,omega_mech);
    uz_pmsm_model9ph_hw_write_omega_mech(BASE_ADDRESS,omega_mech);
}

void test_uz_pmsm_model9ph_hw_write_reset(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+reset_integrators__Data_uz_pmsm_model9ph_dq,true);
    uz_pmsm_model9ph_hw_write_reset(BASE_ADDRESS,true);
}

void test_uz_pmsm_model9ph_hw_write_simulate_mechanical(void){
    _Bool simulate_mech=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+simulate_mechanical_Data_uz_pmsm_model9ph_dq,simulate_mech);
    uz_pmsm_model9ph_hw_write_simulate_mechanical(BASE_ADDRESS,simulate_mech);
}

void test_uz_pmsm_model9ph_hw_write_switch_pspl(void){
    _Bool switch_pspl=true;
    uz_axi_write_bool_Expect(BASE_ADDRESS+use_axi_input_Data_uz_pmsm_model9ph_dq,switch_pspl);
    uz_pmsm_model9ph_hw_write_switch_pspl(BASE_ADDRESS,switch_pspl);
}


#endif // TEST
