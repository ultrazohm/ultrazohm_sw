/******************************************************************************
 * Copyright 2021 Sebastian Wendel, Philipp Löhdefink
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

#include <string.h>
#include "../main.h"
#include "../include/ipc_ARM.h"
#include "../include/uz_platform_state_machine.h"
#include <stdbool.h>

// ======================= PMSM 1 ======================= //
// ---------------- Inverter Measurement ---------------- //

// --------- Field Oriented Control and Signals --------- //
extern float n_ref_rpm_1;
extern float M_ref_Nm_1;
extern float theta_el_offset_1;
extern struct uz_3ph_dq_t i_dq_ref_Amps_1;
extern struct uz_3ph_dq_t v_ind_dq_ref_Volts_1;

// ------------------- Wavegen Chirp -------------------- //
extern bool enable_excitation;
extern float excitation_amplitude;

// ======================= PMSM 2 ======================= //
// ---------------- Inverter Measurement ---------------- //

// --------- Field Oriented Control and Signals --------- //
extern float n_ref_rpm_2;
extern float M_ref_Nm_2;
extern float theta_el_offset_2;
extern struct uz_3ph_dq_t i_dq_ref_Amps_2;
extern struct uz_3ph_dq_t v_ind_dq_ref_Volts_2;

// ======================= Others ======================= //
extern int option;
extern struct uz_3ph_dq_t v_ind_dq_Volts_2 ;
extern float *js_ch_observable[JSO_ENDMARKER];
extern float *js_ch_selected[JS_CHANNELS];
extern uint32_t js_status_BareToRTOS;
extern enum running_mode run_state;
extern enum switch_control switch_control;
extern uz_parameterid_rs_t* test_instance;
extern struct uz_parameterid_output actual_output;
extern struct uz_3ph_dq_t cil_u_ind_Volts;
extern struct uz_3ph_dq_t cil_u_ind_ref_Volts;
extern float r_s_2;
extern float Kp_uind_d_2;
extern float Ki_uind_d_2;
extern float Kp_uind_q_2;
extern float Ki_uind_q_2;

void ipc_Control_func(uint32_t msgId, float value, DS_Data *data)
{
	// HANDLE RECEIVED MESSAGE
	if (msgId != 0)
	{
		// GENERAL VARIABLES
		switch (msgId)
		{

		case (Stop): // Stop
			ultrazohm_state_machine_set_stop(true);
			break;
		case (201): // SELECT_DATA_CH1_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[0] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (202): // SELECT_DATA_CH2_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[1] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (203): // SELECT_DATA_CH3_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[2] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (204): // SELECT_DATA_CH4_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[3] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (205): // SELECT_DATA_CH5_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[4] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (206): // SELECT_DATA_CH6_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[5] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (207): // SELECT_DATA_CH7_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[6] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (208): // SELECT_DATA_CH8_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[7] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (209): // SELECT_DATA_CH9_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[8] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (210): // SELECT_DATA_CH10_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[9] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (211): // SELECT_DATA_CH11_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[10] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (212): // SELECT_DATA_CH12_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[11] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (213): // SELECT_DATA_CH13_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[12] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (214): // SELECT_DATA_CH14_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[13] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (215): // SELECT_DATA_CH15_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[14] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (216): // SELECT_DATA_CH16_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[15] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (217): // SELECT_DATA_CH17_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[16] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (218): // SELECT_DATA_CH18_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[17] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (219): // SELECT_DATA_CH19_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[18] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (220): // SELECT_DATA_CH20_bits
			if (value >= 0 && value < JSO_ENDMARKER)
			{
				js_ch_selected[19] = js_ch_observable[(uint32_t)value];
			}
			break;

		case (Enable_System): // ConverterEnable
			ultrazohm_state_machine_set_enable_system(true);
			break;

		case (Enable_Control): // ControlEnable
			ultrazohm_state_machine_set_enable_control(true);

			break;

		case (Set_Send_Field_1):
		n_ref_rpm_2 = value;
			break;

		case (Set_Send_Field_2):
		i_dq_ref_Amps_1.d = value;
			break;

		case (Set_Send_Field_3):
		i_dq_ref_Amps_1.q = value;
			break;

		case (Set_Send_Field_4):
		r_s_2 = value;
			break;

		case (Set_Send_Field_5):
		v_ind_dq_ref_Volts_1.d = value;
			break;

		case (Set_Send_Field_6):
		v_ind_dq_ref_Volts_1.q = value;
			break;

		case (Set_Send_Field_7):
		Kp_uind_d_2 = value;
			break;

		case (Set_Send_Field_8):
		Ki_uind_d_2 = value;
			break;

		case (Set_Send_Field_9):
		Kp_uind_q_2 = value;
			break;

		case (Set_Send_Field_10):
		Ki_uind_q_2 = value;
			break;

		case (Set_Send_Field_11):

			break;

		case (Set_Send_Field_12):

			break;

		case (Set_Send_Field_13):

			break;

		case (Set_Send_Field_14):

			break;

		case (Set_Send_Field_15):

			break;

		case (Set_Send_Field_16):

			break;

		case (Set_Send_Field_17):

			break;

		case (Set_Send_Field_18):

			break;

		case (Set_Send_Field_19):

			break;

		case (Set_Send_Field_20):

			break;

		case (My_Button_1):
			ultrazohm_state_machine_set_error(true);
			break;

		case (My_Button_2):
			switch_control = control_uind;
			ultrazohm_state_machine_set_userLED(true);
			break;

		case (My_Button_3):
			run_state = rc_measurement_Hoerner;
			ultrazohm_state_machine_set_userLED(true);
			break;

		case (My_Button_4):
			run_state = rs_measurement_Hoerner;
			ultrazohm_state_machine_set_userLED(true);
			break;

		case (My_Button_5):
			run_state = rs_measurement;
			ultrazohm_state_machine_set_userLED(true);
			break;

		case (My_Button_6):
			run_state = rc_measurement;
			ultrazohm_state_machine_set_userLED(true);
			break;

		case (My_Button_7):
			run_state = normal;
			ultrazohm_state_machine_set_userLED(true);
			break;

		case (My_Button_8):
			run_state = reset;
			ultrazohm_state_machine_set_userLED(false);
			break;


		case (Error_Reset):

			break;

		case (0xFFFF):
			// this is triggered if the IPI message buffer is read without being written once before (i.e. at startup)
			break;

		default:
			break;		  // Default just breaks since now a lot of unused control worlds are sent from the javascope->a53 which are never handled here.
			uz_assert(0); // unknown command -> throw error
		}
	}

	platform_state_t current_state = ultrazohm_state_machine_get_state();
	// Feedback bits for controlling the status indicators in the GUI
	/* Bit 0 - Ready LED */
	if (ultrazohm_state_get_led_ready()) {
	js_status_BareToRTOS |= 1 << 0;
	} else {
		js_status_BareToRTOS &= ~(1 << 0);
	}

	/* Bit 1 - Running LED */
	if (ultrazohm_state_get_led_running()) {
	js_status_BareToRTOS |= 1 << 1;
	} else {
		js_status_BareToRTOS &= ~(1 << 1);
	}

	/* Bit 2 - Error LED */
	if (ultrazohm_state_get_led_error()) {
		js_status_BareToRTOS |= 1 << 2;
		} else {
			js_status_BareToRTOS &= ~(1 << 2);
		}

	/* Bit 3 - User LED */
	if (ultrazohm_state_get_led_user()) {
		js_status_BareToRTOS |= 1 << 3;
		} else {
			js_status_BareToRTOS &= ~(1 << 3);
		}

	/* Bit 4 - My_Button_1 */
	//if (your condition = true) {
	//	js_status_BareToRTOS |= (1 << 4);
	//} else {
	//	js_status_BareToRTOS &= ~(1 << 4);
	//}

	/* Bit 5 - My_Button_2 */
	// js_status_BareToRTOS &= ~(1 << 5);

	/* Bit 6 - My_Button_3 */
    if (run_state == rs_measurement_Hoerner) {
       js_status_BareToRTOS |= 1 << 6;
    } else {
    	js_status_BareToRTOS &= ~(1 << 6);;
    }

	/* Bit 7 - My_Button_4 */
    if (run_state == rs_measurement_Hoerner) {
       js_status_BareToRTOS |= 1 << 7;
    } else {
       js_status_BareToRTOS &= ~(1 << 7);
    }

	/* Bit 8 - My_Button_5 */
    if (run_state == rs_measurement) {
       js_status_BareToRTOS |= 1 << 8;
    } else {
       js_status_BareToRTOS &= ~(1 << 8);
    }

	/* Bit 9 - My_Button_6 */
    if (run_state == rc_measurement) {
       js_status_BareToRTOS |= 1 << 9;
    } else {
       js_status_BareToRTOS &= ~(1 << 9);
    }

	/* Bit 10 - My_Button_7 */
    if (run_state == normal ) {
       js_status_BareToRTOS |= 1 << 10;
    } else {
       js_status_BareToRTOS &= ~(1 << 10);
    }

	/* Bit 11 - My_Button_8 */
    if (run_state == reset ) {
       js_status_BareToRTOS |= 1 << 11;
    } else {
       js_status_BareToRTOS &= ~(1 << 11);
    }

	/* Bit 12 - trigger ext. logging */
	// if (your condition == true) {
	//	js_status_BareToRTOS |= (1 << 12);
	// } else {
	//	js_status_BareToRTOS &= ~(1 << 12);
	// }

}
