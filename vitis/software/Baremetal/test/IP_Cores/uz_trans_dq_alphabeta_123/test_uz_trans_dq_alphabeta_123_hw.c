#ifdef TEST

#include "unity.h"

#include "uz_trans_dq_alphabeta_123_hw.h"
#include "uz_struct_helper.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_trans_dq_alphabeta_123_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address




void setUp(void)
{
}

void tearDown(void)
{
}


void test_uz_trans_dq_alphabeta_123_hw_set_thetaOffset(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=20,
        .integer_bits=4
    };
    float theta_offset = 1.35f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+theta_offset_AXI_Data_Trans_dq_alphabeta_123_ip,theta_offset,def);
    uz_trans_dq_alphabeta_123_hw_set_thetaOffset(TEST_BASE_ADDRESS,theta_offset);
}

void test_uz_trans_dq_alphabeta_123_hw_set_thetaOffset_fail_due_to_zero_base_address(void){
    float thetaOffset = 5.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_trans_dq_alphabeta_123_hw_set_thetaOffset(0,thetaOffset));
}

void test_uz_trans_dq_alphabeta_123_hw_set_idref(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=7
    };
    float id_ref = 2.5f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+Id_ref_AXI_Data_Trans_dq_alphabeta_123_ip,id_ref,def);
    uz_trans_dq_alphabeta_123_hw_set_idref(TEST_BASE_ADDRESS,id_ref);
}

void test_uz_trans_dq_alphabeta_123_hw_set_idref_fail_due_to_zero_base_address(void){
    float idref = 3.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_trans_dq_alphabeta_123_hw_set_idref(0,idref));
}

void test_uz_trans_dq_alphabeta_123_hw_set_iqref(void){
    struct uz_fixedpoint_definition_t def={
        .is_signed=true,
        .fractional_bits=11,
        .integer_bits=7
    };
    float iq_ref = 3.5f;
    uz_fixedpoint_axi_write_Expect(TEST_BASE_ADDRESS+Iq_ref_AXI_Data_Trans_dq_alphabeta_123_ip,iq_ref,def);
    uz_trans_dq_alphabeta_123_hw_set_iqref(TEST_BASE_ADDRESS,iq_ref);
}

void test_uz_trans_dq_alphabeta_123_hw_set_iqref_fail_due_to_zero_base_address(void){
    float iqref = 4.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_trans_dq_alphabeta_123_hw_set_iqref(0,iqref));
}

void test_uz_trans_dq_alphabeta_123_hw_get_i1(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };

    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i1_AXI_Data_Trans_dq_alphabeta_123_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_trans_dq_alphabeta_123_hw_get_i1(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_trans_dq_alphabeta_123_hw_get_i2(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };

    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i2_AXI_Data_Trans_dq_alphabeta_123_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_trans_dq_alphabeta_123_hw_get_i2(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_trans_dq_alphabeta_123_hw_get_i3(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };
    
    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i3_AXI_Data_Trans_dq_alphabeta_123_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_trans_dq_alphabeta_123_hw_get_i3(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_trans_dq_alphabeta_123_hw_get_ialpha(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };
    
    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+ialpha_AXI_Data_Trans_dq_alphabeta_123_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_trans_dq_alphabeta_123_hw_get_ialpha(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

void test_uz_trans_dq_alphabeta_123_hw_get_ibeta(void){
    // sfix18_En11
    struct uz_fixedpoint_definition_t fixedpoint_definition={
        .fractional_bits=11,
        .integer_bits=7,
        .is_signed=true
    };
    
    float expected_return_value = -63.25;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+ibeta_AXI_Data_Trans_dq_alphabeta_123_ip,fixedpoint_definition,expected_return_value);
    float actual_return_value = uz_trans_dq_alphabeta_123_hw_get_ibeta(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_return_value,actual_return_value);
}

#endif // TEST
