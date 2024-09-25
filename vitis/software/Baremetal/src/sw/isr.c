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
#include "../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "../uz/uz_CurrentControl/uz_space_vector_limitation.h"
#include "../uz/uz_signals/uz_signals.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

#define 	CURRENT_2_SI_AMPERE	12.5f
#define		VOLTAGE_2_SI_VOLTS	12.0f
#define		MAX_CURRENT			15.0f
#define		RATED_CURRENT		8.0f
#define		DC_VOLTAGE			48.0f
#define		MAX_MODULATION_INDEX (1.0f / sqrtf(3.0f))
#define		MAX_VOLTAGE			(DC_VOLTAGE * MAX_MODULATION_INDEX)
#define		RATED_SPEED			1000.0f
#define		TS_TRAINING			0.0001f
#define		NUMBER_OF_INPUTS_NN 9U

// measurement structs for motor control
struct uz_3ph_abc_t i_abc_left = {0.0f};
struct uz_3ph_abc_t i_abc_right = {0.0f};
struct uz_3ph_dq_t i_dq_left = {0.0f};
struct uz_3ph_dq_t i_dq_right = {0.0f};
struct uz_3ph_dq_t i_dq_ref_right = {0.0f};
struct uz_3ph_dq_t i_dq_error_left = {0.0f};
struct uz_3ph_dq_t i_dq_error_right = {0.0f};
struct uz_3ph_dq_t i_dq_integrated_error_left = {0.0f};
struct uz_3ph_dq_t i_dq_integrated_error_right = {0.0f};
struct uz_3ph_dq_t v_dq_ref_non_limited_left = {0.0f};
struct uz_3ph_dq_t v_dq_ref_non_limited_right = {0.0f};
struct uz_3ph_dq_t v_dq_ref_left = {0.0f};
struct uz_3ph_dq_t v_dq_ref_right = {0.0f};
struct uz_DutyCycle_t dutycyc_left = {0.0f};
struct uz_DutyCycle_t dutycyc_right = {0.0f};
struct uz_pmsmModel_inputs_t pmsm_cil_inputs = {0.0f};
struct uz_pmsmModel_outputs_t pmsm_cil_outputs = {0.0f};

struct uz_fixedpoint_definition_t fixedpoint_definition_debug = {
		.is_signed = true,
		.integer_bits = 12,
		.fractional_bits = 15
};

float observation[NUMBER_OF_INPUTS_NN] = {0};

uz_matrix_t* matrix_output;

bool ddpg_ext_clamping = false;

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

uint32_t setpoint_index = 0;
float setpoint_index_float = 0;
float start_marker = 0.0f;
uint64_t old_uptime = 0;

float id_setpoints[22]={

#include "id_setpoints.csv"

};

float iq_setpoints[22]={

#include "iq_setpoints.csv"

};

float n_ref_left=0.0f;

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
//    update_speed_and_position_of_encoder_on_D5(&Global_Data);
    // update speed and position of resolvers
    Global_Data.av.resolver_pl_outputs_left = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_left);
    Global_Data.av.resolver_pl_outputs_right = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_right);
    // update status of both inverters
    uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_left);
    uz_inverter_adapter_update_states(Global_Data.objects.uz_d_inverter_right);
    // assign status to Global_Data
    Global_Data.av.inverter_left_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_left);
    Global_Data.av.inverter_right_status = uz_inverter_adapter_get_outputs(Global_Data.objects.uz_d_inverter_right);

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

	// assign measurements from global_data to motor control structs
    i_abc_left.a = Global_Data.av.i_a_left;
    i_abc_left.b = Global_Data.av.i_b_left;
    i_abc_left.c = Global_Data.av.i_c_left;
    i_abc_right.a = Global_Data.av.i_a_right;
    i_abc_right.b = Global_Data.av.i_b_right;
    i_abc_right.c = Global_Data.av.i_c_right;

    // check for current limit
    if (fabs(Global_Data.av.i_a_left) > MAX_CURRENT || fabs(Global_Data.av.i_b_left) > MAX_CURRENT || fabs(Global_Data.av.i_c_left) > MAX_CURRENT ||
   		fabs(Global_Data.av.i_a_right) > MAX_CURRENT || fabs(Global_Data.av.i_b_right) > MAX_CURRENT || fabs(Global_Data.av.i_c_right) > MAX_CURRENT) {
    	ultrazohm_state_machine_set_stop(true);
    }

    // calculate mean temperature values over all measured temperatures of each inverter
    Global_Data.av.mean_temp_inv_left = (Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_left_status.ChipTempDegreesCelsius_L3) * 0.1667;
    Global_Data.av.mean_temp_inv_right = (Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_H1+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_L1+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_H2+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_L2+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_H3+Global_Data.av.inverter_right_status.ChipTempDegreesCelsius_L3) * 0.1667;

	//read axi values from mpc ip for debug
