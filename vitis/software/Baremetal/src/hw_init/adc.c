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

void ADC_readCardA1(DS_Data* data){

	static int16_t *ADC_TCM = (int16_t*)ADC_A1_ChA1_REG;

	data->aa.A1.me.ADC_array[0] =  ((float)ADC_TCM[0]) / (1<<Q16) * 10;
	data->aa.A1.me.ADC_array[1] =  ((float)ADC_TCM[1]) / (1<<Q16) * 10;
	data->aa.A1.me.ADC_array[2] =  ((float)ADC_TCM[2]) / (1<<Q16) * 10;
	data->aa.A1.me.ADC_array[3] =  ((float)ADC_TCM[3]) / (1<<Q16) * 10;
	data->aa.A1.me.ADC_array[4] =  ((float)ADC_TCM[4]) / (1<<Q16) * 10;
	data->aa.A1.me.ADC_array[5] =  ((float)ADC_TCM[5]) / (1<<Q16) * 10;
	data->aa.A1.me.ADC_array[6] =  ((float)ADC_TCM[6]) / (1<<Q16) * 10;
	data->aa.A1.me.ADC_array[7] =  ((float)ADC_TCM[7]) / (1<<Q16) * 10;
}

void ADC_readCardA2(DS_Data* data){
/*	ADCread_union ReadBlockA;
	ADCread_union ReadBlockB;

	ReadBlockA.ADC_Block_64bit = Xil_In64(ADC_A2_ChA1_REG);
	ReadBlockB.ADC_Block_64bit = Xil_In64(ADC_A2_ChB5_REG);

	// bitshift operation of -16 digits, because it is an 16-bit ADC
	// Conversion Factor is defined in main.c InitializeDataStructure
	data->aa.A2.me.ADC_array[0] =  ldexpf((float)ReadBlockA.ADC1, -16)* 10;//9.990244; //data->aa.A2.cf.ADC_A1;
	data->aa.A2.me.ADC_array[1] =  ldexpf((float)ReadBlockA.ADC2, -16)* 10;//9.990244; // data->aa.A2.cf.ADC_A2;
	data->aa.A2.me.ADC_array[2] =  ldexpf((float)ReadBlockA.ADC3, -16)* 10;//8.192000; //data->aa.A2.cf.ADC_A3;
	data->aa.A2.me.ADC_array[3] =  ldexpf((float)ReadBlockA.ADC4, -16)* 10;//8.192000; //data->aa.A2.cf.ADC_A4;

	data->aa.A2.me.ADC_array[4] =  ldexpf((float)ReadBlockB.ADC1, -16)* 10;//data->aa.A2.cf.ADC_B5;
	data->aa.A2.me.ADC_array[5] =  ldexpf((float)ReadBlockB.ADC2, -16)* 10;//data->aa.A2.cf.ADC_B6;
	data->aa.A2.me.ADC_array[6] =  ldexpf((float)ReadBlockB.ADC3, -16)* 10;//data->aa.A2.cf.ADC_B7;
	data->aa.A2.me.ADC_array[7] =  ldexpf((float)ReadBlockB.ADC4, -16)* 10;//data->aa.A2.cf.ADC_B8;
	*/
	static int16_t *ADC_TCM = (int16_t*)ADC_A2_ChA1_REG;

	data->aa.A2.me.ADC_array[0] =  ((float)ADC_TCM[0]) / (1<<16) * 10;
	data->aa.A2.me.ADC_array[1] =  ((float)ADC_TCM[1]) / (1<<16) * 10;
	data->aa.A2.me.ADC_array[2] =  ((float)ADC_TCM[2]) / (1<<16) * 10;
	data->aa.A2.me.ADC_array[3] =  ((float)ADC_TCM[3]) / (1<<16) * 10;
	data->aa.A2.me.ADC_array[4] =  ((float)ADC_TCM[4]) / (1<<16) * 10;
	data->aa.A2.me.ADC_array[5] =  ((float)ADC_TCM[5]) / (1<<16) * 10;
	data->aa.A2.me.ADC_array[6] =  ((float)ADC_TCM[6]) / (1<<16) * 10;
	data->aa.A2.me.ADC_array[7] =  ((float)ADC_TCM[7]) / (1<<16) * 10;

};
void ADC_readCardA3(DS_Data* data){
	ADCread_union ReadBlockA;
	ADCread_union ReadBlockB;

	ReadBlockA.ADC_Block_64bit = Xil_In64(ADC_A3_ChA1_REG);
	ReadBlockB.ADC_Block_64bit = Xil_In64(ADC_A3_ChB5_REG);

	data->aa.A3.me.ADC_array[0] =  ldexpf((float)ReadBlockA.ADC1, -16)* 10;//  data->aa.A3.cf.ADC_A1;
	data->aa.A3.me.ADC_array[1] =  ldexpf((float)ReadBlockA.ADC2, -16)* 10;//  data->aa.A3.cf.ADC_A2;
	data->aa.A3.me.ADC_array[2] =  ldexpf((float)ReadBlockA.ADC3, -16)* 10;//  data->aa.A3.cf.ADC_A3;
	data->aa.A3.me.ADC_array[3] =  ldexpf((float)ReadBlockA.ADC4, -16)* 10;//  data->aa.A3.cf.ADC_A4;

	data->aa.A3.me.ADC_array[4] =  ldexpf((float)ReadBlockB.ADC1, -16)* 10;//  data->aa.A3.cf.ADC_B5;
	data->aa.A3.me.ADC_array[5] =  ldexpf((float)ReadBlockB.ADC2, -16)* 10;//  data->aa.A3.cf.ADC_B6;
	data->aa.A3.me.ADC_array[6] =  ldexpf((float)ReadBlockB.ADC3, -16)* 10;//  data->aa.A3.cf.ADC_B7;
	data->aa.A3.me.ADC_array[7] =  ldexpf((float)ReadBlockB.ADC4, -16)* 10;//  data->aa.A3.cf.ADC_B8;
};

void ADC_readCardALL(DS_Data* data){
	ADC_readCardA1(data);
	//ADC_readCardA2(data);
	//ADC_readCardA3(data);
}

void ADC_WriteConversionFactor(int ADC_ConversionFactor){
	// Example how to set the conversion factor in the ADC Module in the FPGA for ADC slot A1 Block A (4 ADCs)
	
	Xil_Out32(XPAR_ADC_A1_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A1_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A2_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A2_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A3_ADC_BLOCK_A_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	Xil_Out32(XPAR_ADC_A3_ADC_BLOCK_B_BASEADDR + Conversion_Factor_1_ADC_Module_LVDS_V2_ip , ADC_ConversionFactor);
	
}
