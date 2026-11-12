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
/* Project Wizard BEGIN: javascope_observables */
	JSO_ADC_A1_CH0,
	JSO_ADC_A1_CH1,
	JSO_ADC_A1_CH2,
	JSO_ADC_A1_CH3,
	JSO_ADC_A1_CH4,
	JSO_ADC_A1_CH5,
	JSO_ADC_A1_CH6,
	JSO_ADC_A1_CH7,
	JSO_SSI_D4_CH1_POS_MECH_ST,
	JSO_SSI_D4_CH1_POS_EL_ST,
	JSO_RESOLVER_PL_D5_CH1_POS_MECH_2PI,
	JSO_RESOLVER_PL_D5_CH1_POS_EL_2PI,
/* Project Wizard END: javascope_observables */
	JSO_id_dut,
	JSO_iq_dut,
	JSO_torque_pmsm_cil,
	JSO_omega_mech_1_s_pmsm_cil,
	JSO_dut_violation,
	JSO_dut_i_a_A,
	JSO_dut_i_b_A,
	JSO_dut_i_c_A,
	JSO_dut_v_a_V,
	JSO_dut_v_b_V,
	JSO_dut_v_c_V,
	JSO_dut_v_dc_V,
	JSO_dut_i_dc_A,
	JSO_dut_omega_mech_rad_per_sec,
	JSO_dut_theta_mech_rad,
	JSO_dut_backend,
	JSO_deskbench_inputs_ready,
	JSO_dut_speed_rpm,
	JSO_id_ref_dut,
	JSO_iq_ref_dut,
	JSO_vd_ref_dut,
	JSO_vq_ref_dut,
	JSO_dut_theta_el_rad,
	JSO_experiment_active,
	JSO_experiment_status,
	JSO_experiment_id,
	JSO_iq_step_state,
	JSO_iq_step_measurement_id,
	JSO_iq_step_kp_active,
	JSO_iq_step_reference,
	JSO_experiment_sample,
	JSO_iq_sweep_state,
	JSO_iq_sweep_frequency_id,
	JSO_iq_sweep_frequency_hz,
	JSO_iq_sweep_reference,
	JSO_iq_sweep_phase_rad,
	JSO_iq_sweep_measurement_active,
	JSO_ENDMARKER
};

// slowData Naming Convention: Use JSSD_FLOAT_ as prefix
// Do not change the first (zero) and last (end) entries.
enum JS_SlowData {
	JSSD_ZEROVALUE=0,
	JSSD_FLOAT_SecondsSinceSystemStart,
	JSSD_FLOAT_ISR_ExecTime_us,
	JSSD_FLOAT_ISR_Period_us,
	JSSD_FLOAT_Milliseconds,
	JSSD_FLOAT_Error_Code,
/* Project Wizard BEGIN: javascope_slowdata */
	JSSD_FLOAT_INVERTER_ADAPTER_D1_CHIP_TEMP_H1,
	JSSD_FLOAT_INVERTER_ADAPTER_D1_CHIP_TEMP_L1,
	JSSD_FLOAT_INVERTER_ADAPTER_D1_CHIP_TEMP_H2,
	JSSD_FLOAT_INVERTER_ADAPTER_D1_CHIP_TEMP_L2,
	JSSD_FLOAT_INVERTER_ADAPTER_D1_CHIP_TEMP_H3,
	JSSD_FLOAT_INVERTER_ADAPTER_D1_CHIP_TEMP_L3,
	JSSD_FLOAT_INVERTER_ADAPTER_D1_OC,
	JSSD_FLOAT_INVERTER_ADAPTER_D1_FAULT,
/* Project Wizard END: javascope_slowdata */
	JSSD_FLOAT_dut_violation,
	JSSD_FLOAT_dut_backend,
	JSSD_FLOAT_deskbench_inputs_ready,
	JSSD_FLOAT_speed_dut,
	JSSD_FLOAT_id_dut,
	JSSD_FLOAT_iq_dut,
	JSSD_FLOAT_torque_dut,
	JSSD_FLOAT_Kp_iq_dut,
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
	speed_ref_prime_mover,
	id_ref_DUT,
	iq_ref_DUT,
	PM_duty_cycle,
	send_field_5,
	Kp_iq_DUT,
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
	0..1,
	-,
	V/A,
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
	speed_DUT,
	id_DUT,
	iq_DUT,
	torque_DUT,
	dut_violation,
	Kp_iq_DUT,
	dut_backend,
	deskbench_inputs_ready,
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
	Nm,
	-,
	V/A,
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
	DUT = CIL,
	DUT = REAL,
	iq step response,
	iq frequency sweep,
	Mode = DUTY,
	PM phase A,
	PM phase B,
	PM phase C,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_speed_dut,
	JSSD_FLOAT_id_dut,
	JSSD_FLOAT_iq_dut,
	JSSD_FLOAT_torque_dut,
	JSSD_FLOAT_dut_violation,
	JSSD_FLOAT_Kp_iq_dut,
	JSSD_FLOAT_dut_backend,
	JSSD_FLOAT_deskbench_inputs_ready,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_FLOAT_Error_Code,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
