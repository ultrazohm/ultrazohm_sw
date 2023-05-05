/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel, Philipp LÃ¶hdefink, Michael Hoerner
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

#ifndef INCLUDE_JAVASCOPE_H_
#define INCLUDE_JAVASCOPE_H_

#include "APU_RPU_shared.h"

// Do not change the first (zero) and last (end) entries.
enum JS_OberservableData {
	JSO_ZEROVALUE=0,
	JSO_u_set_z1,
	JSO_u_set_z2,
	JSO_u_ref_z1,
	JSO_u_ref_z2,
	JSO_u_z1_rot,
	JSO_u_z2_rot,
	JSO_i_z1_rot,
	JSO_i_z2_rot,
	JSO_id,
	JSO_iq,
	JSO_x_rot,
	JSO_y_rot,
	JSO_z1_rot,
	JSO_z2_rot,
	JSO_ix,
	JSO_iy,
	JSO_iz1,
	JSO_iz2,
	JSO_ia1,
	JSO_ib1,
	JSO_ic1,
	JSO_ia2,
	JSO_ib2,
	JSO_ic2,
	JSO_i_dc1,
	JSO_i_dc2,
	JSO_avg_winding_temp,
	JSO_ud,
	JSO_uq,
	JSO_ux,
	JSO_uy,
	JSO_uz1,
	JSO_uz2,
	JSO_v_dc1,
	JSO_v_dc2,
	JSO_theta_mech,
	JSO_state,
	JSO_ISR_ExecTime_us,
	JSO_lifecheck,
	JSO_ISR_Period_us,
	JSO_Speed_rpm,
	JSO_LoadSpeed_rpm,
	JSO_volt_temp,
	JSO_SoC_init,
	JSO_Theta_el,
	JSO_Theta_mech,
	JSO_LoadTheta_mech,
	JSO_DeltaTheta_mech,
	JSO_Wtemp,
	JSO_Rs_mOhm,
	JSO_Ld_mH,
	JSO_Lq_mH,
	JSO_PsiPM_mVs,
	JSO_ENDMARKER
};

// slowData Naming Convention: Use JSSD_FLOAT_ as prefix
// Do not change the first (zero) and last (end) entries.
enum JS_SlowData {
	JSSD_ZEROVALUE=0,
	JSSD_FLOAT_SecondsSinceSystemStart,
	JSSD_FLOAT_ISR_ExecTime_us,
	JSSD_FLOAT_ISR_Period_us,
	JSSD_FLOAT_FreqReadback,
	JSSD_FLOAT_Milliseconds,
	JSSD_FLOAT_ADCconvFactorReadback,
	JSSD_FLOAT_Error_Code,
	JSSD_FLOAT_Rs_Offline,
	JSSD_FLOAT_Ld_Offline,
	JSSD_FLOAT_Lq_Offline,
	JSSD_FLOAT_PsiPM_Offline,
	JSSD_FLOAT_J,
	JSSD_FLOAT_activeState,
	JSSD_FLOAT_u_d,
	JSSD_FLOAT_u_q,
	JSSD_FLOAT_i_d,
	JSSD_FLOAT_i_q,
	JSSD_FLOAT_speed,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_u_d_ref,
	JSSD_FLOAT_u_q_ref,
	JSSD_FLOAT_v_dc1,
	JSSD_FLOAT_v_dc2,
	JSSD_FLOAT_ArrayCounter,
	JSSD_FLOAT_measArraySpeed,
	JSSD_FLOAT_measArrayTorque,
	JSSD_FLOAT_ArrayControlCounter,
	JSSD_FLOAT_Stribtorque,
	JSSD_FLOAT_Coulombtorque,
	JSSD_FLOAT_Viscotorque,
	JSSD_FLOAT_Rs_online_FMID,
	JSSD_FLOAT_Wtemp_FMID,
	JSSD_FLOAT_TrainInertia,
	JSSD_FLOAT_LoadInertia,
	JSSD_FLOAT_c_est,
	JSSD_FLOAT_d_est,
	JSSD_FLOAT_MapCounter,
	JSSD_FLOAT_psidMap,
	JSSD_FLOAT_psiqMap,
	JSSD_FLOAT_FluxTemp,
	JSSD_FLOAT_MapControl,
	JSSD_FLOAT_I_rated,
	JSSD_FLOAT_Ld_Online,
	JSSD_FLOAT_Lq_Online,
	JSSD_FLOAT_PsiPM_Online,
	JSSD_FLOAT_Rs_Online,
	JSSD_FLOAT_n_FluxPoints,
	JSSD_FLOAT_totalRotorInertia,
	JSSD_FLOAT_MapControlCounter,
	JSSD_FLOAT_polePairs,
	JSSD_FLOAT_temp_inv1,
	JSSD_FLOAT_temp_inv2,
	JSSD_FLOAT_fluxmap_index,
	JSSD_FLOAT_fluxmap_id,
	JSSD_FLOAT_fluxmap_iq,
	JSSD_FLOAT_fluxmap_psid,
	JSSD_FLOAT_fluxmap_psiq,
	JSSD_FLOAT_avg_winding_temp,
	JSSD_FLOAT_selected_subs,
	JSSD_ENDMARKER
};

