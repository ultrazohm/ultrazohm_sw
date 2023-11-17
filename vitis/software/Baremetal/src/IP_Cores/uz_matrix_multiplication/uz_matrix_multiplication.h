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
	 uint32_t B_length_of_data;
	 uint32_t B_rows;
	 uint32_t B_columns;
	 float *B_data;
	 uint32_t C_length_of_data;
	 uint32_t C_rows;
	 uint32_t C_columns;
	 float *C_data;
};


uz_Matrix_Multi_t* uz_Matrix_Multi_init(struct uz_Matrix_Multi_config config, uz_matrix_t *A_matrix, uz_matrix_t *B_matrix, uz_matrix_t *C_out_matrix);
void uz_Matrix_Multi_write_input(uz_Matrix_Multi_t* self);
void uz_Matrix_Multi_trigger_calculation(uz_Matrix_Multi_t* self);
void uz_Matrix_Multi_read_output(uz_Matrix_Multi_t* self);
bool uz_Matrix_Multi_get_done_flag(uz_Matrix_Multi_t* self);
void uz_Matrix_Multi_reset(uz_Matrix_Multi_t* self);
#endif
