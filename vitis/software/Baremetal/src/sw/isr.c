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

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();
/*
//IP-Cores for 6 Phase FSC-MPC
extern uz_vsd_and_park_transformation_6phase_t* instance_vsd_and_park_transformation;
uz_3ph_dq_t dq_currents_vsd_and_park_transformation;
uz_6ph_alphabeta_t alpha_beta_x_y_currents_vsd_and_park_transformation;
uz_6ph_abc_t a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation;

extern float d_current_vsd_and_park_transformation;
extern float q_current_vsd_and_park_transformation;
extern float alpha_current_vsd_and_park_transformation;
extern float beta_current_vsd_and_park_transformation;
extern float x_current_vsd_and_park_transformation;
extern float y_current_vsd_and_park_transformation;
extern float a1_current_vsd_and_park_transformation;
extern float b1_current_vsd_and_park_transformation;
extern float c1_current_vsd_and_park_transformation;
extern float a2_current_vsd_and_park_transformation;
extern float b2_current_vsd_and_park_transformation;
extern float c2_current_vsd_and_park_transformation;


extern uz_delay_compensation_fcs_mpc_6phase_t* instance_delay_compensation_fcs_mpc_6phase_pmsm;
static struct uz_delay_compensation_fcs_mpc_6phase_AXI_values_t AXI_values_delay_compensation_fcs_mpc_6phase_pmsm={
    .last_applied_optimal_voltage_ud = 6.3f,
    .last_applied_optimal_voltage_uq = 5.3f,
    .last_applied_optimal_voltage_ux = 4.3f,
    .last_applied_optimal_voltage_uy = 3.3f,
    .id_measured = 1.2f,
    .iq_measured = 2.2f,
    .ix_measured = 3.2f,
    .iy_measured = 4.2f,
    .omega_m_measured = 1.1f
};
uz_6ph_idk1_iqk1_ixk1_iyk1_t idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm;

extern float idk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
extern float iqk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
extern float ixk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
extern float iyk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;


extern uz_phase_voltages_per_switching_state_fcs_mpc_6phase_t* instance_phase_voltages_per_switching_state_fcs_mpc_6phase;
static struct uz_phase_voltages_per_switching_state_fcs_mpc_6phase_AXI_values_t AXI_values_phase_voltages_per_switching_states_fcs_mpc_6phase={
    .theta_el_AXI=2.4f,
    .Index_AXI=46
};
uz_6ph_dvoltage_qvoltage_xvoltage_yvoltage_t d_q_x_y_voltages_per_switching_state;

extern float d_voltage_per_switching_state;
extern float q_voltage_per_switching_state;
extern float x_voltage_per_switching_state;
extern float y_voltage_per_switching_state;


extern uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_t* instance_prediction_and_cost_function_fcs_mpc_6phase_pmsm;
static struct uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_AXI_values_t AXI_values_prediction_and_cost_function_fcs_mpc_6phase_pmsm={
   .d_voltage_per_switching_state_AXI = 6.3f,
   .q_voltage_per_switching_state_AXI = 5.3f,
   .x_voltage_per_switching_state_AXI = 4.3f,
   .y_voltage_per_switching_state_AXI = 3.3f,
   .id_k_1_AXI = 1.2f,
   .iq_k_1_AXI = 2.2f,
   .ix_k_1_AXI = 3.2f,
   .iy_k_1_AXI = 4.2f,
   .omega_m_measured_AXI = 1.1f
};

uz_6ph_idref_iqref_ixref_iyref_t updated_values_idref_iqref_ix_ref_iy_ref={
   .id_ref=0.0f,
   .iq_ref=0.0f,
   .ix_ref=0.0f,
   .iy_ref=0.0f
};

extern float J_AXI;


extern uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_t* instance_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm;
static struct uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_AXI_values_t AXI_values_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm={
    .J_in_AXI = 35.3f,
    .Index_in_AXI = 23,
    .d_phase_voltage_per_switchimng_state_AXI = 22.4f,
    .q_phase_voltage_per_switchimng_state_AXI = 33.2f,
    .x_phase_voltage_per_switchimng_state_AXI = 56.0f,
    .y_phase_voltage_per_switchimng_state_AXI = 43.7f,
    .valid_in_AXI = 1
};
uz_6ph_optimal_dvoltage_qvoltage_xvoltage_yvoltage_t last_applied_optimal_voltages;

extern float last_applied_optimal_voltage_d;
extern float last_applied_optimal_voltage_q;
extern float last_applied_optimal_voltage_x;
extern float last_applied_optimal_voltage_y;
*/

