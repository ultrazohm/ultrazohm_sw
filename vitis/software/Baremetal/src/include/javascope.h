/******************************************************************************
* Copyright 2021 Eyke Liegmann, Sebastian Wendel, Philipp LÃ¶hdefink, Michael Hoerner
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
	JSO_theta_el,
	JSO_theta_mech,
	JSO_i_a1,
	JSO_i_b1,
	JSO_i_c1,
	JSO_i_a2,
	JSO_i_b2,
	JSO_i_c2,
	JSO_i_dc1,
	JSO_i_dc2,
	JSO_v_a1,
	JSO_v_b1,
	JSO_v_c1,
	JSO_v_a2,
	JSO_v_b2,
	JSO_v_c2,
	JSO_i_alpha,
	JSO_i_beta,
	JSO_i_x,
	JSO_i_y,
	JSO_i_z1,
	JSO_i_z2,
	JSO_id,
	JSO_iq,
	JSO_v_d,
	JSO_v_q,
	JSO_mech_Speed_rpm,
	JSO_el_Speed_rpm,
	JSO_ISR_ExecTime_us,
	JSO_ISR_Period_us,
	JSO_lifecheck,
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
	JSSD_FLOAT_v_d,
	JSSD_FLOAT_v_q,
	JSSD_FLOAT_i_d,
	JSSD_FLOAT_i_q,
	JSSD_FLOAT_speed_RPM,
	JSSD_FLOAT_invTemp1,
	JSSD_FLOAT_invTemp2,
	JSSD_FLOAT_v_dc1,
	JSSD_FLOAT_v_dc2,
	JSSD_FLOAT_v_dc1_ADC,
	JSSD_FLOAT_v_dc2_ADC,
	JSSD_FLOAT_i_a1_ADC,
	JSSD_FLOAT_i_b1_ADC,
	JSSD_FLOAT_i_c1_ADC,
	JSSD_FLOAT_i_a2_ADC,
	JSSD_FLOAT_i_b2_ADC,
	JSSD_FLOAT_i_c2_ADC,
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
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	mech_speed,
	i_d,
	i_q,
	invTemp1,
	invTemp2,
	v_dc,
	RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_LABELS_ZEROVALUE=0,
	RPM,
	A,
	A,
	°C,
	°C,
	V,
	RCV_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_speed_RPM,
	JSSD_FLOAT_i_d,
	JSSD_FLOAT_i_q,
	JSSD_FLOAT_invTemp1,
	JSSD_FLOAT_invTemp2,
	JSSD_FLOAT_v_dc1,
	JSSD_FLOAT_Error_Code,
	SLOWDAT_DISPLAY_ENDMARKER
*/

int JavaScope_initalize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
