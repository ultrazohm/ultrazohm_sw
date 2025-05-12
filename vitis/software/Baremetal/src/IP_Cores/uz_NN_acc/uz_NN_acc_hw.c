/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2025 Dennis Hufnagel
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "uz_NN_acc_hw.h"
#include "uz_NN_acc_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_NN_acc_hw_set_Observation_size(uint32_t base_address, uint32_t Observation_size) {
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_SIZE_INPUT_DATA, Observation_size);
}

void uz_NN_acc_hw_set_Action_size(uint32_t base_address, uint32_t Action_size) {
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_ACTION_SIZE_INPUT_DATA, Action_size);
}

void uz_NN_acc_hw_set_Observation_Data(uint32_t base_address, volatile float *Observation_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(Observation_Data);
	volatile uint32_t* pointer = (uint32_t*)Observation_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_OBSERVATION_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_L_1_Weights_Data(uint32_t base_address, volatile float *L_1_Weights_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_1_Weights_Data);
	volatile uint32_t* pointer = (uint32_t*)L_1_Weights_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_1_WEIGHTS_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_L_2_Weights_Data(uint32_t base_address, volatile float *L_2_Weights_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_2_Weights_Data);
	volatile uint32_t* pointer = (uint32_t*)L_2_Weights_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_2_WEIGHTS_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_L_3_Weights_Data(uint32_t base_address, volatile float *L_3_Weights_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_3_Weights_Data);
	volatile uint32_t* pointer = (uint32_t*)L_3_Weights_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_3_WEIGHTS_INPUT_DATA, address);
}
void uz_NN_acc_hw_set_L_Output_Weights_Data(uint32_t base_address, volatile float *L_Output_Weights_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_Output_Weights_Data);
	volatile uint32_t* pointer = (uint32_t*)L_Output_Weights_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_WEIGHTS_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_Actions_Data(uint32_t base_address, volatile float *Actions_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(Actions_Data);
	volatile uint32_t* pointer = (uint32_t*)Actions_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_ACTION_OUTPUT_DATA, address);
}

void uz_NN_acc_hw_set_L_1_Bias_Data(uint32_t base_address, volatile float *L_1_Bias_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_1_Bias_Data);
	volatile uint32_t* pointer = (uint32_t*)L_1_Bias_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_1_BIAS_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_L_2_Bias_Data(uint32_t base_address, volatile float *L_2_Bias_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_2_Bias_Data);
	volatile uint32_t* pointer = (uint32_t*)L_2_Bias_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_2_BIAS_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_L_3_Bias_Data(uint32_t base_address, volatile float *L_3_Bias_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_3_Bias_Data);
	volatile uint32_t* pointer = (uint32_t*)L_3_Bias_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_3_BIAS_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_L_Output_Bias_Data(uint32_t base_address, volatile float *L_Output_Bias_Data) {
    uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(L_Output_Bias_Data);
	volatile uint32_t* pointer = (uint32_t*)L_Output_Bias_Data;
	volatile uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_L_OUTPUT_BIAS_INPUT_DATA, address);
}

void uz_NN_acc_hw_set_copy_mats_flag(uint32_t base_address, bool copy_mats_flag) {
    uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA, copy_mats_flag);
}

bool uz_NN_acc_hw_get_copy_mats_flag(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
	bool copy_mats_flag = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_COPY_MATS_FLAG_DATA));
	return(copy_mats_flag);
}

bool uz_NN_acc_hw_get_copy_flag_out(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
	bool copy_flag_out = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_COPY_FLAG_OUT_DATA));
	return(copy_flag_out);
}

bool uz_NN_acc_hw_get_matrices_updated_out(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
	bool matrices_updated_out = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_MATRICES_UPDATED_OUT_DATA));
	return(matrices_updated_out); 
}

void uz_NN_acc_hw_set_start(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
	uint32_t status = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL) & 0x80);
	uz_axi_write_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL, (status | 0x01U));
}

bool uz_NN_acc_hw_get_is_done_output(uint32_t base_address) {
    uz_assert_not_zero_uint32(base_address);
	bool is_done = (uz_axi_read_uint32(base_address + XUZ_NN_ACC_CONTROL_ADDR_AP_CTRL)>> 1U )& 0x1U;
	return (is_done);
}
