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

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;
// Add extern uz_codegen codegenInstance to Baremtal/sw/isr.c to use the global inside the ISR
extern uz_codegen codegenInstance;



//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    platform_state_t current_state=ultrazohm_state_machine_get_state();


    //----------------------------------------------------
    // write values for control
    // LR
    // Actual Values
    // currents
	codegenInstance.input.Act_Iu = (Global_Data.aa.A2.me.ADC_A1-2.5) * 80.0F/4.0F - 0.20F;		//A
	codegenInstance.input.Act_Iv = (Global_Data.aa.A2.me.ADC_A2-2.5) * 80.0F/4.0F + 0.15F;		//A
	codegenInstance.input.Act_Iw = (Global_Data.aa.A2.me.ADC_A3-2.5) * 80.0F/4.0F - 0.15F;		//A
	// dc-link voltage
	codegenInstance.input.Act_U_ZK = Global_Data.aa.A2.me.ADC_A4 * 12.5F;			//V
	// mechanical values
	codegenInstance.input.Act_n = Global_Data.av.mechanicalRotorSpeed; 				//[RPM]
	codegenInstance.input.Act_w_el = 0.0F; //codegenInstance.input.Act_n * Global_Data.mrp.motorPolePairNumber*M_PI/30.0F; //[rad/s]
	codegenInstance.input.Act_theta_u_el = 0.0F; //Global_Data.av.theta_elec + Global_Data.mrp.incrementalEncoderOffset; 	//[rad] Definition in main.c
	//
	// Reference values
	codegenInstance.input.Ref_n = 0.0F; //Global_Data.rasv.referenceSpeed;
	codegenInstance.input.Ref_I_re_ext_mit = 0.0F; // Global_Data.rasv.referenceCurrent_id;
	codegenInstance.input.Ref_I_im_ext_mit = 0.0F; //Global_Data.rasv.referenceCurrent_iq;
    //
	//----------------------------------------------------

    if (current_state==control_state)
    {
    	// Start: Control algorithm - only if ultrazohm is in control state
    	// Control for TFM with asymetric phase shift (LR)
		uz_codegen_step(&codegenInstance);
    }
    //ultrazohm_state_machine_set_error(codegenInstance.output.fault_peak_current_u);


    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
                        Global_Data.rasv.halfBridge2DutyCycle,
                        Global_Data.rasv.halfBridge3DutyCycle);
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
	codegenInstance.input.fl_angle_prediction = 1U;
	codegenInstance.input.fl_enable_compensation_current = 0U;  // 1 enables the compensation of the asymmetriy
	codegenInstance.input.fl_enable_compensation_cogging_ = 0U; // 1 enables the compensation of the cogging torque
	codegenInstance.input.fl_compensat_CT_current= 1U; // 1 the cogging torque compensation gets through the compensation of the asymmetry; 0 direct cogging torque compensation
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
	// Initialize parameters of the asymmetrie (for compensation, creal32_T)
	codegenInstance.input.Psi_PM_U.re = 0.0F; // real part of flux linkage of phase U as complex number (amplitude * exp(phase angle U))
	codegenInstance.input.Psi_PM_U.im = 0.0F; // imaginary part of flux linkage of phase U as complex number (amplitude * exp(phase angle U))
	codegenInstance.input.Psi_PM_V.re = 0.0F; // real part of flux linkage of phase V as complex number (amplitude * exp(phase angle V))
	codegenInstance.input.Psi_PM_V.im = 0.0F; // imaginary part of flux linkage of phase V as complex number (amplitude * exp(phase angle V))
	codegenInstance.input.Psi_PM_W.re = 0.0F; // real part of flux linkage of phase W as complex number (amplitude * exp(phase angle W))
	codegenInstance.input.Psi_PM_W.im = 0.0F; // imaginary part of flux linkage of phase W as complex number (amplitude * exp(phase angle W))
	//
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


