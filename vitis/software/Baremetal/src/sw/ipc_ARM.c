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
#include "../Codegen/uz_codegen0_ert_rtw/uz_codegen0.h"
#include "../IP_Cores/SDC_Interface/SDC_Interface.h"
#include "../IP_Cores/SDC_OCP/SDC_OCP.h"
#include "../IP_Cores/io_fault_shutdown/io_fault_shutdown.h"

extern float *js_ch_observable[JSO_ENDMARKER];
extern float *js_ch_selected[JS_CHANNELS];
extern DS_Data Global_Data;

extern conv_status_signals_t conv_status_signals;
extern uint32_t js_status_BareToRTOS;
extern bool input_bit;
extern bool output_bit;
extern uint32_t output_port;
extern uint32_t input_port;
extern float DC_LINK_MAX_VOLTS;
extern Bus_Ctrl_Config struct_Ctrl_Config;
extern float DutC;

extern Bus_ZM_In struct_ZM_In;
extern SDC_Interface_t *Sinc3_Filter;
void ipc_Control_func(uint32_t msgId, float value, DS_Data *data)
{
	// HANDLE RECEIVED MESSAGE
	if (msgId != 0)
	{
		// GENERAL VARIABLES
		switch (msgId)
		{

		case (My_Button_1): // switch to manual_duty_cycle (set via Set_Send_Field_1..3)
			data->rasv.ctrl_state = manual_duty_cycle;
			break;

		case (My_Button_2):
			data->rasv.ctrl_state = current_control;
			break;

		case (My_Button_3): 
			data->rasv.ctrl_state = rpm_control;
			break;

		case (My_Button_4): // switch to current_control
			data->rasv.ctrl_state = position_control;
			break;

		case (My_Button_5): // switch to rpm_control
			data->rasv.ctrl_state = ctrl_state_none;
			break;

		case (My_Button_6): // switch to position_control
			resolver_pos_mt_write_preset_deg(data->objects.resolver_pos_mt, 0);
			break;

		case (My_Button_7): // Auf 0 Position fahren (Home-Position)
			data->rasv.Modus_Position_sel = Pos_Home;
			break;

		case (My_Button_8): // Trapez aktivieren
			data->rasv.Modus_Position_sel = Pos_Trapez;
			break;

		case (My_Button_9): // Manuelle Position
			data->rasv.Modus_Position_sel = Pos_Manuell;
			break;
		case (My_Button_10): // Warten
			data->rasv.Modus_Position_sel = Pos_Warten;
			break;

		case (My_Button_11): // Multiturn-Position laden: Sendfeld 13 (Abtriebs-Grad) -> Motor-Grad
			if (ultrazohm_state_machine_get_state() != control_state)   // nur wenn Regelung inaktiv
			{
				double motor_deg = (double)data->av.snd_fld[13] * (double)struct_Ctrl_Config.Getriebeuebersetzung;
				resolver_pos_mt_write_preset_deg(data->objects.resolver_pos_mt, motor_deg);
			}
			break;

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

		case (Set_Send_Field_1): // HB1 duty cycle, wirkt nur im manual_duty_cycle state
			if (data->rasv.ctrl_state == manual_duty_cycle)
			{
				data->rasv.Soll_HB1_DutyCycle = value;
			}
			break;

		case (Set_Send_Field_2): // HB2 duty cycle, wirkt nur im manual_duty_cycle state
			if (data->rasv.ctrl_state == manual_duty_cycle)
			{
				data->rasv.Soll_HB2_DutyCycle = value;
			}
			break;

		case (Set_Send_Field_3): // HB3 duty cycle, wirkt nur im manual_duty_cycle state
			if (data->rasv.ctrl_state == manual_duty_cycle)
			{
				data->rasv.Soll_HB3_DutyCycle = value;
			}
			break;

		case (Set_Send_Field_4):
		data->rasv.Soll_Drehzahl = value;
			break;

		case (Set_Send_Field_5):
		data->av.snd_fld[5] = value;
		struct_Ctrl_Config.KPi = value;
			break;

		case (Set_Send_Field_6):
		data->av.snd_fld[6] = value;
		struct_Ctrl_Config.KIi = value;
			break;

		case (Set_Send_Field_7): // Soll_id
		data->rasv.Soll_id = value;
			break;

		case (Set_Send_Field_8): // Soll_iq
		data->rasv.Soll_iq = value;
			break;

		case (Set_Send_Field_9): // Referenzier-Winkel (Wellenwinkel Motorseite) in Grad fuer My_Button_8
		data->rasv.Ref_Winkel_grad = value;
			break;

		case (Set_Send_Field_10): // position_control: Positionssollwert in Grad
		data->rasv.Soll_Winkel_grad = value;
			break;

		case (Set_Send_Field_11): // position_control: Geschwindigkeitssollwert in Grad/s
		data->rasv.Soll_Geschwindigkeit_grads = value;
			break;

		case (Set_Send_Field_12): // position_control: Beschleunigungssollwert in Grad/s^2
		data->rasv.Soll_Beschleunigung_grads2 = value;
			break;

		case (Set_Send_Field_13): // Preset-Position Abtriebsseite in Grad (fuer My_Button_11)
			data->av.snd_fld[13] = value;
			break;

		case (Set_Send_Field_14): // frei/ungenutzt
			break;

		case (Set_Send_Field_15): // frei/ungenutzt
			break;

		case (Set_Send_Field_16): // frei/ungenutzt
			break;

		case (Set_Send_Field_17): // frei/ungenutzt
			break;

		case (Set_Send_Field_18): // frei/ungenutzt
			break;

		case (Set_Send_Field_19): // frei/ungenutzt
			break;

		case (Set_Send_Field_20): // frei/ungenutzt
			break;

		

		case (Error_Reset): // Fehler quittieren und Wiederanlauf vorbereiten
			// Reihenfolge wichtig: zuerst die Fehlerquellen, die io_fault_shutdown speisen
			// (OCP ueber FLT_PS, Watchdog), erst danach io_fault_shutdown quittieren. Sonst wuerde
			// dessen Latch sofort erneut gesetzt. Jeder Latch laesst sich nur quittieren, wenn der
			// Fehler nicht mehr anliegt - sonst setzt die PL den Latch unmittelbar wieder.
			if (data->objects.sdc_ocp_P != NULL)
			{
				SDC_OCP_acknowledge_fault(data->objects.sdc_ocp_P);     // P-Pfad: DC maskieren -> FLT_Reset -> EN_OCP aus
			}
			if (data->objects.sdc_ocp_OCP != NULL)
			{
				SDC_OCP_acknowledge_fault(data->objects.sdc_ocp_OCP);   // OCP-Pfad: DC maskieren -> FLT_Reset -> EN_OCP aus
			}
			struct_ZM_In.Strom_gesperrt_rst = true;
			ctrl_loop_watchdog_reset_fault(data->objects.ctrl_loop_watchdog); // 1) Watchdog-Latch zuerst loeschen (speist io_fault_shutdown)
			io_fault_shutdown_set_FLT_PS(data->objects.flt_dis, false);  // 2) aggregierte Abschaltanforderung (z.B. OCP) zuruecknehmen
			io_fault_shutdown_reset_fault(data->objects.flt_dis);        // 3) io_fault_shutdown-Latch (FLT_1..4/FLT_PS) loeschen (FLT_RST-Puls)
			conv_status_signals.ocp_fault = 0U;
			uz_axi_gpio_write_pin_zero_based(Global_Data.objects.output_gpio, BOARD_RST_BIT, true);
			// Nur nach idle_state wechseln, wenn kein Fehler mehr anliegt (Latch nicht sofort neu gesetzt).
			if (((data->objects.flt_dis == NULL) || (io_fault_shutdown_get_fault(data->objects.flt_dis) == IO_FAULT_SHUTDOWN_FAULT_NONE))
				&& ((data->objects.ctrl_loop_watchdog == NULL) || (!ctrl_loop_watchdog_get_fault(data->objects.ctrl_loop_watchdog))))
			{
				ultrazohm_state_machine_set_stop(true);              // error_state -> idle_state
			}
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

	/* Bit 12 - trigger ext. logging */
	// if (your condition == true) {
	//	js_status_BareToRTOS |= (1 << 12);
	// } else {
	//	js_status_BareToRTOS &= ~(1 << 12);
	// }

}
