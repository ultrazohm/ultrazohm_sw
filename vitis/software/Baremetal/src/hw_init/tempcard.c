#include "../include/tempcard.h"

struct uz_temperaturecard_config_t t_config = {
    .base_address = XPAR_TEMP_CARD_INTERFACE_TEMPERATURE_CARD_INT_0_BASEADDR,
    .ip_clk_frequency_Hz = 100000000,
    .Sample_Freq = 100,
    .Configdata_A = {0},
	.Configdata_A[4-1]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[6-1]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[8-1]  = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[10-1] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[12-1] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[14-1] = (SENSOR_TYPE__RTD_PT_100) + (RTD_RSENSE_CHANNEL__2) + (0x0 << 20) + (RTD_EXCITATION_MODE__NO_ROTATION_SHARING) + (RTD_EXCITATION_CURRENT__100UA) + (RTD_STANDARD__EUROPEAN),
	.Configdata_A[2-1] = 0xE80FA000,//(SENSOR_TYPE__SENSE_RESISTOR) + (SENSE_RESISTOR_VALUE),
	.Configdata_B = {0},
	.Configdata_C = {0}};


uz_temperaturecard_t* init_tempcard(void){
	uz_temperaturecard_t* obj = uz_temperaturecard_init(t_config);
	uz_TempCard_IF_Reset(obj);
	uz_TempCard_IF_Start(obj);
	return (obj);
}
