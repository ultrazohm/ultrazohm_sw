#ifndef UZ_NN_ACC_HW_H
#define UZ_NN_ACC_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_NN_acc_hw_set_Observation_size(uint32_t base_address, uint32_t Observation_size);
void uz_NN_acc_hw_set_Action_size(uint32_t base_address, uint32_t Action_size);
void uz_NN_acc_hw_set_Observation_Data(uint32_t base_address, volatile float *Observation_Data);
void uz_NN_acc_hw_set_L_1_Weights_Data(uint32_t base_address, volatile float *L_1_Weights_Data);
void uz_NN_acc_hw_set_L_2_Weights_Data(uint32_t base_address, volatile float *L_2_Weights_Data);
void uz_NN_acc_hw_set_L_3_Weights_Data(uint32_t base_address, volatile float *L_3_Weights_Data);
void uz_NN_acc_hw_set_L_Output_Weights_Data(uint32_t base_address, volatile float *L_Output_Weights_Data);
void uz_NN_acc_hw_set_Actions_Data(uint32_t base_address, volatile float *Actions_Data);
void uz_NN_acc_hw_set_L_1_Bias_Data(uint32_t base_address, volatile float *L_1_Bias_Data);
void uz_NN_acc_hw_set_L_2_Bias_Data(uint32_t base_address, volatile float *L_2_Bias_Data);
void uz_NN_acc_hw_set_L_3_Bias_Data(uint32_t base_address, volatile float *L_3_Bias_Data);
void uz_NN_acc_hw_set_L_Output_Bias_Data(uint32_t base_address, volatile float *L_Output_Bias_Data);
void uz_NN_acc_hw_set_copy_mats_flag(uint32_t base_address, bool copy_mats_flag);
bool uz_NN_acc_hw_get_copy_mats_flag(uint32_t base_address);
bool uz_NN_acc_hw_get_copy_flag_out(uint32_t base_address);
bool uz_NN_acc_hw_get_matrices_updated_out(uint32_t base_address);
void uz_NN_acc_hw_set_start(uint32_t base_address);
bool uz_NN_acc_hw_get_is_done_output(uint32_t base_address);
#endif