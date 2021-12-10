/******************************************************************************
* Copyright 2021 Sebastian Wendel, Philipp Löhdefink
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

#include "../include/ipc_ARM.h"
#include <string.h>

#include "../include/javascope.h"
#include "../main.h"


#define SCOPE_OFFSET_bits 0x00
#define MOTORCONTROL_OFFSET_bits 1000

uint16_t 	i_ISR_IPC_LifeCheck=0;
uint32_t ADCconvFactor_Hbytes = 0;
uint32_t ADCconvFactor_Lbytes = 0;
uint16_t ADCconvFactorReadRequest	= 0;
float ADCconvFactorReadback = 0.0;


extern float *js_ch_observable[JSO_ENDMARKER];
extern float *js_ch_selected[JS_CHANNELS];
extern float sin1amp;
extern _Bool bNewControlMethodAvailable;
extern uint32_t js_status_BareToRTOS;

void ipc_Control_func(uint32_t msgId, float value, DS_Data* data)
{
	/* Bit 0 - ui16_drv_enable */
	if (data->cw.enableSystem == true) {
		js_status_BareToRTOS |= 1 << 0;
	} else {
		js_status_BareToRTOS &= ~(1 << 0);
	}
	/* Bit 1 - PIR_ENABLE */
	if (data->cw.enableControl == true) {
		js_status_BareToRTOS |= 1 << 1;
	} else {
		js_status_BareToRTOS &= ~(1 << 1);
	}
	/* Bit 2 - IDENT_LQ */
	if (data->pID.identLq == 1) {
		js_status_BareToRTOS |= 1 << 2;
	} else {
		js_status_BareToRTOS &= ~(1 << 2);
	}
	/* Bit 3 - CURRENT_CONTROL */
	if (data->cw.ControlReference == CurrentControl){
		js_status_BareToRTOS |= 1 << 3;
	} else {
		js_status_BareToRTOS &= ~(1 << 3);
	}
	/* Bit 4 - SPEED_CONTROL */
	if (data->cw.ControlReference == SpeedControl){
		js_status_BareToRTOS |= 1 << 4;
	} else {
		js_status_BareToRTOS &= ~(1 << 4);
	}
	/* Bit 5 - ADD VIBRATION */
	if (data->pID.VibON == 1) {
		js_status_BareToRTOS |= 1 << 5;
	} else {
		js_status_BareToRTOS &= ~(1 << 5);
	}
	/* Bit 6 - IDorNOT */
	//if (data->pID.MotorID == 1) {
	if (data->cw.enableParameterID == true) {
		js_status_BareToRTOS |= 1 << 6;
	} else {
		js_status_BareToRTOS &= ~(1 << 6);
	}
	/* Bit 7 - identROnline */
	if (data->pID.identR == 1) {
		js_status_BareToRTOS |= 1 << 7;
	} else {
		js_status_BareToRTOS &= ~(1 << 7);
	}


	// HANDLE RECEIVED MESSAGE
	if ( msgId != 0)
	{
		//GENERAL VARIABLES
		if (msgId == 1) // state++
		{
			// do something
		}
		else if (msgId == 2) // Stop
		{
			data->cw.enableSystem = false;
			data->cw.enableControl = false;
		}
		else if (msgId == 16) // Reference frequency
		{
			if (value > 50)
				data->rasv.referenceFrequency = 50;
			else if(value < 0)
				data->rasv.referenceFrequency = 0;
			else
				data->rasv.referenceFrequency = value;
		}
		else if (msgId == 17)
		{
			sin1amp = (float)value;
		}
		else if (msgId == 21) // Reference Current Control Angle in �
		{
			data->rasv.currentControlAngle = value;
		}
		else if (msgId == 112) // reset all Errors
		{
			data->er.dcLinkOvervoltageOccured = true;
			data->er.maximumContinuousCurrentExceeded = true;
			data->er.maximumShortTermCurrentReached = true;
			data->er.pwmFrequencyError = true;

		}
		else if (msgId == 204) // SELECT_DATA_CH1_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[0] = js_ch_observable[(uint32_t)value];
			}
		}
		else if (msgId == 205) // SELECT_DATA_CH2_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[1] = js_ch_observable[(uint32_t)value];
			}
		}
		else if (msgId == 206) // SELECT_DATA_CH3_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[2] = js_ch_observable[(uint32_t)value];
			}
		}
		else if (msgId == 207) // SELECT_DATA_CH4_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[3] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 208) // SELECT_DATA_CH5_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[4] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 209) // SELECT_DATA_CH6_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[5] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 210) // SELECT_DATA_CH7_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[6] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 211) // SELECT_DATA_CH8_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[7] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 212) // SELECT_DATA_CH9_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[8] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 213) // SELECT_DATA_CH10_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[9] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 214) // SELECT_DATA_CH11_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[10] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 215) // SELECT_DATA_CH12_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[11] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 216) // SELECT_DATA_CH13_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[12] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 217) // SELECT_DATA_CH14_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[13] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 218) // SELECT_DATA_CH15_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[14] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 219) // SELECT_DATA_CH16_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[15] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 220) // SELECT_DATA_CH17_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[16] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 221) // SELECT_DATA_CH18_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[17] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 222) // SELECT_DATA_CH19_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[18] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 223) // SELECT_DATA_CH20_bits
		{
			if ( value >= 0 && value < JSO_ENDMARKER )
			{
				js_ch_selected[19] = js_ch_observable[(uint32_t)value];

			}
		}
		else if (msgId == 0x01+MOTORCONTROL_OFFSET_bits) // ConverterEnable
		{
			data->cw.enableSystem = true;
		}
		else if (msgId == 0x02+MOTORCONTROL_OFFSET_bits) // ConverterDisable
		{
			data->cw.enableSystem = false;
		}
		else if (msgId == 0x03+MOTORCONTROL_OFFSET_bits) // ControlEnable
		{
			data->cw.enableControl = true;
		}
		else if (msgId == 0x04+MOTORCONTROL_OFFSET_bits) // ControlDisable
		{
			data->cw.enableControl = false;
		}
		else if (msgId == 0x041+MOTORCONTROL_OFFSET_bits) // ResetError
		{
			data->er.communicationTimeoutOccured = true;
			data->er.dcLinkOvervoltageOccured = true;
			data->er.maximumContinuousCurrentExceeded = true;
			data->er.maximumShortTermCurrentReached = true;
			data->er.pwmFrequencyError = true;
		}
		else if (msgId == 0x110+MOTORCONTROL_OFFSET_bits) // referenceTorque (1000 + 0x110 = 1272)
		{
			data->rasv.referenceTorque = (float)value * 0.001; //mNm
		}
		else if (msgId == 0x300+MOTORCONTROL_OFFSET_bits)
			data->cw.rotorAngleEstimationMode= (rotorAngleEstimationMethod)value;
		else if (msgId == 0x320+MOTORCONTROL_OFFSET_bits){ //digital hall
			if(value ==1){
				data->cw.rotorAngleEstimationMode = hallSensors120Degree;
			}
			if(value ==2){
				data->cw.rotorAngleEstimationMode = hallSensors180Degree;
			}
		}
		else if (msgId == 0x340+MOTORCONTROL_OFFSET_bits)
			data->mrp.incrementalEncoderResolution = (float)value;
		else if (msgId == 0x341+MOTORCONTROL_OFFSET_bits)
			data->mrp.motorMaximumSpeed= (float)value;
		else if (msgId == 0x342+MOTORCONTROL_OFFSET_bits)
			data->mrp.incrementalEncoderOffset= (float)value;

		//ADC
		else if (msgId == 0x350+MOTORCONTROL_OFFSET_bits)
			ADCconvFactor_Hbytes = value;
		else if (msgId == 0x351+MOTORCONTROL_OFFSET_bits) {
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorIph = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes & 0xFFFF))*1e-9;
		}
		else if (msgId == 0x352+MOTORCONTROL_OFFSET_bits)
			ADCconvFactor_Hbytes = value;
		else if (msgId == 0x353+MOTORCONTROL_OFFSET_bits) {
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorVph = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
		}
		else if (msgId == 0x354+MOTORCONTROL_OFFSET_bits)
			ADCconvFactor_Hbytes = value;
		else if (msgId == 0x355+MOTORCONTROL_OFFSET_bits) {
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorIdc = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
		}
		else if (msgId == 0x356+MOTORCONTROL_OFFSET_bits)
			ADCconvFactor_Hbytes = value;
		else if (msgId == 0x357+MOTORCONTROL_OFFSET_bits) {
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorVdc = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
		}
		else if (msgId == 0x358+MOTORCONTROL_OFFSET_bits)
			ADCconvFactor_Hbytes = value;
		else if (msgId == 0x359+MOTORCONTROL_OFFSET_bits) {
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorTrq = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
		}
		else if (msgId == 0x360+MOTORCONTROL_OFFSET_bits)
			ADCconvFactor_Hbytes = value;
		else if (msgId == 0x361+MOTORCONTROL_OFFSET_bits) {
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorTmp = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
		}
		else if (msgId == 0x369+MOTORCONTROL_OFFSET_bits) {
			ADCconvFactorReadRequest = value;
			switch (ADCconvFactorReadRequest) {

			case (0x350+MOTORCONTROL_OFFSET_bits):
				data->mrp.ADCconvFactorReadback = data->mrp.ADCConversionFactorIph;
				break;
			case (0x352+MOTORCONTROL_OFFSET_bits):
				data->mrp.ADCconvFactorReadback = data->mrp.ADCConversionFactorVph;
				break;
			case (0x354+MOTORCONTROL_OFFSET_bits):
				data->mrp.ADCconvFactorReadback = data->mrp.ADCConversionFactorIdc;
				break;
			case (0x356+MOTORCONTROL_OFFSET_bits):
				data->mrp.ADCconvFactorReadback = data->mrp.ADCConversionFactorVph;
				break;
			case (0x358+MOTORCONTROL_OFFSET_bits):
				data->mrp.ADCconvFactorReadback = data->mrp.ADCConversionFactorTrq;
				break;
			case (0x360+MOTORCONTROL_OFFSET_bits):
				data->mrp.ADCconvFactorReadback = data->mrp.ADCConversionFactorTmp;
				break;
			default:
				ADCconvFactorReadback = 0.999;
				break;
			}
		}

		//MODULATION
		else if (msgId == 0x600+MOTORCONTROL_OFFSET_bits)
			data->cw.modulationMode = (gatesignalsModulationMethod)value;

		//CONTROL METHOD
		else if (msgId == 0x400+ MOTORCONTROL_OFFSET_bits) // CONTROL_METHOD (1000 + 0x400 = 2024)
			if((data->cw.enableSystem == false)&&(data->cw.enableControl == false)){ //Only allow a new control method, if the system is in a stable status
				data->cw.ControlMethod =  (currentControlMethod)value;
				bNewControlMethodAvailable = true;  //Activate the Flag in order to initialize the IP Cores and functions after a new control method arrives, only once!
			}else{
				//do nothing, keep the old control method
			}

		//CONTROL REFERENCE METHOD
		else if (msgId == 0x401+ MOTORCONTROL_OFFSET_bits) // CONTROL_REFERENCE (1000 + 0x401 = 2025)
			if((data->cw.enableControl == false)){ //Only allow a new control method, if the control is not running currently
				data->cw.ControlReference= (ControlReference)value;
			}else{
				//do nothing, keep the old control method
			}

		//FOC CONTROL
		else if (msgId == 0x402 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.foc.cc.Kp_id = (float)value * 0.001;
		else if (msgId == 0x403 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.foc.cc.Tn_id = (float)value * 0.0001;
		else if (msgId == 0x404 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.foc.cc.Kp_iq = (float)value * 0.001;
		else if (msgId == 0x405 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.foc.cc.Tn_iq = (float)value * 0.0001;
		else if (msgId == 0x406 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.foc.sc.Kp = (float)value * 0.001;
		else if (msgId == 0x407 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.foc.sc.Tn = (float)value * 0.0001;
		else if (msgId == 0x408 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.foc.cc.FOCFeedForward = (_Bool)value;

		//MPC CONTROL
		else if (msgId == 0x421 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.mpc.fcs.lambda_dU = (float)value * 0.001;
		else if (msgId == 0x422 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.mpc.fcs.lambda_2 = (float)value * 0.001;
		else if (msgId == 0x423 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.mpc.fcs.lambda_3 = (float)value * 0.001;
		else if (msgId == 0x424 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.mpc.fcs.lambda_4 = (float)value * 0.001;
		else if (msgId == 0x425 + MOTORCONTROL_OFFSET_bits)
			data->ctrl.mpc.fcs.bEnableVSP2CC = (_Bool)value;

		//online Rs measuring and temp calculation
		else if (msgId == 0x510 + MOTORCONTROL_OFFSET_bits)
			data->mrp.motorStatorResistance = value * 0.001;
		else if (msgId == 0x511 + MOTORCONTROL_OFFSET_bits)
			data->pID.Temp_ref = value * 0.01;

		//Hoerner Offline ID
		//ACCEPT
		else if (msgId == 5 + MOTORCONTROL_OFFSET_bits)
			data->pID.accept = true;
		//RESET
		else if (msgId == 6 + MOTORCONTROL_OFFSET_bits)
			data->pID.reset_Offl = true;
		//MOTOR_ID
		else if (msgId == 0x101 + MOTORCONTROL_OFFSET_bits)
			data->pID.MotorID = (MotorID_Method)value;
		else if (msgId == 0x102 + MOTORCONTROL_OFFSET_bits)
			data->cw.enableParameterID = (_Bool)value;
		//IDENTLQ
		else if (msgId == 0x103 + MOTORCONTROL_OFFSET_bits)
			data->pID.identLq = (uint16_t)value;
		//I_D_SAMPLETIMEISR
		else if (msgId == 0x105 + MOTORCONTROL_OFFSET_bits)
			data->pID.sampleTimeISR = value * 0.000001;
		//I_D_POLEPAIRS
		else if (msgId == 0x106 + MOTORCONTROL_OFFSET_bits)
			data->mrp.motorPolePairNumber = value;
		//I_D_DUTYCYC
		else if (msgId == 0x107 + MOTORCONTROL_OFFSET_bits)
			data->pID.dutyCyc = value * 0.01;
		//I_D_NREFM
		else if (msgId == 0x108 + MOTORCONTROL_OFFSET_bits)
			data->pID.n_ref_measurement = value;
		//I_D_NREFFOC
		else if (msgId == 0x109 + MOTORCONTROL_OFFSET_bits)
			data->rasv.referenceSpeed = value;
		//I_D_IDREF
		else if (msgId == 0x111 + MOTORCONTROL_OFFSET_bits)
			data->rasv.referenceCurrent_id = value * 0.001;
		//I_D_IQREF
		else if (msgId == 0x112 + MOTORCONTROL_OFFSET_bits)
			data->rasv.referenceCurrent_iq = value * 0.001;
		//Ronline_ON
		else if (msgId == 0x190 + MOTORCONTROL_OFFSET_bits)
			data->pID.identR = 1;
		//Ronline_OFF
		else if (msgId == 0x191 + MOTORCONTROL_OFFSET_bits)
			data->pID.identR = 0;
		//identRAmp
		else if (msgId == 0x192 + MOTORCONTROL_OFFSET_bits)
			data->pID.identRAmp = value * 0.01;
		//I_D_MaxCurrent_update
		else if (msgId == 0x193 + MOTORCONTROL_OFFSET_bits)
			data->mrp.motorMaximumCurrentContinuousOperation = value * 0.1;
		//ID_Controlint
		else if(msgId == 0x194 + MOTORCONTROL_OFFSET_bits)
			data->pID.controlArrCounter=value;
		//Ident Encoder offset
		else if(msgId == 0x195 + MOTORCONTROL_OFFSET_bits)
			data->pID.offsetLock=0;
		//MapCounter
		else if(msgId == 0x197 + MOTORCONTROL_OFFSET_bits)
			data->pID.ControlMapCounter=value;
		//AMM_ON
		else if (msgId == 0x201 + MOTORCONTROL_OFFSET_bits)//Automated Measuring Mode - Enter State
			data->pID.AMM_ON = 1;
		//AMM_OFF
		else if (msgId == 0x202 + MOTORCONTROL_OFFSET_bits)
			data->pID.AMM_ON = 0;
		//AMM_RUN_ON
		else if (msgId == 0x203 + MOTORCONTROL_OFFSET_bits)//Automated Measuring Mode - Run Automated Measuring
			data->pID.AMM_RUN = 1;
		//AMM_RUN_OFF
		else if (msgId == 0x204 + MOTORCONTROL_OFFSET_bits)//Automated Measuring Mode - Shut Down Automated Measuring
			data->pID.AMM_RUN = 0;
		//LOG_INTERVALS
		else if (msgId == 0x205 + MOTORCONTROL_OFFSET_bits)
			data->pID.LogIntervals = value * 0.001;
		//NUMBER_OF_MEASURES
		else if (msgId == 0x206 + MOTORCONTROL_OFFSET_bits)
			data->pID.NumberOfSamples = value;
		//SETTLING_TIME
		else if (msgId == 0x207 + MOTORCONTROL_OFFSET_bits)
			data->pID.settlingTime = value;
		//IDstart
		else if (msgId == 0x210 + MOTORCONTROL_OFFSET_bits)
			data->pID.IDstart = value * 0.001;
		//IDstop
		else if (msgId == 0x211 + MOTORCONTROL_OFFSET_bits)
			data->pID.IDstop = value * 0.001;
		//IDstepsize
		else if (msgId == 0x212 + MOTORCONTROL_OFFSET_bits)
			data->pID.IDstepsize = value * 0.001;
		//IQstart
		else if (msgId == 0x213 + MOTORCONTROL_OFFSET_bits)
			data->pID.IQstart = value * 0.001;
		//IQstop
		else if (msgId == 0x214 + MOTORCONTROL_OFFSET_bits)
			data->pID.IQstop = value * 0.001;
		//IQstepsize
		else if (msgId == 0x215 + MOTORCONTROL_OFFSET_bits)
			data->pID.IQstepsize = value * 0.001;
		//Goertzel Amplitude
		else if (msgId == 0x613 + MOTORCONTROL_OFFSET_bits)
			data->pID.goertzlAmp = value * 0.1;

		//Gebhardt Offline ID
		else if (msgId == 0x610+MOTORCONTROL_OFFSET_bits)
			data->pID.eta_omega_Reib = value *0.01;
		else if (msgId == 0x611+MOTORCONTROL_OFFSET_bits)
			data->pID.N_Brk = value *1;
		else if (msgId == 0x612+MOTORCONTROL_OFFSET_bits)
			data->pID.N_visco = value *1;
		else if (msgId == 0x613+MOTORCONTROL_OFFSET_bits)
			data->pID.n_visco_max = value *1;
		else if (msgId == 0x614+MOTORCONTROL_OFFSET_bits)
			data->mrp.motorNominalCurrent= value *0.1;
		else if (msgId == 0x615+MOTORCONTROL_OFFSET_bits)
			data->pID.f_min = value;
		else if (msgId == 0x616+MOTORCONTROL_OFFSET_bits)
			data->pID.f_max = value;
		else if (msgId == 0x617+MOTORCONTROL_OFFSET_bits)
			data->mrp.motorFluxConstant = value *0.0001;
		else if (msgId == 0x618+MOTORCONTROL_OFFSET_bits)
			data->pID.ScaleTorquePRBS=value*0.1;
		else if (msgId == 0x619+MOTORCONTROL_OFFSET_bits)
			data->pID.Brk_Count = value *1;
		else if (msgId == 0x620+MOTORCONTROL_OFFSET_bits)
			data->pID.StepScale= value *0.00001;
		else if (msgId == 0x621+MOTORCONTROL_OFFSET_bits)
			data->pID.d_TMS_start = value *0.0001;

		//Gebhardt Online ID
		else if (msgId == 0x650+MOTORCONTROL_OFFSET_bits)
			data->pID.bEnableOnlineID = true;
		else if (msgId == 0x651+MOTORCONTROL_OFFSET_bits)
			data->pID.bCalcPsi = true;
		else if (msgId == 0x652+MOTORCONTROL_OFFSET_bits)
			data->pID.ResetOnline = 1;
		else if (msgId == 0x653+MOTORCONTROL_OFFSET_bits){
			data->pID.q_current_steps = value;
			data->pID.eta_curr = (data->pID.max_res_ref_current/data->pID.q_current_steps )*sqrt(2)*0.5;
		}
		else if (msgId == 0x654+MOTORCONTROL_OFFSET_bits){
			data->pID.d_current_steps = value;
			data->pID.eta_curr = (data->pID.max_res_ref_current/data->pID.q_current_steps )*sqrt(2)*0.5;
		}
		else if (msgId == 0x655+MOTORCONTROL_OFFSET_bits){
			data->pID.max_res_ref_current = value;
			data->pID.eta_curr = (data->pID.max_res_ref_current/data->pID.q_current_steps )*sqrt(2)*0.5;
		}
		else if (msgId == 0x656+MOTORCONTROL_OFFSET_bits)
			data->pID.Temp_ref= value;
		else if (msgId == 0x657+MOTORCONTROL_OFFSET_bits)
			data->mrp.motorStatorResistance = value*0.001;
		else if (msgId == 0x658+MOTORCONTROL_OFFSET_bits)
			data->pID.bEnableAutoCurrentControl = true;
		else if (msgId == 0x659+MOTORCONTROL_OFFSET_bits)
			data->pID.bEnableOnlineID = false;
		else if (msgId == 0x660+MOTORCONTROL_OFFSET_bits)
			data->pID.bEnableAutoCurrentControl = false;
		else if (msgId == 0x661+MOTORCONTROL_OFFSET_bits)
			data->pID.AdmitParamsFlag = true;
		else if (msgId == 0x662+MOTORCONTROL_OFFSET_bits)
			data->pID.AdmitMechParamsFlag = true;

	}

}

// this ISR is never called, because the interrupt "INTC_IPC_Shared_INTERRUPT_ID" is send private for cpu1, so cpu0 do not see/recognize this interrupt and can not call the "Transfer_ipc_Intr_Handler"
void Transfer_ipc_Intr_Handler(void *data)
{
	i_ISR_IPC_LifeCheck++; //LiveCheck
	if(i_ISR_IPC_LifeCheck > 2500){
		i_ISR_IPC_LifeCheck =0;
		//xil_printf("var_mess new period\r\n");
	}

}
