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
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "../IP_Cores/uz_dataMover/uz_dataMover.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../include/pwm_init.h"
#include "../include/project_wizard_visualization.h"
#include "../uz/uz_pmsm_control/uz_pmsm_control.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;
extern struct uz_PMSM_t Beckhoff_AM8071_0R01;

bool HB_ok = false;
bool OC_ok = false;
bool reset_button_inv = false;
bool reset_button_was_pressed = false;
bool enable_controller_Beckhoff = false;
bool acknowledge_error = false;
uz_3ph_dq_t current_reference_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
uz_3ph_dq_t v_dq_ref_Beckhoff = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
struct uz_pmsmModel_inputs_t pmsm_cil_inputs_Beckhoff = {0.0f};
struct uz_pmsmModel_outputs_t pmsm_cil_outputs_Beckhoff = {0.0f};
struct uz_3ph_abc_t i_abc_cil = {0.0f};
struct uz_3ph_dq_t i_dq_Beckhoff_cil = {0.0f};
struct uz_pmsm_measurement_values measurements_Beckhoff;
struct uz_DutyCycle_t duty_cycle_Beckhoff = {0.0f};
float theta_mech_Beckhoff = 0.0f;

#define		VOLTAGE_2_SI_VOLTS_DHG 		363.6f
#define		VOLTAGE_2_SI_VOLTS_DHG_CH3	37.037f
#define		VOLTAGE_2_SI_VOLTS_DHG_CH4	142.3f
#define		CURRENT_CONV_HASS_50		40.0f // 50.0f / 0.625f datasheet
#define		MAX_CURRENT					50.0f
#define		V_DC						48.0f//565.0f
#define		SAMPLE_TIME_CIL				0.0001f

/* Project Wizard BEGIN: adc_readout_definitions */
static uz_array_int16_t analog_adc_data;
/* Project Wizard END: adc_readout_definitions */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);
static void update_adapter_a1(void);
static void update_adapter_a2(void);
static void update_adapter_a3(void);
static void update_adapter_d1(void);
static void update_adapter_d2(void);
static void update_adapter_d3(void);
static void update_adapter_d4(void);
static void update_adapter_d5(void);

static void read_adapter_cards(void);
static void get_cil_measurements(void);
static void get_real_measurements(void);
static void perform_one_controller_step();
static void set_controller_outputs_cil(void);
static void set_controller_outputs_real(void);

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr

    read_adapter_cards();

    // get measurement values
    if (Global_Data.rasv.control_mode_select == CIL) {
    	get_cil_measurements();
    	perform_one_controller_step();
    	set_controller_outputs_cil();
    } else if (Global_Data.rasv.control_mode_select == REAL) {
    	get_real_measurements();
    	perform_one_controller_step();
    	set_controller_outputs_real();
    }

    // Check for safe operating region violation
    Global_Data.av.status_safe_operating_area_violation = uz_pmsm_control_get_safe_operating_area_violation(Global_Data.objects.pmsm_control_Beckhoff_AM8071);
    if (Global_Data.av.status_safe_operating_area_violation != uz_pmsm_control_no_violation) {
//    	ultrazohm_state_machine_set_stop(true);
    	ultrazohm_state_machine_set_error(true);
    	ultrazohm_state_machine_set_userLED(true);
    }
    if (Global_Data.rasv.control_mode_select == REAL) {
        // read in status of hardware switch off of inverter
        HB_ok = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.axi_gpio_d1,14);
        OC_ok = uz_axi_gpio_read_pin_zero_based(Global_Data.objects.axi_gpio_d1,15);
        if ((HB_ok == false || OC_ok == false) && reset_button_was_pressed == true) {
        	ultrazohm_state_machine_set_stop(true);
        }
    }

    platform_state_t current_state = ultrazohm_state_machine_get_state();
    if (current_state == idle_state)
    {
    	// Reset DHG inverter
        if (reset_button_inv == true) {
        	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1,6,1);
        	reset_button_was_pressed = true;
        	reset_button_inv = false;
    //		    	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio,0,0);
        } else {
        	uz_axi_gpio_write_pin_zero_based(Global_Data.objects.axi_gpio_d1,6,0);
        }
    	enable_controller_Beckhoff = false;
    	uz_pmsm_control_enable(Global_Data.objects.pmsm_control_Beckhoff_AM8071, enable_controller_Beckhoff);
    	uz_pmsm_control_reset(Global_Data.objects.pmsm_control_Beckhoff_AM8071);
        /* Project Wizard BEGIN: idle_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
/* Project Wizard END: idle_state isr_actions */
        theta_mech_Beckhoff = 0.0f;
    }
    else if ((current_state == running_state) && (Global_Data.rasv.control_mode_select == REAL))
    {
        /* Project Wizard BEGIN: running_state isr_actions */
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, false, false, false);
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, false, false, false);
/* Project Wizard END: running_state isr_actions */
    }
    else if (current_state == control_state)
    {
        // Start: Control algorithm - only if ultrazohm is in control state
    	enable_controller_Beckhoff = true;
    	uz_pmsm_control_enable(Global_Data.objects.pmsm_control_Beckhoff_AM8071, enable_controller_Beckhoff);

        /* Project Wizard BEGIN: control_state isr_actions */
/* Project Wizard END: control_state isr_actions */
    }
    else if (current_state == error_state)
    {
    	enable_controller_Beckhoff = false;
    	uz_pmsm_control_enable(Global_Data.objects.pmsm_control_Beckhoff_AM8071, enable_controller_Beckhoff);
        /* Project Wizard BEGIN: error_state isr_actions */
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_0, true, true, true);
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_1 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_2 = 0.0f;
        Global_Data.rasv.pwm_2L_1_halfBridgeDutyCycle_3 = 0.0f;
        uz_PWM_SS_2L_set_tristate(Global_Data.objects.project_wizard_pwm_2l_1, true, true, true);
