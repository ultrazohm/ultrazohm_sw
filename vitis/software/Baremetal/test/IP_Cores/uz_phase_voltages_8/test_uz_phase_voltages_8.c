#ifdef TEST

#include "unity.h"

#include "uz_phase_voltages_8.h"
#include "test_assert_with_exception.h"
#include "mock_uz_phase_voltages_8_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "../../uz/uz_Transformation/uz_Transformation.h"

static struct uz_phase_voltages_8_config_t config={
    .base_address= TEST_BASE_ADDRESS,
    .ip_clk_frequency_Hz=TEST_IP_CORE_FRQ,
    .theta_el_offset=0.9f,
    .u_dc_link_voltage=500.0f
};
void setUp(void)
{
    config.base_address = TEST_BASE_ADDRESS;
    config.ip_clk_frequency_Hz = TEST_IP_CORE_FRQ;
    config.theta_el_offset = 0.9f;
    config.u_dc_link_voltage = 500.0f;
}

void tearDown(void)
{
}

void test_uz_phase_voltages_8_init_test(void)
{
    uz_phase_voltages_8_set_theta_el_offset_Expect(config.base_address, config.theta_el_offset);
    uz_phase_voltages_8_set_u_dc_link_voltage_Expect(config.base_address, config.u_dc_link_voltage);

    uz_phase_voltages_8_init(config);
}
#endif // TEST
