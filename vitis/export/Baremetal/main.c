/******************************************************************************
*
* main.c
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
*
* Description: Zynq UltraScale+
*
******************************************************************************/

//Includes from own files
#include "main.h"
#include "defines.h"
#include "include/isr.h"
#include "include/adc.h"
#include "include/encoder.h"
#include "include/gpio.h"
#include "include/gpio_axi.h"
#include "include/pwm.h"
#include "include/javascope.h"
#include "include/control.h"
#include "include/pwm_3L_driver.h"


//Initialize the global variables
Xint16 i_LifeCheck;
Xboolean bSetDuty 	= valueFalse;
Xboolean bPlotData	= valueFalse;
Xboolean bInit 		= valueFalse;

Xboolean bNewControlMethodAvailable = valueFalse;

DS_Data Global_Data;

extern XGpioPs Gpio_OUT;											/* GPIO Device driver instance for the real GPIOs */

//ARM_to_Oszi_Data_shared_struct OsziData __attribute__((section(".sharedRAM_Oszidata"))); //Data from A9_0 to A9_1 (from BareMetal to FreeRTOS) in order to provide data for the GUI (Ethernet-Plot)
//Oszi_to_ARM_Data_shared_struct ControlData __attribute__((section(".sharedRAM_Controldata"))); //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
ARM_to_Oszi_Data_shared_struct OsziData; //Data from A9_0 to A9_1 (from BareMetal to FreeRTOS) in order to provide data for the GUI (Ethernet-Plot)
Oszi_to_ARM_Data_shared_struct ControlData; //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
Oszi_to_ARM_Data_shared_struct ControlDataShadowBare; //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI


