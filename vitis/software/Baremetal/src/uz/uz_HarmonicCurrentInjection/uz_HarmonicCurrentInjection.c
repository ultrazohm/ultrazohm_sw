/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2024 Benedikt Hofmann
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
*     http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "uz_HarmonicCurrentInjection.h"
#include "../uz_global_configuration.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_HAL.h"
#include <stdbool.h> 
#include "math.h"
#include <stdlib.h>

#if UZ_HARMONICCURRENTINJECTION_MAX_INSTANCES > 0U

// typedef struct uz_HarmonicCurrentInjection_t {
//     bool is_ready;
//     struct uz_HarmonicCurrentInjection_config config;
//     struct uz_CurrentControl_t* CurrentControl_first_harmonic;
//     struct uz_CurrentControl_t* CurrentControl_second_harmonic;
//     struct uz_IIR_Filter_t* Bandpass_first_harmonic_phase_a;
//     struct uz_IIR_Filter_t* Bandpass_first_harmonic_phase_b;
//     struct uz_IIR_Filter_t* Bandpass_first_harmonic_phase_c;
//     struct uz_IIR_Filter_t* Bandpass_second_harmonic_phase_a;
//     struct uz_IIR_Filter_t* Bandpass_second_harmonic_phase_b;
//     struct uz_IIR_Filter_t* Bandpass_second_harmonic_phase_c;
//     struct uz_IIR_Filter_t* Bandpass_harmonic_d_axis;
//     struct uz_IIR_Filter_t* Bandpass_harmonic_q_axis;
//     struct uz_IIR_Filter_t* Lowpass_first_harmonic_d_axis;
//     struct uz_IIR_Filter_t* Lowpass_first_harmonic_q_axis;
//     struct uz_IIR_Filter_t* Lowpass_second_harmonic_d_axis;
//     struct uz_IIR_Filter_t* Lowpass_second_harmonic_q_axis;
// } uz_HarmonicCurrentInjection_t;

typedef struct uz_HarmonicCurrentInjection_t {
    bool is_ready;
    struct uz_HarmonicCurrentInjection_config config;
    struct uz_CurrentControl_t* Controller_harmonic;
    struct uz_IIR_Filter_t* Bandpass_phase_a;
    struct uz_IIR_Filter_t* Bandpass_phase_b;
    struct uz_IIR_Filter_t* Bandpass_phase_c;
    struct uz_IIR_Filter_t* Bandpass_d_axis;
    struct uz_IIR_Filter_t* Bandpass_q_axis;
    struct uz_IIR_Filter_t* Lowpass_d_axis;
    struct uz_IIR_Filter_t* Lowpass_q_axis;
} uz_HarmonicCurrentInjection_t;

static uint32_t instance_counter_HarmonicCurrentInjection = 0U;
static uz_HarmonicCurrentInjection_t instances_HarmonicCurrentInjection[UZ_HARMONICCURRENTINJECTION_MAX_INSTANCES] = { 0 };

/**
 * @brief Memory allocation of the uz_HarmonicCurrentInjection_t struct
 *
 * @return Pointer to uz_HarmonicCurrentInjection_t instance
 */
uz_HarmonicCurrentInjection_t* uz_HarmonicCurrentInjection_allocation(void);

uz_HarmonicCurrentInjection_t* uz_HarmonicCurrentInjection_allocation(void){
    uz_assert(instance_counter_HarmonicCurrentInjection < UZ_HARMONICCURRENTINJECTION_MAX_INSTANCES);
    uz_HarmonicCurrentInjection_t* self = &instances_HarmonicCurrentInjection[instance_counter_HarmonicCurrentInjection];
    uz_assert_false(self->is_ready);
    instance_counter_HarmonicCurrentInjection++;
    self->is_ready = true;
    return (self);
}

