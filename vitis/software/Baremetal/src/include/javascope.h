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
	JSO_ua_3ph,
	JSO_ub_3ph,
	JSO_uc_3ph,
	JSO_ua1_6ph,
	JSO_ub1_6ph,
	JSO_uc1_6ph,
	JSO_ua2_6ph,
	JSO_ub2_6ph,
	JSO_uc2_6ph,
	JSO_u_dc1,
	JSO_u_dc2,
	JSO_u_dc3,
	JSO_ia_3ph,
	JSO_ib_3ph,
	JSO_ic_3ph,
	JSO_ia1_6ph,
	JSO_ib1_6ph,
	JSO_ic1_6ph,
	JSO_ia2_6ph,
	JSO_ib2_6ph,
	JSO_ic2_6ph,
	JSO_i_dc1,
	JSO_i_dc2,
	JSO_i_dc3,
	JSO_ud_3ph,
	JSO_uq_3ph,
	JSO_ud_6ph,
	JSO_uq_6ph,
	JSO_ux_6ph,
	JSO_uy_6ph,
	JSO_id_3ph,
	JSO_iq_3ph,
	JSO_id_6ph,
	JSO_iq_6ph,
	JSO_ix_6ph,
	JSO_iy_6ph,
	JSO_D_PWM_A1,
	JSO_D_PWM_B1,
	JSO_D_PWM_C1,
	JSO_D_PWM_A2,
	JSO_D_PWM_B2,
	JSO_D_PWM_C2,
	JSO_D_PWM_alpha,
	JSO_D_PWM_beta,
	JSO_D_PWM_x,
	JSO_D_PWM_y,
	JSO_D_PWM_z1,
	JSO_D_PWM_z2,
	JSO_n_mech_Last,
	JSO_n_mech_Pruef,
	JSO_theta_el_Last_rad,
	JSO_theta_el_Pruef_rad,
	JSO_theta_mech_Last,
	JSO_theta_mech_Pruef,
	JSO_theta_el_Last_deg,
	JSO_theta_mech_Last_deg,
	JSO_theta_el_Pruef_deg,
	JSO_theta_mech_Pruef_deg,
	JSO_Testvar1,
	JSO_Testvar2,
	JSO_Testvar3,
	JSO_Testvar4,
	JSO_Testvar5,
	JSO_Testvar6,
	JSO_Testvar7,
	JSO_Testvar8,
	JSO_Testvar9,
	JSO_Testvar10,
	JSO_u_ref_alpha,
	JSO_u_ref_beta,
	JSO_u_ref_x,
	JSO_u_ref_y,
	JSO_sector24,
	JS_theta_el_rad_ref_JS,
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
	JSSD_FLOAT_ud_3ph,
	JSSD_FLOAT_uq_3ph,
	JSSD_FLOAT_ud_6ph,
	JSSD_FLOAT_uq_6ph,
	JSSD_FLOAT_ux_6ph,
	JSSD_FLOAT_uy_6ph,
	JSSD_FLOAT_id_3ph,
	JSSD_FLOAT_iq_3ph,
	JSSD_FLOAT_id_6ph,
	JSSD_FLOAT_iq_6ph,
	JSSD_FLOAT_ix_6ph,
	JSSD_FLOAT_iy_6ph,
	JSSD_FLOAT_VSI_TEMP_1,
	JSSD_FLOAT_VSI_TEMP_2,
	JSSD_FLOAT_VSI_TEMP_3,
	JSSD_FLOAT_theta_mech_Last,
	JSSD_FLOAT_theta_mech_Pruef,
	JSSD_FLOAT_theta_el_Last,
	JSSD_FLOAT_theta_el_Pruef,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_4_svpwm_Version,
	JSSD_FLOAT_5_svpwm_Version,
	JSSD_FLOAT_dual_3ph_Version,
	JSSD_FLOAT_Scaled,
	JSSD_FLOAT_dual_3ph,
	JSSD_FLOAT_4_svpwm,
	JSSD_FLOAT_5_svpwm,
	JSSD_FLOAT_4_opt,
	JSSD_FLOAT_5_opt,
	JSSD_FLOAT_d_opt,
	JSSD_FLOAT_MorePWM,
	JSSD_FLOAT_V_DC_Volts,
	JSSD_FLOAT_PWM_Settings,
	JSSD_FLOAT_PWM_Versionsnummer,
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
	n_mech_Last_soll,
	id_6ph_Pruef_soll,
	iq_6ph_Pruef_soll,
	ix_6ph_Pruef_soll,
	iy_6ph_Pruef_soll,
	send_field_6,
	id_3ph_Last_soll,
	iq_3ph_Last_soll,
	id_6ph_Pruef_soll,
	iq_6ph_Pruef_soll,
	ix_6ph_Pruef_soll,
	iy_6ph_Pruef_soll,
	n_mech_Pruef_soll,
	ud_6ph_soll,
	uq_6ph_soll,
	ux_6ph_soll,
	uy_6ph_soll,
	PWM_Nummer,
	PWM_Setting,
	C_D1_D2,
	SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_LABELS_ZEROVALUE=0,
	RPM,
	A,
	A,
	A,
	A,
	-,
	A,
	A,
	A,
	A,
	A,
	A,
	RPM,
	V,
	V,
	V,
	V,
	-,
	-,
	-,
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	-,
	id_6ph,
	iq_6ph,
	ix_6ph,
	iy_6ph,
	SecondsSinceSystemStart,
	id_3ph,
	iq_3ph,
	id_6ph,
	iq_6ph,
	ix_6ph,
	iy_6ph,
	ud_3ph,
	uq_3ph,
	ud_6ph,
	uq_6ph,
	ux_6ph,
	uy_6ph,
	ISR_ExecTime_us,
	ISR_Period_us,
	RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_LABELS_ZEROVALUE=0,
	-,
	A,
	A,
	A,
	A,
	s,
	A,
	A,
	A,
	A,
	A,
	A,
	V,
	V,
	V,
	V,
	V,
	V,
	us,
	us,
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	Speed_3ph Current_6ph,
	Speed_6ph Current_3ph,
	Current_Control_On,
	Speed_Control_Off
	Current_Control_Off,
	MorePWM_On,
	MorePWM_Off,
	MyButton8,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_ZEROVALUE,
	JSSD_FLOAT_id_6ph,
	JSSD_FLOAT_iq_6ph,
	JSSD_FLOAT_ix_6ph,
	JSSD_FLOAT_iy_6ph,
	JSSD_FLOAT_SecondsSinceSystemStart,
	JSSD_FLOAT_id_3ph,
	JSSD_FLOAT_iq_3ph,
	JSSD_FLOAT_id_6ph,
	JSSD_FLOAT_iq_6ph,
	JSSD_FLOAT_ix_6ph,
	JSSD_FLOAT_iy_6ph,
	JSSD_FLOAT_ud_3ph,
	JSSD_FLOAT_uq_3ph,
	JSSD_FLOAT_ud_6ph,
	JSSD_FLOAT_uq_6ph,
	JSSD_FLOAT_ux_6ph,
	JSSD_FLOAT_uy_6ph,
	JSSD_FLOAT_ISR_ExecTime_us,
	JSSD_FLOAT_ISR_Period_us,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