int main (void){

	int status;

	// Initialize the global "Global_Data" structure -> the values can be overwritten afterwards from the Java-GUI -> this must be the first INIT-function, because it is required subsequently!
	InitializeDataStructure(&Global_Data);

	// Initialize the GPIOs which are connected over FPGA pins
	Initialize_AXI_GPIO();

	// Initialize pushbuttons and GPIO
	Initialize_GPIO();

	// Initialize ADCs
	Initialize_ADC_CONVERSION();

	// Initialize Park-Transformation 123 to dq
	Initialize_TRANS_123_DQ_CONVERSION(&Global_Data);

    //Initialize PWM and switch signal control
	PWM_SS_Initialize(&Global_Data); 	// two-level modulator
    PWM_3L_Initialize();				// three-level modulator

	// Initialize Timer in order to Trigger the ISRs
	Initialize_Timer();

	// Initialize Timer in order to Trigger the ADC conversion
	Initialize_Trigger_ADC_Conversion();

	// Initialize the encoder
	Initialize_Encoder(&Global_Data);

	// Initialize the FPGA control algorithm
	Initialize_FPGAController(&Global_Data);

	// Initialize the ARM control algorithm
	Initialize_ARMController(&Global_Data);

   	//Initialize the Soft-Oscilloscope ("JavaScope")
	Initialize_JavaScope();

	// Initialize the Interrupts
	Initialize_ISR();

	//Output to the Terminal over UART to the COM-Port. Use e.g. "Tera Term" to listen with baud-rate 115200
	xil_printf("\r\n\r\n");
	xil_printf("Welcome to the UltraZohm\r\n");
	xil_printf("----------------------------------------\r\n");

	//Set the current value in the ADC as offset/default value
	ADC_Set_Offset();

	// Turn on AXI2TCM communication
	AXI2TCM_on();

	//Initial state of all front panel LEDs is off
	WritePin_PS_GPIO(LED_1,valueFalse); //Write a GPIO for LED_1
	WritePin_PS_GPIO(LED_2,valueFalse); //Write a GPIO for LED_2
	WritePin_PS_GPIO(LED_3,valueFalse); //Write a GPIO for LED_3
	WritePin_PS_GPIO(LED_4,valueFalse); //Write a GPIO for LED_4

	// Infinite loop
	while (1){

		// poll the buttons
		Global_Data.dv.sw1=ReadPin_PS_GPIO(SW_system);
		Global_Data.dv.sw2=ReadPin_PS_GPIO(SW_control);
		Global_Data.dv.sw3=ReadPin_PS_GPIO(SW_stop);
		// Set the system enable flag to false if SW1 is pressed
		if (Global_Data.dv.sw1==valueTrue){
			Global_Data.cw.enableSystem=flagEnabled;
		}
		// Set the control enable flag to false if SW2 is pressed
		if (Global_Data.dv.sw2==flagEnabled){
			Global_Data.cw.enableControl=flagEnabled;
		}
#ifndef UltraZohmV2 // in CarrierBoard_v2 there are no buttons, therefore always SW_stop is always zero/false
		// Set the control enable and system enable flag to false if SW3 is pressed
		if (Global_Data.dv.sw3==valueFalse){
			Global_Data.cw.enableControl=flagDisabled;
			Global_Data.cw.enableSystem=flagDisabled;
		}
#endif

		//ToDo: //Add here more possible errors?!
		if((Global_Data.ew.maximumContinuousCurrentExceeded == valueTrue)||(Global_Data.ew.maximumShortTermCurrentReached == valueTrue)||(Global_Data.ew.dcLinkOvervoltageOccured == valueTrue)||(Global_Data.ew.pwmFrequencyError == valueTrue)){
			WritePin_PS_GPIO(LED_error,valueTrue); //Write a GPIO for LED_3
			ErrorHandling(&Global_Data);
			ErrorReset(&Global_Data);	//If any error is active -> check if an error-reset is received
		}else{//no errors
			//Check the control values
			if(Global_Data.cw.enableSystem == flagDisabled){
				turnPowerElectronicsOff(&Global_Data); //Switch power converter off
			}else if((Global_Data.cw.enableSystem == flagEnabled) && bInit == valueFalse){ //Call this function only once. If there was an error, "enableSystem " must be reseted!
				turnPowerElectronicsOn(&Global_Data); //Switch power converter on
			}

			if(Global_Data.cw.enableControl == flagEnabled){
				ControllerOn(&Global_Data); //Switch controller on
			}else{
				ControllerOff(&Global_Data); //Switch controller off
			}
		}

		//Change the operation mode only if the system is in a safe state
		if((Global_Data.cw.enableSystem == flagDisabled)&&(Global_Data.cw.enableControl == flagDisabled)&&(bNewControlMethodAvailable == valueTrue)){
			switch(Global_Data.cw.ControlMethod){
				case DirectTorqueControl:
					Configure_DTC_Control(&Global_Data);
					PWM_SS_Initialize(&Global_Data);
					xil_printf("DTC is active\n");
					break;
				case fieldOrientedControl:
					Configure_FOC_Control(&Global_Data);
					PWM_SS_Initialize(&Global_Data);
					xil_printf("FOC is active\n");
					break;
				case ModelPredictiveControl:
					Configure_MPC_Control(&Global_Data);
					PWM_SS_Initialize(&Global_Data);
					xil_printf("MPC is active\n");
					break;
				case sixStepCommutation:
					//toDO not used at the moment
					PWM_SS_Initialize(&Global_Data);
					xil_printf("Six-Step commutation is active\n");
					break;
				case halfBridgeControl:
					Configure_HalfBridge_Control(&Global_Data);
					PWM_SS_Initialize(&Global_Data);
					xil_printf("Half Bridge control is active\n");
					break;
				default:
					xil_printf("No valid control method is active\n");
					break;
			}
			bNewControlMethodAvailable = valueFalse; //Reset the Flag in order to initialize the IP Cores and functions after a new control method arrives, only once!
		}


		if (bPlotData){
			plotData(&Global_Data);
		}

		i_LifeCheck++; //LiveCheck for the main while-1 loop
		if(i_LifeCheck > 2500){
			i_LifeCheck =0;
		}
	}
	return status;
}


