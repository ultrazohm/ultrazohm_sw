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
#include "../include/uz_testbench_limits.h"
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

extern uz_codegen codegenInstance;

// measurement structs for motor control
struct uz_3ph_abc_t i_abc_left = {0.0f};
struct uz_3ph_abc_t i_abc_right = {0.0f};
struct uz_3ph_dq_t i_dq_left = {0.0f};
struct uz_3ph_dq_t i_dq_right = {0.0f};
struct uz_3ph_dq_t i_dq_ref_right = {0.0f};
struct uz_3ph_dq_t i_dq_ref_left = {0.0f};
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
static inline float wrap_2pi(float x);
static void encoder_offset_estimation_step();
static void deadtime_comp();
static void deadbeat_right_motor();

struct uz_3ph_abc_t three_phase_output = {0};
float amplitude = 0.0f;
float frequency = 1.0f;
float offset = 0.0f;
bool Speed2Torque = false;

float Te = 0.0f;
float Kp_current = 0.4f;
float Ki_current = 20.0f;
float da = 0.0f;
float db = 0.0f;
float dc = 0.0f;

float theta_e_right_est = 0.0f;
float theta_e_right_unwrap = 0.0f;
float i_alpha_right_est = 0.0f;
float i_beta_right_est = 0.0f;
float i_alpha_right = 0.0f;
float i_beta_right = 0.0f;
float n_right_est = 0.0f;

float k = 100.0f;
float wc = 300.0f;
float wc_speed = 10.0f;

float theta_e_left_est = 0.0f;
float theta_left_est = 0.0f;
float w_e_left_est = 0.0f;
float w_left_est =  0.0f;
float n_left_est = 0.0f;

bool index_switch = false;

//Deadtime Compensation
float theta_i = 0.0f;
int sec = 1;
float delt_U = 0.0f;
float Ua_comp = 0.0f;
float Ub_comp = 0.0f;
float Uc_comp = 0.0f;
float DT_Comp = 0.0f;
float k_dt_c = 1.0f;

//Deadbeat
static float u_a0 = 0.0f;
static float u_b0 = 0.0f;
static float u_c0 = 0.0f;

float u_alpha0, u_beta0;
float ce, se;
float u_d0, u_q0;
float v_d0, v_q0;
float wrTs;
float Ts_over_Ld, Ts_over_Lq;
float id_k, iq_k;
float Theta_k, Theta_k1;
float Ld_over_Ts, Lq_over_Ts;
float vd_ref, vq_ref;
float ck1, sk1;
float v_alpha_ref, v_beta_ref;
float inv_half_Vdc;
float u_alpha, u_beta;
float u_a, u_b, u_c;
float u_min, u_max, u_com;

//Bandwidth test
float sine = 0;
float t_Sec = 0;
float angle = 0;

//Autotuning


