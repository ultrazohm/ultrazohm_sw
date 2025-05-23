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
#include "../uz/uz_CurrentControl/uz_CurrentControl.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_parameterid_rs/uz_parameterid_rs.h"
#include "../uz/uz_ParameterID_rc/uz_ParameterID_rc.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;

#define PHASE_CURRENT_CONV_U 		90.0173			// ideal: 1000/11.211
#define PHASE_CURRENT_CONV_V 		89.7817
#define PHASE_CURRENT_CONV_W 		89.1090
#define PHASE_CURRENT_OFFSET_VOLT 	2.5
#define PHASE_CURRENT_OFFS_U		22.7855
#define PHASE_CURRENT_OFFS_V		8.0661
#define PHASE_CURRENT_OFFS_W		7.9499

#define DC_LINK_VOLT_CONV 			18.27932f		// DC-Voltage 0...5 V -> 0...91.5 V
#define DC_LINK_VOLT_OFFS			-0.01424f
// Korrektur des Skaling-Faktoren noch einmal überprüfen/validieren: alt: 1/0.0546
#define PHASE_VOLT_CONV_U 			17.1377		// Voltage DC_GND to Phase U
#define PHASE_VOLT_CONV_V 			17.1280
#define PHASE_VOLT_CONV_W 			17.1377
#define PHASE_VOLT_OFFS_U 			0.0011f
#define PHASE_VOLT_OFFS_V 			0.0006f
#define PHASE_VOLT_OFFS_W 			0.0011f
#define MOSFET_TEMP_CONV_U 			1

#define ISR_SAMPLE_FREQ				40000

#define MAX_CURRENT_ASSERTION 		300.0f
#define MAX_SPEED_ASSERTION			2300.0f
#define MAX_TEMP_ASSERTION			80.0f
#define MAX_MOTOR_TEMP_ASSERTION	115.0f
#define U_DC_MAX					55.0f
#define U_DC_MIN					40.0f

bool SKAI_nERROUT = 0U;			// Start in error-mode
bool flg_reset_SKAI = 0U;
bool flg_precharge_SKAI = 0U;
platform_state_t last_state;
platform_state_t current_state;
int reset_counter=0;
int delta_counter=0;
uint16_t trigger = 0U;
float cnt_trigger = 1.0f;
float data_valid_old = 0.0f;

float polycoef_a = 1999.3f;
float polycoef_b = -5468.4f;
float polycoef_c = 6334.4f;
float polycoef_d = -2043.7f;
float resistor_temp = 1000.0f;
float resistor_ref = 1000.0f;
float temp_ref = 25.0f;
float faulty_motortemp = 0.0f;

float temp_coef_a = 0.0173f;
float temp_coef_b = 7.64f;
float temp_coef_c = 0;

bool flg_compensate_age = 1U;
bool flg_pred_theta_el = 1U;
bool flg_volt_reverse_filter = 1U;

float theta_elec_pred = 0.0f;
float torque_meas_raw = 0.0f;

enum control_state_list
{
    manual = 0,
    FOC_i_dq_setpoint,
	manual_dq_voltage,
	rs_measurement,
	rc_fingerprint
};
enum control_state_list control_mode = FOC_i_dq_setpoint;


// Variables for Current Control and Speed Control

struct uz_3ph_abc_t measurement_current = {.a = 0.0f, .b = 0.0f, .c = 0.0f};
struct uz_3ph_abc_t measurement_voltage = {.a = 0.0f, .b = 0.0f, .c = 0.0f};

struct uz_3ph_dq_t dq_measurement_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_measurement_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_reference_current = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_3ph_dq_t dq_reference_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

float torque_ref = 0.0f;

struct uz_3ph_dq_t dq_decoup_voltage = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

struct uz_DutyCycle_t output_dutycycle = {
		.DutyCycle_A = 0.0f,
		.DutyCycle_B = 0.0f,
		.DutyCycle_C = 0.0f,
};

