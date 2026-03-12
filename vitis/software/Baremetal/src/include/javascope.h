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
	JSO_theta_mech,
	JSO_pwm_freq,
	JSO_duty_cycle,
	JSO_temp,
	JSO_OCP,
	JSO_FAULT,
	JSO_pwm_frequency_hz,
	JSO_isr_samplerate_s,
	JSO_IM_ia,
	JSO_IM_ib,
	JSO_IM_ic,
	JSO_IM_vdc,
	JSO_IM_mechanicalRotorSpeed,
	JSO_IM_mechanicalRotorSpeed_filtered,
	JSO_IM_mechanicalPosition,
	JSO_IM_I_d,
	JSO_IM_I_q,
	JSO_IM_theta_elec,
	JSO_IM_theta_mech,
	JSO_IM_theta_offset,
	JSO_IM_theta_elec_advanced,
	JSO_VA_polepairs,
	JSO_VA_ia,
	JSO_VA_ib,
	JSO_VA_ic,
	JSO_VA_vd,
	JSO_VA_vq,
	JSO_VA_vdc,
	JSO_VA_mechanicalRotorSpeed,
	JSO_VA_mechanicalRotorSpeed_filtered,
	JSO_VA_mechanicalPosition,
	JSO_VA_omega_mech,
	JSO_VA_I_d,
	JSO_VA_I_q,
	JSO_VA_theta_elec,
	JSO_VA_theta_mech,
	JSO_VA_theta_offset,
	JSO_VA_theta_elec_advanced,
	JSO_VA_i_d_ref,
	JSO_VA_i_q_ref,
	JSO_DUT1,
	JSO_DUT2,
	JSO_DUT3,
	JSO_UF_voltage_magnitude_V,
	JSO_IM_psi_r_mag,         
	JSO_IM_omega_s_rad_s,     
	JSO_IM_kf_innov_alpha,    
	JSO_IM_kf_innov_beta,     
	JSO_IM_id_raw,            
	JSO_IM_iq_raw,           
	JSO_IM_ud_pi,            
	JSO_IM_uq_pi,            
	JSO_IM_ud_decoup,        
	JSO_IM_uq_decoup,      
	JSO_IM_ud_res,         
	JSO_IM_uq_res,         
	JSO_IM_omega_slip,     
	JSO_IM_speed_ref,      
	JSO_IM_speed,			
	JSO_IM_vd,              
	JSO_IM_vq,              
	JSO_IM_id_ref,          
	JSO_IM_iq_ref,          
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
	JSSD_FLOAT_error_vdc_im,
	JSSD_FLOAT_error_vdc_va,
	JSSD_FLOAT_error_max_current_va,
	JSSD_FLOAT_u_d,
	JSSD_FLOAT_u_q,
	JSSD_FLOAT_i_d,
	JSSD_FLOAT_i_q,
	JSSD_FLOAT_speed,
	JSSD_FLOAT_torque,
	JSSD_FLOAT_encoderOffset,
	JSSD_FLOAT_u_d_ref,
	JSSD_FLOAT_u_q_ref,
	JSSD_FLOAT_IM_vdc,
	JSSD_FLOAT_VA_vdc,
	JSSD_FLOAT_VA_i_d,
	JSSD_FLOAT_VA_i_q,
	JSSD_FLOAT_VA_speed,
	JSSD_FLOAT_VA_theta_elec,
	JSSD_FLOAT_IM_ia,
	JSSD_FLOAT_IM_ib,
	JSSD_FLOAT_IM_ic,
	JSSD_FLOAT_VA_ia,
	JSSD_FLOAT_VA_ib,
	JSSD_FLOAT_VA_ic,
	JSSD_FLOAT_kf_q_i,
	JSSD_FLOAT_kf_q_psi,
	JSSD_FLOAT_kf_r_i,
	JSSD_FLOAT_vf_frequency_setpoint_Hz,
	JSSD_FLOAT_vf_ratio_V_per_Hz,
	JSSD_FLOAT_vf_boost_voltage_V,
	JSSD_FLOAT_vf_max_frequency_Hz,
	JSSD_FLOAT_vf_max_voltage_V,
	JSSD_FLOAT_vf_applied_voltage_magnitude_V,
	JSSD_FLOAT_psi_r_mag,
	JSSD_FLOAT_IM_id,
	JSSD_FLOAT_IM_iq,
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
	IM_VF_Freq_Setpoint,
	VA_Id_Ref,
	VA_Iq_Ref,
	VA_Speed_Ref,
	IM_Id_Ref,
	IM_Iq_Ref,
	KF_Q_psi,
	KF_R_i,
	KF_Q_i,
	IM_Speed_Ref,
	reserved_11,
	reserved_12,
	reserved_13,
	reserved_14,
	reserved_15,
	reserved_16,
	reserved_17,
	reserved_18,
	reserved_19,
	reserved_20,
	SND_FLD_ENDMARKER


