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
#include "../uz/uz_ParameterID/uz_ParameterID.h"


// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

// ======================= PMSM 1 ======================= //
// --------------- Pointers to instances ---------------- //
extern struct uz_PMSM_t config_PMSM_1;
extern uz_SpeedControl_t* SC_instance_1;
extern uz_SetPoint_t* SP_instance_1;
extern uz_CurrentControl_t* CC_instance_1;
extern uz_encoder_offset_estimation_t* encoder_offset_obj_1;
extern uz_wavegen_chirp* chirp_instance_1;

// ---------------- Inverter Measurement ---------------- //
struct uz_3ph_abc_t v_abc_Volts_1				= {0};
float v_DC_Volts_1 								= 24.0f;
struct uz_3ph_abc_t i_abc_Amps_1 				= {0};
float i_DC_Amps_1 								= 0.0f;

// --------- Field Oriented Control and Signals --------- //
float omega_m_rad_per_sec_1 					= 0.0f;
float omega_el_rad_per_sec_1 					= 0.0f;
float theta_el_rad_1 							= 0.0f;
float theta_el_offset_1 						= 1.1f;
struct uz_3ph_dq_t 	i_dq_Amps_1 				= {0};
struct uz_3ph_alphabeta_t i_alphabeta_Amps_1 	= {0};
struct uz_3ph_dq_t 	v_dq_Volts_1 				= {0};
float n_ref_rpm_1 								= 0.0f;
float M_ref_Nm_1 								= 0.0f;
struct uz_3ph_dq_t i_dq_ref_Amps_1 				= {0};
struct uz_3ph_dq_t 	v_dq_ref_Volts_1 			= {0};
struct uz_DutyCycle_t output_1 					= {0};

// ---------------- Controller Settings ----------------- //
float Kp_speed_1 								= 0.01f;
float Ki_speed_1 								= 1.0f;
float Kp_id_1 									= 0.3f; 	//= 1.47f;
float Ki_id_1 									= 230.0f; 	//= 830.0f;
float Kp_iq_1 									= 0.5f; 	//= 8.17f;
float Ki_iq_1 									= 230.0f; 	//= 830.0f;


// ------------------- Wavegen Chirp -------------------- //
bool enable_excitation 							= false;
float excitation_amplitude 						= 0.0f;
float sampling_time 							= 1.0f/25.0e3f;

// ======================= PMSM 2 ======================= //
// --------------- Pointers to instances ---------------- //
extern struct uz_PMSM_t config_PMSM_2;
extern uz_SpeedControl_t* SC_instance;
extern uz_SetPoint_t* SP_instance;
extern uz_CurrentControl_t* CC_instance_dq;
extern uz_encoder_offset_estimation_t* encoder_offset_obj_2;

// ---------------- Inverter Measurement ---------------- //
struct uz_3ph_abc_t v_abc_Volts_2 				= {0};
float v_DC_Volts_2 								= 24.0f;
struct uz_3ph_abc_t i_abc_Amps_2 				= {0};
float i_DC_Amps_2 								= 0.0f;

// --------- Field Oriented Control and Signals --------- //
float omega_m_rad_per_sec_2 					= 0.0f;
float omega_el_rad_per_sec_2 					= 0.0f;
float theta_el_rad_2 							= 0.0f;
float theta_el_offset_2 						= 1.54f;
struct uz_3ph_dq_t i_dq_Amps_2 					= {0};
struct uz_3ph_dq_t v_dq_Volts_2 				= {0};
float n_ref_rpm_2 								= 0.0f;
float M_ref_Nm_2 								= 0.0f;
struct uz_3ph_dq_t v_dq_ref_Volts_2 			= {0};
struct uz_3ph_dq_t i_dq_ref_Amps_2 				= {0};
struct uz_DutyCycle_t output_2 					= {0};


// ---------------- Controller Settings ----------------- //
float Kp_speed_2 								= 0.1f;
float Ki_speed_2 								= 1.0f;
float Kp_id_2 									= 0.3f;
float Ki_id_2 									= 230.0f;
float Kp_iq_2 									= 0.5f;
float Ki_iq_2 									= 230.0f;