//==============================================================================================================================================================
int turnPowerElectronicsOff(DS_Data* data){

	bInit = valueFalse;
	data->rasv.referenceCurrent_iq = 0; // in A
	data->rasv.referenceCurrent_id = 0; // in A
	data->rasv.ModifiedReferenceCurrent_iq = 0; // in A
	data->rasv.ModifiedReferenceCurrent_id = 0; // in A
	data->rasv.referenceSpeed = 0; // in rpm
	data->cw.enableControl = flagDisabled; 		//Switch controller off

	//Disable power electronics
	XGpio_DiscreteClear(&Gpio_OUT,GPIO_CHANNEL, 3);//Switch power electronics off = 0b0001 = "Disable_Inverter" //Switch Gate connection off = 0b0010 = "Disable_Gate"
	//	asm(" nop"); //Wait some ticks, otherwise, the second GPIO write will not be updated
	//	XGpio_DiscreteSet(&Gpio_OUT,GPIO_CHANNEL, 0b0010);//Switch Gate connection and power electronics off // "Disable_Gate" = Consider, this is a inverse signal //"Disable_Inverter"
	return (0);
}

//==============================================================================================================================================================
int turnPowerElectronicsOn(DS_Data* data){

	XGpio_DiscreteSet(&Gpio_OUT,GPIO_CHANNEL, 3);//Switch power electronics on = 0b0001 = "Enable_Inverter" On  //Switch Gate connection on = 0b0010 = "Enable_Gate" On

	asm(" nop"); //Wait some ticks, otherwise, the second GPIO write will not be updated
	XGpio_DiscreteClear(&Gpio_OUT,GPIO_CHANNEL, 4);//Stop to the ADC module to set an offset value    0b0100);  	// "Enable_Gate" On //Consider, this is a inverse signal AND "Acknowledge" the set of ADC offset value.
	//	XGpio_DiscreteSet(&Gpio_OUT,GPIO_CHANNEL, 0x0b0001);//Switch power electronics on  // "Enable_Gate" On = Consider, this is a inverse signal // "Enable_Inverter" On
	bInit = valueTrue;
	return (0);
}

//==============================================================================================================================================================
int ControllerOff(DS_Data* data){

	WritePin_PS_GPIO(LED_running,valueFalse); //Write a GPIO for LED_2
	return (0);
}

//==============================================================================================================================================================
int ControllerOn(DS_Data* data){

	WritePin_PS_GPIO(LED_running,valueTrue); //Write a GPIO for LED_2
	return (0);
}

//==============================================================================================================================================================
int ErrorHandling(DS_Data* data){

	ControllerOff(data); 					//Switch controller off
	data->rasv.referenceCurrent_iq = 0; 	// in A
	data->rasv.referenceSpeed = 0; 			// in rpm
	data->cw.enableControl = flagDisabled;	//Switch controller off

	turnPowerElectronicsOff(data); 			// Switch power electronics off
	data->cw.enableSystem = flagDisabled;	// Switch power electronics off
	return (0);
}

//==============================================================================================================================================================
int ErrorReset(DS_Data* data){

	if(data->er.dcLinkOvervoltageOccured == valueTrue){
		data->ew.dcLinkOvervoltageOccured = valueFalse;  	//Reset over-voltage
		data->er.dcLinkOvervoltageOccured = valueFalse;	//Reset flag
	}
	if(data->er.maximumContinuousCurrentExceeded == valueTrue){
		data->ew.maximumContinuousCurrentExceeded  = valueFalse;  //Reset Continuous Current Exceeded
		data->er.maximumContinuousCurrentExceeded = valueFalse;	//Reset flag
	}
	if(data->er.maximumShortTermCurrentReached == valueTrue){
		data->ew.maximumShortTermCurrentReached = valueFalse;  	//Reset maximum Short-Term Current Reached
		data->er.maximumShortTermCurrentReached = valueFalse;		//Reset flag
	}
	if(data->er.pwmFrequencyError == valueTrue){
		data->ew.pwmFrequencyError = valueFalse;  //Reset pwm Frequency Error
		data->er.pwmFrequencyError = valueFalse;	//Reset flag
	}

	WritePin_PS_GPIO(LED_error,valueFalse); //Write a GPIO for LED_3

	return (0);
}

