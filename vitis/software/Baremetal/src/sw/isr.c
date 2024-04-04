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

// Global variable structure
extern DS_Data Global_Data;

// =============== Declares for PMSM 1 =============== //
struct uz_resolver_pl_interface_outputs_t Resolver_outputs = {0};
// FOC Instances and Configs
extern uz_SpeedControl_t* SC_instance_1;
extern uz_SetPoint_t* SP_instance_1;
extern uz_CurrentControl_t* CC_instance_1;
extern struct uz_PMSM_t config_PMSM_1;
extern uz_HarmonicCurrentInjection_t* HCI_instance_5th_1;
extern uz_HarmonicCurrentInjection_t* HCI_instance_7th_1;

// Inverter Measurement
struct uz_3ph_abc_t v_abc_Volts_1 	= {0};
struct uz_3ph_dq_t v_dq_Volts_1 	= {0};
struct uz_3ph_dq_t v_dq_ref_Volts_1 = {0};
struct uz_3ph_abc_t i_abc_Amps_1 	= {0};
struct uz_3ph_dq_t i_dq_Amps_1 		= {0};
struct uz_3ph_dq_t i_dq_ref_Amps_1 	= {0};
float v_DC_Volts_1 					= 24.0f;
float i_DC_Amps_1 					= 0.0f;

// FOC Variables
float n_ref_rpm_1 					= 0.0f;
float M_ref_Nm_1 					= 0.0f;
float omega_m_rad_per_sec_1 		= 0.0f;
float omega_el_rad_per_sec_1 		= 0.0f;
float theta_el_rad_1 				= 0.0f;
float theta_el_offset_1 			= 1.1f;
struct uz_DutyCycle_t output_1 		= {0};

// Controller Settings
float Kp_speed_1 					= 0.005f;
float Ki_speed_1 					= 0.01f;
//float Kp_id_1 = 0.3f;
//float Ki_id_1 = 230.0f;
//float Kp_iq_1 = 0.5f;
//float Ki_iq_1 = 230.0f;

// Harmonic Current Injection
int mode = 0;
struct uz_3ph_dq_t i_dqn_ref_5th_Amps_1 = {0};
struct uz_3ph_dq_t i_dqn_ref_7th_Amps_1 = {0};
struct uz_3ph_dq_t i_dqn_filtered_5th_Amps_1 = {0};
struct uz_3ph_dq_t i_dqn_filtered_7th_Amps_1 = {0};
struct uz_3ph_dq_t v_dq_ref_5th_Volts_1 = {0};
struct uz_3ph_dq_t v_dq_ref_7th_Volts_1 = {0};
struct uz_3ph_dq_t v_dq_ref_HCI_Volts_1 = {0};

// =============== Declares for PMSM 2 =============== //

// FOC Instances and Configs
extern uz_SpeedControl_t* SC_instance_2;
extern uz_SetPoint_t* SP_instance_2;
extern uz_CurrentControl_t* CC_instance_2;
extern struct uz_PMSM_t config_PMSM_2;

// Inverter Measurement
struct uz_3ph_abc_t v_abc_Volts_2 	= {0};
struct uz_3ph_dq_t v_dq_Volts_2 	= {0};
struct uz_3ph_dq_t v_dq_ref_Volts_2 = {0};
struct uz_3ph_abc_t i_abc_Amps_2 	= {0};
struct uz_3ph_dq_t i_dq_Amps_2 		= {0};
struct uz_3ph_dq_t i_dq_ref_Amps_2 	= {0};
float v_DC_Volts_2 					= 12.0f;
float i_DC_Amps_2 					= 0.0f;

