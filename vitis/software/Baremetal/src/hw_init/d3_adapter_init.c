#include "../include/d3_adapter_init.h"

/* Project Wizard BEGIN: D3 definitions */
/* Project Wizard generated content for D3 */
#include "../uz/uz_HAL.h"
#include "../uz/uz_global_configuration.h"
#include "xparameters.h"

static struct uz_temperaturecard_config_t config_temperature_card_d3 = {
    .base_address = XPAR_UZ_DIGITAL_ADAPTER_D3_ADAPTER_TEMPERATURE_CARD_INT_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000U,
    .Sample_Freq_Hz = 5U,
    .Config_Global_A = 0U,
    .Config_Mux_A = 0U,
    .Config_Global_B = 0U,
    .Config_Mux_B = 0U,
    .Config_Global_C = 0U,
    .Config_Mux_C = 0U,
    .Configdata_A = {
        [0] = 0U,
        [1] = SENSOR_TYPE__SENSE_RESISTOR | SENSE_RESISTOR_VALUE_1k,
        [2] = 0U,
        [3] = SENSOR_TYPE__RTD_PT_100 | RTD_RSENSE_CHANNEL__2 | RTD_NUM_WIRES__2_WIRE | RTD_EXCITATION_MODE__NO_ROTATION_SHARING | RTD_EXCITATION_CURRENT__100UA | RTD_STANDARD__EUROPEAN,
        [4] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [5] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [6] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [7] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [8] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [9] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [10] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [11] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [12] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [13] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [14] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [15] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [16] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [17] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [18] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
        [19] = SENSOR_TYPE__TYPE_K_THERMOCOUPLE | TC_COLD_JUNCTION_CH__4 | TC_SINGLE_ENDED | TC_OPEN_CKT_DETECT__NO,
    },
    .Configdata_B = {
        [0] = 0U,
    },
    .Configdata_C = {
        [0] = 0U,
    },
};

uz_temperaturecard_t* initialize_temperature_card_d3(void)
{
    uz_temperaturecard_t* temperature_card = uz_temperaturecard_init(config_temperature_card_d3);
    uint32_t readback = uz_TempCard_IF_hw_readReadbackReg(config_temperature_card_d3.base_address);
    uint32_t internal_error = uz_TempCard_IF_hw_readErrorReg(config_temperature_card_d3.base_address);
    if (readback == IP_CORE_READBACK_VALUE) {
        uz_printf("RPU: D3 temperature card AXI readback OK: 0x%x, internal error: 0x%x\r\n", readback, internal_error);
    } else {
        uz_printf("RPU: D3 temperature card AXI readback FAILED: expected 0x%x, got 0x%x, internal error: 0x%x\r\n", IP_CORE_READBACK_VALUE, readback, internal_error);
    }
    return temperature_card;
}
/* Project Wizard END: D3 definitions */
