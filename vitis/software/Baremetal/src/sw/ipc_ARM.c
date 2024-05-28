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

extern float *js_ch_observable[JSO_ENDMARKER];
extern float *js_ch_selected[JS_CHANNELS];
bool select_CurrentControl = false;
bool select_DDPG_1_64 = false;
bool select_DDPG_3_64 = false;
bool select_Real = false;
bool select_CIL = false;
bool select_automatic_idiq = false;
float n_ref_rpm = 0.0f;
float i_d_ref = 0.0f;
float i_q_ref = 0.0f;
float i_X_ref = 0.0f;
float i_Y_ref = 0.0f;
extern float start_marker;
extern uint32_t js_status_BareToRTOS;

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
			n_ref_rpm = value;
			break;

		case (Set_Send_Field_2):
			i_d_ref = value;
			break;

		case (Set_Send_Field_3):
			i_q_ref = value;
			break;

		case (Set_Send_Field_4):
			i_X_ref = value;
			break;

		case (Set_Send_Field_5):
			i_Y_ref = value;
			break;

		case (Set_Send_Field_6):
		data->av.snd_fld[6] = value;
			break;

		case (Set_Send_Field_7):
		data->av.snd_fld[7] = value;
			break;

		case (Set_Send_Field_8):
		data->av.snd_fld[8] = value;
			break;

		case (Set_Send_Field_9):
		data->av.snd_fld[9] = value;
			break;

		case (Set_Send_Field_10):
		data->av.snd_fld[10] = value;
			break;

		case (Set_Send_Field_11):
		data->av.snd_fld[11] = value;
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
			select_Real = false;
			select_CIL = true;
			break;

		case (My_Button_2):
			select_Real = true;
			select_CIL = false;
			break;

		case (My_Button_3):
			select_CurrentControl = true;
			select_DDPG_1_64 = false;
			select_DDPG_3_64 = false;
			break;

		case (My_Button_4):
			select_CurrentControl = false;
			select_DDPG_1_64 = true;
			select_DDPG_3_64 = false;
			break;

		case (My_Button_5):
			select_CurrentControl = false;
			select_DDPG_1_64 = false;
			select_DDPG_3_64 = true;
			break;

		case (My_Button_6):
				select_automatic_idiq = true;
			break;

		case (My_Button_7):

			break;

		case (My_Button_8):

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
	if (select_CIL == true) {
		js_status_BareToRTOS |= (1 << 4);
	} else {
		js_status_BareToRTOS &= ~(1 << 4);
	}

	/* Bit 5 - My_Button_2 */
	if (select_Real == true) {
		js_status_BareToRTOS |= (1 << 5);
	} else {
		js_status_BareToRTOS &= ~(1 << 5);
	}

	/* Bit 6 - My_Button_3 */
	if (select_CurrentControl == true) {
	 	js_status_BareToRTOS |= (1 << 6);
	} else {
		js_status_BareToRTOS &= ~(1 << 6);
	}

	/* Bit 7 - My_Button_4 */
	if (select_DDPG_1_64 == true) {
		js_status_BareToRTOS |= (1 << 7);
	} else {
	 	js_status_BareToRTOS &= ~(1 << 7);
	}
	/* Bit 8 - My_Button_5 */
	if (select_DDPG_3_64 == true) {
		js_status_BareToRTOS |= (1 << 8);
	} else {
	 	js_status_BareToRTOS &= ~(1 << 8);
	}

	/* Bit 9 - My_Button_6 */
	if (select_automatic_idiq == true) {
		js_status_BareToRTOS |= (1 << 9);
	} else {
		 js_status_BareToRTOS &= ~(1 << 9);
	}

	/* Bit 10 - My_Button_7 */
	// js_status_BareToRTOS &= ~(1 << 10);

	/* Bit 11 - My_Button_8 */
	// js_status_BareToRTOS &= ~(1 << 11);

	/* Bit 12 - trigger ext. logging */
	 if (start_marker > 0.0f) {
		js_status_BareToRTOS |= (1 << 12);
	 } else {
		js_status_BareToRTOS &= ~(1 << 12);
	 }

}
