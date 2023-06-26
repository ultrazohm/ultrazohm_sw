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
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../uz/uz_math_constants.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Data for determination of mechanical resolver angle
float theta_mech_old=0.0f;
int32_t cnt = 0U;
bool cnt_reset = 0;
float cnt_float=0.0f;
float cnt_reset_float=0.0f;
float theta_mech_calc_from_resolver = 0.0f;
float theta_m_max = 0.0f;
float theta_m_min = 0.0f;

// Global variable structure
extern DS_Data Global_Data;

// conversion defines for ADC readings
#define PHASE_CURRENT_CONV	16.75f
#define DC_VOLT_CONV_1		140.27f
#define DC_VOLT_OFF_1		450.25f
#define DC_VOLT_CONV_2		141.28f
#define DC_VOLT_OFF_2		452.17f

// software limits
#define MAX_PHASE_CURRENT_AMP  20.0f
#define MAX_DC_VOLT 590.0f
#define MAX_TEMP_DEG 90.0f

//neutral config
#define NEUTRAL_CONFIG 1U //1U: 1N, 2U: 2N, 3U: zero fluxmap
float u_n1 = 0.0f;
float u_n2 = 0.0f;
float u_a1c1 = 0.0f;
float u_a2c2 = 0.0f;

//ParaID
#include "../uz/uz_ParameterID/uz_ParameterID_6ph.h"
extern uz_ParameterID_Data_t ParaID_Data;
extern uz_ParameterID_6ph_t* ParameterID;
uz_6ph_dq_t paraid_temp_dq_currents = {0};
//Next lines only needed, if the uz_FOC is used as the controller
struct uz_DutyCycle_2x3ph_t ParaID_DutyCycle = { 0 };
uz_3ph_alphabeta_t voltage_stationary_xy = {0};
uz_3ph_alphabeta_t current_stationary_xy = {0};
uz_3ph_alphabeta_t voltage_stationary_zero = {0};
uz_3ph_alphabeta_t current_stationary_zero = {0};
uz_6ph_abc_t m_6ph_abc_currents = {0};
uz_6ph_abc_t m_6ph_abc_voltage = {0};
uz_6ph_dq_t controller_out = {0};
//ParaID end


// zeroing
uz_6ph_abc_t zero_offset = {0};
bool zero_finished = false;
bool first_ISR = false;
uz_6ph_abc_t zero_offset_function(bool* flag);
struct uz_DutyCycle_t dc_non_zero(struct uz_DutyCycle_t uncorrected);

