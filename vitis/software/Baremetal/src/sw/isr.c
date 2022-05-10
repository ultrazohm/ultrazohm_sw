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



//pre-loop code for 9ph model
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../IP_Cores/uz_pmsm_model_9ph/uz_pmsm_model_9ph.h"
#include "../IP_Cores/uz_pmsm_model_9ph/uz_pmsm_model_9ph_hw.h"
#include "../uz/uz_piController/uz_piController.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_Wavegen/uz_wavegen.h"
extern uz_pmsm_model_9ph_t *pmsm;
extern uz_PI_Controller *PI_d_current;
extern uz_PI_Controller *PI_q_current;
extern uz_PI_Controller *PI_rpm;
int reset_on=1;                                               //can be triggered in the expressions to reset integrators
float setp_d=0.0f;
float setp_q=2.0f;
float setp_omega=10.0f;

uz_9ph_alphabeta_t stationary_currents = {0};
uz_9ph_abc_t natural_currents = {0};
uz_3ph_alphabeta_t alpha_beta = {0};
uz_3ph_dq_t dq = {0};

struct uz_pmsm_model_9ph_outputs_general_t pmsm_outputs={
        .torque_Nm=10.0f,
        .omega_mech_1_s=0.0f,
        .theta_el=0.0f
};

struct uz_pmsm_model_9ph_outputs_dq_t pmsm_output_currents={0};

struct uz_pmsm_model_9ph_inputs_general_t pmsm_inputs={
		.load_torque=0.0f,
		.omega_mech_1_s=0.0f,
		.u_d=0.0f,
		.u_q=0.0f
};
//end

//pre-loop for PWM
#include "../uz/uz_FOC/uz_FOC.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph.h"
#include "../IP_Cores/uz_inverter_3ph/uz_inverter_3ph_hw.h"

float uz_inverter_3ph_hw_read_u_ab_ps(uint32_t base_address);

struct uz_DutyCycle_t duty_cycle_sys1 = {0};
struct uz_DutyCycle_t duty_cycle_sys2 = {0};
struct uz_DutyCycle_t duty_cycle_sys3 = {0};

uz_3ph_abc_t setpoint_abc_sys1 = {0};
uz_3ph_abc_t setpoint_abc_sys2 = {0};
uz_3ph_abc_t setpoint_abc_sys3 = {0};

uz_9ph_abc_t setpoint_natural = {0};
uz_9ph_alphabeta_t setpoint_stationary = {0};
uz_3ph_alphabeta_t setpoint_alpha_beta = {0};
uz_3ph_dq_t setpoint_dq = {0};

float V_dc_volts = 24.0f;

extern uz_PWM_SS_2L_t *pwm_instance_1;
extern uz_PWM_SS_2L_t *pwm_instance_2;
extern uz_PWM_SS_2L_t *pwm_instance_3;


struct uz_inverter_3ph_gate_ps_t gate_signal={
		.gate1=0.0f,
		.gate2=1.0f,
		.gate3=0.0f,
		.gate4=1.0f,
		.gate5=0.0f,
		.gate6=1.0f
};

extern struct uz_inverter_3ph_t *inverter_1;
extern struct uz_inverter_3ph_t *inverter_2;
extern struct uz_inverter_3ph_t *inverter_3;

struct uz_inverter_3ph_u_abc_ps_t voltage_inverter_1 = {0};
struct uz_inverter_3ph_u_abc_ps_t voltage_inverter_2 = {0};
struct uz_inverter_3ph_u_abc_ps_t voltage_inverter_3 = {0};

struct uz_inverter_3ph_i_abc_ps_t currents_inv1={
		.i_a = 0.0f,
		.i_b = 0.0f,
		.i_c = 0.0f
};


float g1=0.0f;
float g3=0.0f;
float g5=0.0f;