//	fcs_mpc_debug();

    //calculate given trajectory
    // Global_Data.av.traj_speed_ref = uz_Trajectory_Step(Global_Data.objects.speed_traj);
    // Global_Data.av.traj_current_ref = uz_Trajectory_Step(Global_Data.objects.current_traj);

    // check platform state machine
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // if "STOP"
    if (current_state==idle_state)
    {
    	// disable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_left, false);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_right, false);
    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_left);
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_right);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_left);
		uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_left, 0.0f);
		// write zero dutycycle
		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
		//disable MPC IP
		fcs_mpc_enable(false);
		// reset ddpg integrators
		i_dq_integrated_error_right.d = 0.0f;
		i_dq_integrated_error_right.q = 0.0f;
		i_dq_integrated_error_left.d = 0.0f;
		i_dq_integrated_error_left.q = 0.0f;
		ddpg_ext_clamping = false;
    }

    // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
    	// enable inverters
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_left, true);
    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.uz_d_inverter_right, true);
    }

    // if "ENABLE CONTROL"
    if (current_state==control_state)
    {
    	// Start: Control algorithm - only if ultrazohm is in control state

    	// get reference currents from Global_Data
    	//overwrite q-current ref with trajectory
    	// if (Global_Data.rasv.reference_select == TRAJECTORY) {
    	// 	i_dq_ref_right.q = Global_Data.av.traj_current_ref;
		// 	Global_Data.rasv.n_ref_left = Global_Data.av.traj_speed_ref;
		// }

		setpoint_index_float = (float)setpoint_index;

		if ((Global_Data.rasv.reference_select == TRAJECTORY))
		{
			start_marker = 1.0f;
			i_dq_ref_right.d = id_setpoints[setpoint_index];
			i_dq_ref_right.q = iq_setpoints[setpoint_index];

			// step throught the array
			uint64_t current_uptime = uz_SystemTime_GetInterruptCounter();
			if (current_uptime > (old_uptime + 5000))
			{
				old_uptime = current_uptime;

				if (setpoint_index < 21)
				{
					setpoint_index++;
				}
				else
				{
					setpoint_index = 0;
					Global_Data.rasv.reference_select = MANUAL;
					start_marker = 0.0f;
					n_ref_left=n_ref_left-100.0f;
					if(n_ref_left<-1000.0f){
						n_ref_left=0.0f;
					}
				}
			}
		}
		else
		{
			i_dq_ref_right = Global_Data.rasv.i_dq_ref_right;
			//n_ref_left=Global_Data.rasv.n_ref_left;
		}

		//////////////////////////////////////////////////////////////////////////////////
    	if (Global_Data.rasv.ctrl_plant_select == CIL) {
    		// calculations necessary for all control algorithms
    		uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsm_cil);
    		uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsm_cil);
    		pmsm_cil_outputs = uz_pmsmModel_get_outputs(Global_Data.objects.pmsm_cil);
    		i_dq_right.d = pmsm_cil_outputs.i_d_A;
    		i_dq_right.q = pmsm_cil_outputs.i_q_A;
    		Global_Data.av.omega_mech_right = pmsm_cil_outputs.omega_mech_1_s;
    		Global_Data.av.i_d_right = i_dq_right.d;
    		Global_Data.av.i_q_right = i_dq_right.q;

    		// calculate selected control algorithm for cil motor model
    		control_right_motor();
    	}

    	if (Global_Data.rasv.ctrl_plant_select == REAL) {
    		fcs_mpc_enable(true);
        	// calculations necessary for all control algorithms
        	// park transformation of measured currents
        	i_dq_left = uz_transformation_3ph_abc_to_dq(i_abc_left, Global_Data.av.resolver_pl_outputs_left.position_el_2pi);
        	i_dq_right = uz_transformation_3ph_abc_to_dq(i_abc_right, Global_Data.av.resolver_pl_outputs_right.position_el_2pi);
        	Global_Data.av.omega_mech_right = Global_Data.av.resolver_pl_outputs_right.omega_mech_rad_s;
        	Global_Data.av.i_d_left = i_dq_left.d;
        	Global_Data.av.i_q_left = i_dq_left.q;
        	Global_Data.av.i_d_right = i_dq_right.d;
        	Global_Data.av.i_q_right = i_dq_right.q;

        	//calc average switching frequency of right motor
        	fcs_mpc_calc_f_sw_avg();

        	// calculate control (speed and current) of left motor
        	control_left_motor();

        	// calculate selected control algorithm for right motor
        	control_right_motor();

        	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_left.DutyCycle_A;
        	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_left.DutyCycle_B;
        	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_left.DutyCycle_C;
        	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_right.DutyCycle_A;
        	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_right.DutyCycle_B;
        	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_right.DutyCycle_C;
    	}

    }
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    //uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

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
	//enable MPC
	fcs_mpc_enable(true);
	// calculate reference torque from speed ctrl of left motor
	Global_Data.rasv.n_ref_left_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_left, n_ref_left);
	Global_Data.rasv.M_ref_left = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_left, Global_Data.av.resolver_pl_outputs_left.omega_mech_rad_s, Global_Data.rasv.n_ref_left_filt);
	// calculate current setpoints i_dq_ref for left motor
	Global_Data.rasv.i_dq_ref_left = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_left, Global_Data.av.resolver_pl_outputs_left.omega_mech_rad_s, Global_Data.rasv.M_ref_left, Global_Data.av.v_dc_left, i_dq_left);
    // write measured dc_link voltage to pu_voltages ip
    fcs_mpc_write_axi_v_dc();
	//write setpoint to MPC
	fcs_mpc_write_setpoint();
};

