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

//Includes from own files
#include "main.h"
#include "uz/uz_global_configuration.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L_staticAllocator.h"
#include "Codegen/uz_codegen.h"

//Initialize the global variables
int i_LifeCheck;

uz_codegen codegenInstance;

_Bool bPlotData = false;
_Bool bNewControlMethodAvailable = false;
_Bool bInit = false;
DS_Data Global_Data;
extern XGpio Gpio_OUT; /* GPIO Device driver instance for the real GPIOs */

//Data from R5_0 to A53_0 (from BareMetal to FreeRTOS) in order to provide data for the GUI (Ethernet-Plot)
ARM_to_Oszi_Data_shared_struct OsziData;

//Data from A53_0 to R5_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
Oszi_to_ARM_Data_shared_struct ControlData;
Oszi_to_ARM_Data_shared_struct ControlDataShadowBare;

static void uz_assertCallback(const char8 *file, s32 line) {
	extern XScuGic INTCInst;
	uz_printf("\r\nAssertion in file %s on line %d\r\n", file, line);
	uz_led_set_errorLED_on();
	uz_led_set_readyLED_off();
	uz_led_set_runningLED_off();
	ErrorHandling(&Global_Data);
	XScuGic_Disable(&INTCInst, Interrupt_ISR_ID);
}

