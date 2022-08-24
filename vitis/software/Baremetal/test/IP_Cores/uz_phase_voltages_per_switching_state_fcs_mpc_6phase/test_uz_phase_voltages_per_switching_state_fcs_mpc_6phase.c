#ifdef TEST

#include "unity.h"

#include "uz_phase_voltages_per_switching_state_fcs_mpc_6phase.h"
#include "test_assert_with_exception.h"
#include "mock_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_config_t config={
    .base_address= TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
    .theta_el_offset=0.9f,
    .u_dc_link_voltage=500.0f,
    .use_AXI=1
};

static struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_AXI_values_t AXI_values={
    .theta_el_AXI=2.4f,
    .Index_AXI=46
};

void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS;
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
    config.theta_el_offset = 0.9f;
    config.u_dc_link_voltage = 500.0f;
    config.use_AXI = 1;

    AXI_values.theta_el_AXI = 2.4f;
    AXI_values.Index_AXI = 46;
}

void tearDown(void)
{
}
void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_init_test(void)
{
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset_Expect(config.base_address, config.theta_el_offset);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage_Expect(config.base_address, config.u_dc_link_voltage);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI_Expect(config.base_address, config.use_AXI);

    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_init(config);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_AXI_values_test(void)
{
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset_Expect(config.base_address, config.theta_el_offset);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage_Expect(config.base_address, config.u_dc_link_voltage);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* test_instance = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_init(config);

    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_AXI_Expect(config.base_address, AXI_values.theta_el_AXI);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_Index_AXI_Expect(config.base_address, AXI_values.Index_AXI);

    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_AXI_values(test_instance, AXI_values);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_read_dvoltage_qvoltage_xvoltage_yvoltage_test(void)
{
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_theta_el_offset_Expect(config.base_address, config.theta_el_offset);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_u_dc_link_voltage_Expect(config.base_address, config.u_dc_link_voltage);
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_use_AXI_Expect(config.base_address, config.use_AXI);
    
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* test_instance = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_init(config); 

    float d_expect = 4.5f;
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_d_voltage_per_switching_state_ExpectAndReturn(config.base_address, d_expect);

    float q_expect = 3.3f;
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_q_voltage_per_switching_state_ExpectAndReturn(config.base_address, q_expect);

    float x_expect = 2.3f;
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_x_voltage_per_switching_state_ExpectAndReturn(config.base_address, x_expect);

    float y_expect = 1.7f;
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_get_y_voltage_per_switching_state_ExpectAndReturn(config.base_address, y_expect);

    struct uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t voltage = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_read_dvoltage_qvoltage_xvoltage_yvoltage(test_instance);

   TEST_ASSERT_EQUAL_FLOAT(voltage.d, d_expect);
   TEST_ASSERT_EQUAL_FLOAT(voltage.q, q_expect);
   TEST_ASSERT_EQUAL_FLOAT(voltage.x, x_expect);
   TEST_ASSERT_EQUAL_FLOAT(voltage.y, y_expect);
}

void test_uz_phase_voltages_per_switching_state_fcs_mpc_6phase_read_dvoltage_qvoltage_xvoltage_yvoltage_pointer(void)
{
    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* testpointer = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_phase_voltages_per_switching_state_fcs_mpc_6phase_read_dvoltage_qvoltage_xvoltage_yvoltage(testpointer));
}

#endif // TEST
