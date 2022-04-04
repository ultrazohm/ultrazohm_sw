/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel, Philipp Löhdefink, Michael Hoerner
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
	JSO_ISR_ExecTime_us,
	JSO_ISR_Period_us,
	JSO_lifecheck,
	JSO_theta_mech,
	JSO_ua,
	JSO_ub,
	JSO_uc,
	JSO_ia,
	JSO_ib,
	JSO_ic,
	JSO_id,
	JSO_iq,
	JSO_ud,
	JSO_uq,
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
	JSSD_FLOAT_polePairs,
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
	JSSD_FLOAT_c_0,
	JSSD_FLOAT_MapCounter,
	JSSD_FLOAT_psidMap,
	JSSD_FLOAT_psiqMap,
	JSSD_FLOAT_FluxTemp,
	JSSD_FLOAT_MapControl,
	JSSD_FLOAT_I_rated,
	JSSD_FLOAT_Wtemp,
	JSSD_FLOAT_FluxTempConst,
	JSSD_FLOAT_FluxTempError,
	JSSD_FLOAT_Ld_Online,
	JSSD_FLOAT_Lq_Online,
	JSSD_FLOAT_PsiPM_Online,
	JSSD_FLOAT_Rs_Online,
	JSSD_FLOAT_n_FluxPoints,
	JSSD_FLOAT_Ld,
	JSSD_FLOAT_Lq,
	JSSD_FLOAT_totalRotorInertia,
	JSSD_FLOAT_MapControlCounter,
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
	PID_Enable_System,
	PID_Enable_Control,
	PID_Enable_ParameterID,
	PID_Disable_ParameterID,
	PID_Enable_ElectricalID,
	PID_Disable_ElectricalID,
	PID_Enable_FrictionID,
	PID_Disable_FrictionID,
	PID_Enable_TwoMassID,
	PID_Disable_TwoMassID,
	PID_Enable_FluxMapID,
	PID_Disable_FluxMapID,
	PID_Enable_OnlineID,
	PID_Disable_OnlineID,
	PID_Enable_Current_Control,
	PID_Enable_Speed_Control,
	PID_Disable_FOC_Control,
	PID_ACCEPT,
	PID_RESET,
	PID_EID_sampleTimeISR,
	PID_EID_n_ref_meas,
	PID_EID_goertzl_Amp,
	PID_EID_goertzl_Freq,
	PID_EID_DutyCyc,
	PID_EID_MaxContinousCurrent,
	PID_EID_Enable_IdentLQ,
	PID_EID_Disable_IdentLQ,
	PID_EID_Admit_Params,
	PID_FID_max_speed,
	PID_FID_N_Brk,
	PID_FID_N_Visco,
	PID_FID_s_step,
	PID_FID_Brk_Count,
	PID_FID_eta_speed,
	PID_FID_Array_Control_counter,
	PID_TMID_Scale_PRBS,
	PID_TMID_d_TMS_start,
	PID_TMID_n_ref,
	PID_TMID_f_min,
	PID_TMID_f_max,
	PID_TMID_Admit_Params,
	PID_FMID_i_d_start,
	PID_FMID_i_d_stop,
	PID_FMID_i_d_step,
	PID_FMID_i_q_start,
	PID_FMID_i_q_stop,
	PID_FMID_i_q_step,
	PID_FMID_Rs_ref,
	PID_FMID_Temp_ref,
	PID_FMID_identRAmp,
	PID_FMID_enable_ident_R,
	PID_FMID_disable_ident_R,
	PID_FMID_enable_AMM,
	PID_FMID_disable_AMM,
	PID_OID_Refresh_Flux_Maps,
	PID_OID_Reset_OnlineID,
	PID_OID_Enable_AutoCurrentControl,
	PID_OID_Disable_AutoCurrentControl,
	PID_OID_d_current_steps,
	PID_OID_q_current_steps,
	PID_OID_max_current,
	PID_OID_ref_temp,
	PID_OID_ref_Rs,
	PID_OID_max_speed,
	PID_OID_min_speed,
	PID_OID_Ident_range_factor,
	PID_OID_max_ident_pause,
	PID_OID_identR_Amp,
	PID_OID_Fluxmap_Control_counter,
	GUI_BTN_ENDMARKER
};


/* Visualization Config for GUI*/
// LEAVE IT COMMENTED OUT AS IT IS, the plain text below is parsed by the GUI!
// Change entries according to your needs.
/*
// Description (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_FLD_ZEROVALUE=0,
 n_ref,
 i_d_ref,
 i_q_ref,
	send_field_4,
	send_field_5,
	send_field_6,
	SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_LABELS_ZEROVALUE=0,
	RPM,
	Nm,
	A,
	A,
	A,
	A,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
 speed,
 torque,
 i_d,
 i_q,
 u_d,
 u_q,
	RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_LABELS_ZEROVALUE=0,
	RPM,
	Nm,
	A,
	A,
	V,
	V,
	RCV_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!

	SLOWDAT_DISPLAY_ZEROVALUE=0,
 JSSD_FLOAT_speed,
 JSSD_FLOAT_torque,
 JSSD_FLOAT_i_d,
 JSSD_FLOAT_i_q,
 JSSD_FLOAT_u_d,
 JSSD_FLOAT_u_q,
	JSSD_FLOAT_Error_Code,
	SLOWDAT_DISPLAY_ENDMARKER
*/

int JavaScope_initalize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