// uz_HarmonicCurrentInjection_t* _init(struct uz_HarmonicCurrentInjection_config config) {
//     uz_HarmonicCurrentInjection_t* self = uz_HarmonicCurrentInjection_allocation();
//     switch (config.selection)
//     {
//     case abc_to_dq:
//         uz_assert(abs(config.order_first_harmonic) == 1);
//         uz_assert(abs(config.order_second_harmonic) == 1);
//         self->CurrentControl_first_harmonic = uz_CurrentControl_init(config.config_first_harmonic);
//         self->CurrentControl_second_harmonic = uz_CurrentControl_init(config.config_second_harmonic);
//         self->Bandpass_first_harmonic_phase_a = uz_signals_IIR_Filter_init(config.config_bandpass_first_harmonic_abc);
//         self->Bandpass_first_harmonic_phase_b = uz_signals_IIR_Filter_init(config.config_bandpass_first_harmonic_abc);
//         self->Bandpass_first_harmonic_phase_c = uz_signals_IIR_Filter_init(config.config_bandpass_first_harmonic_abc);
//         self->Bandpass_second_harmonic_phase_a = uz_signals_IIR_Filter_init(config.config_bandpass_second_harmonic_abc);
//         self->Bandpass_second_harmonic_phase_b = uz_signals_IIR_Filter_init(config.config_bandpass_second_harmonic_abc);
//         self->Bandpass_second_harmonic_phase_c = uz_signals_IIR_Filter_init(config.config_bandpass_second_harmonic_abc);
//         self->Lowpass_first_harmonic_d_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->Lowpass_first_harmonic_q_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->Lowpass_second_harmonic_d_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->Lowpass_second_harmonic_q_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->config = config;
//         break;
//     case dq_to_dqn:
//         uz_assert(abs(config.order_first_harmonic) == 1);
//         uz_assert(abs(config.order_second_harmonic) == 1);
//         uz_assert(config.order_first_harmonic>0);
//         uz_assert(config.order_second_harmonic<0);
//         uz_assert(abs(config.order_second_harmonic)-abs(config.order_first_harmonic)>2);
//         self->CurrentControl_first_harmonic = uz_CurrentControl_init(config.config_first_harmonic);
//         self->CurrentControl_second_harmonic = uz_CurrentControl_init(config.config_second_harmonic);
//         self->Bandpass_harmonic_d_axis = uz_signals_IIR_Filter_init(config.config_bandpass_harmonic_dq);
//         self->Bandpass_harmonic_q_axis = uz_signals_IIR_Filter_init(config.config_bandpass_harmonic_dq);
//         self->Lowpass_first_harmonic_d_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->Lowpass_first_harmonic_q_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->Lowpass_second_harmonic_d_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->Lowpass_second_harmonic_q_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
//         self->config = config;
//         break;
//     default:
//         break;
//     }
//     return (self);
// }

