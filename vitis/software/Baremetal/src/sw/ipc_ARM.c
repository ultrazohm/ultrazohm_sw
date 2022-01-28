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

//ParameterID
extern uz_ParameterID_Data_t PID_Data;

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

			break;

		case (Set_Send_Field_2):

			break;

		case (Set_Send_Field_3):

			break;

		case (Set_Send_Field_4):

			break;

		case (Set_Send_Field_5):

			break;

		case (Set_Send_Field_6):

			break;

		case (Enable_Current_Control):
			if (ultrazohm_state_machine_get_state() != control_state) {
				PID_Data.PID_Control_Selection = Current_Control;
			}
			break;

		case (Enable_Speed_Control):
			if (ultrazohm_state_machine_get_state() != control_state) {
				PID_Data.PID_Control_Selection = Speed_Control;
			}
			break;

		case (Disable_FOC_Control):
			if (ultrazohm_state_machine_get_state() != control_state) {
				PID_Data.PID_Control_Selection = No_Control;
			}
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

			//ParameterID

		case (PID_Enable_System):
			ultrazohm_state_machine_set_enable_system(true);
			break;

		case (PID_Enable_Control):
			ultrazohm_state_machine_set_enable_control(true);
			break;

		case (PID_Enable_ParameterID):
			PID_Data.GlobalConfig.enableParameterID = true;
			break;

		case (PID_Disable_ParameterID):
			PID_Data.GlobalConfig.enableParameterID = false;
			PID_Data.GlobalConfig.ElectricalID = false;
			PID_Data.GlobalConfig.TwoMassID = false;
			PID_Data.GlobalConfig.FrictionID = false;
			PID_Data.GlobalConfig.FluxMapID = false;
			PID_Data.GlobalConfig.OnlineID = false;
			break;

		case (PID_Enable_ElectricalID):
			PID_Data.GlobalConfig.ElectricalID = true;
			break;

		case (PID_Disable_ElectricalID):
			PID_Data.GlobalConfig.ElectricalID = false;
			break;

		case (PID_Enable_FrictionID):
			PID_Data.GlobalConfig.FrictionID = true;
			break;

		case (PID_Disable_FrictionID):
			PID_Data.GlobalConfig.FrictionID = false;
			break;

		case (PID_Enable_TwoMassID):
			PID_Data.GlobalConfig.TwoMassID = true;
			break;

		case (PID_Disable_TwoMassID):
			PID_Data.GlobalConfig.TwoMassID = false;
			break;

		case (PID_Enable_FluxMapID):
			PID_Data.GlobalConfig.FluxMapID = true;
			break;

		case (PID_Disable_FluxMapID):
			PID_Data.GlobalConfig.FluxMapID = false;
			break;

		case (PID_Enable_OnlineID):
			PID_Data.GlobalConfig.OnlineID = true;
			break;

		case (PID_Disable_OnlineID):
			PID_Data.GlobalConfig.OnlineID = false;
			PID_Data.AutoRefCurrents_Config.enableCRS = false;
			break;

		case (PID_ACCEPT):
			PID_Data.GlobalConfig.ACCEPT = true;
			break;

		case (PID_RESET):
			PID_Data.GlobalConfig.Reset = true;
			PID_Data.GlobalConfig.ElectricalID = false;
			PID_Data.GlobalConfig.TwoMassID = false;
			PID_Data.GlobalConfig.FrictionID = false;
			PID_Data.GlobalConfig.FluxMapID = false;
			PID_Data.GlobalConfig.OnlineID = false;
			break;

		case (PID_EID_sampleTimeISR):
			PID_Data.GlobalConfig.sampleTimeISR = value * 0.000001f;
			break;

		case (PID_EID_n_ref_meas):
			PID_Data.ElectricalID_Config.n_ref_measurement = value;
			break;

		case (PID_EID_goertzl_Amp):
			PID_Data.ElectricalID_Config.goertzlAmp = value * 0.1f;
			break;

		case (PID_EID_polePairs):
			PID_Data.GlobalConfig.PMSM_config.polePairs = value;
			break;

		case (PID_EID_DutyCyc):
			PID_Data.ElectricalID_Config.dutyCyc = value;
			break;

		case (PID_EID_MaxContinousCurrent):
			PID_Data.GlobalConfig.PMSM_config.I_max_Ampere = value;
			break;

		case (PID_EID_Enable_IdentLQ):
			PID_Data.ElectricalID_Config.identLq = true;
			break;

		case (PID_EID_Disable_IdentLQ):
			PID_Data.ElectricalID_Config.identLq = false;
			break;

		case (PID_EID_Admit_Params):
			break;

		case (PID_FID_max_speed):
			PID_Data.FrictionID_Config.n_eva_max = value;
			break;

		case (PID_FID_N_Brk):
			PID_Data.FrictionID_Config.N_Brk = value;
			break;

		case (PID_FID_N_Visco):
			PID_Data.FrictionID_Config.N_Visco = value;
			break;

		case (PID_FID_s_step):
			PID_Data.FrictionID_Config.StepScale = value;
			break;

		case (PID_FID_Brk_Count):
			PID_Data.FrictionID_Config.BrkCount = value;
			break;

		case (PID_FID_eta_speed):
			PID_Data.FrictionID_Config.eta = value;
			break;

		case (PID_TMID_Scale_PRBS):
			PID_Data.TwoMassID_Config.ScaleTorquePRBS = value;
			break;

		case (PID_TMID_d_TMS_start):
			PID_Data.TwoMassID_Config.d_TMS_start = value;
			break;

		case (PID_TMID_n_ref):
			PID_Data.TwoMassID_Config.n_ref_measurement = value;
			break;

		case (PID_TMID_f_min):
			PID_Data.TwoMassID_Config.f_min = value;
			break;

		case (PID_TMID_f_max):
			PID_Data.TwoMassID_Config.f_max = value;
			break;

		case (PID_FMID_i_d_start):
			PID_Data.FluxMapID_Config.IDstart = value;
			break;

		case (PID_FMID_i_d_stop):
			PID_Data.FluxMapID_Config.IDstop = value;
			break;

		case (PID_FMID_i_d_step):
			PID_Data.FluxMapID_Config.IDstepsize = value;
			break;

		case (PID_FMID_i_q_start):
			PID_Data.FluxMapID_Config.IQstart = value;
			break;

		case (PID_FMID_i_q_stop):
			PID_Data.FluxMapID_Config.IQstop = value;
			break;

		case (PID_FMID_i_q_step):
			PID_Data.FluxMapID_Config.IQstepsize = value;
			break;

		case (PID_FMID_Rs_ref):
			PID_Data.FluxMapID_Config.R_s_ref = value;
			break;

		case (PID_FMID_Temp_ref):
			PID_Data.FluxMapID_Config.Temp_ref = value;
			break;

		case (PID_FMID_identRAmp):
			PID_Data.FluxMapID_Config.identRAmp = value;
			break;

		case (PID_FMID_enable_ident_R):
			PID_Data.FluxMapID_Config.identR = true;
			break;

		case (PID_FMID_disable_ident_R):
			PID_Data.FluxMapID_Config.identR = false;
			break;

		case (PID_FMID_enable_AMM):
			PID_Data.FluxMapID_Config.start_FM_ID = true;
			break;

		case (PID_FMID_disable_AMM):
			PID_Data.FluxMapID_Config.start_FM_ID = false;
			break;

		case (PID_OID_Refresh_Flux_Maps):
			PID_Data.calculate_flux_maps = true;
			break;

		case (PID_OID_Reset_OnlineID):
			PID_Data.OnlineID_Config.OnlineID_Reset = true;
			PID_Data.AutoRefCurrents_Config.Reset = true;
			break;

		case (PID_OID_Enable_AutoCurrentControl):
			PID_Data.AutoRefCurrents_Config.enableCRS = true;
			break;

		case (PID_OID_Disable_AutoCurrentControl):
			PID_Data.AutoRefCurrents_Config.enableCRS = false;
			break;

		case (PID_OID_d_current_steps):
			PID_Data.AutoRefCurrents_Config.id_points = value;
			break;

		case (PID_OID_q_current_steps):
			PID_Data.AutoRefCurrents_Config.iq_points = value;
			break;

		case (PID_OID_max_current):
			PID_Data.AutoRefCurrents_Config.max_current = value;
			break;

		case (PID_OID_ref_temp):
			PID_Data.OnlineID_Config.Temp_ref = value;
			break;

		case (PID_OID_ref_Rs):
			break;

		case (PID_OID_max_speed):
			PID_Data.OnlineID_Config.max_n_ratio = value;
			break;

		case (PID_OID_min_speed):
			PID_Data.OnlineID_Config.min_n_ratio = value;
			break;

		case (PID_OID_Ident_range_factor):
			PID_Data.OnlineID_Config.nom_factor = value;
			break;

		case (PID_OID_max_ident_pause):
			PID_Data.OnlineID_Config.Rs_time = value;
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
	/* Bit 2 - Ident_Lq */
	if (PID_Data.ElectricalID_Config.identLq == true) {
		js_status_BareToRTOS |= (1 << 2);
	} else {
		js_status_BareToRTOS &= ~(1 << 2);
	}

	/* Bit 3 - FluxMapID R-Online */
	if (PID_Data.FluxMapID_Config.identR == true) {
		js_status_BareToRTOS |= (1 << 3);
	} else {
		js_status_BareToRTOS &= ~(1 << 3);
	}

	/* Bit 4 - FluxMapID start */
	if (PID_Data.FluxMapID_Config.start_FM_ID == true) {
		js_status_BareToRTOS |= (1 << 4);
	} else {
		js_status_BareToRTOS &= ~(1 << 4);
	}

	/* Bit 5 - PID_FOC_CC */
	if (PID_Data.PID_Control_Selection == Current_Control) {
		js_status_BareToRTOS |= (1 << 5);
	} else {
		js_status_BareToRTOS &= ~(1 << 5);
	}

	/* Bit 6 - PID_FOC_SC */
	if (PID_Data.PID_Control_Selection == Speed_Control) {
		js_status_BareToRTOS |= (1 << 6);
	} else {
		js_status_BareToRTOS &= ~(1 << 6);
	}

	/* Bit 7 -PID_FOC_no_control */
	if (PID_Data.PID_Control_Selection == No_Control) {
		js_status_BareToRTOS |= (1 << 7);
	} else {
		js_status_BareToRTOS &= ~(1 << 7);
	}

	/* Bit 8 -ParameterID active */
	if (PID_Data.GlobalConfig.enableParameterID == true) {
		uz_led_set_userLED_on();
		js_status_BareToRTOS |= (1 << 8);
	} else {
		js_status_BareToRTOS &= ~(1 << 8);
		uz_led_set_userLED_off();
	}

	/* Bit 9 - My_Button_6 */
	// js_status_BareToRTOS &= ~(1 << 9);

	/* Bit 10 - My_Button_7 */
	// js_status_BareToRTOS &= ~(1 << 10);

	/* Bit 11 - My_Button_8 */
	// js_status_BareToRTOS &= ~(1 << 11);


}
