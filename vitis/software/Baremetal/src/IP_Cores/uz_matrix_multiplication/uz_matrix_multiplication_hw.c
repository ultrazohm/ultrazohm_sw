#include "uz_matrix_multiplication_hw.h"
#include "uz_matrix_multiplication_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

#define REGISTER_OFFSET (XMATRIXMULTIPLICATION_CONTROL_WIDTH_A / 8U)

void uz_matrix_multiplication_hw_set_Observation_size(uint32_t base_address, uint32_t Observation_size) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_SIZE_INPUT_DATA, Observation_size);
}
void uz_matrix_multiplication_hw_set_Action_size(uint32_t base_address, uint32_t Action_size) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_ACTION_SIZE_INPUT_DATA, Action_size);
}

void uz_matrix_multiplication_hw_set_A_matrix(uint32_t base_address, volatile float * A) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(A);
	volatile uint32_t* pointer = (uint32_t*)A;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_B1_matrix(uint32_t base_address, volatile float * B1) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(B1);
	volatile uint32_t* pointer = (uint32_t*)B1;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_INPUT_WEIGHTS_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_B2_matrix(uint32_t base_address, volatile float * B2) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(B2);
	volatile uint32_t* pointer = (uint32_t*)B2;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_1_WEIGHTS_INPUT_DATA, address);
}
void uz_matrix_multiplication_hw_set_B3_matrix(uint32_t base_address, volatile float * B3) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(B3);
	volatile uint32_t* pointer = (uint32_t*)B3;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_2_WEIGHTS_INPUT_DATA, address);
}
void uz_matrix_multiplication_hw_set_B4_matrix(uint32_t base_address, volatile float * B4) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(B4);
	volatile uint32_t* pointer = (uint32_t*)B4;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_3_WEIGHTS_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_C_out_matrix(uint32_t base_address, volatile float *C_out) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(C_out);
	volatile uint32_t* pointer = (uint32_t*)C_out;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_ACTION_OUTPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_Bias1_matrix(uint32_t base_address, volatile float * Bias1) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(Bias1);
	volatile uint32_t* pointer = (uint32_t*)Bias1;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_INPUT_BIAS_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_Bias2_matrix(uint32_t base_address, volatile float * Bias2) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(Bias2);
	volatile uint32_t* pointer = (uint32_t*)Bias2;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_1_BIAS_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_Bias3_matrix(uint32_t base_address, volatile float * Bias3) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(Bias3);
	volatile uint32_t* pointer = (uint32_t*)Bias3;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_2_BIAS_INPUT_DATA, address);
}
void uz_matrix_multiplication_hw_set_Bias4_matrix(uint32_t base_address, volatile float * Bias4) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(Bias4);
	volatile uint32_t* pointer = (uint32_t*)Bias4;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_3_BIAS_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_start(uint32_t base_address, bool flag) {
	uz_assert_not_zero_uint32(base_address);
	if(flag) {
		uint32_t status = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL) & 0x80);
		uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, (status | 0x01U));
	} else {
		uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, 0x00U);
	}

}

bool uz_matrix_multiplication_hw_get_is_done_output(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool is_done = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL)>> 1U )& 0x1U;
	return (is_done);
}

bool uz_matrix_multiplication_hw_get_is_idle_output(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool is_done = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL)>> 2U )& 0x1U;
	return (is_done);
}

void uz_matrix_multiplication_hw_set_copy_mats_flag(uint32_t base_address, bool copy_mats_flag) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA, copy_mats_flag);
}

bool uz_matrix_multiplication_hw_get_copy_mats_flag(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool copy_mats_flag = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA));
	return(copy_mats_flag);
}

bool uz_matrix_multiplication_hw_get_copy_flag_out(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool copy_flag_out = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_COPY_FLAG_OUT_DATA));
	return(copy_flag_out);
}

bool uz_matrix_multiplication_hw_get_matrices_updated_out(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool matrices_updated_out = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA));
	return(matrices_updated_out);
}

void uz_matrix_multiplication_hw_set_auto_restart(uint32_t base_address, bool auto_restart) {
	uz_assert_not_zero_uint32(base_address);
	if (auto_restart) {
		uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, 0x80U);
	} else {
		uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, 0x0U);
	}
}