// uz_3ph_dq_t uz_HarmonicCurrentInjection_sample_abc(uz_HarmonicCurrentInjection_t* self, uz_3ph_dq_t i_ref_first_harmonic_Ampere, uz_3ph_dq_t i_ref_second_harmonic_Ampere, uz_3ph_abc_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad){
//     uz_assert_not_NULL(self);
// 	uz_assert(self->is_ready);
//     uz_3ph_abc_t i_abc_bp_filtered_first_harmonic_Ampere = { 0 };
//     i_abc_bp_filtered_first_harmonic_Ampere.a = uz_signals_IIR_Filter_sample(self->Bandpass_first_harmonic_phase_a, i_actual_Ampere.a);
//     i_abc_bp_filtered_first_harmonic_Ampere.b = uz_signals_IIR_Filter_sample(self->Bandpass_first_harmonic_phase_b, i_actual_Ampere.b);
//     i_abc_bp_filtered_first_harmonic_Ampere.c = uz_signals_IIR_Filter_sample(self->Bandpass_first_harmonic_phase_c, i_actual_Ampere.c);
//     uz_3ph_abc_t i_abc_bp_filtered_second_harmonic_Ampere = { 0 };
//     i_abc_bp_filtered_second_harmonic_Ampere.a = uz_signals_IIR_Filter_sample(self->Bandpass_second_harmonic_phase_a, i_actual_Ampere.a);
//     i_abc_bp_filtered_second_harmonic_Ampere.b = uz_signals_IIR_Filter_sample(self->Bandpass_second_harmonic_phase_b, i_actual_Ampere.b);
//     i_abc_bp_filtered_second_harmonic_Ampere.c = uz_signals_IIR_Filter_sample(self->Bandpass_second_harmonic_phase_c, i_actual_Ampere.c);
//     uz_3ph_dq_t i_dqn_bp_filtered_first_harmonic_Ampere = uz_transformation_3ph_harmonic_abc_to_dqn(i_abc_bp_filtered_first_harmonic_Ampere, theta_el_rad, self->config.order_first_harmonic);
//     uz_3ph_dq_t i_dqn_bp_filtered_second_harmonic_Ampere = uz_transformation_3ph_harmonic_abc_to_dqn(i_abc_bp_filtered_second_harmonic_Ampere, theta_el_rad, self->config.order_second_harmonic);
//     uz_3ph_dq_t i_dqn_lp_filtered_first_harmonic_Ampere = { 0 };
//     i_dqn_lp_filtered_first_harmonic_Ampere.d = uz_signals_IIR_Filter_sample(self->Lowpass_first_harmonic_d_axis, i_dqn_bp_filtered_first_harmonic_Ampere.d);
//     i_dqn_lp_filtered_first_harmonic_Ampere.q = uz_signals_IIR_Filter_sample(self->Lowpass_first_harmonic_q_axis, i_dqn_bp_filtered_first_harmonic_Ampere.q);
//     uz_3ph_dq_t i_dqn_lp_filtered_second_harmonic_Ampere = { 0 };
//     i_dqn_lp_filtered_second_harmonic_Ampere.d = uz_signals_IIR_Filter_sample(self->Lowpass_second_harmonic_d_axis, i_dqn_bp_filtered_second_harmonic_Ampere.d);
//     i_dqn_lp_filtered_second_harmonic_Ampere.q = uz_signals_IIR_Filter_sample(self->Lowpass_second_harmonic_q_axis, i_dqn_bp_filtered_second_harmonic_Ampere.q);
//     uz_3ph_dq_t v_dqn_first_harmonic_Volts = uz_CurrentControl_sample(self->CurrentControl_first_harmonic, i_ref_first_harmonic_Ampere, i_dqn_lp_filtered_first_harmonic_Ampere, V_dc_volts, omega_el_rad_per_sec);
//     uz_3ph_dq_t v_dqn_second_harmonic_Volts = uz_CurrentControl_sample(self->CurrentControl_second_harmonic, i_ref_second_harmonic_Ampere, i_dqn_lp_filtered_second_harmonic_Ampere, V_dc_volts, omega_el_rad_per_sec);
//     uz_3ph_abc_t v_abc_first_harmonic_Volts = uz_transformation_3ph_harmonic_dqn_to_abc(v_dqn_first_harmonic_Volts, theta_el_rad, self->config.order_first_harmonic);
//     uz_3ph_dq_t v_dq_first_harmonic_Volts = uz_transformation_3ph_abc_to_dq(v_abc_first_harmonic_Volts, theta_el_rad);
//     uz_3ph_abc_t v_abc_second_harmonic_Ampere = uz_transformation_3ph_harmonic_dqn_to_abc(v_dqn_second_harmonic_Volts, theta_el_rad, self->config.order_second_harmonic);
//     uz_3ph_dq_t v_dq_second_harmonic_Volts = uz_transformation_3ph_abc_to_dq(v_abc__harmonic_Volts, theta_el_rad);
// }

