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

// Variables for Current Control and Speed Control
struct uz_3ph_abc_t measurement_current = {.a = 0.0f, .b = 0.0f, .c = 0.0f};
struct uz_3ph_abc_t measurement_voltage = {.a = 0.0f, .b = 0.0f, .c = 0.0f};

struct uz_3ph_dq_t dq_measurement_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_measurement_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_reference_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_reference_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

struct uz_DutyCycle_t output = {
		.DutyCycle_A = 0.0f,
		.DutyCycle_B = 0.0f,
		.DutyCycle_C = 0.0f,
};

float omega_el_rad_per_sec = 0.0f;
float omega_m_rad_per_sec = 0.0f;

float unfiltered_signal = 0.0f;

bool state_LMG_measure = false;
bool state_controller_delay = false;
bool state_slow_current_set = false;
bool state_set_next_point = true;
bool state_stop_current_angle = false;
float n_delay_controller = 0.0f;
float n_measurements = 0.0f;
float n_slow_current = 0.0f;
static float counter_slow_current = 0.0f;
static float counter_n_delay_controller = 0.0f;
static float counter_n_measurements = 0.0f;
static float id_last = 0.0f;
static float iq_last = 0.0f;
static float id_soll = 0.0f;
static float iq_soll = 0.0f;
//static float counter_meshpoints = 0.0f;

// automatic measurement
uint32_t counter_current = 0U;
uint32_t counter_angle = 0U;
static uint32_t n_currents_max = 3U; //10U;
static uint32_t n_angles_max = 10U;//37U;

//static float ieff[10] = {1.0f, 5.0f, 10.0f, 15.0f, 20.0f, 25.0f, 30.0f, 35.0f, 40.0f, 45.0f};
static float ieff[3] = {1.0f, 5.0f, 10.0f};
//static float angle[37] = {0.0f, 2.5f, 5.0f, 7.5f, 10.0f, 12.5f, 15.0f, 17.5f, 20.0f, 22.5f, 25.0f, 27.5f,
//		 30.0f, 32.5f, 35.0f, 37.5f, 40.0f, 42.5f, 45.0f, 47.5f, 50.0f, 52.5f, 55.0f, 57.5f, 60.0f, 62.5f,
//		 65.0f, 67.5f, 70.0f, 72.5f, 75.0f, 77.5f, 80.0f, 82.5f, 85.0f, 87.5f, 90.0f};

//static float angle[15] = {35.0f, 37.5f, 40.0f, 42.5f, 45.0f, 47.5f, 50.0f, 52.5f, 55.0f, 57.5f, 60.0f, 62.5f,
//		 65.0f, 67.5f, 70.0f};

static float angle[10] = {0.0f, 10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f};

// Conversion factors for current and voltage
#define NUMBER_OF_TURNS_CURRENT_MEASURING 	1.0f 	// Number of turns Current Measuring FU
#define ADC_CURRENT_SCALING_U 				39.89f //80.0f	// Scaling factor for current measurement
#define ADC_CURRENT_OFFSET_U				-0.55849f // 2.5f	// Offset for LEM Sensors
#define ADC_CURRENT_SCALING_V 				32.887f
#define ADC_CURRENT_OFFSET_V				0.3298f
#define ADC_CURRENT_SCALING_W               -32.887f
#define ADC_CURRENT_OFFSET_W				-0.08244f

#define PHASE_CURRENT_CONV_U					33.722//37.735 // 31,732
#define PHASE_CURRENT_CONV_V					35.983//37.735 // 33.86
#define PHASE_CURRENT_CONV_W					34.206//37.735 // 32.188

