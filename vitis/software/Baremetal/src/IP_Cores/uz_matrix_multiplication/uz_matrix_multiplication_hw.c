#include "uz_matrix_multiplication_hw.h"
#include "uz_matrix_multiplication_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

#define REGISTER_OFFSET (XMATRIXMULTIPLICATION_CONTROL_WIDTH_A / 8U)

void uz_matrix_multiplication_hw_set_A_rows(uint32_t base_address, uint32_t A_rows) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert(A_rows <= XMATRIXMULTIPLICATION_CONTROL_DEPTH_A);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA, A_rows);
}

void uz_matrix_multiplication_hw_set_B_rows(uint32_t base_address, uint32_t B_rows) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert(B_rows <= XMATRIXMULTIPLICATION_CONTROL_DEPTH_B);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA, B_rows);
}

void uz_matrix_multiplication_hw_set_B_columns(uint32_t base_address, uint32_t B_column) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert(B_column <= XMATRIXMULTIPLICATION_CONTROL_DEPTH_B);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA, B_column);
}

void uz_matrix_multiplication_hw_set_A_matrix(uint32_t base_address, float * A) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(A);
	for (uint32_t i=0U; i < 5U; i++) {
		uz_axi_write_float(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_BASE + REGISTER_OFFSET * i, A[i]);
	}
}

void uz_matrix_multiplication_hw_set_B_matrix(uint32_t base_address, float * B) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(B);
	for (uint32_t i=0U; i < 25U; i++) {
		uz_axi_write_float(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_BASE + REGISTER_OFFSET * i, B[i]);
	}
}

void uz_matrix_multiplication_hw_read_C_out_matrix(uint32_t base_address, float *C_out) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(C_out);
	for (uint32_t i=0U; i < 5U; i++) {
			C_out[i] = uz_axi_read_float(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUT_BASE + REGISTER_OFFSET * i );
	}
}

void uz_matrix_multiplication_hw_set_trigger_calculation(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_TRIGGER_DATA, true);
}

bool uz_matrix_multiplication_hw_get_is_done(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_bool(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_IS_DONE_I_DATA));
}