// IP Cores for 6 Phase FCS MPC parallel 8
extern uz_vsd_8_t* test_instance_vsd_8;
uz_6ph_abc_t a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation;
extern float a1_current_vsd_and_park_transformation;
extern float b1_current_vsd_and_park_transformation;
extern float c1_current_vsd_and_park_transformation;
extern float a2_current_vsd_and_park_transformation;
extern float b2_current_vsd_and_park_transformation;
extern float c2_current_vsd_and_park_transformation;

extern uz_prediction_and_cost_function_8_t* test_instance_prediction_and_cost_function_8;
uz_6ph_idref_iqref_ixref_iyref_t updated_values={
	.id_ref=0.0f,
	.iq_ref=0.0f,
	.ix_ref=0.0f,
	.iy_ref=0.0f
 };

extern uz_delay_compensation_8_t* test_instance_delay_compensation_8;
/*
uz_6ph_idk1_iqk1_ixk1_iyk1_t idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm;
extern float idk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
extern float iqk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
extern float ixk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
extern float iyk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm;
*/

//extern uz_min_cost_function_8_t* test_instance_min_cost_function_8;

/*
float theta_el_measured;
float theta_el_offset;
float theta_el;

uz_6ph_dq_t d_q_x_y_0p_0n_currents;
*/

extern uz_incrementalEncoder_t* test_instance_Encoder;

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

/*
    //IP-Cores for 6 Phase FSC-MPC
    dq_currents_vsd_and_park_transformation = uz_vsd_and_park_transformation_6phase_get_id_iq(instance_vsd_and_park_transformation);
    d_current_vsd_and_park_transformation = dq_currents_vsd_and_park_transformation.d;
    q_current_vsd_and_park_transformation = dq_currents_vsd_and_park_transformation.q;

    alpha_beta_x_y_currents_vsd_and_park_transformation = uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus(instance_vsd_and_park_transformation);
    alpha_current_vsd_and_park_transformation = alpha_beta_x_y_currents_vsd_and_park_transformation.alpha;
    beta_current_vsd_and_park_transformation = alpha_beta_x_y_currents_vsd_and_park_transformation.beta;
    x_current_vsd_and_park_transformation = alpha_beta_x_y_currents_vsd_and_park_transformation.x;
    y_current_vsd_and_park_transformation = alpha_beta_x_y_currents_vsd_and_park_transformation.y;

    a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation = uz_vsd_and_park_transformation_6phase_get_ia1_ib1_ic1_ia2_ib2_ic2(instance_vsd_and_park_transformation);
    a1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.a1;
    b1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.b1;
    c1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.c1;
    a2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.a2;
    b2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.b2;
    c2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.c2;
*/