// uz Temp card
#include "../IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
extern uz_temperaturecard_t* uz_Tempcard;
uz_temperaturecard_OneGroup channel_A_data;
uz_6ph_abc_t winding_temperature = {0};


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
    // read resolver
    Global_Data.av.posVel_mech = uz_resolverIP_readMechanicalPositionAndVelocity(Global_Data.objects.resolver_d5_1);
    Global_Data.av.posVel_el = uz_resolverIP_readElectricalPositionAndVelocity(Global_Data.objects.resolver_d5_1);

    // save raw angles to variables
    Global_Data.av.theta_mech_rad = Global_Data.av.posVel_mech.position;
    Global_Data.av.theta_elec_rad = Global_Data.av.posVel_el.position;

    Global_Data.av.theta_mech_calculated = theta_mech_calc_from_resolver-Global_Data.av.theta_mech_offset_rad;

    // save speeds in rad/s to variables
    Global_Data.av.mechanicalRotorSpeedRADpS = Global_Data.av.posVel_mech.velocity;
    Global_Data.av.electricalRotorSpeedRADpS = Global_Data.av.posVel_el.velocity;

    // calculate speeds in rpm
    Global_Data.av.mechanicalRotorSpeedRPM = Global_Data.av.mechanicalRotorSpeedRADpS * 30.0f/UZ_PIf;
    Global_Data.av.electricalRotorSpeedRPM = Global_Data.av.electricalRotorSpeedRADpS * 30.0f/UZ_PIf;

    // convert ADC readings to currents in Amps
    Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_CURRENT_CONV;
    Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_CURRENT_CONV;
    Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
    // convert ADC readings to voltages
    Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A4 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1 - zero_offset.a1;
    Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1 - zero_offset.b1;
    Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1 - zero_offset.c1;
    Global_Data.av.v_dc2 = Global_Data.aa.A2.me.ADC_A4 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2 - zero_offset.a2;
    Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2 - zero_offset.b2;
    Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2 - zero_offset.c2;

    // zero voltage reading at startup
    if(!zero_finished){
    	zero_offset = zero_offset_function(&zero_finished);
    }

    // check current limit
	if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {
		uz_assert(0);
	}
	// check DC Bus
	if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {
			uz_assert(0);
	}
	// check inverter temp
	if(fabs(Global_Data.av.temperature_inv_2) > MAX_TEMP_DEG || fabs(Global_Data.av.temperature_inv_2) > MAX_TEMP_DEG) {
		//uz_assert(0);
	}

	// read temperature values from inverters
	Global_Data.av.tempPWMoutputs1 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.tempMeasurement1);
	Global_Data.av.tempPWMoutputs2 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.tempMeasurement2);
	Global_Data.av.temperature_inv_1 = Global_Data.av.tempPWMoutputs1.TempDegreesCelsius;
	Global_Data.av.temperature_inv_2 = Global_Data.av.tempPWMoutputs2.TempDegreesCelsius;

	// read temperatures from windings
	uz_TempCard_IF_MeasureTemps_cyclic(uz_Tempcard);
	channel_A_data = uz_TempCard_IF_get_channel(uz_Tempcard, 'a');
	winding_temperature.a1 = channel_A_data.temperature[3]*(channel_A_data.Channels_Valid[3]==1);
	winding_temperature.b1 = channel_A_data.temperature[5]*(channel_A_data.Channels_Valid[5]==1);
	winding_temperature.c1 = channel_A_data.temperature[7]*(channel_A_data.Channels_Valid[7]==1);
	winding_temperature.a2 = channel_A_data.temperature[9]*(channel_A_data.Channels_Valid[9]==1);
	winding_temperature.b2 = channel_A_data.temperature[11]*(channel_A_data.Channels_Valid[11]==1);
	winding_temperature.c2 = channel_A_data.temperature[13]*(channel_A_data.Channels_Valid[13]==1);
	Global_Data.av.avg_winding_temperature = (winding_temperature.a1 + winding_temperature.b1 + winding_temperature.c1 + winding_temperature.a2 + winding_temperature.b2 + winding_temperature.c2)/((channel_A_data.Channels_Valid[3]==1) + (channel_A_data.Channels_Valid[5]==1) + (channel_A_data.Channels_Valid[7]==1) + (channel_A_data.Channels_Valid[9]==1) + (channel_A_data.Channels_Valid[11]==1) + (channel_A_data.Channels_Valid[13]==1));

	////////////write to structs
	m_6ph_abc_currents.a1 = Global_Data.av.i_a1;
	m_6ph_abc_currents.b1 = Global_Data.av.i_b1;
	m_6ph_abc_currents.c1 = Global_Data.av.i_c1;
	m_6ph_abc_currents.a2 = Global_Data.av.i_a2;
	m_6ph_abc_currents.b2 = Global_Data.av.i_b2;
	m_6ph_abc_currents.c2 = Global_Data.av.i_c2;

	// calc u neutral voltage
	switch(NEUTRAL_CONFIG){
	case 1U:{
		u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1 + Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2) / 6.0f;
		u_n2 = u_n1;
		break;
	}
	case 2U:{
		u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1)/3.0f;
		u_n2 = (Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2)/3.0f;
		break;
	}
	case 3U:{
		u_a1c1 = Global_Data.av.v_a1 - Global_Data.av.v_c1;
		u_a2c2 = Global_Data.av.v_a2 - Global_Data.av.v_c2;
	}
	default: break;
	}
	// calc phase voltages with neutral voltage
	m_6ph_abc_voltage.a1 = Global_Data.av.v_a1 - u_n1;
	m_6ph_abc_voltage.b1 = Global_Data.av.v_b1 - u_n1;
	m_6ph_abc_voltage.c1 = Global_Data.av.v_c1 - u_n1;
	m_6ph_abc_voltage.a2 = Global_Data.av.v_a2 - u_n2;
	m_6ph_abc_voltage.b2 = Global_Data.av.v_b2 - u_n2;
	m_6ph_abc_voltage.c2 = Global_Data.av.v_c2 - u_n2;

	////////////Para ID actual
	ParaID_Data.ActualValues.i_abc_6ph = m_6ph_abc_currents;
	ParaID_Data.ActualValues.v_abc_6ph = m_6ph_abc_voltage;	ParaID_Data.ActualValues.V_DC = (Global_Data.av.v_dc1 + Global_Data.av.v_dc2)/2.0f;
	ParaID_Data.ActualValues.omega_m = Global_Data.av.mechanicalRotorSpeedRADpS;
	ParaID_Data.ActualValues.omega_el = Global_Data.av.electricalRotorSpeedRADpS;
	ParaID_Data.ActualValues.theta_m = theta_mech_calc_from_resolver;
	ParaID_Data.ActualValues.theta_el = ParaID_Data.ActualValues.theta_m * Global_Data.av.polepairs - ParaID_Data.ElectricalID_Output->thetaOffset;
