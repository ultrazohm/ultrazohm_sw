#include "uz_matrix_multiplication_hw.h"
#include "uz_matrix_multiplication_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

#define REGISTER_OFFSET (XMATRIXMULTIPLICATION_CONTROL_WIDTH_A / 8U)

void uz_matrix_multiplication_hw_set_A_rows(uint32_t base_address, uint32_t A_rows) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_ROWS_DATA, A_rows);
}

void uz_matrix_multiplication_hw_set_B_rows(uint32_t base_address, uint32_t B_rows) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_ROWS_DATA, B_rows);
}

void uz_matrix_multiplication_hw_set_B_columns(uint32_t base_address, uint32_t B_column) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_COLUMNS_DATA, B_column);
}

void uz_matrix_multiplication_hw_set_A_matrix(uint32_t base_address, float * A) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(A);
	uint32_t* pointer = (uint32_t*)A;
	uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_A_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_B_matrix(uint32_t base_address, float * B) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(B);
	uint32_t* pointer = (uint32_t*)B;
	uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_B_INPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_C_out_matrix(uint32_t base_address, float *C_out) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(C_out);
	uint32_t* pointer = (uint32_t*)C_out;
	uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_C_OUTPUT_DATA, address);
}

void uz_matrix_multiplication_hw_set_start(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	uint32_t status = (uz_axi_read_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL) & 0x80);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL, (status | 0x01U));
}

bool uz_matrix_multiplication_hw_get_is_done_output(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool is_done = (uz_axi_read_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL)>> 1U )& 0x1U;
	return (is_done);
}

void uz_matrix_multiplication_hw_set_continue(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	uint32_t status = (uz_axi_read_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL) & 0x80);
	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL, (status | 0x10U));

}
