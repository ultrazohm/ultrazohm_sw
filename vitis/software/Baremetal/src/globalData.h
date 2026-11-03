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
#include "IP_Cores/uz_resolver_pos_mt/uz_resolver_pos_mt.h"
#include "IP_Cores/uz_JL_SigmaDelta_Interface/uz_JL_SigmaDelta_Interface.h"
#include "IP_Cores/uz_JL_SDC_OCP/uz_JL_SDC_OCP.h"
#include "IP_Cores/uz_JL_flt_dis/uz_JL_flt_dis.h"
#include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"
#include "include/JL_SH_Umrichter.h"
#include "include/uz_platform_state_machine.h"

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
	float mechanicalPosition; 		// in m
	float snd_fld[21];
	float theta_el_offset;
	float theta_el;
	float omega_el;
	float mult_pos_grad; 			// Multiturn-Positionsistwert in Grad (aus uz_resolver_pos_mt)
	bool mult_pos_valid; 			// true, sobald der Multiturn-Positionswert eine gueltige Referenz hat
	float mult_pos_turns;
	struct uz_resolver_pl_interface_outputs_t resolver_pl_outputs;
	uint32_t slowDataCounter;
	struct uz_JL_SigmaDelta_Interface_output_t_float Sinc3_Filter_P;
	struct uz_JL_SigmaDelta_Interface_output_t_float Sinc3_Filter_I;
	struct uz_JL_SigmaDelta_Interface_output_t_float Sinc3_Filter_OCP; // kalibrierte Phasenstroeme der FPGA-OCP-Instanz (nur zur JavaScope-Beobachtung)
	float debug_timestamp_s;		// Debug: Timestamp der ISR in Sekunden, fuer JavaScope
	float CB_omega_grads;
} actualValues;

typedef struct _referenceAndSetValues_ {
	float halfBridge1DutyCycle;
	float halfBridge2DutyCycle;
	float halfBridge3DutyCycle;
	ctrl_state_t ctrl_state;
	float Soll_Drehzahl; // speed setpoint for rpm_control, in rpm
	float Soll_id; // d-axis current setpoint for current_control, in A
	float Soll_iq; // q-axis current setpoint for current_control, in A
	float Soll_HB1_DutyCycle; // manual duty cycle setpoint for HB1, 0.0 .. 1.0
	float Soll_HB2_DutyCycle; // manual duty cycle setpoint for HB2, 0.0 .. 1.0
	float Soll_HB3_DutyCycle; // manual duty cycle setpoint for HB3, 0.0 .. 1.0
	float Soll_Winkel_grad;          // position_control: Positionssollwert in Grad
	float Soll_Geschwindigkeit_grads; // position_control: Geschwindigkeitssollwert in Grad/s
	float Soll_Beschleunigung_grads2; // position_control: Beschleunigungssollwert in Grad/s^2
	uint32_t Modus_Position_sel;     // position_control: Untermodus 0=Warten,1=Trapez,2=Home,3=Single_Position (Cast auf Modus_Position in der ISR)
	float Ref_Winkel_grad;           // Referenzier-Preset: Wellenwinkel (Motorseite) in Grad, der per Button in den Multiturn-Zaehler geladen wird
} referenceAndSetValues;

typedef struct{
	uz_PWM_SS_2L_t* pwm_d1_pin_0_to_5;
	uz_interlockDeadtime2L_handle deadtime_interlock_d1_pin_0_to_5;
	uz_resolverIP_t* resolver;
	uz_resolver_pl_interface_t* resolver_pl_interface;
	uz_mux_axi_t* mux_axi;
	uz_JL_SigmaDelta_Interface_t* Sinc3_Filter_P;
	uz_JL_SigmaDelta_Interface_t* Sinc3_Filter_I;
	uz_JL_SigmaDelta_Interface_t* Sinc3_Filter_OCP;
	uz_JL_SDC_OCP_t* sdc_ocp_P;
	uz_JL_SDC_OCP_t* sdc_ocp_OCP;
	uz_JL_flt_dis_t* flt_dis;
	uz_axi_gpio_t* input_gpio;
	uz_axi_gpio_t* output_gpio;
	platform_state_t platform_state_old;
	uz_resolver_pos_mt_t* resolver_pos_mt;
}object_pointers_t;

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	AnalogAdapters aa;
	object_pointers_t objects;
} DS_Data;

#endif