void control_right_motor() {

	if(Global_Data.rasv.current_ctrl_select == PI_FOC) {
    	// calculate reference voltages for current control
    	v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, i_dq_ref_right, i_dq_right, DC_VOLTAGE, Global_Data.av.omega_mech_right*Global_Data.av.polepairs_right);
    	Global_Data.av.v_d_right = v_dq_ref_right.d;
    	Global_Data.av.v_q_right = v_dq_ref_right.q;
    	if(Global_Data.rasv.ctrl_plant_select == REAL) {
        	// calculate duty cycles from reference dq voltages
        	dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_right, Global_Data.av.resolver_pl_outputs_right.position_el_2pi);
    	}
    	if(Global_Data.rasv.ctrl_plant_select == CIL) {
    		// write inputs into CIL model
    		pmsm_cil_inputs.v_d_V = v_dq_ref_right.d;
    		pmsm_cil_inputs.v_q_V = v_dq_ref_right.q;
    		pmsm_cil_inputs.omega_mech_1_s = 2.0f * UZ_PIf * n_ref_left / 60.0f;
    		uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_cil, pmsm_cil_inputs);
    	}
	}

	if(Global_Data.rasv.current_ctrl_select == DDPG_CC) {
    	// calculate integrated error by using Forward-Euler with error of previous timestep for integration
    	if(ddpg_ext_clamping == false) {
    		i_dq_integrated_error_right.d += (i_dq_error_right.d / RATED_CURRENT) * TS_TRAINING;
    		i_dq_integrated_error_right.q += (i_dq_error_right.q / RATED_CURRENT) * TS_TRAINING;
    	} else {
    		i_dq_integrated_error_right.d += 0.0f;
    		i_dq_integrated_error_right.q += 0.0f;
    	}
    	// calculate reference current tracking error
    	i_dq_error_right.d = i_dq_ref_right.d - i_dq_right.d;
    	i_dq_error_right.q = i_dq_ref_right.q - i_dq_right.q;
    	// calculate observations
    	observation[0] = i_dq_error_right.d / RATED_CURRENT;
    	observation[1] = i_dq_integrated_error_right.d / TS_TRAINING;
    	observation[2] = i_dq_error_right.q / RATED_CURRENT;
    	observation[3] = i_dq_integrated_error_right.q / TS_TRAINING;
    	observation[4] = i_dq_right.d / RATED_CURRENT;
    	observation[5] = i_dq_right.q / RATED_CURRENT;
    	observation[6] = ((Global_Data.av.omega_mech_right * 60.0f) / (2.0f * UZ_PIf)) / RATED_SPEED;
    	observation[7] = v_dq_ref_right.d / MAX_VOLTAGE;
    	observation[8] = v_dq_ref_right.q / MAX_VOLTAGE;
    	// calculate neural network
    	for (uint32_t i = 0; i < NUMBER_OF_INPUTS_NN; i++) {
    		uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input,observation[i],0U,i);
    	}
    	uz_nn_ff(Global_Data.objects.nn_layer, Global_Data.objects.matrix_input);
    	matrix_output = uz_nn_get_output_data(Global_Data.objects.nn_layer);
    	uz_matrix_multiply_by_scalar(matrix_output, MAX_VOLTAGE);
    	// calculate reference voltages
    	v_dq_ref_non_limited_right.d = uz_matrix_get_element_zero_based(matrix_output, 0U, 0U);
    	v_dq_ref_non_limited_right.q = uz_matrix_get_element_zero_based(matrix_output, 0U, 1U);
    	v_dq_ref_right = uz_CurrentControl_SpaceVector_Limitation(v_dq_ref_non_limited_right, DC_VOLTAGE, MAX_MODULATION_INDEX, Global_Data.av.omega_mech_right * Global_Data.av.polepairs_right, i_dq_right, &ddpg_ext_clamping);
    	Global_Data.av.v_d_right = v_dq_ref_right.d;
    	Global_Data.av.v_q_right = v_dq_ref_right.q;
    	if(Global_Data.rasv.ctrl_plant_select == REAL) {
        	// calculate duty cycles from reference dq voltages
        	dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, DC_VOLTAGE, Global_Data.av.resolver_pl_outputs_right.position_el_2pi);
    	}
    	if(Global_Data.rasv.ctrl_plant_select == CIL) {
    		// write inputs into CIL model
    		pmsm_cil_inputs.v_d_V = v_dq_ref_right.d;
    		pmsm_cil_inputs.v_q_V = v_dq_ref_right.q;
    		pmsm_cil_inputs.omega_mech_1_s = 2.0f * UZ_PIf * n_ref_left / 60.0f;
    		uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_cil, pmsm_cil_inputs);
    	}
	}

};