void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    // set endat offset
//    uz_endat_interface_set_mechanical_offset_endat_single_turn(Global_Data.objects.endat_encoder_d4_1,Global_Data.rasv.endat_offset);
    // update and calculate measured values
    measured_to_si_values();
    // check for physical and safety limits
    uz_testbench_limits_step(&Global_Data.av);

    platform_state_t current_state=ultrazohm_state_machine_get_state();
    // if "STOP"
    if (current_state==idle_state)
    {
    	// reset controllers
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_left);
		uz_CurrentControl_reset(Global_Data.objects.current_ctrl_right);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_left);
		uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_right);

		Global_Data.rasv.n_ref_left = 0.0f;
		Global_Data.rasv.n_ref_right = 0.0f;
		Global_Data.rasv.n_ref_left_filt = 0.0f;
		Global_Data.rasv.n_ref_right_filt = 0.0f;
		Global_Data.rasv.M_ref_left = 0.0f;
		Global_Data.rasv.M_ref_right = 0.0f;
		Global_Data.rasv.i_dq_ref_left.d = 0.0f;
		Global_Data.rasv.i_dq_ref_left.q = 0.0f;
		Global_Data.rasv.i_dq_ref_right.d = 0.0f;
		Global_Data.rasv.i_dq_ref_right.q = 0.0f;
		uz_signals_IIR_Filter_reset(Global_Data.objects.iir_filter_ref_speed_left);
		uz_signals_IIR_Filter_reset(Global_Data.objects.iir_filter_ref_speed_right);
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
    	//three_phase_output = uz_wavegen_three_phase_sample(amplitude, frequency, offset);//%%%%%%%%%%%%%%%%%%%%%
    	//Global_Data.rasv.halfBridge4DutyCycle = three_phase_output.a;
    	//Global_Data.rasv.halfBridge5DutyCycle = three_phase_output.b;
    	//Global_Data.rasv.halfBridge6DutyCycle = three_phase_output.c;
    	//da = three_phase_output.a;
    	//db = three_phase_output.b;
    	//dc = three_phase_output.c;

    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);
    }

    if (current_state==control_state)
    {

        i_dq_ref_left = Global_Data.rasv.i_dq_ref_left;
        i_dq_ref_right = Global_Data.rasv.i_dq_ref_right;
        t_Sec = uz_SystemTime_GetGlobalTimeInSec();
        angle = 2.0f * UZ_PIf * t_Sec * frequency;
        sine = amplitude * sinf(angle) + offset;//%%%%%%%%%%%%%%%%%%%%%
    	i_dq_ref_right.d = sine;

        // park transformation of measured currents
    	i_dq_left = uz_transformation_3ph_abc_to_dq(i_abc_left, Global_Data.av.position_el_2pi_d3_1);
    	i_dq_right = uz_transformation_3ph_abc_to_dq(i_abc_right, Global_Data.av.position_el_2pi_d4_1);
    	Global_Data.av.i_d_left = i_dq_left.d;
    	Global_Data.av.i_q_left = i_dq_left.q;
    	Global_Data.av.i_d_right = i_dq_right.d;
    	Global_Data.av.i_q_right = i_dq_right.q;

    	//encoder_offset_estimation_step();

    	// calculate control (speed and current) of left motor
    	control_left_motor();

    	// calculate control algorithm for right motor
    	control_right_motor();

    	//deadbeat_right_motor();
    	//Deadtime Compensation
    	//deadtime_comp();
    	// Control Algorithm: Input
    	/*
    	codegenInstance.input.ia = i_abc_right.a;
		codegenInstance.input.ib = i_abc_right.b;
		codegenInstance.input.ic = i_abc_right.c;
		codegenInstance.input.id_ref = i_dq_ref_right.d;
		codegenInstance.input.iq_ref = i_dq_ref_right.q;
		codegenInstance.input.id = i_dq_right.d;
		codegenInstance.input.iq = i_dq_right.q;
		codegenInstance.input.theta_e = Global_Data.av.position_el_2pi_d4_1;
		codegenInstance.input.w_e = Global_Data.av.omega_el_right;
		codegenInstance.input.Comp_PM = 1.0f;
		codegenInstance.input.Rs_PM = 1.2f;
		//codegenInstance.input.Psi_PM = 0.1142f;
		codegenInstance.input.Psi_PM = 0.140f;
		codegenInstance.input.Ts = Global_Data.av.isr_samplerate_s;
		codegenInstance.input.V_dc_nom_PM = Global_Data.av.v_dc_left;
		codegenInstance.input.Ld_PM = 0.0136f;
		codegenInstance.input.Lq_PM = 0.0136f;
		*/

		//codegenInstance.input.Lambda = 0.0f;
		////codegenInstance.input.Lambda = 0.00001f;
		//codegenInstance.input.Np = 3.0f;
		//codegenInstance.input.Kp_current = Kp_current;
		//codegenInstance.input.Ki_current = Ki_current;

		//Left MATLAB
		//codegenInstance.input.id_ref_left = Global_Data.rasv.i_dq_ref_left.d;
		//codegenInstance.input.iq_ref_left = Global_Data.rasv.i_dq_ref_left.q;
		//codegenInstance.input.id_left = Global_Data.av.i_d_left;
		//codegenInstance.input.iq_left = Global_Data.av.i_q_left;
		//codegenInstance.input.theta_left = Global_Data.av.position_el_2pi_d3_1;
		//codegenInstance.input.we_left = Global_Data.av.omega_el_left;

		//Sliding Mode
		//codegenInstance.input.k = k;
		//codegenInstance.input.wc = wc;
		//codegenInstance.input.wc_speed = wc_speed;

		// Control Algorithm: Execution
    	//uz_codegen_step(&codegenInstance);

    	//Te = codegenInstance.output.Te_est - 0.12f;

    	//da = codegenInstance.output.da;
    	//db = codegenInstance.output.db;
    	//dc = codegenInstance.output.dc;

    	/*Estimation
    	theta_e_right_est = codegenInstance.output.theta_e_est;
    	theta_e_right_unwrap = codegenInstance.output.theta_unwrap;
    	i_alpha_right_est = codegenInstance.output.i_alpha_est;
    	i_beta_right_est = codegenInstance.output.i_beta_est;
    	i_alpha_right = codegenInstance.output.i_alpha;
    	i_beta_right = codegenInstance.output.i_beta;
    	n_right_est = codegenInstance.output.n_est;
    	 */





    	// Control Algorithm: Output/Set dutycycles
    	Global_Data.rasv.halfBridge1DutyCycle = dutycyc_left.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = dutycyc_left.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = dutycyc_left.DutyCycle_C;
    	Global_Data.rasv.halfBridge4DutyCycle = dutycyc_right.DutyCycle_A;
    	Global_Data.rasv.halfBridge5DutyCycle = dutycyc_right.DutyCycle_B;
    	Global_Data.rasv.halfBridge6DutyCycle = dutycyc_right.DutyCycle_C;
    	//Global_Data.rasv.halfBridge1DutyCycle = codegenInstance.output.da_left;
    	//Global_Data.rasv.halfBridge2DutyCycle = codegenInstance.output.db_left;
    	//Global_Data.rasv.halfBridge3DutyCycle = codegenInstance.output.dc_left;

    	/////////////////////////////////////////////////////////////////////////

    	/*Deadtime Compensation
    	if (DT_Comp == 1)
    			{
    			dutycyc_right.DutyCycle_A = dutycyc_right.DutyCycle_A + Ua_comp;
    			dutycyc_right.DutyCycle_B = dutycyc_right.DutyCycle_B + Ub_comp;
    			dutycyc_right.DutyCycle_C = dutycyc_right.DutyCycle_C + Uc_comp;
    			if (dutycyc_right.DutyCycle_A >= 1.0f)
    				dutycyc_right.DutyCycle_A = 1.0f;
    			if (dutycyc_right.DutyCycle_A <= 0.0f)
    				dutycyc_right.DutyCycle_A = 0.0f;

    			if (dutycyc_right.DutyCycle_B >= 1.0f)
    				dutycyc_right.DutyCycle_B = 1.0f;
    			if (dutycyc_right.DutyCycle_B <= 0.0f)
    				dutycyc_right.DutyCycle_B = 0.0f;

    			if (dutycyc_right.DutyCycle_C >= 1.0f)
    				dutycyc_right.DutyCycle_C = 1.0f;
    			if (dutycyc_right.DutyCycle_C <= 0.0f)
    				dutycyc_right.DutyCycle_C = 0.0f;

    			}
    	*/
//    	Global_Data.rasv.halfBridge4DutyCycle = da;
//    	Global_Data.rasv.halfBridge5DutyCycle = db;
//    	Global_Data.rasv.halfBridge6DutyCycle = dc;


    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

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

static void encoder_offset_estimation_step()
{
	if (Global_Data.objects.encoder_offset_estimation_resolver_d3 != 0)
	{
		struct uz_encoder_offset_estimation_status resolver_status = uz_encoder_offset_estimation_get_status(Global_Data.objects.encoder_offset_estimation_resolver_d3);
		Global_Data.av.encoder_offset_resolver_progress = resolver_status.progress;
		Global_Data.av.encoder_offset_resolver_diagnose = (float)resolver_status.diagnose;

		if (!uz_encoder_offset_estimation_get_finished(Global_Data.objects.encoder_offset_estimation_resolver_d3))
		{
			Global_Data.av.encoder_offset_resolver_i_dq_ref = uz_encoder_offset_estimation_step(Global_Data.objects.encoder_offset_estimation_resolver_d3);
		}
		else
		{
			Global_Data.av.encoder_offset_resolver_i_dq_ref.d = 0.0f;
			Global_Data.av.encoder_offset_resolver_i_dq_ref.q = 0.0f;
			Global_Data.av.encoder_offset_resolver_i_dq_ref.zero = 0.0f;
		}
	}

	if (Global_Data.objects.encoder_offset_estimation_endat_d4 != 0)
	{
		struct uz_encoder_offset_estimation_status endat_status = uz_encoder_offset_estimation_get_status(Global_Data.objects.encoder_offset_estimation_endat_d4);
		Global_Data.av.encoder_offset_endat_progress = endat_status.progress;
		Global_Data.av.encoder_offset_endat_diagnose = (float)endat_status.diagnose;

		if (!uz_encoder_offset_estimation_get_finished(Global_Data.objects.encoder_offset_estimation_endat_d4))
		{
			Global_Data.av.encoder_offset_endat_i_dq_ref = uz_encoder_offset_estimation_step(Global_Data.objects.encoder_offset_estimation_endat_d4);
		}
		else
		{
			Global_Data.av.encoder_offset_endat_i_dq_ref.d = 0.0f;
			Global_Data.av.encoder_offset_endat_i_dq_ref.q = 0.0f;
			Global_Data.av.encoder_offset_endat_i_dq_ref.zero = 0.0f;
		}
	}
}

static void control_left_motor() {

	if (Speed2Torque)
	{
		if (index_switch == false)
		{
			Global_Data.rasv.n_ref_left = -Global_Data.rasv.n_ref_right;
			Global_Data.rasv.i_dq_ref_right.d = -Global_Data.rasv.i_dq_ref_left.d;
			Global_Data.rasv.i_dq_ref_right.q = -Global_Data.rasv.i_dq_ref_left.q;
			index_switch = true;
		}
		//Speed Mode
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
	}
	else
	{
		if (index_switch == true)
		{
			Global_Data.rasv.i_dq_ref_left.d = -Global_Data.rasv.i_dq_ref_right.d;
			Global_Data.rasv.i_dq_ref_left.q = -Global_Data.rasv.i_dq_ref_right.q;
			Global_Data.rasv.n_ref_right = -Global_Data.rasv.n_ref_left;
			index_switch = false;
		}
		//Torque Mode

		Global_Data.rasv.n_ref_left_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_left, Global_Data.rasv.n_ref_left);

		// calculate reference voltages for current control
		v_dq_ref_left = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_left, Global_Data.rasv.i_dq_ref_left, i_dq_left, Global_Data.av.v_dc_left, Global_Data.av.omega_el_left);
		Global_Data.av.v_d_left = v_dq_ref_left.d;
		Global_Data.av.v_q_left = v_dq_ref_left.q;
		// calculate SVPMW dutycycles
		dutycyc_left = uz_Space_Vector_Modulation(v_dq_ref_left, Global_Data.av.v_dc_left, Global_Data.av.position_el_2pi_d3_1);
	}
};

