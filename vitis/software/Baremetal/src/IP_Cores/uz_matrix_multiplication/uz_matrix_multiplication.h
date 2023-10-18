#ifndef UZ_MATRIX_MULTIPLICATION_H
#define UZ_MATRIX_MULTIPLICATION_H

#include <stdint.h>
#include <stdbool.h>

typedef struct uz_Matrix_Multi_t uz_Matrix_Multi_t;

struct uz_Matrix_Multi_config{
	 uint32_t base_address;              /**< Base address of the IP-Core */
	 uint32_t A_rows;
	 uint32_t B_rows;
	 uint32_t B_columns;
};


uz_Matrix_Multi_t* uz_Matrix_Multi_init(struct uz_Matrix_Multi_config config);
void uz_Matrix_Multi_set_A_matrix(uz_Matrix_Multi_t* self, float* A);
void uz_Matrix_Multi_set_B_matrix(uz_Matrix_Multi_t* self, float* B);
void uz_Matrix_Multi_get_C_out_matrix(uz_Matrix_Multi_t* self, float* C_out);

#endif
