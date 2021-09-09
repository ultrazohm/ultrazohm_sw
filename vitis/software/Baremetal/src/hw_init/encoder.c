/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel
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

#include "../include/encoder.h"

//----------------------------------------------------
// INITIALIZE & SET THE ENCODER
//----------------------------------------------------
int Encoder_Incremental_Initialize(DS_Data* data){

	int Status = 0;

	int32_t increments_per_turn_elec = (int32_t)((data->mrp.incrementalEncoderResolution*QUADRATURE_FACTOR)/data->mrp.motorPolePairNumber); // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	int32_t increments_per_turn_mech = (int32_t)(data->mrp.incrementalEncoderResolution*QUADRATURE_FACTOR); // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	int32_t pi2_to_increments_elec = (int32_t)(ldexpf(((2.0*M_PI/(data->mrp.incrementalEncoderResolution*QUADRATURE_FACTOR))*data->mrp.motorPolePairNumber),Q24)); // Shift 24 Bit for fixed-point
    int32_t OmegaPerOverSample = (int32_t)(ldexpf(500.0*((2*M_PI)/60),Q11));  //In steps of 500rpm, the Oversampling-Factor is increased in order to have a better speed accuracy. Smaller value, smoother speed but less dynamic. Higher value, less averaging but also higher dynamic.

	//Write down the factor 2*pi/Increments for theta elek. calculation
	Xil_Out32(EncoderPI2_Inc_elek_REG, (int32_t)pi2_to_increments_elec);	// Input to the IP-Core

	//Write down the number of increments per turn ( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xil_Out32(EncoderIncsPerTurn_elek_REG, (int32_t)increments_per_turn_elec);	// Input to the IP-Core

	//Write down the number of increments per turn ( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	Xil_Out32(EncoderIncsPerTurn_mech_REG, (int32_t)increments_per_turn_mech);	// Input to the IP-Core

	//Write down the hardware time of the counter in ms (100 MHz Clock is connected)
    Xil_Out32(Encoder_Time_REG, (int32_t)((ldexpf(((1.0f/25000000.0f)*data->mrp.incrementalEncoderResolution), Q32))/(M_TWOPI)));      // Input to the IP-Core

	//Write down the OverSampling factor for the Speed measurement
	Xil_Out32(Encoder_OmegaPerOverSampl_REG, (int32_t)data->mrp.incrementalEncoderOversamplingFactor);	// Input to the IP-Core

    //Write down the omega value which increments the OverSampling factor for the Speed measurement
    Xil_Out32(Encoder_OmegaPerOverSampl_REG, (int32_t)OmegaPerOverSample);       // Input to the IP-Core

return Status;
}

//Initialize the variables for filtering of the speed encoder
    float 	fSpeed_rpm_Buf[SPEED_BUF_SIZE] = {0.0F};
    u8 		u8Speed_Buf_Inc = 0U;
    float 	fSpeed_rpm = 0.0F;
    float 	fSpeed_rpm_Sum = 0.0F;
    float 	fSpeed_rpm_exp_old = 0.0F;
    float	fSpeed_rpm_exp = 0.0F;
    float	expB = 0.0F;
    float 	expB_old = 0.0F;
    int32_t i_theta_m_old = 0;