static void control_right_motor() {

	if (Speed2Torque)
	{
		//Torque Mode

		Global_Data.rasv.n_ref_right_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_right, Global_Data.rasv.n_ref_right);

		// calculate reference voltages for current control
	    v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, Global_Data.rasv.i_dq_ref_right, i_dq_right, Global_Data.av.v_dc_right, Global_Data.av.omega_el_right);
	    Global_Data.av.v_d_right = v_dq_ref_right.d;
	    Global_Data.av.v_q_right = v_dq_ref_right.q;
	    // calculate duty cycles from reference dq voltages
	    dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_right, Global_Data.av.position_el_2pi_d4_1);
//	    da = dutycyc_right.DutyCycle_A;
//	    db = dutycyc_right.DutyCycle_B;
//	    dc = dutycyc_right.DutyCycle_C;
	}
	else
	{
		//Speed Mode
		// filter speed setpoint signal
		Global_Data.rasv.n_ref_right_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_ref_speed_right, Global_Data.rasv.n_ref_right);
		// calculate reference torque from speed ctrl of left motor
		Global_Data.rasv.M_ref_right = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_right, Global_Data.av.omega_mech_right, Global_Data.rasv.n_ref_right_filt);
		// calculate current setpoints i_dq_ref for left motor
		Global_Data.rasv.i_dq_ref_right = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_right,Global_Data.av.omega_mech_right, Global_Data.rasv.M_ref_right, Global_Data.av.v_dc_right, i_dq_right);

		// calculate reference voltages for current control
		v_dq_ref_right = uz_CurrentControl_sample(Global_Data.objects.current_ctrl_right, Global_Data.rasv.i_dq_ref_right, i_dq_right, Global_Data.av.v_dc_right, Global_Data.av.omega_el_right);

		// get integrator clamping flag from current control
		Global_Data.av.currentcontrol_clamping_right = uz_CurrentControl_get_ext_clamping(Global_Data.objects.current_ctrl_right);

		// set clamping of integrators of speed control when current control is clamped
		uz_SpeedControl_set_ext_clamping(Global_Data.objects.speed_ctrl_right, Global_Data.av.currentcontrol_clamping_right);

		// write v_dq_ref_left to Global_Data
		Global_Data.av.v_d_right = v_dq_ref_right.d;
		Global_Data.av.v_q_right = v_dq_ref_right.q;

		// calculate SVPMW dutycycles
		dutycyc_right = uz_Space_Vector_Modulation(v_dq_ref_right, Global_Data.av.v_dc_right, Global_Data.av.position_el_2pi_d4_1);