// Determination of Button IDs via enum. When a button in the GUI is pressed,
// the GUI sends an ID and a value. IDs of the buttons are the respective enum
// numbers in the following enum.
// Do not change the first (zero) and last (end) entries.
// Do not change names! They are hard coupled within the GUI!
enum gui_button_mapping {
    GUI_BTN_ZEROVALUE=0,
    Enable_System,
    Enable_Control,
    Stop,
    Set_Send_Field_1,
    Set_Send_Field_2,
    Set_Send_Field_3,
    Set_Send_Field_4,
    Set_Send_Field_5,
    Set_Send_Field_6,
    My_Button_1,
    My_Button_2,
    My_Button_3,
    My_Button_4,
    My_Button_5,
    My_Button_6,
    My_Button_7,
    My_Button_8,
    Error_Reset,
    ParaID_Enable_System,
    ParaID_Enable_Control,
    ParaID_Enable_ParameterID,
    ParaID_Disable_ParameterID,
    ParaID_Enable_ElectricalID,
    ParaID_Disable_ElectricalID,
    ParaID_Enable_FrictionID,
    ParaID_Disable_FrictionID,
    ParaID_Enable_TwoMassID,
    ParaID_Disable_TwoMassID,
    ParaID_Enable_FluxMapID,
    ParaID_Disable_FluxMapID,
    ParaID_Enable_OnlineID,
    ParaID_Disable_OnlineID,
    ParaID_Enable_Current_Control,
    ParaID_Enable_Speed_Control,
    ParaID_Disable_FOC_Control,
    ParaID_ACCEPT,
    ParaID_RESET,
    ParaID_EID_sampleTimeISR,
    ParaID_EID_n_ref_meas,
    ParaID_EID_goertzl_Torque,
    ParaID_EID_goertzl_Freq,
    ParaID_EID_DutyCyc,
    ParaID_EID_MaxContinousCurrent,
    ParaID_EID_Enable_IdentLQ,
    ParaID_EID_Disable_IdentLQ,
    ParaID_EID_Admit_Params,
    ParaID_FID_max_speed,
    ParaID_FID_N_Brk,
    ParaID_FID_N_Visco,
    ParaID_FID_s_step,
    ParaID_FID_Brk_Count,
    ParaID_FID_eta_speed,
    ParaID_FID_Array_Control_counter,
    ParaID_TMID_Scale_PRBS,
    ParaID_TMID_d_TMS_start,
    ParaID_TMID_n_ref,
    ParaID_TMID_f_min,
    ParaID_TMID_f_max,
    ParaID_TMID_Admit_Params,
    ParaID_FMID_i_d_start,
    ParaID_FMID_i_d_stop,
    ParaID_FMID_i_d_step,
    ParaID_FMID_i_q_start,
    ParaID_FMID_i_q_stop,
    ParaID_FMID_i_q_step,
    ParaID_FMID_Rs_ref,
    ParaID_FMID_Temp_ref,
    ParaID_FMID_identRAmp,
    ParaID_FMID_enable_ident_R,
    ParaID_FMID_disable_ident_R,
    ParaID_FMID_enable_AMM,
    ParaID_FMID_disable_AMM,
    ParaID_OID_Refresh_Flux_Maps,
    ParaID_OID_Reset_OnlineID,
    ParaID_OID_Enable_AutoCurrentControl,
    ParaID_OID_Disable_AutoCurrentControl,
    ParaID_OID_d_current_steps,
    ParaID_OID_q_current_steps,
    ParaID_OID_max_current,
    ParaID_OID_ref_temp,
    ParaID_OID_ref_Rs,
    ParaID_OID_max_speed,
    ParaID_OID_min_speed,
    ParaID_OID_Ident_range_factor,
    ParaID_OID_max_ident_pause,
    ParaID_OID_identR_Amp,
    ParaID_OID_Fluxmap_Control_counter,
    GUI_BTN_ENDMARKER
};


/* Visualization Config for GUI*/
// LEAVE IT COMMENTED OUT AS IT IS, the plain text below is parsed by the GUI!
// Change entries according to your needs.
/*
// Description (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

SND_FLD_ZEROVALUE=0,
selcted_Fluxmap,
i_d_ref,
i_q_ref,
kp_dq,
ki_dq,
res_gain,
SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

SND_LABELS_ZEROVALUE=0,
,
A,
A,
Ohm,
Ohm,
Ohm,
SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

RCV_FLD_ZEROVALUE=0,
AvgWindingTemp,
inv_1_tmp,
inv_2_tmp,
v_dc1,
v_dc2,
speed,
RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

RCV_LABELS_ZEROVALUE=0,
°C,
°C,
°C,
V,
V,
rpm,
RCV_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!

SLOWDAT_DISPLAY_ZEROVALUE=0,
JSSD_FLOAT_avg_winding_temp,
JSSD_FLOAT_temp_inv1,
JSSD_FLOAT_temp_inv2,
JSSD_FLOAT_v_dc1,
JSSD_FLOAT_v_dc2,
JSSD_FLOAT_speed,
JSSD_FLOAT_Error_Code,
SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initalize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
