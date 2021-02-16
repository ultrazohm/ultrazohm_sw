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
#include <xtmrctr.h> //library for timing measurement
#include "../include/javascope.h"
#include "../include/pwm.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"

// Include for code-gen
#include "../Codegen/uz_codegen.h"

//Timing measurement variables
//Variables for ISR-time measurement
typedef struct _globalTiming_ {
	unsigned long long uptime_micro_seconds; 	// total uptime in micro seconds - us
	unsigned long long interrupt_counter;
	unsigned int uptime_minutes; 		// total uptime in minutes
	unsigned int uptime_milli_seconds; 	// total uptime in milli seconds
	unsigned int uptime_seconds; 		// total uptime in seconds
	unsigned int tick_counter_overflow;
	float isr_period_us;
	float isr_execution_time_us;
	float isr_execution_time_maximum_us;

} globalTimingR5;

globalTimingR5 timingR5 = {0,0,0,0,0,0,0};

uint32_t 	time_ISR_total, time_ISR_start, time_ISR_end;
float 	time_ISR_total_us, time_ISR_max_us = 0;
uint32_t 		i_ISRLifeCheck = 0;
uint32_t 		i_count_1ms = 0; // count up by 1 every 1ms
uint32_t 		i_count_1s = 0; // count up by 1 every 1s
float 	isr_period_us_measured;
unsigned int time_overflow_counter = 0;

//Initialize the variables for the ADC measurement
u32 		XADC_Buf[RX_BUFFER_SIZE]; //Test ADC
uint32_t 		ADC_RAW_Sum_1 = 0.0;
float 	ADC_RAW_Offset_1 = 0.0;
int 		i_CountADCinit =0, MessOnce=0, CountCurrentError =0;
_Bool     initADCdone = false;

//Initialize the Interrupt structure
XScuGic INTCInst;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

//Initialize the Timer structure
XTmrCtr TMR_Con_Inst;

float sin1amp=100.0;

//Global variable structure
extern DS_Data Global_Data;



//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void toggleLEDdependingOnReadyOrRunning(uint32_t i_count_1ms, uint32_t i_count_1s);
static void MeasureTimeForJavascope(globalTimingR5* time);
static void ReadAllADC();
static void CheckForErrors();
static void CalculateTimeISRtookToExecute();

void ISR_Control(void *data)
{
	// Enable and acknowledge the timer
	XTmrCtr_Reset(&TMR_Con_Inst,0);
	// Read the timer value at the beginning of the ISR in order to measure the ISR-time
	// Is the timer not simply zero due to the reset above?
	time_ISR_start = XTmrCtr_GetValue(&TMR_Con_Inst,0);

	//measure the time for the JavaScope
	MeasureTimeForJavascope(&timingR5);
	// Toggle the System-Ready LED in order to show a Life-Check on the front panel
	toggleLEDdependingOnReadyOrRunning(i_count_1ms,i_count_1s);

	ReadAllADC();
	CheckForErrors();
	Encoder_UpdateSpeedPosition(&Global_Data); 	//Read out speed and theta angle

	//Start: Write the references for the FPGA ---------------------------------------------------------------------------------------
	if (Global_Data.cw.ControlReference == SpeedControl)
	{
		// add your speed controller here
	}
	else if(Global_Data.cw.ControlReference == CurrentControl)
	{
		// add your current controller here
	}
	else if(Global_Data.cw.ControlReference == TorqueControl)
	{
		// add your torque controller here
	}

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

	//Read the timer value at the end of the ISR in order to measure the ISR-time
	time_ISR_end = XTmrCtr_GetValue(&TMR_Con_Inst,0);

	//Calculate the required ISR-time
	CalculateTimeISRtookToExecute();
}