//	    da = dutycyc_right.DutyCycle_A;
//	    db = dutycyc_right.DutyCycle_B;
//	    dc = dutycyc_right.DutyCycle_C;
	}
};


static void deadbeat_right_motor(){
    /* Clarke transformation */
    u_alpha0 = 0.667f * (u_a0 - 0.5f * u_b0 - 0.5f * u_c0);
    u_beta0  = 0.667f * (0.866f * u_b0 - 0.866f * u_c0);

    /* Park transformation */
    ce = cosf(Global_Data.av.position_el_2pi_d4_1);
    se = sinf(Global_Data.av.position_el_2pi_d4_1);

    u_d0 = ce * u_alpha0 + se * u_beta0;
    u_q0 = -se * u_alpha0 + ce * u_beta0;

    /* last-step voltage */
    v_d0 = u_d0 * (Global_Data.av.v_dc_left * 0.5f);
    v_q0 = u_q0 * (Global_Data.av.v_dc_left * 0.5f);

    /* one step compensation for current measurement: from (k-1) to (k) */
    wrTs = Global_Data.av.omega_el_right * Global_Data.av.isr_samplerate_s;
    Ts_over_Ld = Global_Data.av.isr_samplerate_s / 0.0136f;
    Ts_over_Lq = Global_Data.av.isr_samplerate_s / 0.0136f;

    id_k = Ts_over_Ld * v_d0
         + (1.0f - Ts_over_Ld * 1.2f) * i_dq_right.d
         + 0.0136f * Global_Data.av.omega_el_right * Ts_over_Ld * i_dq_right.q;

    iq_k = Ts_over_Lq * v_q0
         + (1.0f - Ts_over_Lq * 1.2f) * i_dq_right.q
         - 0.0136f * Global_Data.av.omega_el_right * Ts_over_Lq * i_dq_right.d
         - Ts_over_Lq * Global_Data.av.omega_el_right * 0.140f;

    /* one step compensation for angle measurement */
    Theta_k = Global_Data.av.position_el_2pi_d4_1 + 1.0f * wrTs;

    /* deadbeat solution: from (k) to (k+1) */
    Ld_over_Ts = 0.0136f / Global_Data.av.isr_samplerate_s;
    Lq_over_Ts = 0.0136f / Global_Data.av.isr_samplerate_s;

    vd_ref = Ld_over_Ts * (i_dq_ref_right.d - id_k)
           + 1.2f * id_k
           - 0.0136f * Global_Data.av.omega_el_right * iq_k;

    vq_ref = Lq_over_Ts * (i_dq_ref_right.q - iq_k)
           + 1.2f * iq_k
           + 0.0136f * Global_Data.av.omega_el_right * id_k
           + Global_Data.av.omega_el_right * 0.140f;

    /* one step compensation for angle */
    Theta_k1 = Theta_k + wrTs;

    /* inverse Park transformation */
    ck1 = cosf(Theta_k1);
    sk1 = sinf(Theta_k1);

    v_alpha_ref = ck1 * vd_ref - sk1 * vq_ref;
    v_beta_ref  = sk1 * vd_ref + ck1 * vq_ref;

    /* transfer reference voltage into modulating voltage */
    inv_half_Vdc = 1.0f / (0.5f * Global_Data.av.v_dc_left);
    u_alpha = v_alpha_ref * inv_half_Vdc;
    u_beta  = v_beta_ref  * inv_half_Vdc;

    /* inverse Clarke transformation */
    u_a = u_alpha;
    u_b = -0.5f * u_alpha + 0.866f * u_beta;
    u_c = -0.5f * u_alpha - 0.866f * u_beta;

    /* common-mode injection (SVM-equivalent) */
    u_min = u_a;
    if (u_b < u_min) u_min = u_b;
    if (u_c < u_min) u_min = u_c;

    u_max = u_a;
    if (u_b > u_max) u_max = u_b;
    if (u_c > u_max) u_max = u_c;

    u_com = -0.5f * (u_min + u_max);

    u_a += u_com;
    u_b += u_com;
    u_c += u_com;

    /* saturation */
    if (u_a > 1.0f) u_a = 1.0f;
    else if (u_a < -1.0f) u_a = -1.0f;

    if (u_b > 1.0f) u_b = 1.0f;
    else if (u_b < -1.0f) u_b = -1.0f;

    if (u_c > 1.0f) u_c = 1.0f;
    else if (u_c < -1.0f) u_c = -1.0f;

    /* duty cycle */
    da = 0.5f * (u_a + 1.0f);
    db = 0.5f * (u_b + 1.0f);
    dc = 0.5f * (u_c + 1.0f);

    /* store modulating voltage */
    u_a0 = u_a;
    u_b0 = u_b;
    u_c0 = u_c;
}


