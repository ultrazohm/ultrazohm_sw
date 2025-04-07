#include "xup_MatrixMulti_hw.h"
#include "xup_MatrixMulti_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

#define REGISTER_OFFSET (XMATRIXMULTIPLICATION_CONTROL_WIDTH_A / 8U)

void xup_MatrixMulti_hw_set_In1_matrix(uint32_t base_address, int * In1) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(In1);
	uint32_t* pointer = (uint32_t*)In1;
	uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XMMULT_HW_CTRL_ADDR_IN1_DATA, address);
}

void xup_MatrixMulti_hw_set_In2_matrix(uint32_t base_address, int * In2) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(In2);
	uint32_t* pointer = (uint32_t*)In2;
	uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XMMULT_HW_CTRL_ADDR_IN2_DATA, address);
}

void xup_MatrixMulti_hw_set_out_matrix(uint32_t base_address, float *out) {
	uz_assert_not_zero_uint32(base_address);
	uz_assert_not_NULL(out);
	uint32_t* pointer = (uint32_t*)out;
	uint32_t address = (uint32_t)pointer;
	uz_axi_write_uint32(base_address + XMMULT_HW_CTRL_ADDR_OUT_R_DATA, address);
}


void xup_MatrixMulti_hw_set_start(uint32_t base_address, bool flag) {
	uz_assert_not_zero_uint32(base_address);
	if(flag) {
		uint32_t status = (uz_axi_read_uint32(base_address + XMMULT_HW_CTRL_ADDR_AP_CTRL) & 0x80);
		uz_axi_write_uint32(base_address + XMMULT_HW_CTRL_ADDR_AP_CTRL, (status | 0x01U));
	} else {
		uz_axi_write_uint32(base_address + XMMULT_HW_CTRL_ADDR_AP_CTRL, 0x00U);
	}

}

bool xup_MatrixMulti_hw_get_is_done_output(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool is_done = (uz_axi_read_uint32(base_address + XMMULT_HW_CTRL_ADDR_AP_CTRL)>> 1U )& 0x1U;
	return (is_done);
}

bool xup_MatrixMulti_hw_get_is_idle_output(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	bool is_done = (uz_axi_read_uint32(base_address + XMMULT_HW_CTRL_ADDR_AP_CTRL)>> 2U )& 0x1U;
	return (is_done);
}

//void xup_MatrixMulti_hw_set_continue(uint32_t base_address) {
//	uz_assert_not_zero_uint32(base_address);
//	uint32_t status = (uz_axi_read_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL) & 0x80);
//	uz_axi_write_uint32(base_address + XMATRIXMULTIPLICATION_CONTROL_ADDR_AP_CTRL, (status | 0x10U));
//
//}

void xup_MatrixMulti_hw_set_auto_restart(uint32_t base_address, bool auto_restart) {
	uz_assert_not_zero_uint32(base_address);
	if (auto_restart) {
		uz_axi_write_uint32(base_address + XMMULT_HW_CTRL_ADDR_AP_CTRL, 0x80U);
	} else {
		uz_axi_write_uint32(base_address + XMMULT_HW_CTRL_ADDR_AP_CTRL, 0x0U);
	}
}