uz_HarmonicCurrentInjection_t* uz_HarmonicCurrentInjection_init(struct uz_HarmonicCurrentInjection_config config) {
    uz_HarmonicCurrentInjection_t* self = uz_HarmonicCurrentInjection_allocation();
    uz_assert(fabsf(config.order_harmonic) != 1.0f);
    self->Controller_harmonic = uz_CurrentControl_init(config.config_currentcontroller);
    self->config = config;
    switch (config.selection)
    {
    case abc_to_dq:
        self->Bandpass_phase_a = uz_signals_IIR_Filter_init(config.config_bandpass_abc);
        self->Bandpass_phase_b = uz_signals_IIR_Filter_init(config.config_bandpass_abc);
        self->Bandpass_phase_c = uz_signals_IIR_Filter_init(config.config_bandpass_abc);
        self->Lowpass_d_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
        self->Lowpass_q_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
        break;
    case dq_to_dqn:
        self->Bandpass_d_axis = uz_signals_IIR_Filter_init(config.config_bandpass_dq);
        self->Bandpass_q_axis = uz_signals_IIR_Filter_init(config.config_bandpass_dq);
        self->Lowpass_d_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
        self->Lowpass_q_axis = uz_signals_IIR_Filter_init(config.config_lowpass_dq);
        break;
    default:
        break;
    }
    return (self);
}

// uz_3ph_dq_t uz_HarmonicCurrentInjection_sample_abc(uz_HarmonicCurrentInjection_t* self, uz_3ph_dq_t i_ref_first_harmonic_Ampere, uz_3ph_dq_t i_ref_second_harmonic_Ampere, uz_3ph_abc_t i_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad){
//     uz_assert_not_NULL(self);
// 	uz_assert(self->is_ready);
//     uz_3ph_abc_t i_abc_bp_filtered_first_harmonic_Ampere = { 0 };
//     i_abc_bp_filtered_first_harmonic_Ampere.a = uz_signals_IIR_Filter_sample(self->Bandpass_first_harmonic_phase_a, i_actual_Ampere.a);
//     i_abc_bp_filtered_first_harmonic_Ampere.b = uz_signals_IIR_Filter_sample(self->Bandpass_first_harmonic_phase_b, i_actual_Ampere.b);
//     i_abc_bp_filtered_first_harmonic_Ampere.c = uz_signals_IIR_Filter_sample(self->Bandpass_first_harmonic_phase_c, i_actual_Ampere.c);
//     uz_3ph_abc_t i_abc_bp_filtered_second_harmonic_Ampere = { 0 };
//     i_abc_bp_filtered_second_harmonic_Ampere.a = uz_signals_IIR_Filter_sample(self->Bandpass_second_harmonic_phase_a, i_actual_Ampere.a);
//     i_abc_bp_filtered_second_harmonic_Ampere.b = uz_signals_IIR_Filter_sample(self->Bandpass_second_harmonic_phase_b, i_actual_Ampere.b);
//     i_abc_bp_filtered_second_harmonic_Ampere.c = uz_signals_IIR_Filter_sample(self->Bandpass_second_harmonic_phase_c, i_actual_Ampere.c);
//     uz_3ph_dq_t i_dqn_bp_filtered_first_harmonic_Ampere = uz_transformation_3ph_harmonic_abc_to_dqn(i_abc_bp_filtered_first_harmonic_Ampere, theta_el_rad, self->config.order_first_harmonic);
//     uz_3ph_dq_t i_dqn_bp_filtered_second_harmonic_Ampere = uz_transformation_3ph_harmonic_abc_to_dqn(i_abc_bp_filtered_second_harmonic_Ampere, theta_el_rad, self->config.order_second_harmonic);
//     uz_3ph_dq_t i_dqn_lp_filtered_first_harmonic_Ampere = { 0 };
//     i_dqn_lp_filtered_first_harmonic_Ampere.d = uz_signals_IIR_Filter_sample(self->Lowpass_first_harmonic_d_axis, i_dqn_bp_filtered_first_harmonic_Ampere.d);
//     i_dqn_lp_filtered_first_harmonic_Ampere.q = uz_signals_IIR_Filter_sample(self->Lowpass_first_harmonic_q_axis, i_dqn_bp_filtered_first_harmonic_Ampere.q);
//     uz_3ph_dq_t i_dqn_lp_filtered_second_harmonic_Ampere = { 0 };
//     i_dqn_lp_filtered_second_harmonic_Ampere.d = uz_signals_IIR_Filter_sample(self->Lowpass_second_harmonic_d_axis, i_dqn_bp_filtered_second_harmonic_Ampere.d);
//     i_dqn_lp_filtered_second_harmonic_Ampere.q = uz_signals_IIR_Filter_sample(self->Lowpass_second_harmonic_q_axis, i_dqn_bp_filtered_second_harmonic_Ampere.q);
//     uz_3ph_dq_t v_dqn_first_harmonic_Volts = uz_CurrentControl_sample(self->CurrentControl_first_harmonic, i_ref_first_harmonic_Ampere, i_dqn_lp_filtered_first_harmonic_Ampere, V_dc_volts, omega_el_rad_per_sec);
//     uz_3ph_dq_t v_dqn_second_harmonic_Volts = uz_CurrentControl_sample(self->CurrentControl_second_harmonic, i_ref_second_harmonic_Ampere, i_dqn_lp_filtered_second_harmonic_Ampere, V_dc_volts, omega_el_rad_per_sec);
//     uz_3ph_abc_t v_abc_first_harmonic_Volts = uz_transformation_3ph_harmonic_dqn_to_abc(v_dqn_first_harmonic_Volts, theta_el_rad, self->config.order_first_harmonic);
//     uz_3ph_dq_t v_dq_first_harmonic_Volts = uz_transformation_3ph_abc_to_dq(v_abc_first_harmonic_Volts, theta_el_rad);
//     uz_3ph_abc_t v_abc_second_harmonic_Ampere = uz_transformation_3ph_harmonic_dqn_to_abc(v_dqn_second_harmonic_Volts, theta_el_rad, self->config.order_second_harmonic);
//     uz_3ph_dq_t v_dq_second_harmonic_Volts = uz_transformation_3ph_abc_to_dq(v_abc__harmonic_Volts, theta_el_rad);
//     uz_3ph_dq_t v_dq_Volts = { 0 };
//     v_dq_Volts.d = v_dq_first_harmonic_Volts.d + v_dq_second_harmonic_Volts.d;
//     v_dq_Volts.q = v_dq_first_harmonic_Volts.q + v_dq_second_harmonic_Volts.q;
//     return (v_dq_Volts);
// }

