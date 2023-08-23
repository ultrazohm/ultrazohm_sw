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
	JSO_el_Speed_rpm,
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
	JSSD_FLOAT_cnt_1,
	JSSD_FLOAT_cnt_2,
	JSSD_FLOAT_cnt_3,
	JSSD_FLOAT_cnt_4,
	JSSD_FLOAT_cnt_5,
	JSSD_FLOAT_cnt_6,
	JSSD_FLOAT_cnt_7,
	JSSD_FLOAT_cnt_8,
	JSSD_FLOAT_cnt_9,
	JSSD_FLOAT_cnt_10,
	JSSD_FLOAT_cnt_11,
	JSSD_FLOAT_cnt_12,
	JSSD_FLOAT_cnt_13,
	JSSD_FLOAT_cnt_14,
	JSSD_FLOAT_cnt_15,
	JSSD_FLOAT_cnt_16,
	JSSD_FLOAT_cnt_17,
	JSSD_FLOAT_cnt_18,
	JSSD_FLOAT_cnt_19,
	JSSD_FLOAT_cnt_20,
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
	send_field_1,
	send_field_2,
	send_field_3,
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
	Nm,
	A,
	A,
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
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	JSSD_FLOAT_cnt_1,
	JSSD_FLOAT_cnt_2,
	JSSD_FLOAT_cnt_3,
	JSSD_FLOAT_cnt_4,
	JSSD_FLOAT_cnt_5,
	JSSD_FLOAT_cnt_6,
	JSSD_FLOAT_cnt_7,
	JSSD_FLOAT_cnt_8,
	JSSD_FLOAT_cnt_9,
	JSSD_FLOAT_cnt_10,
	JSSD_FLOAT_cnt_11,
	JSSD_FLOAT_cnt_12,
	JSSD_FLOAT_cnt_13,
	JSSD_FLOAT_cnt_14,
	JSSD_FLOAT_cnt_15,
	JSSD_FLOAT_cnt_16,
	JSSD_FLOAT_cnt_17,
	JSSD_FLOAT_cnt_18,
	JSSD_FLOAT_cnt_19,
	JSSD_FLOAT_cnt_20,
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
MyButton4,
MyButton5,
MyButton6,
MyButton7,
MyButton8,
MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_cnt_1,
	JSSD_FLOAT_cnt_2,
	JSSD_FLOAT_cnt_3,
	JSSD_FLOAT_cnt_4,
	JSSD_FLOAT_cnt_5,
	JSSD_FLOAT_cnt_6,
	JSSD_FLOAT_cnt_7,
	JSSD_FLOAT_cnt_8,
	JSSD_FLOAT_cnt_9,
	JSSD_FLOAT_cnt_10,
	JSSD_FLOAT_cnt_11,
	JSSD_FLOAT_cnt_12,
	JSSD_FLOAT_cnt_13,
	JSSD_FLOAT_cnt_14,
	JSSD_FLOAT_cnt_15,
	JSSD_FLOAT_cnt_16,
	JSSD_FLOAT_cnt_17,
	JSSD_FLOAT_cnt_18,
	JSSD_FLOAT_cnt_19,
	JSSD_FLOAT_cnt_20,
	JSSD_FLOAT_Error_Code,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