/* Project Wizard END: error_state isr_actions */
    	if (acknowledge_error == true) {
            uz_pmsm_control_acknowledge_and_reset_error(Global_Data.objects.pmsm_control_Beckhoff_AM8071, measurements_Beckhoff);
            ultrazohm_state_machine_set_stop(true);
			ultrazohm_state_machine_set_userLED(false);
			acknowledge_error = false;
    	}
    }
    
    /* Project Wizard BEGIN: pwm_runtime */
    project_wizard_update_pwm_outputs(&Global_Data);
/* Project Wizard END: pwm_runtime */

    project_wizard_visualization_update(&Global_Data);
    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

static void update_adapter_a1(void)
{
    /* Project Wizard BEGIN: A1 isr_control */
    Global_Data.av.adc_ltc2311_a1_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[0], 0U);
    Global_Data.av.adc_ltc2311_a1_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[1], 1U);
    Global_Data.av.adc_ltc2311_a1_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[2], 2U);
    Global_Data.av.adc_ltc2311_a1_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[3], 3U);
    Global_Data.av.adc_ltc2311_a1_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[4], 4U);
    Global_Data.av.adc_ltc2311_a1_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[5], 5U);
    Global_Data.av.adc_ltc2311_a1_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[6], 6U);
    Global_Data.av.adc_ltc2311_a1_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a1, analog_adc_data.data[7], 7U);
/* Project Wizard END: A1 isr_control */
}

static void update_adapter_a2(void)
{
    /* Project Wizard BEGIN: A2 isr_control */
    Global_Data.av.adc_ltc2311_a2_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[8], 0U);
    Global_Data.av.adc_ltc2311_a2_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[9], 1U);
    Global_Data.av.adc_ltc2311_a2_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[10], 2U);
    Global_Data.av.adc_ltc2311_a2_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[11], 3U);
    Global_Data.av.adc_ltc2311_a2_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[12], 4U);
    Global_Data.av.adc_ltc2311_a2_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[13], 5U);
    Global_Data.av.adc_ltc2311_a2_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[14], 6U);
    Global_Data.av.adc_ltc2311_a2_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a2, analog_adc_data.data[15], 7U);
/* Project Wizard END: A2 isr_control */
}

static void update_adapter_a3(void)
{
    /* Project Wizard BEGIN: A3 isr_control */
    Global_Data.av.adc_ltc2311_a3_ch0 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[16], 0U);
    Global_Data.av.adc_ltc2311_a3_ch1 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[17], 1U);
    Global_Data.av.adc_ltc2311_a3_ch2 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[18], 2U);
    Global_Data.av.adc_ltc2311_a3_ch3 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[19], 3U);
    Global_Data.av.adc_ltc2311_a3_ch4 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[20], 4U);
    Global_Data.av.adc_ltc2311_a3_ch5 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[21], 5U);
    Global_Data.av.adc_ltc2311_a3_ch6 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[22], 6U);
    Global_Data.av.adc_ltc2311_a3_ch7 = uz_adcLtc2311_convert_raw_to_physical_value(Global_Data.objects.adc_ltc2311_a3, analog_adc_data.data[23], 7U);
