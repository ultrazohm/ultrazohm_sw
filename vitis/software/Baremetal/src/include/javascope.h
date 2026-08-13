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
	JSO_IM_I_A,
	JSO_IM_I_B,
	JSO_IM_I_C,
	JSO_IM_V_DC,
	JSO_IM_SPEED_RPM,
	JSO_IM_FREQUENCY_HZ,
	JSO_IM_VOLTAGE_V,
	JSO_IM_I_D,
	JSO_IM_I_Q,
	JSO_IM_I_D_RAW,
	JSO_IM_I_Q_RAW,
	JSO_IM_I_D_REF,
	JSO_IM_I_Q_REF,
	JSO_IM_FLUX_VS,
	JSO_IM_FLUX_ANGLE_RAD,
	JSO_IM_ROTOR_ELECTRICAL_ANGLE_RAD,
	JSO_IM_FLUX_ROTOR_ANGLE_DIFFERENCE_RAD,
	JSO_IM_ROTOR_ELECTRICAL_FREQUENCY_HZ,
	JSO_IM_SLIP_FREQUENCY_HZ,
	JSO_IM_SLIP_PERCENT,
	JSO_IM_STATOR_FREQUENCY_HZ,
	JSO_IM_DUTY_A,
	JSO_IM_DUTY_B,
	JSO_IM_DUTY_C,
	JSO_D3_INPUT_LOOPBACK_UINT32,
	JSO_INVERTER_TEMPERATURE_DEG_C,
	JSO_INVERTER_TEMPERATURE_PWM_DUTY_CYCLE_PERCENT,
	JSO_INVERTER_TEMPERATURE_PWM_FREQUENCY_HZ,
	JSO_IM_CURRENT_OFFSET_A_A,
	JSO_IM_CURRENT_OFFSET_B_A,
	JSO_IM_CURRENT_OFFSET_C_A,
	JSO_IM_CURRENT_OFFSET_PROGRESS_PERCENT,
	JSO_IM_CURRENT_OFFSET_MAX_STDDEV_A,
	JSO_IM_CURRENT_SUM_ERROR_A,
	JSO_IM_CURRENT_OFFSET_VALID,
	JSO_IM_ROTOR_FLUX_VALID,
	JSO_IM_SLIP_FREQUENCY_LIMITED,
	JSO_IM_FLUX_ANGLE_STEP_RAD,
	JSO_IM_FLUX_ANGLE_STEP_VIOLATION,
	JSO_IM_PHASE_CURRENT_SUM_A,
	JSO_IM_PHASE_CURRENT_SUM_VIOLATION,
	JSO_IM_VOLTAGE_VECTOR_MAGNITUDE_V,
	JSO_IM_VOLTAGE_VECTOR_LIMIT_V,
	JSO_IM_VOLTAGE_VECTOR_SATURATED,
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
	JSSD_FLOAT_IM_Speed_RPM,
	JSSD_FLOAT_IM_V_DC,
	JSSD_FLOAT_IM_Slip_Percent,
	JSSD_FLOAT_IM_Frequency_Hz,
	JSSD_FLOAT_IM_Voltage_V,
	JSSD_FLOAT_Inverter_Temperature_DegC,
	JSSD_FLOAT_IM_I_D,
	JSSD_FLOAT_IM_I_Q,
	JSSD_FLOAT_IM_I_D_Raw,
	JSSD_FLOAT_IM_I_Q_Raw,
	JSSD_FLOAT_IM_Flux_Vs,
	JSSD_FLOAT_IM_Flux_Angle_Rad,
	JSSD_FLOAT_IM_Rotor_Electrical_Angle_Rad,
	JSSD_FLOAT_IM_Flux_Rotor_Angle_Difference_Rad,
	JSSD_FLOAT_IM_Rotor_Electrical_Frequency_Hz,
	JSSD_FLOAT_Inverter_Hardware_Overcurrent,
	JSSD_FLOAT_IM_Slip_Frequency_Hz,
	JSSD_FLOAT_IM_Stator_Frequency_Hz,
	JSSD_FLOAT_IM_I_D_Reference_A,
	JSSD_FLOAT_IM_I_Q_Reference_A,
	JSSD_FLOAT_IM_FOC_SOR_Status,
	JSSD_FLOAT_IM_Current_Offset_Valid,
	JSSD_FLOAT_IM_Rotor_Flux_Valid,
	JSSD_FLOAT_IM_Slip_Frequency_Limited,
	JSSD_FLOAT_IM_Flux_Angle_Step_Violation,
	JSSD_FLOAT_IM_Phase_Current_Sum_Violation,
	JSSD_FLOAT_IM_Voltage_Vector_Saturated,
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
	IM_Id_Reference,
	IM_Iq_Reference,
	IM_UF_Frequency,
	IM_FOC_Current_Kp_D,
	IM_FOC_Current_Ki_D,
	IM_FOC_Current_Kp_Q,
	IM_FOC_Current_Ki_Q,
	IM_FOC_Kalman_Q_A2_Per_S,
	IM_FOC_Kalman_R_A2,
	IM_FOC_Resonant_Gain_D,
	IM_FOC_Resonant_Gain_Q,
	IM_FOC_Resonant_Harmonic_Order,
	IM_FOC_Resonant_Antiwindup_Gain,
	IM_FOC_Resonant_Voltage_Limit,
	IM_FOC_Slip_Flux_Minimum,
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
	V_per_A,
	V_per_As,
	V_per_A,
	V_per_As,
	A2_per_s,
	A2,
	V_per_As,
	V_per_As,
	-,
	-,
	V,
	Vs,
	-,
	-,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	IM_Speed,
	Inverter_Hardware_Overcurrent,
	IM_Slip_Frequency,
	IM_Stator_Frequency,
	IM_V_DC,
	IM_Slip_Percent,
	IM_FOC_Current_Kp_D,
	IM_FOC_Current_Ki_D,
	IM_FOC_Current_Kp_Q,
	IM_FOC_Current_Ki_Q,
	IM_FOC_Kalman_Q_A2_Per_S,
	IM_FOC_Kalman_R_A2,
	IM_FOC_Resonant_Gain_D,
	IM_FOC_Resonant_Gain_Q,
	IM_FOC_Resonant_Harmonic_Order,
	IM_FOC_Resonant_Antiwindup_Gain,
	IM_FOC_Resonant_Voltage_Limit,
	IM_FOC_Slip_Flux_Minimum,
	IM_Inverter_Temperature,
	IM_FOC_SOR_Status,
	Error_Code,
	RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_LABELS_ZEROVALUE=0,
	rpm,
	bool,
	Hz,
	Hz,
	V,
	percent,
	V_per_A,
	V_per_As,
	V_per_A,
	V_per_As,
	A2_per_s,
	A2,
	V_per_As,
	V_per_As,
	-,
	-,
	V,
	Vs,
	degC,
	-,
	-,
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	IM_FOC__OFF_UF,
	VA_Speed__OFF_Current,
	IM_Kalman_Filter,
	IM_Resonant_6th,
	Enable_Trajectories,
	Unused_6,
	Unused_7,
	Unused_8,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_IM_Speed_RPM,
	JSSD_FLOAT_Inverter_Hardware_Overcurrent,
	JSSD_FLOAT_IM_Slip_Frequency_Hz,
	JSSD_FLOAT_IM_Stator_Frequency_Hz,
	JSSD_FLOAT_IM_V_DC,
	JSSD_FLOAT_IM_Slip_Percent,
	JSSD_FLOAT_Inverter_Temperature_DegC,
	JSSD_FLOAT_IM_FOC_SOR_Status,
	JSSD_FLOAT_IM_Current_Offset_Valid,
	JSSD_FLOAT_IM_Rotor_Flux_Valid,
	JSSD_FLOAT_IM_Slip_Frequency_Limited,
	JSSD_FLOAT_IM_Flux_Angle_Step_Violation,
	JSSD_FLOAT_IM_Phase_Current_Sum_Violation,
	JSSD_FLOAT_IM_Voltage_Vector_Saturated,
	JSSD_FLOAT_Error_Code,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	JSSD_ZEROVALUE,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