int main(void) {

	int status = UZ_SUCCESS;
	Xil_AssertSetCallback((Xil_AssertCallback) uz_assertCallback);
	uz_printf("\r\n\r\n");
	uz_printf("Welcome to the UltraZohm\r\n");
	uz_printf("----------------------------------------\r\n");

	// Initialize the global "Global_Data" structure -> the values can be overwritten afterwards from the Java-GUI -> this must be the first INIT-function, because it is required subsequently!
	InitializeDataStructure(&Global_Data);
	Initialize_AXI_GPIO(); 	// Initialize the GPIOs which are connected over FPGA pins
	uz_frontplane_button_and_led_init();
	ADC_WriteConversionFactor(10); 	// Conversion Factor of 10, because the full input range of the ADC is +-5V = 10V range

	// Initialize Park-Transformation 123 to dq
	DQTransformation_Initialize(&Global_Data);
	uz_interlockDeadtime2L_handle deadtime_slotd1 = uz_interlockDeadtime2L_staticAllocator_slotD1();
	uz_interlockDeadtime2L_set_deadtime_us(deadtime_slotd1, 2.0f);
	uz_interlockDeadtime2L_set_enable_output(deadtime_slotd1, true);
	//Initialize PWM and switch signal control
	PWM_SS_Initialize(&Global_Data); 	// two-level modulator
	PWM_3L_Initialize(&Global_Data);	// three-level modulator

	// Initialize Timer in order to Trigger the ISRs
	Initialize_Timer();
	uz_SystemTime_init();

	// Initialize the incremental encoder
	Encoder_Incremental_Initialize(&Global_Data);

	// Initialize the FPGA control algorithm
	Initialize_FPGAController(&Global_Data);

	// Initialize the ARM control algorithm
	Initialize_ARMController(&Global_Data);

	// Initialize the Soft-Oscilloscope ("JavaScope")
	JavaScope_initalize(&Global_Data);

	// Initialize CodeGen
	uz_codegen_init(&codegenInstance);

	// Initialize the Interrupts
	Initialize_ISR();

	//Set the current value in the ADC as offset/default value
	ADC_Set_Offset();

	// Turn on AXI2TCM communication
	AXI2TCM_on();

	// Infinite loop
	while (1) {

		// poll the buttons
		Global_Data.dv.sw1 = uz_GetPushButtonEnableSystem();
		Global_Data.dv.sw2 = uz_GetPushButtonEnableControl();
		Global_Data.dv.sw3 = uz_GetPushButtonStop();
		// Set the system enable flag to false if SW1 is pressed
		if (Global_Data.dv.sw1 == true) {
			Global_Data.cw.enableSystem = true;
		}
		// Set the control enable flag to false if SW2 is pressed
		if (Global_Data.dv.sw2 == true) {
			Global_Data.cw.enableControl = true;
		}
#if (UZ_HARDWARE_VERSION > 2U) // in CarrierBoard_v2 there are no buttons, therefore SW_stop is always zero/false
		// Set the control enable and system enable flag to false if SW3 is pressed
		if (Global_Data.dv.sw3 == false) {
			Global_Data.cw.enableControl = false;
			Global_Data.cw.enableSystem = false;
		}
#endif
		if ((Global_Data.ew.maximumContinuousCurrentExceeded == true) || (Global_Data.ew.maximumShortTermCurrentReached == true) || (Global_Data.ew.dcLinkOvervoltageOccured == true)
		                || (Global_Data.ew.pwmFrequencyError == true)) {
			uz_led_set_errorLED_on();
			ErrorHandling(&Global_Data);
			ErrorReset(&Global_Data);	//If any error is active -> check if an error-reset is received
		} else {	//no errors
		                //Check the control values
			if (Global_Data.cw.enableSystem == false) {
				turnPowerElectronicsOff(&Global_Data); //Switch power converter off
			} else if ((Global_Data.cw.enableSystem == true) && bInit == false) { //Call this function only once. If there was an error, "enableSystem " must be reseted!
				bInit = turnPowerElectronicsOn(&Global_Data); //Switch power converter on
			}

			if (Global_Data.cw.enableControl == true) {
				ControllerOn(&Global_Data); //Switch controller on
			} else {
				ControllerOff(&Global_Data); //Switch controller off
			}
		}

		//Change the operation mode only if the system is in a safe state
		if ((Global_Data.cw.enableSystem == false) && (Global_Data.cw.enableControl == false) && (bNewControlMethodAvailable == true)) {
			switch (Global_Data.cw.ControlMethod) {
			case DirectTorqueControl:
				Configure_DTC_Control(&Global_Data);
				PWM_SS_Initialize(&Global_Data);
				uz_printf("DTC is active\n");
				break;
			case fieldOrientedControl:
				Configure_FOC_Control(&Global_Data);
				PWM_SS_Initialize(&Global_Data);
				uz_printf("FOC is active\n");
				break;
			case ModelPredictiveControl:
				Configure_MPC_Control(&Global_Data);
				PWM_SS_Initialize(&Global_Data);
				uz_printf("MPC is active\n");
				break;
			case sixStepCommutation:
				//toDO not used at the moment
				PWM_SS_Initialize(&Global_Data);
				uz_printf("Six-Step commutation is active\n");
				break;
			case halfBridgeControl:
				Configure_HalfBridge_Control(&Global_Data);
				PWM_SS_Initialize(&Global_Data);
				uz_printf("Half Bridge control is active\n");
				break;
			default:
				uz_printf("No valid control method is active\n");
				break;
			}
			bNewControlMethodAvailable = false; //Reset the Flag in order to initialize the IP Cores and functions after a new control method arrives, only once!
		}

		if (bPlotData) {
			plotData(&Global_Data);
		}

		i_LifeCheck++; //LiveCheck for the main while-1 loop
		if (i_LifeCheck > 2500) {
			i_LifeCheck = 0;
		}
	}
	return (status);
}

//==============================================================================================================================================================
int turnPowerElectronicsOff(DS_Data* data) {
	bInit = false;

	data->rasv.referenceCurrent_iq = 0; // in A
	data->rasv.referenceCurrent_id = 0; // in A
	data->rasv.ModifiedReferenceCurrent_iq = 0; // in A
	data->rasv.ModifiedReferenceCurrent_id = 0; // in A
	data->rasv.referenceSpeed = 0; // in rpm
	data->cw.enableControl = false; 		//Switch controller off

	//Disable power electronics
	XGpio_DiscreteClear(&Gpio_OUT, GPIO_CHANNEL, 3); 		//Switch power electronics off = 0b0001 = "Disable_Inverter" //Switch Gate connection off = 0b0010 = "Disable_Gate"
	return (0);
}