static void deadtime_comp() {
	theta_i = Global_Data.av.position_el_2pi_d4_1 + UZ_PIf/2.0f;//
	theta_i = wrap_2pi(theta_i);

	if ((theta_i <= UZ_PIf / 6.0f) || (theta_i > 11.0f * UZ_PIf / 6.0f))
    {
        sec = 1;
    }
    else if ((theta_i > UZ_PIf / 6.0f) && (theta_i <= 3.0f * UZ_PIf / 6.0f))
    {
        sec = 2;
    }
    else if ((theta_i > 3.0f * UZ_PIf / 6.0f) && (theta_i <= 5.0f * UZ_PIf / 6.0f))
    {
        sec = 3;
    }
    else if ((theta_i > 5.0f * UZ_PIf / 6.0f) && (theta_i <= 7.0f * UZ_PIf / 6.0f))
    {
        sec = 4;
    }
    else if ((theta_i > 7.0f * UZ_PIf / 6.0f) && (theta_i <= 9.0f * UZ_PIf / 6.0f))
    {
        sec = 5;
    }
    else
    {
        sec = 6;
    }

	delt_U = k_dt_c * 0.000002f / Global_Data.av.isr_samplerate_s;

    switch (sec)
    {
        case 1:
            Ua_comp = delt_U;
            Ub_comp = -delt_U;
            Uc_comp = -delt_U;
            break;

        case 2:
            Ua_comp = delt_U;
            Ub_comp = delt_U;
            Uc_comp = -delt_U;
            break;

        case 3:
            Ua_comp = -delt_U;
            Ub_comp = delt_U;
            Uc_comp = -delt_U;
            break;

        case 4:
            Ua_comp = -delt_U;
            Ub_comp = delt_U;
            Uc_comp = delt_U;
            break;

        case 5:
            Ua_comp = -delt_U;
            Ub_comp = -delt_U;
            Uc_comp = delt_U;
            break;

        default:
            Ua_comp = delt_U;
            Ub_comp = -delt_U;
            Uc_comp = delt_U;
            break;
    }
    //Ua_comp = (Ua_comp + delt_U)/2.0f;
    //Ub_comp = (Ub_comp + delt_U)/2.0f;
    //Uc_comp = (Uc_comp + delt_U)/2.0f;

};

