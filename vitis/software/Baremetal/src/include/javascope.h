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
	JSO_va_DUT,
	JSO_vb_DUT,
	JSO_vc_DUT,
	JSO_ia_DUT,
	JSO_ib_DUT,
	JSO_ic_DUT,
	JSO_id_DUT,
	JSO_iq_DUT,
	JSO_id_ref_DUT,
	JSO_iq_ref_DUT,
	JSO_vd_DUT,
	JSO_vq_DUT,
	JSO_vd_ref_DUT,
	JSO_vq_ref_DUT,
	JSO_current_angle_deg_DUT,
	JSO_current_angle_ref_DUT,
	JSO_is_DUT,
	JSO_is_ref_DUT,
	JSO_torque_DUT,
	JSO_torque_ref_DUT,
	JSO_Speed_rpm_DUT,
	JSO_Theta_el_DUT,
	JSO_Theta_mech_DUT,
	JSO_i_dc_DUT,
	JSO_v_dc_DUT,
	JSO_va_Load,
	JSO_vb_Load,
	JSO_vc_Load,
	JSO_ia_Load,
	JSO_ib_Load,
	JSO_ic_Load,
	JSO_id_Load,
	JSO_iq_Load,
	JSO_id_ref_Load,
	JSO_iq_ref_Load,
	JSO_vd_Load,
	JSO_vq_Load,
	JSO_vd_ref_Load,
	JSO_vq_ref_Load,
	JSO_is_Load,
	JSO_torque_Load,
	JSO_torque_ref_Load,
	JSO_Speed_rpm_Load,
	JSO_Theta_el_Load,
	JSO_Theta_mech_Load,
	JSO_i_dc_Load,
	JSO_v_dc_Load,
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
	JSSD_FLOAT_v_d_DUT,
	JSSD_FLOAT_v_q_DUT,
	JSSD_FLOAT_i_d_DUT,
	JSSD_FLOAT_i_q_DUT,
	JSSD_FLOAT_i_s_DUT,
	JSSD_FLOAT_speed_DUT,
	JSSD_FLOAT_torque_DUT,
	JSSD_FLOAT_v_d_ref_DUT,
	JSSD_FLOAT_v_q_ref_DUT,
	JSSD_FLOAT_current_angle_deg_DUT,
	JSSD_FLOAT_v_d_Load,
	JSSD_FLOAT_v_q_Load,
	JSSD_FLOAT_i_d_Load,
	JSSD_FLOAT_i_q_Load,
	JSSD_FLOAT_speed_Load,
	JSSD_FLOAT_torque_Load,
	JSSD_FLOAT_v_d_ref_Load,
	JSSD_FLOAT_v_q_ref_Load,
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
	n_ref(CIL/REAL),
	M_ref,
	v_d_manual(CIL),
	v_q_manual(CIL),
	send_field_5,
	send_field_6,
	DUT_DutyCycle_A,
	DUT_DutyCycle_B,
	DUT_DutyCycle_C,
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
	-,
	-,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	n_rpm_DUT,
	Torque_DUT,
	i_d_DUT,
	i_q_DUT,
	i_s_DUT,
	i_q_Load,
	i_d_Load,
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
	NM,
	A,
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
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	CIL,
	REAL,
	FOC,
	RL,
	manual,
	MyButton6,
	MyButton7,
	MyButton8,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_speed_DUT,
	JSSD_FLOAT_torque_DUT,
	JSSD_FLOAT_i_d_DUT,
	JSSD_FLOAT_i_q_DUT,
	JSSD_FLOAT_i_s_DUT,
	JSSD_FLOAT_i_q_Load,
	JSSD_FLOAT_i_d_Load,
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
