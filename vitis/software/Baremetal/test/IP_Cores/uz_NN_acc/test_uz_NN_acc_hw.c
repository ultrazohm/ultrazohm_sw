#include "unity.h"

#include "uz_NN_acc_hw.h"
#include <stdbool.h>
#include <stdint.h>
#include "test_assert_with_exception.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_NN_acc_hwAddresses.h"
#include "uz_struct_helper.h"
#include "uz_matrix.h"

#define BASE_ADDRESS 0x0F0000000U // random hex value that represents a fictional base address
#define ZERO_BASE_ADDRESS 0x00000000

volatile float Observation[24] = {0};
volatile float Action[12] = {0};
volatile float L_1_Bias[64] = {0};
volatile float L_2_Bias[64] = {0};
volatile float L_3_Bias[64] = {0};
volatile float L_Output_Bias[64] = {0};
volatile float L_1_Weights[64] = {0};
volatile float L_2_Weights[64] = {0};
volatile float L_3_Weights[64] = {0};
volatile float L_Output_Weights[64] = {0};
void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_NN_acc_hw_set_Observation_size_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_Observation_size(ZERO_BASE_ADDRESS, 20U));
}

void test_uz_NN_acc_hw_set_Observation_size(void) {
    uint32_t size = 20U;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_SIZE_INPUT_DATA, size);
    uz_NN_acc_hw_set_Observation_size(BASE_ADDRESS, size);
}

void test_uz_NN_acc_hw_set_Action_size_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_Action_size(ZERO_BASE_ADDRESS, 20U));
}

void test_uz_NN_acc_hw_set_Action_size(void) {
    uint32_t size = 20U;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_ACTION_SIZE_INPUT_DATA, size);
    uz_NN_acc_hw_set_Action_size(BASE_ADDRESS, size);
}

void test_uz_NN_acc_hw_set_Observation_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_Observation_Data(ZERO_BASE_ADDRESS, &Observation[0]));
}

void test_uz_NN_acc_hw_set_Observation_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_Observation_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_Observation_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)Observation;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_INPUT_DATA, address);
    uz_NN_acc_hw_set_Observation_Data(BASE_ADDRESS, &Observation[0]);
}

void test_uz_NN_acc_hw_set_Actions_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_Actions_Data(ZERO_BASE_ADDRESS, &Action[0]));
}

void test_uz_NN_acc_hw_set_Actions_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_Actions_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_Actions_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)Action;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_ACTION_OUTPUT_DATA, address);
    uz_NN_acc_hw_set_Actions_Data(BASE_ADDRESS, &Action[0]);
}

void test_uz_NN_acc_hw_set_L_1_Bias_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_1_Bias_Data(ZERO_BASE_ADDRESS, &L_1_Bias[0]));
}

void test_uz_NN_acc_hw_set_L_1_Bias_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_1_Bias_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_1_Bias_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_1_Bias;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_1_BIAS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_1_Bias_Data(BASE_ADDRESS, &L_1_Bias[0]);
}

void test_uz_NN_acc_hw_set_L_2_Bias_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_2_Bias_Data(ZERO_BASE_ADDRESS, &L_2_Bias[0]));
}

void test_uz_NN_acc_hw_set_L_2_Bias_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_2_Bias_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_2_Bias_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_2_Bias;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_2_BIAS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_2_Bias_Data(BASE_ADDRESS, &L_2_Bias[0]);
}

void test_uz_NN_acc_hw_set_L_3_Bias_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_3_Bias_Data(ZERO_BASE_ADDRESS, &L_3_Bias[0]));
}

void test_uz_NN_acc_hw_set_L_3_Bias_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_3_Bias_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_3_Bias_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_3_Bias;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_3_BIAS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_3_Bias_Data(BASE_ADDRESS, &L_3_Bias[0]);
}

void test_uz_NN_acc_hw_set_L_Output_Bias_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_Output_Bias_Data(ZERO_BASE_ADDRESS, &L_Output_Bias[0]));
}

void test_uz_NN_acc_hw_set_L_Output_Bias_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_Output_Bias_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_Output_Bias_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_Output_Bias;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_BIAS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_Output_Bias_Data(BASE_ADDRESS, &L_Output_Bias[0]);
}