void Encoder_UpdateSpeedPosition(DS_Data* data){	// update speed and position in global data struct

	// Get mechanical angle theta prototype
	int32_t i_theta_m  = Xil_In32(Encoder_position_REG);  //Read AXI-register
	float fTheta_mech  = ((float)(i_theta_m) / (float)(data->mrp.incrementalEncoderResolution*QUADRATURE_FACTOR)) * 2.0F * M_PI;


	//Read the speed encoder (own IP-Block) and write to filtered speed for comparison
	int32_t i_speed = Xil_In32(Encoder_rps_REG); //Read AXI-register
	data->av.mechanicalRotorSpeed_filtered = OMEGA_2_RPM * (float)(ldexpf(i_speed, Q11toF));  // Shift 11 Bit for fixed-point //(60/(2*pi)) = 9.5493 Conversion Omega to rpm (Compare Simulink)


	//Manual speed calculation
	//calculate difference between new and old mechanical angle
	/*
	float deltaTheta_mech = fTheta_mech - data->av.theta_mech;
	//Detect 2pi->0 crossing (change bigger than one quarter negative mechanical rotation)
	if (deltaTheta_mech < (-0.5F * M_PI))
	{
		fSpeed_rpm = (deltaTheta_mech + 2.0F * M_PI)/(data->ctrl.samplingPeriod) * OMEGA_2_RPM;
	}
	//Detect 0->2pi crossing (change bigger than one quarter positive mechanical rotation)
	else if (deltaTheta_mech > (0.5F * M_PI))
	{
		fSpeed_rpm = (deltaTheta_mech - 2.0F * M_PI)/(data->ctrl.samplingPeriod) * OMEGA_2_RPM;
	}
	else
	{
		fSpeed_rpm = deltaTheta_mech/(data->ctrl.samplingPeriod) * OMEGA_2_RPM;
	}
	*/

	//Manual speed calculation
	//calculate difference between new and old mechanical angle INCREMENT

	int32_t deltaITheta_mech = i_theta_m - i_theta_m_old;
	//Detect 2pi->0 crossing (change bigger than one quarter negative mechanical rotation)
	if (deltaITheta_mech < (-5000))
	{
		fSpeed_rpm = ((float)(deltaITheta_mech + 19992))/(data->ctrl.samplingPeriod) * 60.0F/20000.0F;
	}
	//Detect 0->2pi crossing (change bigger than one quarter positive mechanical rotation)
	else if (deltaITheta_mech > (5000))
	{
		fSpeed_rpm = ((float)(deltaITheta_mech - 19992))/(data->ctrl.samplingPeriod) * 60.0F/20000.0F;
	}
	else
	{
		fSpeed_rpm = ((float)(deltaITheta_mech))/(data->ctrl.samplingPeriod) * 60.0F/20000.0F;
	}
	i_theta_m_old = i_theta_m;


	//Smoothing 1: Double exponential smoothing
	// Save old variables
	fSpeed_rpm_exp_old = fSpeed_rpm_exp;
	expB_old = expB;
	//FIltering Algorithm
	fSpeed_rpm_exp = SPEED_FIL_ALPHA * fSpeed_rpm + (1-SPEED_FIL_ALPHA) * (fSpeed_rpm_exp_old + expB_old);
	expB = SPEED_FIL_BETA * (fSpeed_rpm_exp - fSpeed_rpm_exp_old) + (1 - SPEED_FIL_BETA) * expB_old;


	//Smoothing 2: moving average

	fSpeed_rpm_Sum -= fSpeed_rpm_Buf[u8Speed_Buf_Inc]; //subtract the old value for the averaging
	fSpeed_rpm_Buf[u8Speed_Buf_Inc] = fSpeed_rpm_exp;		//restore the new value for the averaging
	fSpeed_rpm_Sum += fSpeed_rpm_Buf[u8Speed_Buf_Inc]; //add the new value for the averaging

	u8Speed_Buf_Inc +=1; //Count up for the averaging
	if (u8Speed_Buf_Inc >= SPEED_BUF_SIZE){ //Safe calculation for array overflow
		u8Speed_Buf_Inc = 0;
	}

	//Speed over buffer
	data->av.mechanicalRotorSpeed = fSpeed_rpm_Sum / ((float)SPEED_BUF_SIZE); //Calculate mean value for the speed
	//data->av.mechanicalRotorSpeed = fSpeed_rpm_exp;

	//Write theta mech
	data->av.theta_mech = (float)i_theta_m;//fTheta_mech;

	// Get electrical angle theta
	int32_t i_theta_e  = Xil_In32(Encoder_theta_e_REG);  //Read AXI-register
	data->av.theta_elec  = (float)(ldexpf(i_theta_e, Q20toF));  // Shift 20 Bit for fixed-point



	/*
	// low-pass filter of mechanical speed
	static float speed_lpf_mem_in = 0.0f;
	static float speed_lpf_mem_out = 0.0f;
	data->av.mechanicalRotorSpeed_filtered = LPF1(	data->av.mechanicalRotorSpeed, &speed_lpf_mem_in, &speed_lpf_mem_out,
													data->ctrl.samplingFrequency, data->mrp.IncEncoderLPF_freq);
	*/
}