// Physical unit label (printed text) for the send_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	SND_LABELS_ZEROVALUE=0,
	Hz,
	A,
	A,
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
	SND_LABELS_ENDMARKER


// Description (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_FLD_ZEROVALUE=0,
	IM_vdc,
	VA_vdc,
	VA_i_d,
	VA_i_q,
	VA_speed,
	VA_theta_elec,
	IM_ia,
	IM_ib,
	IM_ic,
	VA_ia,
	VA_ib,
	VA_ic,
	reserved_13,
	reserved_14,
	reserved_15,
	reserved_16,
	reserved_17,
	reserved_18,
	reserved_19,
	reserved_20,
	RCV_FLD_ENDMARKER


// Physical unit label (printed text) for the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.

	RCV_LABELS_ZEROVALUE=0,
	V,
	V,
	A,
	A,
	rpm,
	rad,
	A,
	A,
	A,
	A,
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
	RCV_LABELS_ENDMARKER

// Physical unit label (printed text) for the MyButtons top to bottom
// Do not change the first (zero) and last (end) entries.

	MYBUTTONS_LABELS_ZEROVALUE=0,
	VA_Controller_on,
	IM_Controller_on,
	VA_Speedcontrol_on,
	Toggle_FOC,
	Toggle_IM_Speed_Ctrl,
	Toggle_KalmanFilter,
	Reserved_Button7,
	Toggle_Resonant6th,
	MYBUTTONS_LABELS_ENDMARKER


// Slow Data values that are displayed in the receive_fields top to bottom
// Do not change the first (zero) and last (end) entries.
// Make sure that the signal names below are also present in the JS_SlowData enum!
//Set the line to JSSD_FLOAT_ZEROVALUE if no value should be transmitted

	SLOWDAT_DISPLAY_ZEROVALUE=0,
	JSSD_FLOAT_error_vdc_im,
	JSSD_FLOAT_error_vdc_va,
	JSSD_FLOAT_error_max_current_va,
	JSSD_FLOAT_IM_vdc,
	JSSD_FLOAT_VA_vdc,
	JSSD_FLOAT_VA_i_d,
	JSSD_FLOAT_VA_i_q,
	JSSD_FLOAT_VA_speed,
	JSSD_FLOAT_VA_theta_elec,
	JSSD_FLOAT_IM_ia,
	JSSD_FLOAT_IM_ib,
	JSSD_FLOAT_IM_ic,
	JSSD_FLOAT_VA_ia,
	JSSD_FLOAT_VA_ib,
	JSSD_FLOAT_VA_ic,
	JSSD_FLOAT_SecondsSinceSystemStart,
	JSSD_FLOAT_ISR_ExecTime_us,
	JSSD_FLOAT_ISR_Period_us,
	JSSD_FLOAT_Milliseconds,
	JSSD_FLOAT_ZEROVALUE,
	SLOWDAT_DISPLAY_ENDMARKER
*/


int JavaScope_initialize(DS_Data* data);
void JavaScope_update(DS_Data* data);

#endif /* INCLUDE_JAVASCOPE_H_ */