#define DC_VOLT_CONV						240 // -240.0f //12.5f	// Scaling factor for voltage measurement
#define DC_VOLT_OFFSET						240 //-1.0f    // Offset for DC voltage sensor
#define PHASE_VOLT_CONV						1.0f //12.5f	// Scaling factor for voltage measurement
#define ADC_PH_VOLT_OFFSET					0.0f	// Offset for voltage sensors
#define USE_RESOVER							0U		// 0u: Incremental Encoder on D5
#define MAX_CURRENT_ASSERTION				110.0f	// Maximum Current
#define MAX_SPEED_ASSERTION					2700.0f	// Maximum Speed


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

    // Calculate theta_elec
    Global_Data.av.theta_elec = Global_Data.av.theta_elec - Global_Data.av.theta_offset;
    Global_Data.av.theta_mech = 1.0f / Global_Data.av.polepairs * Global_Data.av.theta_elec;
    // convert ADC currents

    Global_Data.av.I_U = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV_U;
    Global_Data.av.I_V = Global_Data.aa.A1.me.ADC_B7 * PHASE_CURRENT_CONV_V;
    Global_Data.av.I_W = -1.0f * Global_Data.aa.A1.me.ADC_B6 * PHASE_CURRENT_CONV_W;

    measurement_current.a = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_u, Global_Data.av.I_U) + 0.2f;
    measurement_current.b = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_v, Global_Data.av.I_V) - 0.4f;
    measurement_current.c = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_w, Global_Data.av.I_W) + 0.45f;

//    measurement_current.a = ADC_CURRENT_SCALING_U * (uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_u, Global_Data.aa.A1.me.ADC_B5)) - ADC_CURRENT_OFFSET_U;
//    measurement_current.b = ADC_CURRENT_SCALING_V * (uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_v, Global_Data.aa.A1.me.ADC_B7)) - ADC_CURRENT_OFFSET_V;
//    measurement_current.c = ADC_CURRENT_SCALING_W * (uz_signals_IIR_Filter_sample(Global_Data.objects.iir_i_w, Global_Data.aa.A1.me.ADC_B6)) - ADC_CURRENT_OFFSET_W;
    dq_measurement_current = uz_transformation_3ph_abc_to_dq(measurement_current, Global_Data.av.theta_elec);

    // Value to Scope
    Global_Data.av.I_U_filt = measurement_current.a;
    Global_Data.av.I_V_filt = measurement_current.b;
    Global_Data.av.I_W_filt = measurement_current.c;

    Global_Data.av.I_d = dq_measurement_current.d;
    Global_Data.av.I_q = dq_measurement_current.q;

    Global_Data.av.testsignal = 0.0f;

    // Check if maximum current or maximum speed is reached
    if (fabs(measurement_current.a) > MAX_CURRENT_ASSERTION || fabs(measurement_current.b) > MAX_CURRENT_ASSERTION || fabs(measurement_current.c) > MAX_CURRENT_ASSERTION || fabs(Global_Data.av.mechanicalRotorSpeed) > MAX_SPEED_ASSERTION)
    {
    	// Assertion to Stop Machine if max. Current or max. Speed
    	output.DutyCycle_A = 0.0f;
    	output.DutyCycle_B = 0.0f;
    	output.DutyCycle_C = 0.0f;
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU, 0);
    	ultrazohm_state_machine_set_stop(true);
    }

    // convert ADC voltages
    measurement_voltage.a = PHASE_VOLT_CONV * (uz_signals_IIR_Filter_sample(Global_Data.objects.iir_u_u, Global_Data.aa.A1.me.ADC_A2)) - ADC_PH_VOLT_OFFSET;
    measurement_voltage.b = PHASE_VOLT_CONV * (uz_signals_IIR_Filter_sample(Global_Data.objects.iir_u_v, Global_Data.aa.A1.me.ADC_A1)) - ADC_PH_VOLT_OFFSET;
    measurement_voltage.c = PHASE_VOLT_CONV * (uz_signals_IIR_Filter_sample(Global_Data.objects.iir_u_w, Global_Data.aa.A1.me.ADC_A3)) - ADC_PH_VOLT_OFFSET;
    dq_measurement_voltage = uz_transformation_3ph_abc_to_dq(measurement_voltage, Global_Data.av.theta_elec);

