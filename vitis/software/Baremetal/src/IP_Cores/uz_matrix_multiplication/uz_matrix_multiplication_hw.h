#ifndef UZ_MATRIX_MULTIPLICATION_HW_H
#define UZ_MATRIX_MULTIPLICATION_HW_H
#include <stdint.h>
#include <stdbool.h>


void uz_matrix_multiplication_hw_set_A_rows(uint32_t base_address, uint32_t A_rows);
void uz_matrix_multiplication_hw_set_B_rows(uint32_t base_address, uint32_t B_rows);
void uz_matrix_multiplication_hw_set_B_columns(uint32_t base_address, uint32_t B_columns);
void uz_matrix_multiplication_hw_set_A_matrix(uint32_t base_address, float * A);
void uz_matrix_multiplication_hw_set_B_matrix(uint32_t base_address, float * B);
void uz_matrix_multiplication_hw_read_C_out_matrix(uint32_t base_address, float *C_out);
#endif