/* Project Wizard END: A3 isr_control */
}

static void update_adapter_d1(void)
{
    /* Project Wizard BEGIN: D1 isr_control */
    Global_Data.av.io_card_d1_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_d1);
/* Project Wizard END: D1 isr_control */
}

static void update_adapter_d2(void)
{
    /* Project Wizard BEGIN: D2 isr_control */
    Global_Data.av.io_card_d2_state = uz_axi_gpio_read_bitmask(Global_Data.objects.axi_gpio_d2);
/* Project Wizard END: D2 isr_control */
}

static void update_adapter_d3(void)
{
    /* Project Wizard BEGIN: D3 isr_control */
    uz_TempCard_IF_MeasureTemps_cyclic(Global_Data.objects.temperature_card_d3);
    Global_Data.av.temperature_card_d3_channel_A = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d3, 'A');
    Global_Data.av.temperature_card_d3_channel_B = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d3, 'B');
    Global_Data.av.temperature_card_d3_channel_C = uz_TempCard_IF_get_channel_group(Global_Data.objects.temperature_card_d3, 'C');
/* Project Wizard END: D3 isr_control */
}

static void update_adapter_d4(void)
{
    /* Project Wizard BEGIN: D4 isr_control */
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_1_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_1);
    Global_Data.av.resolver_pl_interface_d4_1_revolution_counter = resolver_pl_interface_d4_1_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_1_position_mech_2pi = resolver_pl_interface_d4_1_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_1_position_el_2pi = resolver_pl_interface_d4_1_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_1_omega_mech_rad_s = resolver_pl_interface_d4_1_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_1_n_mech_rpm = resolver_pl_interface_d4_1_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_1_omega_el_rad_s = resolver_pl_interface_d4_1_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_1);
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_2_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_2);
    Global_Data.av.resolver_pl_interface_d4_2_revolution_counter = resolver_pl_interface_d4_2_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_2_position_mech_2pi = resolver_pl_interface_d4_2_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_2_position_el_2pi = resolver_pl_interface_d4_2_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_2_omega_mech_rad_s = resolver_pl_interface_d4_2_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_2_n_mech_rpm = resolver_pl_interface_d4_2_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_2_omega_el_rad_s = resolver_pl_interface_d4_2_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_2);
    struct uz_resolver_pl_interface_outputs_t resolver_pl_interface_d4_3_outputs = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface_d4_3);
    Global_Data.av.resolver_pl_interface_d4_3_revolution_counter = resolver_pl_interface_d4_3_outputs.revolution_counter;
    Global_Data.av.resolver_pl_interface_d4_3_position_mech_2pi = resolver_pl_interface_d4_3_outputs.position_mech_2pi;
    Global_Data.av.resolver_pl_interface_d4_3_position_el_2pi = resolver_pl_interface_d4_3_outputs.position_el_2pi;
    Global_Data.av.resolver_pl_interface_d4_3_omega_mech_rad_s = resolver_pl_interface_d4_3_outputs.omega_mech_rad_s;
    Global_Data.av.resolver_pl_interface_d4_3_n_mech_rpm = resolver_pl_interface_d4_3_outputs.n_mech_rpm;
    Global_Data.av.resolver_pl_interface_d4_3_omega_el_rad_s = resolver_pl_interface_d4_3_outputs.omega_mech_rad_s * uz_resolverIP_getMachinePolePairs(Global_Data.objects.resolver_ip_d4_3);
/* Project Wizard END: D4 isr_control */
}

