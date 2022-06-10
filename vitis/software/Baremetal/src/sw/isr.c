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

// pre-loop code for 9ph model
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../IP_Cores/uz_pmsm_model_9ph_dq/uz_pmsm_model9ph_dq.h"
#include "../uz/uz_piController/uz_piController.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
extern uz_pmsm_model9ph_dq_t *pmsm;
extern uz_PI_Controller *PI_d_current;
extern uz_PI_Controller *PI_q_current;
extern uz_PI_Controller *PI_rpm;

float setp_omega = 16.6f*2.0f*M_PI;
uz_3ph_dq_t current_set_point = {
    .d = 0.0f,
    .q = 0.0f,
    .zero = 0.0f};

struct uz_pmsm_model9ph_dq_outputs_general_t pmsm_outputs = {
    .torque_Nm = 10.0f,
    .omega_mech_1_s = 0.0f,
    .theta_el = 0.0f};

uz_9ph_abc_t pmsm_output_currents = {0};

struct uz_pmsm_model9ph_dq_inputs_general_t pmsm_inputs = {
    .load_torque = 0.0f,
    .omega_mech_1_s = 0.0f};

// pre-loop for PWM
#include "../uz/uz_FOC/uz_FOC.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph_hw.h"
#include "../IP_Cores/uz_pmsm_9ph_transformation/uz_pmsm9ph_transformation.h"

struct uz_DutyCycle_t duty_cycle_sys1 = {0};
struct uz_DutyCycle_t duty_cycle_sys2 = {0};
struct uz_DutyCycle_t duty_cycle_sys3 = {0};

uz_3ph_abc_t setpoint_abc_sys1 = {0};
uz_3ph_abc_t setpoint_abc_sys2 = {0};
uz_3ph_abc_t setpoint_abc_sys3 = {0};

float V_dc_volts = 560.0f;

extern uz_PWM_SS_2L_t *pwm_instance_1;
extern uz_PWM_SS_2L_t *pwm_instance_2;
extern uz_PWM_SS_2L_t *pwm_instance_3;

extern struct uz_inverter_3ph_t *inverter_1;
extern struct uz_inverter_3ph_t *inverter_2;
extern struct uz_inverter_3ph_t *inverter_3;

struct uz_inverter_3ph_u_abc_ps_t voltage_inverter_1 = {0};
struct uz_inverter_3ph_u_abc_ps_t voltage_inverter_2 = {0};
struct uz_inverter_3ph_u_abc_ps_t voltage_inverter_3 = {0};

struct uz_inverter_3ph_i_abc_ps_t currents_inv1 = {
    .i_a = 0.0f,
    .i_b = 0.0f,
    .i_c = 0.0f};

extern uz_pmsm9ph_transformation_t *transformation_9ph;

uz_9ph_abc_t actual_currents_abc = {0};
uz_9ph_dq_t actual_currents_dq = {0};

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
#include "../uz/uz_fixedpoint/uz_fixedpoint.h"
struct uz_fixedpoint_definition_t fixed_out = {
    .is_signed = true,
    .fractional_bits = 18,
    .integer_bits = (27 - 18)};

