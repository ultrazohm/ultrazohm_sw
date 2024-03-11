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
#include "../include/adc.h"
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

// Global variable structure
extern DS_Data Global_Data;

#define 	CURRENT_2_SI_AMPERE	12.5f
#define		VOLTAGE_2_SI_VOLTS	12.0f
#define		MAX_CURRENT			25.0f
#define		RATED_CURRENT		8.0f
#define		DC_VOLTAGE			48.0f
#define		MAX_MODULATION_INDEX (1.0f / sqrtf(3.0f))

// measurement structs for motor control
struct uz_3ph_abc_t i_abc_0 = {0.0f};
struct uz_3ph_abc_t i_abc_1 = {0.0f};
struct uz_3ph_dq_t i_dq_0 = {0.0f};
struct uz_3ph_dq_t i_dq_1 = {0.0f};
struct uz_3ph_dq_t i_dq_ref_0 = {0.0f};
struct uz_3ph_dq_t i_dq_ref_1 = {0.0f};
struct uz_3ph_dq_t i_dq_error_0 = {0.0f};
struct uz_3ph_dq_t i_dq_error_1 = {0.0f};
struct uz_3ph_dq_t v_dq_ref_0 = {0.0f};
struct uz_3ph_dq_t v_dq_ref_1 = {0.0f};
struct uz_DutyCycle_t dutycyc_0 = {0.0f};
struct uz_DutyCycle_t dutycyc_1 = {0.0f};

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

    // update speed and position of resolvers
    Global_Data.av.resolver_pl_outputs_d5_1 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d5_1);
    Global_Data.av.resolver_pl_outputs_d5_2 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d5_2);

	// assign measurements to Global_Data
	Global_Data.av.i_a_d1 = Global_Data.aa.A1.me.ADC_A4 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_b_d1 = Global_Data.aa.A1.me.ADC_A3 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_c_d1 = Global_Data.aa.A1.me.ADC_A2 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_dc_d1 = Global_Data.aa.A1.me.ADC_B5 * CURRENT_2_SI_AMPERE;
	Global_Data.av.v_a_d1 = Global_Data.aa.A1.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_b_d1 = Global_Data.aa.A1.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_c_d1 = Global_Data.aa.A1.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_dc_d1 = Global_Data.aa.A1.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;
//	Global_Data.av.v_dc_d1 = DC_VOLTAGE;

	Global_Data.av.i_a_d2 = Global_Data.aa.A2.me.ADC_A4 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_b_d2 = Global_Data.aa.A2.me.ADC_A3 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_c_d2 = Global_Data.aa.A2.me.ADC_A2 * CURRENT_2_SI_AMPERE;
	Global_Data.av.i_dc_d2 = Global_Data.aa.A2.me.ADC_B5 * CURRENT_2_SI_AMPERE;
	Global_Data.av.v_a_d2 = Global_Data.aa.A2.me.ADC_B8 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_b_d2 = Global_Data.aa.A2.me.ADC_B7 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_c_d2 = Global_Data.aa.A2.me.ADC_B6 * VOLTAGE_2_SI_VOLTS;
	Global_Data.av.v_dc_d2 = Global_Data.aa.A2.me.ADC_A1 * VOLTAGE_2_SI_VOLTS;
//	Global_Data.av.v_dc_d2 = DC_VOLTAGE;

	Global_Data.av.omega_mech_d5_1 = Global_Data.av.resolver_pl_outputs_d5_1.omega_mech_rad_s;
	Global_Data.av.omega_mech_d5_2 = Global_Data.av.resolver_pl_outputs_d5_2.omega_mech_rad_s;

	// get reference currents from Global_Data
	i_dq_ref_0 = Global_Data.rasv.i_dq_ref_0;
	i_dq_ref_1 = Global_Data.rasv.i_dq_ref_1;

	// assign measurements from global_data to motor control structs
    i_abc_0.a = Global_Data.av.i_a_d1;
    i_abc_0.b = Global_Data.av.i_b_d1;
    i_abc_0.c = Global_Data.av.i_c_d1;
    i_abc_1.a = Global_Data.av.i_a_d2;
    i_abc_1.b = Global_Data.av.i_b_d2;
    i_abc_1.c = Global_Data.av.i_c_d2;

	// park transformation of measured currents
	i_dq_0 = uz_transformation_3ph_abc_to_dq(i_abc_0, Global_Data.av.resolver_pl_outputs_d5_1.position_el_2pi);
	i_dq_1 = uz_transformation_3ph_abc_to_dq(i_abc_1, Global_Data.av.resolver_pl_outputs_d5_2.position_el_2pi);
	Global_Data.av.i_d_0 = i_dq_0.d;
	Global_Data.av.i_q_0 = i_dq_0.q;
	Global_Data.av.i_d_1 = i_dq_1.d;
	Global_Data.av.i_q_1 = i_dq_1.q;

    // check for current limit
    if (fabs(Global_Data.av.i_a_d1) > MAX_CURRENT || fabs(Global_Data.av.i_b_d1) > MAX_CURRENT || fabs(Global_Data.av.i_c_d1) > MAX_CURRENT ||
   		fabs(Global_Data.av.i_a_d2) > MAX_CURRENT || fabs(Global_Data.av.i_b_d2) > MAX_CURRENT || fabs(Global_Data.av.i_c_d2) > MAX_CURRENT) {
    	ultrazohm_state_machine_set_stop(true);
    }

	//read axi values from mpc ip for debug