//==============================================================================================================================================================
int ADC_Set_Offset(){
	XGpio_DiscreteSet(&Gpio_OUT,GPIO_CHANNEL, 4);// 4 = 0b0100 Enable the ADC module to set an offset value. Call this function only at the beginning once
	return (0);
}

//==============================================================================================================================================================
int AXI2TCM_on(){
	XGpio_DiscreteSet(&Gpio_OUT,GPIO_CHANNEL, 0b10000);// bit 5 : 16 = 0b10000 Enables the AXI2TCM module to write measurements directly to the TCM
	return(0);
}

//==============================================================================================================================================================
int plotData(DS_Data* data){

	printf("Reference current in float: %f \r\n", data->rasv.referenceCurrent_iq );

	printf("ADC I_a: %f \r\n", data->av.I_U);
	printf("ADC I_b: %f \r\n", data->av.I_V);
	printf("ADC I_c: %f \r\n", data->av.I_W);

	//Output encoder values
	printf("Speed in rpm: %f \r\n", data->av.mechanicalRotorSpeed);
	printf("theta_el: %f \r\n", data->av.theta_elec);
	printf("theta_mech: %f \r\n", data->av.theta_mech);
//	printf("Direction ( 1= positiv and 0 = negativ): %d \r\n", u8Direction);
	printf("Actual DutyCycle: %d \r\n", (Xint16)(data->rasv.sixStepCommutationDutyCycle*100.0));

	bPlotData	= valueFalse; // print only once

	return 0;
}


//==============================================================================================================================================================
//----------------------------------------------------
// Software delay
//----------------------------------------------------
void delayy(){
	int i ;
	int x;
	int delayTime=10000;
	for (i=0;i<delayTime;i++){
		x=x+0; // Idle Loop
	}
}


