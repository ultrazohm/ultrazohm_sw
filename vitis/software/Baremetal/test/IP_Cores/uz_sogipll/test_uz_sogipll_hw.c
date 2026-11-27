#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h"
#include "uz_sogipll_hw.h"
#include "uz_sogipll_hwAddresses.h"

#define TEST_BASE_ADDRESS 0x40000000U

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_sogipll_hw_write_ipcore_reset_true(void)
{
    bool value = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IPCORE_RESET_OFFSET, value);
    uz_sogipll_hw_write_ipcore_reset(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_ipcore_reset_false(void)
{
    bool value = false;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IPCORE_RESET_OFFSET, value);
    uz_sogipll_hw_write_ipcore_reset(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_ipcore_reset_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_ipcore_reset(0U, true));
}

void test_uz_sogipll_hw_write_ipcore_enable_true(void)
{
    bool value = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IPCORE_ENABLE_OFFSET, value);
    uz_sogipll_hw_write_ipcore_enable(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_ipcore_enable_false(void)
{
    bool value = false;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IPCORE_ENABLE_OFFSET, value);
    uz_sogipll_hw_write_ipcore_enable(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_ipcore_enable_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_ipcore_enable(0U, true));
}

void test_uz_sogipll_hw_read_ipcore_timestamp(void)
{
    uint32_t expected_value = 2611271204U;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS + UZ_SOGIPLL_IPCORE_TIMESTAMP_OFFSET, expected_value);
    uint32_t actual_value = uz_sogipll_hw_read_ipcore_timestamp(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_UINT32(expected_value, actual_value);
}

void test_uz_sogipll_hw_read_ipcore_timestamp_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_ipcore_timestamp(0U));
}

void test_uz_sogipll_hw_write_in_rst_true(void)
{
    bool value = true;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_RST_OFFSET, value);
    uz_sogipll_hw_write_in_rst(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_rst_false(void)
{
    bool value = false;
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_RST_OFFSET, value);
    uz_sogipll_hw_write_in_rst(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_rst_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_rst(0U, true));
}

void test_uz_sogipll_hw_write_in_v(void)
{
    float value = -230.5f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_V_OFFSET, value);
    uz_sogipll_hw_write_in_v(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_v_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_v(0U, -230.5f));
}

void test_uz_sogipll_hw_write_in_omega_ff(void)
{
    float value = 314.159f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_OMEGA_FF_OFFSET, value);
    uz_sogipll_hw_write_in_omega_ff(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_omega_ff_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_omega_ff(0U, 314.159f));
}

void test_uz_sogipll_hw_write_in_k(void)
{
    float value = 1.414f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_K_OFFSET, value);
    uz_sogipll_hw_write_in_k(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_k_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_k(0U, 1.414f));
}

void test_uz_sogipll_hw_write_in_kp(void)
{
    float value = 2.5f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_KP_OFFSET, value);
    uz_sogipll_hw_write_in_kp(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_kp_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_kp(0U, 2.5f));
}

void test_uz_sogipll_hw_write_in_ki(void)
{
    float value = 12.5f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_KI_OFFSET, value);
    uz_sogipll_hw_write_in_ki(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_ki_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_ki(0U, 12.5f));
}

void test_uz_sogipll_hw_write_in_t_sample(void)
{
    float value = 0.0001f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_T_SAMPLE_OFFSET, value);
    uz_sogipll_hw_write_in_t_sample(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_t_sample_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_t_sample(0U, 0.0001f));
}

void test_uz_sogipll_hw_write_in_v_scaling(void)
{
    float value = 0.01f;
    uz_axi_write_float_Expect(TEST_BASE_ADDRESS + UZ_SOGIPLL_IN_V_SCALING_OFFSET, value);
    uz_sogipll_hw_write_in_v_scaling(TEST_BASE_ADDRESS, value);
}

void test_uz_sogipll_hw_write_in_v_scaling_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_write_in_v_scaling(0U, 0.01f));
}

void test_uz_sogipll_hw_read_out_v_est(void)
{
    float expected_value = -0.75f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + UZ_SOGIPLL_OUT_V_EST_OFFSET, expected_value);
    float actual_value = uz_sogipll_hw_read_out_v_est(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
}

void test_uz_sogipll_hw_read_out_v_est_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_v_est(0U));
}

void test_uz_sogipll_hw_read_out_qv_est(void)
{
    float expected_value = 0.25f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + UZ_SOGIPLL_OUT_QV_EST_OFFSET, expected_value);
    float actual_value = uz_sogipll_hw_read_out_qv_est(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
}

void test_uz_sogipll_hw_read_out_qv_est_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_qv_est(0U));
}

void test_uz_sogipll_hw_read_out_v_d(void)
{
    float expected_value = 0.9f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + UZ_SOGIPLL_OUT_V_D_OFFSET, expected_value);
    float actual_value = uz_sogipll_hw_read_out_v_d(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
}

void test_uz_sogipll_hw_read_out_v_d_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_v_d(0U));
}

void test_uz_sogipll_hw_read_out_v_q(void)
{
    float expected_value = -0.125f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + UZ_SOGIPLL_OUT_V_Q_OFFSET, expected_value);
    float actual_value = uz_sogipll_hw_read_out_v_q(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
}

void test_uz_sogipll_hw_read_out_v_q_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_v_q(0U));
}

void test_uz_sogipll_hw_read_out_theta_est(void)
{
    float expected_value = 1.57f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + UZ_SOGIPLL_OUT_THETA_EST_OFFSET, expected_value);
    float actual_value = uz_sogipll_hw_read_out_theta_est(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
}

void test_uz_sogipll_hw_read_out_theta_est_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_theta_est(0U));
}

void test_uz_sogipll_hw_read_out_omega_est(void)
{
    float expected_value = 313.5f;
    uz_axi_read_float_ExpectAndReturn(TEST_BASE_ADDRESS + UZ_SOGIPLL_OUT_OMEGA_EST_OFFSET, expected_value);
    float actual_value = uz_sogipll_hw_read_out_omega_est(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expected_value, actual_value);
}

void test_uz_sogipll_hw_read_out_omega_est_rejects_zero_base_address(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_hw_read_out_omega_est(0U));
}

#endif // TEST
