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
#include "../IP_Cores/uz_dataMover/uz_dataMover.h"
#include "../uz/uz_HAL.h"
#define R5_0_BTCM_SPLIT_REG	0x20000
#define ADC_A1_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x00)
#define ADC_A1_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x02)
#define ADC_A1_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x04)
#define ADC_A1_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x06)

#define ADC_A1_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x08)
#define ADC_A1_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x0A)
#define ADC_A1_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x0C)
#define ADC_A1_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x0E)

// ADC Card Slot
#define ADC_A2_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x10)
#define ADC_A2_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x12)
#define ADC_A2_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x14)
#define ADC_A2_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x16)

#define ADC_A2_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x18)
#define ADC_A2_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x1A)
#define ADC_A2_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x1C)
#define ADC_A2_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x1E)

// ADC Card Slot
#define ADC_A3_ChA1_REG		(R5_0_BTCM_SPLIT_REG + 0x20)
#define ADC_A3_ChA2_REG		(R5_0_BTCM_SPLIT_REG + 0x22)
#define ADC_A3_ChA3_REG		(R5_0_BTCM_SPLIT_REG + 0x24)
#define ADC_A3_ChA4_REG		(R5_0_BTCM_SPLIT_REG + 0x26)

#define ADC_A3_ChB5_REG		(R5_0_BTCM_SPLIT_REG + 0x28)
#define ADC_A3_ChB6_REG		(R5_0_BTCM_SPLIT_REG + 0x2A)
#define ADC_A3_ChB7_REG		(R5_0_BTCM_SPLIT_REG + 0x2C)
#define ADC_A3_ChB8_REG		(R5_0_BTCM_SPLIT_REG + 0x2E)

#define ADC_ChA1	0
#define ADC_ChA2	1
#define ADC_ChA3	2
#define ADC_ChA4	3
#define ADC_ChB5	4
#define ADC_ChB6	5
#define ADC_ChB7	6
#define ADC_ChB8	7

uz_array_int16_t adc_values={0};
float is_equal_adc=0.0F;

extern int16_t buffer[24];
extern int16_t *ptr;

uz_array_int16_t dat_by_value;

void ADC_readCardA1(DS_Data* data){

	// read all 8 ADC values from Analog Adapter card slot A1
	int16_t ADC1 = Xil_In16(ADC_A1_ChA1_REG);
	int16_t ADC2 = Xil_In16(ADC_A1_ChA2_REG);
	int16_t ADC3 = Xil_In16(ADC_A1_ChA3_REG);
	int16_t ADC4 = Xil_In16(ADC_A1_ChA4_REG);
	int16_t ADC5 = Xil_In16(ADC_A1_ChB5_REG);
	int16_t ADC6 = Xil_In16(ADC_A1_ChB6_REG);
	int16_t ADC7 = Xil_In16(ADC_A1_ChB7_REG);
	int16_t ADC8 = Xil_In16(ADC_A1_ChB8_REG);

	// bitshift operation of -16 digits, because it is an 16-bit ADC
	// Conversion Factor is defined in main.c InitializeDataStructure
	 data->aa.A1.me.ADC_array[0] =  ldexpf((float)ADC1, -16)* data->aa.A1.cf.ADC_A1;
	 data->aa.A1.me.ADC_array[1] =  ldexpf((float)ADC2, -16)* data->aa.A1.cf.ADC_A2;
	 data->aa.A1.me.ADC_array[2] =  ldexpf((float)ADC3, -16)* data->aa.A1.cf.ADC_A3;
	 data->aa.A1.me.ADC_array[3] =  ldexpf((float)ADC4, -16)* data->aa.A1.cf.ADC_A4;
	 data->aa.A1.me.ADC_array[4] =  ldexpf((float)ADC5, -16)* data->aa.A1.cf.ADC_B5;
	 data->aa.A1.me.ADC_array[5] =  ldexpf((float)ADC6, -16)* data->aa.A1.cf.ADC_B6;
	 data->aa.A1.me.ADC_array[6] =  ldexpf((float)ADC7, -16)* data->aa.A1.cf.ADC_B7;
	 data->aa.A1.me.ADC_array[7] =  ldexpf((float)ADC8, -16)* data->aa.A1.cf.ADC_B8;
	 dat_by_value=uz_dataMover_get_data_by_buffer();
	 uz_assert(dat_by_value.data[0] == ADC1);
	 uz_assert(adc_values.data[0] == ADC1);
	 //uz_printf("Xil_in: %i, ptr: %i, by value: %i \n",ADC1,adc_values.data[0],dat_by_value.data[0]);

}

