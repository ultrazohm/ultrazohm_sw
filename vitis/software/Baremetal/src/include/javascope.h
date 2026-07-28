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
	JSO_speed_Beckhoff,
	JSO_id_Beckhoff,
	JSO_iq_Beckhoff,
	JSO_ia_Beckhoff,
	JSO_ib_Beckhoff,
	JSO_ic_Beckhoff,
	JSO_vdc_Beckhoff,
	JSO_vd_Beckhoff,
	JSO_vq_Beckhoff,
	JSO_theta_el_Beckhoff,
	JSO_speed_HM,
	JSO_id_HM,
	JSO_iq_HM,
	JSO_ia_HM,
	JSO_ib_HM,
	JSO_ic_HM,
	JSO_vdc_HM,
	JSO_vd_HM,
	JSO_vq_HM,
	JSO_theta_el_HM,
	JSO_beck_actual_i_d,
	JSO_beck_actual_i_q,
	JSO_beck_actual_v_d,
	JSO_beck_actual_v_q,
	JSO_beck_actual_omega_el,
	JSO_beck_actual_theta_el,
	JSO_beck_actual_speed_rpm,
	JSO_beck_actual_theta_el_advanced,
	JSO_beck_meas_i_a,
	JSO_beck_meas_i_b,
	JSO_beck_meas_i_c,
	JSO_beck_meas_v_a,
	JSO_beck_meas_v_b,
	JSO_beck_meas_v_c,
	JSO_beck_meas_vdc,
	JSO_beck_meas_idc,
	JSO_beck_meas_omega_mech,
	JSO_beck_meas_theta_mech,
	JSO_beck_ref_speed_rpm,
	JSO_beck_ref_M_in_Nm,
	JSO_beck_ref_i_d,
	JSO_beck_ref_i_q,
	JSO_beck_ref_v_d,
	JSO_beck_ref_v_q,
	JSO_beck_ref_v_a,
	JSO_beck_ref_v_b,
	JSO_beck_ref_v_c,
	JSO_beck_ref_duty_a,
	JSO_beck_ref_duty_b,
	JSO_beck_ref_duty_c,
	JSO_hm_actual_i_d,
	JSO_hm_actual_i_q,
	JSO_hm_actual_v_d,
	JSO_hm_actual_v_q,
	JSO_hm_actual_omega_el,
	JSO_hm_actual_theta_el,
	JSO_hm_actual_speed_rpm,
	JSO_hm_actual_theta_el_advanced,
	JSO_hm_meas_i_a,
	JSO_hm_meas_i_b,
	JSO_hm_meas_i_c,
	JSO_hm_meas_v_a,
	JSO_hm_meas_v_b,
	JSO_hm_meas_v_c,
	JSO_hm_meas_vdc,
	JSO_hm_meas_idc,
	JSO_hm_meas_omega_mech,
	JSO_hm_meas_theta_mech,
	JSO_hm_ref_speed_rpm,
	JSO_hm_ref_M_in_Nm,
	JSO_hm_ref_i_d,
	JSO_hm_ref_i_q,
	JSO_hm_ref_v_d,
	JSO_hm_ref_v_q,
	JSO_hm_ref_v_a,
	JSO_hm_ref_v_b,
	JSO_hm_ref_v_c,
	JSO_hm_ref_duty_a,
	JSO_hm_ref_duty_b,
	JSO_hm_ref_duty_c,
