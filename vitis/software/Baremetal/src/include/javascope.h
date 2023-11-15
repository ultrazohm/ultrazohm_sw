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
	JSO_theta_mech_1,
	JSO_theta_mech_2,
	JSO_ud_ind_2,
	JSO_uq_ind_2,
	JSO_ua_1,
	JSO_ub_1,
	JSO_uc_1,
	JSO_ua_2,
	JSO_ub_2,
	JSO_uc_2,
	JSO_ia_1,
	JSO_ib_1,
	JSO_ic_1,
	JSO_ia_2,
	JSO_ib_2,
	JSO_ic_2,
	JSO_id_1,
	JSO_iq_1,
	JSO_id_2,
	JSO_iq_2,
	JSO_uq_ref_1,
	JSO_ud_ref_1,
	JSO_uq_ref_2,
	JSO_ud_ref_2,
	JSO_id_ref_1,
	JSO_iq_ref_1,
	JSO_id_ref_2,
	JSO_iq_ref_2,
	JSO_n_ref_1,
	JSO_n_ref_2,
	JSO_M_meas,
	JSO_ud_1,
	JSO_uq_1,
	JSO_ud_2,
	JSO_uq_2,
	JSO_Speed_rpm_1,
	JSO_Speed_rpm_2,
	JSO_Speed_rpm_3,
	JSO_Speed_rpm_filtered_1,
	JSO_Speed_rpm_filtered_2,
	JSO_Speed_rpm_filtered_3,
	JSO_el_Speed_rpm_1,
	JSO_el_Speed_rpm_2,
	JSO_el_Speed_rpm_3,
	JSO_LoadSpeed_rpm,
	JSO_volt_temp,
	JSO_SoC_init,
	JSO_Theta_el_1,
	JSO_Theta_el_2,
	JSO_Theta_el_3,
	JSO_Theta_el_cor_1,
	JSO_Theta_el_cor_2,
	JSO_Theta_el_off_1,
	JSO_Theta_el_off_2,
	JSO_Theta_mech_1,
	JSO_LoadTheta_mech,
	JSO_DeltaTheta_mech,
	JSO_Wtemp,
	JSO_Rs_mOhm,
	JSO_Ld_mH,
	JSO_Lq_mH,
	JSO_PsiPM_mVs,
	JSO_error_type,
	JSO_ud_ind_filt_2,
	JSO_uq_ind_filt_2,
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
	JSSD_FLOAT_u_d_1,
	JSSD_FLOAT_u_q_1,
	JSSD_FLOAT_i_d_1,
	JSSD_FLOAT_i_q_1,
	JSSD_FLOAT_i_d_2,
	JSSD_FLOAT_i_q_2,
	JSSD_FLOAT_speed_1,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_u_d_ref,
	JSSD_FLOAT_u_q_ref,
	JSSD_FLOAT_ArrayCounter,
	JSSD_FLOAT_measArray,
	JSSD_FLOAT_i_est,
	JSSD_FLOAT_ArrayControl,
	JSSD_FLOAT_Stribtorque,
	JSSD_FLOAT_Coulombtorque,
	JSSD_FLOAT_Viscotorque,
	JSSD_FLOAT_Rs,
	JSSD_FLOAT_PsiPM,
	JSSD_FLOAT_TrainInertia,
	JSSD_FLOAT_LoadInertia,
	JSSD_FLOAT_c_est,
	JSSD_FLOAT_d_est,
	JSSD_FLOAT_c_0,
	JSSD_FLOAT_MapCounter,
	JSSD_FLOAT_psidMap,
	JSSD_FLOAT_psiqMap,
	JSSD_FLOAT_idMap,
	JSSD_FLOAT_iqMap,
	JSSD_FLOAT_psi_array,
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
	JSSD_FLOAT_TempH1_1,
	JSSD_FLOAT_TempL1_1,
	JSSD_FLOAT_TempH2_1,
	JSSD_FLOAT_TempL2_1,
	JSSD_FLOAT_TempH3_1,
	JSSD_FLOAT_TempL3_1,
	JSSD_FLOAT_TempH1_2,
	JSSD_FLOAT_TempL1_2,
	JSSD_FLOAT_TempH2_2,
	JSSD_FLOAT_TempL2_2,
	JSSD_FLOAT_TempH3_2,
	JSSD_FLOAT_TempL3_2,
	JSSD_FLOAT_u_ind_d,
	JSSD_FLOAT_u_ind_q,
	JSSD_FLOAT_u_ind_filt_d,
	JSSD_FLOAT_u_ind_filt_q,
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
	Set_Send_Field_7,
	Set_Send_Field_8,
	Set_Send_Field_9,
	Set_Send_Field_10,
	Set_Send_Field_11,
	Set_Send_Field_12,
	Set_Send_Field_13,
	Set_Send_Field_14,
	Set_Send_Field_15,
	Set_Send_Field_16,
	Set_Send_Field_17,
	Set_Send_Field_18,
	Set_Send_Field_19,
	Set_Send_Field_20,
	My_Button_1,
	My_Button_2,
	My_Button_3,
	My_Button_4,
	My_Button_5,
	My_Button_6,
	My_Button_7,
	My_Button_8,
	Error_Reset,
	GUI_BTN_ENDMARKER
};


/* Visualization Config for GUI*/
// LEAVE IT COMMENTED OUT AS IT IS, the plain text below is parsed by the GUI!
// Change entries according to your needs.
/*
// Description (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_FLD_ZEROVALUE=0,
	n_ref_rpm_1,
	i_dq_ref_Amps_2.d,
	i_dq_ref_Amps_2.q,
	send_field_4,
	send_field_5,
	send_field_6,
	send_field_7,
	send_field_8,
	send_field_9,
	send_field_10,
	send_field_11,
	send_field_12,
	send_field_13,
	send_field_14,
	send_field_15,
	send_field_16,
	send_field_17,
	send_field_18,
	send_field_19,
	send_field_20,
	SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_LABELS_ZEROVALUE=0,

	RPM,
	A,
	A,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	Rotor_speed_1,
	i_d_2,
	i_q_2,
	u_ind_filt_d_2,
	u_ind_filt_q_2,
	torque,
	receive_field_7,
	receive_field_8,
	receive_field_9,
	receive_field_10,
	receive_field_11,
	receive_field_12,
	receive_field_13,
	receive_field_14,
	receive_field_15,
	receive_field_16,
	receive_field_17,
	receive_field_18,
	receive_field_19,
	receive_field_20,
	RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_LABELS_ZEROVALUE=0,
	RPM,
	A,
	A,
	V,
	V,
	Nm,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	-,
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	MyButton1,
	MyButton2,
	MyButton3,
	HC_off,
	HC_on,
	MyButton6,
	MyButton7,
	MyButton8,
	MYBUTTONS_LABELS_ENDMARKER

// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_speed_1,
	JSSD_FLOAT_i_d_2,
	JSSD_FLOAT_i_q_2,
	JSSD_FLOAT_u_ind_filt_d,
	JSSD_FLOAT_u_ind_filt_q,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_Error_Code,
	SLOWDAT_DISPLAY_ENDMARKER
*/

int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