//==============================================================================================================================================================
int turnPowerElectronicsOn(DS_Data* data) {

	XGpio_DiscreteSet(&Gpio_OUT, GPIO_CHANNEL, 3); 		//Switch power electronics on = 0b0001 = "Enable_Inverter" On  //Switch Gate connection on = 0b0010 = "Enable_Gate" On

	asm(" nop");
	//Wait some ticks, otherwise, the second GPIO write will not be updated
	XGpio_DiscreteClear(&Gpio_OUT, GPIO_CHANNEL, 4); //Stop to the ADC module to set an offset value    0b0100);  	// "Enable_Gate" On //Consider, this is a inverse signal AND "Acknowledge" the set of ADC offset value.
	bInit = true;
	return (0);
}

//==============================================================================================================================================================
void ControllerOff(DS_Data* data) {
	uz_led_set_runningLED_off();
}

//==============================================================================================================================================================
void ControllerOn(DS_Data* data) {
	uz_led_set_runningLED_on();
}

//==============================================================================================================================================================
void ErrorHandling(DS_Data* data) {

	ControllerOff(data); 					//Switch controller off
	data->rasv.referenceCurrent_iq = 0; 	// in A
	data->rasv.referenceSpeed = 0; 			// in rpm
	data->cw.enableControl = false;	//Switch controller off

	turnPowerElectronicsOff(data); 			// Switch power electronics off
	data->cw.enableSystem = false;	// Switch power electronics off
}

//==============================================================================================================================================================
void ErrorReset(DS_Data* data) {

	if (data->er.dcLinkOvervoltageOccured == true) {
		data->ew.dcLinkOvervoltageOccured = false;  	//Reset over-voltage
		data->er.dcLinkOvervoltageOccured = false;	//Reset flag
	}
	if (data->er.maximumContinuousCurrentExceeded == true) {
		data->ew.maximumContinuousCurrentExceeded = false;  //Reset Continuous Current Exceeded
		data->er.maximumContinuousCurrentExceeded = false;	//Reset flag
	}
	if (data->er.maximumShortTermCurrentReached == true) {
		data->ew.maximumShortTermCurrentReached = false;  	//Reset maximum Short-Term Current Reached
		data->er.maximumShortTermCurrentReached = false;		//Reset flag
	}
	if (data->er.pwmFrequencyError == true) {
		data->ew.pwmFrequencyError = false;  //Reset pwm Frequency Error
		data->er.pwmFrequencyError = false;	//Reset flag
	}
	uz_led_set_errorLED_off();

}

//==============================================================================================================================================================
void ADC_Set_Offset() {
	XGpio_DiscreteSet(&Gpio_OUT, GPIO_CHANNEL, 4);	// 4 = 0b0100 Enable the ADC module to set an offset value. Call this function only at the beginning once
}

//==============================================================================================================================================================
void ADC_Clear_Offset() {
	XGpio_DiscreteClear(&Gpio_OUT, GPIO_CHANNEL, 4);	// 4 = 0b0100 Release the offset, otherwise converted output remains 0
}
//==============================================================================================================================================================
void AXI2TCM_on() {
	XGpio_DiscreteSet(&Gpio_OUT, GPIO_CHANNEL, 0b10000);	// bit 5 : 16 = 0b10000 Enables the AXI2TCM module to write measurements directly to the TCM
}

//==============================================================================================================================================================
void plotData(DS_Data* data) {

	uz_printf("Reference current in float: %f \r\n", data->rasv.referenceCurrent_iq);

	uz_printf("ADC I_a: %f \r\n", data->av.I_U);
	uz_printf("ADC I_b: %f \r\n", data->av.I_V);
	uz_printf("ADC I_c: %f \r\n", data->av.I_W);

	//Output encoder values
	uz_printf("Speed in rpm: %f \r\n", data->av.mechanicalRotorSpeed);
	uz_printf("theta_el: %f \r\n", data->av.theta_elec);
	uz_printf("theta_mech: %f \r\n", data->av.theta_mech);
	uz_printf("Actual DutyCycle: %d \r\n", (int16_t) (data->rasv.sixStepCommutationDutyCycle * 100.0));

	bPlotData = false; // print only once
}

