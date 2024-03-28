#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_signals/uz_signals.h"
#include "uz/uz_movingAverageFilter/uz_movingAverageFilter.h"

enum current_control_select {
		PI_FOC,
		FCS_MPC,
};

// union allows to access the values as array and individual variables
// see also this link for more information: https://hackaday.com/2018/03/02/unionize-your-variables-an-introduction-to-advanced-data-types-in-c/
typedef union _ConversionFactors_ {
	struct{
		float ADC_A1;
		float ADC_A2;
		float ADC_A3;
		float ADC_A4;
		float ADC_B5;
		float ADC_B6;
		float ADC_B7;
		float ADC_B8;
		};
	float ADC_array[8];
} ConversionFactors;

typedef union _Measurements_ {
	struct{
		float ADC_A1;
		float ADC_A2;
		float ADC_A3;
		float ADC_A4;
		float ADC_B5;
		float ADC_B6;
		float ADC_B7;
		float ADC_B8;
		};
	float ADC_array[8];
} Measurements;

typedef struct _ADCcard_ {
	ConversionFactors 	cf;
	Measurements		me;
} ADCcard;

typedef struct _AnalogAdapters_ {
	ADCcard A1;
	ADCcard A2;
	ADCcard A3;
} AnalogAdapters;

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d5_1;
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs_d5_2;
	struct uz_inverter_adapter_outputs_t inverter_d1_status;
	struct uz_inverter_adapter_outputs_t inverter_d2_status;
	float mean_temp_inv_d1;
	float mean_temp_inv_d2;
	float i_a_d1;
	float i_b_d1;
	float i_c_d1;
	float i_dc_d1;
	float v_a_d1;
	float v_b_d1;
	float v_c_d1;
	float v_dc_d1;
	float i_a_d2;
	float i_b_d2;
	float i_c_d2;
	float i_dc_d2;
	float v_a_d2;
	float v_b_d2;
	float v_c_d2;
	float v_dc_d2;
	float i_d_0;
	float i_q_0;
	float i_d_1;
	float i_q_1;
	float v_d_0;
	float v_d_0_filt;
	float v_q_0;
	float v_d_1;
	float v_q_1;
	float polepairs_left;
	float polepairs_right;
	float omega_mech_d5_1;
	float omega_mech_d5_2;
	float lambda_d;
	float lambda_q;
	float lambda_u_left;
	float lambda_u_e5_left;
	float lambda_u_right;
	float lambda_u_e5_right;
	float i_max_mpc;
	float speed_rpm_d5_1;
	float speed_rpm_d5_2;
	bool f_sw_measure_flag;
	float f_f_sw_measure_flag;
	float pause_time_sec;
	float pause_timer_sec;
	bool measure_flag;
	float f_measure_flag;
	bool start_trade_off_measurement;
	float f_start_trade_off_measurement;
	float f_sw_avg_Hz_0;
	float f_sw_avg_Hz_1;
	float i_d_ip;
	float i_q_ip;
	float i_a_pu;
	float i_b_pu;
	float i_c_pu;
	float vd_pu;
	float vq_pu;
	float id_delay_pu;
	float iq_delay_pu;
	bool svm_clamping_left;
	float f_svm_clamping_left;
	bool trig_flag;
	float f_trig_flag;
	float d_pred_error;
	float q_pred_error;
	float d_pred_error_sq;
	float q_pred_error_sq;
	float d_pred_error_sq_filt;
	float q_pred_error_sq_filt;
} actualValues;

typedef struct _referenceAndSetValues_ {
	float halfBridge1DutyCycle;
	float halfBridge2DutyCycle;
	float halfBridge3DutyCycle;
	float halfBridge4DutyCycle;
	float halfBridge5DutyCycle;
	float halfBridge6DutyCycle;
	float halfBridge7DutyCycle;
	float halfBridge8DutyCycle;
	float halfBridge9DutyCycle;
	float halfBridge10DutyCycle;
	float halfBridge11DutyCycle;
	float halfBridge12DutyCycle;
	float M_ref_right;
	float n_ref_right;
	float n_ref_right_filt;
	float M_ref_left;
	float n_ref_left;
	float n_ref_left_filt;
	uz_3ph_dq_t i_dq_ref_0;
	uz_3ph_dq_t i_dq_ref_1;
	enum current_control_select current_ctrl_select;
	bool req_measure_flag;
	float f_req_measure_flag;
	uint32_t cnt_lambda_u;
	float f_cnt_lambda_u;
	float lambda_u_now;
	float lambda_u_step;
	uint32_t cnt_lambda_u_end;
	float lambda_u_start;
	float lambda_u_stop;
	float f_cnt_lambda_u_end;
	float Ts_minus_Td_over_Ts;
	float Td_over_Ts;
	bool deadtime_comp_onoff;
	float lambda_u_LUT[42];
	float Kp_spd_right;
	float Ki_spd_right;
	float Kp_spd_left;
	float Ki_spd_left;
	float Kp_cur_d_left;
	float Ki_cur_d_left;
	float Kp_cur_q_left;
	float Ki_cur_q_left;
	float Kp_cur_d_right;
	float Ki_cur_d_right;
	float Kp_cur_q_right;
	float Ki_cur_q_right;
	float iq_ref_step;
	uz_3ph_abc_t i_abc_ref_left;
	float i_a_ref_last_and_present[2];
	bool i_a_ref_zero_crossing;
	float f_i_a_ref_zero_crossing;
	bool trigger_iq_step_armed;
	float Ts_left_changed;
} referenceAndSetValues;

typedef struct{
	uz_PWM_SS_2L_t* pwm_0;
	uz_PWM_SS_2L_t* pwm_1;
	uz_PWM_SS_2L_t* pwm_2;
	uz_PWM_SS_2L_t* pwm_3;
	uz_interlockDeadtime2L_handle deadtime_interlock_PWM_0;
	uz_interlockDeadtime2L_handle deadtime_interlock_PWM_1;
	uz_interlockDeadtime2L_handle deadtime_interlock_PWM_2;
	uz_interlockDeadtime2L_handle deadtime_interlock_PWM_3;
	uz_mux_axi_t* mux_axi_0;
	uz_mux_axi_t* mux_axi_1;
	uz_resolverIP_t* resolver_d5_1;
	uz_resolverIP_t* resolver_d5_2;
	uz_resolver_pl_interface_t* resolver_pl_interface_d5_1;
	uz_resolver_pl_interface_t* resolver_pl_interface_d5_2;
	uz_inverter_adapter_t* uz_d_inverter_d1;
	uz_inverter_adapter_t* uz_d_inverter_d2;
	uz_CurrentControl_t* current_ctrl_right;
	uz_CurrentControl_t* current_ctrl_left;
	uz_SpeedControl_t* speed_ctrl_right;
	uz_SpeedControl_t* speed_ctrl_left;
	uz_SetPoint_t* setpoint_ctrl_right;
	uz_SetPoint_t* setpoint_ctrl_left;
	uz_IIR_Filter_t* iir_filter_ref_speed_left;
	uz_IIR_Filter_t* iir_filter_ref_speed_right;
	uz_IIR_Filter_t* iir_filter_pred_error_d;
	uz_IIR_Filter_t* iir_filter_pred_error_q;
	uz_movingAverageFilter_t* movAvgFilt_d;
	uz_movingAverageFilter_t* movAvgFilt_q;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

