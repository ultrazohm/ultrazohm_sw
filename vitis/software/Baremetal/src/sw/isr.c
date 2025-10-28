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
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_CurrentControl/uz_space_vector_limitation.h"
#include "../uz/uz_signals/uz_signals.h"
// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

//defines and limits
#define		MAX_CURRENT_AMP		  15.0f
#define		MAX_SPEED 			3200.0f
#define		MAX_DC_LINK_VOLTAGE  350.0f
#define		MAX_TORQUE			  9.0f

// measurement structs for motor control
struct uz_3ph_abc_t i_abc_left = {0.0f};
struct uz_3ph_abc_t i_abc_right = {0.0f};
struct uz_3ph_dq_t i_dq_left = {0.0f};
struct uz_3ph_dq_t i_dq_right = {0.0f};
struct uz_3ph_dq_t i_dq_ref_right = {0.0f};
struct uz_3ph_dq_t v_dq_ref_left = {0.0f};
struct uz_3ph_dq_t v_dq_ref_right = {0.0f};
struct uz_DutyCycle_t dutycyc_left = {0.0f};
struct uz_DutyCycle_t dutycyc_right = {0.0f};
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static void control_left_motor();
static void control_right_motor();
static void measured_to_si_values();
static void check_constraints_current_voltage_temperature();
static inline float wrap_2pi(float x);

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    // update and calculate measured values
    measured_to_si_values();
    // check for physical and safety limits
    check_constraints_current_voltage_temperature();

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    // if "STOP"
    if (current_state==idle_state)
    {
    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_left);
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_right);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_left);

		Global_Data.rasv.n_ref_left = 0.0f;
		Global_Data.rasv.n_ref_left_filt = 0.0f;
		Global_Data.rasv.M_ref_left = 0.0f;
		Global_Data.rasv.i_dq_ref_left.d = 0.0f;
		Global_Data.rasv.i_dq_ref_left.q = 0.0f;
		Global_Data.rasv.i_dq_ref_right.d = 0.0f;
		Global_Data.rasv.i_dq_ref_right.q = 0.0f;
		uz_signals_IIR_Filter_reset(Global_Data.objects.iir_filter_ref_speed_left);
		uz_signals_IIR_Filter_reset(Global_Data.objects.iir_filter_torque);
    	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge4DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge5DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge6DutyCycle = 0.5f;
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);
    }
    // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);
    }

    if (current_state==control_state)
    {

        i_dq_ref_right = Global_Data.rasv.i_dq_ref_right;
    	// park transformation of measured currents
    	i_dq_left = uz_transformation_3ph_abc_to_dq(i_abc_left, Global_Data.av.position_el_2pi_d3_1);
    	i_dq_right = uz_transformation_3ph_abc_to_dq(i_abc_right, Global_Data.av.position_el_2pi_d4_1);
    	Global_Data.av.i_d_left = i_dq_left.d;
    	Global_Data.av.i_q_left = i_dq_left.q;
    	Global_Data.av.i_d_right = i_dq_right.d;
    	Global_Data.av.i_q_right = i_dq_right.q;

    	// calculate control (speed and current) of left motor
    	control_left_motor();

    	// calculate control algorithm for right motor
    	control_right_motor();

    	// set dutycycles
    	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_left.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_left.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_left.DutyCycle_C;
    	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_right.DutyCycle_A;
    	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_right.DutyCycle_B;
    	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_right.DutyCycle_C;
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

static void control_left_motor() {
	// filter speed setpoint signal
	Global_Data.rasv.n_ref_left_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_left, Global_Data.rasv.n_ref_left);
	// calculate reference torque from speed ctrl of left motor
	Global_Data.rasv.M_ref_left = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_left, Global_Data.av.omega_mech_left, Global_Data.rasv.n_ref_left_filt);
	// calculate current setpoints i_dq_ref for left motor
	Global_Data.rasv.i_dq_ref_left = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_left,Global_Data.av.omega_mech_left, Global_Data.rasv.M_ref_left, Global_Data.av.v_dc_left, i_dq_left);
	// calculate reference voltages for current control
	v_dq_ref_left = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_left, Global_Data.rasv.i_dq_ref_left, i_dq_left, Global_Data.av.v_dc_left, Global_Data.av.omega_el_left);
	// get integrator clamping flag from current control
	Global_Data.av.currentcontrol_clamping_left = uz_CurrentControl_get_ext_clamping(Global_Data.objects.current_ctrl_left);
	// set clamping of integrators of speed control when current control is clamped
	uz_SpeedControl_set_ext_clamping(Global_Data.objects.speed_ctrl_left, Global_Data.av.currentcontrol_clamping_left);
	// write v_dq_ref_left to Global_Data
	Global_Data.av.v_d_left = v_dq_ref_left.d;
	Global_Data.av.v_q_left = v_dq_ref_left.q;
	// calculate SVPMW dutycycles
	dutycyc_left = uz_Space_Vector_Modulation(v_dq_ref_left, Global_Data.av.v_dc_left, Global_Data.av.position_el_2pi_d3_1);
};

static void control_right_motor() {
    // calculate reference voltages for current control
    v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, i_dq_ref_right, i_dq_right, Global_Data.av.v_dc_right, Global_Data.av.omega_el_right);
    Global_Data.av.v_d_right = v_dq_ref_right.d;
    Global_Data.av.v_q_right = v_dq_ref_right.q;
    // calculate duty cycles from reference dq voltages
    dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_right, Global_Data.av.position_el_2pi_d4_1);
};


static void measured_to_si_values() {
// update position and speed from resolver
Global_Data.av.resolver_pl_outputs_d3_1 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d3_1);

