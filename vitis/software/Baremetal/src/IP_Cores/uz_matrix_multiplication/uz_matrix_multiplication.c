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
	uz_matrix_t* B1_matrix;
	uz_matrix_t* B2_matrix;
	uz_matrix_t* C_out_matrix;
	bool copy_mats_flag;
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

uz_Matrix_Multi_t* uz_Matrix_Multi_init(struct uz_Matrix_Multi_config config, uz_matrix_t *A_matrix, uz_matrix_t *B1_matrix, uz_matrix_t *B2_matrix, uz_matrix_t *C_out_matrix){
	uz_assert_not_zero_uint32(config.base_address);
	uz_Matrix_Multi_t* self = uz_Matrix_Multi_allocation();
	//Current max size allowed for IP-Core
	uz_assert(config.A_columns <= 20U);
	uz_assert(config.A_rows == 1U);
	uz_assert(config.B1_columns <= 64U);
	uz_assert(config.B1_rows <= 20U);
	uz_assert(config.B2_columns <= 4U);
	uz_assert(config.B2_rows <= 64U);
	uz_assert(config.C_columns == 4U);
	uz_assert(config.C_rows <= 1U);
	self->config = config;
	self->A_matrix = uz_matrix_init(A_matrix, self->config.A_data, self->config.A_length_of_data, self->config.A_rows, self->config.A_columns);
	self->B1_matrix = uz_matrix_init(B1_matrix, self->config.B1_data, self->config.B1_length_of_data, self->config.B1_rows, self->config.B1_columns);
	self->B2_matrix = uz_matrix_init(B2_matrix, self->config.B2_data, self->config.B2_length_of_data, self->config.B2_rows, self->config.B2_columns);
	self->C_out_matrix = uz_matrix_init(C_out_matrix, self->config.C_data, self->config.C_length_of_data, self->config.C_rows, self->config.C_columns);
	uz_assert_not_zero(self->is_ready);
	uz_assert(self->A_matrix->columns == self->B1_matrix->rows);
    uz_assert(self->B1_matrix->columns == self->B2_matrix->rows);
    uz_assert(self->B2_matrix->columns == self->C_out_matrix->columns);
    uz_assert(self->A_matrix->rows == self->C_out_matrix->rows);
	uz_matrix_multiplication_hw_set_A_matrix(self->config.base_address, self->A_matrix->data);
	uz_matrix_multiplication_hw_set_A_rows(self->config.base_address, self->A_matrix->rows);
	uz_matrix_multiplication_hw_set_B1_matrix(self->config.base_address, self->B1_matrix->data);
	uz_matrix_multiplication_hw_set_B1_rows(self->config.base_address, self->B1_matrix->rows);
	uz_matrix_multiplication_hw_set_B1_columns(self->config.base_address, self->B1_matrix->columns);
	uz_matrix_multiplication_hw_set_B2_matrix(self->config.base_address, self->B2_matrix->data);
	uz_matrix_multiplication_hw_set_B2_columns(self->config.base_address, self->B2_matrix->columns);
	uz_matrix_multiplication_hw_set_C_out_matrix(self->config.base_address, self->C_out_matrix->data);
	self->copy_mats_flag = true;
	uz_matrix_multiplication_hw_set_copy_mats_flag(self->config.base_address, self->copy_mats_flag);
	uz_matrix_multiplication_hw_set_start(self->config.base_address, true);
	while(1) {
		bool copy_flag_out = uz_matrix_multiplication_hw_get_copy_flag_out(self->config.base_address);
		bool matrices_updated_out = uz_matrix_multiplication_hw_get_matrices_updated_out(self->config.base_address);
				if(matrices_updated_out && copy_flag_out) {
					break;
				}
	}
//	self->copy_mats_flag = false;
//	uz_matrix_multiplication_hw_set_copy_mats_flag(self->config.base_address, false);
	//uz_matrix_multiplication_hw_set_start(self->config.base_address, true);
	return(self);
}

void uz_Matrix_Multi_trigger_calculation(uz_Matrix_Multi_t* self, bool flag) {
	uz_assert_not_NULL(self);
	uz_matrix_multiplication_hw_set_start(self->config.base_address, flag);
}


bool uz_Matrix_Multi_get_done_flag(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	bool is_done = uz_matrix_multiplication_hw_get_is_done_output(self->config.base_address);
	return(is_done);
}

bool uz_Matrix_Multi_get_idle_flag(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	bool is_idle = uz_matrix_multiplication_hw_get_is_idle_output(self->config.base_address);
	return(is_idle);
}

void uz_Matrix_Multi_continue_calculation(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	uz_matrix_multiplication_hw_set_continue(self->config.base_address);
}

void uz_Matrix_Multi_set_auto_restart(uz_Matrix_Multi_t* self, bool auto_restart) {
	uz_assert_not_NULL(self);
	uz_matrix_multiplication_hw_set_auto_restart(self->config.base_address, auto_restart);
}

void uz_Matrix_Multi_set_copy_mats_flag(uz_Matrix_Multi_t* self, bool copy_mats_flag) {
	uz_assert_not_NULL(self);
	self->copy_mats_flag = copy_mats_flag;
	uz_matrix_multiplication_hw_set_copy_mats_flag(self->config.base_address, self->copy_mats_flag);
}

bool uz_Matrix_Multi_get_copy_mats_flag(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	bool copy_mats_flag = uz_matrix_multiplication_hw_get_copy_flag_out(self->config.base_address);
	return(copy_mats_flag);
}

bool uz_Matrix_Multi_get_copy_flag_out(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	bool copy_flag_out = uz_matrix_multiplication_hw_get_copy_flag_out(self->config.base_address);
	return(copy_flag_out);
}
bool uz_Matrix_Multi_get_matrices_updated_out(uz_Matrix_Multi_t* self) {
	uz_assert_not_NULL(self);
	bool matrices_updated_out = uz_matrix_multiplication_hw_get_matrices_updated_out(self->config.base_address);
	return(matrices_updated_out);
}

#endif