enum controller_state_t
{
    closed_loop_inverter = 0,
    closed_loop_dgl_only
};
enum controller_state_t controller_state = closed_loop_inverter;
uz_9ph_dq_t output_voltage_dq = {0};
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);
    platform_state_t current_state = ultrazohm_state_machine_get_state();
    if (current_state == control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

        switch (controller_state)
        {
        case closed_loop_inverter:
            uz_pmsm_model9ph_dq_set_use_axi_input(pmsm,false);

            pmsm_outputs = uz_pmsm_model9ph_dq_get_outputs_general(pmsm);
            pmsm_inputs.omega_mech_1_s = setp_omega;
            uz_pmsm_model9ph_dq_set_inputs_general(pmsm, pmsm_inputs);

            actual_currents_abc = uz_pmsm9ph_transformation_get_currents(transformation_9ph);

            actual_currents_dq = uz_transformation_9ph_abc_to_dq(actual_currents_abc, pmsm_outputs.theta_el);

            output_voltage_dq.d = uz_PI_Controller_sample(PI_d_current, current_set_point.d, actual_currents_dq.d, false); // outputs_dq.d
            output_voltage_dq.q = uz_PI_Controller_sample(PI_q_current, current_set_point.q, actual_currents_dq.q, false); // outputs_dq.q
            uz_9ph_abc_t output_voltage_abc = uz_transformation_9ph_dq_to_abc(output_voltage_dq, pmsm_outputs.theta_el);

            setpoint_abc_sys1.a = output_voltage_abc.a1;
            setpoint_abc_sys1.b = output_voltage_abc.b1;
            setpoint_abc_sys1.c = output_voltage_abc.c1;
            setpoint_abc_sys2.a = output_voltage_abc.a2;
            setpoint_abc_sys2.b = output_voltage_abc.b2;
            setpoint_abc_sys2.c = output_voltage_abc.c2;
            setpoint_abc_sys3.a = output_voltage_abc.a3;
            setpoint_abc_sys3.b = output_voltage_abc.b3;
            setpoint_abc_sys3.c = output_voltage_abc.c3;
            duty_cycle_sys1 = uz_FOC_generate_DutyCycles(setpoint_abc_sys1, V_dc_volts);
            duty_cycle_sys2 = uz_FOC_generate_DutyCycles(setpoint_abc_sys2, V_dc_volts);
            duty_cycle_sys3 = uz_FOC_generate_DutyCycles(setpoint_abc_sys3, V_dc_volts);
            break;
        case closed_loop_dgl_only:
        	uz_pmsm_model9ph_dq_set_use_axi_input(pmsm,true);
            pmsm_outputs = uz_pmsm_model9ph_dq_get_outputs_general(pmsm);
            pmsm_inputs.omega_mech_1_s = setp_omega;
            uz_pmsm_model9ph_dq_set_inputs_general(pmsm, pmsm_inputs);


            actual_currents_abc = uz_pmsm9ph_transformation_get_currents(transformation_9ph);
            
            actual_currents_dq=uz_pmsm_model9ph_dq_get_output_currents(pmsm);
            output_voltage_dq.d = uz_PI_Controller_sample(PI_d_current, current_set_point.d, actual_currents_dq.d, false); // outputs_dq.d
            output_voltage_dq.q = uz_PI_Controller_sample(PI_q_current, current_set_point.q, actual_currents_dq.q, false); // outputs_dq.q
            uz_pmsm_model9ph_dq_set_voltage(pmsm,output_voltage_dq);
            break;
        default:
            break;
        }
    }
    else
    {
        uz_PI_Controller_reset(PI_q_current);
        uz_PI_Controller_reset(PI_d_current);
        uz_pmsm_model9ph_dq_reset(pmsm);
        duty_cycle_sys1.DutyCycle_U = 0.0f;
        duty_cycle_sys1.DutyCycle_V = 0.0f;
        duty_cycle_sys1.DutyCycle_W = 0.0f;
        duty_cycle_sys2.DutyCycle_U = 0.0f;
        duty_cycle_sys2.DutyCycle_V = 0.0f;
        duty_cycle_sys2.DutyCycle_W = 0.0f;
        duty_cycle_sys3.DutyCycle_U = 0.0f;
        duty_cycle_sys3.DutyCycle_V = 0.0f;
        duty_cycle_sys3.DutyCycle_W = 0.0f;
    }
    // Duty Cycle
    uz_PWM_SS_2L_set_duty_cycle(pwm_instance_1, duty_cycle_sys1.DutyCycle_U, duty_cycle_sys1.DutyCycle_V, duty_cycle_sys1.DutyCycle_W);
    uz_PWM_SS_2L_set_duty_cycle(pwm_instance_2, duty_cycle_sys2.DutyCycle_U, duty_cycle_sys2.DutyCycle_V, duty_cycle_sys2.DutyCycle_W);
    uz_PWM_SS_2L_set_duty_cycle(pwm_instance_3, duty_cycle_sys3.DutyCycle_U, duty_cycle_sys3.DutyCycle_V, duty_cycle_sys3.DutyCycle_W);

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
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
    // uz_mux_axi_enable(Global_Data.objects.mux_axi);

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