float amplitude = 0.05f;
float frequency_Hz = 40.0f;
float setp_factor=0.8f;
float setp_torque=0.1f;
//float g2=0.0f;
//end


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


    //++PMSM++
    // Set INputs and get Outputs
    uz_pmsm_model_9ph_trigger_input_general_strobe(pmsm);
    uz_pmsm_model_9ph_trigger_output_general_strobe(pmsm);
    uz_pmsm_model_9ph_trigger_output_currents_dq_strobe(pmsm);
    pmsm_outputs = uz_pmsm_model_9ph_get_outputs_general(pmsm);
    pmsm_output_currents = uz_pmsm_model_9ph_get_outputs_dq(pmsm);

    pmsm_inputs.omega_mech_1_s = setp_omega;
    //pmsm_inputs.load_torque = setp_torque;
    uz_pmsm_model_9ph_set_inputs_general(pmsm, pmsm_inputs);

    // Transformation to natural currents for output
    dq.d = pmsm_output_currents.i_dq.d;
    dq.q = pmsm_output_currents.i_dq.q;
    alpha_beta = uz_transformation_3ph_dq_to_alphabeta(dq,pmsm_outputs.theta_el);
    stationary_currents.alpha = alpha_beta.alpha;
    stationary_currents.beta = alpha_beta.beta;
    stationary_currents.z1 = pmsm_output_currents.i_subspaces.z1;
    stationary_currents.z2 = pmsm_output_currents.i_subspaces.z2;
    stationary_currents.x1 = pmsm_output_currents.i_subspaces.x1;
    stationary_currents.y1 = pmsm_output_currents.i_subspaces.y1;
    stationary_currents.x2 = pmsm_output_currents.i_subspaces.x2;
    stationary_currents.y2 = pmsm_output_currents.i_subspaces.y2;
    stationary_currents.z3 = pmsm_output_currents.i_subspaces.z3;
    natural_currents = uz_transformation_9ph_alphabeta_to_abc(stationary_currents);

    //++PWM++

    // Controller
    //setp_q = uz_PI_Controller_sample(PI_rpm,setp_omega,pmsm_outputs.omega_mech_1_s,false);
    setpoint_dq.d = uz_PI_Controller_sample(PI_d_current, setp_d, pmsm_output_currents.i_dq.d, false);
    setpoint_dq.q = uz_PI_Controller_sample(PI_q_current, setp_q, pmsm_output_currents.i_dq.q, false);

    //pmsm_inputs.u_d = setpoint_dq.d;
    //pmsm_inputs.u_q = setpoint_dq.q;

    // Transformation
    setpoint_alpha_beta = uz_transformation_3ph_dq_to_alphabeta(setpoint_dq,pmsm_outputs.theta_el);
    setpoint_stationary.alpha = setpoint_alpha_beta.alpha;
    setpoint_stationary.beta = setpoint_alpha_beta.beta;
    setpoint_stationary.z1 = 0.0f;
    setpoint_stationary.z2 = 0.0f;
    setpoint_stationary.x1 = 0.0f;
    setpoint_stationary.y1 = 0.0f;
    setpoint_stationary.x2 = 0.0f;
    setpoint_stationary.y2 = 0.0f;
    setpoint_stationary.z3 = 0.0f;
    setpoint_natural = uz_transformation_9ph_alphabeta_to_abc(setpoint_stationary);

    // Split Systems
    setpoint_abc_sys1.a = setpoint_natural.a1*setp_factor;
    setpoint_abc_sys1.b = setpoint_natural.b1*setp_factor;
    setpoint_abc_sys1.c = setpoint_natural.c1*setp_factor;
    //+uz_wavegen_sine(amplitude, frequency_Hz)

    setpoint_abc_sys2.a = setpoint_natural.a2;
	setpoint_abc_sys2.b = setpoint_natural.b2;
	setpoint_abc_sys2.c = setpoint_natural.c2;

	setpoint_abc_sys3.a = setpoint_natural.a3;
	setpoint_abc_sys3.b = setpoint_natural.b3;
	setpoint_abc_sys3.c = setpoint_natural.c3;

	// Duty Cycle
	duty_cycle_sys1 = uz_FOC_generate_DutyCycles(setpoint_abc_sys1,V_dc_volts);
	duty_cycle_sys2 = uz_FOC_generate_DutyCycles(setpoint_abc_sys2,V_dc_volts);
	duty_cycle_sys3 = uz_FOC_generate_DutyCycles(setpoint_abc_sys3,V_dc_volts);

	uz_PWM_SS_2L_set_duty_cycle(pwm_instance_1,duty_cycle_sys1.DutyCycle_U,duty_cycle_sys1.DutyCycle_V,duty_cycle_sys1.DutyCycle_W);
	uz_PWM_SS_2L_set_duty_cycle(pwm_instance_2,duty_cycle_sys2.DutyCycle_U,duty_cycle_sys2.DutyCycle_V,duty_cycle_sys2.DutyCycle_W);
	uz_PWM_SS_2L_set_duty_cycle(pwm_instance_3,duty_cycle_sys3.DutyCycle_U,duty_cycle_sys3.DutyCycle_V,duty_cycle_sys3.DutyCycle_W);
	//uz_PWM_SS_2L_set_duty_cycle(pwm_instance_2,0.5,0.5,0.5);
	//uz_PWM_SS_2L_set_duty_cycle(pwm_instance_3,0.5,0.5,0.5);
    //reset PMSM and PI controllers
    if(reset_on==1)
    {
          uz_PI_Controller_reset(PI_q_current);
          uz_PI_Controller_reset(PI_d_current);
          uz_pmsm_model_9ph_reset(pmsm);
    }
/*
    gate_signal.gate1=g1;
    gate_signal.gate2=!g1;

    gate_signal.gate3=g3;
	gate_signal.gate4=!g3;

	gate_signal.gate5=g5;
	gate_signal.gate6=!g5;


    uz_inverter_3ph_trigger_i_abc_ps_strobe(inverter_1);
    uz_inverter_3ph_trigger_i_abc_ps_strobe(inverter_2);
    uz_inverter_3ph_set_i_abc_ps(inverter_1,currents_inv1);
    uz_inverter_3ph_set_i_abc_ps(inverter_2,currents_inv1);

*/
    uz_inverter_3ph_trigger_u_abc_ps_strobe(inverter_1);
    uz_inverter_3ph_trigger_u_abc_ps_strobe(inverter_2);
    uz_inverter_3ph_trigger_u_abc_ps_strobe(inverter_3);

//  uz_inverter_3ph_trigger_gate_ps_strobe(inverter_1);
	uz_inverter_3ph_trigger_gate_ps_strobe(inverter_2);
//	uz_inverter_3ph_trigger_gate_ps_strobe(inverter_3);

//	uz_inverter_3ph_set_gate_ps(inverter_1,gate_signal);
	uz_inverter_3ph_set_gate_ps(inverter_2,gate_signal);
//	uz_inverter_3ph_set_gate_ps(inverter_3,gate_signal);

    //voltage_inverter_1.u_ab = uz_inverter_3ph_hw_read_u_ab_ps(0x800E0000);
	voltage_inverter_1 = uz_inverter_3ph_get_u_abc_ps(inverter_1);
    voltage_inverter_2 = uz_inverter_3ph_get_u_abc_ps(inverter_2);
    voltage_inverter_3 = uz_inverter_3ph_get_u_abc_ps(inverter_3);


    //end



    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    }
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
