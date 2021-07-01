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

#include "../include/isr.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../include/pwm.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"


// Include for codegen
#include "../Codegen/uz_codegen.h"

//Initialize the variables for the ADC measurement
u32 		XADC_Buf[RX_BUFFER_SIZE]; //Test ADC
uint32_t 		ADC_RAW_Sum_1 = 0.0;
float 	ADC_RAW_Offset_1 = 0.0;
int 		i_CountADCinit =0, MessOnce=0, CountCurrentError =0;
_Bool     initADCdone = false;

//Initialize the Interrupt structure
XScuGic INTCInst;  		//Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

//Initialize the Timer structure
XTmrCtr Timer_Interrupt;

//Variables for debugging
float meas_Ua_Voltage = 0.0;
float meas_Ub_Voltage = 0.0;
float meas_Uc_Voltage = 0.0;
int bool_fault_U_Top = 0;
int bool_fault_U_Bot = 0;
int bool_fault_V_Top = 0;
int bool_fault_V_Bot = 0;
int bool_fault_W_Top = 0;
int bool_fault_W_Bot = 0;


float sin1amp=1.0;
//Global variable structure
extern DS_Data Global_Data;
extern uz_codegen codegenInstance;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void toggleLEDdependingOnReadyOrRunning(uint32_t i_count_1ms, uint32_t i_count_1s);
static void ReadAllADC();
static void CheckForErrors();

void ISR_Control(void *data)
{
	uz_SystemTime_ISR_Tic();
	// Toggle the System-Ready LED in order to show a Life-Check on the front panel
	toggleLEDdependingOnReadyOrRunning(uz_SystemTime_GetUptimeInMs(),uz_SystemTime_GetUptimeInSec());

	ReadAllADC();
	CheckForErrors();
	Encoder_UpdateSpeedPosition(&Global_Data); 	//Read out speed and theta angle

	//Assign Input Data

	//Enable Control Software
	codegenInstance.input.RESET = 0;
	codegenInstance.input.START = 0;

	//Read input values
	codegenInstance.input.ia = Global_Data.aa.A1.me.ADC_A1;
	codegenInstance.input.ib = Global_Data.aa.A1.me.ADC_A2;
	codegenInstance.input.ic = Global_Data.aa.A1.me.ADC_A3;
	codegenInstance.input.U_IC = Global_Data.aa.A1.me.ADC_A4;
	//Not used in Simulink-Model:
	meas_Ua_Voltage = Global_Data.aa.A1.me.ADC_B5;
	meas_Ub_Voltage = Global_Data.aa.A1.me.ADC_B6;
	meas_Uc_Voltage = Global_Data.aa.A1.me.ADC_B7;

	//Encoder
	codegenInstance.input.theta_el = Global_Data.av.theta_elec; //rad
	codegenInstance.input.n_ist = Global_Data.av.mechanicalRotorSpeed; //rpm
	codegenInstance.input.w_el = Global_Data.av.mechanicalRotorSpeed * Global_Data.mrp.motorPolePairNumber*M_PI/30; //rad/s



	//Start: Control algorithm -------------------------------------------------------------------------------
	if (Global_Data.cw.ControlReference == SpeedControl)
	{
		// add your speed controller here
		codegenInstance.input.flg_SpeedControl = 1.0;
	}
	else if(Global_Data.cw.ControlReference == CurrentControl)
	{
		// add your current controller here
		codegenInstance.input.flg_SpeedControl = 0.0;
	}
	else if(Global_Data.cw.ControlReference == TorqueControl)
	{
		// add your torque controller here
	}
	//End: Control algorithm -------------------------------------------------------------------------------

	//Call generated code
	uz_codegen_step(&codegenInstance);

	//Dutycycle outputs
	Global_Data.rasv.halfBridge1DutyCycle = codegenInstance.output.Ua_DutyCycle;
	Global_Data.rasv.halfBridge2DutyCycle = codegenInstance.output.Ub_DutyCycle;
	Global_Data.rasv.halfBridge3DutyCycle = codegenInstance.output.Uc_DutyCycle;

	Global_Data.av.I_d = codegenInstance.output.id_ist;
	Global_Data.av.I_q = codegenInstance.output.iq_ist;

	// Set duty cycles for two-level modulator
	PWM_SS_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
					Global_Data.rasv.halfBridge2DutyCycle,
					Global_Data.rasv.halfBridge3DutyCycle);

	// Set duty cycles for three-level modulator
	PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
					Global_Data.rasv.halfBridge2DutyCycle,
					Global_Data.rasv.halfBridge3DutyCycle);


	// Update JavaScope
	JavaScope_update(&Global_Data);

	// Read the timer value at the very end of the ISR to minimize measurement error
	// This has to be the last function executed in the ISR!
	uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================