static void measured_to_si_values() {
// update position and speed from resolver
Global_Data.av.resolver_pl_outputs_d3_1 = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d3_1);

// calc motor angles and speeds with right orientation
//Measured with encoder
Global_Data.av.position_el_2pi_d3_1 = (2.0f * UZ_PIf) - Global_Data.av.resolver_pl_outputs_d3_1.position_el_2pi;
Global_Data.av.position_mech_2pi_d3_1 =  (2.0f * UZ_PIf) - Global_Data.av.resolver_pl_outputs_d3_1.position_mech_2pi;
//Estimation
/*
theta_e_left_est = (2.0f * UZ_PIf) - wrap_2pi(theta_e_right_est + Global_Data.av.polepairs_left * Global_Data.rasv.d4_to_d3_offset_mech);
theta_left_est = wrap_2pi(((2.0f * UZ_PIf)-theta_e_right_unwrap)/Global_Data.av.polepairs_left);
//Global_Data.av.position_el_2pi_d3_1 = theta_e_left_est;
//Global_Data.av.position_mech_2pi_d3_1 = theta_left_est;
*/

//Measured with encoder
Global_Data.av.omega_mech_left = -1.0f * Global_Data.av.resolver_pl_outputs_d3_1.omega_mech_rad_s * 4.0f; // *4.0f accounting for bit resolution bug in resolverIP 16bit vs 14bit is factor 4
Global_Data.av.omega_el_left = Global_Data.av.omega_mech_left * Global_Data.av.polepairs_left;
//Estimation
/*
w_left_est = -1.0f * (n_right_est * UZ_PIf/30.0f);
w_e_left_est = w_left_est * Global_Data.av.polepairs_left;
//Global_Data.av.omega_mech_left = w_left_est;
//Global_Data.av.omega_el_left = w_e_left_est;
*/

