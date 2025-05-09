#ifndef UZ_MATRIX_MULTIPLICATION_HW_H
#define UZ_MATRIX_MULTIPLICATION_HW_H
#include <stdint.h>
#include <stdbool.h>


void uz_matrix_multiplication_hw_set_Observation_size(uint32_t base_address, uint32_t Observation_size);
void uz_matrix_multiplication_hw_set_Action_size(uint32_t base_address, uint32_t Action_size);
void uz_matrix_multiplication_hw_set_A_matrix(uint32_t base_address, volatile float * A);
void uz_matrix_multiplication_hw_set_B1_matrix(uint32_t base_address, volatile float * B1);
void uz_matrix_multiplication_hw_set_B2_matrix(uint32_t base_address, volatile float * B2);
void uz_matrix_multiplication_hw_set_B3_matrix(uint32_t base_address, volatile float * B3);
void uz_matrix_multiplication_hw_set_B4_matrix(uint32_t base_address, volatile float * B4);
void uz_matrix_multiplication_hw_set_Bias1_matrix(uint32_t base_address, volatile float * Bias1);
void uz_matrix_multiplication_hw_set_Bias2_matrix(uint32_t base_address, volatile float * Bias2);
void uz_matrix_multiplication_hw_set_Bias3_matrix(uint32_t base_address, volatile float * Bias3);
void uz_matrix_multiplication_hw_set_Bias4_matrix(uint32_t base_address, volatile float * Bias4);
void uz_matrix_multiplication_hw_set_C_out_matrix(uint32_t base_address, volatile float *C_out);
void uz_matrix_multiplication_hw_set_start(uint32_t base_address, bool flag);
bool uz_matrix_multiplication_hw_get_is_done_output(uint32_t base_address);
bool uz_matrix_multiplication_hw_get_is_idle_output(uint32_t base_address);
void uz_matrix_multiplication_hw_set_auto_restart(uint32_t base_address, bool auto_restart);
void uz_matrix_multiplication_hw_set_copy_mats_flag(uint32_t base_address, bool copy_mats_flag);
bool uz_matrix_multiplication_hw_get_copy_mats_flag(uint32_t base_address);
bool uz_matrix_multiplication_hw_get_copy_flag_out(uint32_t base_address);
bool uz_matrix_multiplication_hw_get_matrices_updated_out(uint32_t base_address);
#endif