struct uz_parameterid_output actual_output;
struct uz_parameterID_rc_ref_val_t ref_rc_meas;



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
    //update_speed_and_position_of_encoder_on_D5(&Global_Data);
    Global_Data.av.theta_mech = uz_EnDat_read_pos_t0_as_radiant_and_age_wrapper(Global_Data.objects.EnDat_master_pointer, 32, false, true) - 2.9290f - (Global_Data.av.theta_offset/21.0f);
    Global_Data.av.EnDat_pos_age = uz_EnDat_read_pos_t0_as_radiant_and_age_wrapper(Global_Data.objects.EnDat_master_pointer, 32, true, false);
    Global_Data.av.mechanicalRotorSpeed = uz_EnDat_easy_speedreadout_revolutions_per_minute(Global_Data.objects.EnDat_master_pointer);
    Global_Data.av.mechanicalRotorSpeed_filtered = Global_Data.av.mechanicalRotorSpeed;
	//Global_Data.av.mechanicalRotorSpeed_filtered = uz_EnDat_rpm_smoothening(Global_Data.av.mechanicalRotorSpeed, 256U);
	Global_Data.av.omega_mech = uz_EnDat_rpm_to_rad_per_second_converter(Global_Data.av.mechanicalRotorSpeed);
	//Global_Data.av.omega_mech_filtered = uz_EnDat_rpm_to_rad_per_second_converter(Global_Data.av.mechanicalRotorSpeed_filtered);
    Global_Data.av.omega_el = Global_Data.av.omega_mech * 21.0f;
    //Global_Data.av.omega_el_filtered = Global_Data.av.omega_mech_filtered * 21.0f;
	//if(flg_compensate_age == true){
    	// compensation of delay time
	Global_Data.av.theta_mech_comp = Global_Data.av.theta_mech + Global_Data.av.omega_mech * Global_Data.av.EnDat_pos_age;
	Global_Data.av.theta_elec = Global_Data.av.theta_mech_comp * 21.0f;
    //} else{
    //	Global_Data.av.theta_elec = Global_Data.av.theta_mech * 21.0f;
    //}

    //Global_Data.av.EnDat_value_calc_time = uz_EnDat_time_elapsed_ns_to_s_converter(uz_EnDat_read_time_elapsed(Global_Data.objects.EnDat_master_pointer, uz_EnDat_elapsed_t0_t1));
    //Global_Data.av.EnDat_value_response_length = uz_EnDat_read_reponselength_and_convert_to_float(Global_Data.objects.EnDat_master_pointer);
    //Global_Data.av.EnDat_sync_quality = uz_EnDat_calculate_sync_quality_indicator(Global_Data.objects.EnDat_master_pointer, Global_Data.av.EnDat_value_calc_time);

    Global_Data.av.I_U = (Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV_U) - PHASE_CURRENT_OFFS_U;
    Global_Data.av.I_V = (Global_Data.aa.A1.me.ADC_A3) * PHASE_CURRENT_CONV_V - PHASE_CURRENT_OFFS_V;
    Global_Data.av.I_W = (Global_Data.aa.A1.me.ADC_A2) * PHASE_CURRENT_CONV_W - PHASE_CURRENT_OFFS_W;

    Global_Data.av.U_ZK = (Global_Data.aa.A1.me.ADC_A1 * DC_LINK_VOLT_CONV) + DC_LINK_VOLT_OFFS;
    Global_Data.av.U_L1 = (Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_U) + PHASE_VOLT_OFFS_U;
    Global_Data.av.U_L2 = (Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_V) + PHASE_VOLT_OFFS_V;
    Global_Data.av.U_L3 = (Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_W) + PHASE_VOLT_OFFS_W;

    float phi = 0.0f;
    if (flg_volt_reverse_filter == 1U){
    	//Global_Data.av.U_U = uz_signals_IIR_Filter_reverse_sample(Global_Data.objects.phase_a_lowpass, Global_Data.av.U_L1);
    	//Global_Data.av.U_V = uz_signals_IIR_Filter_reverse_sample(Global_Data.objects.phase_b_lowpass, Global_Data.av.U_L2);
    	//Global_Data.av.U_W = uz_signals_IIR_Filter_reverse_sample(Global_Data.objects.phase_c_lowpass, Global_Data.av.U_L3);

    	float magnitude = sqrt(1.0f + powf(((Global_Data.av.omega_el) / (2.0f * UZ_PIf * 4270.0f)),2.0f));

    	Global_Data.av.U_U = Global_Data.av.U_L1 * magnitude;
    	Global_Data.av.U_V = Global_Data.av.U_L2 * magnitude;
    	Global_Data.av.U_W = Global_Data.av.U_L3 * magnitude;

    	phi = - atanf((Global_Data.av.omega_el) / (2.0f * UZ_PIf * 4270.0f));
		phi = - 1.0f * uz_signals_wrap(phi, 2.0f*UZ_PIf);
    } else{
    	Global_Data.av.U_U = Global_Data.av.U_L1;
    	Global_Data.av.U_V = Global_Data.av.U_L2;
    	Global_Data.av.U_W = Global_Data.av.U_L3;
    }

    //torque_meas_raw = Global_Data.aa.A2.me.ADC_A1 * 20.0f;
    //Global_Data.av.torque_meas = uz_signals_IIR_Filter_sample(Global_Data.objects.torque_meas_filter_LP, torque_meas_raw);

    // Wieder fuer Lastpunkte verwenden:
    //float volt_temp = Global_Data.aa.A1.me.ADC_B5 * MOSFET_TEMP_CONV_U;
    //resistor_temp = polycoef_a * pow(volt_temp, 3) + polycoef_b * pow(volt_temp, 2) + polycoef_c * volt_temp + polycoef_d;
    //Global_Data.av.temperature_mosfet = temp_ref + (-temp_coef_b + sqrt(temp_coef_b*temp_coef_b - (4*temp_coef_a*(resistor_ref - resistor_temp))))/(2*temp_coef_a);
    Global_Data.av.temperature_mosfet = 20.0f;

    uz_TempCard_IF_MeasureTemps_cyclic(Global_Data.objects.temperature_card_d3);
    Global_Data.av.channel_A_data = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d3, 'A');
    faulty_motortemp =Global_Data.av.channel_A_data.temperature[19];
    Global_Data.av.temperature_motor = -0.000324f * faulty_motortemp*faulty_motortemp + 0.490982f * faulty_motortemp +24.728f;

    // Assertion check
    // (fabs(Global_Data.av.temperature_mosfet) >= MAX_TEMP_ASSERTION) ||
    //
    if ((fabs(Global_Data.av.I_U) >= MAX_CURRENT_ASSERTION) || (fabs(Global_Data.av.I_V) >= MAX_CURRENT_ASSERTION) || (fabs(Global_Data.av.I_W) >= MAX_CURRENT_ASSERTION) || (fabs(Global_Data.av.temperature_mosfet) >= MAX_TEMP_ASSERTION) || (fabs(Global_Data.av.mechanicalRotorSpeed) >= MAX_SPEED_ASSERTION) || (Global_Data.av.U_ZK > U_DC_MAX) || (Global_Data.av.U_ZK < U_DC_MIN) ) {

    	// Assertion to Stop Machine if max. Current or max. Speed
    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	SKAI_nERROUT = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.input_gpio, 0);
    	if (SKAI_nERROUT == 1U){
    		// Umrichter noch nicht im Fehlerfall
    		Global_Data.av.error_num = 1.0f;
    	}
    	ultrazohm_state_machine_set_stop(true);
    	// Set reset-gpio to zero
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, 2, 0U);
    }

    // Values for FOC:
    measurement_current.a = Global_Data.av.I_U;
    measurement_current.b = Global_Data.av.I_V;
    measurement_current.c = Global_Data.av.I_W;
    measurement_voltage.a = Global_Data.av.U_U;
    measurement_voltage.b = Global_Data.av.U_V;
    measurement_voltage.c = Global_Data.av.U_W;

    dq_measurement_current = uz_transformation_3ph_abc_to_dq(measurement_current, Global_Data.av.theta_elec);
    dq_measurement_voltage = uz_transformation_3ph_abc_to_dq(measurement_voltage, Global_Data.av.theta_elec - phi);

    Global_Data.av.I_d = dq_measurement_current.d;
    Global_Data.av.I_q = dq_measurement_current.q;
    Global_Data.av.U_d = dq_measurement_voltage.d;
    Global_Data.av.U_q = dq_measurement_voltage.q;

    if (Global_Data.rasv.flg_start_meas == 1.0f && control_mode != rc_fingerprint){
    	control_mode = rc_fingerprint;
    }

    if (Global_Data.rasv.flg_use_setpoint_calculation == 0.0f) {
        dq_reference_current.d = Global_Data.rasv.Id_ref;
        dq_reference_current.q = Global_Data.rasv.Iq_ref;
    } else {
    	//torque_ref = Global_Data.rasv.torque_ref;
    	//dq_reference_current = uz_SetPoint_sample(Global_Data.objects.current_setpoint_obj, Global_Data.av.omega_mech, torque_ref, Global_Data.av.U_ZK, dq_measurement_current);
    	dq_reference_current.d = Global_Data.rasv.Ipeak_ref * cos(Global_Data.rasv.Iphase_ref_deg * M_PI / 180.0f);
    	dq_reference_current.q = Global_Data.rasv.Ipeak_ref * sin(Global_Data.rasv.Iphase_ref_deg * M_PI / 180.0f);
    	Global_Data.rasv.Id_ref = dq_reference_current.d;
    	Global_Data.rasv.Iq_ref = dq_reference_current.q;
    }
