#ifndef GLOBAL_DATA_H
#define GLOBAL_DATA_H

#include <stdbool.h>
#include <stdint.h>
#include "IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "IP_Cores/uz_interlockDeadtime2L/uz_interlockDeadtime2L.h"
#include "IP_Cores/uz_mux_axi/uz_mux_axi.h"
#include "uz/uz_wavegen/uz_wavegen.h"
#include "IP_Cores/uz_plantPT1/uz_plantPT1.h"
#include "IP_Cores/uz_pmsmmodel/uz_pmsmModel.h"
#include "uz/uz_CurrentControl/uz_CurrentControl.h"
#include "uz/uz_setpoint/uz_setpoint.h"
#include "uz/uz_SpeedControl/uz_speedcontrol.h"
#include "uz/uz_signals/uz_signals.h"
// Project Wizard adapter slot headers
#include "include/a1_adapter_init.h"
#include "include/a2_adapter_init.h"
#include "include/a3_adapter_init.h"
#include "include/d1_adapter_init.h"
#include "include/d2_adapter_init.h"
#include "include/d3_adapter_init.h"
#include "include/d4_adapter_init.h"
#include "include/d5_adapter_init.h"
#include "uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"

#include "uz/uz_pmsm_control/uz_pmsm_control.h"
#include "IP_Cores/uz_axi_gpio/uz_axi_gpio.h"

enum control_mode_t
{
    DUT_ONLY_CURRENT_CONTROL = 0,
    PM_ONLY_CURRENT_CONTROL,
    DUT_ONLY_SPEED_CONTROL,
    PM_ONLY_SPEED_CONTROL,
    PM_ONLY_DUTY_CYCLE,
    DUT_ONLY_DUTY_CYCLE,
    PM_SPEED_DUT_CURRENT,
    PM_CURRENT_DUT_SPEED,
    DUT_ONLY_CURRENT_CONTROL_CIL,
    PM_ONLY_CURRENT_CONTROL_CIL,
    DUT_ONLY_SPEED_CONTROL_CIL,
    PM_ONLY_SPEED_CONTROL_CIL,
    PM_SPEED_DUT_CURRENT_CIL,
    PM_CURRENT_DUT_SPEED_CIL,
};

typedef struct _actualValues_
{
	float pwm_frequency_hz;
	float isr_samplerate_s;
	uint32_t heartbeatframe_content;
	float snd_fld[21];
	uint32_t slowDataCounter;
	float d3_input_loopback_uint32;
	struct uz_pmsm_measurement_values dut_measurements;
	struct uz_pmsm_measurement_values prime_mover_measurements;
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
	struct uz_inverter_adapter_outputs_t inverter_adapter_d1;
	struct uz_inverter_adapter_outputs_t inverter_adapter_d2;
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
	float incremental_encoder_d5_1_theta_el;
	float incremental_encoder_d5_1_omega_mech;
	float incremental_encoder_d5_1_omega_mech_ma_n4;
	uint32_t incremental_encoder_d5_1_position;
	uint32_t incremental_encoder_d5_1_position_w_offset;
	uint32_t incremental_encoder_d5_1_index_found;
	float incremental_encoder_d5_2_theta_el;
	float incremental_encoder_d5_2_omega_mech;
	float incremental_encoder_d5_2_omega_mech_ma_n4;
	uint32_t incremental_encoder_d5_2_position;
	uint32_t incremental_encoder_d5_2_position_w_offset;
	uint32_t incremental_encoder_d5_2_index_found;
	float incremental_encoder_d5_3_theta_el;
	float incremental_encoder_d5_3_omega_mech;
	float incremental_encoder_d5_3_omega_mech_ma_n4;
	uint32_t incremental_encoder_d5_3_position;
	uint32_t incremental_encoder_d5_3_position_w_offset;
	uint32_t incremental_encoder_d5_3_index_found;
	/* Project Wizard END: actualValues */
	float prime_mover_mean_temp_degC;
	float dut_mean_temp_degC;
	enum uz_pmsm_control_safe_operating_region_violation dut_safe_operating_region_violation;
	enum uz_pmsm_control_safe_operating_region_violation prime_mover_safe_operating_region_violation;
	float pm_torque_Nm;
	float dut_torque_Nm;
	uint32_t io_card_d3_state;
} actualValues;

