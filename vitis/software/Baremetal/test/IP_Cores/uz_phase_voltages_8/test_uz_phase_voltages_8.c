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

_Bool done_delay_compensation_AXI=0;

void tearDown(void)
{
}

void test_uz_phase_voltages_8_init_test(void)
{
    uz_phase_voltages_8_set_theta_el_offset_Expect(config.base_address, config.theta_el_offset);
    uz_phase_voltages_8_set_u_dc_link_voltage_Expect(config.base_address, config.u_dc_link_voltage);

    uz_phase_voltages_8_init(config);
}

void test_uz_phase_voltages_8_read_Index_in(void){

    uz_phase_voltages_8_set_theta_el_offset_Expect(config.base_address, config.theta_el_offset);
    uz_phase_voltages_8_set_u_dc_link_voltage_Expect(config.base_address, config.u_dc_link_voltage);

    uz_phase_voltages_8_t* test_instance = uz_phase_voltages_8_init(config);

    int32_t Index_in_expect = 3;
    uz_phase_voltages_8_get_Index_in_ExpectAndReturn(config.base_address, Index_in_expect);
    int32_t Index_in = uz_phase_voltages_8_read_Index_in(test_instance);
    TEST_ASSERT_EQUAL_INT(Index_in, Index_in_expect);
}

void test_phase_voltages_8_set_set_done_delay_compensation_AXI_test(void)
{
    uz_phase_voltages_8_set_theta_el_offset_Expect(config.base_address, config.theta_el_offset);
    uz_phase_voltages_8_set_u_dc_link_voltage_Expect(config.base_address, config.u_dc_link_voltage);

    uz_phase_voltages_8_t* test_instance = uz_phase_voltages_8_init(config);

   uz_phase_voltages_8_hw_set_done_delay_compensation_AXI_Expect(config.base_address, done_delay_compensation_AXI);

   uz_phase_voltages_8_set_set_done_delay_compensation_AXI(test_instance, done_delay_compensation_AXI);
   }
   
#endif // TEST