// calc motor angles and speeds with right orientation
Global_Data.av.position_el_2pi_d3_1 = (2.0f * UZ_PIf) - Global_Data.av.resolver_pl_outputs_d3_1.position_el_2pi;
Global_Data.av.position_mech_2pi_d3_1 =  (2.0f * UZ_PIf) - Global_Data.av.resolver_pl_outputs_d3_1.position_mech_2pi;
Global_Data.av.omega_mech_left = -1.0f * Global_Data.av.resolver_pl_outputs_d3_1.omega_mech_rad_s * 4.0f; // *4.0f accounting for bit resolution bug in resolverIP 16bit vs 14bit is factor 4
Global_Data.av.omega_el_left = Global_Data.av.omega_mech_left * Global_Data.av.polepairs_left;
Global_Data.av.n_mech_rpm_d3_1 = -1.0f * Global_Data.av.resolver_pl_outputs_d3_1.n_mech_rpm * 4.0f;

// Fake right position and speeds, if endat working delete this block
Global_Data.av.omega_mech_right = Global_Data.av.resolver_pl_outputs_d3_1.omega_mech_rad_s * 4.0f;
Global_Data.av.omega_el_right = Global_Data.av.omega_mech_right * Global_Data.av.polepairs_right;
Global_Data.av.n_mech_rpm_d4_1 = Global_Data.av.resolver_pl_outputs_d3_1.n_mech_rpm * 4.0f;
Global_Data.rasv.d4_to_d3_offset_el = Global_Data.av.polepairs_right * Global_Data.rasv.d4_to_d3_offset_mech;
Global_Data.av.position_el_2pi_d4_1 =  wrap_2pi(Global_Data.av.resolver_pl_outputs_d3_1.position_el_2pi - Global_Data.rasv.d4_to_d3_offset_el);
Global_Data.av.position_mech_2pi_d4_1 =  wrap_2pi(Global_Data.av.resolver_pl_outputs_d3_1.position_mech_2pi - Global_Data.rasv.d4_to_d3_offset_mech);

// Torque Sensor measurement
Global_Data.av.torque = Global_Data.aa.A1.me.ADC_B5 * 2.0f + Global_Data.rasv.torque_offset; //positive q-current = positive torque | Burster 8656-5010: 10Nm/10V = 1Nm/1V -> to +-5V via torque box: 1Nm/0.5V -> 2Nm/1V -> *2.0f
Global_Data.av.torque_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_torque, Global_Data.av.torque);

// assign inverter measurements - Conversion factors from Michi
Global_Data.av.i_a_left = (Global_Data.aa.A1.me.ADC_A3 * 12.129f) + 0.10f;
Global_Data.av.i_b_left = (Global_Data.aa.A1.me.ADC_A2 * 11.338) + 0.12f;
Global_Data.av.i_c_left = (Global_Data.aa.A1.me.ADC_A1 * 12.051f) - 0.07f;
Global_Data.av.i_a_right = (Global_Data.aa.A2.me.ADC_A3 * 12.038f) - 0.03f;
Global_Data.av.i_b_right = (Global_Data.aa.A2.me.ADC_A2 * 12.115f) - 0.00f;
Global_Data.av.i_c_right = (Global_Data.aa.A2.me.ADC_A1 * 12.038f) - 0.00f;

Global_Data.av.v_dc_left = (Global_Data.aa.A1.me.ADC_A4 * 100.302f) + 451.30f;
Global_Data.av.v_dc_right = (Global_Data.aa.A2.me.ADC_A4 * 99.700f) + 450.30f;

// assign measurements from global_data to motor control structs
i_abc_left.a = Global_Data.av.i_a_left;
i_abc_left.b = Global_Data.av.i_b_left;
i_abc_left.c = Global_Data.av.i_c_left;
i_abc_right.a = Global_Data.av.i_a_right;
i_abc_right.b = Global_Data.av.i_b_right;
i_abc_right.c = Global_Data.av.i_c_right;


};

static void check_constraints_current_voltage_temperature() {

    // check for current limit
    if (fabs(Global_Data.av.i_a_right) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_b_right) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_c_right) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_a_left) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_b_left) > MAX_CURRENT_AMP || fabs(Global_Data.av.i_c_left) > MAX_CURRENT_AMP)
    {
    	Global_Data.av.overcurrent_ac = 1.0f;
    	ultrazohm_state_machine_set_stop(true);
    }
    // check for dc link voltage
    if (fabs(Global_Data.av.v_dc_left) > MAX_DC_LINK_VOLTAGE || fabs(Global_Data.av.v_dc_right) > MAX_DC_LINK_VOLTAGE)
    {
    	Global_Data.av.overvoltage_dc = 1.0f;
    	ultrazohm_state_machine_set_stop(true);
    }
    // check for max speed
      if (fabs(Global_Data.av.n_mech_rpm_d3_1) > MAX_SPEED || fabs(Global_Data.av.n_mech_rpm_d4_1) > MAX_SPEED) {
    	Global_Data.av.overspeed = 1.0f;
    	ultrazohm_state_machine_set_stop(true);
    }
    // check for max torque
      if (fabs(Global_Data.av.torque_filt) > MAX_TORQUE) {
    	Global_Data.av.overtorque = 1.0f;
    	ultrazohm_state_machine_set_stop(true);
    }
};
static inline float wrap_2pi(float x) {
    float y = fmodf(x, 2.0f * (float)UZ_PIf);
    if (y < 0.0f) {
        y += 2.0f * (float)UZ_PIf;
    }
    return y;
}