//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR(){


	int Status = 0;

	// Initialize interrupt controller for the IPI -> Initialize RPU IPI
	Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
		if(Status != XST_SUCCESS) {
			xil_printf("RPU: Error: IPI initialization failed\r\n");
			return XST_FAILURE;
		}

	// Initialize interrupt controller for the GIC
	Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &Timer_Interrupt);
		if(Status != XST_SUCCESS) {
			xil_printf("RPU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}

	// Initialize mux_axi to use correct interrupt for triggering the ADCs
	Xil_Out32(XPAR_INTERRUPT_MUX_AXI_IP_0_BASEADDR + IPCore_Enable_mux_axi_ip, 1); // enable IP core
	Xil_Out32(XPAR_INTERRUPT_MUX_AXI_IP_0_BASEADDR + select_AXI_Data_mux_axi_ip, Interrupt_ISR_source_user_choice); // write selector

	//Motor parameters and constant factors
	Global_Data.mrp.motorPolePairNumber = 21;
	//ADC conversion factors
	Global_Data.aa.A1.cf.ADC_A1 = 80*5/32767;
	Global_Data.aa.A1.cf.ADC_A2 = 80*5/32767;
	Global_Data.aa.A1.cf.ADC_A3 = 80*5/32767;
	Global_Data.aa.A1.cf.ADC_A4 = 12.5*5/32767;
	Global_Data.aa.A1.cf.ADC_B5 = 12.5*5/32767;
	Global_Data.aa.A1.cf.ADC_B6 = 12.5*5/32767;
	Global_Data.aa.A1.cf.ADC_B7 = 12.5*5/32767;

	//Offset theta_el ---> Need to specify
	Global_Data.av.theta_offset = 0.0;

	//Flags
	codegenInstance.input.flg_PreCntr = 1.0;
	codegenInstance.input.flg_fieldWeakening = 0.0;
	codegenInstance.input.flgLimitUdUq = 1.0;
	codegenInstance.input.flg_UseMMPA = 0.0;

	//Only ratio of frequencies is crucial
	codegenInstance.input.T_speedController = 1/10000; //Hz
	codegenInstance.input.T_controller = 1/10000; //Hz

	//Controller settings
	Global_Data.cw.ControlReference = CurrentControl;
	//Setpoints Controller
	codegenInstance.input.iq_ref = 0.0;
	codegenInstance.input.id_ref = 0.0;
	codegenInstance.input.n_soll = 0.0;



return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE AXI-TIMER FOR ISRs
// - "TIMER_LOAD_VALUE" sets the counter-end-value in order to set the ISR-frequency f_c
// - "Con_TIMER_DEVICE_ID" uses the Device-ID of the used timer in Vivado
// - "Timer_Interrupt" is the used timer structure instance
// - "XTC_INT_MODE_OPTION" activates the Interrupt function
// - "XTC_AUTO_RELOAD_OPTION" activates an automatic reload of the timer
// - By default, the counter counts up
//----------------------------------------------------
int Initialize_Timer(){

	int Status;

	// SETUP THE TIMER 1 for Interrupts
	Status = XTmrCtr_Initialize(&Timer_Interrupt, XPAR_INTERRUPT_TRIGGER_F_CC_DEVICE_ID);
	if(Status != XST_SUCCESS) return XST_FAILURE;
	//XTmrCtr_SetHandler(&Timer_Interrupt, ISR_Control, &Timer_Interrupt);
	XTmrCtr_SetOptions(&Timer_Interrupt, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
	XTmrCtr_SetResetValue(&Timer_Interrupt, 0, TIMER_LOAD_VALUE);
	XTmrCtr_Reset(&Timer_Interrupt, 0);
	XTmrCtr_Start(&Timer_Interrupt,0);

	return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Timer_Interrupt_InstancePtr)
{
	XScuGic_Config *IntcConfig;
	int status;

	// Interrupt controller initialization
	IntcConfig = XScuGic_LookupConfig(DeviceId);
	status = XScuGic_CfgInitialize(IntcInstPtr, IntcConfig, IntcConfig->CpuBaseAddress);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,(Xil_ExceptionHandler)XScuGic_InterruptHandler,IntcInstPtr);

	/* Enable interrupts in the processor */
	Xil_ExceptionEnable();	//Enable interrupts in the ARM

	// setting interrupt trigger sensitivity
	// b01	Active HIGH level sensitive
	// b11 	Rising edge sensitive
	// XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
	XScuGic_SetPriorityTriggerType(IntcInstPtr, Interrupt_ISR_ID, 0x0, 0b11); // rising-edge
	//XScuGic_SetPriorityTriggerType(&INTCInst, Interrupt_ISR_ID, 0x0, 0b01); // active-high - default case

	// Make the connection between the IntId of the interrupt source and the
	// associated handler that is to run when the interrupt is recognized.
	status = XScuGic_Connect(IntcInstPtr,
								Interrupt_ISR_ID,
								(Xil_ExceptionHandler)ISR_Control,
								(void *)IntcInstPtr);
	if(status != XST_SUCCESS) return XST_FAILURE;

	// Connect ADC conversion interrupt to handler
//		status = XScuGic_Connect(&INTCInst,
//								INTC_ADC_Conv_INTERRUPT_ID,
//								(Xil_ExceptionHandler)Conv_ADC_Intr_Handler,
//								(void *)Conv_ADC_InstancePtr);
//		if(status != XST_SUCCESS) return XST_FAILURE;

	// Enable GPIO and timer interrupts in the controller
	XScuGic_Enable(IntcInstPtr, Interrupt_ISR_ID);
	XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);
//	XScuGic_Enable(&INTCInst, INTC_ADC_Conv_INTERRUPT_ID);


	xil_printf("RPU: Rpu_GicInit: Done\r\n");
	return XST_SUCCESS;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
 //----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
	XIpiPsu_Config *IntcConfig_IPI;
	int status;

	// Interrupt controller configuration
	IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
		if (IntcConfig_IPI == NULL) {
			xil_printf("RPU: Error: Ipi Init failed\r\n");
			return XST_FAILURE;
		}

	// Interrupt controller initialization
	status = XIpiPsu_CfgInitialize(&INTCInst_IPI, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
		if (status != XST_SUCCESS) {
			xil_printf("RPU: Error: IPI Config failed\r\n");
			return XST_FAILURE;
		}

	XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);



	xil_printf("RPU: RPU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}

static void toggleLEDdependingOnReadyOrRunning(uint32_t uptime_ms, uint32_t uptime_sec){
	if(Global_Data.cw.enableSystem){
	if((uptime_ms % 200)>100){
		uz_led_set_readyLED_on();
	}else{
		uz_led_set_readyLED_off();
	}
}else{
	if(uptime_sec % 2){
		uz_led_set_readyLED_on();
	}else{
		uz_led_set_readyLED_off();
	}
}
};

static void ReadAllADC(){
	if (initADCdone == false) { // init not done, determine ADC offset
		if (i_CountADCinit < 1000){
			i_CountADCinit++;
		}else{
			//ToDo: calculate average value in order to use as offset subsequently, e.g. like
			//ADC_RAW_Offset_1 = (float)ADC_RAW_Sum_1 / (float)i_CountADCinit;

			//toDO write for each ADC channel an own offset down.
			initADCdone = true;
			Global_Data.cw.ControlReference = CurrentControl; //default
			Global_Data.cw.ControlMethod = fieldOrientedControl; //default
			ADC_Clear_Offset();
		}
	}else{
		ADC_readCardALL(&Global_Data);
	}
};

static void CheckForErrors(){
	//Error detection
	if(Global_Data.cw.enableControl == true){
		//Detect continuous current-limit ---------------------------------------------------------------------------------------
		if ((Global_Data.av.I_U > Global_Data.mrp.motorMaximumCurrentContinuousOperation) || (Global_Data.av.I_V > Global_Data.mrp.motorMaximumCurrentContinuousOperation) || (Global_Data.av.I_W > Global_Data.mrp.motorMaximumCurrentContinuousOperation)){
			CountCurrentError++;
			if(CountCurrentError > 10){ //Only if the error is available for at least 10 cycles
		 // if(CountCurrentError > 20000){ //Only if the error is available for at least 2 seconds @100us ISR-cycle
				Global_Data.ew.maximumContinuousCurrentExceeded = true; //Current error detected -> errors are handled in the main.c
			}
		}else{
			CountCurrentError =0; //Reset Error Counter
		}

		//Detect short-time current-limit ---------------------------------------------------------------------------------------
		if ((Global_Data.av.I_U > Global_Data.mrp.motorMaximumCurrentShortTimeOperation) || (Global_Data.av.I_V > Global_Data.mrp.motorMaximumCurrentShortTimeOperation) || (Global_Data.av.I_W > Global_Data.mrp.motorMaximumCurrentShortTimeOperation)){
			ErrorHandling(&Global_Data);
			Global_Data.ew.maximumShortTermCurrentReached = true; //Current error detected -> errors are handled directly herein
		}
	}
};