// FOC Variables
float n_ref_rpm_2 					= 0.0f;
float M_ref_Nm_2 					= 0.0f;
float omega_m_rad_per_sec_2 		= 0.0f;
float omega_el_rad_per_sec_2 		= 0.0f;
float theta_el_rad_2 				= 0.0f;
float theta_el_offset_2 			= 1.4f;
struct uz_DutyCycle_t output_2 		= {0};
uz_3ph_dq_t flux_approx             = {0};
uz_3ph_dq_t flux_reference          = {0};
float K_p_id                        = 0.0f;
float K_p_iq                        = 0.0f;
// Controller Settings
float Kp_speed_2 					= 0.2f;
float Ki_speed_2 					= 0.25f;

//Stuff

uint32_t setpoint_index				= 0U;
uint64_t old_uptime					= 0U;
float start_marker					= 0.0f;
float id_setpoints[22]={
#include "id_setpoints.csv"
};

float iq_setpoints[22]={
#include "iq_setpoints.csv"
};
extern bool select_automatic_idiq;
extern float PMSM_rated_current_1;
uint32_t Fehlerfall  = 0U;
extern bool select_misalignment;
extern uz_3ph_dq_t i_dq_ref_java_Amps_1;
//DDPG Stuff
float observation_ip_9n[9U] = {0};
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
    update_speed_and_position_of_encoder_on_D5_1(&Global_Data);

    if( (select_automatic_idiq) ){
    	start_marker=1.0f;
    	i_dq_ref_Amps_1.d = id_setpoints[setpoint_index];
    	i_dq_ref_Amps_1.q = iq_setpoints[setpoint_index] * PMSM_rated_current_1;

    	// step throught the array
    	uint64_t current_uptime=uz_SystemTime_GetInterruptCounter();
    	if(current_uptime>(old_uptime +300 ) ){
    		old_uptime=current_uptime;

    		if(setpoint_index<21){
    			setpoint_index++;
    		}else{
    			setpoint_index=0;
    			select_automatic_idiq=false;
    			start_marker=0.0f;
    		}



    	}
    }else{
    	i_dq_ref_Amps_1=i_dq_ref_java_Amps_1;
    }

    // Set tristate to false
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);

    // Read Measurement Data of First Inverter
    v_abc_Volts_1.a = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
    v_abc_Volts_1.b = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
    v_abc_Volts_1.c = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
    v_DC_Volts_1 	= Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    i_abc_Amps_1.a  = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
    i_abc_Amps_1.b  = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
    i_abc_Amps_1.c  = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
    i_DC_Amps_1     = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);

    // Read Measurement of Second Inverter
    v_abc_Volts_2.a = Global_Data.aa.A2.me.ADC_B8 * 12.0f;
    v_abc_Volts_2.b = Global_Data.aa.A2.me.ADC_B7 * 12.0f;
    v_abc_Volts_2.c = Global_Data.aa.A2.me.ADC_B6 * 12.0f;
    v_DC_Volts_2 	= Global_Data.aa.A2.me.ADC_A1 * 12.0f;
    i_abc_Amps_2.a  = Global_Data.aa.A2.me.ADC_A4 * 12.5f;
    i_abc_Amps_2.b  = Global_Data.aa.A2.me.ADC_A3 * 12.5f;
    i_abc_Amps_2.c  = Global_Data.aa.A2.me.ADC_A2 * 12.5f;
    i_DC_Amps_2     = Global_Data.aa.A2.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);

    // Get current state
    platform_state_t current_state=ultrazohm_state_machine_get_state();

    // Enable Inverter Adapter Hardware
    if (current_state == running_state || current_state == control_state) {
    	// enable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    } else {
        // disable inverter adapter hardware
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
        uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    }

    // Calculation of Signals for FOC for PMSM 1
    omega_m_rad_per_sec_1 = Global_Data.av.mechanicalRotorSpeed_filtered_1*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec_1 = omega_m_rad_per_sec_1*config_PMSM_1.polePairs;
    Global_Data.av.omega_el_1 = omega_el_rad_per_sec_1;
    theta_el_rad_1 = Global_Data.av.theta_elec_1 - Global_Data.av.theta_offset_1;
    if(select_misalignment==true) {
    	theta_el_rad_1 += 5.0f * (M_PI / 180.0f);
    }
    //Anglelead
    theta_el_rad_1 += (1.5f * omega_el_rad_per_sec_1 ) / UZ_PWM_FREQUENCY;
    Global_Data.av.theta_mech_1 = theta_el_rad_1 / 4.0f;
    i_dq_Amps_1 = uz_transformation_3ph_abc_to_dq(i_abc_Amps_1, theta_el_rad_1);
    v_dq_Volts_1 = uz_transformation_3ph_abc_to_dq(v_abc_Volts_1, theta_el_rad_1);



    // Calculation of Signals for FOC for PMSM 2
    Resolver_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4);
    Global_Data.av.mechanicalRotorSpeed_2 = Resolver_outputs.n_mech_rpm;
    Global_Data.av.mechanicalRotorSpeed_filtered_2 = Resolver_outputs.n_mech_rpm;
    omega_m_rad_per_sec_2 = Resolver_outputs.omega_mech_rad_s;
    omega_el_rad_per_sec_2 = omega_m_rad_per_sec_2 * config_PMSM_2.polePairs;
    Global_Data.av.omega_el_2 = omega_el_rad_per_sec_2;
    theta_el_rad_2 = Resolver_outputs.position_el_2pi;
    //Anglelead
    theta_el_rad_2 += (1.5f * omega_el_rad_per_sec_2 ) / UZ_PWM_FREQUENCY;
    i_dq_Amps_2 = uz_transformation_3ph_abc_to_dq(i_abc_Amps_2, theta_el_rad_2);
    v_dq_Volts_2 = uz_transformation_3ph_abc_to_dq(v_abc_Volts_2, theta_el_rad_2);

    if (current_state==control_state)
    {
    	// Field Oriented Control of PMSM 1
    	//M_ref_Nm_1 = uz_SpeedControl_sample(SC_instance_1, omega_m_rad_per_sec_1, n_ref_rpm_1);
    	//i_dq_ref_Amps_1 = uz_SetPoint_sample(SP_instance_1, omega_m_rad_per_sec_1, M_ref_Nm_1, v_DC_Volts_1, i_dq_Amps_1);

        //Approximate psid and psiq and set new kpd and kpq
    	flux_approx = uz_approximate_flux_step(Global_Data.objects.approximate_flux_instance, i_dq_Amps_1);
    	uz_CurrentControl_set_flux_approx(CC_instance_1, flux_approx);
    	flux_reference = uz_approximate_flux_reference_step(Global_Data.objects.approximate_flux_instance,i_dq_ref_Amps_1,i_dq_Amps_1);
        K_p_id = uz_CurrentControl_Kp_id_adjustment_step(Global_Data.objects.Kp_id_adjustment_instance,i_dq_ref_Amps_1, i_dq_Amps_1, flux_reference, flux_approx);
        K_p_iq = uz_CurrentControl_Kp_iq_adjustment_step(Global_Data.objects.Kp_iq_adjustment_instance,i_dq_ref_Amps_1, i_dq_Amps_1, flux_reference, flux_approx);
        uz_CurrentControl_set_Kp_id(CC_instance_1, K_p_id);
        uz_CurrentControl_set_Kp_iq(CC_instance_1, K_p_iq);
    	v_dq_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_1, i_dq_ref_Amps_1, i_dq_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
    	i_dqn_filtered_5th_Amps_1 = uz_HarmonicCurrentInjection_filter(HCI_instance_5th_1, i_abc_Amps_1, theta_el_rad_1);
    	i_dqn_filtered_7th_Amps_1 = uz_HarmonicCurrentInjection_filter(HCI_instance_7th_1, i_abc_Amps_1, theta_el_rad_1);
    	uz_HarmonicCurrentInjection_set_filters(HCI_instance_5th_1, omega_el_rad_per_sec_1);
    	uz_HarmonicCurrentInjection_set_filters(HCI_instance_7th_1, omega_el_rad_per_sec_1);
    	switch (mode)
    	{
    	default:
    		output_1 = uz_Space_Vector_Modulation(v_dq_ref_Volts_1, v_DC_Volts_1, theta_el_rad_1);
    		break;
		case 1:
			v_dq_ref_HCI_Volts_1.d = v_dq_ref_Volts_1.d +  v_dq_ref_5th_Volts_1.d + v_dq_ref_7th_Volts_1.d;
			v_dq_ref_HCI_Volts_1.q = v_dq_ref_Volts_1.q +  v_dq_ref_5th_Volts_1.q + v_dq_ref_7th_Volts_1.q;
			v_dq_ref_5th_Volts_1 = uz_HarmonicCurrentInjection_sample(HCI_instance_5th_1, i_dqn_ref_5th_Amps_1, i_dqn_filtered_5th_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1, theta_el_rad_1);
			v_dq_ref_7th_Volts_1 = uz_HarmonicCurrentInjection_sample(HCI_instance_7th_1, i_dqn_ref_7th_Amps_1, i_dqn_filtered_7th_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1, theta_el_rad_1);
			output_1 = uz_Space_Vector_Modulation(v_dq_ref_HCI_Volts_1, v_DC_Volts_1, theta_el_rad_1);
			break;
    	}
    	Global_Data.rasv.halfBridge1DutyCycle = output_1.DutyCycle_A;
    	Global_Data.rasv.halfBridge2DutyCycle = output_1.DutyCycle_B;
    	Global_Data.rasv.halfBridge3DutyCycle = output_1.DutyCycle_C;

    	// Field Oriented Control of PMSM 2
        M_ref_Nm_2 = uz_SpeedControl_sample(SC_instance_2, omega_m_rad_per_sec_2, n_ref_rpm_2);
        i_dq_ref_Amps_2 = uz_SetPoint_sample(SP_instance_2, omega_m_rad_per_sec_2, M_ref_Nm_2, v_DC_Volts_2, i_dq_Amps_2);
       	v_dq_ref_Volts_2 = uz_CurrentControl_sample(CC_instance_2, i_dq_ref_Amps_2, i_dq_Amps_2, v_DC_Volts_2, omega_el_rad_per_sec_2);
       	output_2 = uz_Space_Vector_Modulation(v_dq_ref_Volts_2, v_DC_Volts_2, theta_el_rad_2);
       	Global_Data.rasv.halfBridge4DutyCycle = output_2.DutyCycle_A;
       	Global_Data.rasv.halfBridge5DutyCycle = output_2.DutyCycle_B;
       	Global_Data.rasv.halfBridge6DutyCycle = output_2.DutyCycle_C;

    }
    else
    {
    	// Set tristate
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);

    	// Reset speed and current control
    	uz_SpeedControl_reset(SC_instance_1);
    	uz_CurrentControl_reset(CC_instance_1);
    	uz_SpeedControl_reset(SC_instance_2);
    	uz_CurrentControl_reset(CC_instance_2);
    }

    // Set duty cycles for two-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    // Update Javascope
    JavaScope_update(&Global_Data);

    // Inverter 1 safety
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 1U;
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
        //ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 2U;
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 3U;
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 4U;
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 5U;
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 6U;
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 7U;
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 8U;
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 9U;
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 10U;
    }

    // Inverter 2 safety
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 11U;
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L1) {
    	//ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 12U;
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 13U;
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 14U;
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H3) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 15U;
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L3) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 16U;
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d2.OC_L1) {
    	ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 17U;
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d2.OC_H1) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 18U;
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d2.OC_L2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 19U;
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d2.OC_H2) {
        ultrazohm_state_machine_set_error(true);
    	Fehlerfall = 20U;
    }

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
