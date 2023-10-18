#include "uz_matrix_multiplication.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_MATRIX_MULTIPLICATION_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_matrix_multiplication_hw.h"

struct uz_Matrix_Multi_t {
	bool is_ready;
	struct uz_Matrix_Multi_config config;
};

static uint32_t instance_counter = 0U;
static uz_Matrix_Multi_t instances[UZ_MATRIX_MULTIPLICATION_MAX_INSTANCES] = { 0 };

static uz_Matrix_Multi_t* uz_Matrix_Multi_allocation(void);

static uz_Matrix_Multi_t*uz_Matrix_Multi_allocation(void){
    uz_assert(instance_counter < UZ_MATRIX_MULTIPLICATION_MAX_INSTANCES);
    uz_Matrix_Multi_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_Matrix_Multi_t* uz_Matrix_Multi_init(struct uz_Matrix_Multi_config config){
	uz_assert_not_zero_uint32(config.base_address);
	 uz_Matrix_Multi_t* self = uz_Matrix_Multi_allocation();
	 //assertion for max array size
	 self->config=config;
	 uz_assert_not_zero(self->is_ready);
	 return(self);
}

void uz_Matrix_Multi_set_A_matrix(uz_Matrix_Multi_t* self, float* A) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(A);
	uz_matrix_multiplication_hw_set_A_rows(self->config.base_address, self->config.A_rows);
	uz_matrix_multiplication_hw_set_A_matrix(self->config.base_address, A);
}

void uz_Matrix_Multi_set_B_matrix(uz_Matrix_Multi_t* self, float* B) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(B);
	uz_matrix_multiplication_hw_set_B_rows(self->config.base_address, self->config.A_rows);
	uz_matrix_multiplication_hw_set_B_columns(self->config.base_address, self->config.B_columns);
	uz_matrix_multiplication_hw_set_B_matrix(self->config.base_address, B);
}

void uz_Matrix_Multi_get_C_out_matrix(uz_Matrix_Multi_t* self, float* C_out) {
	uz_assert_not_NULL(self);
	uz_assert_not_NULL(C_out);
	uz_matrix_multiplication_hw_read_C_out_matrix(self->config.base_address, C_out);
}
#endif