//	fcs_mpc_debug();

	//calc average switching frequency of inverters
	fcs_mpc_calc_f_sw_avg();

    // check platform state machine
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // if "STOP"
    if (current_state==idle_state)
    {
    	// disable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_d1, false);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_d2, false);
    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_left);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_right);
		// write zero dutycycle
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
		//disable MPC IP
		fcs_mpc_enable_0(false);
		fcs_mpc_enable_1(false);
    }

    // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
    	// enable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_d1, true);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_d2, true);
    }

    // if "ENABLE CONTROL"
    if (current_state==control_state)
    {
    	//enable MPC IP
		fcs_mpc_enable_0(true);
		fcs_mpc_enable_1(true);

    	// calculate control of left motor at inverter d1 and resolver d5_1
    	control_left_motor();

    	// calculate control of right motor at inverter d2 and resolver d5_2
    	control_right_motor();

    	// assign dutycycles to PWM module variables
    	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_0.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_0.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_0.DutyCycle_C;
    	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_1.DutyCycle_A;
    	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_1.DutyCycle_B;
    	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_1.DutyCycle_C;
    }


    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_0, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_1, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_2, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_3, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

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

void control_left_motor() {


//	v_dq_ref_0 = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_left, i_dq_ref_0, i_dq_0, DC_VOLTAGE, Global_Data.av.omega_mech_d5_1*Global_Data.av.polepairs_left);
//	dutycyc_0 = uz_Space_Vector_Modulation(v_dq_ref_0, Global_Data.av.v_dc_d1, Global_Data.av.resolver_pl_outputs_d5_1.position_el_2pi);
	// write measured dc_link voltage to pu_voltages ip
    fcs_mpc_write_axi_v_dc();
	//write setpoint to MPC
	fcs_mpc_write_setpoint_0();
	//write setpoint to pu_voltages for deadtime compensation algorithm
//	fcs_mpc_write_i_ref_to_pu_voltages();
};

void control_right_motor() {
	// filter speed setpoint signal
	Global_Data.rasv.n_ref_right_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed, Global_Data.rasv.n_ref_right);
	// calculate reference torque from speed ctrl of right motor
	Global_Data.rasv.M_ref_right = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_right, Global_Data.av.resolver_pl_outputs_d5_2.omega_mech_rad_s, Global_Data.rasv.n_ref_right_filt);
	// calculate current setpoints i_dq_ref for right motor
	Global_Data.rasv.i_dq_ref_1 = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_right, Global_Data.av.resolver_pl_outputs_d5_2.omega_mech_rad_s, Global_Data.rasv.M_ref_right, Global_Data.av.v_dc_d2, i_dq_1);
	// calculate reference voltages for current control
//	v_dq_ref_1 = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, i_dq_ref_1, i_dq_1, DC_VOLTAGE, Global_Data.av.omega_mech_d5_2*Global_Data.av.polepairs_right);
	// calculate duty cycles from reference dq voltages
//	dutycyc_1 = uz_Space_Vector_Modulation(v_dq_ref_1, Global_Data.av.v_dc_d2, Global_Data.av.resolver_pl_outputs_d5_2.position_el_2pi);
	// write measured dc_link voltage to pu_voltages ip
    fcs_mpc_write_axi_v_dc();
	//write setpoint to MPC
	fcs_mpc_write_setpoint_1();
	//write setpoint to pu_voltages for deadtime compensation algorithm
//	fcs_mpc_write_i_ref_to_pu_voltages();
};
