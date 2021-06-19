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
    uz_axi_write_bool_Expect(BASE_ADDRESS+reset_Data_uz_pmsm_model,true);
    uz_pmsmModel_hw_write_reset(BASE_ADDRESS,true);
}

void test_uz_pmsmModel_hw_write_omega_mech(void){
    float omega_mech=123.4f;
    uz_axi_write_float_Expect(BASE_ADDRESS+omega_mech_Data_uz_pmsm_model,omega_mech);
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



#endif // TEST