void ADC_readCardA2(DS_Data* data){
	// read all 8 ADC values from Analog Adapter card slot A1


	// bitshift operation of -16 digits, because it is an 16-bit ADC
	// Conversion Factor is defined in main.c InitializeDataStructure
	// data->aa.A2.me.ADC_array[0] =  ldexpf((float)ADC1, -16)* data->aa.A2.cf.ADC_A1;
	// data->aa.A2.me.ADC_array[1] =  ldexpf((float)ADC2, -16)* data->aa.A2.cf.ADC_A2;
	// data->aa.A2.me.ADC_array[2] =  ldexpf((float)ADC3, -16)* data->aa.A2.cf.ADC_A3;
	// data->aa.A2.me.ADC_array[3] =  ldexpf((float)ADC4, -16)* data->aa.A2.cf.ADC_A4;
	// data->aa.A2.me.ADC_array[4] =  ldexpf((float)ADC5, -16)* data->aa.A2.cf.ADC_B5;
	// data->aa.A2.me.ADC_array[5] =  ldexpf((float)ADC6, -16)* data->aa.A2.cf.ADC_B6;
	// data->aa.A2.me.ADC_array[6] =  ldexpf((float)ADC7, -16)* data->aa.A2.cf.ADC_B7;
	// data->aa.A2.me.ADC_array[7] =  ldexpf((float)ADC8, -16)* data->aa.A2.cf.ADC_B8;
};
void ADC_readCardA3(DS_Data* data){


	//data->aa.A3.me.ADC_array[0] =  ldexpf((float)ReadBlockA.ADC1, -16)* data->aa.A3.cf.ADC_A1;
	//data->aa.A3.me.ADC_array[1] =  ldexpf((float)ReadBlockA.ADC2, -16)* data->aa.A3.cf.ADC_A2;
	//data->aa.A3.me.ADC_array[2] =  ldexpf((float)ReadBlockA.ADC3, -16)* data->aa.A3.cf.ADC_A3;
	//data->aa.A3.me.ADC_array[3] =  ldexpf((float)ReadBlockA.ADC4, -16)* data->aa.A3.cf.ADC_A4;
//
	//data->aa.A3.me.ADC_array[4] =  ldexpf((float)ReadBlockB.ADC1, -16)* data->aa.A3.cf.ADC_B5;
	//data->aa.A3.me.ADC_array[5] =  ldexpf((float)ReadBlockB.ADC2, -16)* data->aa.A3.cf.ADC_B6;
	//data->aa.A3.me.ADC_array[6] =  ldexpf((float)ReadBlockB.ADC3, -16)* data->aa.A3.cf.ADC_B7;
	//data->aa.A3.me.ADC_array[7] =  ldexpf((float)ReadBlockB.ADC4, -16)* data->aa.A3.cf.ADC_B8;
};

void ADC_readCardALL(DS_Data* data){
	ADC_readCardA1(data);
	ADC_readCardA2(data);
	ADC_readCardA3(data);
}

void ADC_WriteConversionFactor(int ADC_ConversionFactor){
	// Example how to set the conversion factor in the ADC Module in the FPGA for ADC slot A1 Block A (4 ADCs)
	adc_values=uz_dataMover_get_data_by_pointer();
	Xil_Out32(XPAR_ADC_A1_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A1_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A2_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A2_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A3_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A3_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	
}