/*
    if (Global_Data.av.I_d > 10.0f){
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio_LMG, 0, 1U);
    } else{
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio_LMG, 0, 0U);
    }

    if (Global_Data.av.I_q > 10.0f){
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio_LMG, 1, 1U);
    } else{
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio_LMG, 1, 0U);
    }
*/
    SKAI_nERROUT = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.input_gpio, 0);

    last_state = current_state;
    current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
    	//uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    	//uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
        // Start: Control algorithm - only if ultrazohm is in control state
    	if(current_state != last_state){
    		// First step in control-loop
    		flg_reset_SKAI = 1U;
    		reset_counter = 0;
    		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	}
    	if (flg_reset_SKAI){
    		// Check if control loop is enabled for one period
    		if(reset_counter > 0){
    			uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, 2, 1U);
    			if (SKAI_nERROUT == 1U){
    				//flg_reset_SKAI = 0U;
    				if (flg_precharge_SKAI == 0U){
    					flg_precharge_SKAI = 1U;
    					delta_counter = reset_counter;
    					uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, false, false, false);
    				}
    				// Precharge for minimum 1 ms -> Set bottom gate to high
    				if ((flg_precharge_SKAI == 1U) && ((reset_counter - delta_counter) <= 2.0f*0.001f*ISR_SAMPLE_FREQ) ){
    					Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
						Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
						Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
						Global_Data.av.error_num = 0.0f;
						uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    				} else{
    					flg_reset_SKAI = 0U;
    					flg_precharge_SKAI = 0U;
    					Global_Data.rasv.Ud_ref = 0.0f;
    					Global_Data.rasv.Uq_ref = 0.0f;
    					uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio_LMG, 1, 1U);
    				}
    			}
    		}
    		reset_counter++;
    	} else{
    		if (SKAI_nERROUT == 1U){
				// Begin of control algorithm
				switch(control_mode){
				case manual:
					// control of dutycycles with GUI
					uz_CurrentControl_reset(Global_Data.objects.FOC_instance);
					uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
					break;
				case FOC_i_dq_setpoint:
					uz_3ph_dq_t current_setpoints_filtered = uz_signals_IIR_Filter_dq_setpoint(Global_Data.objects.dq_setpoint_filter, dq_reference_current);
					//uz_3ph_dq_t current_setpoints_filtered = dq_reference_current;
					dq_reference_voltage = uz_CurrentControl_sample(Global_Data.objects.FOC_instance, current_setpoints_filtered, dq_measurement_current, Global_Data.av.U_ZK, Global_Data.av.omega_el);
					Global_Data.rasv.Ud_ref = dq_reference_voltage.d;
					Global_Data.rasv.Uq_ref = dq_reference_voltage.q;

					//if (flg_pred_theta_el){
						Global_Data.av.theta_elec_pred = Global_Data.av.theta_elec + ((1.5f*1.0f/ISR_SAMPLE_FREQ)*Global_Data.av.omega_el);
						output_dutycycle = uz_Space_Vector_Modulation(dq_reference_voltage, Global_Data.av.U_ZK, Global_Data.av.theta_elec_pred);
					//} else{
					//	output_dutycycle = uz_Space_Vector_Modulation(dq_reference_voltage, Global_Data.av.U_ZK, Global_Data.av.theta_elec);
					//}
					//Global_Data.rasv.halfBridge1DutyCycle = output_dutycycle.DutyCycle_A;
					//Global_Data.rasv.halfBridge2DutyCycle = output_dutycycle.DutyCycle_B;
					//Global_Data.rasv.halfBridge3DutyCycle = output_dutycycle.DutyCycle_C;
					uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output_dutycycle.DutyCycle_A, output_dutycycle.DutyCycle_B, output_dutycycle.DutyCycle_C);
					break;
				case manual_dq_voltage:
					dq_reference_voltage.d = Global_Data.rasv.Ud_ref;
					dq_reference_voltage.q = Global_Data.rasv.Uq_ref;
					Global_Data.av.theta_elec_pred = Global_Data.av.theta_elec + ((1.5f*1.0f/ISR_SAMPLE_FREQ)*Global_Data.av.omega_el);
					output_dutycycle = uz_Space_Vector_Modulation(dq_reference_voltage, Global_Data.av.U_ZK, Global_Data.av.theta_elec_pred);
					uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output_dutycycle.DutyCycle_A, output_dutycycle.DutyCycle_B, output_dutycycle.DutyCycle_C);

					break;
				case rs_measurement:
					actual_output = uz_parameterid_rs_generate_outputs(Global_Data.objects.rs_meas_instance, dq_measurement_voltage.d, dq_measurement_current.d);
					dq_reference_current.d = actual_output.i_sample;
					dq_reference_current.q = 0.0f;
					Global_Data.rasv.Id_ref = dq_reference_current.d;
					Global_Data.rasv.Iq_ref = dq_reference_current.q;
					Global_Data.rasv.n_ref = actual_output.n_sample;

					// Basic FOC current control
					uz_3ph_dq_t dq_current_filt = uz_signals_IIR_Filter_dq_setpoint(Global_Data.objects.dq_setpoint_filter, dq_reference_current);
					dq_reference_voltage = uz_CurrentControl_sample(Global_Data.objects.FOC_instance, dq_current_filt, dq_measurement_current, Global_Data.av.U_ZK, Global_Data.av.omega_el);
					Global_Data.rasv.Ud_ref = dq_reference_voltage.d;
					Global_Data.rasv.Uq_ref = dq_reference_voltage.q;

					Global_Data.av.theta_elec_pred = Global_Data.av.theta_elec + ((1.5f*1.0f/ISR_SAMPLE_FREQ)*Global_Data.av.omega_el);
					output_dutycycle = uz_Space_Vector_Modulation(dq_reference_voltage, Global_Data.av.U_ZK, Global_Data.av.theta_elec_pred);

					uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output_dutycycle.DutyCycle_A, output_dutycycle.DutyCycle_B, output_dutycycle.DutyCycle_C);
					break;
				case rc_fingerprint:
					Global_Data.rasv.rc_meas_output = uz_parameterID_rc_generate_idq_ref(Global_Data.objects.rc_meas_instance, Global_Data.av.temperature_motor);
					dq_reference_current.d = Global_Data.rasv.rc_meas_output.id_ref_Amps;
					dq_reference_current.q = Global_Data.rasv.rc_meas_output.iq_ref_Amps;
					Global_Data.rasv.Id_ref = dq_reference_current.d;
					Global_Data.rasv.Iq_ref = dq_reference_current.q;
					Global_Data.rasv.n_ref = Global_Data.rasv.rc_meas_output.n_ref_rpm;
					Global_Data.rasv.operatingpoints_rc_meas = Global_Data.rasv.rc_meas_output.operating_points_all;

					// Basic FOC current control
					uz_3ph_dq_t dq_current_filt_rc = uz_signals_IIR_Filter_dq_setpoint(Global_Data.objects.dq_setpoint_filter, dq_reference_current);
					dq_reference_voltage = uz_CurrentControl_sample(Global_Data.objects.FOC_instance, dq_current_filt_rc, dq_measurement_current, Global_Data.av.U_ZK, Global_Data.av.omega_el);
					Global_Data.rasv.Ud_ref = dq_reference_voltage.d;
					Global_Data.rasv.Uq_ref = dq_reference_voltage.q;

					Global_Data.av.theta_elec_pred = Global_Data.av.theta_elec + ((1.5f*1.0f/ISR_SAMPLE_FREQ)*Global_Data.av.omega_el);
					output_dutycycle = uz_Space_Vector_Modulation(dq_reference_voltage, Global_Data.av.U_ZK, Global_Data.av.theta_elec_pred);


					if (Global_Data.rasv.rc_meas_output.data_valid == 1.0f && Global_Data.rasv.rc_meas_output.data_valid != data_valid_old){
						trigger = 0U;
					} else {
						cnt_trigger++;
						if (cnt_trigger > 1000U){
							trigger = 1U;
							cnt_trigger = 0U;
						}
					}
					data_valid_old = Global_Data.rasv.rc_meas_output.data_valid;

					uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio_LMG, 1, trigger);

					uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, output_dutycycle.DutyCycle_A, output_dutycycle.DutyCycle_B, output_dutycycle.DutyCycle_C);
					break;
				}
    		} else{
    			// Umrichter in Fehlermodus
    	    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, 2, 0U);
    	    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	    	output_dutycycle.DutyCycle_A = 0.0f;
    	    	output_dutycycle.DutyCycle_B = 0.0f;
    	    	output_dutycycle.DutyCycle_C = 0.0f;
    	    	uz_CurrentControl_reset(Global_Data.objects.FOC_instance);
    	        dq_reference_current.d = 0.0f;
    	        dq_reference_current.q = 0.0f;
    	        dq_reference_current.zero = 0.0f;
    			ultrazohm_state_machine_set_stop(true);
    		}
    	}
    } else{
    	// Jumped out of control state --> Reset has to be low for 1 ms
    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, 2, 0U);
    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	control_mode = FOC_i_dq_setpoint;
    	output_dutycycle.DutyCycle_A = 0.0f;
    	output_dutycycle.DutyCycle_B = 0.0f;
    	output_dutycycle.DutyCycle_C = 0.0f;
    	uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, true, true, true);
    	uz_CurrentControl_reset(Global_Data.objects.FOC_instance);
        dq_reference_current.d = 0.0f;
        dq_reference_current.q = 0.0f;
        dq_reference_current.zero = 0.0f;
    }


    Global_Data.rasv.SKAI_nERROUT = SKAI_nERROUT;
    Global_Data.rasv.flg_reset_SKAI = flg_reset_SKAI;
    Global_Data.rasv.SKAI_reset_counter = reset_counter;

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
