#include "uz_matrix_multiplication.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_MATRIX_MULTIPLICATION_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_matrix_multiplication_hw.h"

struct uz_Matrix_Multi_t {
	bool is_ready;
	struct uz_Matrix_Multi_config config;
	uz_matrix_t* A_matrix;
	uz_matrix_t* B_matrix;
	uz_matrix_t* C_out_matrix;
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

uz_Matrix_Multi_t* uz_Matrix_Multi_init(struct uz_Matrix_Multi_config config, uz_matrix_t *A_matrix, uz_matrix_t *B_matrix, uz_matrix_t *C_out_matrix){
	uz_assert_not_zero_uint32(config.base_address);
	uz_Matrix_Multi_t* self = uz_Matrix_Multi_allocation();
	//Current max size allowed for IP-Core
	uz_assert(config.A_columns <= 2U);
	uz_assert(config.A_rows == 1U);
	uz_assert(config.B_columns <= 16U);
	uz_assert(config.C_columns == 1U);
	uz_assert(config.C_rows <= 16U);
	self->config = config;
	self->A_matrix = uz_matrix_init(A_matrix, self->config.A_data, self->config.A_length_of_data, self->config.A_rows, self->config.A_columns);
	self->B_matrix = uz_matrix_init(B_matrix, self->config.B_data, self->config.B_length_of_data, self->config.B_rows, self->config.B_columns);
	self->C_out_matrix = uz_matrix_init(C_out_matrix, self->config.C_data, self->config.C_length_of_data, self->config.C_rows, self->config.C_columns);
	uz_assert_not_zero(self->is_ready);
	uz_assert(self->A_matrix->columns == self->B_matrix->rows);
	uz_assert(self->A_matrix->rows == self->C_out_matrix->columns);
    uz_assert(self->B_matrix->columns == self->C_out_matrix->rows);
	uz_matrix_multiplication_hw_set_A_matrix(self->config.base_address, self->A_matrix->data);
	uz_matrix_multiplication_hw_set_A_rows(self->config.base_address, self->A_matrix->rows);
	uz_matrix_multiplication_hw_set_B_matrix(self->config.base_address, self->B_matrix->data);
	uz_matrix_multiplication_hw_set_B_rows(self->config.base_address, self->B_matrix->rows);
	uz_matrix_multiplication_hw_set_B_columns(self->config.base_address, self->B_matrix->columns);
	uz_matrix_multiplication_hw_set_C_out_matrix(self->config.base_address, self->C_out_matrix->data);
	return(self);
}

void uz_Matrix_Multi_trigger_calculation(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	uz_matrix_multiplication_hw_set_start(self->config.base_address);
}

bool uz_Matrix_Multi_get_done_flag(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	bool is_done = uz_matrix_multiplication_hw_get_is_done_output(self->config.base_address);
	return(is_done);
}

void uz_Matrix_Multi_continue_calculation(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	uz_matrix_multiplication_hw_set_continue(self->config.base_address);
}

#endif