//    unfiltered_signal = DC_VOLT_CONV * (Global_Data.aa.A1.me.ADC_B8 - DC_VOLT_OFFSET); //Global_Data.aa.A1.me.ADC_A4;
    Global_Data.av.U_ZK  = -1.0f * DC_VOLT_CONV * Global_Data.aa.A1.me.ADC_B8 - DC_VOLT_OFFSET;
    Global_Data.av.U_ZK_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.iir_u_dc, Global_Data.av.U_ZK);

    // Value to Scope
    Global_Data.av.U_U = measurement_voltage.a;
    Global_Data.av.U_V = measurement_voltage.b;
    Global_Data.av.U_W = measurement_voltage.c;

    Global_Data.av.U_d = dq_measurement_voltage.d;
    Global_Data.av.U_q = dq_measurement_voltage.q;

    // calculating values needed for current control
    omega_m_rad_per_sec = Global_Data.av.mechanicalRotorSpeed * (2.0f * M_PI) / 60.0f; // omega_mech
    omega_el_rad_per_sec = omega_m_rad_per_sec * Global_Data.av.polepairs;

    // Value to Scope

    n_delay_controller = Global_Data.rasv.t_delay_controller * UZ_PWM_FREQUENCY;
    n_measurements = Global_Data.rasv.t_measurement * UZ_PWM_FREQUENCY;
    n_slow_current = Global_Data.rasv.t_set_current * UZ_PWM_FREQUENCY;

    // Set kp and ki for current control (only for the first initialization or for modifying)
//    uz_CurrentControl_set_Kp_id(Global_Data.objects.CurrentControl_instance, Global_Data.av.kp_d);
//    uz_CurrentControl_set_Ki_id(Global_Data.objects.CurrentControl_instance, Global_Data.av.ki_d);

//    uz_CurrentControl_set_Kp_iq(Global_Data.objects.CurrentControl_instance, Global_Data.av.kp_q);
//    uz_CurrentControl_set_Ki_iq(Global_Data.objects.CurrentControl_instance, Global_Data.av.ki_q);


    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
    	switch (Global_Data.rasv.state_of_statemachine)
    	{
    		case 0U: // All Off
    			// Disable FU
    			// Set DutyCycles to zero
    	    	output.DutyCycle_A = 0.0f;
    	    	output.DutyCycle_B = 0.0f;
    	    	output.DutyCycle_C = 0.0f;
    	    	// Set state of Half-Brides of FU in tristate
    	    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    			// Disable Half-Bridges of FU
    	    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU, 0);
    	    	Global_Data.av.flg_enable_FU = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU);

    	    	// Reset Measurement
    	    	counter_n_measurements = 0.0f;
    	    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_continues, 0);
    	    	Global_Data.av.flg_enable_LMG_continues = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_continues);
				uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_transient, 0);
				Global_Data.av.flg_enable_LMG_transient = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_transient);

				// Reset Current Angle Measurement
				state_stop_current_angle = false;
				state_set_next_point = true;
				counter_angle = 0U;
				counter_current = 0U;

				Global_Data.rasv.i_d_ref = 0.0f;
				Global_Data.rasv.i_q_ref = 0.0f;
				Global_Data.rasv.n_ref_rpm = 0.0f;

    			break;
			case 1U: // Manual Control
		    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
		    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU, 1);
		    	Global_Data.av.flg_enable_FU = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU);

		        if (Global_Data.av.flg_speed_control){
		        	if(Global_Data.rasv.n_ref_rpm==0.0f){
		        		dq_reference_current.d = 0.0f;
		        		dq_reference_current.q = 0.0f;
		        		Global_Data.rasv.i_d_ref = dq_reference_current.d;
		        		Global_Data.rasv.i_q_ref = dq_reference_current.q;
		        	} else {
		        		dq_reference_current.q = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, Global_Data.rasv.n_ref_rpm);
		        		dq_reference_current.d = fabs(dq_reference_current.q);
		        		Global_Data.rasv.i_d_ref = dq_reference_current.d;
		        		Global_Data.rasv.i_q_ref = dq_reference_current.q;
		        	}
		        	// currently not implemented !!!
		        }else{
		        	// Set I_d and I_q currents for current control
		        	dq_reference_current.d = Global_Data.rasv.i_d_ref;
		        	dq_reference_current.q = Global_Data.rasv.i_q_ref;
		        	dq_reference_current.zero = 0;
		        }

		        // FOC - get U_d and U_q as controlled variables
		        dq_reference_voltage = uz_CurrentControl_sample(Global_Data.objects.CurrentControl_instance, dq_reference_current, dq_measurement_current, Global_Data.av.U_ZK_filt, omega_el_rad_per_sec);
