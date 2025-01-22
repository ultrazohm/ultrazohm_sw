#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_resolverIP/uz_resolverIP.h"
#include "IP_Cores/uz_resolver_pl_interface/uz_resolver_pl_interface.h"
#include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
#include "uz/uz_FOC/uz_FOC.h"
#include "IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"

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
	float i_a1;
	float i_b1;
	float i_c1;
	float i_dc1;
	float i_a2;
	float i_b2;
	float i_c2;
	float i_dc2;
	float v_a1;
	float v_b1;
	float v_c1;
	float v_dc1;
	float v_a2;
	float v_b2;
	float v_c2;
	float v_dc2;
	float i_alpha;
	float i_beta;
	float i_x;
	float i_y;
	float i_z1;
	float i_z2;
	float i_d;
	float i_q;
	float mechanicalRotorSpeedRPM;
	float electricalRotorSpeedRPM;
	float mechanicalRotorSpeedRADpS;
	float electricalRotorSpeedRADpS;
	float v_d;
	float v_q;
	float theta_elec_rad;
	float theta_mech_rad;
	float theta_mech_offset_rad;
	float theta_mech_calculated;
	float theta_offset_rad;
	float temperature_inv_1;
	float temperature_inv_2;
	struct uz_PWM_duty_freq_detection_outputs_t tempPWMoutputs1;
	struct uz_PWM_duty_freq_detection_outputs_t tempPWMoutputs2;
	float polepairs;
	uint32_t  heartbeatframe_content;
	struct uz_resolverIP_position_velocity_t posVel_mech;
	struct uz_resolverIP_position_velocity_t posVel_el;
	float i_d_ref;
	float i_q_ref;
	float i_d_ref_pu;
	float i_q_ref_pu;
	float i_q_ref_PI_out_pu;
	struct uz_resolver_pl_interface_outputs_t pl_interface;
	float theta_elec_rad_ip;
	float theta_mech_rad_ip;
	float mechanicalRotorSpeedRPM_ip;
	float mechanicalRotorSpeedRADpS_ip;
	float i_a1_pu;
	float i_b1_pu;
	float i_c1_pu;
	float i_a2_pu;
	float i_b2_pu;
	float i_c2_pu;
	float i_alpha_ip;
	float i_beta_ip;
	float i_X_ip;
	float i_Y_ip;
	float i_0p_ip;
	float i_0n_ip;
	float i_d_ip;
	float i_q_ip;
	float v_dc1_ip;
	float v_dc2_ip;
	float i_d_delay;
	float i_q_delay;
	float i_x_delay;
	float i_y_delay;
	float f_sw_avg_Hz;
	float i_x_ref;
	float i_y_ref;
	float lambda_d;
	float lambda_q;
	float lambda_x;
	float lambda_y;
	float lambda_u;
	float vd_pu;
	float vq_pu;
	float vx_pu;
	float vy_pu;
	uint32_t ref_idx;
	bool debug_ip_off;
	float i_max;
	float i_max_fpga;
	float torque;
	bool f_sw_measure_flag;
	float f_f_sw_measure_flag;
	bool measure_flag;
	float f_measure_flag;
	bool start_trade_off_measurement;
	float f_start_trade_off_measurement;
	float pause_timer_sec;
	float pause_time_sec;
	bool overcurrent_FPGA;
	float overcurrent_FPGA_fl;
	bool lmg_trigger_status;
	float theta_el_incre_ip;
	float theta_elec_incre;
	float mechanicalRotorSpeed_incre;
	uint32_t offset_el_incre;
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
	bool req_measure_flag;
	float f_req_measure_flag;
	float lambda_u_start;
	float lambda_u_stop;
	float lambda_u_step;
	float lambda_u_now;
	uint32_t cnt_lambda_u;
	float f_cnt_lambda_u;
	uint32_t cnt_lambda_u_end;
	float f_cnt_lambda_u_end;
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
	uz_mux_axi_t* mux_axi;
	uz_resolverIP_t* resolver_d5_1;
	uz_resolver_pl_interface_t* pl_interface;
	uz_PWM_duty_freq_detection_t* tempMeasurement1;
	uz_PWM_duty_freq_detection_t* tempMeasurement2;
	uz_adcLtc2311_t* ADC_A1;
	uz_adcLtc2311_t* ADC_A2;
	uz_FOC* foc_current;
	uz_PI_Controller* MPC_setpoint_PI;
	uz_axi_gpio_t* lmg_trigger;
	uz_incrementalEncoder_t* encoder_D3;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