static void update_adapter_d5(void)
{
    /* Project Wizard BEGIN: D5 isr_control */
    Global_Data.av.incremental_encoder_d5_1_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_1_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_1);
    Global_Data.av.incremental_encoder_d5_2_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_2_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_2);
    Global_Data.av.incremental_encoder_d5_3_theta_el = uz_incrementalEncoder_get_theta_el(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech = uz_incrementalEncoder_get_omega_mech(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_omega_mech_ma_n4 = uz_incrementalEncoder_get_omega_mech_MA_N4(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position = uz_incrementalEncoder_get_position(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_position_w_offset = uz_incrementalEncoder_get_position_wOffset(Global_Data.objects.incremental_encoder_d5_3);
    Global_Data.av.incremental_encoder_d5_3_index_found = uz_incrementalEncoder_get_Index_Found(Global_Data.objects.incremental_encoder_d5_3);
/* Project Wizard END: D5 isr_control */
}

//==============================================================================================================================================================

static void read_adapter_cards(void)
{
	/* Project Wizard BEGIN: adc_readout */
	    analog_adc_data = uz_dataMover_update_buffer_and_get_data();
	/* Project Wizard END: adc_readout */
	    update_adapter_a1();
	    update_adapter_a2(); // DHG inverter ADC
	    update_adapter_a3();
	    update_adapter_d1(); // DHG inverter optical
	    update_adapter_d2();
	    update_adapter_d3();
	    update_adapter_d4(); // Resolver, 1: Beckhoff, 3: HM
	    update_adapter_d5();
}

static void get_cil_measurements(void)
{
    // trigger input and output strobe
    uz_pmsmModel_trigger_input_strobe(Global_Data.objects.pmsm_cil_Beckhoff);
	uz_pmsmModel_trigger_output_strobe(Global_Data.objects.pmsm_cil_Beckhoff);

	// assign output values to variables
	pmsm_cil_outputs_Beckhoff = uz_pmsmModel_get_outputs(Global_Data.objects.pmsm_cil_Beckhoff);
	Global_Data.av.speed_n_rpm_Beckhoff = pmsm_cil_outputs_Beckhoff.omega_mech_1_s * 60.0f / (2.0f * UZ_PIf);
	Global_Data.av.i_d_Beckhoff = pmsm_cil_outputs_Beckhoff.i_d_A;
	Global_Data.av.i_q_Beckhoff = pmsm_cil_outputs_Beckhoff.i_q_A;
	i_dq_Beckhoff_cil = (struct uz_3ph_dq_t){.d = Global_Data.av.i_d_Beckhoff, .q = Global_Data.av.i_q_Beckhoff, .zero = 0.0f};
	Global_Data.av.theta_el_Beckhoff = theta_mech_Beckhoff * Beckhoff_AM8071_0R01.polePairs;
	i_abc_cil = uz_transformation_3ph_dq_to_abc(i_dq_Beckhoff_cil, Global_Data.av.theta_el_Beckhoff);
	Global_Data.av.i_a_Beckhoff = i_abc_cil.a;
	Global_Data.av.i_b_Beckhoff = i_abc_cil.b;
	Global_Data.av.i_c_Beckhoff = i_abc_cil.c;

	// assign values to measurement struct for pmsm control module
	Global_Data.av.v_dc_Beckhoff = V_DC; // fixed value in CIL
	Global_Data.av.i_dc_Beckhoff = 0.0f;
	measurements_Beckhoff = (struct uz_pmsm_measurement_values){
		.i_abc_in_A = {.a = Global_Data.av.i_a_Beckhoff, .b = Global_Data.av.i_b_Beckhoff, .c = Global_Data.av.i_c_Beckhoff},
		.v_abc_in_V = uz_transformation_3ph_dq_to_abc(v_dq_ref_Beckhoff, Global_Data.av.theta_el_Beckhoff),
		.v_dc_in_V = Global_Data.av.v_dc_Beckhoff,
		.i_dc_in_A = Global_Data.av.i_dc_Beckhoff,
		.omega_mech_rad_per_sec = pmsm_cil_outputs_Beckhoff.omega_mech_1_s,
		.theta_mech = theta_mech_Beckhoff};
	theta_mech_Beckhoff = uz_signals_wrap(theta_mech_Beckhoff + pmsm_cil_outputs_Beckhoff.omega_mech_1_s * SAMPLE_TIME_CIL, 2.0f*UZ_PIf); // Forward Euler integration of theta_mech
}

static void get_real_measurements(void)
{
	// assign measurements to Global_Data
	Global_Data.av.i_a_Beckhoff = Global_Data.av.adc_ltc2311_a2_ch0 * CURRENT_CONV_HASS_50 - 0.15f;
	Global_Data.av.i_b_Beckhoff = Global_Data.av.adc_ltc2311_a2_ch1 * CURRENT_CONV_HASS_50 + 0.1f;
	Global_Data.av.i_c_Beckhoff = Global_Data.av.adc_ltc2311_a2_ch2 * CURRENT_CONV_HASS_50 - 0.05f;
	Global_Data.av.i_dc_Beckhoff = Global_Data.av.adc_ltc2311_a2_ch7 * CURRENT_CONV_HASS_50 - 0.3f;
	Global_Data.av.v_a_Beckhoff = (Global_Data.av.adc_ltc2311_a2_ch4 - 0.0033f) * VOLTAGE_2_SI_VOLTS_DHG;
	Global_Data.av.v_b_Beckhoff = (Global_Data.av.adc_ltc2311_a2_ch5 - 0.001f) * VOLTAGE_2_SI_VOLTS_DHG;
	Global_Data.av.v_c_Beckhoff = (Global_Data.av.adc_ltc2311_a2_ch6 - 0.0017f) * VOLTAGE_2_SI_VOLTS_DHG_CH3;
	Global_Data.av.v_dc_Beckhoff = (Global_Data.av.adc_ltc2311_a2_ch3 + 0.0005f) * VOLTAGE_2_SI_VOLTS_DHG_CH4;

	// assign values to measurement struct for pmsm control module
	measurements_Beckhoff = (struct uz_pmsm_measurement_values){
        .i_abc_in_A = {.a = Global_Data.av.i_a_Beckhoff, .b = Global_Data.av.i_b_Beckhoff, .c = Global_Data.av.i_c_Beckhoff},
        .v_abc_in_V = {.a = Global_Data.av.v_a_Beckhoff, .b = Global_Data.av.v_b_Beckhoff, .c = Global_Data.av.v_c_Beckhoff},
        .v_dc_in_V = Global_Data.av.v_dc_Beckhoff,
        .i_dc_in_A = Global_Data.av.i_dc_Beckhoff,
        .omega_mech_rad_per_sec = Global_Data.av.resolver_pl_interface_d4_1_omega_mech_rad_s,
        .theta_mech = Global_Data.av.resolver_pl_interface_d4_1_position_mech_2pi};
}

static void perform_one_controller_step()
{
	// enable/disable speed control
    if (Global_Data.rasv.dut_control_select == speed) {
    	uz_pmsm_control_enable_speed_control(Global_Data.objects.pmsm_control_Beckhoff_AM8071,true);
    } else {
    	uz_pmsm_control_enable_speed_control(Global_Data.objects.pmsm_control_Beckhoff_AM8071,false);
    }

	// assign current reference (javascope user input)
	current_reference_A.d = Global_Data.rasv.i_d_ref_A_Beckhoff;
	current_reference_A.q = Global_Data.rasv.i_q_ref_A_Beckhoff;

	if (Global_Data.rasv.control_mode_select == CIL) {
		v_dq_ref_Beckhoff = (struct uz_3ph_dq_t)uz_pmsm_control_sample_dq(
			Global_Data.objects.pmsm_control_Beckhoff_AM8071,
			measurements_Beckhoff,
			Global_Data.rasv.speed_n_ref_rpm_Beckhoff,
			current_reference_A,
			0.0f);
		Global_Data.av.v_d_Beckhoff = v_dq_ref_Beckhoff.d;
		Global_Data.av.v_q_Beckhoff = v_dq_ref_Beckhoff.q;
	} else {
		struct uz_DutyCycle_t dutycycle_contr = uz_pmsm_control_sample_duty(
			Global_Data.objects.pmsm_control_Beckhoff_AM8071,
		    measurements_Beckhoff,
		    Global_Data.rasv.speed_n_ref_rpm_Beckhoff,
		    current_reference_A,
		    0.0f);
		if (Global_Data.rasv.dut_control_select == dutycycle) {
			duty_cycle_Beckhoff.DutyCycle_A = Global_Data.rasv.dutycycle_A_Beckhoff;
			duty_cycle_Beckhoff.DutyCycle_B = Global_Data.rasv.dutycycle_B_Beckhoff;
			duty_cycle_Beckhoff.DutyCycle_C = Global_Data.rasv.dutycycle_C_Beckhoff;
		} else {
			duty_cycle_Beckhoff.DutyCycle_A = dutycycle_contr.DutyCycle_A;
			duty_cycle_Beckhoff.DutyCycle_B = dutycycle_contr.DutyCycle_B;
			duty_cycle_Beckhoff.DutyCycle_C = dutycycle_contr.DutyCycle_C;
		}
	}
}

static void set_controller_outputs_cil(void)
{
	// assign and set pmsm model inputs
	pmsm_cil_inputs_Beckhoff.v_d_V = v_dq_ref_Beckhoff.d;
	pmsm_cil_inputs_Beckhoff.v_q_V = v_dq_ref_Beckhoff.q;
	pmsm_cil_inputs_Beckhoff.omega_mech_1_s = 2.0f * UZ_PIf * Global_Data.rasv.speed_n_ref_rpm_Beckhoff / 60.0f;
	uz_pmsmModel_set_inputs(Global_Data.objects.pmsm_cil_Beckhoff, pmsm_cil_inputs_Beckhoff);
}

static void set_controller_outputs_real(void)
{
	// set dutycycle
	Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_1 = duty_cycle_Beckhoff.DutyCycle_A;
    Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_2 = duty_cycle_Beckhoff.DutyCycle_B;
    Global_Data.rasv.pwm_2L_0_halfBridgeDutyCycle_3 = duty_cycle_Beckhoff.DutyCycle_C;
}

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
    Status = Rpu_GicInit(&GIC_instance, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable interrupt on CPU level
    Xil_ExceptionEnable();

    return Status;
}


/**
 * @brief Initialize the R5 GIC and connect/enable the PL-to-PS interrupt used by the RPU.
 *
 * @param[in,out] GIC_instance_ptr Pointer to an XScuGic instance to initialize.
 * @param[in]     DeviceId    GIC device ID (typically XPAR_SCUGIC_0_DEVICE_ID).
 *
 * @return XST_SUCCESS on success. This implementation asserts on failures.
 */
int Rpu_GicInit(XScuGic *GIC_instance_ptr, u16 DeviceId)
{
    XScuGic_Config *GIC_config;
    int status;

    // Disable all interrupts
    Xil_ExceptionDisable();

    GIC_config = XScuGic_LookupConfig(DeviceId);

    uz_assert_not_NULL(GIC_config);

    status = XScuGic_CfgInitialize(GIC_instance_ptr, GIC_config, GIC_config->CpuBaseAddress);
	uz_assert(status == XST_SUCCESS);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GIC_instance_ptr);

    // Clear latched active interrupt register - for UZ warm start
    uz_r5_gic_reset_active_pl_interrupts(GIC_instance_ptr);

    // Configure trigger/priority
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(GIC_instance_ptr, Interrupt_ISR_ID, 0x0, 0b11); // Trigger 0b11 = rising-edge, Trigger 0b01 = active-high

    // Connect handler
    status = XScuGic_Connect(GIC_instance_ptr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             NULL);
	uz_assert(status == XST_SUCCESS);

    // Enable only the connected interrupt
    XScuGic_Enable(GIC_instance_ptr, Interrupt_ISR_ID);

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
    XIpiPsu_Config *IPI_config;
    int status;

    // Interrupt controller configuration
    IPI_config = XIpiPsu_LookupConfig(DeviceId);
    if (IPI_config == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&IPI_instance, IPI_config, IPI_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: Rpu_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    /* Active status is in Distributor ACTIVE banked registers */
    const u32 reg = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bit = (u32)1U << (IntId % 32U);

    const u32 act = XScuGic_DistReadReg(Gic, reg);
    return ((act & bit) != 0U);
}


/**
 * @brief Clears stuck ACTIVE PL interrupts by writing GICC_EOIR (End Of Interrupt Register)
 * with the active interrupt ID, to enable soft restart without resetting entire system.
 *
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
 *
 * Call during GIC init, before enabling IRQ delivery on the R5.
 *
 */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic)
{
	// list of all PL Interrupt IDs
	const uint16_t uz_fpga_spi_ids[] = {
	    XPS_FPGA0_INT_ID,  XPS_FPGA1_INT_ID,  XPS_FPGA2_INT_ID,  XPS_FPGA3_INT_ID,
	    XPS_FPGA4_INT_ID,  XPS_FPGA5_INT_ID,  XPS_FPGA6_INT_ID,  XPS_FPGA7_INT_ID,
	    XPS_FPGA8_INT_ID,  XPS_FPGA9_INT_ID,  XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
	    XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID
	};

	uz_assert_not_NULL(Gic);
	uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
	for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids)/sizeof(uz_fpga_spi_ids[0])); ++i)
	{
		const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("RPU: GIC Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



