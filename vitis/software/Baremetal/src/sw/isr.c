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

float sin1amp=1.0;
//Global variable structure
extern DS_Data Global_Data;
extern uz_codegen codegenInstance;
extern P rtP;

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
	Encoder_UpdateSpeedPosition(&Global_Data); 	//Read out speed and theta angle

	//FOC_Strom Assign Signal-Values
	codegenInstance.input.Act_Iu = (Global_Data.aa.A2.me.ADC_A1-2.5) * 80.0F/4.0F - 0.17F;		//A
	codegenInstance.input.Act_Iv = (Global_Data.aa.A2.me.ADC_A2-2.5) * 80.0F/4.0F + 0.06F;		//A
	codegenInstance.input.Act_Iw = (Global_Data.aa.A2.me.ADC_A3-2.5) * 80.0F/4.0F - 0.21F;		//A
	codegenInstance.input.Act_U_ZK = Global_Data.aa.A2.me.ADC_A4 * 12.5F;			//V

	codegenInstance.input.Act_n = Global_Data.av.mechanicalRotorSpeed; 				//[RPM]
	codegenInstance.input.Act_w_el = codegenInstance.input.Act_n * Global_Data.mrp.motorPolePairNumber*M_PI/30.0F; //[rad/s]
	codegenInstance.input.Act_theta_el = Global_Data.av.theta_elec + Global_Data.mrp.incrementalEncoderOffset; 	//[rad] Definition in main.c

	//FOC Assign Javasope-reference-values
	codegenInstance.input.Ref_n = Global_Data.rasv.referenceSpeed;
	codegenInstance.input.Ref_Id_ext = Global_Data.rasv.referenceCurrent_id;
	codegenInstance.input.Ref_Iq_ext = Global_Data.rasv.referenceCurrent_iq;

	//FOC Enable control with Javascope
	codegenInstance.input.fl_power = Global_Data.cw.enableControl;

	//Change control type with javascope
	if(Global_Data.cw.ControlReference == 2U)
	{
		codegenInstance.input.fl_control_type = 1U;
	}
	else
	{
		codegenInstance.input.fl_control_type = 0U;
	}

	//FOC_Strom Call generated code if no faults are present
	if (Global_Data.cw.enableSystem)
	{
		uz_codegen_step(&codegenInstance);
	}
	CheckForErrors();

	//FOC_Strom Output


	Global_Data.rasv.halfBridge1DutyCycle = codegenInstance.output.a_U;
	Global_Data.rasv.halfBridge2DutyCycle = codegenInstance.output.a_V;
	Global_Data.rasv.halfBridge3DutyCycle = codegenInstance.output.a_W;


	// Set duty cycles for two-level modulator
	PWM_SS_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
					Global_Data.rasv.halfBridge2DutyCycle,
					Global_Data.rasv.halfBridge3DutyCycle);

	// Set duty cycles for three-level modulator
	/*
	PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
					Global_Data.rasv.halfBridge2DutyCycle,
					Global_Data.rasv.halfBridge3DutyCycle);
	*/


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

	//Set Flags and referenceValues of FOC to zero
	codegenInstance.input.fl_power = 0U;
	codegenInstance.input.fl_control_type = 0U;
	codegenInstance.input.fl_integrator_reset = 0U;
	codegenInstance.input.fl_field_weakening = 1U;
	codegenInstance.input.fl_voltage_limitation = 2U;
	codegenInstance.input.fl_decoupling = 1U;
	codegenInstance.input.fl_angle_prediction = 1U;
	codegenInstance.input.Ref_n = 0.0F;
	codegenInstance.input.Ref_Id_ext = 0.0F;
	codegenInstance.input.Ref_Iq_ext = 0.0F;

	//Set CodeGen-SampleTime according to settings in main
	rtP.T_R = Global_Data.ctrl.samplingPeriod;

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

/* Old CheckForErrors
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
*/

static void CheckForErrors(){
	//Error detection
	if(Global_Data.cw.enableControl == true)
	{
		//Detect peak current-limit ---------------------------------------------------------------------------------------
		if (codegenInstance.output.fault_peak_current == 1.0F)
		{
			Global_Data.ew.maxPeakCurrentReached = true; //Current error detected
			ErrorHandling(&Global_Data);
		}

		//Detect continuous current-limit ---------------------------------------------------------------------------------------
		if (codegenInstance.output.fault_max_current == 1.0F)
		{
			Global_Data.ew.maxContinuousCurrentReached = true; //Current error detected
			ErrorHandling(&Global_Data);
		}
		//Detect peak speed-limit ---------------------------------------------------------------------------------------
		if (codegenInstance.output.fault_peak_speed == 1.0F)
		{
			Global_Data.ew.maxPeakSpeedReached = true; //Speed error detected
			ErrorHandling(&Global_Data);
		}
		//Detect continuous speed-limit ---------------------------------------------------------------------------------------
		if (codegenInstance.output.fault_max_speed == 1.0F)
		{
			Global_Data.ew.maxContinuousSpeedReached = true; //Speed error detected
			ErrorHandling(&Global_Data);
		}
		//Detect DC-Link Overvoltage ---------------------------------------------------------------------------------------
		if (codegenInstance.input.Act_U_ZK >= Global_Data.mrp.motorMaximumDcLinkVoltage)
		{
			Global_Data.ew.dcLinkOvervoltageOccured = true; //Speed error detected
			ErrorHandling(&Global_Data);
		}
	}
};
