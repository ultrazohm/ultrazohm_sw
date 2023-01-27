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
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../include/encoder.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include <complex.h>
#include "../uz/uz_signals/uz_signals.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;
// Add extern uz_codegen codegenInstance to Baremtal/sw/isr.c to use the global inside the ISR
extern uz_codegen codegenInstance;
float time_current_ramp; // in s
float current_ramp_duration;





//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static void CheckForErrors();
static void CalcCompensatingHarmonics();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);
    platform_state_t current_state=ultrazohm_state_machine_get_state();
    //----------------------------------------------------
    CheckForErrors();
    //----------------------------------------------------
    // write values for control
    // LR
    // Actual Values
    // currents
    codegenInstance.input.Act_Iu =(Global_Data.aa.A2.me.ADC_A1-2.5) * 80.0F/4.0F - 0.15F;		//A * 80.0F/4.0F
    codegenInstance.input.Act_Iv =(Global_Data.aa.A2.me.ADC_A2-2.5) * 80.0F/4.0F - 0.50F;		//A * 80.0F/4.0F
   	codegenInstance.input.Act_Iw =(Global_Data.aa.A2.me.ADC_A3-2.5) * 80.0F/4.0F - 0.20F;		//A * 80.0F/4.0F
   	Global_Data.av.mechanicalTorque=-(Global_Data.aa.A2.me.ADC_B5) * 20.0F; // Kistler torque shaft + voltage divider (1/2) -> 5 V equal 100 Nm
   	// Torque low pass filter
   	static float torque_lpf_mem_in = 0.0f;
   	static float torque_lpf_mem_out = 0.0f;
   	Global_Data.av.mechanicalTorqueObserved = LPF1(Global_Data.av.mechanicalTorque,&torque_lpf_mem_in, &torque_lpf_mem_out,Global_Data.av.pwm_frequency_hz, Global_Data.vLR.torque_LPF_frequ);
   	// dc-link voltage
   	codegenInstance.input.Act_U_ZK = Global_Data.aa.A2.me.ADC_A4 * 12.5F;			//V
   	// mechanical values
   	codegenInstance.input.Act_n = Global_Data.av.mechanicalRotorSpeed; 				//[RPM]
   	codegenInstance.input.Act_w_el = (Global_Data.av.mechanicalRotorSpeed/60.0F)*2.0F*M_PI*rtP.p; // rad/s
    codegenInstance.input.Act_theta_u_el = fmodf( (Global_Data.av.theta_elec) *(float)rtP.p + (Global_Data.av.theta_offset),2.0F*M_PI) ;
   	// reference values
    Global_Data.vLR.I_U_ref=codegenInstance.output.Iu_ref;
    Global_Data.vLR.I_V_ref=codegenInstance.output.Iv_ref;
    Global_Data.vLR.I_W_ref=codegenInstance.output.Iw_ref;
    //
	// Global_Data.vLR
	Global_Data.vLR.status_control=codegenInstance.input.fl_power*100+codegenInstance.input.fl_enable_compensation_current*10+codegenInstance.input.fl_enable_compensation_cogging_;
	//----------------------------------------------------
	// calculate load depend harmonics for cogging torque compensation
	if ((codegenInstance.input.Ref_I_im_ext_mit != Global_Data.vLR.set_imag_current_old) || (codegenInstance.input.fl_enable_compensation_cogging_ != Global_Data.vLR.fl_enable_compensation_cogging_old))
	{ 	// calculate new harmonics with every new reference imag current or enabled cogging torque compensation
	CalcCompensatingHarmonics();
	// set actuel current values to "old" values
	Global_Data.vLR.set_imag_current_old = codegenInstance.input.Ref_I_im_ext_mit;
	Global_Data.vLR.set_real_current_old = codegenInstance.input.Ref_I_re_ext_mit;
	Global_Data.vLR.fl_enable_compensation_cogging_old = codegenInstance.input.fl_enable_compensation_cogging_;
	}
	//
	//----------------------------------------------------
	if (current_state==control_state)
    {
		//----------------------------------------------------
		// second harmonic - parameter identification - DEBUG ONLY!
		//codegenInstance.input.ordnung_a = 2.0;
		//codegenInstance.input.amplitude_a = Global_Data.vLR.ampl_work;
		//codegenInstance.input.phase_a = Global_Data.vLR.phase_work;
		//----------------------------------------------------
		if(codegenInstance.input.Act_w_el == 0.0F){codegenInstance.input.Act_w_el=0.00001F;}
    	// Start: Control algorithm - only if ultrazohm is in control state
    	// Control for TFM with asymmetric phase shift (LR)
		uz_codegen_step(&codegenInstance);
		// duty cycle limitation (LR)
		codegenInstance.output.a_U = uz_signals_saturation(codegenInstance.output.a_U,1.0,0.0);
		codegenInstance.output.a_V = uz_signals_saturation(codegenInstance.output.a_V,1.0,0.0);
		codegenInstance.output.a_W = uz_signals_saturation(codegenInstance.output.a_W,1.0,0.0);
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5,false,false,false);
    	}
		else{
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5,true,true,true);
    	}

	//----------------------------------------------------
	// assign duty cycle to PWM-Module
	//
	Global_Data.rasv.halfBridge1DutyCycle = codegenInstance.output.a_U;
	Global_Data.rasv.halfBridge2DutyCycle = codegenInstance.output.a_V;
	Global_Data.rasv.halfBridge3DutyCycle = codegenInstance.output.a_W;

	//
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);
    //
    // Set duty cycles for three-level modulator
    //PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
     //                   Global_Data.rasv.halfBridge2DutyCycle,
      //                  Global_Data.rasv.halfBridge3DutyCycle);
	//
	//----------------------------------------------------
    //
    // assign JavaScope variables
    Global_Data.av.I_U = codegenInstance.input.Act_Iu;
    Global_Data.av.I_V = codegenInstance.input.Act_Iv;
    Global_Data.av.I_W = codegenInstance.input.Act_Iw;
    Global_Data.av.I_q = codegenInstance.output.I_im_Ref;
    Global_Data.av.I_d = codegenInstance.output.I_re_Ref;
    Global_Data.av.a_u = codegenInstance.output.a_U;
    Global_Data.av.a_v = codegenInstance.output.a_V;
    Global_Data.av.a_w = codegenInstance.output.a_W;
    Global_Data.av.U_ZK = codegenInstance.input.Act_U_ZK;
    Global_Data.av.theta_elec_LR = codegenInstance.input.Act_theta_u_el;
    //
    JavaScope_update(&Global_Data);
	//
	//----------------------------------------------------
	// assign actual values to old values (LR)
	Global_Data.vLR.theta_el_old = codegenInstance.input.Act_theta_u_el;
	Global_Data.vLR.theta_mech_old = Global_Data.av.theta_elec;
	Global_Data.vLR.n_period_mech_old = Global_Data.vLR.n_period_mech;
	//----------------------------------------------------
	//
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &Timer_Interrupt);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable uz_mux_axi for triggering the ADCs and the ISR
//    uz_mux_axi_hw_enable_IP_core(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR);
//    uz_mux_axi_hw_set_mux(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
//    uz_mux_axi_hw_set_n_th_interrupt(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
    //uz_mux_axi_enable(Global_Data.objects.mux_axi);

    //----------------------------------------------------
    // LR
    // Initialize flags for control the TFM
	//Set Flags and referenceValues of FOC to zero (unit8_T)
	codegenInstance.input.fl_power = 0U; // 0 no phase is controlled; 1 only phase one gets controlled; 2 only phase 1 and 2 getting controlled; 3 all trhee phases getting controlled
	codegenInstance.input.fl_control_type = 0U; // 0 current control; 1 speed control
	codegenInstance.input.fl_integrator_reset = 0U; //
	codegenInstance.input.fl_field_weakening = 1U; // 1 simple field weakening
	codegenInstance.input.fl_voltage_limitation = 2U; // in field weakening: 1 prio U_d; 2 Quang
	codegenInstance.input.fl_decoupling = 1U;
	codegenInstance.input.fl_angle_prediction = 0U;
	codegenInstance.input.fl_enable_compensation_current = 0U;  // 1 enables the compensation of the asymmetriy
	codegenInstance.input.fl_enable_compensation_cogging_ = 0U; // 1 enables the compensation of the cogging torque
	codegenInstance.input.fl_compensat_CT_current= 1U; // 1 the cogging torque compensation gets through the compensation of the asymmetry; 0 direct cogging torque compensation
	codegenInstance.input.fl_lookup_table= 0U; // 1 use lookup tables for sin/cos; 0: use sin/cos function
	// Initialize reference values (real32_T)
	codegenInstance.input.Ref_n = 0.0F;
	codegenInstance.input.Ref_I_re_ext_mit = 0.0F;
	codegenInstance.input.Ref_I_im_ext_mit = 0.0F;
	// Initialize cogging torque compensation values (real32_T)
	codegenInstance.input.amplitude_a = 0.0F; // amplitude of the first compensated harmonic
	codegenInstance.input.ordnung_a = 0.0F; // order of the first compensated harmonic
	codegenInstance.input.phase_a = 0.0F;// phase of the first compensated harmonic
	codegenInstance.input.amplitude_b = 0.0F;
	codegenInstance.input.ordnung_b = 0.0F;
	codegenInstance.input.phase_b = 0.0F;
	codegenInstance.input.amplitude_c = 0.0F;
	codegenInstance.input.ordnung_c = 0.0F;
	codegenInstance.input.phase_c = 0.0F;
	codegenInstance.input.amplitude_d = 0.0F;
	codegenInstance.input.ordnung_d = 0.0F;
	codegenInstance.input.phase_d = 0.0F;
	// Initialize parameters of the asymmetry (for compensation, creal32_T)
	codegenInstance.input.Psi_PM_U.re = +0.0167226F; //value 15n_1n -> +0.01691371537745F;//0.0185800F; // real part of flux linkage of phase U as complex number (amplitude * exp(phase angle U))
	codegenInstance.input.Psi_PM_U.im = +0.0000000F; //value 15n_1n -> +0.000000000000000F; // imaginary part of flux linkage of phase U as complex number (amplitude * exp(phase angle U))
	codegenInstance.input.Psi_PM_V.re = -0.0112042F; //value 15n_1n -> -0.012530035337452F;//-0.0131380F; // real part of flux linkage of phase V as complex number (amplitude * exp(phase angle V))
	codegenInstance.input.Psi_PM_V.im = -0.0147213F; //value 15n_1n -> -0.012340872957559F;//-0.0131380F; // imaginary part of flux linkage of phase V as complex number (amplitude * exp(phase angle V))
	codegenInstance.input.Psi_PM_W.re = -0.0061064F; //value 15n_1n -> -0.007978636850798F;//-0.0091492F; // real part of flux linkage of phase W as complex number (amplitude * exp(phase angle W))
	codegenInstance.input.Psi_PM_W.im = +0.0147373F; //value 15n_1n -> 0.014430547280038F;//0.0161712F; // imaginary part of flux linkage of phase W as complex number (amplitude * exp(phase angle W))
	//
	// Reference values
	codegenInstance.input.Ref_n = 0.0F; //Global_Data.rasv.referenceSpeed;
	codegenInstance.input.Ref_I_re_ext_mit = 0.0F; // Global_Data.rasv.referenceCurrent_id;
	codegenInstance.input.Ref_I_im_ext_mit = 0.0F; //Global_Data.rasv.referenceCurrent_iq;
	//
	time_current_ramp = 0.0; // Initial time for current ramp
	current_ramp_duration = 2.0; // time for a current value in sec.
	Global_Data.vLR.torque_LPF_frequ = 1000.0f;
	//
    //----------------------------------------------------
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
int Initialize_Timer()
{

    int Status;

    // SETUP THE TIMER 1 for Interrupts
    Status = XTmrCtr_Initialize(&Timer_Interrupt, XPAR_UZ_SYSTEM_INTERRUPT_TRIGGER_F_CC_DEVICE_ID);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;
    // XTmrCtr_SetHandler(&Timer_Interrupt, ISR_Control, &Timer_Interrupt);
    XTmrCtr_SetOptions(&Timer_Interrupt, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
    XTmrCtr_SetResetValue(&Timer_Interrupt, 0, TIMER_LOAD_VALUE);
    XTmrCtr_Reset(&Timer_Interrupt, 0);
    XTmrCtr_Start(&Timer_Interrupt, 0);

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
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntcInstPtr);

    /* Enable interrupts in the processor */
    Xil_ExceptionEnable(); // Enable interrupts in the ARM

    // setting interrupt trigger sensitivity
    // b01	Active HIGH level sensitive
    // b11 	Rising edge sensitive
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(IntcInstPtr, Interrupt_ISR_ID, 0x0, 0b11); // rising-edge
    // XScuGic_SetPriorityTriggerType(&INTCInst, Interrupt_ISR_ID, 0x0, 0b01); // active-high - default case

    // Make the connection between the IntId of the interrupt source and the
    // associated handler that is to run when the interrupt is recognized.
    status = XScuGic_Connect(IntcInstPtr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             (void *)IntcInstPtr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Enable GPIO and timer interrupts in the controller
    XScuGic_Enable(IntcInstPtr, Interrupt_ISR_ID);
    XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);

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
    if (IntcConfig_IPI == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&INTCInst_IPI, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: RPU_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};

static void CheckForErrors()
{
	// over current (fast, peak)
	if (codegenInstance.output.fault_peak_current_u==1)
	{
	ultrazohm_state_machine_set_error(true);
	Global_Data.vLR.error_code_LR=101;
	}
	if (codegenInstance.output.fault_peak_current_v==1)
	{
	ultrazohm_state_machine_set_error(true);
	Global_Data.vLR.error_code_LR=102;
	}
	if (codegenInstance.output.fault_peak_current_w==1)
	{
	ultrazohm_state_machine_set_error(true);
	Global_Data.vLR.error_code_LR=103;
	}
	// over current (slow, rms)
	if (codegenInstance.output.fault_rms_current_u==1)
	{
	ultrazohm_state_machine_set_error(true);
	Global_Data.vLR.error_code_LR=111;
	}
	if (codegenInstance.output.fault_rms_current_v==1)
	{
	ultrazohm_state_machine_set_error(true);
	Global_Data.vLR.error_code_LR=112;
	}
	if (codegenInstance.output.fault_rms_current_w==1)
	{
	ultrazohm_state_machine_set_error(true);
	Global_Data.vLR.error_code_LR=113;
	}
	// speed limit
	//if (codegenInstance.output.fault_peak_speed==1)
	//{
	//ultrazohm_state_machine_set_error(true);
	//Global_Data.vLR.error_code_LR=201;
	//}
	//if (codegenInstance.output.fault_max_speed==1)
	//{
	//ultrazohm_state_machine_set_error(true);
	//Global_Data.vLR.error_code_LR=202;
	//}
	//if (codegenInstance.output.error_speed_limit==1)
	//{
	//ultrazohm_state_machine_set_error(true);
	//Global_Data.vLR.error_code_LR=203;
	//}
};
//
static void CalcCompensatingHarmonics()
{
	// Calculation of the harmonics for the cogging torque compensation
	//
	//
	//
	float factor_torque_constant = -1/((Global_Data.vLR.ke_idle * Global_Data.vLR.fkt_ke_asym)+ (0.3859*expf(-0.2403 * codegenInstance.input.Ref_I_im_ext_mit)+0.05417*expf(-0.01041 * codegenInstance.input.Ref_I_im_ext_mit)));
	//
	//----------------------------------------------------
	// second harmonic -> harmonic_a
	codegenInstance.input.ordnung_a = 2.0F;// TFM_config_15n_1n value ->2.0;
	codegenInstance.input.amplitude_a = 1.68F;// TFM_config_15n_1n value ->-2.4F;//factor_torque_constant*1.08;
	codegenInstance.input.phase_a = 4.825F;// TFM_config_15n_1n value ->0.45F;//(0.005818*codegenInstance.input.Ref_I_im_ext_mit +  0.828908    -0.3352); // load depend phase for cogging torque compensation
	//
	//----------------------------------------------------
	// fourth harmonic -> harmonic_b
	codegenInstance.input.ordnung_b= 4.0F;// TFM_config_15n_1n value ->4.0F;//4.0F;
	codegenInstance.input.amplitude_b = 0.685F;// TFM_config_15n_1n value ->-0.63f;//factor_torque_constant *0.4F;
	codegenInstance.input.phase_b = 1.8F;// TFM_config_15n_1n value ->5.2F;//-0.2F;
	//
	//----------------------------------------------------
	// sixth harmonic -> harmonic_c
	codegenInstance.input.ordnung_c = 6.0F;// TFM_config_15n_1n value ->6.0;//6.0F;
	codegenInstance.input.amplitude_c = 0.3316F;// TFM_config_15n_1n value ->-0.25;//factor_torque_constant *(0.0018*powf(codegenInstance.input.Ref_I_im_ext_mit,2)+0.0034*codegenInstance.input.Ref_I_im_ext_mit+0.1674);
	codegenInstance.input.phase_c = 3.0F;//-1.05F;// TFM_config_15n_1n value -> 5.95;//-0.0308*codegenInstance.input.Ref_I_im_ext_mit+0.932;
	//
	//
	codegenInstance.input.ordnung_d = 0.0F;
	codegenInstance.input.amplitude_d =  0.0F;
	codegenInstance.input.phase_d =  0.0F;//
	//
	return codegenInstance;
}

