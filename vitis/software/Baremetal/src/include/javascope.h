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
	JSO_mech_Speed_rpm_left,
	JSO_id_ref_left,
	JSO_iq_ref_left,
	JSO_id_left,
	JSO_iq_left,
	JSO_ia_left,
	JSO_ib_left,
	JSO_ic_left,
	JSO_mech_Speed_rpm_right,
	JSO_torque,
	JSO_id_ref_right,
	JSO_iq_ref_right,
	JSO_id_right,
	JSO_iq_right,
	JSO_ia_right,
	JSO_ib_right,
	JSO_ic_right,
	JSO_v_dc_left,
	JSO_v_dc_right,
	JSO_Te,
	JSO_theta_el_left,
	JSO_theta_el_right,
	JSO_vd_left,
	JSO_vq_left,
	JSO_vd_right,
	JSO_vq_right,
	JSO_idc_left,
	JSO_idc_right,
	JSO_theta_mech_left,
	JSO_theta_mech_right,
	JSO_torque_filt,
	JSO_n_ref_left,
	JSO_n_ref_left_filt,
	JSO_n_ref_right,
	JSO_n_ref_right_filt,
	JSO_ISR_ExecTime_us,
	JSO_ISR_Period_us,
	JSO_lifecheck,
	JSO_M_ref_left,
	JSO_omega_mech_left,
	JSO_omega_el_left,
	JSO_duty_a_left,
	JSO_duty_b_left,
	JSO_duty_c_left,
	JSO_duty_a_right,
	JSO_duty_b_right,
	JSO_duty_c_right,
	JSO_da,
	JSO_db,
	JSO_dc,
	JSO_theta_e_right_est,
	JSO_theta_e_right_unwrap,
	JSO_i_alpha_right_est,
	JSO_i_beta_right_est,
	JSO_i_alpha_right,
	JSO_i_beta_right,
	JSO_n_right_est,
	JSO_theta_e_left_est,
	JSO_theta_left_est,
	JSO_w_e_left_est,
	JSO_w_left_est,
	JSO_n_left_est,
	JSO_theta_i,
	JSO_sec,
	JSO_Ua_comp,
	JSO_Ub_comp,
	JSO_Uc_comp,
	JSO_Endat_theta_mech,
	JSO_Endat_theta_elec,
	JSO_Endat_Speed_rpm,
	JSO_Endat_el_Speed_rad_s,
	JSO_Endat_PLL_theta_mech,
	JSO_Endat_PLL_theta_elec,
	JSO_Endat_PLL_Speed_rpm,
	JSO_Endat_PLL_el_Speed_rad_s,
	JSO_EncoderOffset_Resolver_Progress,
	JSO_EncoderOffset_Resolver_Diagnose,
	JSO_EncoderOffset_Resolver_Id_Ref,
	JSO_EncoderOffset_Resolver_Iq_Ref,
	JSO_EncoderOffset_Resolver_Offset,
	JSO_EncoderOffset_Endat_Progress,
	JSO_EncoderOffset_Endat_Diagnose,
	JSO_EncoderOffset_Endat_Id_Ref,
	JSO_EncoderOffset_Endat_Iq_Ref,
	JSO_EncoderOffset_Endat_Offset,
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
	JSSD_FLOAT_Overcurrent_AC,
	JSSD_FLOAT_Overvoltage_DC,
	JSSD_FLOAT_Overspeed,
	JSSD_FLOAT_Overtorque,
	JSSD_FLOAT_Error_Max_Current_Left,
	JSSD_FLOAT_Error_Max_Current_Right,
	JSSD_FLOAT_Error_Vdc_Left,
	JSSD_FLOAT_Error_Vdc_Right,
	JSSD_FLOAT_Error_Overspeed_Latch,
	JSSD_FLOAT_Error_Overtorque_Latch,
	JSSD_FLOAT_v_dc_left,
	JSSD_FLOAT_speed_left,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_torque_filt,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_u_d_ref,
	JSSD_FLOAT_u_q_ref,
	JSSD_FLOAT_Endat_theta_mech,
	JSSD_FLOAT_Endat_theta_elec,
	JSSD_FLOAT_Endat_Speed_rpm,
	JSSD_FLOAT_Endat_el_Speed_rad_s,
	JSSD_FLOAT_Endat_PLL_theta_mech,
	JSSD_FLOAT_Endat_PLL_theta_elec,
	JSSD_FLOAT_Endat_PLL_Speed_rpm,
	JSSD_FLOAT_Endat_PLL_el_Speed_rad_s,
	JSSD_FLOAT_EncoderOffset_Resolver_Progress,
	JSSD_FLOAT_EncoderOffset_Resolver_Diagnose,
	JSSD_FLOAT_EncoderOffset_Resolver_Id_Ref,
	JSSD_FLOAT_EncoderOffset_Resolver_Iq_Ref,
	JSSD_FLOAT_EncoderOffset_Resolver_Offset,
	JSSD_FLOAT_EncoderOffset_Endat_Progress,
	JSSD_FLOAT_EncoderOffset_Endat_Diagnose,
	JSSD_FLOAT_EncoderOffset_Endat_Id_Ref,
	JSSD_FLOAT_EncoderOffset_Endat_Iq_Ref,
	JSSD_FLOAT_EncoderOffset_Endat_Offset,
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
	n_ref_rpm_right,
	iq_ref_right,
	iq_ref_left,
	torque_calibration_offset,
	DT_Comp,
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
	fake_mech_offset_endat_machine,
	mech_offset_endat_machine_ipcore,
	wc_filter_EMF/amplitude,
	wc_speed/frequency,
	SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_LABELS_ZEROVALUE=0,
	RPM,
	-,
	A,
	A,
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
	rad,
	-,
	-,
	-,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	speed_left,
	torque_right,
	id_left,
	iq_left,
	vd_left,
	vq_left,
	receive_field_7,
	receive_field_8,
	receive_field_9,
	receive_field_10,
	Error_OC_Left,
	Error_OC_Right,
	Error_Vdc_Left,
	Error_Vdc_Right,
	Error_Overspeed,
	Error_Overtorque,
	Endat_PLL_Speed_rpm,
	Endat_PLL_el_Speed_rad_s,
	EO_Resolver_Progress,
	EO_Endat_Progress,
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
	bool,
	bool,
	bool,
	bool,
	bool,
	bool,
	RPM,
	rad/s,
	-,
	-,
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	MyButton1,
	MyButton2,
	MyButton3,
	Right_Speed2Torque,
	Right_Torque2Speed,
	MyButton6,
	MyButton7,
	MyButton8,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_speed_left,
	JSSD_FLOAT_torque_filt,
	JSSD_FLOAT_id_left,
	JSSD_FLOAT_iq_left,
	JSSD_FLOAT_vd_left,
	JSSD_FLOAT_vq_left,
	JSSD_FLOAT_Endat_theta_mech,
	JSSD_FLOAT_Endat_theta_elec,
	JSSD_FLOAT_Endat_Speed_rpm,
	JSSD_FLOAT_Endat_el_Speed_rad_s,
	JSSD_FLOAT_Error_Max_Current_Left,
	JSSD_FLOAT_Error_Max_Current_Right,
	JSSD_FLOAT_Error_Vdc_Left,
	JSSD_FLOAT_Error_Vdc_Right,
	JSSD_FLOAT_Error_Overspeed_Latch,
	JSSD_FLOAT_Error_Overtorque_Latch,
	JSSD_FLOAT_Endat_PLL_Speed_rpm,
	JSSD_FLOAT_Endat_PLL_el_Speed_rad_s,
	JSSD_FLOAT_EncoderOffset_Resolver_Progress,
	JSSD_FLOAT_EncoderOffset_Endat_Progress,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
