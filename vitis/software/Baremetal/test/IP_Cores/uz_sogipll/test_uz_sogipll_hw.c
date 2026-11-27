#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h"
#include "uz_sogipll_hw.h"
#include "uz_sogipll_hwAddresses.h"

#define TEST_BASE_ADDRESS 0x40000000U

void setUp(void) {
}

void tearDown(void) {
}

void test_uz_sogipll_hw_write_ipcore_reset(void) {
	TEST_ASSERT_EQUAL_HEX32(0x000U, UZ_SOGIPLL_IPCORE_RESET_OFFSET);
	uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + 0x000U, true);
	uz_sogipll_hw_write_ipcore_reset(TEST_BASE_ADDRESS, true);
	uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + 0x000U, false);
	uz_sogipll_hw_write_ipcore_reset(TEST_BASE_ADDRESS, false);
}

void test_uz_sogipll_hw_write_ipcore_reset_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_ipcore_reset(0U, true));
}

void test_uz_sogipll_hw_write_ipcore_enable(void) {
	TEST_ASSERT_EQUAL_HEX32(0x004U, UZ_SOGIPLL_IPCORE_ENABLE_OFFSET);
	uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + 0x004U, true);
	uz_sogipll_hw_write_ipcore_enable(TEST_BASE_ADDRESS, true);
	uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + 0x004U, false);
	uz_sogipll_hw_write_ipcore_enable(TEST_BASE_ADDRESS, false);
}

void test_uz_sogipll_hw_write_ipcore_enable_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_ipcore_enable(0U, true));
}

void test_uz_sogipll_hw_read_ipcore_timestamp(void) {
	TEST_ASSERT_EQUAL_HEX32(0x008U, UZ_SOGIPLL_IPCORE_TIMESTAMP_OFFSET);
	uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + 0x008U, 2611271204U);
	TEST_ASSERT_EQUAL_UINT32(2611271204U, uz_sogipll_hw_read_ipcore_timestamp(TEST_BASE_ADDRESS));
}

void test_uz_sogipll_hw_read_ipcore_timestamp_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_ipcore_timestamp(0U));
}

void test_uz_sogipll_hw_write_in_rst(void) {
	TEST_ASSERT_EQUAL_HEX32(0x100U, UZ_SOGIPLL_IN_RST_OFFSET);
	uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + 0x100U, true);
	uz_sogipll_hw_write_in_rst(TEST_BASE_ADDRESS, true);
	uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + 0x100U, false);
	uz_sogipll_hw_write_in_rst(TEST_BASE_ADDRESS, false);
}

void test_uz_sogipll_hw_write_in_rst_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_rst(0U, true));
}

void test_uz_sogipll_hw_write_in_v(void) {
	TEST_ASSERT_EQUAL_HEX32(0x104U, UZ_SOGIPLL_IN_V_OFFSET);
	uz_axi_write_float_Expect(TEST_BASE_ADDRESS + 0x104U, -230.5f);
	uz_sogipll_hw_write_in_v(TEST_BASE_ADDRESS, -230.5f);
}

void test_uz_sogipll_hw_write_in_v_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_v(0U, -230.5f));
}

void test_uz_sogipll_hw_write_in_omega_ff(void) {
	TEST_ASSERT_EQUAL_HEX32(0x108U, UZ_SOGIPLL_IN_OMEGA_FF_OFFSET);
	uz_axi_write_float_Expect(TEST_BASE_ADDRESS + 0x108U, 314.159f);
	uz_sogipll_hw_write_in_omega_ff(TEST_BASE_ADDRESS, 314.159f);
}

void test_uz_sogipll_hw_write_in_omega_ff_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_omega_ff(0U, 314.159f));
}

void test_uz_sogipll_hw_write_in_k(void) {
	TEST_ASSERT_EQUAL_HEX32(0x10CU, UZ_SOGIPLL_IN_K_OFFSET);
	uz_axi_write_float_Expect(TEST_BASE_ADDRESS + 0x10CU, 1.414f);
	uz_sogipll_hw_write_in_k(TEST_BASE_ADDRESS, 1.414f);
}

void test_uz_sogipll_hw_write_in_k_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_k(0U, 1.414f));
}

void test_uz_sogipll_hw_write_in_kp(void) {
	TEST_ASSERT_EQUAL_HEX32(0x110U, UZ_SOGIPLL_IN_KP_OFFSET);
	uz_axi_write_float_Expect(TEST_BASE_ADDRESS + 0x110U, 2.5f);
	uz_sogipll_hw_write_in_kp(TEST_BASE_ADDRESS, 2.5f);
}

void test_uz_sogipll_hw_write_in_kp_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_kp(0U, 2.5f));
}

