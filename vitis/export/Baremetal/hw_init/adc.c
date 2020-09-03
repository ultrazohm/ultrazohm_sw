/******************************************************************************
 *
 * adc.c
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 22.08.2019
*      Author: Wendel Sebastian (SW)
*
* Description: Zynq UltraScale+
*
******************************************************************************/

#include "../include/adc.h"
#include "../defines.h"

//The following minus for the conversion factor is necessary, because at the first version of the ADC Adapter card from Eyke, the polarity is wrong
Xint32 ADCConvFactor_1  = -0.000732398*pow(2, 32); //(1<<32); //2^32 is necessary, because we have have a high Bit accuracy and 32 Bit by using AXI4. 0.000732398 is the conversion factor for the LEM CASR 18A current sensor. 0.000732398*pow(2, 32)=3145625


//----------------------------------------------------
// INITIALIZE ADC-CONVERSION-MODULE
//----------------------------------------------------
int Initialize_ADC_CONVERSION(){

	int Status = 0;

	//Write down the conversion gain factor for the 6A current LEM
	//Xil_Out32(ADC_ConversionFactor_1_REG, (Xint32)(ADCConvFactor_1));

	//Write down the offset factor for the ADC. However, this factor is only used, when the check box "ADC_USER_OFFSET" in the IP Core in Vivado is activated.
	//Xil_Out32(ADC_OffsetFactor_1_REG, (Xint32)(32768)); //32768 = 2^15 = ADC middle

return Status;
}


//----------------------------------------------------
// INITIALIZE ADC-CONVERSION-MODULE
//----------------------------------------------------
int Initialize_TRANS_123_DQ_CONVERSION(DS_Data* data){

	int Status = 0;

	//Write down the theta-offset
	Xil_Out32(Trans_123_dq_theta_offset_REG, (Xint32)(ldexpf(data->mrp.incrementalEncoderOffset, Q20)));	// Shift 20 Bit for fixed-point // Input to the IP-Core

return Status;
}
