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
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_CurrentControl/uz_space_vector_limitation.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

#define 	CURRENT_2_SI_AMPERE	12.5f
#define		VOLTAGE_2_SI_VOLTS	12.0f
#define		MAX_CURRENT			15.0f
#define		V_DC				48.0f

struct uz_3ph_abc_t i_abc_left = {0.0f};
struct uz_3ph_abc_t i_abc_right = {0.0f};
struct uz_3ph_dq_t i_dq_left = {0.0f};
struct uz_3ph_dq_t i_dq_right = {0.0f};
struct uz_3ph_dq_t i_dq_ref_right = {0.0f};
struct uz_3ph_dq_t v_dq_ref_left = {0.0f};
struct uz_3ph_dq_t v_dq_ref_right = {0.0f};
struct uz_DutyCycle_t dutycyc_left = {0.0f};
struct uz_DutyCycle_t dutycyc_right = {0.0f};
struct uz_pmsmModel_inputs_t pmsm_cil_inputs = {0.0f};
struct uz_pmsmModel_outputs_t pmsm_cil_outputs = {0.0f};

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
static void control_left_motor();
static void control_right_motor();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();

    // update speed and position of resolvers// update speed and position of resolvers
    Global_Data.av.resolver_pl_outputs_left = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_left);
    Global_Data.av.resolver_pl_outputs_right = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_right);

	// assign measurements to Global_Data
	Global_Data.av.i_a_left = Global_Data.aa.A1.me.ADC_A4 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_b_left = Global_Data.aa.A1.me.ADC_A3 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_c_left = Global_Data.aa.A1.me.ADC_A2 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_dc_left = Global_Data.aa.A1.me.ADC_B5 * CURRENT_2_SI_AMPERE;
	Global_Data.av.v_a_left = Global_Data.aa.A1.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_b_left = Global_Data.aa.A1.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_c_left = Global_Data.aa.A1.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_dc_left = Global_Data.aa.A1.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;

	Global_Data.av.i_a_right = Global_Data.aa.A2.me.ADC_A4 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_b_right = Global_Data.aa.A2.me.ADC_A3 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_c_right = Global_Data.aa.A2.me.ADC_A2 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_dc_right = Global_Data.aa.A2.me.ADC_B5 * CURRENT_2_SI_AMPERE;
	Global_Data.av.v_a_right = Global_Data.aa.A2.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_b_right = Global_Data.aa.A2.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_c_right = Global_Data.aa.A2.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_dc_right = Global_Data.aa.A2.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;

    // check for current limit
    if (fabs(Global_Data.av.i_a_left) > MAX_CURRENT || fabs(Global_Data.av.i_b_left) > MAX_CURRENT || fabs(Global_Data.av.i_c_left) > MAX_CURRENT ||
   		fabs(Global_Data.av.i_a_right) > MAX_CURRENT || fabs(Global_Data.av.i_b_right) > MAX_CURRENT || fabs(Global_Data.av.i_c_right) > MAX_CURRENT) {
    	ultrazohm_state_machine_set_stop(true);
    }

    // update status of inverter adapters
    Global_Data.av.inverter_d1_left_status = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1_left);
    Global_Data.av.inverter_d2_right_status = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2_right);

    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // assign measurements from global_data to motor control structs
	i_abc_left.a = Global_Data.av.i_a_left;
	i_abc_left.b = Global_Data.av.i_b_left;
	i_abc_left.c = Global_Data.av.i_c_left;
	i_abc_right.a = Global_Data.av.i_a_right;
	i_abc_right.b = Global_Data.av.i_b_right;
	i_abc_right.c = Global_Data.av.i_c_right;

    // if "STOP"
    if (current_state==idle_state)
    {
    	// disable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_left, false);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_right, false);

    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_left);
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_right);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_left);
		Global_Data.rasv.n_ref_left = 0.0f;
		Global_Data.rasv.M_ref_left = 0.0f;
		Global_Data.rasv.i_dq_ref_left.d = 0.0f;
		Global_Data.rasv.i_dq_ref_left.q = 0.0f;
		Global_Data.rasv.i_dq_ref_right.d = 0.0f;
		Global_Data.rasv.i_dq_ref_right.q = 0.0f;

		// write zero dutycycle
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
    }

    // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
    	// enable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1_left, true);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2_right, true);
    }

    // if "ENABLE CONTROL"
    if (current_state==control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state

    	if (Global_Data.rasv.ctrl_plant_select == CIL) {
    		// get reference currents from Global_Data
    		i_dq_ref_right = Global_Data.rasv.i_dq_ref_right;
    		// calculations necessary for all control algorithms
    		uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsm_cil);
    		uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsm_cil);
    		pmsm_cil_outputs = uz_pmsmModel_get_outputs(Global_Data.objects.pmsm_cil);
    		i_dq_right.d = pmsm_cil_outputs.i_d_A;
    		i_dq_right.q = pmsm_cil_outputs.i_q_A;
    		Global_Data.av.omega_mech_right = pmsm_cil_outputs.omega_mech_1_s;
    		Global_Data.av.speed_rpm_right = (Global_Data.av.omega_mech_right*60.0f)/(2.0f*UZ_PIf);
    		Global_Data.av.speed_rpm_left = Global_Data.av.speed_rpm_right; // left because in real left motor is speed controlled
    		Global_Data.av.i_d_right = i_dq_right.d;
    		Global_Data.av.i_q_right = i_dq_right.q;

    		// calculate selected control algorithm for cil motor model
    		control_right_motor();
    	}

    	if (Global_Data.rasv.ctrl_plant_select == REAL) {
			// get reference currents from Global_Data
			i_dq_ref_right = Global_Data.rasv.i_dq_ref_right;

			// park transformation of measured currents
			i_dq_left = uz_transformation_3ph_abc_to_dq(i_abc_left, Global_Data.av.resolver_pl_outputs_left.position_el_2pi);
			i_dq_right = uz_transformation_3ph_abc_to_dq(i_abc_right, Global_Data.av.resolver_pl_outputs_right.position_el_2pi);
			Global_Data.av.i_d_left = i_dq_left.d;
			Global_Data.av.i_q_left = i_dq_left.q;
			Global_Data.av.i_d_right = i_dq_right.d;
			Global_Data.av.i_q_right = i_dq_right.q;
			Global_Data.av.omega_mech_right = Global_Data.av.resolver_pl_outputs_right.omega_mech_rad_s;
			Global_Data.av.omega_mech_left = Global_Data.av.resolver_pl_outputs_left.omega_mech_rad_s;
			Global_Data.av.speed_rpm_left = (Global_Data.av.omega_mech_left*60.0f)/(2.0f*UZ_PIf);
			Global_Data.av.speed_rpm_right = (Global_Data.av.omega_mech_right*60.0f)/(2.0f*UZ_PIf);

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
    }

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    // uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    // uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

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
	// calculate reference torque from speed ctrl of left motor
	Global_Data.rasv.M_ref_left = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_left, Global_Data.av.resolver_pl_outputs_left.omega_mech_rad_s, Global_Data.rasv.n_ref_left);
	// calculate current setpoints i_dq_ref for left motor
	Global_Data.rasv.i_dq_ref_left = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_left, Global_Data.av.resolver_pl_outputs_left.omega_mech_rad_s, Global_Data.rasv.M_ref_left, Global_Data.av.v_dc_left, i_dq_left);
	// calculate reference voltages for current control
	v_dq_ref_left = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_left, Global_Data.rasv.i_dq_ref_left, i_dq_left, Global_Data.av.v_dc_left, Global_Data.av.omega_mech_left*Global_Data.av.polepairs_left);
	Global_Data.av.v_d_ref_left = v_dq_ref_left.d;
	Global_Data.av.v_q_ref_left = v_dq_ref_left.q;
	dutycyc_left = uz_Space_Vector_Modulation(v_dq_ref_left, Global_Data.av.v_dc_left, Global_Data.av.resolver_pl_outputs_left.position_el_2pi);
};

