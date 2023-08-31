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


void test_uz_TempCard_IF_average_temperature_for_valid(void)
{
    float average = uz_TempCard_IF_average_temperature_for_valid(test_channeldata, 0U, 6U);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, average);
    average = uz_TempCard_IF_average_temperature_for_valid(test_channeldata, 1U, 5U);
    TEST_ASSERT_EQUAL_FLOAT(-333.3f, average);
}

void test_uz_temperaturecard_init_null_base_address(void)
{
    struct uz_temperaturecard_config_t test_config = {
        .base_address = 0U,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .Sample_Freq_Hz = 5U
    };
    TEST_ASSERT_FAIL_ASSERT(uz_temperaturecard_init(test_config));
}

void test_uz_temperaturecard_init_null_ip_clk(void)
{
    struct uz_temperaturecard_config_t test_config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = 0U,
        .Sample_Freq_Hz = 5U
    };
    TEST_ASSERT_FAIL_ASSERT(uz_temperaturecard_init(test_config));
}

void test_uz_temperaturecard_init_null_sample_freq(void)
{
    struct uz_temperaturecard_config_t test_config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .Sample_Freq_Hz = 0U
    };
    TEST_ASSERT_FAIL_ASSERT(uz_temperaturecard_init(test_config));
}

void test_uz_temperaturecard_init_success(void)
{
    

    struct uz_temperaturecard_config_t test_config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .Sample_Freq_Hz = 5U,
        .Configdata_A[1 - 1] = 0,
        .Configdata_A[2 - 1] = SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k,
        .Configdata_A[3 - 1] = 0,
        .Configdata_A[4 - 1] = SENSOR_TYPE__RTD_PT_100 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__100UA | RTD_STANDARD__EUROPEAN,
        .Configdata_A[5 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[6 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[7 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[8 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[9 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[10 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[11 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[12 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[13 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[14 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[15 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[16 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[17 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[18 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[19 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[20 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_B = {0U},
        .Configdata_C = {0U},
        .Config_Global_A = 0U,
        .Config_Global_B = 0U,
        .Config_Global_C = 0U,
        .Config_Mux_A = 0U,
        .Config_Mux_B = 0U,
        .Config_Mux_C = 0U
    };

    uint32_t Configbuffer_Global = 0U;
    uint32_t Configbuffer_Mux = 0U;
    Configbuffer_Global = (test_config.Config_Global_C << 16U) | (test_config.Config_Global_B << 8U) | (test_config.Config_Global_A << 0U);
    Configbuffer_Mux = (test_config.Config_Mux_C << 16U) | (test_config.Config_Mux_B << 8U) | (test_config.Config_Mux_A << 0U);
    uint32_t sample_counter_end_value = (uint32_t)((1.0f/((float)test_config.Sample_Freq_Hz))/(1.0f/(float)test_config.ip_clk_frequency_Hz));

    uz_TempCard_IF_hw_writeGlobalConfigReg_Expect(test_config.base_address,Configbuffer_Global);
    uz_TempCard_IF_hw_writeMuxConfigReg_Expect(test_config.base_address,Configbuffer_Mux);
    uz_TempCard_IF_hw_writeCounterReg_Expect(test_config.base_address, sample_counter_end_value);
    uz_TempCard_IF_hw_write_channel_group_A_configdata_Expect(TEST_BASE_ADDRESS, test_config.Configdata_A);
    uz_TempCard_IF_hw_write_channel_group_B_configdata_Expect(TEST_BASE_ADDRESS, test_config.Configdata_B);
    uz_TempCard_IF_hw_write_channel_group_C_configdata_Expect(TEST_BASE_ADDRESS, test_config.Configdata_C);
    
    uz_temperaturecard_init(test_config);
}

void test_uz_TempCard_IF_MeasureTemps_cyclic(void)
{
        struct uz_temperaturecard_config_t test_config = {
        .base_address = TEST_BASE_ADDRESS,
        .ip_clk_frequency_Hz = TEST_IP_CORE_FRQ,
        .Sample_Freq_Hz = 5U,
        .Configdata_A[1 - 1] = 0,
        .Configdata_A[2 - 1] = SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k,
        .Configdata_A[3 - 1] = 0,
        .Configdata_A[4 - 1] = SENSOR_TYPE__RTD_PT_100 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__100UA | RTD_STANDARD__EUROPEAN,
        .Configdata_A[5 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[6 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[7 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[8 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[9 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,  // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[10 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[11 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[12 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[13 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[14 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[15 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[16 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[17 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[18 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[19 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_A[20 - 1] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO, // | TC_OPEN_CKT_DETECT_CURRENT__10UA,
        .Configdata_B = {0U},
        .Configdata_C = {0U},
        .Config_Global_A = 0U,
        .Config_Global_B = 0U,
        .Config_Global_C = 0U,
        .Config_Mux_A = 0U,
        .Config_Mux_B = 0U,
        .Config_Mux_C = 0U
    };

    uint32_t Configbuffer_Global = 0U;
    uint32_t Configbuffer_Mux = 0U;
    Configbuffer_Global = (test_config.Config_Global_C << 16U) | (test_config.Config_Global_B << 8U) | (test_config.Config_Global_A << 0U);
    Configbuffer_Mux = (test_config.Config_Mux_C << 16U) | (test_config.Config_Mux_B << 8U) | (test_config.Config_Mux_A << 0U);
    uint32_t sample_counter_end_value = (uint32_t)((1.0f/((float)test_config.Sample_Freq_Hz))/(1.0f/(float)test_config.ip_clk_frequency_Hz));

    uz_TempCard_IF_hw_writeGlobalConfigReg_Expect(test_config.base_address,Configbuffer_Global);
    uz_TempCard_IF_hw_writeMuxConfigReg_Expect(test_config.base_address,Configbuffer_Mux);
    uz_TempCard_IF_hw_writeCounterReg_Expect(test_config.base_address, sample_counter_end_value);
    uz_TempCard_IF_hw_write_channel_group_A_configdata_Expect(TEST_BASE_ADDRESS, test_config.Configdata_A);
    uz_TempCard_IF_hw_write_channel_group_B_configdata_Expect(TEST_BASE_ADDRESS, test_config.Configdata_B);
    uz_TempCard_IF_hw_write_channel_group_C_configdata_Expect(TEST_BASE_ADDRESS, test_config.Configdata_C);
    
    uz_temperaturecard_t* test_instance = uz_temperaturecard_init(test_config);

    uint32_t test_raw_values_A[20] = {0U};
    uint32_t test_raw_values_B[20] = {0U};
    uint32_t test_raw_values_C[20] = {0U};

    // uint32_t test_raw_values_A[20] = {
    //     0b00000001000000000000000000000000
    // }
    // uint32_t result_raw_values_A[20] = {0U};
    

    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {
        uz_TempCard_IF_hw_read_raw_value_channel_group_A_ExpectAndReturn(TEST_BASE_ADDRESS, i, test_raw_values_A[i]);
    }

    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {
        uz_TempCard_IF_hw_read_raw_value_channel_group_B_ExpectAndReturn(TEST_BASE_ADDRESS, i, test_raw_values_B[i]);
    }
    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {
        uz_TempCard_IF_hw_read_raw_value_channel_group_C_ExpectAndReturn(TEST_BASE_ADDRESS, i, test_raw_values_C[i]);
    }

    for(uint32_t k=0;k<(3U*CHANNEL_COUNT);k++) {
    uz_TempCard_IF_MeasureTemps_cyclic(test_instance);
    }
}


#endif // TEST