// ---------------- induced voltage ----------------- //
struct uz_3ph_dq_t v_ind_dq_Volts_2 			= {0};
struct uz_3ph_dq_t v_ind_dq_filt_Volts_2 			= {0};
float r_s_2 									= 0.023f;
extern uz_IIR_Filter_t* LP_instance_ud_ind_2;
extern uz_IIR_Filter_t* LP_instance_uq_ind_2;
struct uz_3ph_dq_t psi_dq_mVoltseconds_2 			= {0};

// ======================= Others ======================= //
float error_type = 0.0f;
int counter = 1;
float M_meas_Nm = 0.0f;
extern uz_ParameterID_Data_t ParaID_Data;
extern uz_ParameterID_t* ParameterID;
struct uz_3ph_dq_t ParaID_v_dq = { 0 };
struct uz_DutyCycle_t ParaID_DutyCycle = { 0 };

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

    // Read Measurement from ADCs and Encoder
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5_1(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_2(&Global_Data);
    update_speed_and_position_of_encoder_on_D5_3(&Global_Data);
    M_meas_Nm = Global_Data.aa.A3.me.ADC_A4 * 2.0f;

    // Tristate Inverters
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, false, false, false);

    // Read Measurement Data of first Inverter Card
    v_abc_Volts_1.a = Global_Data.aa.A1.me.ADC_B8 * 12.0f;
    v_abc_Volts_1.b = Global_Data.aa.A1.me.ADC_B7 * 12.0f;
    v_abc_Volts_1.c = Global_Data.aa.A1.me.ADC_B6 * 12.0f;
    v_DC_Volts_1 	= Global_Data.aa.A1.me.ADC_A1 * 12.0f;
    i_abc_Amps_1.a  = Global_Data.aa.A1.me.ADC_A4 * 12.5f;
    i_abc_Amps_1.b  = Global_Data.aa.A1.me.ADC_A3 * 12.5f;
    i_abc_Amps_1.c  = Global_Data.aa.A1.me.ADC_A2 * 12.5f;
    i_DC_Amps_1     = Global_Data.aa.A1.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);

    // Read Measurement Data of second Inverter Card
    ParaID_Data.ActualValues.I_abc.a = Global_Data.aa.A2.me.ADC_B8 * 12.0f;
    ParaID_Data.ActualValues.I_abc.b = Global_Data.aa.A2.me.ADC_B7 * 12.0f;
    ParaID_Data.ActualValues.I_abc.c = Global_Data.aa.A2.me.ADC_B6 * 12.0f;
    ParaID_Data.ActualValues.V_DC 	= Global_Data.aa.A2.me.ADC_A1 * 12.0f;
    ParaID_Data.ActualValues.V_abc.a  = Global_Data.aa.A2.me.ADC_A4 * 12.5f;
    ParaID_Data.ActualValues.V_abc.b  = Global_Data.aa.A2.me.ADC_A3 * 12.5f;
    ParaID_Data.ActualValues.V_abc.c  = Global_Data.aa.A2.me.ADC_A2 * 12.5f;
    i_DC_Amps_2     = Global_Data.aa.A2.me.ADC_B5 * 12.5f;
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);

    // Get Current State
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

    // Calculation of Signals for FOC of PMSM 1
    omega_m_rad_per_sec_1 = Global_Data.av.mechanicalRotorSpeed_filtered_1*(2.0f*M_PI)/60.0f;
    omega_el_rad_per_sec_1 = omega_m_rad_per_sec_1*config_PMSM_1.polePairs;
    Global_Data.av.omega_el_1 = omega_el_rad_per_sec_1;
    theta_el_rad_1 = Global_Data.av.theta_elec_1 - Global_Data.av.theta_offset_1;
    i_dq_Amps_1 = uz_transformation_3ph_abc_to_dq(i_abc_Amps_1, theta_el_rad_1);
    v_dq_Volts_1 = uz_transformation_3ph_abc_to_dq(v_abc_Volts_1, theta_el_rad_1);

    // Calculation of Signals for FOC of PMSM 2
    ParaID_Data.ActualValues.omega_m = Global_Data.av.mechanicalRotorSpeed_filtered_2*(2.0f*M_PI)/60.0f;
    ParaID_Data.ActualValues.omega_el = omega_m_rad_per_sec_2*config_PMSM_2.polePairs;
    Global_Data.av.omega_el_2 = omega_el_rad_per_sec_2;
    ParaID_Data.ActualValues.theta_el = Global_Data.av.theta_elec_2 - theta_el_offset_2;
    ParaID_Data.ActualValues.i_dq = uz_transformation_3ph_abc_to_dq(ParaID_Data.ActualValues.I_abc, ParaID_Data.ActualValues.theta_el);
    ParaID_Data.ActualValues.v_dq = uz_transformation_3ph_abc_to_dq(ParaID_Data.ActualValues.V_abc, ParaID_Data.ActualValues.theta_el);
