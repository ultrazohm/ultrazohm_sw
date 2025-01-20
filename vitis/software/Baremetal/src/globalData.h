#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
#include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"
#include "IP_Cores/uz_temperaturecard/uz_temperaturecard.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_signals/uz_signals.h"
#include "uz/uz_subspace_resonant_control/uz_subspace_resonant_control.h"
#include "uz/uz_sysmon_ps/uz_sysmon_ps.h"


enum current_control_select {
		PI_FOC,
		FCS_MPC,
		IMPL_MOD,
		PI_R_FOC,
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
	float temperature;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
	uz_temperaturecard_OneGroup channel_A_data;
	float average_winding_temp;
	float temperature_inv_1;
	float temperature_inv_2;
	struct uz_PWM_duty_freq_detection_outputs_t tempPWMoutputs1;
	struct uz_PWM_duty_freq_detection_outputs_t tempPWMoutputs2;
	bool invFault1;
	bool invFault2;
	float i_max_cur_lim_ip_SI;
	float polepairs;
	struct uz_resolver_pl_interface_outputs_t resolver_pl_interface;
	float theta_elec_rad_ip;
	float theta_mech_rad_ip;
	float mechanicalRotorSpeedRPM;
	float mechanicalRotorSpeedRADpS;
	float electricalRotorSpeedRADpS;
	float i_a1;
	float i_b1;
	float i_c1;
	float i_a1_calib;
	float i_b1_calib;
	float i_c1_calib;
	float i_dc1;
	float i_a2;
	float i_b2;
	float i_c2;
	float i_a2_calib;
	float i_b2_calib;
	float i_c2_calib;
	float i_dc2;
	float v_a1;
	float v_b1;
	float v_c1;
	float v_dc1;
	float v_a2;
	float v_b2;
	float v_c2;
	float v_dc2;
	bool overcurrent_FPGA;
	float overcurrent_FPGA_fl;
	float i_alpha;
	float i_beta;
	float i_X;
	float i_Y;
	float i_z1;
	float i_z2;
	float i_d;
	float i_q;
	float i_x;
	float i_y;
	float i_d_pu;
	float i_q_pu;
	float i_x_pu;
	float i_y_pu;
	float omega_mech_pu;
	float omega_el_pu;
	float v_dc1_pu;
	float v_dc2_pu;
	float i_d_ref;
	float i_q_ref;
	float i_x_ref;
	float i_y_ref;
	float i_d_ref_pu;
	float i_q_ref_pu;
	float i_x_ref_pu;
	float i_y_ref_pu;
	float lambda_dq;
	float lambda_xy;
	float solver_tolerance;
	float max_iter;
	bool HC_off_on;
	float dutycyc[6];
	float iterations;
	float angle_lead_factor_FOC;
	float angle_lead_factor_MPC;
	float psiPM_h_pu[2];
	float phiPM_h[2];
	float Rs;
	float Ld;
	float Lq;
	float Lx;
	float Ly;
	float psi_pm;
	float Rs_over_ZB;
	float Ts_times_ZB_over_Ld;
	float Ts_times_ZB_over_Lq;
	float Ts_times_ZB_over_Lx;
	float Ts_times_ZB_over_Ly;
	float Ld_over_LB;
	float Lq_over_LB;
	float Lx_over_LB;
	float Ly_over_LB;
	float psi_pm_over_psiB;
	float psi_pm_h_pu_over_psiB[2];
	float phi_pm_h_over_psiB[2];
	uz_3ph_dq_t u_dq_ref;
	uz_3ph_dq_t u_xy_ref;
	float v_d;
	float v_q;
	float v_x;
	float v_y;
	float pos_mech;
	float pos_elec;
	float Kp_id;
	float Ki_id;
	float Kp_iq;
	float Ki_iq;
	float Kp_speed;
	float Ki_speed;
	float M_ref;
	float speed_ref_rpm;
	float speed_ref_rpm_filt;
	float theta_elec_incre;
	float mechanicalRotorSpeed_incre;
	float mechanicalRotorSpeed_filtered_incre;
	uint32_t offset_el_incre;
	bool kalman_off_on;
	float kalman_R;
	float kalman_Q1;
	float kalman_Q2;
	float Ts_over_tB;
	float tB_over_Ts;
	float theta_el_pos_FOC;
	float theta_el_neg_FOC;
	float theta_el_pos_MPC;
	float theta_el_neg_MPC;
	float dob_e_est_d;
	float dob_e_est_q;
	float dob_e_est_x;
	float dob_e_est_y;
	float zynq_temp;
	bool dualsvm_clamped;
	float dualsvm_clamped_f;
	float xy_r6_v_d_ref;
	float xy_r6_v_q_ref;
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
	enum current_control_select current_ctrl_select;
	bool a53_ctrl_off_on;
} referenceAndSetValues;

typedef struct{
	uz_PWM_SS_2L_t* pwm_d1_pin_0_to_5;
	uz_PWM_SS_2L_t* pwm_d1_pin_6_to_11;
	uz_PWM_SS_2L_t* pwm_d1_pin_12_to_17;
	uz_PWM_SS_2L_t* pwm_d1_pin_18_to_23;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_0_to_5;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_6_to_11;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_12_to_17;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_18_to_23;
	uz_incrementalEncoder_t* encoder_D3;
	uz_mux_axi_t* mux_axi;
	uz_resolverIP_t* resolver_d5_1;
	uz_resolver_pl_interface_t* resolver_pl_interface;
	uz_axi_gpio_t* inv_fault_in;
	uz_PWM_duty_freq_detection_t* tempMeasurement1;
	uz_PWM_duty_freq_detection_t* tempMeasurement2;
	uz_temperaturecard_t* temperature_card_d4;
	uz_CurrentControl_t* foc_current_dq;
	uz_CurrentControl_t* foc_current_xy;
	uz_subspace_resonant_control* resonant_dq2;
	uz_subspace_resonant_control* resonant_xy2;
	uz_subspace_resonant_control* resonant_xy6;
	uz_IIR_Filter_t* speed_ref_filt;
	uz_SetPoint_t* setpoint;
	uz_SpeedControl_t* speed_control;
	uz_IIR_Filter_t* invTemp1_filter;
	uz_IIR_Filter_t* invTemp2_filter;
	uz_sysmon_ps_t* sysmon;
	uz_PI_Controller* ph_curr_ctrl;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