//==============================================================================================================================================================
void InitializeDataStructure(DS_Data* data) {

	data->av.U_ZK = 24.0; 								//[V] DC-Link voltage

	//Control NOT USED
	data->cw.ControlReference = CurrentControl; 		// default because of Parameter ID
	data->cw.ControlMethod = fieldOrientedControl; 		// default because of Parameter ID

	//Default control method
	Configure_FOC_Control(data);

	//Encoder
	data->mrp.incrementalEncoderResolution = 5000.0; 	//[Increments per turn] // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	data->mrp.incrementalEncoderOffset = 3.141592653589; //[rad]  //Offset for the Park-Transformation -> pi = 3.141592653589
	data->mrp.motorMaximumSpeed = 6000.0; //[rpm]
	data->mrp.incrementalEncoderOversamplingFactor = 5.0; //Oversampling factor must be between 1.0-6.0 (Achtung, immer mit Punkt da sonst nicht als float interpretiert

	//Motor related parameters
	Initialize_MotorRelatedParameters(data);

	//MPC
	data->ctrl.mpc.fcs.bEnableVSP2CC = false;
	data->ctrl.mpc.fcs.lambda_dU = 0;

	//FOC
	data->ctrl.foc.cc.FOCFeedForward = false;
	data->ctrl.foc.sc.referenceSpeedRamped = 0.0;
	data->ctrl.foc.numberValidValuesInMTPA = 0;

	//toDO: Write the ADC conversion factors from the processor -> at the moment this factors are not used!
	data->mrp.ADCConversionFactorIph = 0.0;
	data->mrp.ADCConversionFactorIdc = 0.0;
	data->mrp.ADCConversionFactorVph = 0.0;
	data->mrp.ADCConversionFactorVdc = 0.0;
	data->mrp.ADCConversionFactorTrq = 0.0;
	data->mrp.ADCConversionFactorTmp = 0.0;
	data->mrp.ADCconvFactorReadback = 0.0;

	//Initialize Automatic Current Reference Control Inputs
	data->pID.bEnableAutoCurrentControl = false;
	data->pID.d_current_steps = 10; // Between 3 -10 is a good range
	data->pID.q_current_steps = 10; // Between 3 -10 is a good range
	data->pID.max_res_ref_current = 12.0; // Depends on the required range of the identified flux map and the possible range of the current sensor
	//Initialize Automatic Current Reference Control Outputs
	data->pID.bRefAutomaticControlled = false;

	//Initialize Offline ID Stateflow Inputs
	data->pID.MotorID = 1;
	data->pID.accept = false;
	data->pID.reset_Offl = false;
	data->pID.sampleTimeISR = 0.0001;
	data->pID.dutyCyc = 0.05;
	data->pID.n_ref_measurement = 200;
	data->pID.identLq = 0;
	data->pID.VibON = 0;
	data->pID.VibAmp = 0;
	data->pID.VibFreq = 0;
	data->pID.identR = 0;
	data->pID.AMM_ON = 0;
	data->pID.AMM_RUN = 0;
	data->pID.IDstart = 0.0;
	data->pID.IDstop = 0.0;
	data->pID.IDstepsize = 0.0;
	data->pID.IQstart = 0.0;
	data->pID.IQstop = 0.0;
	data->pID.IQstepsize = 0.0;
	data->pID.LogIntervals = 0;
	data->pID.NumberOfSamples = 0;
	data->pID.settlingTime = 0.0;
	data->pID.n_visco_max = 500;
	data->pID.N_Brk = 5;
	data->pID.Brk_Count = 20;
	data->pID.N_visco = 200;
	data->pID.f_min = 5;
	data->pID.f_max = 90;
	data->pID.d_TMS_start = 0.0001;
	data->pID.StepScale = 0.001;
	data->pID.ScaleTorquePRBS = 2;
	data->pID.eta_omega_Reib = 0.2;

	//Online and Offline ID Stateflow Inputs
	data->pID.identRAmp = 0.1 * data->mrp.motorNominalCurrent;
	data->pID.Temp_ref = 20.0;

	//Online ID Stateflow Inputs
	data->pID.bEnableOnlineID = false;
	data->pID.DevSpeed = 0.1;	// 10% of actual Value
	data->pID.DevCurrent = 0.2;	//20% of actual Value
	data->pID.AverageTransParams = 1;
	data->pID.AllowStepFlag = 1;
	data->pID.ResetOnline = 0;

	//Initialize Offline ID Stateflow Outputs
	data->pID.activeState = 0;
	data->pID.offsetLock = 1;
	data->pID.array_counter = 0;
	data->pID.controlArrCounter = 0;
	data->pID.AdmitParamsFlag = false;
	data->pID.AdmitMechParamsFlag = false;

	// Initialize Online ID Stateflow Outputs
	data->pID.bOnlineIDenabled = false;
	data->pID.map_counter = 0;
	data->pID.ControlMapCounter = 0;

	//Initialize the error states
	data->ew.communicationTimeoutOccured = false;
	data->ew.dcLinkOvervoltageOccured = false;
	data->ew.errorCodeXilinx = 0;
	data->ew.maximumContinuousCurrentExceeded = false;
	data->ew.maximumShortTermCurrentReached = false;
	data->ew.mtpaTableError = false;
	data->ew.pwmFrequencyError = false;
	data->rasv.currentControlAngle = 0.0;
	data->rasv.halfBridge1DutyCycle = 0.0;
	data->rasv.halfBridge2DutyCycle = 0.0;
	data->rasv.halfBridge3DutyCycle = 0.0;
	data->rasv.phaseAdvanceAngle = 0.0;
	data->rasv.referenceCurrent_id = 0.0;
	data->rasv.referenceCurrent_iq = 0.0;
	data->rasv.referenceFrequency = 0.0;
	data->rasv.referencePosition = 0.0;
	data->rasv.referenceSpeed = 0.0;
	data->rasv.referenceTorque = 0.0;
	data->rasv.sixStepCommutationDutyCycle = 0.0;
	//Initialize the modified reference values
	data->rasv.ModifiedReferenceCurrent_id = 0.0;
	data->rasv.ModifiedReferenceCurrent_iq = 0.0;

	//Initialize ADC conversion factors
	// Conversion Factor of 10, because the full input range of the ADC is +-5V = 10V range
	data->aa.A1.cf.ADC_A1 = 10;
	data->aa.A1.cf.ADC_A2 = 10;
	data->aa.A1.cf.ADC_A3 = 10;
	data->aa.A1.cf.ADC_A4 = 10;
	data->aa.A1.cf.ADC_B5 = 10;
	data->aa.A1.cf.ADC_B6 = 10;
	data->aa.A1.cf.ADC_B7 = 10;
	data->aa.A1.cf.ADC_B8 = 10;

	data->aa.A2.cf.ADC_A1 = 10;
	data->aa.A2.cf.ADC_A2 = 10;
	data->aa.A2.cf.ADC_A3 = 10;
	data->aa.A2.cf.ADC_A4 = 10;
	data->aa.A2.cf.ADC_B5 = 10;
	data->aa.A2.cf.ADC_B6 = 10;
	data->aa.A2.cf.ADC_B7 = 10;
	data->aa.A2.cf.ADC_B8 = 10;

	data->aa.A3.cf.ADC_A1 = 10;
	data->aa.A3.cf.ADC_A2 = 10;
	data->aa.A3.cf.ADC_A3 = 10;
	data->aa.A3.cf.ADC_A4 = 10;
	data->aa.A3.cf.ADC_B5 = 10;
	data->aa.A3.cf.ADC_B6 = 10;
	data->aa.A3.cf.ADC_B7 = 10;
	data->aa.A3.cf.ADC_B8 = 10;

	// initalize PWM parameters
	data->ctrl.pwmFrequency = 10e3;		// PWM carrier frequency
	data->ctrl.pwmPeriod = 1 / data->ctrl.pwmFrequency;

	data->ctrl.samplingFrequency = data->ctrl.pwmFrequency * Interrupt_ISR_freq_factor;
	data->ctrl.samplingPeriod = 1 / data->ctrl.samplingFrequency;

	data->cw.switchingMode = 0; 		// PWM modulation
	data->rasv.pwmMinPulseWidth = 0.01;	// PWM minimum on time in %
}
