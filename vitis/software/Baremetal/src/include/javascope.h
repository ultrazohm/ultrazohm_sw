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
	JSO_ia_left,
	JSO_ib_left,
	JSO_ic_left,
	JSO_ia_right,
	JSO_ib_right,
	JSO_ic_right,
	JSO_id_left,
	JSO_iq_left,
	JSO_id_right,
	JSO_iq_right,
	JSO_va_left,
	JSO_vb_left,
	JSO_vc_left,
	JSO_va_right,
	JSO_vb_right,
	JSO_vc_right,
	JSO_v_dc_left,
	JSO_v_dc_right,
	JSO_vd_left,
	JSO_vq_left,
	JSO_vd_right,
	JSO_vq_right,
	JSO_ia_pu_ip,
	JSO_ib_pu_ip,
	JSO_ic_pu_ip,
	JSO_id_pu_ip,
	JSO_iq_pu_ip,
	JSO_id_delay_pu,
	JSO_iq_delay_pu,
	JSO_idc_left,
	JSO_idc_right,
	JSO_vd_pu,
	JSO_vq_pu,
	JSO_theta_el_left,
	JSO_theta_el_right,
	JSO_theta_mech_left,
	JSO_theta_mech_right,
	JSO_mech_Speed_rpm_left,
	JSO_mech_Speed_rpm_right,
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
	JSSD_FLOAT_temp_inv_left,
	JSSD_FLOAT_temp_inv_right,
	JSSD_FLOAT_f_sw_avg_Hz_right,
	JSSD_FLOAT_vd_left,
	JSSD_FLOAT_vq_left,
	JSSD_FLOAT_id_left,
	JSSD_FLOAT_iq_left,
	JSSD_FLOAT_v_dc_left,
	JSSD_FLOAT_speed,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_u_d_ref,
	JSSD_FLOAT_u_q_ref,
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
	n_ref_rpm_left,
	send_field_2,
	id_ref_right,
	iq_ref_right,
	send_field_5,
	send_field_6,
	Kp_id_left,
	Ki_id_left,
	Kp_iq_left,
	Ki_iq_left,
	Kp_speed_left,
	Ki_speed_left,
	Kp_id_right,
	Ki_id_right,
	Kp_iq_right,
	Ki_iq_right,
	lambda_d,
	lambda_q,
	lambda_u,
	i_max_mpc,
	SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_LABELS_ZEROVALUE=0,
	RPM,
	-,
	A,
	A,
	-,
	-,
	Ohm,
	Ohm/s,
	Ohm,
	Ohm/s,
	Nms/rad,
	Nm/rad,
	Ohm,
	Ohm/s,
	Ohm,
	Ohm/s,
	-,
	-,
	-,
	p.u.,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	mech_speed_left,
	id_left,
	iq_left,
	vd_left,
	vq_left,
	v_dc_left,
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
	PI_FOC_right,
	FCS-MPC_right,
	DDPG-CC_right,
	MyButton4,
	MyButton5,
	MyButton6,
	MyButton7,
	MyButton8,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_speed,
	JSSD_FLOAT_id_left,
	JSSD_FLOAT_iq_left,
	JSSD_FLOAT_vd_left,
	JSSD_FLOAT_vq_left,
	JSSD_FLOAT_v_dc_left,
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
