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

#include "../include/uz_CIL_6ph.h"
extern uz_CIL_objects_t cil_objects;

// Data for PMSM
float omega_mech = 100.0f;
float load_torque = 0.0f;
struct uz_pmsm_model6ph_dq_outputs_general_t pmsm_output = {0};

// Data for Transformation
uz_6ph_abc_t transformation_currents_abc = {0};
float theta_el = 0.0f;

// Data for PI
#include "../uz/uz_piController/uz_piController.h"
extern uz_PI_Controller *PI_d_current;
extern uz_PI_Controller *PI_q_current;
uz_6ph_dq_t transformed_currents = {0};
uz_3ph_dq_t setp_currents = {0};
uz_6ph_dq_t output_voltage_dq = {0};
uz_6ph_abc_t out_voltage_abc = {0};
uz_3ph_abc_t out_voltage_abc1 = {0};
uz_3ph_abc_t out_voltage_abc2 = {0};

// Data for PWM
#include "../uz/uz_FOC/uz_FOC.h"
float V_dc_volts = 500.0f;
struct uz_DutyCycle_t duty_cycle_sys1 = {0};
struct uz_DutyCycle_t duty_cycle_sys2 = {0};

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Global variable structure
extern DS_Data Global_Data;


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

    // CIL
    uz_pmsm_model6ph_dq_set_inputs_general(cil_objects.cil_pmsm,omega_mech,load_torque);
    pmsm_output = uz_pmsm_model6ph_dq_get_outputs_general(cil_objects.cil_pmsm);
    transformation_currents_abc = uz_pmsm6ph_transformation_get_currents(cil_objects.cil_transformation);
    theta_el = uz_pmsm6ph_transformation_get_theta_el(cil_objects.cil_transformation);

    // Controller
    transformed_currents = uz_transformation_asym30deg_6ph_abc_to_dq(transformation_currents_abc, theta_el);
    output_voltage_dq.d = uz_PI_Controller_sample(PI_d_current, setp_currents.d, transformed_currents.d, false);
    output_voltage_dq.q = uz_PI_Controller_sample(PI_q_current, setp_currents.q, transformed_currents.q, false);
    out_voltage_abc = uz_transformation_asym30deg_6ph_dq_to_abc(output_voltage_dq, theta_el);
    out_voltage_abc1.a = out_voltage_abc.a1;
    out_voltage_abc1.b = out_voltage_abc.b1;
    out_voltage_abc1.c = out_voltage_abc.c1;
    out_voltage_abc2.a = out_voltage_abc.a2;
    out_voltage_abc2.b = out_voltage_abc.b2;
    out_voltage_abc2.c = out_voltage_abc.c2;

    // Duty Cycles
    duty_cycle_sys1 = uz_FOC_generate_DutyCycles(out_voltage_abc1, V_dc_volts);
    duty_cycle_sys2 = uz_FOC_generate_DutyCycles(out_voltage_abc2, V_dc_volts);
    uz_PWM_SS_2L_set_duty_cycle(cil_objects.cil_pwm1, duty_cycle_sys1.DutyCycle_U, duty_cycle_sys1.DutyCycle_V, duty_cycle_sys1.DutyCycle_W);
    uz_PWM_SS_2L_set_duty_cycle(cil_objects.cil_pwm2, duty_cycle_sys2.DutyCycle_U, duty_cycle_sys2.DutyCycle_V, duty_cycle_sys2.DutyCycle_W);




    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
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
