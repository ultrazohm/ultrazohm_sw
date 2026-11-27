#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_sogipll.h"
#include "mock_uz_sogipll_hw.h"
#include "uz_global_configuration.h"
#include <math.h>

#define TEST_BASE_ADDRESS 0x40000000U
#define TEST_IP_CORE_FRQ 100000000U
#define TEST_ADDRESS_STRIDE 0x10000U

static struct uz_sogipll_config_t config = {0};
static uint32_t allocated_instances = 0U;

void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS + (allocated_instances * TEST_ADDRESS_STRIDE);
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
    config.omega_feedforward_rad_per_s = 314.159f;
    config.sogi_gain = 1.414f;
    config.proportional_gain = 2.5f;
    config.integral_gain = 12.5f;
    config.voltage_scaling = 0.01f;
}

void tearDown(void)
{
}

static uz_sogipll_t *successful_init(void);

static uz_sogipll_t *successful_init(void)
{
    uz_sogipll_hw_write_in_rst_Expect(config.base_address, true);
    uz_sogipll_hw_write_in_v_Expect(config.base_address, 0.0f);
    uz_sogipll_hw_write_in_omega_ff_Expect(config.base_address, config.omega_feedforward_rad_per_s);
    uz_sogipll_hw_write_in_k_Expect(config.base_address, config.sogi_gain);
    uz_sogipll_hw_write_in_kp_Expect(config.base_address, config.proportional_gain);
    uz_sogipll_hw_write_in_ki_Expect(config.base_address, config.integral_gain);
    uz_sogipll_hw_write_in_t_sample_Expect(config.base_address, 2.0e-6f);
    uz_sogipll_hw_write_in_v_scaling_Expect(config.base_address, config.voltage_scaling);
    uz_sogipll_hw_write_in_rst_Expect(config.base_address, false);
    uz_sogipll_t *self = uz_sogipll_init(config);
    allocated_instances++;
    TEST_ASSERT_NOT_NULL(self);
    return self;
}

void test_uz_sogipll_init(void)
{
    (void)successful_init();
}

void test_uz_sogipll_init_allows_zero_pi_gains_and_negative_scaling(void)
{
    config.proportional_gain = 0.0f;
    config.integral_gain = 0.0f;
    config.voltage_scaling = -1.0f;
    (void)successful_init();
}

void test_uz_sogipll_init_rejects_zero_address(void)
{
    config.base_address = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_unaligned_address(void)
{
    config.base_address = 0x40000001U;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_zero_clock(void)
{
    config.ip_clk_frequency_Hz = 0U;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_unsupported_clock(void)
{
    config.ip_clk_frequency_Hz = 50000000U;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_nan_omega_feedforward_rad_per_s(void)
{
    config.omega_feedforward_rad_per_s = NAN;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_infinity_omega_feedforward_rad_per_s(void)
{
    config.omega_feedforward_rad_per_s = -INFINITY;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_omega_feedforward_rad_per_s(void)
{
    config.omega_feedforward_rad_per_s = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_zero_omega_feedforward_rad_per_s(void)
{
    config.omega_feedforward_rad_per_s = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_nan_sogi_gain(void)
{
    config.sogi_gain = NAN;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_infinity_sogi_gain(void)
{
    config.sogi_gain = -INFINITY;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_sogi_gain(void)
{
    config.sogi_gain = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_zero_sogi_gain(void)
{
    config.sogi_gain = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_nan_proportional_gain(void)
{
    config.proportional_gain = NAN;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_infinity_proportional_gain(void)
{
    config.proportional_gain = -INFINITY;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_proportional_gain(void)
{
    config.proportional_gain = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_nan_integral_gain(void)
{
    config.integral_gain = NAN;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_infinity_integral_gain(void)
{
    config.integral_gain = -INFINITY;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_negative_integral_gain(void)
{
    config.integral_gain = -1.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_nan_voltage_scaling(void)
{
    config.voltage_scaling = NAN;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_zero_voltage_scaling(void)
{
    config.voltage_scaling = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_init_rejects_duplicate_hardware(void)
{
    (void)successful_init();
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

void test_uz_sogipll_set_voltage_with_multiple_instances(void)
{
    uint32_t first_address = config.base_address;
    uz_sogipll_t *first = successful_init();
    config.base_address += TEST_ADDRESS_STRIDE;
    uz_sogipll_t *second = successful_init();
    TEST_ASSERT_NOT_EQUAL(first, second);
    uz_sogipll_hw_write_in_v_Expect(first_address, -230.5f);
    uz_sogipll_set_voltage(first, -230.5f);
    uz_sogipll_hw_write_in_v_Expect(config.base_address, 0.0f);
    uz_sogipll_set_voltage(second, 0.0f);
}

void test_uz_sogipll_reset_preserves_configuration_and_toggles_algorithm_reset(void)
{
    uz_sogipll_t *self = successful_init();
    uz_sogipll_hw_write_in_rst_Expect(config.base_address, true);
    uz_sogipll_hw_write_in_rst_Expect(config.base_address, false);
    uz_sogipll_reset(self);
}

void test_uz_sogipll_read_outputs_maps_all_fields(void)
{
    uz_sogipll_t *self = successful_init();
    uz_sogipll_hw_read_out_v_est_ExpectAndReturn(config.base_address, -0.75f);
    uz_sogipll_hw_read_out_qv_est_ExpectAndReturn(config.base_address, 0.25f);
    uz_sogipll_hw_read_out_v_d_ExpectAndReturn(config.base_address, 0.9f);
    uz_sogipll_hw_read_out_v_q_ExpectAndReturn(config.base_address, -0.125f);
    uz_sogipll_hw_read_out_theta_est_ExpectAndReturn(config.base_address, 1.57f);
    uz_sogipll_hw_read_out_omega_est_ExpectAndReturn(config.base_address, 313.5f);
    struct uz_sogipll_outputs_t outputs = uz_sogipll_read_outputs(self);
    TEST_ASSERT_EQUAL_FLOAT(-0.75f, outputs.voltage_estimate);
    TEST_ASSERT_EQUAL_FLOAT(0.25f, outputs.quadrature_voltage_estimate);
    TEST_ASSERT_EQUAL_FLOAT(0.9f, outputs.voltage_d);
    TEST_ASSERT_EQUAL_FLOAT(-0.125f, outputs.voltage_q);
    TEST_ASSERT_EQUAL_FLOAT(1.57f, outputs.theta_rad);
    TEST_ASSERT_EQUAL_FLOAT(313.5f, outputs.omega_rad_per_s);
}

void test_uz_sogipll_set_voltage_with_null_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_set_voltage(NULL, 1.0f));
}

void test_uz_sogipll_reset_with_null_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_reset(NULL));
}

void test_uz_sogipll_read_outputs_with_null_pointer(void)
{
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_read_outputs(NULL));
}

// Run last: the production pool deliberately cannot be released or reset.
void test_uz_sogipll_pool_exhaustion_asserts_before_hardware_access(void)
{
    while (allocated_instances < UZ_SOGIPLL_MAX_INSTANCES) {
        config.base_address = TEST_BASE_ADDRESS + (allocated_instances * TEST_ADDRESS_STRIDE);
        (void)successful_init();
    }
    config.base_address = 0x50000000U;
    TEST_ASSERT_FAIL_ASSERT(uz_sogipll_init(config));
}

#endif // TEST