//		        dq_reference_voltage = uz_CurrentControl_sample(Global_Data.objects.CurrentControl_instance, dq_reference_current, dq_measurement_current, 30.0f, omega_el_rad_per_sec);
		        Global_Data.rasv.U_d_ref = dq_reference_voltage.d;
		        Global_Data.rasv.U_q_ref = dq_reference_voltage.q;

		        // Generate PWM Signal for each phase
		        output = uz_Space_Vector_Modulation(dq_reference_voltage, Global_Data.av.U_ZK_filt, Global_Data.av.theta_elec);
		        Global_Data.av.duty_cycle_A = output.DutyCycle_A;
		        Global_Data.av.duty_cycle_B = output.DutyCycle_B;
		        Global_Data.av.duty_cycle_C = output.DutyCycle_C;

		        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_A, output.DutyCycle_B, output.DutyCycle_C);

		        break;
			case 2U: // Detect initial Angle
//		    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
//		       	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU, 1);
//		       	Global_Data.av.flg_enable_FU = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU);
//
//		       	output.DutyCycle_A = 0.1f;
//		       	output.DutyCycle_B = 0.0f;
//		       	output.DutyCycle_C = 0.0f;
//
//		        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_A, output.DutyCycle_B, output.DutyCycle_C);

		        break;

			case 3U: // Torque Current Angle

				// Set Currents

				if(state_set_next_point && (state_stop_current_angle == false))
				{
					if(counter_angle >= n_angles_max){
						counter_current = counter_current + 1U;
//						Global_Data.av.testsignal = Global_Data.av.testsignal + 1.0f;
						counter_angle = 0U;
//						Global_Data.av.testsignal = 0.0f;
						if(counter_current >= n_currents_max) {
							Global_Data.rasv.i_d_ref = 0.0f;
							Global_Data.rasv.i_q_ref = 0.0f;
							state_stop_current_angle = true;
							Global_Data.rasv.state_of_statemachine = 0U;
						}
					}

					if(state_stop_current_angle == false){
						id_last = id_soll;
						iq_last = iq_soll;
						id_soll = ieff[counter_current] * cos(angle[counter_angle] * M_PI / 180.0f);
						iq_soll = ieff[counter_current] * sin(angle[counter_angle] * M_PI / 180.0f);
						counter_angle = counter_angle + 1U;
//						Global_Data.av.testsignal = Global_Data.av.testsignal + 1.0f;
					}

					counter_n_delay_controller = 0.0f;
					counter_n_measurements = 0.0f;
					counter_slow_current = 0.0f;

					state_set_next_point = false;
					state_slow_current_set = true;
					state_controller_delay = false;
					state_LMG_measure = false;


				}

				if((state_stop_current_angle == false) && state_slow_current_set){
					if(counter_slow_current <= n_slow_current){
						counter_slow_current = counter_slow_current + 1.0f;

						Global_Data.rasv.i_d_ref = id_last + (id_soll - id_last)/n_slow_current * counter_slow_current;
						Global_Data.rasv.i_q_ref = iq_last + (iq_soll - iq_last)/n_slow_current * counter_slow_current;
					}else{
	//					state_slow_current_set = false;
	//					state_controller_delay = true;

						state_set_next_point = false;
						state_slow_current_set = false;
						state_controller_delay = true;
						state_LMG_measure = false;

					}
				}

				// FOC
