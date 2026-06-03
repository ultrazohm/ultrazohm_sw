#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
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
	float I_L1; 		// Grid side current in A
	float I_L2; 		// Grid side current in A
	float I_L3; 		// Grid side current in A
	float U_L1; 		// Grid side voltage in V
	float U_L2; 		// Grid side voltage in V
	float U_L3; 		// Grid side voltage in V
	float I_U; 		// Machine side current in A
	float I_V; 		// Machine side current in A
	float I_W; 		// Machine side current in A
	float U_U; 		// Machine side voltage in V
	float U_V; 		// Machine side voltage in V
	float U_W; 		// Machine side voltage in V
	float U_ZK; 		// DC-Link voltage in V
	float U_ZK2; 	// DC-Link voltage 2 in V
	float Res1; 		// Reserveeingang 1 - X51 (normiert auf 0...1 --> 0...4095)
	float Res2; 		// Reserveeingang 2 - X50 (normiert auf 0...1 --> 0...4095)
	float mechanicalRotorSpeed; 		// in rpm
	float mechanicalRotorSpeed_filtered; // in rpm
	float mechanicalPosition; 		// in m
	float mechanicalTorque; 			// in Nm
	float mechanicalTorqueSensitive; // in Nm
	float mechanicalTorqueObserved; 	// in Nm for observing the load torque
	float I_d;
	float I_q;
	float U_d;
	float U_q;
	float theta_elec;
	float theta_mech;
	float theta_offset; //in rad/s
	float temperature;
	uint32_t  heartbeatframe_content;
	float electricalRotorSpeed;
	float snd_fld[21];
	uint32_t slowDataCounter;
	/* Project Wizard BEGIN: actualValues */
	float adc_ltc2311_a1_ch0;
	float adc_ltc2311_a1_ch1;
	float adc_ltc2311_a1_ch2;
	float adc_ltc2311_a1_ch3;
	float adc_ltc2311_a1_ch4;
	float adc_ltc2311_a1_ch5;
	float adc_ltc2311_a1_ch6;
	float adc_ltc2311_a1_ch7;
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
	uz_temperaturecard_OneGroup temperature_card_d4_channel_A;
	uz_temperaturecard_OneGroup temperature_card_d4_channel_B;
	uz_temperaturecard_OneGroup temperature_card_d4_channel_C;
	uint32_t endat_encoder_d5_1_position_raw_single_turn;
	uint32_t endat_encoder_d5_1_position_raw_multi_turn;
	uint32_t endat_encoder_d5_1_position_multi_turn;
	float endat_encoder_d5_1_position_mech_si_single_turn;
	float endat_encoder_d5_1_position_el_si_single_turn;
	float endat_encoder_d5_1_speed_mech_si;
	float endat_encoder_d5_1_speed_el_si;
	float endat_encoder_d5_1_speed_mech_rpm;
	uint32_t ssi_encoder_d5_2_position_raw_single_turn;
	uint32_t ssi_encoder_d5_2_position_raw_multi_turn;
	uint32_t ssi_encoder_d5_2_position_multi_turn;
	float ssi_encoder_d5_2_position_mech_si_single_turn;
	float ssi_encoder_d5_2_position_el_si_single_turn;
	float ssi_encoder_d5_2_speed_mech_si;
	float ssi_encoder_d5_2_speed_el_si;
	float ssi_encoder_d5_2_speed_mech_rpm;
	uint32_t ssi_encoder_d5_3_position_raw_single_turn;
	uint32_t ssi_encoder_d5_3_position_raw_multi_turn;
	uint32_t ssi_encoder_d5_3_position_multi_turn;
	float ssi_encoder_d5_3_position_mech_si_single_turn;
	float ssi_encoder_d5_3_position_el_si_single_turn;
	float ssi_encoder_d5_3_speed_mech_si;
	float ssi_encoder_d5_3_speed_el_si;
	float ssi_encoder_d5_3_speed_mech_rpm;
/* Project Wizard END: actualValues */
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
	uz_mux_axi_t* mux_axi;
	/* Project Wizard BEGIN: objects */
	uz_adcLtc2311_t* adc_ltc2311_a1;
	uz_dac_interface_t* dac8831_a2;
	uz_adcMax11331_t* adc_max11331_a3;
	uz_temperaturecard_t* temperature_card_d4;
	uz_endat_interface_t* endat_encoder_d5_1;
	uz_ssi_interface_t* ssi_encoder_d5_2;
	uz_ssi_interface_t* ssi_encoder_d5_3;
/* Project Wizard END: objects */
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
} DS_Data;

#endif

