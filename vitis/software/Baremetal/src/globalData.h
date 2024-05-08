#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "xparameters.h"
#include "IP_Cores/uz_pmsm_model_6ph_dq/uz_pmsm_model6ph_dq.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_nn/uz_nn.h"
#include "uz/uz_matrix/uz_matrix.h"

// additional inclusions, see Michael mpc reference code
#include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
#include "IP_Cores/uz_adcLtc2311/uz_adcLtc2311.h"
#include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"



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

	// 6p currents and voltages, DC and AC
	float i_a1; 		// Machine side current in A
	float i_b1; 		// Machine side current in A
	float i_c1; 		// Machine side current in A
	float i_a2; 		// Machine side current in A
	float i_b2; 		// Machine side current in A
	float i_c2; 		// Machine side current in A
	float i_dc1;
	float i_dc2;
	float v_a1; 		// Machine side voltage in V
	float v_b1; 		// Machine side voltage in V
	float v_c1; 		// Machine side voltage in V
	float v_a2; 		// Machine side voltage in V
	float v_b2; 		// Machine side voltage in V
	float v_c2; 		// Machine side voltage in V
	float v_dc1;
	float v_dc2;


	float U_ZK; 		// DC-Link voltage in V
	float U_ZK2; 	// DC-Link voltage 2 in V
	float Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	float Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)


	float mechanicalRotorSpeed; 		// in rpm
	float electricalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_filtered; // in rpm
	float omega_mech;                    // in rad/s
	float omega_elec;                     // in rad/s

	float mechanicalRotorSpeedRADpS;    // New
	float electricalRotorSpeedRADpS;     // New
	float mechanicalRotorSpeedRPM; 		// New
	float electricalRotorSpeedRPM; 		// New



	float omega_ip; 		// New
	float theta_ip; 		// New


	float mechanicalPosition; 		// in m
	float theta_elec;			// Add _rad for MC
	float theta_mech;			// Add _rad for MC
	float theta_offset; //in rad/s

	float theta_mech_offset_rad;			// New
	float theta_mech_calculated;			// New
	float theta_elec_rad;			// New
	float theta_mech_rad;			// New
	float theta_offset_rad;			// New


	float mechanicalTorque; 			// in Nm
	float mechanicalTorqueSensitive; // in Nm
	float mechanicalTorqueObserved; 	// in Nm for observing the load torque


	float i_alpha; // New
	float i_beta;  // New
	float I_X; //
	float I_Y; //
	float i_x; // New
	float i_y; // New
	float i_z1; // New
	float i_z2; // New
	float I_d;
	float I_q;
	float U_d;	//
	float U_q;  //
	float U_X;
	float U_Y;

	float v_d;	//New
	float v_q;  //New
	float i_d;
	float i_q;


	float temperature;
	uint32_t  heartbeatframe_content;


	float temp_VSI_1;
	float temp_VSI_2;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d1;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2;


	// All new variables
	    float polepairs;
		float i_d_ref;
		float i_q_ref;
		float i_d_ref_pu;
		float i_q_ref_pu;
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

	// All new variables
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
	uz_pmsm_model6ph_dq_t* CIL_pmsm;
	uz_CurrentControl_t* CC_dq_instance;
	uz_CurrentControl_t* CC_xy_instance;
	uz_matrix_t* matrix_input_15n;
	uz_nn_t* nn_layer_15n;
	uz_matrix_t* matrix_input_17n;
	uz_nn_t* nn_layer_17n;
	uz_inverter_adapter_t* inverter_d1;
	uz_inverter_adapter_t* inverter_d2;


	// All new variables
	uz_PWM_duty_freq_detection_t* tempMeasurement1;
	uz_PWM_duty_freq_detection_t* tempMeasurement2;
	uz_adcLtc2311_t* ADC_A1;
	uz_adcLtc2311_t* ADC_A2;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