//		    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
//		    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU, 1);
//		    	Global_Data.av.flg_enable_FU = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU);
//
//		        if (Global_Data.av.flg_speed_control){
//		        	//dq_reference_current = uz_SpeedControl_sample(Global_Data.objects.Speed_instance, omega_m_rad_per_sec, Global_Data.rasv.n_ref_rpm);
//		        	// currently not implemented !!!
//		        }else{
//		        	// Set I_d and I_q currents for current control
//		        	dq_reference_current.d = Global_Data.rasv.i_d_ref;
//		        	dq_reference_current.q = Global_Data.rasv.i_q_ref;
//		        	dq_reference_current.zero = 0.0f;
//		        }
//
//		        // FOC - get U_d and U_q as controlled variables
//		        dq_reference_voltage = uz_CurrentControl_sample(Global_Data.objects.CurrentControl_instance, dq_reference_current, dq_measurement_current, Global_Data.av.U_ZK_filt, omega_el_rad_per_sec);
////		        dq_reference_voltage = uz_CurrentControl_sample(Global_Data.objects.CurrentControl_instance, dq_reference_current, dq_measurement_current, 30.0f, omega_el_rad_per_sec);
//		        Global_Data.rasv.U_d_ref = dq_reference_voltage.d;
//		        Global_Data.rasv.U_q_ref = dq_reference_voltage.q;
//
//		        // Generate PWM Signal for each phase
//		        output = uz_Space_Vector_Modulation(dq_reference_voltage, Global_Data.av.U_ZK_filt, Global_Data.av.theta_elec);
//		        Global_Data.av.duty_cycle_A = output.DutyCycle_A;
//		        Global_Data.av.duty_cycle_B = output.DutyCycle_B;
//		        Global_Data.av.duty_cycle_C = output.DutyCycle_C;
//
//
//		        uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output.DutyCycle_A, output.DutyCycle_B, output.DutyCycle_C);


		        // Enable / Disable Measurement
				if((state_controller_delay == true) && (state_stop_current_angle == false)){
					if(counter_n_delay_controller <= n_delay_controller)
					{
						counter_n_delay_controller = counter_n_delay_controller + 1.0f;

					} else {
	//					state_controller_delay = false;
	//					state_LMG_measure = true;

						state_set_next_point = false;
						state_slow_current_set = false;
						state_controller_delay = false;
						state_LMG_measure = true;
					}
    			}

				// Counter for continues measurement
				if((state_LMG_measure == true) && (state_stop_current_angle == false)){
					if(counter_n_measurements <= n_measurements)
					{
						counter_n_measurements = counter_n_measurements + 1.0f;
//						Global_Data.av.testsignal = counter_n_measurements;
					} else {
//						state_LMG_measure = false;
//						state_set_next_point = true;

						state_set_next_point = true;
						state_slow_current_set = false;
						state_controller_delay = false;
						state_LMG_measure = false;

					}
				}

				switch (Global_Data.rasv.LMG_measurement_typ) {
					case 1U: // Continues
						if((state_LMG_measure == true) && (state_stop_current_angle == false)) {
							uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_continues, 1);
							Global_Data.av.flg_enable_LMG_continues = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_continues);

						} else {
							uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_continues, 0);
							Global_Data.av.flg_enable_LMG_continues = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_LMG_continues);
						}

//						if (Global_Data.av.flg_enable_LMG_continues == true){
//							Global_Data.av.testsignal = 1.0f;
//						} else {
//							Global_Data.av.testsignal = 0.0f;
//						}
						break;

					case 2U: // Transient
						break;
					default:
						break;

				}


				break;

			case 4U: // Efficiency Map

				break;

	        default:
	            break;
    	}
    } else {
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.Output_instance, Global_Data.rasv.enable_FU, 0);
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	output.DutyCycle_A = 0.0f;
    	output.DutyCycle_B = 0.0f;
    	output.DutyCycle_C = 0.0f;
    }


//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

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
