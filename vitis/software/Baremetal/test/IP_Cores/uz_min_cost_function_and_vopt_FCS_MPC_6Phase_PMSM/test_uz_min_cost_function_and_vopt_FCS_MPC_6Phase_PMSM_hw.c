#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI(void){
    _Bool use_AXI = 1;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+use_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,use_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI(TEST_BASE_ADDRESS,use_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI_fail_due_to_zero_base_address(void){
    _Bool use_AXI = 1;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_use_AXI(0,use_AXI));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=9
    };
    float J_in_AXI = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+J_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,J_in_AXI,def);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI(TEST_BASE_ADDRESS,J_in_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI_fail_due_to_zero_base_address(void){
    float J_in_AXI = 5.3f;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_J_in_AXI(0,J_in_AXI));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_Index_in_AXI(void){
    int32_t Index_in_AXI = 35;
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+Index_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,Index_in_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_Index_in_AXI(TEST_BASE_ADDRESS,Index_in_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_Index_in_AXI_fail_due_to_zero_base_address(void){
    int32_t Index_in_AXI = 35;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_Index_in_AXI(0,Index_in_AXI));
}


void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_d_phase_voltage_per_switchimng_state_AXI(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=13
    };
    float d_phase_voltage_per_switchimng_state_AXI = 1.25f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+d_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,d_phase_voltage_per_switchimng_state_AXI,def);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_d_phase_voltage_per_switchimng_state_AXI(TEST_BASE_ADDRESS,d_phase_voltage_per_switchimng_state_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_d_phase_voltage_per_switchimng_state_AXI_fail_due_to_zero_base_address(void){
    float d_phase_voltage_per_switchimng_state_AXI = 5.32f;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_d_phase_voltage_per_switchimng_state_AXI(0,d_phase_voltage_per_switchimng_state_AXI));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_q_phase_voltage_per_switchimng_state_AXI(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=13
    };
    float q_phase_voltage_per_switchimng_state_AXI = 4.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+q_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,q_phase_voltage_per_switchimng_state_AXI,def);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_q_phase_voltage_per_switchimng_state_AXI(TEST_BASE_ADDRESS,q_phase_voltage_per_switchimng_state_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_q_phase_voltage_per_switchimng_state_AXI_fail_due_to_zero_base_address(void){
    float q_phase_voltage_per_switchimng_state_AXI = 4.3f;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_q_phase_voltage_per_switchimng_state_AXI(0,q_phase_voltage_per_switchimng_state_AXI));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_x_phase_voltage_per_switchimng_state_AXI(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=13
    };
    float x_phase_voltage_per_switchimng_state_AXI = 6.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+x_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,x_phase_voltage_per_switchimng_state_AXI,def);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_x_phase_voltage_per_switchimng_state_AXI(TEST_BASE_ADDRESS,x_phase_voltage_per_switchimng_state_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_x_phase_voltage_per_switchimng_state_AXI_fail_due_to_zero_base_address(void){
    float x_phase_voltage_per_switchimng_state_AXI = 6.3f;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_x_phase_voltage_per_switchimng_state_AXI(0,x_phase_voltage_per_switchimng_state_AXI));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_y_phase_voltage_per_switchimng_state_AXI(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=13
    };
    float y_phase_voltage_per_switchimng_state_AXI = 12.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+y_phase_voltage_per_switchimng_state_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,y_phase_voltage_per_switchimng_state_AXI,def);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_y_phase_voltage_per_switchimng_state_AXI(TEST_BASE_ADDRESS,y_phase_voltage_per_switchimng_state_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_y_phase_voltage_per_switchimng_state_AXI_fail_due_to_zero_base_address(void){
    float y_phase_voltage_per_switchimng_state_AXI = 12.3f;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_y_phase_voltage_per_switchimng_state_AXI(0,y_phase_voltage_per_switchimng_state_AXI));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_valid_in_AXI(void){
    _Bool valid_in_AXI = 1;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+valid_in_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,valid_in_AXI);
    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_valid_in_AXI(TEST_BASE_ADDRESS,valid_in_AXI);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_valid_in_AXI_fail_due_to_zero_base_address(void){
    _Bool valid_in_AXI = 1;
    TEST_ASSERT_FAIL_ASSERT(uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_set_valid_in_AXI(0,valid_in_AXI));
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uy_AXI(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+last_applied_optimal_voltage_uy_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uy_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ux_AXI(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+last_applied_optimal_voltage_ux_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ux_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uq_AXI(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+last_applied_optimal_voltage_uq_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_uq_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ud_AXI(void){
        struct uz_fixedpoint_definition_t fixedpoint_definition = {
        .fractional_bits = 11,
        .integer_bits = 13,
        .is_signed = true};
    float expected_return_value = -1.0;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+last_applied_optimal_voltage_ud_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_last_applied_optimal_voltage_ud_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_done_complete_AXI(void){
    _Bool expected_return_value = 1;
    uz_axi_read_bool_ExpectAndReturn(TEST_BASE_ADDRESS+done_complete_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,expected_return_value);
    _Bool actual_return_value = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_done_complete_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return_value,actual_return_value);
}

void test_uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_Index_out_AXI(void){
    int32_t expected_return_value = 6;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+Index_out_AXI_Data_min_cost_function_and_vopt_FCS_MPC_6Phase,expected_return_value);
    int32_t actual_return_value = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_hw_get_Index_out_AXI(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(expected_return_value,actual_return_value);
}
#endif // TEST