uz_3ph_dq_t uz_HarmonicCurrentInjection_sample(uz_HarmonicCurrentInjection_t* self, uz_3ph_dq_t i_ref_harmonic_Ampere, uz_3ph_abc_t i_abc_actual_Ampere, float V_dc_volts, float omega_el_rad_per_sec, float theta_el_rad){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    uz_3ph_dq_t i_dq_actual_Ampere = { 0 };
    uz_3ph_abc_t i_abc_bp_filtered_Ampere = { 0 };
    uz_3ph_dq_t i_dq_bp_filtered_Ampere = { 0 };
    uz_3ph_dq_t i_dqn_bp_filtered_Ampere = { 0 };
    uz_3ph_dq_t i_dqn_lp_filtered_Ampere = { 0 };
    uz_3ph_dq_t v_dqn_Volts = { 0 };
    uz_3ph_abc_t v_abc_Volts = { 0 };
    uz_3ph_dq_t v_dq_Volts = { 0 };
    switch (self->config.selection)
    {
    case abc_to_dq:
        i_abc_bp_filtered_Ampere.a = uz_signals_IIR_Filter_sample(self->Bandpass_phase_a, i_abc_actual_Ampere.a);
        i_abc_bp_filtered_Ampere.b = uz_signals_IIR_Filter_sample(self->Bandpass_phase_b, i_abc_actual_Ampere.b);
        i_abc_bp_filtered_Ampere.c = uz_signals_IIR_Filter_sample(self->Bandpass_phase_c, i_abc_actual_Ampere.c);
        i_dqn_bp_filtered_Ampere = uz_transformation_3ph_harmonic_abc_to_dqn(i_abc_bp_filtered_Ampere, theta_el_rad, self->config.order_harmonic);
        i_dqn_lp_filtered_Ampere.d = uz_signals_IIR_Filter_sample(self->Lowpass_d_axis, i_dqn_bp_filtered_Ampere.d);
        i_dqn_lp_filtered_Ampere.q = uz_signals_IIR_Filter_sample(self->Lowpass_q_axis, i_dqn_bp_filtered_Ampere.q);
        v_dqn_Volts = uz_CurrentControl_sample(self->Controller_harmonic, i_ref_harmonic_Ampere, i_dqn_lp_filtered_Ampere, V_dc_volts, omega_el_rad_per_sec);
        v_abc_Volts = uz_transformation_3ph_harmonic_dqn_to_abc(v_dqn_Volts, theta_el_rad, self->config.order_harmonic);
        v_dq_Volts = uz_transformation_3ph_abc_to_dq(v_abc_Volts, theta_el_rad);
        break;
    case dq_to_dqn: ;
        i_dq_actual_Ampere = uz_transformation_3ph_abc_to_dq(i_abc_actual_Ampere, theta_el_rad);
        i_dq_bp_filtered_Ampere.d = uz_signals_IIR_Filter_sample(self->Bandpass_d_axis, i_dq_actual_Ampere.d);
        i_dq_bp_filtered_Ampere.q = uz_signals_IIR_Filter_sample(self->Bandpass_q_axis, i_dq_actual_Ampere.q);
        i_dqn_bp_filtered_Ampere = uz_transformation_3ph_harmonic_dq_to_dqn(i_dq_bp_filtered_Ampere, theta_el_rad, self->config.order_harmonic);
        i_dqn_lp_filtered_Ampere.d = uz_signals_IIR_Filter_sample(self->Lowpass_d_axis, i_dqn_bp_filtered_Ampere.d);
        i_dqn_lp_filtered_Ampere.q = uz_signals_IIR_Filter_sample(self->Lowpass_q_axis, i_dqn_bp_filtered_Ampere.q);
        v_dqn_Volts = uz_CurrentControl_sample(self->Controller_harmonic, i_ref_harmonic_Ampere, i_dqn_lp_filtered_Ampere, V_dc_volts, omega_el_rad_per_sec);
        v_dq_Volts = uz_transformation_3ph_harmonic_dqn_to_dq(v_dqn_Volts, theta_el_rad, self->config.order_harmonic);
        break;
    default: ;
        break;
    }
    return(v_dq_Volts);
}

