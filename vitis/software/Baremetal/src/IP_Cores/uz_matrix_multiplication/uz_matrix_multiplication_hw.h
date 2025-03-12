#ifndef UZ_MATRIX_MULTIPLICATION_HW_H
#define UZ_MATRIX_MULTIPLICATION_HW_H
#include <stdint.h>
#include <stdbool.h>


void uz_matrix_multiplication_hw_set_A_rows(uint32_t base_address, uint32_t A_rows);
void uz_matrix_multiplication_hw_set_B1_rows(uint32_t base_address, uint32_t B1_rows);
void uz_matrix_multiplication_hw_set_B1_columns(uint32_t base_address, uint32_t B1_columns);
void uz_matrix_multiplication_hw_set_B2_columns(uint32_t base_address, uint32_t B2_columns);
void uz_matrix_multiplication_hw_set_A_matrix(uint32_t base_address, float * A);
void uz_matrix_multiplication_hw_set_B1_matrix(uint32_t base_address, float * B1);
void uz_matrix_multiplication_hw_set_B2_matrix(uint32_t base_address, float * B2);
void uz_matrix_multiplication_hw_set_C_out_matrix(uint32_t base_address, float *C_out);
void uz_matrix_multiplication_hw_set_start(uint32_t base_address, bool flag);
bool uz_matrix_multiplication_hw_get_is_done_output(uint32_t base_address);
bool uz_matrix_multiplication_hw_get_is_idle_output(uint32_t base_address);
//void uz_matrix_multiplication_hw_set_continue(uint32_t base_address);
void uz_matrix_multiplication_hw_set_auto_restart(uint32_t base_address, bool auto_restart);
void uz_matrix_multiplication_hw_set_copy_mats_flag(uint32_t base_address, bool copy_mats_flag);
bool uz_matrix_multiplication_hw_get_copy_mats_flag(uint32_t base_address);
bool uz_matrix_multiplication_hw_get_copy_flag_out(uint32_t base_address);
bool uz_matrix_multiplication_hw_get_matrices_updated_out(uint32_t base_address);
#endif
