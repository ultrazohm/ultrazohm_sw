#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "IP_Cores/uz_incrementalEncoder/uz_incrementalEncoder.h"
#include "IP_Cores/uz_PWM_duty_freq_detection/uz_PWM_duty_freq_detection.h"
#include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"
#include "IP_Cores/uz_inverter_adapter/uz_inverter_adapter.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_signals/uz_signals.h"
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
	float VA_polepairs;
	float IM_polepairs;
	float IM_ia; 		// im
	float IM_ib; 		// im
	float IM_ic; 		// im
	float VA_ia; 		// va
	float VA_ib; 		// va
	float VA_ic; 		// va
	float VA_vd;
	float VA_vq;
	float VA_ua;
	float VA_ub;
	float VA_uc;
	float VA_idc;
	float IM_vdc; 		// DC-Link im
	float VA_vdc;// DC-Link va
	float IM_mechanicalRotorSpeed; 		// in rpm
	float IM_mechanicalRotorSpeed_filtered; // in rpm
	float IM_mechanicalPosition; 		// in m
	float VA_mechanicalRotorSpeed; 		// in rpm
	float VA_mechanicalRotorSpeed_filtered; // in rpm
	float VA_mechanicalPosition; 		// in m
	float IM_I_d;
	float IM_I_q;
	float VA_I_d;
	float VA_I_q;
	float IM_theta_elec;
	float IM_theta_mech;
	float IM_omega_mech;
	float IM_omega_elec;
	float IM_theta_offset;
	float IM_theta_elec_advanced;
	float VA_theta_elec;
	float VA_theta_mech;
	float VA_omega_mech;
	float VA_omega_elec;
	float VA_theta_offset;
	float VA_theta_elec_advanced;
	float snd_fld[21];
	float pwm_freq;
	float duty_cycle;
	float temp;
	float OCP_INVERTER;
	float FAULT_INVERTER;
	uint32_t slowDataCounter;
	struct uz_inverter_adapter_outputs_t inverter_outputs_d2;
	float mean_temp_inv_d2;
	float IM_vd;   // d-axis voltage reference (FOC output)
	float IM_vq;   // q-axis voltage reference (FOC output)
} actualValues;

typedef struct _referenceAndSetValues_ {
	float halfBridge1DutyCycle;
	float halfBridge2DutyCycle;
	float halfBridge3DutyCycle;
	float halfBridge4DutyCycle;
	float halfBridge5DutyCycle;
	float halfBridge6DutyCycle;
	float M_ref_VA;
	float n_ref_VA;
	float n_ref_filt_VA;
	uz_3ph_dq_t i_dq_ref_VA;
} referenceAndSetValues;

typedef struct {
	bool select_automatic_idiq;
	bool setpoints_from_javascope;
	float start_marker;
	uz_3ph_dq_t dut_reference_currents_in_A;
	uint32_t setpoint_index;
} rr_profile_data_t;

typedef struct{
	uz_PWM_SS_2L_t* pwm_d1_pin_0_to_5;
	uz_PWM_SS_2L_t* pwm_d1_pin_6_to_11;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_0_to_5;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_6_to_11;
	uz_incrementalEncoder_t* encoder_IM;
	uz_incrementalEncoder_t* encoder_VA;
	uz_mux_axi_t* mux_axi;
	uz_PWM_duty_freq_detection_t* PWM_Detect_instance;
	uz_axi_gpio_t* d1_gpi_ch15_17;
	uz_inverter_adapter_t* inverter_d2;
	uz_CurrentControl_t* current_ctrl_VA;
	uz_SpeedControl_t* speed_ctrl_VA;
	uz_SetPoint_t* setpoint_ctrl_VA;
	uz_IIR_Filter_t* iir_filter_ref_speed_VA;
	uz_IIR_Filter_t* iir_filter_speed_IM;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
	rr_profile_data_t rr_profile;
} DS_Data;

#endif
