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
	float theta_elec;
	float theta_mech;
	float theta_offset; //in rad/s
	float temperature;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
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
	float mechanicalRotorSpeedRPM_ip;
	float mechanicalRotorSpeedRADpS_ip;
	float electricalRotorSpeedRADpS;
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
	float i_d_ref;
	float i_q_ref;
	float i_x_ref;
	float i_y_ref;
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
	uz_incrementalEncoder_t* encoder_D5;
	uz_mux_axi_t* mux_axi;
	uz_resolverIP_t* resolver_d5_1;
	uz_resolver_pl_interface_t* resolver_pl_interface;
	uz_axi_gpio_t* inv_fault_in;
	uz_PWM_duty_freq_detection_t* tempMeasurement1;
	uz_PWM_duty_freq_detection_t* tempMeasurement2;
	uz_temperaturecard_t* temperature_card_d4;
	uz_CurrentControl_t* foc_current;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

