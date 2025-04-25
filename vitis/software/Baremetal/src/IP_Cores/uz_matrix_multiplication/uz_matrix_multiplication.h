#ifndef UZ_MATRIX_MULTIPLICATION_H
#define UZ_MATRIX_MULTIPLICATION_H

#include <stdint.h>
#include <stdbool.h>
#include "../../uz/uz_matrix/uz_matrix.h"

typedef struct uz_Matrix_Multi_t uz_Matrix_Multi_t;

struct uz_Matrix_Multi_config{
	 uint32_t base_address;              /**< Base address of the IP-Core */
	 uint32_t A_length_of_data;
	 uint32_t A_rows;
	 uint32_t A_columns;
	 volatile float *A_data;
	 uint32_t B1_length_of_data;
	 uint32_t B1_rows;
	 uint32_t B1_columns;
	 volatile float *B1_data;
	 uint32_t B2_length_of_data;
	 uint32_t B2_rows;
	 uint32_t B2_columns;
	 volatile float *B2_data;
	 uint32_t B3_length_of_data;
	 uint32_t B3_rows;
	 uint32_t B3_columns;
	 volatile float *B3_data;
	 uint32_t B4_length_of_data;
	 uint32_t B4_rows;
	 uint32_t B4_columns;
	 volatile float *B4_data;
	 uint32_t C_length_of_data;
	 uint32_t C_rows;
	 uint32_t C_columns;
	 volatile float *C_data;
	 volatile float *Bias1_data;
	 volatile float *Bias2_data;
	 volatile float *Bias3_data;
	 volatile float *Bias4_data;
};


uz_Matrix_Multi_t* uz_Matrix_Multi_init(struct uz_Matrix_Multi_config config);
void uz_Matrix_Multi_trigger_calculation(uz_Matrix_Multi_t* self, bool flag);
bool uz_Matrix_Multi_get_done_flag(uz_Matrix_Multi_t* self);
bool uz_Matrix_Multi_get_idle_flag(uz_Matrix_Multi_t* self);
void uz_Matrix_Multi_set_auto_restart(uz_Matrix_Multi_t* self, bool auto_restart);
void uz_Matrix_Multi_set_copy_mats_flag(uz_Matrix_Multi_t* self, bool copy_mats_flag);
bool uz_Matrix_Multi_get_copy_mats_flag(uz_Matrix_Multi_t* self);
bool uz_Matrix_Multi_get_copy_flag_out(uz_Matrix_Multi_t* self);
bool uz_Matrix_Multi_get_matrices_updated_out(uz_Matrix_Multi_t* self);
#endif
