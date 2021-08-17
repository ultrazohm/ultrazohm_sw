/******************************************************************************
* Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "../include/adc.h"
#include <stdint.h>
#include <math.h>
#include "xil_types.h"
#include "xil_io.h"

#include "../IP_Cores/ADC_Module_LVDS_v2_ip_addr.h"
#include "../IP_Cores/uz_dataMover/uz_dataMover.h"
#include "../uz/uz_HAL.h"

void ADC_readCardA1(DS_Data *data, uz_array_int16_t adc_data)
{
	// bitshift operation of -16 digits, because it is an 16-bit ADC
	// Conversion Factor is defined in main.c InitializeDataStructure
	data->aa.A1.me.ADC_array[0] = ((float)adc_data.data[0]) / (1<<Q16) * data->aa.A1.cf.ADC_A1;
	data->aa.A1.me.ADC_array[1] = ((float)adc_data.data[1]) / (1<<Q16) * data->aa.A1.cf.ADC_A2;
	data->aa.A1.me.ADC_array[2] = ((float)adc_data.data[2]) / (1<<Q16) * data->aa.A1.cf.ADC_A3;
	data->aa.A1.me.ADC_array[3] = ((float)adc_data.data[3]) / (1<<Q16) * data->aa.A1.cf.ADC_A4;
	data->aa.A1.me.ADC_array[4] = ((float)adc_data.data[4]) / (1<<Q16) * data->aa.A1.cf.ADC_B5;
	data->aa.A1.me.ADC_array[5] = ((float)adc_data.data[5]) / (1<<Q16) * data->aa.A1.cf.ADC_B6;
	data->aa.A1.me.ADC_array[6] = ((float)adc_data.data[6]) / (1<<Q16) * data->aa.A1.cf.ADC_B7;
	data->aa.A1.me.ADC_array[7] = ((float)adc_data.data[7]) / (1<<Q16) * data->aa.A1.cf.ADC_B8;
}

void ADC_readCardA2(DS_Data *data, uz_array_int16_t adc_data)
{
	data->aa.A2.me.ADC_array[0] = ((float)adc_data.data[8] ) / (1<<Q16) * data->aa.A2.cf.ADC_A1;
	data->aa.A2.me.ADC_array[1] = ((float)adc_data.data[9] ) / (1<<Q16) * data->aa.A2.cf.ADC_A2;
	data->aa.A2.me.ADC_array[2] = ((float)adc_data.data[10]) / (1<<Q16) * data->aa.A2.cf.ADC_A3;
	data->aa.A2.me.ADC_array[3] = ((float)adc_data.data[11]) / (1<<Q16) * data->aa.A2.cf.ADC_A4;
	data->aa.A2.me.ADC_array[4] = ((float)adc_data.data[12]) / (1<<Q16) * data->aa.A2.cf.ADC_B5;
	data->aa.A2.me.ADC_array[5] = ((float)adc_data.data[13]) / (1<<Q16) * data->aa.A2.cf.ADC_B6;
	data->aa.A2.me.ADC_array[6] = ((float)adc_data.data[14]) / (1<<Q16) * data->aa.A2.cf.ADC_B7;
	data->aa.A2.me.ADC_array[7] = ((float)adc_data.data[15]) / (1<<Q16) * data->aa.A2.cf.ADC_B8;
}

void ADC_readCardA3(DS_Data *data, uz_array_int16_t adc_data)
{
	data->aa.A3.me.ADC_array[0] = ((float)adc_data.data[16]) / (1<<Q16) * data->aa.A3.cf.ADC_A1;
	data->aa.A3.me.ADC_array[1] = ((float)adc_data.data[17]) / (1<<Q16) * data->aa.A3.cf.ADC_A2;
	data->aa.A3.me.ADC_array[2] = ((float)adc_data.data[18]) / (1<<Q16) * data->aa.A3.cf.ADC_A3;
	data->aa.A3.me.ADC_array[3] = ((float)adc_data.data[19]) / (1<<Q16) * data->aa.A3.cf.ADC_A4;
	data->aa.A3.me.ADC_array[4] = ((float)adc_data.data[20]) / (1<<Q16) * data->aa.A3.cf.ADC_B5;
	data->aa.A3.me.ADC_array[5] = ((float)adc_data.data[21]) / (1<<Q16) * data->aa.A3.cf.ADC_B6;
	data->aa.A3.me.ADC_array[6] = ((float)adc_data.data[22]) / (1<<Q16) * data->aa.A3.cf.ADC_B7;
	data->aa.A3.me.ADC_array[7] = ((float)adc_data.data[23]) / (1<<Q16) * data->aa.A3.cf.ADC_B8;
};

void ADC_readCardALL(DS_Data *data)
{
	uz_array_int16_t adc_data = uz_dataMover_update_buffer_and_get_data();
	ADC_readCardA1(data, adc_data);
	ADC_readCardA2(data, adc_data);
	ADC_readCardA3(data, adc_data);
}

void ADC_WriteConversionFactor(int ADC_ConversionFactor)
{
	// Example how to set the conversion factor in the ADC Module in the FPGA for ADC slot A1 Block A (4 ADCs)
	Xil_Out32(XPAR_ADC_A1_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip, ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A1_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip, ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A2_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip, ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A2_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip, ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A3_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip, ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A3_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip, ADC_ConversionFactor);
}