/*    //crude over current protection
    if((fabs(a1_current_vsd_and_park_transformation) > 15.0f || fabs(b1_current_vsd_and_park_transformation) > 15.0f || fabs(c1_current_vsd_and_park_transformation) > 15.0f || fabs(a2_current_vsd_and_park_transformation) > 15.0f || fabs(b2_current_vsd_and_park_transformation) > 15.0f || fabs(c2_current_vsd_and_park_transformation) > 15.0f) && (fabs(updated_values_idref_iqref_ix_ref_iy_ref.id_ref) > 15.0f || fabs(updated_values_idref_iqref_ix_ref_iy_ref.iq_ref) > 15.0f || fabs(updated_values_idref_iqref_ix_ref_iy_ref.ix_ref) > 15.0f || fabs(updated_values_idref_iqref_ix_ref_iy_ref.iy_ref) > 15.0f)) {
    	uz_assert(0);
    	}
*/
/*
    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_idref_iqref_ixref_iyref_update(instance_prediction_and_cost_function_fcs_mpc_6phase_pmsm, updated_values_idref_iqref_ix_ref_iy_ref);


    uz_delay_compensation_fcs_mpc_6phase_pmsm_set_AXI_values(instance_delay_compensation_fcs_mpc_6phase_pmsm, AXI_values_delay_compensation_fcs_mpc_6phase_pmsm);

    idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm = uz_delay_compensation_fcs_mpc_6phase_pmsm_read_idk1_iqK1_ixk1_iyk1(instance_delay_compensation_fcs_mpc_6phase_pmsm);
    idk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.id_k_1;
    iqk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.iq_k_1;
    ixk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.ix_k_1;
    iyk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.iy_k_1;


    uz_phase_voltages_per_switching_state_fcs_mpc_6phase_set_AXI_values(instance_phase_voltages_per_switching_state_fcs_mpc_6phase, AXI_values_phase_voltages_per_switching_states_fcs_mpc_6phase);

    d_q_x_y_voltages_per_switching_state = uz_phase_voltages_per_switching_state_fcs_mpc_6phase_read_dvoltage_qvoltage_xvoltage_yvoltage(instance_phase_voltages_per_switching_state_fcs_mpc_6phase);
    d_voltage_per_switching_state = d_q_x_y_voltages_per_switching_state.d;
    q_voltage_per_switching_state = d_q_x_y_voltages_per_switching_state.q;
    x_voltage_per_switching_state = d_q_x_y_voltages_per_switching_state.x;
	y_voltage_per_switching_state = d_q_x_y_voltages_per_switching_state.y;

    uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_set_AXI_values(instance_prediction_and_cost_function_fcs_mpc_6phase_pmsm, AXI_values_prediction_and_cost_function_fcs_mpc_6phase_pmsm);
    J_AXI = uz_prediction_and_cost_function_fcs_mpc_6phase_pmsm_get_J_AXI(instance_prediction_and_cost_function_fcs_mpc_6phase_pmsm);


    uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_set_AXI_values(instance_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm, AXI_values_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm);

    last_applied_optimal_voltages = uz_min_cost_function_and_vopt_FCS_MPC_6Phase_PMSM_read_last_applied_optimal_voltage_d_q_x_y(instance_min_cost_function_and_vopt_fcs_mpc_6phase_pmsm);
    last_applied_optimal_voltage_d = last_applied_optimal_voltages.d;
    last_applied_optimal_voltage_q = last_applied_optimal_voltages.q;
    last_applied_optimal_voltage_x = last_applied_optimal_voltages.x;
    last_applied_optimal_voltage_y = last_applied_optimal_voltages.y;
*/

    // IP-Cores FCS MPC 6 Phase parallel 8
    uz_prediction_and_cost_function_8_idref_iqref_ixref_iyref_update(test_instance_prediction_and_cost_function_8, updated_values);

    a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation = uz_vsd_8_get_ia1_ib1_ic1_ia2_ib2_ic2(test_instance_vsd_8);
    a1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.a1;
    b1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.b1;
    c1_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.c1;
    a2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.a2;
    b2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.b2;
    c2_current_vsd_and_park_transformation = a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation.c2;

    /*
    theta_el_measured=uz_incrementalEncoder_get_theta_el(test_instance_Encoder);
    theta_el=theta_el_measured-theta_el_offset;

    d_q_x_y_0p_0n_currents=uz_transformation_asym30deg_6ph_abc_to_dq(a1_b1_c1_a2_b2_c2_currents_vsd_and_park_transformation, theta_el);
*/

    //crude over current protection
      if((fabs(a1_current_vsd_and_park_transformation) > 15.0f || fabs(b1_current_vsd_and_park_transformation) > 15.0f || fabs(c1_current_vsd_and_park_transformation) > 15.0f || fabs(a2_current_vsd_and_park_transformation) > 15.0f || fabs(b2_current_vsd_and_park_transformation) > 15.0f || fabs(c2_current_vsd_and_park_transformation) > 15.0f) && (fabs(updated_values.id_ref) > 15.0f || fabs(updated_values.iq_ref) > 15.0f || fabs(updated_values.ix_ref) > 15.0f || fabs(updated_values.iy_ref) > 15.0f)) {
      	uz_assert(0);
      	}
/*
      idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm=uz_delay_compensation_8_read_idk1_iqK1_ixk1_iyk1(test_instance_delay_compensation_8);
      idk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.id_k_1;
      iqk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.iq_k_1;
      ixk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.ix_k_1;
      iyk1_predicted_current_delay_compensation_fcs_mpc_6phase_pmsm = idk1_iqk1_ixk1_iyk1_currents_delay_compensation_fcs_mpc_6phase_pmsm.iy_k_1;
*/
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