void uz_HarmonicCurrentInjection_set_filters_abc(uz_HarmonicCurrentInjection_t* self, float omega_el_rad_per_sec){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    float pass_frequency_Hz = fabsf(omega_el_rad_per_sec / (2.0f * UZ_PIf) * self->config.order_harmonic);
    float cutoff_frequency_Hz = omega_el_rad_per_sec / (2.0f * UZ_PIf * 10.0f);
    uz_signals_IIR_Filter_set_bandpass(self->Bandpass_phase_a, pass_frequency_Hz, 0.05f);
    uz_signals_IIR_Filter_set_bandpass(self->Bandpass_phase_b, pass_frequency_Hz, 0.05f);
    uz_signals_IIR_Filter_set_bandpass(self->Bandpass_phase_c, pass_frequency_Hz, 0.05f);
    uz_signals_IIR_Filter_set_lowpass(self->Lowpass_d_axis, cutoff_frequency_Hz);
    uz_signals_IIR_Filter_set_lowpass(self->Lowpass_q_axis, cutoff_frequency_Hz);
} 

void uz_HarmonicCurrentInjection_set_filters_dq(uz_HarmonicCurrentInjection_t* self, float omega_el_rad_per_sec){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    float pass_frequency_Hz = fabsf(omega_el_rad_per_sec / (2.0f * UZ_PIf) * (self->config.order_harmonic - 1.0f));
    float cutoff_frequency_Hz = omega_el_rad_per_sec / (2.0f * UZ_PIf * 10.0f);
    uz_signals_IIR_Filter_set_bandpass(self->Bandpass_d_axis, pass_frequency_Hz, 0.05f);
    uz_signals_IIR_Filter_set_bandpass(self->Bandpass_q_axis, pass_frequency_Hz, 0.05f);
    uz_signals_IIR_Filter_set_lowpass(self->Lowpass_d_axis, cutoff_frequency_Hz);
    uz_signals_IIR_Filter_set_lowpass(self->Lowpass_q_axis, cutoff_frequency_Hz);
} 

#endif