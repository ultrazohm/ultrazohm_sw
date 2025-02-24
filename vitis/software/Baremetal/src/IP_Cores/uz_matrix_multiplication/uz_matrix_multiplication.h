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
	 float *A_data;
	 uint32_t B1_length_of_data;
	 uint32_t B1_rows;
	 uint32_t B1_columns;
	 float *B1_data;
	 uint32_t B2_length_of_data;
	 uint32_t B2_rows;
	 uint32_t B2_columns;
	 float *B2_data;
	 uint32_t C_length_of_data;
	 uint32_t C_rows;
	 uint32_t C_columns;
	 float *C_data;
};


uz_Matrix_Multi_t* uz_Matrix_Multi_init(struct uz_Matrix_Multi_config config, uz_matrix_t *A_matrix, uz_matrix_t *B1_matrix, uz_matrix_t *B2_matrix, uz_matrix_t *C_out_matrix);
void uz_Matrix_Multi_trigger_calculation(uz_Matrix_Multi_t* self, bool flag);
bool uz_Matrix_Multi_get_done_flag(uz_Matrix_Multi_t* self);
bool uz_Matrix_Multi_get_idle_flag(uz_Matrix_Multi_t* self);
void uz_Matrix_Multi_continue_calculation(uz_Matrix_Multi_t* self);
void uz_Matrix_Multi_set_auto_restart(uz_Matrix_Multi_t* self, bool auto_restart);
#endif