void test_uz_sogipll_hw_write_in_ki(void) {
	TEST_ASSERT_EQUAL_HEX32(0x114U, UZ_SOGIPLL_IN_KI_OFFSET);
	uz_axi_write_float_Expect(TEST_BASE_ADDRESS + 0x114U, 12.5f);
	uz_sogipll_hw_write_in_ki(TEST_BASE_ADDRESS, 12.5f);
}

void test_uz_sogipll_hw_write_in_ki_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_ki(0U, 12.5f));
}

void test_uz_sogipll_hw_write_in_t_sample(void) {
	TEST_ASSERT_EQUAL_HEX32(0x118U, UZ_SOGIPLL_IN_T_SAMPLE_OFFSET);
	uz_axi_write_float_Expect(TEST_BASE_ADDRESS + 0x118U, 0.0001f);
	uz_sogipll_hw_write_in_t_sample(TEST_BASE_ADDRESS, 0.0001f);
}

void test_uz_sogipll_hw_write_in_t_sample_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_t_sample(0U, 0.0001f));
}

void test_uz_sogipll_hw_write_in_v_scaling(void) {
	TEST_ASSERT_EQUAL_HEX32(0x11CU, UZ_SOGIPLL_IN_V_SCALING_OFFSET);
	uz_axi_write_float_Expect(TEST_BASE_ADDRESS + 0x11CU, 0.01f);
	uz_sogipll_hw_write_in_v_scaling(TEST_BASE_ADDRESS, 0.01f);
}

void test_uz_sogipll_hw_write_in_v_scaling_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_v_scaling(0U, 0.01f));
}

void test_uz_sogipll_hw_read_out_v_est(void) {
	TEST_ASSERT_EQUAL_HEX32(0x120U, UZ_SOGIPLL_OUT_V_EST_OFFSET);
	uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + 0x120U, -0.75f);
	TEST_ASSERT_EQUAL_FLOAT(-0.75f, uz_sogipll_hw_read_out_v_est(TEST_BASE_ADDRESS));
}

void test_uz_sogipll_hw_read_out_v_est_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_v_est(0U));
}

void test_uz_sogipll_hw_read_out_qv_est(void) {
	TEST_ASSERT_EQUAL_HEX32(0x124U, UZ_SOGIPLL_OUT_QV_EST_OFFSET);
	uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + 0x124U, 0.25f);
	TEST_ASSERT_EQUAL_FLOAT(0.25f, uz_sogipll_hw_read_out_qv_est(TEST_BASE_ADDRESS));
}

void test_uz_sogipll_hw_read_out_qv_est_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_qv_est(0U));
}

void test_uz_sogipll_hw_read_out_v_d(void) {
	TEST_ASSERT_EQUAL_HEX32(0x128U, UZ_SOGIPLL_OUT_V_D_OFFSET);
	uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + 0x128U, 0.9f);
	TEST_ASSERT_EQUAL_FLOAT(0.9f, uz_sogipll_hw_read_out_v_d(TEST_BASE_ADDRESS));
}

void test_uz_sogipll_hw_read_out_v_d_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_v_d(0U));
}

void test_uz_sogipll_hw_read_out_v_q(void) {
	TEST_ASSERT_EQUAL_HEX32(0x12CU, UZ_SOGIPLL_OUT_V_Q_OFFSET);
	uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + 0x12CU, -0.125f);
	TEST_ASSERT_EQUAL_FLOAT(-0.125f, uz_sogipll_hw_read_out_v_q(TEST_BASE_ADDRESS));
}

void test_uz_sogipll_hw_read_out_v_q_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_v_q(0U));
}

void test_uz_sogipll_hw_read_out_theta_est(void) {
	TEST_ASSERT_EQUAL_HEX32(0x130U, UZ_SOGIPLL_OUT_THETA_EST_OFFSET);
	uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + 0x130U, 1.57f);
	TEST_ASSERT_EQUAL_FLOAT(1.57f, uz_sogipll_hw_read_out_theta_est(TEST_BASE_ADDRESS));
}

void test_uz_sogipll_hw_read_out_theta_est_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_theta_est(0U));
}

void test_uz_sogipll_hw_read_out_omega_est(void) {
	TEST_ASSERT_EQUAL_HEX32(0x134U, UZ_SOGIPLL_OUT_OMEGA_EST_OFFSET);
	uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + 0x134U, 313.5f);
	TEST_ASSERT_EQUAL_FLOAT(313.5f, uz_sogipll_hw_read_out_omega_est(TEST_BASE_ADDRESS));
}

void test_uz_sogipll_hw_read_out_omega_est_rejects_zero_base_address(void) {
	TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_omega_est(0U));
}

#endif // TEST