//==============================================================================================================================================================
//----------------------------------------------------
// Measure the time for the JavaScope
//----------------------------------------------------
static void MeasureTimeForJavascope(globalTimingR5* time){

	// DO NOT USE COUNTS_PER_USECOND, this macro has a large rounding error!
	float const counts_per_us = (COUNTS_PER_SECOND) * 1e-6;

	XTime tPrev;
	XTime static tNow = 0;

	// save previous read
	tPrev = tNow;
	// read clock counter of R5 processor, which starts at 0 after reset/starting the processor
	XTime_GetTime(&tNow);

	// calculate ISR period, the time between two calls of this function
	XTime isr_period_counts = (tNow - tPrev);
	isr_period_us_measured = isr_period_counts / counts_per_us;

	//catch overflow after 9.16 minutes when tNow (32bit) starts from 0 again
	if (tNow < tPrev){
		time->tick_counter_overflow++;
	}

	//measure with 1ms cycle
	time->uptime_milli_seconds = tNow/((COUNTS_PER_SECOND) * 1e-3);

	//measure with 1s cycle
	const unsigned int unsigned_int_max_number = ~(unsigned int)0;
	i_count_1s = (int) (i_count_1ms*1e-3) + time_overflow_counter * (unsigned_int_max_number/COUNTS_PER_SECOND); //   9.16minutes = 549.7559 seconds = (2^32-1)/COUNTS_PER_SECOND

	// counting interrupts since booting
	time->interrupt_counter++;
	i_ISRLifeCheck = time->interrupt_counter % 1000; //to be deleted?


}

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
	Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &TMR_Con_Inst);
		if(Status != XST_SUCCESS) {
			xil_printf("RPU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}

	// Initialize mux_axi to use correct interrupt for triggering the ADCs
	Xil_Out32(XPAR_INTERRUPT_MUX_AXI_IP_0_BASEADDR + IPCore_Enable_mux_axi_ip, 1); // enable IP core
	Xil_Out32(XPAR_INTERRUPT_MUX_AXI_IP_0_BASEADDR + select_AXI_Data_mux_axi_ip, Interrupt_ISR_source_user_choice); // write selector

return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE AXI-TIMER FOR ISRs
// - "TMR_Con_LOAD" sets the counter-end-value in order to set the ISR-frequency f_c
// - "Con_TIMER_DEVICE_ID" uses the Device-ID of the used timer in Vivado
// - "TMR_Con_Inst" is the used timer structure instance
// - "XTC_INT_MODE_OPTION" activates the Interrupt function
// - "XTC_AUTO_RELOAD_OPTION" activates an automatic reload of the timer
// - By default, the counter counts up
//----------------------------------------------------
int Initialize_Timer(){

	int Status;

	// SETUP THE TIMER for Control
	Status = XTmrCtr_Initialize(&TMR_Con_Inst, Con_TIMER_DEVICE_ID);
	if(Status != XST_SUCCESS) return XST_FAILURE;
	//XTmrCtr_SetHandler(&TMR_Con_Inst, ISR_Control, &TMR_Con_Inst);
	XTmrCtr_SetOptions(&TMR_Con_Inst, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
	XTmrCtr_SetResetValue(&TMR_Con_Inst, 0, TMR_Con_LOAD);
	XTmrCtr_Start(&TMR_Con_Inst,0);

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
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Tmr_Con_InstancePtr)
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

static void toggleLEDdependingOnReadyOrRunning(uint32_t i_count_1ms, uint32_t i_count_1s){
	if(Global_Data.cw.enableSystem){
	if((i_count_1ms % 200)>100){
		uz_led_SetLedReadyOn();
	}else{
		uz_led_SetLedReadyOff();
	}
}else{
	if(i_count_1s % 2){
		uz_led_SetLedReadyOn();
	}else{
		uz_led_SetLedReadyOff();
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


static void CalculateTimeISRtookToExecute(){
	time_ISR_total = time_ISR_end - time_ISR_start;
	time_ISR_total_us = time_ISR_total * 1e-2 ; //PL clock-Ticks* @100MHz Clock [us]

	if(time_ISR_total_us > time_ISR_max_us){
		time_ISR_max_us = (time_ISR_total_us);
	}
};
