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

extern _Bool bNewControlMethodAvailable;
extern uint32_t js_status_BareToRTOS;

// Variables for Send fields
extern struct uz_3ph_dq_t i_reference_Ampere;
extern float Kp_id;
extern float Kp_iq;
extern float Ki_id;
extern float Ki_iq;

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
			i_reference_Ampere.d =  value;
			break;

		case (Set_Send_Field_2):
			i_reference_Ampere.q =  value;
			break;

		case (Set_Send_Field_3):
			Kp_id = value;

			break;

		case (Set_Send_Field_4):
			Kp_iq = value;

			break;

		case (Set_Send_Field_5):
			Ki_id = value;
			break;

		case (Set_Send_Field_6):
			Ki_iq = value;
			break;

		case (My_Button_1):
			ultrazohm_state_machine_set_error(true);
			break;

		case (My_Button_2):
			ultrazohm_state_machine_set_userLED(true);
			break;

		case (My_Button_3):
			ultrazohm_state_machine_set_userLED(false);
			break;

		case (My_Button_4):

			break;

		case (My_Button_5):

			break;

		case (My_Button_6):

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
	// if (your condition == true) {
	//	js_status_BareToRTOS |= (1 << 4);
	// } else {
	//	js_status_BareToRTOS &= ~(1 << 4);
	// }

	/* Bit 5 - My_Button_2 */
	// js_status_BareToRTOS &= ~(1 << 5);

	/* Bit 6 - My_Button_3 */
	// js_status_BareToRTOS &= ~(1 << 6);

	/* Bit 7 - My_Button_4 */
	// js_status_BareToRTOS &= ~(1 << 7);

	/* Bit 8 - My_Button_5 */
	// js_status_BareToRTOS &= ~(1 << 8);

	/* Bit 9 - My_Button_6 */
	// js_status_BareToRTOS &= ~(1 << 9);

	/* Bit 10 - My_Button_7 */
	// js_status_BareToRTOS &= ~(1 << 10);

	/* Bit 11 - My_Button_8 */
	// js_status_BareToRTOS &= ~(1 << 11);


}