//	ParaID_Data.ActualValues.theta_m = theta_mech_calc_from_resolver - Global_Data.av.theta_mech_offset_rad;
//	ParaID_Data.ActualValues.theta_el = ParaID_Data.ActualValues.theta_m * Global_Data.av.polepairs;
	ParaID_Data.ActualValues.average_winding_temp = Global_Data.av.avg_winding_temperature;
	// inside:
	uz_ParameterID_6ph_process_actual_values(&ParaID_Data, u_a1c1, u_a2c2);
	//////////////ParaID ende


	// actual currents
	Global_Data.av.i_abc_6ph = m_6ph_abc_voltage;

	// actual currents in VSD-Systems
	Global_Data.av.i_vsd_6ph = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Global_Data.av.i_abc_6ph);
	Global_Data.av.i_alphabeta.alpha = Global_Data.av.i_vsd_6ph.alpha;
	Global_Data.av.i_alphabeta.beta = Global_Data.av.i_vsd_6ph.beta;
	Global_Data.av.i_alphabeta.gamma = 0.0f;

	Global_Data.av.i_xy.alpha = Global_Data.av.i_vsd_6ph.x;
	Global_Data.av.i_xy.beta = Global_Data.av.i_vsd_6ph.y;
	Global_Data.av.i_xy.gamma = 0.0f;

	Global_Data.av.i_zero.d = Global_Data.av.i_vsd_6ph.z1;
	Global_Data.av.i_zero.q = Global_Data.av.i_vsd_6ph.z2;
	Global_Data.av.i_zero.zero = 0.0f;

	// actual velocity and angle
	ParaID_Data.ActualValues.omega_m = Global_Data.av.mechanicalRotorSpeedRADpS;
	ParaID_Data.ActualValues.omega_el = Global_Data.av.electricalRotorSpeedRADpS;
	Global_Data.av.theta_mech_rad = theta_mech_calc_from_resolver - Global_Data.av.theta_mech_offset_rad;
	Global_Data.av.theta_elec_rad = Global_Data.av.theta_mech_rad * Global_Data.av.polepairs;

	Global_Data.av.i_dq = uz_transformation_3ph_alphabeta_to_dq(Global_Data.av.i_alphabeta, Global_Data.av.theta_elec_rad);

	// reference currents in VSD-Systems
	Global_Data.rasv.i_dq_ref.d = 0;
	Global_Data.rasv.i_dq_ref.q = 1;
	Global_Data.rasv.i_dq_ref.zero = 0;
	Global_Data.rasv.i_alphabeta_ref = uz_transformation_3ph_dq_to_alphabeta(Global_Data.rasv.i_dq_ref, Global_Data.av.theta_elec_rad);

	Global_Data.rasv.i_vsd_6ph_ref.alpha = Global_Data.rasv.i_alphabeta_ref.alpha;
	Global_Data.rasv.i_vsd_6ph_ref.beta = Global_Data.rasv.i_alphabeta_ref.beta;
	Global_Data.rasv.i_vsd_6ph_ref.x = 0;
	Global_Data.rasv.i_vsd_6ph_ref.y = 0;
	Global_Data.rasv.i_vsd_6ph_ref.z1 = 0;
	Global_Data.rasv.i_vsd_6ph_ref.z2 = 0;

	Global_Data.rasv.i_xy_ref.alpha = Global_Data.rasv.i_vsd_6ph_ref.x;
	Global_Data.rasv.i_xy_ref.beta = Global_Data.rasv.i_vsd_6ph_ref.x;
	Global_Data.rasv.i_zero_ref.d = Global_Data.rasv.i_vsd_6ph_ref.z1;
	Global_Data.rasv.i_zero_ref.q = Global_Data.rasv.i_vsd_6ph_ref.z2;


    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==control_state)
    {
    	//ParaID
		uz_ParameterID_6ph_step(ParameterID, &ParaID_Data);
		controller_out = uz_ParameterID_6ph_Controller(ParameterID, &ParaID_Data);
		ParaID_DutyCycle = uz_ParameterID_6ph_generate_DutyCycle(&ParaID_Data, controller_out);
		// change DutyCycles=0 to 0.01
		ParaID_DutyCycle.system1 = dc_non_zero(ParaID_DutyCycle.system1);
		ParaID_DutyCycle.system2 = dc_non_zero(ParaID_DutyCycle.system2);


		// dq control
			// PI-Control
			Global_Data.rasv.u_dq_ref = uz_CurrentControl_sample(Global_Data.objects.CC_instance_dq, Global_Data.rasv.i_dq_ref, Global_Data.av.i_dq, Global_Data.av.v_dc1, Global_Data.av.electricalRotorSpeedRADpS);
			// Resonant-Control

			// Reverse-Transformation in alpha-beta system
			Global_Data.rasv.u_alphabeta_ref = uz_transformation_3ph_dq_to_alphabeta(Global_Data.rasv.u_dq_ref, Global_Data.av.theta_elec_rad);

		// xy control
			// Transformation in rotating system
			Global_Data.rasv.i_xy_n_ref = uz_transformation_3ph_alphabeta_to_dq(Global_Data.rasv.i_xy_ref, -Global_Data.av.theta_elec_rad);
			Global_Data.av.i_xy_n     = uz_transformation_3ph_alphabeta_to_dq(Global_Data.av.i_xy,     -Global_Data.av.theta_elec_rad);
			// PI-control
			Global_Data.rasv.u_xy_n_ref = uz_CurrentControl_sample(Global_Data.objects.CC_instance_xy, Global_Data.rasv.i_xy_n_ref, Global_Data.av.i_xy_n, Global_Data.av.v_dc1, Global_Data.av.electricalRotorSpeedRADpS);
			// Resonant-Control

			// Reverse-Transformation back in stationary system
			Global_Data.rasv.u_xy_ref = uz_transformation_3ph_dq_to_alphabeta(Global_Data.rasv.u_xy_n_ref, -Global_Data.av.theta_elec_rad);


		// zero control
			// PI-control
			Global_Data.rasv.u_zero_ref = uz_CurrentControl_sample(Global_Data.objects.CC_instance_zero, Global_Data.rasv.i_zero_ref, Global_Data.av.i_zero, Global_Data.av.v_dc1, Global_Data.av.electricalRotorSpeedRADpS);
			// Resonant-Control


		// combined vsd-ref values:
		Global_Data.rasv.u_vsd_6ph_ref.alpha = Global_Data.rasv.u_alphabeta_ref.alpha;
		Global_Data.rasv.u_vsd_6ph_ref.beta  = Global_Data.rasv.u_alphabeta_ref.beta;
		Global_Data.rasv.u_vsd_6ph_ref.x     = Global_Data.rasv.u_xy_ref.alpha;
		Global_Data.rasv.u_vsd_6ph_ref.y     = Global_Data.rasv.u_xy_ref.beta;
		Global_Data.rasv.u_vsd_6ph_ref.z1    = Global_Data.rasv.u_zero_ref.d;
		Global_Data.rasv.u_vsd_6ph_ref.z2    = Global_Data.rasv.u_zero_ref.q;

		// inverse vsd Transformation
		Global_Data.rasv.u_abc_6ph_ref = uz_transformation_asym30deg_6ph_alphabeta_to_abc(Global_Data.rasv.u_vsd_6ph_ref);

		// split into two three phase systems
		Global_Data.rasv.u_abc_sys1_ref.a = Global_Data.rasv.u_abc_6ph_ref.a1;
		Global_Data.rasv.u_abc_sys1_ref.b = Global_Data.rasv.u_abc_6ph_ref.b1;
		Global_Data.rasv.u_abc_sys1_ref.c = Global_Data.rasv.u_abc_6ph_ref.c1;
		Global_Data.rasv.u_abc_sys2_ref.a = Global_Data.rasv.u_abc_6ph_ref.a2;
		Global_Data.rasv.u_abc_sys2_ref.b = Global_Data.rasv.u_abc_6ph_ref.b2;
		Global_Data.rasv.u_abc_sys2_ref.c = Global_Data.rasv.u_abc_6ph_ref.c2;

		// transform into dq-systems for Space Vector Modulation
		Global_Data.rasv.u_dq_sys1_ref = uz_transformation_3ph_abc_to_dq(Global_Data.rasv.u_abc_sys1_ref, Global_Data.av.theta_elec_rad);
		Global_Data.rasv.u_dq_sys2_ref = uz_transformation_3ph_abc_to_dq(Global_Data.rasv.u_abc_sys2_ref, Global_Data.av.theta_elec_rad);


		Global_Data.rasv.DutyCycle_system1 = uz_Space_Vector_Modulation(Global_Data.rasv.u_dq_sys1_ref, Global_Data.av.v_dc1, Global_Data.av.theta_elec_rad);
		Global_Data.rasv.DutyCycle_system2 = uz_Space_Vector_Modulation(Global_Data.rasv.u_dq_sys2_ref, Global_Data.av.v_dc2, Global_Data.av.theta_elec_rad);




		// write DutyCycles
		Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.DutyCycle_system1.DutyCycle_A; //ParaID_DutyCycle.system1.DutyCycle_A;
		Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.DutyCycle_system1.DutyCycle_B; //ParaID_DutyCycle.system1.DutyCycle_B;
		Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.DutyCycle_system1.DutyCycle_C; //ParaID_DutyCycle.system1.DutyCycle_C;
		Global_Data.rasv.halfBridge4DutyCycle = Global_Data.rasv.DutyCycle_system2.DutyCycle_A; //ParaID_DutyCycle.system2.DutyCycle_A;
		Global_Data.rasv.halfBridge5DutyCycle = Global_Data.rasv.DutyCycle_system2.DutyCycle_B; //ParaID_DutyCycle.system2.DutyCycle_B;
		Global_Data.rasv.halfBridge6DutyCycle = Global_Data.rasv.DutyCycle_system2.DutyCycle_C; //ParaID_DutyCycle.system2.DutyCycle_C;

		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_0_to_5, ParaID_Data.ElectricalID_Output->enable_TriState[0], ParaID_Data.ElectricalID_Output->enable_TriState[1], ParaID_Data.ElectricalID_Output->enable_TriState[2]);
		uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_6_to_11, ParaID_Data.ElectricalID_Output->enable_TriState_set_2[0], ParaID_Data.ElectricalID_Output->enable_TriState_set_2[1], ParaID_Data.ElectricalID_Output->enable_TriState_set_2[2]);
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

    uz_ParameterID_6ph_step(ParameterID, &ParaID_Data);

    // Determine mechanical angle of resolver
    if(theta_mech_old-Global_Data.av.theta_mech_rad > 4.0f) {
    	cnt++;
    	cnt_float=(float)cnt;
    } else if (theta_mech_old-Global_Data.av.theta_mech_rad < -4.0f) {
    	cnt--;
    	cnt_float=(float)cnt;
    }

    if(cnt > 1 || cnt < -1) {
    	cnt = 0;
    	cnt_float = 0.0f;
    }

    if(cnt_reset == 1) {
    	cnt = 0;
    	cnt_float = 0;
    	cnt_reset = 0;
    	cnt_reset_float=0;
    }


    if(cnt >= 0){
    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech_rad/uz_resolverIP_getResolverPolePairs(Global_Data.objects.resolver_d5_1) + cnt*2*UZ_PIf/2.0f;
    } else {
    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech_rad/2.0f + (2+cnt)*2*UZ_PIf/2.0f;
    }

    theta_mech_old = Global_Data.av.theta_mech_rad;

    // reset SW and FPGA resolver calculation counter for having defined init state
	if (first_ISR == true) {
		cnt = 0;
		cnt_float = 0.0f;
		first_ISR = false;
	}

    if (Global_Data.av.theta_mech_rad <= theta_m_min) {
    	theta_m_min = Global_Data.av.theta_mech_rad;
    }

    if (Global_Data.av.theta_mech_rad >= theta_m_max) {
    	theta_m_max = Global_Data.av.theta_mech_rad;
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

struct uz_DutyCycle_t dc_non_zero(struct uz_DutyCycle_t uncorrected){
	struct uz_DutyCycle_t corrected = uncorrected;
	if(corrected.DutyCycle_A == 0.0f)
		corrected.DutyCycle_A =  0.01f;
	if(corrected.DutyCycle_B == 0.0f)
		corrected.DutyCycle_B =  0.01f;
	if(corrected.DutyCycle_C == 0.0f)
		corrected.DutyCycle_C =  0.01f;
	return corrected;
}

uz_6ph_abc_t zero_offset_function(bool* flag){
	static uz_6ph_abc_t data[1000];
	static uz_6ph_abc_t sum = {0};
	static int i = 0;
	uz_6ph_abc_t out = {0};
	data[i].a1 = Global_Data.av.v_a1;
	sum.a1 = sum.a1 + data[i].a1;
	data[i].b1 = Global_Data.av.v_b1;
	sum.b1 = sum.b1 + data[i].b1;
	data[i].c1 = Global_Data.av.v_c1;
	sum.c1 = sum.c1 + data[i].c1;
	data[i].a2 = Global_Data.av.v_a2;
	sum.a2 = sum.a2 + data[i].a2;
	data[i].b2 = Global_Data.av.v_b2;
	sum.b2 = sum.b2 + data[i].b2;
	data[i].c2 = Global_Data.av.v_c2;
	sum.c2 = sum.c2 + data[i].c2;
	i++;
	if(i==999){
		out.a1 = sum.a1/i;
		out.b1 = sum.b1/i;
		out.c1 = sum.c1/i;
		out.a2 = sum.a2/i;
		out.b2 = sum.b2/i;
		out.c2 = sum.c2/i;
		*flag = true;
	}
	return out;
}
