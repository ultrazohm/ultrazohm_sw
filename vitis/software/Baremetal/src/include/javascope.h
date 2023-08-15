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
	JSO_ia1,
	JSO_ib1,
	JSO_ic1,
	JSO_ia2,
	JSO_ib2,
	JSO_ic2,
	JSO_ia3,
	JSO_ib3,
	JSO_ic3,
	JSO_ua1,
	JSO_ub1,
	JSO_uc1,
	JSO_ua2,
	JSO_ub2,
	JSO_uc2,
	JSO_ua3,
	JSO_ub3,
	JSO_uc3,
	JSO_id,
	JSO_iq,
	JSO_iX1,
	JSO_iY1,
	JSO_iX2,
	JSO_iY2,
	JSO_iX3,
	JSO_iY3,
	JSO_iZero,
	JSO_ud,
	JSO_uq,
	JSO_uX1,
	JSO_uY1,
	JSO_uX2,
	JSO_uY2,
	JSO_uX3,
	JSO_uY3,
	JSO_uZero,
	JSO_Speed_rpm,
	JSO_Theta_el,
	JSO_Theta_mech,
	JSO_ISR_ExecTime_us,
	JSO_ISR_Period_us,
	JSO_ix1,
	JSO_iy1,
	JSO_ix2,
	JSO_iy2,
	JSO_ix3,
	JSO_iy3,
	JSO_lifecheck,
	JSO_debug_x1,
	JSO_debug_y1,
	JSO_debug_x2,
	JSO_debug_y2,
	JSO_debug_x3,
	JSO_debug_y3,
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
	JSSD_FLOAT_polePairs,
	JSSD_FLOAT_activeState,
	JSSD_FLOAT_u_d,
	JSSD_FLOAT_u_q,
	JSSD_FLOAT_i_d,
	JSSD_FLOAT_i_q,
	JSSD_FLOAT_speed,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_temperature_inv1,
	JSSD_FLOAT_temperature_inv2,
	JSSD_FLOAT_temperature_inv3,
	JSSD_FLOAT_u_dc_inv1,
	JSSD_FLOAT_u_dc_inv2,
	JSSD_FLOAT_u_dc_inv3,
	JSSD_FLOAT_i_dc_inv2,
	JSSD_FLOAT_i_dc_inv3,
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
	set_id,
	set_iq,
	none,
	none,
	none,
	send_field_6,
	SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_LABELS_ZEROVALUE=0,
	A,
	A,
	,
	,
	,
	,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	receive_field_1,
	receive_field_2,
	receive_field_3,
	receive_field_4,
	receive_field_5,
	receive_field_6,
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
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

MYBUTTONS_LABELS_ZEROVALUE=0,
En_XY1,
Dis_XY1,
En_XY2,
Dis_XY2,
En_XY3,
Dis_XY3,
MyButton7,
MyButton8,
MYBUTTONS_LABELS_ENDMARKER

// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_SecondsSinceSystemStart,
	JSSD_FLOAT_ISR_ExecTime_us,
	JSSD_FLOAT_ISR_Period_us,
	JSSD_FLOAT_polePairs,
	JSSD_FLOAT_Milliseconds,
	JSSD_FLOAT_Ld,
	JSSD_FLOAT_Error_Code,
	SLOWDAT_DISPLAY_ENDMARKER
*/

int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