//Measured with encoder
Global_Data.av.n_mech_rpm_d3_1 = -1.0f * Global_Data.av.resolver_pl_outputs_d3_1.n_mech_rpm * 4.0f;
//Estimation
/*
n_left_est = -1.0f * n_right_est;
//Global_Data.av.n_mech_rpm_d3_1 = n_left_est;
*/

// Fake right position and speeds, if endat working delete this block

//Global_Data.av.omega_mech_right = Global_Data.av.resolver_pl_outputs_d3_1.omega_mech_rad_s * 4.0f;
//Global_Data.av.omega_el_right = Global_Data.av.omega_mech_right * Global_Data.av.polepairs_right;
//Global_Data.av.n_mech_rpm_d4_1 = Global_Data.av.resolver_pl_outputs_d3_1.n_mech_rpm * 4.0f;
//Global_Data.rasv.d4_to_d3_offset_el = Global_Data.av.polepairs_right * Global_Data.rasv.d4_to_d3_offset_mech;
//Global_Data.av.position_el_2pi_d4_1 =  wrap_2pi(Global_Data.av.resolver_pl_outputs_d3_1.position_el_2pi - Global_Data.rasv.d4_to_d3_offset_el);
//Global_Data.av.position_mech_2pi_d4_1 =  wrap_2pi(Global_Data.av.resolver_pl_outputs_d3_1.position_mech_2pi - Global_Data.rasv.d4_to_d3_offset_mech);