static void control_right_motor() {
    if(Global_Data.rasv.ctrl_plant_select == REAL) {
        // calculate reference voltages for current control
        v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, i_dq_ref_right, i_dq_right, Global_Data.av.v_dc_right, Global_Data.av.omega_mech_right*Global_Data.av.polepairs_right);
        Global_Data.av.v_d_ref_right = v_dq_ref_right.d;
        Global_Data.av.v_q_ref_right = v_dq_ref_right.q;
		// calculate duty cycles from reference dq voltages
		dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_right, Global_Data.av.resolver_pl_outputs_right.position_el_2pi);
	}
	if(Global_Data.rasv.ctrl_plant_select == CIL) {
	    // calculate reference voltages for current control
	    v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, i_dq_ref_right, i_dq_right, V_DC, Global_Data.av.omega_mech_right*Global_Data.av.polepairs_right);
	    Global_Data.av.v_d_ref_right = v_dq_ref_right.d;
	    Global_Data.av.v_q_ref_right = v_dq_ref_right.q;
		// write inputs into CIL model
		pmsm_cil_inputs.v_d_V = v_dq_ref_right.d;
		pmsm_cil_inputs.v_q_V = v_dq_ref_right.q;
		pmsm_cil_inputs.omega_mech_1_s = 2.0f * UZ_PIf * Global_Data.rasv.n_ref_left / 60.0f;
		uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_cil, pmsm_cil_inputs);
	}
};
