/******************************************************************************
 *
 * encoder.c
 *
 * Copyright (C) 2018 Institute ELSYS, TH Nürnberg, All rights reserved.
 *
 *  Created on: 21.08.2016
 *      Author: Sebastian Wendel (SW)
 *
******************************************************************************/

#include "../include/encoder.h"
#include "../defines.h"


//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------
int Initialize_Encoder(DS_Data* data){

	int Status = 0;

	Xint32 increments_per_turn_elec = (Xint32)((data->mrp.incrementalEncoderResolution*4.0)/data->mrp.motorPolePairNumber); // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xint32 increments_per_turn_mech = (Xint32)(data->mrp.incrementalEncoderResolution*4.0); // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xint32 pi2_to_increments_elec = (Xint32)(ldexpf(((2.0*PI/(data->mrp.incrementalEncoderResolution*4.0))*data->mrp.motorPolePairNumber),Q24)); // Shift 24 Bit for fixed-point
	Xint32 pi2_to_increments_mech = (Xint32)(ldexpf((2.0*PI/(data->mrp.incrementalEncoderResolution*4.0)),Q24)); // Shift 24 Bit for fixed-point
	Xint32 oversampling_inverse_factor_for_speed = (Xint32)(ldexpf((1.0/data->mrp.incrementalEncoderOversamplingFactor),Q15)); // Shift 15 Bit for fixed-point
	Xint32 hardware_timer_ms = (Xint32)(ldexpf(((1.0f/50000000.0f)*data->mrp.incrementalEncoderResolution),Q26)); // with 50MHz AXI-Timer // Shift 26 Bit for fixed-point

	//Write down the factor 2*pi/Increments for theta elek. calculation
	//Xil_Out32(EncoderPI2_Inc_elek_REG, (Xint32)PI2_TO_INCREMENTS_ELEK);	// Input to the IP-Core
	Xil_Out32(EncoderPI2_Inc_elek_REG, (Xint32)pi2_to_increments_elec);	// Input to the IP-Core

	//Write down the factor 2*pi/Increments for theta mech. calculation
	//Xil_Out32(EncoderPI2_Inc_mech_REG, (Xint32)PI2_TO_INCREMENTS_MECH);	// Input to the IP-Core
	Xil_Out32(EncoderPI2_Inc_mech_REG, (Xint32)pi2_to_increments_mech);	// Input to the IP-Core

	//Write down the number of increments per turn ( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	//Xil_Out32(EncoderIncsPerTurn_elek_REG, (Xint32)INCREMENTS_PER_TURN_ELEK);	// Input to the IP-Core
	Xil_Out32(EncoderIncsPerTurn_elek_REG, (Xint32)increments_per_turn_elec);	// Input to the IP-Core

	//Write down the number of increments per turn ( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	//Xil_Out32(EncoderIncsPerTurn_mech_REG, (Xint32)INCREMENTS_PER_TURN_MECH);	// Input to the IP-Core
	Xil_Out32(EncoderIncsPerTurn_mech_REG, (Xint32)increments_per_turn_mech);	// Input to the IP-Core

	//Write down the hardware time of the counter in ms (100 MHz Clock is connected)
	//Xil_Out32(Encoder_Time_REG, (Xint32)HARDWARE_TIMER_ms);	// Input to the IP-Core
	Xil_Out32(Encoder_Time_REG, (Xint32)hardware_timer_ms);	// Input to the IP-Core

	//Write down the OverSampling factor for the Speed measurement
	//Xil_Out32(OverSamplingFactorREG, (Xint32)OVERSAMPLING_FACTOR_FOR_SPEED);	// Input to the IP-Core
	Xil_Out32(OverSamplingFactorREG, (Xint32)data->mrp.incrementalEncoderOversamplingFactor);	// Input to the IP-Core

	//Write down the Inverse factor of the OverSampling factor for the Speed measurement
	//Xil_Out32(OverSamplingFactorInverseREG, (Xint32)OVERSAMPLING_INVERSE_FACTOR_FOR_SPEED);	// Input to the IP-Core
	Xil_Out32(OverSamplingFactorInverseREG, (Xint32)oversampling_inverse_factor_for_speed);	// Input to the IP-Core

return Status;
}
