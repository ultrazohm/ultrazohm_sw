#include "uz_sogipll_hw.h"
#include "uz_sogipll_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_sogipll_hw_write_ipcore_reset(uint32_t base_address, bool value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + UZ_SOGIPLL_IPCORE_RESET_OFFSET, value);
}

void uz_sogipll_hw_write_ipcore_enable(uint32_t base_address, bool value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + UZ_SOGIPLL_IPCORE_ENABLE_OFFSET, value);
}

uint32_t uz_sogipll_hw_read_ipcore_timestamp(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_uint32(base_address + UZ_SOGIPLL_IPCORE_TIMESTAMP_OFFSET));
}

void uz_sogipll_hw_write_in_rst(uint32_t base_address, bool value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_bool(base_address + UZ_SOGIPLL_IN_RST_OFFSET, value);
}

void uz_sogipll_hw_write_in_v(uint32_t base_address, float value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + UZ_SOGIPLL_IN_V_OFFSET, value);
}

void uz_sogipll_hw_write_in_omega_ff(uint32_t base_address, float value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + UZ_SOGIPLL_IN_OMEGA_FF_OFFSET, value);
}

void uz_sogipll_hw_write_in_k(uint32_t base_address, float value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + UZ_SOGIPLL_IN_K_OFFSET, value);
}

void uz_sogipll_hw_write_in_kp(uint32_t base_address, float value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + UZ_SOGIPLL_IN_KP_OFFSET, value);
}

void uz_sogipll_hw_write_in_ki(uint32_t base_address, float value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + UZ_SOGIPLL_IN_KI_OFFSET, value);
}

void uz_sogipll_hw_write_in_t_sample(uint32_t base_address, float value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + UZ_SOGIPLL_IN_T_SAMPLE_OFFSET, value);
}

void uz_sogipll_hw_write_in_v_scaling(uint32_t base_address, float value) {
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_float(base_address + UZ_SOGIPLL_IN_V_SCALING_OFFSET, value);
}

float uz_sogipll_hw_read_out_v_est(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_float(base_address + UZ_SOGIPLL_OUT_V_EST_OFFSET));
}

float uz_sogipll_hw_read_out_qv_est(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_float(base_address + UZ_SOGIPLL_OUT_QV_EST_OFFSET));
}

float uz_sogipll_hw_read_out_v_d(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_float(base_address + UZ_SOGIPLL_OUT_V_D_OFFSET));
}

float uz_sogipll_hw_read_out_v_q(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_float(base_address + UZ_SOGIPLL_OUT_V_Q_OFFSET));
}

float uz_sogipll_hw_read_out_theta_est(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_float(base_address + UZ_SOGIPLL_OUT_THETA_EST_OFFSET));
}

float uz_sogipll_hw_read_out_omega_est(uint32_t base_address) {
	uz_assert_not_zero_uint32(base_address);
	return (uz_axi_read_float(base_address + UZ_SOGIPLL_OUT_OMEGA_EST_OFFSET));
}