// =============== Offset Estimation =============== //
//    // Offset Estimation
//    Global_Data.av.U_q = v_dq_ref_Volts_1.q;                                              // write controller output ref voltage to global data
// =============== Offset Estimation =============== //

    // Enable Control
    if (current_state==control_state)
    {

    	    uz_ParameterID_step(ParameterID, &ParaID_Data);
    		// Field Oriented Control of PMSM 1 - speed-controlled
    		M_ref_Nm_1 = uz_SpeedControl_sample(SC_instance_1, omega_m_rad_per_sec_1, n_ref_rpm_1);
    		i_dq_ref_Amps_1 = uz_SetPoint_sample(SP_instance_1, omega_m_rad_per_sec_1, M_ref_Nm_1, v_DC_Volts_1, i_dq_Amps_1);
			v_dq_ref_Volts_1 = uz_CurrentControl_sample(CC_instance_1, i_dq_ref_Amps_1, i_dq_Amps_1, v_DC_Volts_1, omega_el_rad_per_sec_1);
			output_1 = uz_Space_Vector_Modulation(v_dq_ref_Volts_1, v_DC_Volts_1, theta_el_rad_1);

			// Set DutyCycles of PMSM 1
			Global_Data.rasv.halfBridge1DutyCycle = output_1.DutyCycle_A;
			Global_Data.rasv.halfBridge2DutyCycle = output_1.DutyCycle_B;
			Global_Data.rasv.halfBridge3DutyCycle = output_1.DutyCycle_C;

			// Field Oriented Control of PMSM 2 - current-controlled
	        ParaID_v_dq = uz_ParameterID_Controller(&ParaID_Data, CC_instance_dq, SC_instance, SP_instance);
	        //If Gate-output is on the first 6 DIG-IO Pins. Otherwise use different PWM object
	        ParaID_DutyCycle = uz_ParameterID_generate_DutyCycle(&ParaID_Data, ParaID_v_dq, Global_Data.objects.pwm_d1_pin_6_to_11);
	        Global_Data.rasv.halfBridge1DutyCycle = ParaID_DutyCycle.DutyCycle_A;
	        Global_Data.rasv.halfBridge2DutyCycle = ParaID_DutyCycle.DutyCycle_B;
	        Global_Data.rasv.halfBridge3DutyCycle = ParaID_DutyCycle.DutyCycle_C;

    }
    else
    {
    	// Set Tristate
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, true, true, true);

    	// Reset Speed and Current Controllers
    	uz_SpeedControl_reset(SC_instance_1);
    	uz_CurrentControl_reset(CC_instance_1);
    	uz_SpeedControl_reset(SC_instance);
    	uz_CurrentControl_reset(CC_instance_dq);

    }

    // Set duty cycles for two-level modulator
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // Set duty cycles for three-level modulator
    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);

    // Set Controllers of PMSM 1
    uz_SpeedControl_set_Kp(SC_instance_1, Kp_speed_1);
    uz_SpeedControl_set_Ki(SC_instance_1, Ki_speed_1);
    uz_CurrentControl_set_Kp_id(CC_instance_1, Kp_id_1);
    uz_CurrentControl_set_Kp_iq(CC_instance_1, Kp_iq_1);
    uz_CurrentControl_set_Ki_id(CC_instance_1, Ki_id_1);
    uz_CurrentControl_set_Ki_iq(CC_instance_1, Ki_iq_1);


    // Set Controllers of PMSM 2
    uz_SpeedControl_set_Kp(SC_instance, Kp_speed_2);
    uz_SpeedControl_set_Ki(SC_instance, Ki_speed_2);
    uz_CurrentControl_set_Kp_id(CC_instance_dq, Kp_id_2);
    uz_CurrentControl_set_Kp_iq(CC_instance_dq, Kp_iq_2);
    uz_CurrentControl_set_Ki_id(CC_instance_dq, Ki_id_2);
    uz_CurrentControl_set_Ki_iq(CC_instance_dq, Ki_iq_2);

    //calculate induced voltage for estimation of r_fe + filter
    v_ind_dq_Volts_2.q = v_dq_Volts_2.q - r_s_2 * i_dq_Amps_2.q;
    v_ind_dq_Volts_2.d = v_dq_Volts_2.d - r_s_2 * i_dq_Amps_2.d;

    v_ind_dq_filt_Volts_2.d = uz_signals_IIR_Filter_sample(LP_instance_ud_ind_2, v_ind_dq_Volts_2.d);
    v_ind_dq_filt_Volts_2.q = uz_signals_IIR_Filter_sample(LP_instance_uq_ind_2, v_ind_dq_Volts_2.q);

    psi_dq_mVoltseconds_2.q  = (v_ind_dq_filt_Volts_2.d/(omega_el_rad_per_sec_2*-1.0f))*1000;
    psi_dq_mVoltseconds_2.d  = (v_ind_dq_filt_Volts_2.q/omega_el_rad_per_sec_2)*1000;


    // Update JavaScope
    JavaScope_update(&Global_Data);

    // ------ Inverter 1 ------ //
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H1) {
        error_type = 1.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L1) {
    	error_type = 2.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H2) {
    	error_type = 3.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L2) {
    	error_type = 4.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_H3) {
    	error_type = 5.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d1.FAULT_L3) {
    	error_type = 6.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d1.OC_L1) {
    	error_type = 7.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d1.OC_H1) {
    	error_type = 8.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d1.OC_L2) {
    	error_type = 9.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d1.OC_H2) {
    	error_type = 10.0f;
       ultrazohm_state_machine_set_error(true);
    }

    // ------ Inverter 2 ------ //
    //Read out overtemperature signal (low-active) and disable PWM and set UltraZohm in error state
    //Overtemperature for H1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H1) {
        error_type = 11.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L1
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L1) {
     	error_type = 12.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H2) {
     	error_type = 13.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L2
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L2) {
    	error_type = 14.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for H3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_H3) {
      	error_type = 15.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overtemperature for L3
    if (!Global_Data.av.inverter_outputs_d2.FAULT_L3) {
      	error_type = 16.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Read out overcurrent signal (low-active) and disable PWM and set UltraZohm in error state
    //Binding of the signals to the driver is slightly unintuitive
    //Overcurrent for Phase A
    if (!Global_Data.av.inverter_outputs_d2.OC_L1) {
      	error_type = 17.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase B
    if (!Global_Data.av.inverter_outputs_d2.OC_H1) {
     	error_type = 18.0f;
       ultrazohm_state_machine_set_error(true);
    }
    //Overcurrent for Phase C
    if (!Global_Data.av.inverter_outputs_d2.OC_L2) {
      	error_type = 19.0f;
       ultrazohm_state_machine_set_error(true);
     }
    //Overcurrent for DC-link
    if (!Global_Data.av.inverter_outputs_d2.OC_H2) {
      	error_type = 20.0f;
       ultrazohm_state_machine_set_error(true);
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