typedef struct _referenceAndSetValues_
{

	float prime_mover_n_ref_rpm;
	float dut_n_ref_rpm;
	float prime_mover_n_ref_rpm_filtered;
	float prime_mover_M_ref_Nm;
	uz_3ph_dq_t prime_mover_i_dq_ref_A;
	uz_3ph_dq_t dut_i_dq_ref_A;
	/* Project Wizard BEGIN: referenceAndSetValues */
	struct uz_DutyCycle_t prime_mover_duty_cycle;
	struct uz_DutyCycle_t dut_duty_cycle;
	float pwm_3L_0_halfBridgeDutyCycle_1;
	float pwm_3L_0_halfBridgeDutyCycle_2;
	float pwm_3L_0_halfBridgeDutyCycle_3;
	/* Project Wizard END: referenceAndSetValues */
} referenceAndSetValues;

typedef struct
{
	uz_mux_axi_t *mux_axi;
	uz_pmsmModel_t *dut_pmsm_model;
	uz_pmsmModel_t *prime_mover_pmsm_model;
	uz_pmsm_control_t *prime_mover_control;
	uz_pmsm_control_t *dut_control;
	struct uz_pmsm_actual_data *prime_mover_actual_data;
	struct uz_pmsm_actual_data *dut_actual_data;
	struct uz_pmsm_measurement_values *prime_mover_measurements;
	struct uz_pmsm_measurement_values *dut_measurements;
	struct uz_pmsm_reference_values *prime_mover_reference_values;
	struct uz_pmsm_reference_values *dut_reference_values;
	/* Project Wizard BEGIN: objects */
	uz_PWM_SS_2L_t *project_wizard_pwm_2l_0_d1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_0_d1;
	uz_PWM_SS_2L_t *project_wizard_pwm_2l_1_d2;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_1_d2;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_d3_1;
	uz_PWM_SS_2L_t *project_wizard_pwm_2l_d3_1;
	uz_interlockDeadtime2L_handle project_wizard_deadtime_2l_d3_2;
	uz_PWM_SS_2L_t *project_wizard_pwm_2l_d3_2;
	uz_wavegen_three_phase *three_phase_sine;
	uz_adcLtc2311_t *adc_ltc2311_a1;
	uz_adcLtc2311_t *adc_ltc2311_a2;
	uz_adcLtc2311_t *adc_ltc2311_a3;
	uz_inverter_adapter_t *inverter_adapter_d1;
	uz_inverter_adapter_t *inverter_adapter_d2;
	uz_resolverIP_t *resolver_ip_d4_1;
	uz_resolver_pl_interface_t *resolver_pl_interface_d4_1;
	uz_resolverIP_t *resolver_ip_d4_2;
	uz_resolver_pl_interface_t *resolver_pl_interface_d4_2;
	uz_resolverIP_t *resolver_ip_d4_3;
	uz_resolver_pl_interface_t *resolver_pl_interface_d4_3;
	uz_incrementalEncoder_t *incremental_encoder_d5_1;
	uz_incrementalEncoder_t *incremental_encoder_d5_2;
	uz_incrementalEncoder_t *incremental_encoder_d5_3;
	uz_axi_gpio_t *axi_gpio_d3;
	/* Project Wizard END: objects */
} object_pointers_t;

typedef struct _DS_Data_
{
	referenceAndSetValues rasv;
	actualValues av;
	object_pointers_t objects;
	enum control_mode_t control_mode;
	struct uz_DutyCycle_t dut_manual_duty_cycle;
	struct uz_DutyCycle_t prime_mover_manual_duty_cycle;
} DS_Data;


#endif
