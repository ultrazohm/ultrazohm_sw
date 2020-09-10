/******************************************************************************
*
* isr.c
*
* Copyright (C) 2019 UltraZohm Community, All rights reserved.
*
*  Created on: 22.08.2018
*      Author: Wendel Sebastian (SW)
* Description: Zynq UltraScale+
*
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

//General variables
Xfloat32 	time_ISR_max=0;
Xint32 		i_ISRLifeCheck = 0;
Xfloat32 	f_ISRLifeCheck = 0;
Xint32 		i_count_1ms = 0; // count up by 1 every 1ms
Xint32 		i_count_1s = 0; // count up by 1 every 1s

//Initialize the variables for the ADC measurement
u32 		XADC_Buf[RX_BUFFER_SIZE]; //Test ADC
Xint32 		ADC_RAW_Sum_1 = 0.0;
Xfloat32 	ADC_RAW_Offset_1 = 0.0;
Xint16 		i_CountADCinit =0, MessOnce=0, CountCurrentError =0;
boolean     initADCdone = valueFalse;

// Initialize the  GPIO structure
extern XGpioPs Gpio_IN;											/* GPIO Device driver instance for the real GPIOs */
extern XGpioPs Gpio_OUT;											/* GPIO Device driver instance for the real GPIOs */

//Initialize the Interrupt structure
XScuGic INTCInst;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI;  	//Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

//Initialize the Timer structure
XTmrCtr TMR_Con_Inst;

//Variables for JavaScope
extern Oszi_to_ARM_Data_shared_struct ControlData; //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
extern Oszi_to_ARM_Data_shared_struct ControlDataShadowBare; //Data from A9_1 to A9_0 (from FreeRTOS to BareMetal) in order to receive control data from the GUI
Xfloat32 test_js_sinewave1=0.0, test_javaScope_freqHz=1.0, argument=0.0, sin1amp=100.0, sin2amp=80.0, sawfak=0.2;
Xfloat32 test_js_sinewave2=0.0, test_js_sawtooth1=0.0, test_js_sawtooth2=0.0;
Xuint32 cnt_200us=0, chscope=4;

