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
#include "uz/uz_pmsm_control/uz_pmsm_control.h"

typedef struct _actualValues_
{
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
	float adc_ltc2311_a2_ch0;
	float adc_ltc2311_a2_ch1;
	float adc_ltc2311_a2_ch2;
	float adc_ltc2311_a2_ch3;
	float adc_ltc2311_a2_ch4;
	float adc_ltc2311_a2_ch5;
	float adc_ltc2311_a2_ch6;
	float adc_ltc2311_a2_ch7;
	float adc_ltc2311_a3_ch0;
	float adc_ltc2311_a3_ch1;
	float adc_ltc2311_a3_ch2;
	float adc_ltc2311_a3_ch3;
	float adc_ltc2311_a3_ch4;
	float adc_ltc2311_a3_ch5;
	float adc_ltc2311_a3_ch6;
	float adc_ltc2311_a3_ch7;
	uint32_t io_card_d1_state;
	uint32_t io_card_d2_state;
	uint32_t io_card_d3_state;
	int32_t resolver_pl_interface_d4_1_revolution_counter;
	float resolver_pl_interface_d4_1_position_mech_2pi;
	float resolver_pl_interface_d4_1_position_el_2pi;
	float resolver_pl_interface_d4_1_omega_mech_rad_s;
	float resolver_pl_interface_d4_1_n_mech_rpm;
	float resolver_pl_interface_d4_1_omega_el_rad_s;
	int32_t resolver_pl_interface_d4_2_revolution_counter;
	float resolver_pl_interface_d4_2_position_mech_2pi;
	float resolver_pl_interface_d4_2_position_el_2pi;
	float resolver_pl_interface_d4_2_omega_mech_rad_s;
	float resolver_pl_interface_d4_2_n_mech_rpm;
	float resolver_pl_interface_d4_2_omega_el_rad_s;
	int32_t resolver_pl_interface_d4_3_revolution_counter;
	float resolver_pl_interface_d4_3_position_mech_2pi;
	float resolver_pl_interface_d4_3_position_el_2pi;
	float resolver_pl_interface_d4_3_omega_mech_rad_s;
	float resolver_pl_interface_d4_3_n_mech_rpm;
	float resolver_pl_interface_d4_3_omega_el_rad_s;
	int32_t resolver_pl_interface_d5_1_revolution_counter;
	float resolver_pl_interface_d5_1_position_mech_2pi;
	float resolver_pl_interface_d5_1_position_el_2pi;
	float resolver_pl_interface_d5_1_omega_mech_rad_s;
	float resolver_pl_interface_d5_1_n_mech_rpm;
	float resolver_pl_interface_d5_1_omega_el_rad_s;
	int32_t resolver_pl_interface_d5_2_revolution_counter;
	float resolver_pl_interface_d5_2_position_mech_2pi;
	float resolver_pl_interface_d5_2_position_el_2pi;
	float resolver_pl_interface_d5_2_omega_mech_rad_s;
	float resolver_pl_interface_d5_2_n_mech_rpm;
	float resolver_pl_interface_d5_2_omega_el_rad_s;
	enum uz_pmsm_control_safe_operating_region_violation pm_safe_operating_region_violation;
	struct uz_pmsm_measurement_values prime_mover_measurements;
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
	uz_adcLtc2311_t* adc_ltc2311_a2;
	uz_adcLtc2311_t* adc_ltc2311_a3;
	uz_axi_gpio_t* axi_gpio_d1;
	uz_axi_gpio_t* axi_gpio_d2;
	uz_axi_gpio_t* axi_gpio_d3;
	uz_resolverIP_t* resolver_ip_d4_1;
	uz_resolver_pl_interface_t* resolver_pl_interface_d4_1;
	uz_resolverIP_t* resolver_ip_d4_2;
	uz_resolver_pl_interface_t* resolver_pl_interface_d4_2;
	uz_resolverIP_t* resolver_ip_d4_3;
	uz_resolver_pl_interface_t* resolver_pl_interface_d4_3;
	uz_resolverIP_t* resolver_ip_d5_1;
	uz_resolver_pl_interface_t* resolver_pl_interface_d5_1;
	uz_resolverIP_t* resolver_ip_d5_2;
	uz_resolver_pl_interface_t* resolver_pl_interface_d5_2;
	uz_wavegen_three_phase* m1_sine;
	uz_wavegen_three_phase* m2_sine;
	uz_wavegen_three_phase* m3_sine;
	uz_wavegen_three_phase* m4_sine;
	uz_pmsm_control_t *prime_mover_control;
	struct uz_pmsm_measurement_values *prime_mover_measurements;
	struct uz_pmsm_actual_data *prime_mover_actual_data;
	struct uz_pmsm_reference_values *prime_mover_reference_values;
	/* Project Wizard END: objects */
}object_pointers_t;

enum control_mode_t {
	control_mode_manual = 0,
	control_mode_wavegen,
	control_mode_m1_only_foc};

typedef struct _DS_Data_ {
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
	struct uz_3ph_abc_t m1_duty;
	struct uz_3ph_abc_t m2_duty;
	struct uz_3ph_abc_t m3_duty;
	struct uz_3ph_abc_t m4_duty;
	struct uz_3ph_abc_t m1_duty_from_javascope;
	struct uz_3ph_abc_t m2_duty_from_javascope;
	struct uz_3ph_abc_t m3_duty_from_javascope;
	struct uz_3ph_abc_t m4_duty_from_javascope;
	struct uz_3ph_abc_t m1_phase_current;
	struct uz_3ph_abc_t m1_phase_voltage;
	struct uz_3ph_abc_t m2_phase_current;
	struct uz_3ph_abc_t m2_phase_voltage;
	float m1_dc_current;
	float m2_dc_current;
	float m12_dc_voltage;
	bool d1_inverter_enable;
	bool d2_inverter_enable;
	bool d3_inverter_enable;
	bool d4_inverter_enable;
	enum control_mode_t control_mode;
	float sine_amp;
	float sine_frq;
	float prime_mover_n_ref_rpm;
	struct uz_3ph_dq_t prime_mover_i_dq_ref_A;
	bool enable_speed_control;
} DS_Data;

#endif