// update position and speed from EnDat on D4
update_endat_encoder_on_D4(&Global_Data);
Global_Data.av.omega_el_right = Global_Data.av.endat_software_pll_machine.electricalRotorSpeed;
Global_Data.av.omega_mech_right = Global_Data.av.omega_el_right / Global_Data.av.polepairs_right;
Global_Data.av.n_mech_rpm_d4_1 = Global_Data.av.endat_software_pll_machine.mechanicalRotorSpeed;
Global_Data.av.position_el_2pi_d4_1 = Global_Data.av.endat_machine.theta_elec;
Global_Data.av.position_mech_2pi_d4_1 = Global_Data.av.endat_machine.theta_mech;

// Torque Sensor measurement
Global_Data.av.torque = (Global_Data.aa.A1.me.ADC_B5 * 20.0f) + Global_Data.rasv.torque_offset; //positive q-current = positive torque | Burster 8656-5010: 10Nm/10V = 1Nm/1V -> to +-5V via torque box: 1Nm/0.5V -> 2Nm/1V -> *2.0f
Global_Data.av.torque_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_filter_torque, Global_Data.av.torque);

// assign inverter measurements - Conversion factors from Michi
Global_Data.av.i_a_left = (Global_Data.aa.A1.me.ADC_A1 * 92.713f) + 0.186f;
Global_Data.av.i_b_left = (Global_Data.aa.A1.me.ADC_A2 * 92.688f) + 0.159f;
Global_Data.av.i_c_left = (Global_Data.aa.A1.me.ADC_A3 * -92.861f) + 0.076f;
Global_Data.av.v_dc_left = (Global_Data.aa.A1.me.ADC_A4 * 4153.408f) - 0.138f;

Global_Data.av.i_a_right = (Global_Data.aa.A1.me.ADC_B8 * 92.593f) + 0.186f;
Global_Data.av.i_b_right = (Global_Data.aa.A1.me.ADC_B6 * 92.822f) + 0.229f;
Global_Data.av.i_c_right = (Global_Data.aa.A1.me.ADC_B7 * -92.681f) + 0.088f;
//
//
//Global_Data.av.v_dc_right = (Global_Data.aa.A1.me.ADC_B5  * 2004.1883f) -0.26683f;
Global_Data.av.v_dc_right = Global_Data.av.v_dc_left;
// assign measurements from global_data to motor control structs
i_abc_left.a = Global_Data.av.i_a_left;
i_abc_left.b = Global_Data.av.i_b_left;
i_abc_left.c = Global_Data.av.i_c_left;
i_abc_right.a = Global_Data.av.i_a_right;
i_abc_right.b = Global_Data.av.i_b_right;
i_abc_right.c = Global_Data.av.i_c_right;


};

static inline float wrap_2pi(float x) {
    float y = fmodf(x, 2.0f * (float)UZ_PIf);
    if (y < 0.0f) {
        y += 2.0f * (float)UZ_PIf;
    }
    return y;
}
