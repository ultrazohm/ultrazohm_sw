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
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_math_constants.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

// Variables for Current Control


// Conversion factors for current and voltage
#define PHASE_CURRENT_CONV_U				36.75
#define PHASE_CURRENT_CONV_V				36.75
#define PHASE_CURRENT_CONV_W				36.75

#define MAX_PHASE_CURRENT					45.0f
#define MAX_MECHANICAL_RPM					400.0f
#define MIN_MECHANICAL_RPM					-10.0f

//#define PHASE_VOLT_CONV						1.0f
//#define DC_VOLT_CONV						240
//#define DC_VOLT_OFFSET						240

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
//    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    // get measured rotor position from resolver
    Global_Data.av.resolver_d4_0 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interf_d4_0);
//    Global_Data.av.resolver_d4_1 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interf_d4_1);
//    Global_Data.av.resolver_d4_2 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interf_d4_2);

    // assign electrical/mechanical rotor angle in rad to Global_Data and the mechanical rotational speed in rpm
    Global_Data.av.angle_mech_rad = 2.0f*UZ_PIf - Global_Data.av.resolver_d4_0.position_mech_2pi;
    Global_Data.av.angle_el_rad = 2.0f*UZ_PIf - Global_Data.av.resolver_d4_0.position_el_2pi;
    Global_Data.av.mechanicalRotorSpeed = -1.0f*Global_Data.av.resolver_d4_0.n_mech_rpm;
    Global_Data.av.electricalRotorSpeed = -1.0f*Global_Data.av.resolver_d4_0.omega_mech_rad_s*5.0f;

    // get measured currents from ADCs
    Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV_U;
    Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_CURRENT_CONV_V;
    Global_Data.av.i_c1 = -1.0f * Global_Data.aa.A1.me.ADC_B6 * PHASE_CURRENT_CONV_W;

    Global_Data.av.i_a1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_a1, Global_Data.av.i_a1);
    Global_Data.av.i_b1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_b1, Global_Data.av.i_b1);
    Global_Data.av.i_c1_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_c1, Global_Data.av.i_c1);

    // check for current limit violation
    if (fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT)
        {
        	ultrazohm_state_machine_set_stop(true);
        }
    // check for dc-link voltage limit violation
    //dc voltag is not measured at the moment -> no check for overvoltage

    // check for speed limit violation
    if (Global_Data.av.mechanicalRotorSpeed > MAX_MECHANICAL_RPM || Global_Data.av.mechanicalRotorSpeed < MIN_MECHANICAL_RPM)
    {
    	ultrazohm_state_machine_set_stop(true);
    }


    // assign phase currents to struct
    Global_Data.av.i_phase.a = Global_Data.av.i_a1_filt;
    Global_Data.av.i_phase.b = Global_Data.av.i_b1_filt;
    Global_Data.av.i_phase.c = Global_Data.av.i_c1_filt;
    // Transform phase currents into rotating dq-frame
    Global_Data.av.i_dq = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_phase, Global_Data.av.angle_el_rad);




    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==idle_state)
    {
    	// Reset controller and set all dutycycles to 0.5
    	uz_CurrentControl_reset(Global_Data.objects.CurrentControl);
    	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.5f;

    }


    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    	Global_Data.av.v_dq_ref = uz_CurrentControl_sample(Global_Data.objects.CurrentControl, Global_Data.av.i_dq_ref, Global_Data.av.i_dq, Global_Data.av.v_dc, Global_Data.av.electricalRotorSpeed);
    	Global_Data.av.dutycyc_svm_ref = uz_Space_Vector_Modulation(Global_Data.av.v_dq_ref, Global_Data.av.v_dc, Global_Data.av.angle_el_rad + (Global_Data.av.angle_lead_factor*Global_Data.av.electricalRotorSpeed*UZ_TIME_ISR));

    	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.dutycyc_svm_ref.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.dutycyc_svm_ref.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.dutycyc_svm_ref.DutyCycle_C;
    }


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
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG);
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
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId)
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
