#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_temperaturecard.h"
#include "mock_uz_temperaturecard_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "uz_temperaturecard_test_vectors.h"

uz_temperaturecard_OneGroup test_channeldata;
uz_temperaturecard_t* test_instance_global;

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
    test_channeldata.Channel_Fault_Data[0] = 1;
    test_channeldata.Channel_Fault_Data[1] = 0;
    test_channeldata.Channel_Fault_Data[2] = 0;
    test_channeldata.Channel_Fault_Data[3] = 0;
    test_channeldata.Channel_Fault_Data[4] = 0;
    test_channeldata.Channel_Fault_Data[5] = 0;
    test_channeldata.Channel_Fault_Data[6] = 1;
    test_channeldata.Channel_Fault_Data[7] = 1;
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


void test_get_Fault_Data_bits(void)
{
    struct uz_temperaturecard_config_t test_config_global = {
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
    Configbuffer_Global = (test_config_global.Config_Global_C << 16U) | (test_config_global.Config_Global_B << 8U) | (test_config_global.Config_Global_A << 0U);
    Configbuffer_Mux = (test_config_global.Config_Mux_C << 16U) | (test_config_global.Config_Mux_B << 8U) | (test_config_global.Config_Mux_A << 0U);
    uint32_t sample_counter_end_value = (uint32_t)((1.0f/((float)test_config_global.Sample_Freq_Hz))/(1.0f/(float)test_config_global.ip_clk_frequency_Hz));


    uz_TempCard_IF_hw_writeGlobalConfigReg_Expect(test_config_global.base_address,Configbuffer_Global);
    uz_TempCard_IF_hw_writeMuxConfigReg_Expect(test_config_global.base_address,Configbuffer_Mux);
    uz_TempCard_IF_hw_writeCounterReg_Expect(test_config_global.base_address, sample_counter_end_value);
    uz_TempCard_IF_hw_write_channel_group_A_configdata_Expect(TEST_BASE_ADDRESS, test_config_global.Configdata_A);
    uz_TempCard_IF_hw_write_channel_group_B_configdata_Expect(TEST_BASE_ADDRESS, test_config_global.Configdata_B);
    uz_TempCard_IF_hw_write_channel_group_C_configdata_Expect(TEST_BASE_ADDRESS, test_config_global.Configdata_C);

    test_instance_global = uz_temperaturecard_init(test_config_global);

    uint32_t test_raw_values_A[20] = {0U};
    uint32_t test_raw_values_B[20] = {0U};
    uint32_t test_raw_values_C[20] = {0U};

for(uint32_t k=117;k<127;k++) { //sweep through all 256 possible Fault_Data states

    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {
            test_raw_values_A[i] = (Channel_Fault_Data_test[k] << 24U);
            test_raw_values_B[i] = (Channel_Fault_Data_test[k] << 24U); 
            test_raw_values_C[i] = (Channel_Fault_Data_test[k] << 24U); 
    }

    

    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {
    uz_TempCard_IF_hw_read_raw_value_channel_group_A_ExpectAndReturn(TEST_BASE_ADDRESS, i, test_raw_values_A[i]);
    }
    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {
    uz_TempCard_IF_hw_read_raw_value_channel_group_B_ExpectAndReturn(TEST_BASE_ADDRESS, i, test_raw_values_B[i]);
    }
    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {
    uz_TempCard_IF_hw_read_raw_value_channel_group_C_ExpectAndReturn(TEST_BASE_ADDRESS, i, test_raw_values_C[i]);
    }


    // from here on actually the test starts
    for(uint32_t m=0;m<=(3U*CHANNEL_COUNT);m++) {
    uz_TempCard_IF_MeasureTemps_cyclic(test_instance_global);
    }


    uz_temperaturecard_OneGroup test_group_A = uz_TempCard_IF_get_channel_group(test_instance_global, 'a');
    uz_temperaturecard_OneGroup test_group_B = uz_TempCard_IF_get_channel_group(test_instance_global, 'b');
    uz_temperaturecard_OneGroup test_group_C = uz_TempCard_IF_get_channel_group(test_instance_global, 'c');

    for(uint32_t i=0;i<CHANNEL_COUNT;i++) {

    // printf("FAULT_DATA_A_bit0: %i, expected: %i, iteration: %i\n", test_group_A.Channel_Fault_Data[i] & 1U, Channel_Fault_Data_ref_result_bit0[k], i);
    // printf("FAULT_DATA_B_bit0: %i, expected: %i, iteration: %i\n", test_group_B.Channel_Fault_Data[i] & 1U, Channel_Fault_Data_ref_result_bit0[k], i);
    // printf("FAULT_DATA_C_bit0: %i, expected: %i, iteration: %i\n", test_group_C.Channel_Fault_Data[i] & 1U, Channel_Fault_Data_ref_result_bit0[k], i);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit0[k], test_group_A.Channel_Fault_Data[i] & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit0[k], test_group_B.Channel_Fault_Data[i] & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit0[k], test_group_C.Channel_Fault_Data[i] & 1U);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit1[k], (test_group_A.Channel_Fault_Data[i] >> 1U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit1[k], (test_group_B.Channel_Fault_Data[i] >> 1U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit1[k], (test_group_C.Channel_Fault_Data[i] >> 1U) & 1U);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit2[k], (test_group_A.Channel_Fault_Data[i] >> 2U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit2[k], (test_group_B.Channel_Fault_Data[i] >> 2U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit2[k], (test_group_C.Channel_Fault_Data[i] >> 2U) & 1U);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit3[k], (test_group_A.Channel_Fault_Data[i] >> 3U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit3[k], (test_group_B.Channel_Fault_Data[i] >> 3U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit3[k], (test_group_C.Channel_Fault_Data[i] >> 3U) & 1U);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit4[k], (test_group_A.Channel_Fault_Data[i] >> 4U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit4[k], (test_group_B.Channel_Fault_Data[i] >> 4U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit4[k], (test_group_C.Channel_Fault_Data[i] >> 4U) & 1U);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit5[k], (test_group_A.Channel_Fault_Data[i] >> 5U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit5[k], (test_group_B.Channel_Fault_Data[i] >> 5U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit5[k], (test_group_C.Channel_Fault_Data[i] >> 5U) & 1U);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit6[k], (test_group_A.Channel_Fault_Data[i] >> 6U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit6[k], (test_group_B.Channel_Fault_Data[i] >> 6U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit6[k], (test_group_C.Channel_Fault_Data[i] >> 6U) & 1U);

    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit7[k], (test_group_A.Channel_Fault_Data[i] >> 7U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit7[k], (test_group_B.Channel_Fault_Data[i] >> 7U) & 1U);
    TEST_ASSERT_EQUAL_UINT32(Channel_Fault_Data_ref_result_bit7[k], (test_group_C.Channel_Fault_Data[i] >> 7U) & 1U);
    }

}//sweep through all 256 possible Fault_Data states


}

#endif // TEST
