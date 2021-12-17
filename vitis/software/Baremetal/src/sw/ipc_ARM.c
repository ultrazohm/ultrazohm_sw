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

#include <string.h>
#include "../main.h"
#include "../include/ipc_ARM.h"


#define SCOPE_OFFSET_bits 0x00
#define MOTORCONTROL_OFFSET_bits 1000

extern float *js_ch_observable[JSO_ENDMARKER];
extern float *js_ch_selected[JS_CHANNELS];

extern _Bool bNewControlMethodAvailable;
extern uint32_t js_status_BareToRTOS;

void ipc_Control_func(uint32_t msgId, float value, DS_Data* data)
{
	// HANDLE RECEIVED MESSAGE
	if ( msgId != 0)
	{
		uint32_t ADCconvFactor_Hbytes = 0;
		uint32_t ADCconvFactor_Lbytes = 0;
		uint32_t ADCconvFactorReadRequest = 0;

		//GENERAL VARIABLES
		switch (msgId){
		case 1:
			// do something
			break;

		case( 2): // Stop
			data->cw.enableSystem = false;
			data->cw.enableControl = false;
			break;

		case( 16): // Reference frequency
			if (value > 50)
				data->rasv.referenceFrequency = 50;
			else if(value < 0)
				data->rasv.referenceFrequency = 0;
			else
				data->rasv.referenceFrequency = value;
			break;

		case( 21): // Reference Current Control Angle
			data->rasv.currentControlAngle = value;
			break;

		case( 112): // reset all Errors
			data->er.dcLinkOvervoltageOccured = true;
			data->er.maximumContinuousCurrentExceeded = true;
			data->er.maximumShortTermCurrentReached = true;
			data->er.pwmFrequencyError = true;
			break;

		case( 201): // SELECT_DATA_CH1_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[0] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 202): // SELECT_DATA_CH2_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[1] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 203): // SELECT_DATA_CH3_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[2] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 204): // SELECT_DATA_CH4_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[3] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 205): // SELECT_DATA_CH5_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[4] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 206): // SELECT_DATA_CH6_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[5] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 207): // SELECT_DATA_CH7_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[6] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 208): // SELECT_DATA_CH8_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[7] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 209): // SELECT_DATA_CH9_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[8] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 210): // SELECT_DATA_CH10_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[9] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 211): // SELECT_DATA_CH11_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[10] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 212): // SELECT_DATA_CH12_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[11] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 213): // SELECT_DATA_CH13_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[12] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 214): // SELECT_DATA_CH14_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[13] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 215): // SELECT_DATA_CH15_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[14] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 216): // SELECT_DATA_CH16_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[15] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 217): // SELECT_DATA_CH17_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[16] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 218): // SELECT_DATA_CH18_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[17] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 219): // SELECT_DATA_CH19_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[18] = js_ch_observable[(uint32_t)value];	}
			break;

		case( 220): // SELECT_DATA_CH20_bits
			if ( value >= 0 && value < JSO_ENDMARKER )	{js_ch_selected[19] = js_ch_observable[(uint32_t)value];	}
			break;


		case( 0x01+MOTORCONTROL_OFFSET_bits): // ConverterEnable
			data->cw.enableSystem = true;
			break; 

		case( 0x02+MOTORCONTROL_OFFSET_bits): // ConverterDisable
			data->cw.enableSystem = false;
			break; 

		case( 0x03+MOTORCONTROL_OFFSET_bits): // ControlEnable
			data->cw.enableControl = true;
			break; 

		case( 0x04+MOTORCONTROL_OFFSET_bits): // ControlDisable
			data->cw.enableControl = false;
			break; 

		case( 0x041+MOTORCONTROL_OFFSET_bits): // ResetError
			data->er.communicationTimeoutOccured = true;
			data->er.dcLinkOvervoltageOccured = true;
			data->er.maximumContinuousCurrentExceeded = true;
			data->er.maximumShortTermCurrentReached = true;
			data->er.pwmFrequencyError = true;
			break; 

		case( 0x110+MOTORCONTROL_OFFSET_bits): // referenceTorque (1000 + 0x110 = 1272)
			data->rasv.referenceTorque = (float)value * 0.001; //mNm
			break; 

		case( 0x300+MOTORCONTROL_OFFSET_bits):
			data->cw.rotorAngleEstimationMode= (rotorAngleEstimationMethod)value;
			break; 

		case( 0x320+MOTORCONTROL_OFFSET_bits): //digital hall
			if(value ==1){ data->cw.rotorAngleEstimationMode = hallSensors120Degree;}
			else if(value ==2){ data->cw.rotorAngleEstimationMode = hallSensors180Degree;}
			break; 

		case( 0x340+MOTORCONTROL_OFFSET_bits):
			data->mrp.incrementalEncoderResolution = (float)value;
			break; 

		case( 0x341+MOTORCONTROL_OFFSET_bits):
			data->mrp.motorMaximumSpeed= (float)value;
			break; 

		case( 0x342+MOTORCONTROL_OFFSET_bits):
			data->mrp.incrementalEncoderOffset= (float)value;
			break;

		//ADC
		case( 0x350+MOTORCONTROL_OFFSET_bits):
			ADCconvFactor_Hbytes = value;
			break; 

		case( 0x351+MOTORCONTROL_OFFSET_bits): 
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorIph = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes & 0xFFFF))*1e-9;
			break; 
			
		case( 0x352+MOTORCONTROL_OFFSET_bits):
			ADCconvFactor_Hbytes = value;
			break; 

		case( 0x353+MOTORCONTROL_OFFSET_bits): 
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorVph = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
			break; 
			
		case( 0x354+MOTORCONTROL_OFFSET_bits):
			ADCconvFactor_Hbytes = value;
			break; 

		case( 0x355+MOTORCONTROL_OFFSET_bits): 
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorIdc = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
			break; 
			
		case( 0x356+MOTORCONTROL_OFFSET_bits):
			ADCconvFactor_Hbytes = value;
			break; 

		case( 0x357+MOTORCONTROL_OFFSET_bits): 
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorVdc = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
			break; 
			
		case( 0x358+MOTORCONTROL_OFFSET_bits):
			ADCconvFactor_Hbytes = value;
			break; 

		case( 0x359+MOTORCONTROL_OFFSET_bits): 
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorTrq = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
			break; 
			
		case( 0x360+MOTORCONTROL_OFFSET_bits):
			ADCconvFactor_Hbytes = value;
			break; 

		case( 0x361+MOTORCONTROL_OFFSET_bits): 
			ADCconvFactor_Lbytes = value;
			data->mrp.ADCConversionFactorTmp = ((ADCconvFactor_Hbytes << 16) | (ADCconvFactor_Lbytes % 0xFFFF))*1e-9;
			break; 
			
		case( 0x369+MOTORCONTROL_OFFSET_bits):
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
					uz_assert(0); // unknown command -> throw error
					break;
			}
			break;

		//MODULATION
		case( 0x600+MOTORCONTROL_OFFSET_bits):
			data->cw.modulationMode = (gatesignalsModulationMethod)value;
			break;

		//CONTROL METHOD
		case( 0x400+ MOTORCONTROL_OFFSET_bits): // CONTROL_METHOD (1000 + 0x400 = 2024)
			if((data->cw.enableSystem == false)&&(data->cw.enableControl == false)){ //Only allow a new control method, if the system is in a stable status
				data->cw.ControlMethod =  (currentControlMethod)value;
				bNewControlMethodAvailable = true;  //Activate the Flag in order to initialize the IP Cores and functions after a new control method arrives, only once!
			}else{
				//do nothing, keep the old control method
			}
			break;


		//CONTROL REFERENCE METHOD
		case( 0x401+ MOTORCONTROL_OFFSET_bits): // CONTROL_REFERENCE (1000 + 0x401 = 2025)
			if((data->cw.enableControl == false)){ //Only allow a new control method, if the control is not running currently
				data->cw.ControlReference= (ControlReference)value;
			}else{
				//do nothing, keep the old control method
			}
			break;

		//FOC CONTROL
		case( 0x402 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.foc.cc.Kp_id = (float)value * 0.001;
			break;
			
		case( 0x403 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.foc.cc.Tn_id = (float)value * 0.0001;
			break; 

		case( 0x404 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.foc.cc.Kp_iq = (float)value * 0.001;
			break; 

		case( 0x405 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.foc.cc.Tn_iq = (float)value * 0.0001;
			break; 

		case( 0x406 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.foc.sc.Kp = (float)value * 0.001;
			break; 

		case( 0x407 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.foc.sc.Tn = (float)value * 0.0001;
			break; 

		case( 0x408 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.foc.cc.FOCFeedForward = (_Bool)value;
			break;

		//MPC CONTROL
		case( 0x421 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.mpc.fcs.lambda_dU = (float)value * 0.001;
			break; 

		case( 0x422 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.mpc.fcs.lambda_2 = (float)value * 0.001;
			break; 

		case( 0x423 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.mpc.fcs.lambda_3 = (float)value * 0.001;
			break; 

		case( 0x424 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.mpc.fcs.lambda_4 = (float)value * 0.001;
			break; 

		case( 0x425 + MOTORCONTROL_OFFSET_bits):
			data->ctrl.mpc.fcs.bEnableVSP2CC = (_Bool)value;
			break;

		//online Rs measuring and temp calculation
		case( 0x510 + MOTORCONTROL_OFFSET_bits):
			data->mrp.motorStatorResistance = value * 0.001;
			break; 

		case( 0x511 + MOTORCONTROL_OFFSET_bits):
			data->pID.Temp_ref = value * 0.01;
			break;

		//Hoerner Offline ID
		//ACCEPT
		case( 5 + MOTORCONTROL_OFFSET_bits):
			data->pID.accept = true;
			break;
			
		//RESET
		case( 6 + MOTORCONTROL_OFFSET_bits):
			data->pID.reset_Offl = true;
			break;
			
		//MOTOR_ID
		case( 0x101 + MOTORCONTROL_OFFSET_bits):
			data->pID.MotorID = (MotorID_Method)value;
			break; 

		case( 0x102 + MOTORCONTROL_OFFSET_bits):
			data->cw.enableParameterID = (_Bool)value;
			break;
			
		//IDENTLQ
		case( 0x103 + MOTORCONTROL_OFFSET_bits):
			data->pID.identLq = (uint16_t)value;
			break;
			
		//I_D_SAMPLETIMEISR
		case( 0x105 + MOTORCONTROL_OFFSET_bits):
			data->pID.sampleTimeISR = value * 0.000001;
			break;
			
		//I_D_POLEPAIRS
		case( 0x106 + MOTORCONTROL_OFFSET_bits):
			data->mrp.motorPolePairNumber = value;
			break;
			
		//I_D_DUTYCYC
		case( 0x107 + MOTORCONTROL_OFFSET_bits):
			data->pID.dutyCyc = value * 0.01;
			break;
			
		//I_D_NREFM
		case( 0x108 + MOTORCONTROL_OFFSET_bits):
			data->pID.n_ref_measurement = value;
			break;
			
		//I_D_NREFFOC
		case( 0x109 + MOTORCONTROL_OFFSET_bits):
			data->rasv.referenceSpeed = value;
			break;

		//I_D_IDREF
		case( 0x111 + MOTORCONTROL_OFFSET_bits):
			data->rasv.referenceCurrent_id = value * 0.001;
			break; 

		//I_D_IQREF
		case( 0x112 + MOTORCONTROL_OFFSET_bits):
			data->rasv.referenceCurrent_iq = value * 0.001;
			break; 

		//Ronline_ON
		case( 0x190 + MOTORCONTROL_OFFSET_bits):
			data->pID.identR = 1;
			break; 

		//Ronline_OFF
		case( 0x191 + MOTORCONTROL_OFFSET_bits):
			data->pID.identR = 0;
			break; 

		//identRAmp
		case( 0x192 + MOTORCONTROL_OFFSET_bits):
			data->pID.identRAmp = value * 0.01;
			break; 

		//I_D_MaxCurrent_update
		case( 0x193 + MOTORCONTROL_OFFSET_bits):
			data->mrp.motorMaximumCurrentContinuousOperation = value * 0.1;
			break; 

		//ID_Controlint
		case( 0x194 + MOTORCONTROL_OFFSET_bits):
			data->pID.controlArrCounter=value;
		//Ident Encoder offsetcase( if(msgId == 0x195 + MOTORCONTROL_OFFSET_bits):
			data->pID.offsetLock=0;
			break; 

		//MapCounter
		case( 0x197 + MOTORCONTROL_OFFSET_bits):
			data->pID.ControlMapCounter=value;
			break; 

		//AMM_ON
		case( 0x201 + MOTORCONTROL_OFFSET_bits)://Automated Measuring Mode - Enter State
			data->pID.AMM_ON = 1;
			break; 

		//AMM_OFF
		case( 0x202 + MOTORCONTROL_OFFSET_bits):
			data->pID.AMM_ON = 0;
			break; 

		//AMM_RUN_ON
		case( 0x203 + MOTORCONTROL_OFFSET_bits)://Automated Measuring Mode - Run Automated Measuring
			data->pID.AMM_RUN = 1;
			break; 

		//AMM_RUN_OFF
		case( 0x204 + MOTORCONTROL_OFFSET_bits)://Automated Measuring Mode - Shut Down Automated Measuring
			data->pID.AMM_RUN = 0;
			break; 

		//LOG_INTERVALS
		case( 0x205 + MOTORCONTROL_OFFSET_bits):
			data->pID.LogIntervals = value * 0.001;
			break; 

		//NUMBER_OF_MEASURES
		case( 0x206 + MOTORCONTROL_OFFSET_bits):
			data->pID.NumberOfSamples = value;
			break; 

		//SETTLING_TIME
		case( 0x207 + MOTORCONTROL_OFFSET_bits):
			data->pID.settlingTime = value;
			break; 

		//IDstart
		case( 0x210 + MOTORCONTROL_OFFSET_bits):
			data->pID.IDstart = value * 0.001;
			break; 

		//IDstop
		case( 0x211 + MOTORCONTROL_OFFSET_bits):
			data->pID.IDstop = value * 0.001;
			break; 

		//IDstepsize
		case( 0x212 + MOTORCONTROL_OFFSET_bits):
			data->pID.IDstepsize = value * 0.001;
			break; 

		//IQstart
		case( 0x213 + MOTORCONTROL_OFFSET_bits):
			data->pID.IQstart = value * 0.001;
			break; 

		//IQstop
		case( 0x214 + MOTORCONTROL_OFFSET_bits):
			data->pID.IQstop = value * 0.001;
			break; 

		//IQstepsize
		case( 0x215 + MOTORCONTROL_OFFSET_bits):
			data->pID.IQstepsize = value * 0.001;
			break; 

		//Goertzel Amplitude
	//	case( 0x613 + MOTORCONTROL_OFFSET_bits):
	//		data->pID.goertzlAmp = value * 0.1;
	//		break;

		//Gebhardt Offline ID
		case( 0x610+MOTORCONTROL_OFFSET_bits):
			data->pID.eta_omega_Reib = value *0.01;
			break; 

		case( 0x611+MOTORCONTROL_OFFSET_bits):
			data->pID.N_Brk = value *1;
			break; 

		case( 0x612+MOTORCONTROL_OFFSET_bits):
			data->pID.N_visco = value *1;
			break; 

		case( 0x613+MOTORCONTROL_OFFSET_bits):
			data->pID.n_visco_max = value *1;
			break; 

		case( 0x614+MOTORCONTROL_OFFSET_bits):
			data->mrp.motorNominalCurrent= value *0.1;
			break; 

		case( 0x615+MOTORCONTROL_OFFSET_bits):
			data->pID.f_min = value;
			break; 

		case( 0x616+MOTORCONTROL_OFFSET_bits):
			data->pID.f_max = value;
			break; 

		case( 0x617+MOTORCONTROL_OFFSET_bits):
			data->mrp.motorFluxConstant = value *0.0001;
			break; 

		case( 0x618+MOTORCONTROL_OFFSET_bits):
			data->pID.ScaleTorquePRBS=value*0.1;
			break; 

		case( 0x619+MOTORCONTROL_OFFSET_bits):
			data->pID.Brk_Count = value *1;
			break; 

		case( 0x620+MOTORCONTROL_OFFSET_bits):
			data->pID.StepScale= value *0.00001;
			break; 

		case( 0x621+MOTORCONTROL_OFFSET_bits):
			data->pID.d_TMS_start = value *0.0001;

		//Gebhardt Online ID
		case( 0x650+MOTORCONTROL_OFFSET_bits):
			data->pID.bEnableOnlineID = true;
			break; 

		case( 0x651+MOTORCONTROL_OFFSET_bits):
			data->pID.bCalcPsi = true;
			break; 

		case( 0x652+MOTORCONTROL_OFFSET_bits):
			data->pID.ResetOnline = 1;
			break; 

		case( 0x653+MOTORCONTROL_OFFSET_bits):
			data->pID.q_current_steps = value;
			data->pID.eta_curr = (data->pID.max_res_ref_current/data->pID.q_current_steps )*sqrt(2)*0.5;
			break;

		case( 0x654+MOTORCONTROL_OFFSET_bits):
			data->pID.d_current_steps = value;
			data->pID.eta_curr = (data->pID.max_res_ref_current/data->pID.q_current_steps )*sqrt(2)*0.5;
			break;

		case( 0x655+MOTORCONTROL_OFFSET_bits):
			data->pID.max_res_ref_current = value;
			data->pID.eta_curr = (data->pID.max_res_ref_current/data->pID.q_current_steps )*sqrt(2)*0.5;
			break;

		case( 0x656+MOTORCONTROL_OFFSET_bits):
			data->pID.Temp_ref= value;
			break;

		case( 0x657+MOTORCONTROL_OFFSET_bits):
			data->mrp.motorStatorResistance = value*0.001;
			break;

		case( 0x658+MOTORCONTROL_OFFSET_bits):
			data->pID.bEnableAutoCurrentControl = true;
			break;

		case( 0x659+MOTORCONTROL_OFFSET_bits):
			data->pID.bEnableOnlineID = false;
			break;

		case( 0x660+MOTORCONTROL_OFFSET_bits):
			data->pID.bEnableAutoCurrentControl = false;
			break;

		case( 0x661+MOTORCONTROL_OFFSET_bits):
			data->pID.AdmitParamsFlag = true;
			break;

		case( 0x662+MOTORCONTROL_OFFSET_bits):
			data->pID.AdmitMechParamsFlag = true;
			break;

		default:
			uz_assert(0); // unknown command -> throw error
		}
	}

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


}

