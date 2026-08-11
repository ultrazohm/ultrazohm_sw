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
	JSO_VA_I_A,
	JSO_VA_I_B,
	JSO_VA_I_C,
	JSO_VA_V_DC,
	JSO_VA_I_DC,
	JSO_VA_SPEED_RPM,
	JSO_VA_OMEGA_MECH,
	JSO_VA_THETA_EL,
	JSO_VA_I_D,
	JSO_VA_I_Q,
	JSO_VA_V_D,
	JSO_VA_V_Q,
	JSO_VA_I_D_REF,
	JSO_VA_I_Q_REF,
	JSO_VA_SPEED_REF_RPM,
	JSO_VA_DUTY_A,
	JSO_VA_DUTY_B,
	JSO_VA_DUTY_C,
	JSO_VA_SOR_VIOLATION,
	JSO_IM_1LA7073_I_A,
	JSO_IM_1LA7073_I_B,
	JSO_IM_1LA7073_I_C,
	JSO_IM_1LA7073_V_DC,
	JSO_IM_1LA7073_SPEED_RPM,
	JSO_IM_1LA7073_FREQUENCY_HZ,
	JSO_IM_1LA7073_VOLTAGE_V,
	JSO_IM_1LA7073_I_D,
	JSO_IM_1LA7073_I_Q,
	JSO_IM_1LA7073_I_D_REF,
	JSO_IM_1LA7073_I_Q_REF,
	JSO_IM_1LA7073_FLUX_VS,
/* Project Wizard BEGIN: javascope_observables */
	JSO_ADC_A1_CH0,
	JSO_ADC_A1_CH1,
	JSO_ADC_A1_CH2,
	JSO_ADC_A1_CH3,
	JSO_ADC_A1_CH4,
	JSO_ADC_A1_CH5,
	JSO_ADC_A1_CH6,
	JSO_ADC_A1_CH7,
	JSO_ADC_MAX11331_A3_CH0,
	JSO_ADC_MAX11331_A3_CH1,
	JSO_ADC_MAX11331_A3_CH2,
	JSO_ADC_MAX11331_A3_CH3,
	JSO_ADC_MAX11331_A3_CH4,
	JSO_ADC_MAX11331_A3_CH5,
	JSO_ADC_MAX11331_A3_CH6,
	JSO_ADC_MAX11331_A3_CH7,
	JSO_ADC_MAX11331_A3_CH8,
	JSO_ADC_MAX11331_A3_CH9,
	JSO_ADC_MAX11331_A3_CH10,
	JSO_ADC_MAX11331_A3_CH11,
	JSO_ADC_MAX11331_A3_CH12,
	JSO_ADC_MAX11331_A3_CH13,
	JSO_ADC_MAX11331_A3_CH14,
	JSO_ADC_MAX11331_A3_CH15,
	JSO_ADC_MAX11331_A3_CH16,
	JSO_ADC_MAX11331_A3_CH17,
	JSO_ADC_MAX11331_A3_CH18,
	JSO_ADC_MAX11331_A3_CH19,
	JSO_ADC_MAX11331_A3_CH20,
	JSO_ADC_MAX11331_A3_CH21,
	JSO_ADC_MAX11331_A3_CH22,
	JSO_ADC_MAX11331_A3_CH23,
/* Project Wizard END: javascope_observables */
	JSO_D3_INPUT_LOOPBACK_UINT32,
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
	JSSD_FLOAT_VA_Speed_RPM,
	JSSD_FLOAT_VA_V_DC,
	JSSD_FLOAT_VA_I_A,
	JSSD_FLOAT_VA_I_B,
	JSSD_FLOAT_VA_I_C,
	JSSD_FLOAT_VA_I_D,
	JSSD_FLOAT_VA_I_Q,
	JSSD_FLOAT_VA_SOR_Violation,
	JSSD_FLOAT_IM_1LA7073_Speed_RPM,
	JSSD_FLOAT_IM_1LA7073_V_DC,
	JSSD_FLOAT_IM_1LA7073_I_A,
	JSSD_FLOAT_IM_1LA7073_I_B,
	JSSD_FLOAT_IM_1LA7073_I_C,
	JSSD_FLOAT_IM_1LA7073_Frequency_Hz,
	JSSD_FLOAT_IM_1LA7073_Voltage_V,
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
	VA_Speed_Reference,
	VA_Id_Reference,
	VA_Iq_Reference,
	IM_1LA7073_Id_Reference,
	IM_1LA7073_Iq_Reference,
	IM_1LA7073_UF_Frequency,
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
	A,
	A,
	Hz,
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
	SecondsSinceSystemStart,
	ISR_ExecTime,
	ISR_PeriodTime,
	MillisecondsTimer,
	VA_Speed,
	VA_V_DC,
	VA_I_A,
	VA_I_B,
	VA_I_C,
	VA_I_D,
	VA_I_Q,
	VA_SOR_Violation,
	IM_1LA7073_Speed,
	IM_1LA7073_V_DC,
	IM_1LA7073_I_A,
	IM_1LA7073_I_B,
	IM_1LA7073_I_C,
	IM_1LA7073_UF_Frequency,
	IM_1LA7073_Voltage,
	receive_field_20,
	RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_LABELS_ZEROVALUE=0,
	s,
	us,
	us,
	ms,
	rpm,
	V,
	A,
	A,
	A,
	A,
	A,
	rpm,
	V,
	A,
	A,
	A,
	Hz,
	V,
	-,
	-,
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	VA_Speed__OFF_Current,
	IM_FOC__OFF_UF,
	IM_Kalman_Filter,
	IM_Resonant_6th,
	Unused_5,
	Unused_6,
	Unused_7,
	Unused_8,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_SecondsSinceSystemStart,
	JSSD_FLOAT_ISR_ExecTime_us,
	JSSD_FLOAT_ISR_Period_us,
	JSSD_FLOAT_Milliseconds,
	JSSD_FLOAT_VA_Speed_RPM,
	JSSD_FLOAT_VA_V_DC,
	JSSD_FLOAT_VA_I_A,
	JSSD_FLOAT_VA_I_B,
	JSSD_FLOAT_VA_I_C,
	JSSD_FLOAT_VA_I_D,
	JSSD_FLOAT_VA_I_Q,
	JSSD_FLOAT_VA_SOR_Violation,
	JSSD_FLOAT_IM_1LA7073_Speed_RPM,
	JSSD_FLOAT_IM_1LA7073_V_DC,
	JSSD_FLOAT_IM_1LA7073_I_A,
	JSSD_FLOAT_IM_1LA7073_I_B,
	JSSD_FLOAT_IM_1LA7073_I_C,
	JSSD_FLOAT_IM_1LA7073_Frequency_Hz,
	JSSD_FLOAT_IM_1LA7073_Voltage_V,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_Error_Code,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
