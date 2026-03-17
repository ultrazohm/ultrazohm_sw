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
#include "../include/error_checks.h"
#include <stdbool.h>

extern float *js_ch_observable[JSO_ENDMARKER];
extern float *js_ch_selected[JS_CHANNELS];

extern uint32_t js_status_BareToRTOS;

// V/f Control Parameters from isr.c
extern float vf_frequency_setpoint_Hz;
extern bool enable_controller_VA;
extern bool enable_controller_IM;

extern bool va_use_speed_control;
extern void reset_VA(void);
extern void reset_im(void);
// FOC / observer control parameters from isr.c
extern bool use_foc;
extern bool use_speed_control;
extern bool use_kalman_filter;
extern bool use_deterministic_observer;
extern bool use_resonant_6th;
extern float kf_q_i;
extern float kf_q_psi;
extern float kf_r_i;
extern float id_ref_A;
extern float iq_ref_A;
extern float speed_ref_rpm;
extern float im_speed_pi_kp;
extern float im_speed_pi_ki;
extern void set_im_speed_pi_kp(float new_kp);
extern void set_im_speed_pi_ki(float new_ki);

static const unsigned int IPC_TOGGLE_DEBOUNCE_MS = 100U;

static bool ipc_toggle_button_debounce_allows_toggle(uint32_t msgId)
{
	static unsigned int last_toggle_time_ms[My_Button_8 - My_Button_1 + 1U] = {0U};
	static bool has_last_toggle_time[My_Button_8 - My_Button_1 + 1U] = {false};
	uint32_t button_index = 0U;
	unsigned int current_uptime_ms = 0U;

	if ((msgId < My_Button_1) || (msgId > My_Button_8)) {
		return true;
	}

	button_index = msgId - My_Button_1;
	current_uptime_ms = uz_SystemTime_GetUptimeInMs();

	if (has_last_toggle_time[button_index] &&
		((current_uptime_ms - last_toggle_time_ms[button_index]) < IPC_TOGGLE_DEBOUNCE_MS)) {
		return false;
	}

	last_toggle_time_ms[button_index] = current_uptime_ms;
	has_last_toggle_time[button_index] = true;
	return true;
}

