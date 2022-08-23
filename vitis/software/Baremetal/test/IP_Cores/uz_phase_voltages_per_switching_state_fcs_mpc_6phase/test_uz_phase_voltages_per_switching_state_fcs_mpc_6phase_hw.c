#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_phase_voltages_per_switching_state_fcs_mpc_6phase_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_phase_voltages_per_switching_state_fcs_mpc_6phase_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset(void){
    float theta_el_offset = 1.35f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+theta_el_offset_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,theta_el_offset);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset(TEST_BASE_ADDRESS,theta_el_offset);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset_fail_due_to_zero_base_address(void){
    float theta_el_offset = 1.35f;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset(0,theta_el_offset));
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage(void){
    float u_dc_link_voltage = 560.0f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+u_dc_link_voltage_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,u_dc_link_voltage);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage(TEST_BASE_ADDRESS,u_dc_link_voltage);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage_fail_due_to_zero_base_address(void){
    float u_dc_link_voltage = 560.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage(0,u_dc_link_voltage));
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI(void){
    _Bool use_AXI = 1;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+use_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,use_AXI);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI(TEST_BASE_ADDRESS,use_AXI);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI_fail_due_to_zero_base_address(void){
    _Bool use_AXI = 1;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI(0,use_AXI));
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_AXI(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float theta_el_AXI = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+theta_el_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,theta_el_AXI,def);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_AXI(TEST_BASE_ADDRESS,theta_el_AXI);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_AXI_fail_due_to_zero_base_address(void){
    float theta_el_AXI = 1.35f;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_AXI(0,theta_el_AXI));
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_Index_AXI(void){
    int32_t Index_AXI = 35;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+Index_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,Index_AXI);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_Index_AXI(TEST_BASE_ADDRESS,Index_AXI);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_Index_AXI_fail_due_to_zero_base_address(void){
    int32_t Index_AXI = 35;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_Index_AXI(0,Index_AXI));
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_d_voltage_per_switching_state(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+d_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_d_voltage_per_switching_state(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_q_voltage_per_switching_state(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+q_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_q_voltage_per_switching_state(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_x_voltage_per_switching_state(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+x_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_x_voltage_per_switching_state(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

    void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_y_voltage_per_switching_state(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+y_voltage_per_switching_state_AXI_Data_Phase_voltages_per_switching_state_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_y_voltage_per_switching_state(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

#endif // TEST
