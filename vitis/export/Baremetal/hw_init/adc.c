/******************************************************************************
 *
 * adc.c
 *
 * Copyright (C) 2020 UltraZohm Community, All rights reserved.
 *
 *  Created on: 08.09.2020
 *      Author: Eyke Liegmann (EL)
 *
******************************************************************************/
#include "../include/adc.h"
#include "../defines.h"

void ADC_readCardA1(DS_Data* data){

	// read all 8 ADC values from Analog Adapter card slot A1
	Xint16 ADC1 = Xil_In16(ADC_A1_ChA1_REG);
	Xint16 ADC2 = Xil_In16(ADC_A1_ChA2_REG);
	Xint16 ADC3 = Xil_In16(ADC_A1_ChA3_REG);
	Xint16 ADC4 = Xil_In16(ADC_A1_ChA4_REG);
	Xint16 ADC5 = Xil_In16(ADC_A1_ChB5_REG);
	Xint16 ADC6 = Xil_In16(ADC_A1_ChB6_REG);
	Xint16 ADC7 = Xil_In16(ADC_A1_ChB7_REG);
	Xint16 ADC8 = Xil_In16(ADC_A1_ChB8_REG);

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
}

void ADC_readCardA2(DS_Data* data){
	// read all 8 ADC values from Analog Adapter card slot A1
	Xint16 ADC1 = Xil_In16(ADC_A2_ChA1_REG);
	Xint16 ADC2 = Xil_In16(ADC_A2_ChA2_REG);
	Xint16 ADC3 = Xil_In16(ADC_A2_ChA3_REG);
	Xint16 ADC4 = Xil_In16(ADC_A2_ChA4_REG);
	Xint16 ADC5 = Xil_In16(ADC_A2_ChB5_REG);
	Xint16 ADC6 = Xil_In16(ADC_A2_ChB6_REG);
	Xint16 ADC7 = Xil_In16(ADC_A2_ChB7_REG);
	Xint16 ADC8 = Xil_In16(ADC_A2_ChB8_REG);

	// bitshift operation of -16 digits, because it is an 16-bit ADC
	// Conversion Factor is defined in main.c InitializeDataStructure
	data->aa.A2.me.ADC_array[0] =  ldexpf((float)ADC1, -16)* data->aa.A2.cf.ADC_A1;
	data->aa.A2.me.ADC_array[1] =  ldexpf((float)ADC2, -16)* data->aa.A2.cf.ADC_A2;
	data->aa.A2.me.ADC_array[2] =  ldexpf((float)ADC3, -16)* data->aa.A2.cf.ADC_A3;
	data->aa.A2.me.ADC_array[3] =  ldexpf((float)ADC4, -16)* data->aa.A2.cf.ADC_A4;
	data->aa.A2.me.ADC_array[4] =  ldexpf((float)ADC5, -16)* data->aa.A2.cf.ADC_B5;
	data->aa.A2.me.ADC_array[5] =  ldexpf((float)ADC6, -16)* data->aa.A2.cf.ADC_B6;
	data->aa.A2.me.ADC_array[6] =  ldexpf((float)ADC7, -16)* data->aa.A2.cf.ADC_B7;
	data->aa.A2.me.ADC_array[7] =  ldexpf((float)ADC8, -16)* data->aa.A2.cf.ADC_B8;
};
void ADC_readCardA3(DS_Data* data){
	ADCread_union ReadBlockA;
	ADCread_union ReadBlockB;

	ReadBlockA.ADC_Block_64bit = Xil_In64(ADC_A3_ChA1_REG);
	ReadBlockB.ADC_Block_64bit = Xil_In64(ADC_A3_ChB5_REG);

	data->aa.A3.me.ADC_array[0] =  ldexpf((float)ReadBlockA.ADC1, -16)* data->aa.A3.cf.ADC_A1;
	data->aa.A3.me.ADC_array[1] =  ldexpf((float)ReadBlockA.ADC2, -16)* data->aa.A3.cf.ADC_A2;
	data->aa.A3.me.ADC_array[2] =  ldexpf((float)ReadBlockA.ADC3, -16)* data->aa.A3.cf.ADC_A3;
	data->aa.A3.me.ADC_array[3] =  ldexpf((float)ReadBlockA.ADC4, -16)* data->aa.A3.cf.ADC_A4;

	data->aa.A3.me.ADC_array[4] =  ldexpf((float)ReadBlockB.ADC1, -16)* data->aa.A3.cf.ADC_B5;
	data->aa.A3.me.ADC_array[5] =  ldexpf((float)ReadBlockB.ADC2, -16)* data->aa.A3.cf.ADC_B6;
	data->aa.A3.me.ADC_array[6] =  ldexpf((float)ReadBlockB.ADC3, -16)* data->aa.A3.cf.ADC_B7;
	data->aa.A3.me.ADC_array[7] =  ldexpf((float)ReadBlockB.ADC4, -16)* data->aa.A3.cf.ADC_B8;

	/*
	Naive implementation reading one 16 bit register after the other
	// read all 8 ADC values from Analog Adapter card slot A1
	Xint16 ADC1 = Xil_In16(ADC_A3_ChA1_REG);
	Xint16 ADC2 = Xil_In16(ADC_A3_ChA2_REG);
	Xint16 ADC3 = Xil_In16(ADC_A3_ChA3_REG);
	Xint16 ADC4 = Xil_In16(ADC_A3_ChA4_REG);
	Xint16 ADC5 = Xil_In16(ADC_A3_ChB5_REG);
	Xint16 ADC6 = Xil_In16(ADC_A3_ChB6_REG);
	Xint16 ADC7 = Xil_In16(ADC_A3_ChB7_REG);
	Xint16 ADC8 = Xil_In16(ADC_A3_ChB8_REG);

	// bitshift operation of -16 digits, because it is an 16-bit ADC
	// Conversion Factor is defined in main.c InitializeDataStructure
	data->aa.A3.me.ADC_array[0] =  ldexpf((float)ADC1, -16)* data->aa.A3.cf.ADC_A1;
	data->aa.A3.me.ADC_array[1] =  ldexpf((float)ADC2, -16)* data->aa.A3.cf.ADC_A2;
	data->aa.A3.me.ADC_array[2] =  ldexpf((float)ADC3, -16)* data->aa.A3.cf.ADC_A3;
	data->aa.A3.me.ADC_array[3] =  ldexpf((float)ADC4, -16)* data->aa.A3.cf.ADC_A4;
	data->aa.A3.me.ADC_array[4] =  ldexpf((float)ADC5, -16)* data->aa.A3.cf.ADC_B5;
	data->aa.A3.me.ADC_array[5] =  ldexpf((float)ADC6, -16)* data->aa.A3.cf.ADC_B6;
	data->aa.A3.me.ADC_array[6] =  ldexpf((float)ADC7, -16)* data->aa.A3.cf.ADC_B7;
	data->aa.A3.me.ADC_array[7] =  ldexpf((float)ADC8, -16)* data->aa.A3.cf.ADC_B8;

	*/
};

void ADC_readCardALL(DS_Data* data){
	ADC_readCardA1(data);
	ADC_readCardA2(data);
	ADC_readCardA3(data);
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

void DQTransformation_Initialize(DS_Data* data){
	//Write down the theta-offset
	Xil_Out32(Trans_123_dq_theta_offset_REG, (Xint32)(ldexpf(data->mrp.incrementalEncoderOffset, Q20)));	// Shift 20 Bit for fixed-point // Input to the IP-Core
}