void ipc_Control_func(uint32_t msgId, float value, DS_Data *data)
{
	// HANDLE RECEIVED MESSAGE
	if (msgId != 0)
	{
		bool handle_message = true;
		if ((msgId >= My_Button_1) && (msgId <= My_Button_8)) {
			handle_message = ipc_toggle_button_debounce_allows_toggle(msgId);
		}

		if (handle_message) {
			// GENERAL VARIABLES
			switch (msgId)
			{

			case (Stop): // Stop
				ultrazohm_state_machine_set_stop(true);
				enable_controller_VA = false;
				enable_controller_IM = false;
				reset_VA();
				reset_im();
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
			enable_controller_IM = true;
			ultrazohm_state_machine_set_enable_control(true);

			break;

		case (Set_Send_Field_1):
		data->av.snd_fld[1] = value;
			break;

		case (Set_Send_Field_2):
		data->av.snd_fld[2] = value;
			break;

		case (Set_Send_Field_3):
		data->av.snd_fld[3] = value;
			break;

		case (Set_Send_Field_4):
		data->av.snd_fld[4] = value;
			break;

		case (Set_Send_Field_5):
		data->av.snd_fld[5] = value;
			break;

		case (Set_Send_Field_6):
		data->av.snd_fld[6] = value;
			break;

		case (Set_Send_Field_7): // KF Q_psi noise covariance
		if (value > 0.0f) { kf_q_psi = value; }
		data->av.snd_fld[7] = kf_q_psi;
			break;

		case (Set_Send_Field_8): // KF R_i noise covariance
		if (value > 0.0f) { kf_r_i = value; }
		data->av.snd_fld[8] = kf_r_i;
			break;

		case (Set_Send_Field_9): // KF Q_i noise covariance
		if (value > 0.0f) { kf_q_i = value; }
		data->av.snd_fld[9] = kf_q_i;
			break;

		case (Set_Send_Field_10): // IM speed PI Kp
		if (value >= 0.0f) { set_im_speed_pi_kp(value); }
		data->av.snd_fld[10] = im_speed_pi_kp;
			break;

		case (Set_Send_Field_11): // IM speed PI Ki
		if (value >= 0.0f) { set_im_speed_pi_ki(value); }
		data->av.snd_fld[11] = im_speed_pi_ki;
			break;

		case (Set_Send_Field_12):
		data->av.snd_fld[12] = value;
			break;

		case (Set_Send_Field_13):
		data->av.snd_fld[13] = value;
			break;

		case (Set_Send_Field_14):
		data->av.snd_fld[14] = value;
			break;

		case (Set_Send_Field_15):
		data->av.snd_fld[15] = value;
			break;

		case (Set_Send_Field_16):
		data->av.snd_fld[16] = value;
			break;

		case (Set_Send_Field_17):
		data->av.snd_fld[17] = value;
			break;

		case (Set_Send_Field_18):
		data->av.snd_fld[18] = value;
			break;

		case (Set_Send_Field_19):
		data->av.snd_fld[19] = value;
			break;

		case (Set_Send_Field_20):
		data->av.snd_fld[20] = value;
			break;

		case (My_Button_1):
			break; /* unused */

		case (My_Button_2):
			break; /* unused */

		case (My_Button_3):
			break; /* unused */

		case (My_Button_4): // Toggle FOC on/off for IM
			use_foc = !use_foc;
			break;

		case (My_Button_5): // Toggle IM speed control on/off
			use_speed_control = !use_speed_control;
			break;

		case (My_Button_6): // Toggle Kalman filter observer
			use_kalman_filter = !use_kalman_filter;
			use_deterministic_observer = !use_kalman_filter;
			break;

		case (My_Button_7): // Toggle 6th harmonic resonant controller
			use_resonant_6th = !use_resonant_6th;
			break;

		case (My_Button_8): // Toggle RR profile for IM
			data->rr_profile.select_automatic_idiq = !data->rr_profile.select_automatic_idiq;
			data->rr_profile.setpoints_from_javascope = !data->rr_profile.select_automatic_idiq;
			data->rr_profile.start_marker = data->rr_profile.select_automatic_idiq ? 1.0f : 0.0f;
			data->rr_profile.setpoint_index = 0U;
			if (data->rr_profile.select_automatic_idiq) {
				use_speed_control = true;
			}
			break;

			case (Error_Reset):
				enable_controller_VA = false;
				enable_controller_IM = false;
				reset_VA();
				reset_im();
				error_checks_reset();
				ultrazohm_state_machine_set_stop(true);
				ultrazohm_state_machine_set_error(false);
				break;

			case (0xFFFF):
				// this is triggered if the IPI message buffer is read without being written once before (i.e. at startup)
				break;

			default:
				break;		  // Default just breaks since now a lot of unused control worlds are sent from the javascope->a53 which are never handled here.
				uz_assert(0); // unknown command -> throw error
			}
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

	/* Bit 4 - unused */
	js_status_BareToRTOS &= ~(1 << 4);

	/* Bit 5 - unused */
	js_status_BareToRTOS &= ~(1 << 5);

	/* Bit 6 - unused */
	js_status_BareToRTOS &= ~(1 << 6);

	/* Bit 7 - My_Button_4 (Toggle_FOC) */
	if (use_foc) {
		js_status_BareToRTOS |= (1 << 7);
	} else {
		js_status_BareToRTOS &= ~(1 << 7);
	}

	/* Bit 8 - My_Button_5 (Toggle_IM_Speed_Ctrl) */
	if (use_speed_control) {
		js_status_BareToRTOS |= (1 << 8);
	} else {
		js_status_BareToRTOS &= ~(1 << 8);
	}

	/* Bit 9 - My_Button_6 (Toggle_KalmanFilter) */
	if (use_kalman_filter) {
		js_status_BareToRTOS |= (1 << 9);
	} else {
		js_status_BareToRTOS &= ~(1 << 9);
	}

	/* Bit 10 - My_Button_7 (Toggle_Resonant6th) */
	if (use_resonant_6th) {
		js_status_BareToRTOS |= (1 << 10);
	} else {
		js_status_BareToRTOS &= ~(1 << 10);
	}

	/* Bit 11 - My_Button_8 (Toggle_RR_Profile) */
	if (data->rr_profile.select_automatic_idiq) {
		js_status_BareToRTOS |= (1 << 11);
	} else {
		js_status_BareToRTOS &= ~(1 << 11);
	}

	/* Bit 12 - trigger ext. logging */
	// if (your condition == true) {
	//	js_status_BareToRTOS |= (1 << 12);
	// } else {
	//	js_status_BareToRTOS &= ~(1 << 12);
	// }

	if (data->av.snd_fld[1] > 0.0f) {
		vf_frequency_setpoint_Hz = data->av.snd_fld[1];
	}
	if (data->rr_profile.setpoints_from_javascope) {
		speed_ref_rpm = data->av.snd_fld[2];
		id_ref_A = data->av.snd_fld[3];
		iq_ref_A = data->av.snd_fld[4];
	}
	data->rasv.i_dq_ref_VA.d = data->av.snd_fld[12];
	data->rasv.i_dq_ref_VA.q = data->av.snd_fld[13];
	data->rasv.n_ref_VA = data->av.snd_fld[14];
}
