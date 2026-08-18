#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "uz/uz_wavegen/uz_wavegen.h"
// Project Wizard adapter slot headers
#include "include/a1_adapter_init.h"
#include "include/a2_adapter_init.h"
#include "include/a3_adapter_init.h"
#include "include/d1_adapter_init.h"
#include "include/d2_adapter_init.h"
#include "include/d3_adapter_init.h"
#include "include/d4_adapter_init.h"
#include "include/d5_adapter_init.h"

typedef struct _actualValues_ {
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t  heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float d3_input_loopback_uint32;
	/* Project Wizard BEGIN: actualValues */
	float adc_ltc2311_a1_ch0;
	float adc_ltc2311_a1_ch1;
	float adc_ltc2311_a1_ch2;
	float adc_ltc2311_a1_ch3;
	float adc_ltc2311_a1_ch4;
	float adc_ltc2311_a1_ch5;
	float adc_ltc2311_a1_ch6;
	float adc_ltc2311_a1_ch7;
	float dac8831_a2_ch0;
	float dac8831_a2_ch1;
	float dac8831_a2_ch2;
	float dac8831_a2_ch3;
	float dac8831_a2_ch4;
	float dac8831_a2_ch5;
	float dac8831_a2_ch6;
	float dac8831_a2_ch7;
	float adc_max11331_a3_ch0;
	float adc_max11331_a3_ch1;
	float adc_max11331_a3_ch2;
	float adc_max11331_a3_ch3;
	float adc_max11331_a3_ch4;
	float adc_max11331_a3_ch5;
	float adc_max11331_a3_ch6;
	float adc_max11331_a3_ch7;
	float adc_max11331_a3_ch8;
	float adc_max11331_a3_ch9;
	float adc_max11331_a3_ch10;
	float adc_max11331_a3_ch11;
	float adc_max11331_a3_ch12;
	float adc_max11331_a3_ch13;
	float adc_max11331_a3_ch14;
	float adc_max11331_a3_ch15;
	float adc_max11331_a3_ch16;
	float adc_max11331_a3_ch17;
	float adc_max11331_a3_ch18;
	float adc_max11331_a3_ch19;
	float adc_max11331_a3_ch20;
	float adc_max11331_a3_ch21;
	float adc_max11331_a3_ch22;
	float adc_max11331_a3_ch23;
	uint32_t io_card_d1_state;
	struct uz_inverter_adapter_outputs_t inverter_adapter_d2;
	uz_temperaturecard_OneGroup temperature_card_d3_channel_A;
	uz_temperaturecard_OneGroup temperature_card_d3_channel_B;
	uz_temperaturecard_OneGroup temperature_card_d3_channel_C;
	int32_t resolver_pl_interface_d4_1_revolution_counter;
	float resolver_pl_interface_d4_1_position_mech_2pi;
	float resolver_pl_interface_d4_1_position_el_2pi;
	float resolver_pl_interface_d4_1_omega_mech_rad_s;
	float resolver_pl_interface_d4_1_n_mech_rpm;
	float resolver_pl_interface_d4_1_omega_el_rad_s;
	float resolver_ip_d4_2_position_mech_2pi;
	float resolver_ip_d4_2_position_el_2pi;
	float resolver_ip_d4_2_omega_mech_rad_s;
	float resolver_ip_d4_2_n_mech_rpm;
	float resolver_ip_d4_2_omega_el_rad_s;
	float resolver_ip_d4_3_position_mech_2pi;
	float resolver_ip_d4_3_position_el_2pi;
	float resolver_ip_d4_3_omega_mech_rad_s;
	float resolver_ip_d4_3_n_mech_rpm;
	float resolver_ip_d4_3_omega_el_rad_s;
	uint32_t endat_encoder_d5_1_position_raw_single_turn;
	uint32_t endat_encoder_d5_1_position_raw_multi_turn;
	uint32_t endat_encoder_d5_1_position_multi_turn;
	float endat_encoder_d5_1_position_mech_si_single_turn;
	float endat_encoder_d5_1_position_el_si_single_turn;
	float endat_encoder_d5_1_speed_mech_si;
	float endat_encoder_d5_1_speed_el_si;
	float endat_encoder_d5_1_speed_mech_rpm;
/* Project Wizard END: actualValues */
} actualValues;

typedef struct _referenceAndSetValues_ {
/* Project Wizard BEGIN: referenceAndSetValues */
	float pwm_2L_0_halfBridgeDutyCycle_1;
	float pwm_2L_0_halfBridgeDutyCycle_2;
	float pwm_2L_0_halfBridgeDutyCycle_3;
	float pwm_2L_1_halfBridgeDutyCycle_1;
	float pwm_2L_1_halfBridgeDutyCycle_2;
	float pwm_2L_1_halfBridgeDutyCycle_3;
	float pwm_2L_2_halfBridgeDutyCycle_1;
	float pwm_2L_2_halfBridgeDutyCycle_2;
	float pwm_2L_2_halfBridgeDutyCycle_3;
	float pwm_2L_3_halfBridgeDutyCycle_1;
	float pwm_2L_3_halfBridgeDutyCycle_2;
	float pwm_2L_3_halfBridgeDutyCycle_3;
	float pwm_3L_0_halfBridgeDutyCycle_1;
	float pwm_3L_0_halfBridgeDutyCycle_2;
	float pwm_3L_0_halfBridgeDutyCycle_3;
/* Project Wizard END: referenceAndSetValues */
} referenceAndSetValues;

typedef struct{
	uz_mux_axi_t* mux_axi;
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_0;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_2;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_2;
	uz_PWM_SS_2L_t* project_wizard_pwm_2l_3;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_3;
	uz_wavegen_three_phase* three_phase_sine;
	uz_adcLtc2311_t* adc_ltc2311_a1;
	uz_dac_interface_t* dac8831_a2;
	uz_wavegen_sine_t* dac8831_a2_ch0_sine;
	uz_wavegen_sawtooth_t* dac8831_a2_ch1_sawtooth;
	uz_wavegen_triangle_t* dac8831_a2_ch2_triangle;
	uz_wavegen_square_t* dac8831_a2_ch3_square;
	uz_wavegen_pulse_t* dac8831_a2_ch4_pulse;
	uz_wavegen_sine_t* dac8831_a2_ch5_sine;
	uz_wavegen_sawtooth_t* dac8831_a2_ch6_sawtooth;
	uz_wavegen_triangle_t* dac8831_a2_ch7_triangle;
	uz_adcMax11331_t* adc_max11331_a3;
	uz_axi_gpio_t* axi_gpio_d1;
	uz_inverter_adapter_t* inverter_adapter_d2;
	uz_temperaturecard_t* temperature_card_d3;
	uz_resolverIP_t* resolver_ip_d4_1;
	uz_resolver_pl_interface_t* resolver_pl_interface_d4_1;
	uz_resolverIP_t* resolver_ip_d4_2;
	uz_resolverIP_t* resolver_ip_d4_3;
	uz_endat_interface_t* endat_encoder_d5_1;
/* Project Wizard END: objects */
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
} DS_Data;

#endif

