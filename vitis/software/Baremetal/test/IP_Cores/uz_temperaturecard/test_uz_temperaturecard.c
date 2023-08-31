#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_temperaturecard.h"
#include "mock_uz_temperaturecard_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "uz_temperaturecard.h"

uz_temperaturecard_OneGroup test_channeldata;

void setUp(void)
{
    test_channeldata.temperature[0] = 1.0f;
    test_channeldata.temperature[1] = 2.0f;
    test_channeldata.temperature[2] = 3.0f;
    test_channeldata.temperature[3] = 4.0f;
    test_channeldata.temperature[4] = 5.0f;
    test_channeldata.temperature[5] = 6.0f;
    test_channeldata.temperature[6] = 7.0f;
    test_channeldata.temperature[7] = 8.0f;
    test_channeldata.Channels_Valid[0] = 1;
    test_channeldata.Channels_Valid[1] = 0;
    test_channeldata.Channels_Valid[2] = 0;
    test_channeldata.Channels_Valid[3] = 0;
    test_channeldata.Channels_Valid[4] = 0;
    test_channeldata.Channels_Valid[5] = 0;
    test_channeldata.Channels_Valid[6] = 1;
    test_channeldata.Channels_Valid[7] = 1;
}

void tearDown(void)
{
}

void test_uz_temperaturecard_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_temperaturecard");
}

void test_uz_TempCard_IF_average_temperature_for_valid(void)
{
    float average = uz_TempCard_IF_average_temperature_for_valid(test_channeldata, 0U, 6U);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, average);
    average = uz_TempCard_IF_average_temperature_for_valid(test_channeldata, 1U, 5U);
    TEST_ASSERT_EQUAL_FLOAT(-333.3f, average);
}

// void test_uz_TempCard_IF_hw_write_channel_group_A_configdata(void)
// {
    

//     struct uz_temperaturecard_config_t test_config = {
//         .base_address = TEST_BASE_ADDRESS,
//         .ip_clk_frequency_Hz = 100000000,
//         .Sample_Freq_Hz = 5U,
//         .Configdata_A[1 - 1] = 0,
//         .Configdata_A[2 - 1] = SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k,
//         .Configdata_A[3 - 1] = 0,
//         .Configdata_A[4 - 1] = SENSOR_TYPE__RTD_PT_100 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__100UA | RTD_STANDARD__EUROPEAN,
//         .Configdata_A[5 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[6 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[7 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[8 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[9 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[10 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[11 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[12 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[13 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[14 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[15 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[16 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[17 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[18 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[19 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_A[20 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
//         .Configdata_B = {0U},
//         .Configdata_C = {0U},
//         .Config_Global_A = 0U,
//         .Config_Global_B = 0U,
//         .Config_Global_C = 0U,
//         .Config_Mux_A = 0U,
//         .Config_Mux_B = 0U,
//         .Config_Mux_C = 0U
//     };

//     uint32_t Configbuffer_Global = 0U;
//     uint32_t Configbuffer_Mux = 0U;
//     Configbuffer_Global = (test_config.Config_Global_C << 16U) | (test_config.Config_Global_B << 8U) | (test_config.Config_Global_A << 0U);
//     Configbuffer_Mux = (test_config.Config_Mux_C << 16U) | (test_config.Config_Mux_B << 8U) | (test_config.Config_Mux_A << 0U);
//     uint32_t sample_counter_end_value = (uint32_t)((1.0f/((float)test_config.Sample_Freq_Hz))/(1.0f/(float)test_config.ip_clk_frequency_Hz));

//     uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+TempCard_IF_GlobalConfig, Configbuffer_Global);
//     uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+TempCard_IF_MuxConfig, Configbuffer_Mux);
//     uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS+TempCard_IF_Counterreg, sample_counter_end_value);
//     for (uint32_t i=1;i<20;i++) {
//     uz_axi_write_uint32_Expect(TEST_BASE_ADDRESS, test_config.Configdata_A[i]);
//     }
//     uz_temperaturecard_init(test_config);
// }

#endif // TEST
