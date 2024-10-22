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
enum JS_OberservableData
{
	JSO_ZEROVALUE=0,
	JSO_ISR_ExecTime_us,
	JSO_ISR_Period_us,
	JSO_lifecheck,
	JSO_dut_ia,
	JSO_dut_ib,
	JSO_dut_ic,
	JSO_dut_id,
	JSO_dut_iq,
	JSO_dut_id_set,
	JSO_dut_iq_set,
	JSO_dut_vd,
	JSO_dut_vq,
	JSO_dut_vd_ref,
	JSO_dut_vq_ref,
	JSO_dut_v_dc,
	JSO_dut_i_dc,
	JSO_dut_speed_rpm,
	JSO_dut_speed_rpm_ref,
	JSO_dut_theta_el,
	JSO_dut_theta_mech,
	JSO_dut_torque_setpoint_Nm,
	JSO_pm_ia,
	JSO_pm_ib,
	JSO_pm_ic,
	JSO_pm_id,
	JSO_pm_iq,
	JSO_pm_id_set,
	JSO_pm_iq_set,
	JSO_pm_vd,
	JSO_pm_vq,
	JSO_pm_vd_ref,
	JSO_pm_vq_ref,
	JSO_pm_v_dc,
	JSO_pm_i_dc,
	JSO_pm_speed_rpm,
	JSO_pm_speed_rpm_ref,
	JSO_pm_theta_el,
	JSO_pm_theta_mech,
	JSO_pm_torque_setpoint_Nm,
	JSO_enable,
	JSO_ddpg_obs_1,
	JSO_ddpg_obs_2,
	JSO_ddpg_obs_3,
	JSO_ddpg_obs_4,
	JSO_ddpg_obs_5,
	JSO_ddpg_obs_6,
	JSO_ddpg_obs_7,
	JSO_ddpg_obs_8,
	JSO_ddpg_obs_9,
	JSO_torque_measured_Nm,
	JSO_debug_speed_d5_1,
	JSO_torque_added_d1,
	JSO_torque_added_d2,
	JSO_debug_speed_d5_1_filtered,
	JSO_SoC_init,
	JSO_n_ref_rpm_beckhoff_filtered,
	JSO_n_rpm_beckhoff_filtered,
	JSO_pm_speed_filtered,
	JSO_ENDMARKER
};

// slowData Naming Convention: Use JSSD_FLOAT_ as prefix
// Do not change the first (zero) and last (end) entries.
enum JS_SlowData
{
	JSSD_ZEROVALUE=0,
	JSSD_FLOAT_SecondsSinceSystemStart,
	JSSD_FLOAT_ISR_ExecTime_us,
	JSSD_FLOAT_ISR_Period_us,
	JSSD_FLOAT_FreqReadback,
	JSSD_FLOAT_Milliseconds,
	JSSD_FLOAT_ADCconvFactorReadback,
	JSSD_FLOAT_Error_Code,
	JSSD_FLOAT_dut_ia,
	JSSD_FLOAT_dut_ib,
	JSSD_FLOAT_dut_ic,
	JSSD_FLOAT_dut_id,
	JSSD_FLOAT_dut_iq,
	JSSD_FLOAT_dut_id_set,
	JSSD_FLOAT_dut_iq_set,
	JSSD_FLOAT_dut_vd_ref,
	JSSD_FLOAT_dut_vq_ref,
	JSSD_FLOAT_dut_v_dc,
	JSSD_FLOAT_dut_i_dc,
	JSSD_FLOAT_dut_speed_rpm,
	JSSD_FLOAT_dut_speed_rpm_ref,
	JSSD_FLOAT_dut_theta_el,
	JSSD_FLOAT_dut_theta_mech,
	JSSD_FLOAT_dut_torque_setpoint_Nm,
	JSSD_FLOAT_pm_ia,
	JSSD_FLOAT_pm_ib,
	JSSD_FLOAT_pm_ic,
	JSSD_FLOAT_pm_id,
	JSSD_FLOAT_pm_iq,
	JSSD_FLOAT_pm_id_set,
	JSSD_FLOAT_pm_iq_set,
	JSSD_FLOAT_pm_vd_ref,
	JSSD_FLOAT_pm_vq_ref,
	JSSD_FLOAT_pm_v_dc,
	JSSD_FLOAT_pm_i_dc,
	JSSD_FLOAT_pm_speed_rpm,
	JSSD_FLOAT_pm_speed_rpm_ref,
	JSSD_FLOAT_pm_theta_el,
	JSSD_FLOAT_pm_theta_mech,
	JSSD_FLOAT_pm_torque_setpoint_Nm,
	JSSD_FLOAT_u_d_1,
	JSSD_FLOAT_u_q_1,
	JSSD_FLOAT_u_q_2,
	JSSD_FLOAT_i_d_1,
	JSSD_FLOAT_i_d_2,
	JSSD_FLOAT_i_q_1,
	JSSD_FLOAT_i_q_2,
	JSSD_FLOAT_speed_1,
	JSSD_FLOAT_speed_2,
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
enum gui_button_mapping
{
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
	Speed,
	i_d,
	i_q,
	send_field_4,
	send_field_5,
	dut_theta_offset,
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
	rpm,
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
	dut_id,
	dut_iq,
	dut_n,
	pm_id,
	pm_iq,
	pm_n,
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
	A,
	A,
	rpm,
	A,
	A,
	rpm,
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
	ManualSetpoints,
	Enable_DUT,
	FOC,
	DisableSC,
	DDPG,
	Auto_IdIq,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_dut_id,
	JSSD_FLOAT_dut_iq,
	JSSD_FLOAT_dut_speed_rpm,
	JSSD_FLOAT_pm_id,
	JSSD_FLOAT_pm_iq,
	JSSD_FLOAT_pm_speed_rpm,
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

int JavaScope_initialize(DS_Data *data);
void JavaScope_update(DS_Data *data);

#endif /* INCLUDE_JAVASCOPE_H_ */
