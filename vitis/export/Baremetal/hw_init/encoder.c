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



//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------
int Encoder_Incremental_Initialize(DS_Data* data){

	int Status = 0;
    int QuadratureFactor = 4.0;

	Xint32 increments_per_turn_elec = (Xint32)((data->mrp.incrementalEncoderResolution*QuadratureFactor)/data->mrp.motorPolePairNumber); // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xint32 increments_per_turn_mech = (Xint32)(data->mrp.incrementalEncoderResolution*QuadratureFactor); // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xint32 pi2_to_increments_elec = (Xint32)(ldexpf(((2.0*PI/(data->mrp.incrementalEncoderResolution*QuadratureFactor))*data->mrp.motorPolePairNumber),Q24)); // Shift 24 Bit for fixed-point
	//Xint32 pi2_to_increments_mech = (Xint32)(ldexpf((2.0*PI/(data->mrp.incrementalEncoderResolution*QuadratureFactor)),Q24)); // Shift 24 Bit for fixed-point
	//Xint32 oversampling_inverse_factor_for_speed = (Xint32)(ldexpf((1.0/data->mrp.incrementalEncoderOversamplingFactor),Q15)); // Shift 15 Bit for fixed-point
	//Xint32 hardware_timer_ms = (Xint32)(ldexpf(((1.0f/50000000.0f)*data->mrp.incrementalEncoderResolution),Q26)); // with 50MHz AXI-Timer // Shift 26 Bit for fixed-point
    Xint32 OmegaPerOverSample = (Xint32)(ldexpf(500.0*((2*PI)/60),Q11));  //In steps of 500rpm, the Oversampling-Factor is increased in order to have a better speed accuracy. Smaller value, smoother speed but less dynamic. Higher value, less averaging but also higher dynamic.

	//Write down the factor 2*pi/Increments for theta elek. calculation
	Xil_Out32(EncoderPI2_Inc_elek_REG, (Xint32)pi2_to_increments_elec);	// Input to the IP-Core

	//Write down the factor 2*pi/Increments for theta mech. calculation
	//Xil_Out32(EncoderPI2_Inc_mech_REG, (Xint32)pi2_to_increments_mech);	// Input to the IP-Core

	//Write down the number of increments per turn ( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xil_Out32(EncoderIncsPerTurn_elek_REG, (Xint32)increments_per_turn_elec);	// Input to the IP-Core

	//Write down the number of increments per turn ( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xil_Out32(EncoderIncsPerTurn_mech_REG, (Xint32)increments_per_turn_mech);	// Input to the IP-Core

	//Write down the hardware time of the counter in ms (100 MHz Clock is connected)
//	Xil_Out32(Encoder_Time_REG, (Xint32)hardware_timer_ms);	// Input to the IP-Core
    Xil_Out32(Encoder_Time_REG, (Xint32)((ldexpf(((1.0f/25000000.0f)*data->mrp.incrementalEncoderResolution), Q32))/(2*PI)));      // Input to the IP-Core

	//Write down the OverSampling factor for the Speed measurement
	//Xil_Out32(OverSamplingFactorREG, (Xint32)OVERSAMPLING_FACTOR_FOR_SPEED);	// Input to the IP-Core
	Xil_Out32(Encoder_OmegaPerOverSampl_REG, (Xint32)data->mrp.incrementalEncoderOversamplingFactor);	// Input to the IP-Core

    //Write down the omega value which increments the OverSampling factor for the Speed measurement
    Xil_Out32(Encoder_OmegaPerOverSampl_REG, (Xint32)OmegaPerOverSample);       // Input to the IP-Core

return Status;
}

//Initialize the variables for the speed encoder
Xfloat32 	fSpeed_rpm_Buf[SPEED_BUF_SIZE] = {0,0};
u8 			u8Speed_Buf_Inc =0;
Xfloat32 	fSpeed_rpm_Mean = 0;

void Encoder_UpdateSpeedPosition(DS_Data* data){	// update speed and position in global data struct

	//Read the speed encoder (own IP-Block)
	Xint32 i_speed = Xil_In32(Encoder_rps_REG); //Read AXI-register
	Xfloat32 fSpeed_rpm = 9.5492966 * (Xfloat32)(ldexpf(i_speed, Q11toF));  // Shift 11 Bit for fixed-point //(60/(2*pi)) = 9.5493 Conversion Omega to rpm (Compare Simulink)

	fSpeed_rpm_Mean -= fSpeed_rpm_Buf[u8Speed_Buf_Inc]; //subtract the old value for the averaging
	fSpeed_rpm_Buf[u8Speed_Buf_Inc] = fSpeed_rpm;		//restore the new value for the averaging
	fSpeed_rpm_Mean += fSpeed_rpm_Buf[u8Speed_Buf_Inc]; //add the new value for the averaging

	u8Speed_Buf_Inc +=1; //Count up for the averaging
	if (u8Speed_Buf_Inc >= SPEED_BUF_SIZE){ //Safe calculation for array overflow
		u8Speed_Buf_Inc = 0;
	}

	//Speed over buffer
	data->av.mechanicalRotorSpeed = fSpeed_rpm_Mean * SPEED_BUF_SIZE_INVERS; //Calculate mean value for the speed

	// Get electrical angle theta
	Xint32 i_theta_e  = Xil_In32(Encoder_theta_e_REG);  //Read AXI-register
	data->av.theta_elec  = (Xfloat32)(ldexpf(i_theta_e, Q20toF));  // Shift 20 Bit for fixed-point

	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(	data->av.mechanicalRotorSpeed, &speed_lpf_mem_in, &speed_lpf_mem_out,
													data->ctrl.samplingFrequency, data->mrp.IncEncoderLPF_freq);

}