//Global variable structure
extern DS_Data Global_Data;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - called by the hardware timer
// - start of the control period
//----------------------------------------------------
void TMR_Con_Intr_Handler(void *data)
{
	//Show start of control-ISR by toggling a pin
	//XGpio_DiscreteWrite(&Gpio_OUT,GPIO_CHANNEL , 0b0010);  // --+-
	//if you have a device, which may produce several interrupts one after another, the first thing you should do here, is to disable interrupts!
	// Enable and acknowledge the timer
	XTmrCtr_Reset(&TMR_Con_Inst,0);

	//Read the timer value at the beginning of the ISR in order to measure the ISR-time
	time_ISR_start = XTmrCtr_GetValue(&TMR_Con_Inst,0);

	i_ISRLifeCheck++; //LiveCheck
	if(i_ISRLifeCheck > 10000){
		i_ISRLifeCheck = 1; //If the value is 10001, than set to 1 in order to avoid value-overflow
	}

	MeasureTime();	//measure the time for the JavaScope

	// Toggle the System-Ready LED in order to show a Life-Check on the front panel
	if(Global_Data.cw.enableSystem){
		if((i_count_1ms % 200)>100){
			WritePin_PS_GPIO(LED_ready,valueTrue); //Write a GPIO for LED_1
		}else{
			WritePin_PS_GPIO(LED_ready,valueFalse); //Write a GPIO for LED_1
		}
	}else{
		if(i_count_1s % 2){
			WritePin_PS_GPIO(LED_ready,valueTrue); //Write a GPIO for LED_1
		}else{
			WritePin_PS_GPIO(LED_ready,valueFalse); //Write a GPIO for LED_1
		}
	}

	//Start: Read out ADCs ---------------------------------------------------------------------------------------
	if (initADCdone == valueFalse) { // init not done, determine ADC offset
		if (i_CountADCinit < 1000){
			//ToDo: Read the ADC-Register and sum up over 1000 measurements, e.g. like
			//ADC_RAW_Sum_1 += Xil_In32(ADC_RAW_Value_1_REG); //Read AXI-register
			i_CountADCinit++;
		}else{
			//ToDo: calculate average value in order to use as offset subsequently, e.g. like
			//ADC_RAW_Offset_1 = (Xfloat32)ADC_RAW_Sum_1 / (Xfloat32)i_CountADCinit;

			//toDO write for each ADC channel an own offset down.
			initADCdone = valueTrue;
			Global_Data.cw.ControlReference = CurrentControl; //default
			Global_Data.cw.ControlMethod = fieldOrientedControl; //default
			ADC_Clear_Offset();
		}
	}else{

		// Choose here which ADC card to read
		//ADC_readCardA1(&Global_Data);
		//ADC_readCardA2(&Global_Data);
		//ADC_readCardA3(&Global_Data);
		ADC_readCardALL(&Global_Data);

	}
	//End: Read out ADCs ---------------------------------------------------------------------------------------


	//Error detection
	if(Global_Data.cw.enableControl == flagEnabled){
		//Detect continuous current-limit ---------------------------------------------------------------------------------------
		if ((Global_Data.av.I_U > Global_Data.mrp.motorMaximumCurrentContinuousOperation) || (Global_Data.av.I_V > Global_Data.mrp.motorMaximumCurrentContinuousOperation) || (Global_Data.av.I_W > Global_Data.mrp.motorMaximumCurrentContinuousOperation)){
			CountCurrentError++;
			if(CountCurrentError > 10){ //Only if the error is available for at least 10 cycles
		 // if(CountCurrentError > 20000){ //Only if the error is available for at least 2 seconds @100us ISR-cycle
				Global_Data.ew.maximumContinuousCurrentExceeded = valueTrue; //Current error detected -> errors are handled in the main.c
			}
		}else{
			CountCurrentError =0; //Reset Error Counter
		}

		//Detect short-time current-limit ---------------------------------------------------------------------------------------
		if ((Global_Data.av.I_U > Global_Data.mrp.motorMaximumCurrentShortTimeOperation) || (Global_Data.av.I_V > Global_Data.mrp.motorMaximumCurrentShortTimeOperation) || (Global_Data.av.I_W > Global_Data.mrp.motorMaximumCurrentShortTimeOperation)){
			ErrorHandling(&Global_Data);
			Global_Data.ew.maximumShortTermCurrentReached = valueTrue; //Current error detected -> errors are handled directly herein
		}
	}

	//Read out speed and theta angle ---------------------------------------------------------------------------------------
	Encoder_UpdateSpeedPosition(&Global_Data);

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

	// PWM status is set to 0 and disable the PWM Module
	PWM_SS_SetStatus(Global_Data.cw.enableControl);
	// Reference m u1-u3  ->  Valid value range for the duty cycle: 0-1
	PWM_SS_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
						Global_Data.rasv.halfBridge2DutyCycle,
						Global_Data.rasv.halfBridge3DutyCycle);
	// Set for three-level modulator
	PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
						Global_Data.rasv.halfBridge2DutyCycle,
						Global_Data.rasv.halfBridge3DutyCycle);
	//End: Write the references for the FPGA ---------------------------------------------------------------------------------------


	// Start JavaScope---------------------------------------------------------------------------------------
	 //In order to avoid unnecessary memory access, call only if something has changed!
	if((ControlDataShadowBare.id != ControlData.id)||(ControlDataShadowBare.value != ControlData.value)){
		//Safe the current control data into a shadow register
		ControlDataShadowBare.id = ControlData.id;
		ControlDataShadowBare.value = ControlData.value;
		ControlDataShadowBare.digInputs = ControlData.digInputs;
		//Read the control values from JavaScope
		ipc_Control_func(ControlDataShadowBare.id, ControlDataShadowBare.value, &Global_Data); //check always in while(1) if there are new control values
	}

	f_ISRLifeCheck = ((Xfloat32)i_ISRLifeCheck)*0.1; //for representation, keep the value between 0-1000

	// Store every observable signal into the Pointer-Array.
	// With the JavaScope, 4 signals can be displayed simultaneously (data stream at 200us time intervals).
	// Changing between the observable signals is possible at runtime in the JavaScope.
	js_ptr_arr[JSO_Speed_rpm]	= &Global_Data.av.mechanicalRotorSpeed;
	js_ptr_arr[JSO_ia] 			= &Global_Data.av.I_U;
	js_ptr_arr[JSO_ib] 			= &Global_Data.av.I_V;
	js_ptr_arr[JSO_ic] 			= &Global_Data.av.I_W;
	js_ptr_arr[JSO_ua] 			= &Global_Data.av.U_U;
	js_ptr_arr[JSO_ub] 			= &Global_Data.av.U_V;
	js_ptr_arr[JSO_uc] 			= &Global_Data.av.U_W;
	js_ptr_arr[JSO_iq] 			= &Global_Data.av.I_q;
	js_ptr_arr[JSO_id] 			= &Global_Data.av.I_d;
	js_ptr_arr[JSO_Theta_el] 	= &Global_Data.av.theta_elec;
	js_ptr_arr[JSO_theta_mech] 	= &Global_Data.av.theta_mech;
	js_ptr_arr[JSO_Wtemp]		= &Global_Data.pID.WindingTemp;
	js_ptr_arr[JSO_ud]			= &Global_Data.av.U_d;
	js_ptr_arr[JSO_uq]			= &Global_Data.av.U_q;
	js_ptr_arr[JSO_Ld_mH]		= &Global_Data.pID.Online_Ld;
	js_ptr_arr[JSO_Lq_mH]		= &Global_Data.pID.Online_Lq;
	js_ptr_arr[JSO_Rs_mOhm]		= &Global_Data.pID.Online_Rs;
	js_ptr_arr[JSO_PsiPM_mVs]	= &Global_Data.pID.Online_Psi_PM;
	js_ptr_arr[JSO_Sawtooth1] 	= &f_ISRLifeCheck;

	// Store slow / not-time-critical signals into the SlowData-Array.
	// Will be transferred one after another (one every 0,5 ms).
	// The array may grow arbitrarily long, the refresh rate of the individual values decreases.
	js_slowDataArray[JSSD_INT_SecondsSinceSystemStart].i = i_count_1s;
	js_slowDataArray[JSSD_FLOAT_uSecPerIsr].f 	= ((Xfloat32)time_ISR_total*10.0e-03); //AXI-Ticks* @100MHz AXI-Clock [us]
	js_slowDataArray[JSSD_FLOAT_Sine].f 		= time_ISR_max; //10.0 * sin(PI2 * 0.05 * ((Xfloat32)0.0002));	// 0.05 Hz => T=20sec
	js_slowDataArray[JSSD_FLOAT_FreqReadback].f = Global_Data.rasv.referenceFrequency;
	js_slowDataArray[JSSD_INT_Milliseconds].i 	= (Xint32)i_count_1ms;
	js_slowDataArray[JSSD_FLOAT_ADCconvFactorReadback].f = Global_Data.mrp.ADCconvFactorReadback;
	js_slowDataArray[JSSD_FLOAT_PsiPM_Offline].f= Global_Data.pID.Offline_Psi_PM;
	js_slowDataArray[JSSD_FLOAT_Lq_Offline].f 	= Global_Data.pID.Offline_Lq;
	js_slowDataArray[JSSD_FLOAT_Ld_Offline].f 	= Global_Data.pID.Offline_Ld;
	js_slowDataArray[JSSD_FLOAT_Rs_Offline].f 	= Global_Data.pID.Offline_Rs;
	js_slowDataArray[JSSD_INT_polePairs].i 		= (Xint32)Global_Data.mrp.motorPolePairNumber;
	js_slowDataArray[JSSD_FLOAT_J].f 			= Global_Data.pID.Offline_motorRotorInertia;
	js_slowDataArray[JSSD_INT_activeState].i 	= Global_Data.pID.activeState;
	js_slowDataArray[JSSD_FLOAT_J].f 			= Global_Data.pID.Offline_motorRotorInertia;
	js_slowDataArray[JSSD_FLOAT_u_d].f 			= Global_Data.av.U_d;
	js_slowDataArray[JSSD_FLOAT_u_q].f 			= Global_Data.av.U_q;
	js_slowDataArray[JSSD_FLOAT_i_d].f 			= Global_Data.av.I_d; //Global_Data.pID.ParameterID_I_d;	//
	js_slowDataArray[JSSD_FLOAT_i_q].f 			= Global_Data.av.I_q; //Global_Data.pID.ParameterID_I_q;	//
	js_slowDataArray[JSSD_FLOAT_speed].f 		= Global_Data.av.mechanicalRotorSpeed;
	js_slowDataArray[JSSD_FLOAT_torque].f 		= 1.5*Global_Data.mrp.motorPolePairNumber*(Global_Data.pID.Offline_Psi_PM*Global_Data.pID.ParameterID_I_q+(Global_Data.pID.Offline_Ld-Global_Data.pID.Offline_Lq)*Global_Data.pID.ParameterID_I_d*Global_Data.pID.ParameterID_I_q);
	js_slowDataArray[JSSD_FLOAT_encoderOffset].f= Global_Data.mrp.incrementalEncoderOffset;
	js_slowDataArray[JSSD_FLOAT_u_d_ref].f 		= Global_Data.pID.Offline_ud_ref;
	js_slowDataArray[JSSD_FLOAT_u_q_ref].f 		= Global_Data.pID.Offline_uq_ref;
	js_slowDataArray[JSSD_FLOAT_ArrayCounter].f = Global_Data.pID.array_counter;
	js_slowDataArray[JSSD_FLOAT_measArray].f 	= Global_Data.pID.Online_MessArray_Element; //OHMrichterMotorControl_Y_measArray1[(Xuint16)(Global_Data.pID.array_counter)];
	js_slowDataArray[JSSD_FLOAT_i_est].f		= Global_Data.pID.Online_i_est_Element; //OHMrichterMotorControl_Y_i_est[(Xuint16)(Global_Data.pID.array_counter)];
	js_slowDataArray[JSSD_FLOAT_ArrayControl].f = Global_Data.pID.array_counter;
	js_slowDataArray[JSSD_FLOAT_Stribtorque].f 	= Global_Data.pID.Offline_BreakawayTorque;
	js_slowDataArray[JSSD_FLOAT_Coulombtorque].f= Global_Data.pID.Offline_CoulombFriction;
	js_slowDataArray[JSSD_FLOAT_Viscotorque].f 	= Global_Data.pID.Offline_ViscousFriction;
	js_slowDataArray[JSSD_FLOAT_Rs].f 			= Global_Data.mrp.motorStatorResistance;
	js_slowDataArray[JSSD_FLOAT_PsiPM].f 		= Global_Data.mrp.motorFluxConstant;
	js_slowDataArray[JSSD_FLOAT_TrainInertia].f = Global_Data.pID.Offline_totalRotorInertia;//OHMrichterMotorControl_Y_ViscoTorqueLoad;
	js_slowDataArray[JSSD_FLOAT_LoadInertia].f 	= Global_Data.pID.Offline_loadRotorInertia;
	js_slowDataArray[JSSD_FLOAT_c_est].f		= Global_Data.pID.Offline_TwoMassSystemStiffness;
	js_slowDataArray[JSSD_FLOAT_d_est].f		= Global_Data.pID.Offline_TwoMassSystemDamping;
	js_slowDataArray[JSSD_FLOAT_c_0].f			= Global_Data.pID.Offline_TwoMassSystem_c_0;
	js_slowDataArray[JSSD_FLOAT_MapCounter].f	= Global_Data.pID.map_counter;

	if(Global_Data.pID.map_counter<401){ //400 = comes from 20x20 Raster of the flux maps
		js_slowDataArray[JSSD_FLOAT_psidMap].f	= Global_Data.pID.FluxMap_d[(Xuint16)(Global_Data.pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_psiqMap].f	= Global_Data.pID.FluxMap_q[(Xuint16)(Global_Data.pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_idMap].f	= Global_Data.pID.InvFluxMap_d[(Xuint16)(Global_Data.pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_iqMap].f	= Global_Data.pID.InvFluxMap_q[(Xuint16)(Global_Data.pID.map_counter)];
		js_slowDataArray[JSSD_FLOAT_FluxTemp].f	= Global_Data.pID.FluxTemp[(Xuint16)(Global_Data.pID.map_counter/2)];
	}
	js_slowDataArray[JSSD_FLOAT_psi_array].f	= Global_Data.pID.psi_array[(Xuint16)(Global_Data.pID.map_counter)];
	js_slowDataArray[JSSD_FLOAT_MapControl].f	= Global_Data.pID.map_counter;
	js_slowDataArray[JSSD_FLOAT_I_rated].f		= Global_Data.mrp.motorNominalCurrent;
	js_slowDataArray[JSSD_FLOAT_Wtemp].f		= Global_Data.pID.WindingTemp;
	js_slowDataArray[JSSD_FLOAT_FluxTempConst].f= Global_Data.pID.FluxTempConst;
	js_slowDataArray[JSSD_FLOAT_FluxTempError].f= Global_Data.pID.FluxTempError;
	js_slowDataArray[JSSD_FLOAT_Ld_Online].f	= Global_Data.pID.Online_Ld;
	js_slowDataArray[JSSD_FLOAT_Lq_Online].f	= Global_Data.pID.Online_Lq;
	js_slowDataArray[JSSD_FLOAT_PsiPM_Online].f	= Global_Data.pID.Online_Psi_PM;
	js_slowDataArray[JSSD_FLOAT_Rs_Online].f	= Global_Data.pID.Online_Rs;
	js_slowDataArray[JSSD_FLOAT_n_FluxPoints].f	= Global_Data.pID.n_FluxPoints;
	js_slowDataArray[JSSD_FLOAT_Ld].f 			= Global_Data.mrp.motorDirectInductance;
	js_slowDataArray[JSSD_FLOAT_Lq].f 			= Global_Data.mrp.motorQuadratureInductance;
	js_slowDataArray[JSSD_FLOAT_totalRotorInertia].f 	= Global_Data.mrp.totalRotorInertia;

	if (chJavaScope==4)
		js_fetchData4CH();
	else if (chJavaScope==2)
		js_fetchData2CH();
	// End JavaScope---------------------------------------------------------------------------------------

	//Read the timer value at the end of the ISR in order to measure the ISR-time
	time_ISR_end = XTmrCtr_GetValue(&TMR_Con_Inst,0);
	//Calculate the required ISR-time
	time_ISR_total = time_ISR_end - time_ISR_start;

	if(((Xfloat32)time_ISR_total*10.0e-03)>time_ISR_max){
			time_ISR_max=((Xfloat32)time_ISR_total*10.0e-03);
	}
	//Show end of control-ISR
	//XGpio_DiscreteWrite(&Gpio_OUT,GPIO_CHANNEL , 0b0000);  // ----
}

//==============================================================================================================================================================
//----------------------------------------------------
// Measure the time for the JavaScope
//----------------------------------------------------
int MeasureTime(){

	//measure with 1ms cycle
	if ((i_ISRLifeCheck % 10) == 1){
		i_count_1ms= i_count_1ms +1;
		if(i_count_1ms >= 2073600000) //Reset after 24 days
			i_count_1ms = 0;
	}

	//measure with 1s cycle
	if ((i_ISRLifeCheck  == 1000) == 1){
		i_count_1s = i_count_1s +1;
		if(i_count_1s >= 2073600) //Reset after 24 days
			i_count_1s = 0;
	}
return 0;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE ADC-COUNTER TIMER IN ORDER TO TRIGGER THE ADC CONVERSION
// - If connected to 10MHz clock, a count value of 25 starts an ADC conversion every 2,5us (= 400 kHz)
//----------------------------------------------------
int Initialize_Trigger_ADC_Conversion(){

	int Status = 0;

	//Write down the Counter End-Value in order to start a ADC conversion
//	Xil_Out32(ADCCounter_EndValue_REG, (Xint32)25); //Original = 100

return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR(){

	int Status = 0;

	// Initialize interrupt controller for the GIC
	Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &TMR_Con_Inst);
		if(Status != XST_SUCCESS) {
			xil_printf("RPU: Error: GIC initialization failed\r\n");
			return XST_FAILURE;
		}

	// Initialize interrupt controller for the IPI -> Initialize RPU IPI
	Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
		if(Status != XST_SUCCESS) {
			xil_printf("RPU: Error: IPI initialization failed\r\n");
			return XST_FAILURE;
		}
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
	XTmrCtr_SetHandler(&TMR_Con_Inst, TMR_Con_Intr_Handler, &TMR_Con_Inst);
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

	if(status != XST_SUCCESS) return XST_FAILURE;

	// Make the connection between the IntId of the interrupt source and the
	// associated handler that is to run when the interrupt is recognized.
		status = XScuGic_Connect(IntcInstPtr,
								INTC_Con_TIMER_INTERRUPT_ID,
								(Xil_ExceptionHandler)TMR_Con_Intr_Handler,
								(void *)Tmr_Con_InstancePtr);
		if(status != XST_SUCCESS) return XST_FAILURE;

	// Connect ADC conversion interrupt to handler
//		status = XScuGic_Connect(&INTCInst,
//								INTC_ADC_Conv_INTERRUPT_ID,
//								(Xil_ExceptionHandler)Conv_ADC_Intr_Handler,
//								(void *)Conv_ADC_InstancePtr);
//		if(status != XST_SUCCESS) return XST_FAILURE;


	// Enable GPIO and timer interrupts in the controller
	XScuGic_Enable(IntcInstPtr, INTC_Con_TIMER_INTERRUPT_ID);
	XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);
//	XScuGic_Enable(&INTCInst, INTC_ADC_Conv_INTERRUPT_ID);

	/* Enable interrupts in the processor */
	Xil_ExceptionEnable();	//Enable interrupts in the ARM

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

	// Enable IPI from RPU_0 to APU_0
	//	Xil_Out32(0xFF310018U, 0xF0000U);
	//Explanation: 0xFF310018U = XPAR_PSU_IPI_1_BASE_ADDRESS + XIPIPSU_IER_OFFSET
	//Explanation: 0xF0000U =  XPAR_PSU_IPI_3_BIT_MASK +XPAR_PSU_IPI_4_BIT_MASK + XPAR_PSU_IPI_5_BIT_MASK + XPAR_PSU_IPI_6_BIT_MASK
	//Explanation: 0xF0000U =  0x00010000U + 0x00020000U + 0x00040000U + 0x00080000U = Enable all IPI to the PMU
	XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);
	//XIpiPsu_InterruptEnable(&INTCInst_IPI, 0x00000301U); //Enable all interrupts with "0x00000301U"

	xil_printf("RPU: RPU_IpiInit: Done\r\n");
	return XST_SUCCESS;
}
