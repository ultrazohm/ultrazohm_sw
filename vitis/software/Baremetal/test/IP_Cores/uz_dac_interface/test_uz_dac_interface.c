#ifdef TEST

#include "unity.h"

#include "test_assert_with_exception.h"
#include "uz_dac_interface.h"
#include "mock_uz_dac_interface_hw.h"
#include <stdint.h>
#include "uz_array.h"

#define TEST_BASE_ADDRESS 0x0000000Fu
#define TEST_IP_CORE_FRQ 100000000u

void setUp(void)
{
}

void tearDown(void)
{
}

static int32_t convert_voltage_to_int(float input, float gain);

void test_uz_dac_interface_set_values(void)
{
    struct uz_dac_interface_config_t config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .gain = {2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f}

    };

    uz_dac_interface_t *test = uz_dac_interface_init(config);
    float output[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    uz_array_float_t output_values = {
        .data = &output[0],
        .length = 8};

    uz_dac_interface_hw_write_dac1_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[0], config.gain[0]));
    uz_dac_interface_hw_write_dac2_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[1], config.gain[1]));
    uz_dac_interface_hw_write_dac3_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[2], config.gain[2]));
    uz_dac_interface_hw_write_dac4_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[3], config.gain[3]));
    uz_dac_interface_hw_write_dac5_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[4], config.gain[4]));
    uz_dac_interface_hw_write_dac6_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[5], config.gain[5]));
    uz_dac_interface_hw_write_dac7_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[6], config.gain[6]));
    uz_dac_interface_hw_write_dac8_Expect(TEST_BASE_ADDRESS, convert_voltage_to_int(output[7], config.gain[7]));

    uz_dac_interface_hw_write_trigger_Expect(TEST_BASE_ADDRESS, true);
    uz_dac_interface_hw_write_trigger_Expect(TEST_BASE_ADDRESS, false);

    uz_dac_interface_set_ouput_values(test, &output_values);
}

static int32_t convert_voltage_to_int(float input, float gain)
{
    int32_t voltage_set_point = (int32_t)((input / (2.5f*gain) ) * 32768) + 32768;
    return voltage_set_point;
}

#endif // TEST