//==============================================================================================================================================================
int InitializeDataStructure(DS_Data* data){

	data->av.U_ZK = 24.0; 								//[V] DC-Link voltage

	//Control
	data->cw.ControlReference 	= CurrentControl; 		// default because of Parameter ID
	data->cw.ControlMethod 		= fieldOrientedControl; // default because of Parameter ID
	//Default control method
	Configure_FOC_Control(data);

	//Encoder
	data->mrp.incrementalEncoderResolution = 5000.0; //[Increments per turn] // Number of increments in the motor (necessary for the encoder)( the orange encoder has 2500 lines. This means 10000 edges with the two A and B lines)
	data->mrp.incrementalEncoderOffset = 3.141592653589; //[rad]  //Offset for the Park-Transformation -> pi = 3.141592653589
	data->mrp.motorMaximumSpeed = 6000.0; //[rpm]
	data->mrp.incrementalEncoderOversamplingFactor = 5.0; //Oversampling factor must be between 1.0-6.0 (Achtung, immer mit Punkt da sonst nicht als float interpretiert

	//Motor related parameters
	Initialize_MotorRelatedParameters(data);

	//MPC
	data->ctrl.mpc.fcs.bEnableVSP2CC 	= valueFalse;
	data->ctrl.mpc.fcs.lambda_dU 		= 0;

	//FOC
	data->ctrl.foc.cc.FOCFeedForward =valueFalse;
	data->ctrl.foc.sc.referenceSpeedRamped =0.0;
	data->ctrl.foc.numberValidValuesInMTPA =0;

	//toDO: Write the ADC conversion factors from the processor -> at the moment this factors are not used!
	data->mrp.ADCConversionFactorIph =0.0;
	data->mrp.ADCConversionFactorIdc =0.0;
	data->mrp.ADCConversionFactorVph =0.0;
	data->mrp.ADCConversionFactorVdc =0.0;
	data->mrp.ADCConversionFactorTrq =0.0;
	data->mrp.ADCConversionFactorTmp =0.0;
	data->mrp.ADCconvFactorReadback  =0.0;

	//Initialize Automatic Current Reference Control Inputs
	data->pID.bEnableAutoCurrentControl=valueFalse;
	data->pID.d_current_steps		= 10; // Between 3 -10 is a good range
	data->pID.q_current_steps		= 10; // Between 3 -10 is a good range
	data->pID.max_res_ref_current	= 12.0; // Depends on the required range of the identified flux map and the possible range of the current sensor
	//Initialize Automatic Current Reference Control Outputs
	data->pID.bRefAutomaticControlled= valueFalse;

	//Initialize Offline ID Stateflow Inputs
	data->pID.MotorID				= 1;
//	data->pID.controlType			= 1;
	data->pID.accept				= valueFalse;
	data->pID.reset_Offl			= valueFalse;
	data->pID.sampleTimeISR			= 0.0001;
	data->pID.dutyCyc				= 0.05;
	data->pID.n_ref_measurement		= 200;
	data->pID.identLq				= 0;
	data->pID.VibON					= 0;
	data->pID.VibAmp				= 0;
	data->pID.VibFreq				= 0;
	data->pID.identR 				= 0;
	data->pID.AMM_ON				= 0;
	data->pID.AMM_RUN				= 0;
	data->pID.IDstart	 			= 0.0;
	data->pID.IDstop				= 0.0;
	data->pID.IDstepsize			= 0.0;
	data->pID.IQstart 				= 0.0;
	data->pID.IQstop				= 0.0;
	data->pID.IQstepsize			= 0.0;
	data->pID.LogIntervals 			= 0;
	data->pID.NumberOfSamples		= 0;
	data->pID.settlingTime			= 0.0;
	data->pID.n_visco_max			= 500;
	data->pID.N_Brk					= 5;
	data->pID.Brk_Count				= 20;
	data->pID.N_visco				= 200;
	data->pID.f_min					= 5;
	data->pID.f_max					= 90;
	data->pID.d_TMS_start			= 0.0001;
	data->pID.StepScale 			= 0.001;
	data->pID.ScaleTorquePRBS 		= 2;
	data->pID.eta_omega_Reib		= 0.2;

	//Online and Offline ID Stateflow Inputs
	data->pID.identRAmp				= 0.1*data->mrp.motorNominalCurrent;
	data->pID.Temp_ref				= 20.0;

	//Online ID Stateflow Inputs
	data->pID.bEnableOnlineID=valueFalse;
	data->pID.DevSpeed			= 0.1;// 10% of actual Value
	data->pID.DevCurrent		= 0.2;//20% of actual Value
	data->pID.AverageTransParams= 1;
	data->pID.AllowStepFlag		= 1;
	data->pID.ResetOnline		= 0;

	//Initialize Offline ID Stateflow Outputs
	data->pID.activeState 		= 0;
	data->pID.offsetLock		= 1;
	data->pID.array_counter 	= 0;
	data->pID.controlArrCounter	= 0;
	data->pID.AdmitParamsFlag	= valueFalse;
	data->pID.AdmitMechParamsFlag= valueFalse;

	// Initialize Online ID Stateflow Outputs
	data->pID.bOnlineIDenabled		= valueFalse;
	data->pID.map_counter 			= 0;
	data->pID.ControlMapCounter		= 0;

	//Initialize the error states
	data->ew.communicationTimeoutOccured = valueFalse;
	data->ew.dcLinkOvervoltageOccured = valueFalse;
	data->ew.errorCodeXilinx = 0;
	data->ew.maximumContinuousCurrentExceeded = valueFalse;
	data->ew.maximumShortTermCurrentReached = valueFalse;
	data->ew.mtpaTableError = valueFalse;
	data->ew.pwmFrequencyError = valueFalse;
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

	return (0);
}


