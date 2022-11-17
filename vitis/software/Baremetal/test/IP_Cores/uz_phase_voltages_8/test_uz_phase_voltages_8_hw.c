#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "uz_phase_voltages_8_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_phase_voltages_hwAdresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_phase_voltages_8_set_theta_el_offset(void){
        struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float theta_el_offset = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+theta_el_offset_AXI_Data_parallel_8_sim_phase_voltages,theta_el_offset,def);
    uz_phase_voltages_8_set_theta_el_offset(TEST_BASE_ADDRESS,theta_el_offset);
}

void test_uz_phase_voltages_8_set_theta_el_offset_fail_due_to_zero_base_address(void){
    float theta_el_offset = 1.35f;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_8_set_theta_el_offset(0,theta_el_offset));
}

void test_uz_phase_voltages_8_set_u_dc_link_voltage(void){
    float u_dc_link_voltage = 560.0f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS+u_dc_link_voltage_AXI_Data_parallel_8_sim_phase_voltages,u_dc_link_voltage);
    uz_phase_voltages_8_set_u_dc_link_voltage(TEST_BASE_ADDRESS,u_dc_link_voltage);
}

void test_uz_phase_voltages_8_set_u_dc_link_voltage_fail_due_to_zero_base_address(void){
    float u_dc_link_voltage = 560.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_8_set_u_dc_link_voltage(0,u_dc_link_voltage));
}

void test_uz_phase_voltages_8_get_Index_in(void){
     int32_t expected_return_value = 3;
     uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+Index_in_AXI_Data_parallel_8_sim_phase_voltages,expected_return_value);
     int32_t actual_return_value = uz_phase_voltages_8_get_Index_in(TEST_BASE_ADDRESS);
     TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}
#endif // TEST
