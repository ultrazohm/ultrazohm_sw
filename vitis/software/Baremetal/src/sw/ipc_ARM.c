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
#include "../uz/uz_ParameterID/uz_ParameterID.h"

// ======================= PMSM 1 ======================= //
// ---------------- Inverter Measurement ---------------- //

// --------- Field Oriented Control and Signals --------- //
extern float n_ref_rpm_1;
extern float M_ref_Nm_1;
extern float theta_el_offset_1;
extern struct uz_3ph_dq_t i_dq_ref_Amps_1;


// ---------------- Controller Settings ----------------- //
extern float Kp_speed_1;
extern float Ki_speed_1;
extern float Kp_id_1;
extern float Ki_id_1;
extern float Kp_iq_1;
extern float Ki_iq_1;


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


// ---------------- Resonant Controllers ---------------- //
extern float Gain_RC_6th_2;

// ---------------- Controller Settings ----------------- //
extern float Kp_speed_2;
extern float Ki_speed_2;
extern float Kp_id_2;
extern float Ki_id_2;
extern float Kp_iq_2;
extern float Ki_iq_2;

// ======================= Others ======================= //
extern int option;
extern struct uz_3ph_dq_t v_ind_dq_Volts_2 ;
extern uz_ParameterID_Data_t ParaID_Data;
extern struct uz_PMSM_t config_PMSM_2;
extern uz_SpeedControl_t* SC_instance;
extern uz_SetPoint_t* SP_instance;
extern uz_CurrentControl_t* CC_instance_dq;