/* Project Wizard BEGIN: javascope_observables */
	JSO_ADC_A1_CH0,
	JSO_ADC_A1_CH1,
	JSO_ADC_A1_CH2,
	JSO_ADC_A1_CH3,
	JSO_ADC_A1_CH4,
	JSO_ADC_A1_CH5,
	JSO_ADC_A1_CH6,
	JSO_ADC_A1_CH7,
	JSO_ADC_A2_CH0,
	JSO_ADC_A2_CH1,
	JSO_ADC_A2_CH2,
	JSO_ADC_A2_CH3,
	JSO_ADC_A2_CH4,
	JSO_ADC_A2_CH5,
	JSO_ADC_A2_CH6,
	JSO_ADC_A2_CH7,
	JSO_ADC_A3_CH0,
	JSO_ADC_A3_CH1,
	JSO_ADC_A3_CH2,
	JSO_ADC_A3_CH3,
	JSO_ADC_A3_CH4,
	JSO_ADC_A3_CH5,
	JSO_ADC_A3_CH6,
	JSO_ADC_A3_CH7,
	JSO_RESOLVER_PL_D4_CH1_POS_MECH_2PI,
	JSO_RESOLVER_PL_D4_CH1_POS_EL_2PI,
	JSO_RESOLVER_PL_D4_CH1_OMEGA_MECH_RAD_S,
	JSO_RESOLVER_PL_D4_CH1_N_MECH_RPM,
	JSO_RESOLVER_PL_D4_CH1_OMEGA_EL_RAD_S,
	JSO_RESOLVER_PL_D4_CH1_REVOLUTION_COUNTER,
	JSO_RESOLVER_PL_D4_CH2_POS_MECH_2PI,
	JSO_RESOLVER_PL_D4_CH2_POS_EL_2PI,
	JSO_RESOLVER_PL_D4_CH2_OMEGA_MECH_RAD_S,
	JSO_RESOLVER_PL_D4_CH2_N_MECH_RPM,
	JSO_RESOLVER_PL_D4_CH2_OMEGA_EL_RAD_S,
	JSO_RESOLVER_PL_D4_CH2_REVOLUTION_COUNTER,
	JSO_RESOLVER_PL_D4_CH3_POS_MECH_2PI,
	JSO_RESOLVER_PL_D4_CH3_POS_EL_2PI,
	JSO_RESOLVER_PL_D4_CH3_OMEGA_MECH_RAD_S,
	JSO_RESOLVER_PL_D4_CH3_N_MECH_RPM,
	JSO_RESOLVER_PL_D4_CH3_OMEGA_EL_RAD_S,
	JSO_RESOLVER_PL_D4_CH3_REVOLUTION_COUNTER,
/* Project Wizard END: javascope_observables */
	JSO_D3_INPUT_LOOPBACK_UINT32,
	JSO_ENDMARKER
};

// slowData Naming Convention: Use JSSD_FLOAT_ as prefix
// Do not change the first (zero) and last (end) entries.
enum JS_SlowData {
	JSSD_ZEROVALUE=0,
	JSSD_FLOAT_speed_n,
	JSSD_FLOAT_id_Beckhoff,
	JSSD_FLOAT_iq_Beckhoff,
	JSSD_FLOAT_id_HM,
	JSSD_FLOAT_iq_HM,
	JSSD_FLOAT_Milliseconds,
	JSSD_FLOAT_Error_Code,
	JSSD_FLOAT_dut_select,
/* Project Wizard BEGIN: javascope_slowdata */
/* Project Wizard END: javascope_slowdata */
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
	n_ref_DUT,
	i_d_ref_HM,
	i_q_ref_HM,
	dutycycle_A_HM,
	dutycycle_B_HM,
	dutycycle_C_HM,
	i_d_ref_Beckhoff,
	i_q_ref_Beckhoff,
	dutycycle_A_Beckhoff,
	dutycycle_B_Beckhoff,
	dutycycle_C_Beckhoff
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
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	speed_n,
	i_d_in_A_HM,
	i_q_in_A_HM,
	receive_field_4,
	receive_field_5,
	receive_field_6,
	i_d_in_A_Beckhoff,
	i_q_in_A_Beckhoff,
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
	rpm,
	A,
	A,
	-,
	-,
	-,
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
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	RESET_DHG_INV,
	CIL,
	REAL,
	speed,
	current,
	dutycycle,
	reset_error,
	DUT,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_speed_n,
	JSSD_FLOAT_id_HM,
	JSSD_FLOAT_iq_HM,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_id_Beckhoff,
	JSSD_FLOAT_iq_Beckhoff,
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
	JSSD_FLOAT_dut_select,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