void test_uz_NN_acc_hw_set_L_1_Weights_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_1_Weights_Data(ZERO_BASE_ADDRESS, &L_1_Weights[0]));
}

void test_uz_NN_acc_hw_set_L_1_Weights_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_1_Weights_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_1_Weights_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_1_Weights;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_1_WEIGHTS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_1_Weights_Data(BASE_ADDRESS, &L_1_Weights[0]);
}

void test_uz_NN_acc_hw_set_L_2_Weights_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_2_Weights_Data(ZERO_BASE_ADDRESS, &L_2_Weights[0]));
}

void test_uz_NN_acc_hw_set_L_2_Weights_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_2_Weights_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_2_Weights_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_2_Weights;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_2_WEIGHTS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_2_Weights_Data(BASE_ADDRESS, &L_2_Weights[0]);
}

void test_uz_NN_acc_hw_set_L_3_Weights_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_3_Weights_Data(ZERO_BASE_ADDRESS, &L_3_Weights[0]));
}

void test_uz_NN_acc_hw_set_L_3_Weights_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_3_Weights_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_3_Weights_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_3_Weights;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_3_WEIGHTS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_3_Weights_Data(BASE_ADDRESS, &L_3_Weights[0]);
}

void test_uz_NN_acc_hw_set_L_Output_Weights_Data_assert_base_address(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_Output_Weights_Data(ZERO_BASE_ADDRESS, &L_Output_Weights[0]));
}

void test_uz_NN_acc_hw_set_L_Output_Weights_Data_assert_array_pointer(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_L_Output_Weights_Data(BASE_ADDRESS, NULL));
}

void test_uz_NN_acc_hw_set_L_Output_Weights_Data(void) {
    volatile uint32_t* pointer = (uint32_t*)L_Output_Weights;
	volatile uint32_t address = (uint32_t)pointer;
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_WEIGHTS_INPUT_DATA, address);
    uz_NN_acc_hw_set_L_Output_Weights_Data(BASE_ADDRESS, &L_Output_Weights[0]);
}

void test_uz_NN_acc_hw_set_copy_mats_flag_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_copy_mats_flag(ZERO_BASE_ADDRESS,true)); 
}

void test_uz_NN_acc_hw_set_copy_mats_flag(void) {
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA, true);
    uz_NN_acc_hw_set_copy_mats_flag(BASE_ADDRESS,true); 
} 

void test_uz_NN_acc_hw_get_copy_mats_flag_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_get_copy_mats_flag(ZERO_BASE_ADDRESS)); 
}

void test_uz_NN_acc_hw_get_copy_mats_flag(void) {
    uint32_t expected_return = true;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA, expected_return);
    uint32_t actual_return = uz_NN_acc_hw_get_copy_mats_flag(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
}

void test_uz_NN_acc_hw_get_matrices_updated_out_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_get_matrices_updated_out(ZERO_BASE_ADDRESS)); 
}

void test_uz_NN_acc_hw_get_matrices_updated_out_flag(void) {
    uint32_t expected_return = true;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA, expected_return);
    uint32_t actual_return = uz_NN_acc_hw_get_matrices_updated_out(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
} 

void test_uz_NN_acc_hw_get_is_done_output_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_get_is_done_output(ZERO_BASE_ADDRESS)); 
}

void test_uz_NN_acc_hw_get_is_done_output(void) {
    bool expected_return = (0x10U >> 1U )& 0x1U;
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL,0x10U);
    bool actual_return = uz_NN_acc_hw_get_is_done_output(BASE_ADDRESS);
    TEST_ASSERT_EQUAL(expected_return, actual_return);
} 

void test_uz_NN_acc_hw_set_start_assert(void) {
    TEST_ASSERT_FAIL_ASSERT(uz_NN_acc_hw_set_start(ZERO_BASE_ADDRESS)); 
}

void test_uz_NN_acc_hw_set_start(void) {
    uz_axi_read_uint32_ExpectAndReturn(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL,0x00U);
    uz_axi_write_uint32_Expect(BASE_ADDRESS + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, 0x01U);
    uz_NN_acc_hw_set_start(BASE_ADDRESS); 
} 