extern float *js_ch_observable[JSO_ENDMARKER];
extern float *js_ch_selected[JS_CHANNELS];

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
		n_ref_rpm_1 = value;
			break;

		case (Set_Send_Field_2):
		i_dq_ref_Amps_2.d = value;
			break;

		case (Set_Send_Field_3):
		i_dq_ref_Amps_2.q = value;
			break;

		case (Set_Send_Field_4):
		data->av.theta_offset_2 = value;
			break;

		case (Set_Send_Field_5):

			break;

		case (Set_Send_Field_6):

			break;

		case (Set_Send_Field_7):

			break;

		case (Set_Send_Field_8):

			break;

		case (Set_Send_Field_9):

			break;

		case (Set_Send_Field_10):

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

		 case (ParaID_Enable_System):
		            ultrazohm_state_machine_set_enable_system(true);
		            break;

		        case (ParaID_Enable_Control):
		            ultrazohm_state_machine_set_enable_control(true);
		            break;

		        case (ParaID_Enable_ParameterID):
		            ParaID_Data.GlobalConfig.enableParameterID = true;
		            break;

		        case (ParaID_Disable_ParameterID):
		            ParaID_Data.GlobalConfig.enableParameterID = false;
		            ParaID_Data.GlobalConfig.ElectricalID = false;
		            ParaID_Data.GlobalConfig.TwoMassID = false;
		            ParaID_Data.GlobalConfig.FrictionID = false;
		            ParaID_Data.GlobalConfig.FluxMapID = false;
		            ParaID_Data.GlobalConfig.OnlineID = false;
		            ParaID_Data.FluxMapID_Config.start_FM_ID = false;
		        break;

					case (ParaID_Enable_Current_Control):
						if (ultrazohm_state_machine_get_state() != control_state) {
							ParaID_Data.ParaID_Control_Selection = Current_Control;
						}
						break;

					case (ParaID_Enable_Speed_Control):
						if (ultrazohm_state_machine_get_state() != control_state) {
							ParaID_Data.ParaID_Control_Selection = Speed_Control;
						}
						break;

					case (ParaID_Disable_FOC_Control):
						ParaID_Data.ParaID_Control_Selection = No_Control;
						break;

					case (ParaID_Enable_ElectricalID):
						ParaID_Data.GlobalConfig.ElectricalID = true;
						break;

					case (ParaID_Disable_ElectricalID):
						ParaID_Data.GlobalConfig.ElectricalID = false;
						break;

					case (ParaID_Enable_FrictionID):
						ParaID_Data.GlobalConfig.FrictionID = true;
						break;

					case (ParaID_Disable_FrictionID):
						ParaID_Data.GlobalConfig.FrictionID = false;
						break;

					case (ParaID_Enable_TwoMassID):
						ParaID_Data.GlobalConfig.TwoMassID = true;
						break;

					case (ParaID_Disable_TwoMassID):
						ParaID_Data.GlobalConfig.TwoMassID = false;
						break;

					case (ParaID_Enable_FluxMapID):
						ParaID_Data.GlobalConfig.FluxMapID = true;
						break;

					case (ParaID_Disable_FluxMapID):
						ParaID_Data.GlobalConfig.FluxMapID = false;
						ParaID_Data.FluxMapID_Config.start_FM_ID = false;
						break;

					case (ParaID_Enable_OnlineID):
						ParaID_Data.GlobalConfig.OnlineID = true;
						break;

					case (ParaID_Disable_OnlineID):
						ParaID_Data.GlobalConfig.OnlineID = false;
						ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
						break;

					case (ParaID_ACCEPT):
						ParaID_Data.GlobalConfig.ACCEPT = true;
						break;

					case (ParaID_RESET):
						ParaID_Data.GlobalConfig.Reset = true;
						ParaID_Data.GlobalConfig.ElectricalID = false;
						ParaID_Data.GlobalConfig.TwoMassID = false;
						ParaID_Data.GlobalConfig.FrictionID = false;
						ParaID_Data.GlobalConfig.FluxMapID = false;
						ParaID_Data.GlobalConfig.OnlineID = false;
						ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
						ParaID_Data.ParaID_Control_Selection = No_Control;
						ParaID_Data.ElectricalID_Config.identLq = false;
						ParaID_Data.FluxMapID_Config.start_FM_ID = false;

						break;

					case (ParaID_EID_sampleTimeISR):
						ParaID_Data.GlobalConfig.sampleTimeISR = value * 0.000001f;
						break;

					case (ParaID_EID_n_ref_meas):
						ParaID_Data.ElectricalID_Config.n_ref_measurement = value;
						break;

					case (ParaID_EID_goertzl_Torque):
						ParaID_Data.ElectricalID_Config.goertzlTorque = value;
						break;

					case (ParaID_EID_goertzl_Freq):
						ParaID_Data.ElectricalID_Config.goertzlFreq = value;
						break;

					case (ParaID_EID_DutyCyc):
						ParaID_Data.ElectricalID_Config.dutyCyc = value;
						break;

					case (ParaID_EID_MaxContinousCurrent):
						ParaID_Data.GlobalConfig.PMSM_config.I_max_Ampere = value;
						break;

					case (ParaID_EID_Enable_IdentLQ):
						ParaID_Data.ElectricalID_Config.identLq = true;
						break;

					case (ParaID_EID_Disable_IdentLQ):
						ParaID_Data.ElectricalID_Config.identLq = false;
						break;

					case (ParaID_EID_Admit_Params):
						//If FOC is used
						uz_CurrentControl_set_PMSM_parameters(CC_instance_dq, ParaID_Data.ElectricalID_Output->PMSM_parameters);
						uz_SetPoint_set_PMSM_config(SP_instance, ParaID_Data.ElectricalID_Output->PMSM_parameters);
						break;

					case (ParaID_FID_max_speed):
						ParaID_Data.FrictionID_Config.n_eva_max = value;
						break;

					case (ParaID_FID_N_Brk):
						ParaID_Data.FrictionID_Config.N_Brk = value;
						break;

					case (ParaID_FID_N_Visco):
						ParaID_Data.FrictionID_Config.N_Visco = value;
						break;

					case (ParaID_FID_s_step):
						ParaID_Data.FrictionID_Config.StepScale = value;
						break;

					case (ParaID_FID_Brk_Count):
						ParaID_Data.FrictionID_Config.BrkCount = value;
						break;

					case (ParaID_FID_eta_speed):
						ParaID_Data.FrictionID_Config.eta = value;
						break;

					case (ParaID_TMID_Scale_PRBS):
						ParaID_Data.TwoMassID_Config.ScaleTorquePRBS = value;
						break;

					case (ParaID_TMID_d_TMS_start):
						ParaID_Data.TwoMassID_Config.d_TMS_start = value;
						break;

					case (ParaID_TMID_n_ref):
						ParaID_Data.TwoMassID_Config.n_ref_measurement = value;
						break;

					case (ParaID_TMID_f_min):
						ParaID_Data.TwoMassID_Config.f_min = value;
						break;

					case (ParaID_TMID_f_max):
						ParaID_Data.TwoMassID_Config.f_max = value;
						break;

					case (ParaID_FMID_i_d_start):
						ParaID_Data.FluxMapID_Config.IDstart = value;
						break;

					case (ParaID_FMID_i_d_stop):
						ParaID_Data.FluxMapID_Config.IDstop = value;
						break;

					case (ParaID_FMID_i_d_step):
						ParaID_Data.FluxMapID_Config.IDstepsize = value;
						break;

					case (ParaID_FMID_i_q_start):
						ParaID_Data.FluxMapID_Config.IQstart = value;
						break;

					case (ParaID_FMID_i_q_stop):
						ParaID_Data.FluxMapID_Config.IQstop = value;
						break;

					case (ParaID_FMID_i_q_step):
						ParaID_Data.FluxMapID_Config.IQstepsize = value;
						break;

					case (ParaID_FMID_Rs_ref):
						ParaID_Data.FluxMapID_Config.R_s_ref = value;
						break;

					case (ParaID_FMID_Temp_ref):
						ParaID_Data.FluxMapID_Config.Temp_ref = value;
						break;

					case (ParaID_FMID_identRAmp):
						ParaID_Data.FluxMapID_Config.identRAmp = value;
						break;

					case (ParaID_FMID_enable_ident_R):
						ParaID_Data.FluxMapID_Config.identR = true;
						break;

					case (ParaID_FMID_disable_ident_R):
						ParaID_Data.FluxMapID_Config.identR = false;
						break;

					case (ParaID_FMID_enable_AMM):
						ParaID_Data.FluxMapID_Config.start_FM_ID = true;
						break;

					case (ParaID_FMID_disable_AMM):
						ParaID_Data.FluxMapID_Config.start_FM_ID = false;
						break;

					case (ParaID_OID_Refresh_Flux_Maps):
						ParaID_Data.calculate_flux_maps = true;
						break;

					case (ParaID_OID_Reset_OnlineID):
						ParaID_Data.OnlineID_Config.OnlineID_Reset = true;
						ParaID_Data.AutoRefCurrents_Config.Reset = true;
						ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
						break;

					case (ParaID_OID_Enable_AutoCurrentControl):
						ParaID_Data.AutoRefCurrents_Config.enableCRS = true;
						break;

					case (ParaID_OID_Disable_AutoCurrentControl):
						ParaID_Data.AutoRefCurrents_Config.enableCRS = false;
						break;

					case (ParaID_OID_d_current_steps):
						ParaID_Data.AutoRefCurrents_Config.id_points = value;
						break;

					case (ParaID_OID_q_current_steps):
						ParaID_Data.AutoRefCurrents_Config.iq_points = value;
						break;

					case (ParaID_OID_max_current):
						ParaID_Data.AutoRefCurrents_Config.max_current = value;
						break;

					case (ParaID_OID_ref_temp):
						ParaID_Data.OnlineID_Config.Temp_ref = value;
						break;

					case (ParaID_OID_ref_Rs):
						ParaID_Data.GlobalConfig.PMSM_config.R_ph_Ohm = value;
						break;

					case (ParaID_OID_max_speed):
						ParaID_Data.OnlineID_Config.max_n_ratio = value;
						break;

					case (ParaID_OID_min_speed):
						ParaID_Data.OnlineID_Config.min_n_ratio = value;
						break;

					case (ParaID_OID_Ident_range_factor):
						ParaID_Data.OnlineID_Config.nom_factor = value;
						break;

					case (ParaID_OID_max_ident_pause):
						ParaID_Data.OnlineID_Config.Rs_time = value;
						break;
					case (ParaID_OID_identR_Amp):
						ParaID_Data.OnlineID_Config.identRAmp = value;
						break;

					case (ParaID_OID_Fluxmap_Control_counter):
						ParaID_Data.FluxMap_Control_counter = value;
						break;

					case (ParaID_FID_Array_Control_counter):
						ParaID_Data.Array_Control_counter = value;
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

	/* Bit 12 - trigger ext. logging */
	// if (your condition == true) {
	//	js_status_BareToRTOS |= (1 << 12);
	// } else {
	//	js_status_BareToRTOS &= ~(1 << 12);
	// }
	//Replace Bit 13-19 with the following
	    /* Bit 13 - Ident_Lq */
	    if (ParaID_Data.ElectricalID_Config.identLq == true) {
	        js_status_BareToRTOS |= (1 << 13);
	    } else {
	        js_status_BareToRTOS &= ~(1 << 13);
	    }

	    /* Bit 14 - FluxMapID R-Online */
	    if (ParaID_Data.FluxMapID_Config.identR == true) {
	        js_status_BareToRTOS |= (1 << 14);
	    } else {
	        js_status_BareToRTOS &= ~(1 << 14);
	    }

	    /* Bit 15 - FluxMapID start */
	    if (ParaID_Data.FluxMapID_Config.start_FM_ID == true) {
	        js_status_BareToRTOS |= (1 << 15);
	    } else {
	        js_status_BareToRTOS &= ~(1 << 15);
	    }

	    /* Bit 16 - ParaID_FOC_CC */
	    if (ParaID_Data.ParaID_Control_Selection == Current_Control) {
	        js_status_BareToRTOS |= (1 << 16);
	    } else {
	        js_status_BareToRTOS &= ~(1 << 16);
	    }

	    /* Bit 17 - ParaID_FOC_SC */
	    if (ParaID_Data.ParaID_Control_Selection == Speed_Control) {
	        js_status_BareToRTOS |= (1 << 17);
	    } else {
	        js_status_BareToRTOS &= ~(1 << 17);
	    }

	    /* Bit 18 -ParaID_FOC_no_control */
	    if (ParaID_Data.ParaID_Control_Selection == No_Control) {
	        js_status_BareToRTOS |= (1 << 18);
	    } else {
	        js_status_BareToRTOS &= ~(1 << 18);
	    }

	    /* Bit 19 -ParameterID active */
	    if (ParaID_Data.GlobalConfig.enableParameterID == true) {
	        ultrazohm_state_machine_set_userLED(true);
	        js_status_BareToRTOS |= (1 << 19);
	    } else {
	        js_status_BareToRTOS &= ~(1 << 19);
	        ultrazohm_state_machine_set_userLED(false);
	    }
}
