/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Valentin Hoppe
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

#include "uz_subspace_resonant_control.h"
#include "../uz_global_configuration.h"
#include <stdint.h>
#include <stdbool.h>
#include "../uz_HAL.h"

#if UZ_RESONANT_CONTROL_MAX_INSTANCES > 0


typedef struct uz_subspace_resonant_control {
	bool is_ready;
    uz_resonantController_t* resonant_1;
    uz_resonantController_t* resonant_2;
    struct uz_subspace_resonant_control_config config;
}uz_subspace_resonant_control;

static uint32_t instances_counter_resonant_control = 0;

static uz_subspace_resonant_control instances_resonant_control[UZ_RESONANT_CONTROL_MAX_INSTANCES] = {0};


/**
 * @brief Memory allocation of the uz_CurrentControl_t struct
 *
 * @return Pointer to uz_CurrentControl_t instance
 */
static uz_subspace_resonant_control* uz_subspace_resonant_control_allocation(void);

static void uz_subspace_resonant_control_step_controllers_general(uz_subspace_resonant_control* self, float actual1, float actual2, float ref1, float ref2, float* out1, float* out2, float omega_el_fundamental);

static uz_subspace_resonant_control* uz_subspace_resonant_control_allocation(void) {
	uz_assert(instances_counter_resonant_control < UZ_RESONANT_CONTROL_MAX_INSTANCES);
	uz_subspace_resonant_control* self = &instances_resonant_control[instances_counter_resonant_control];
	uz_assert(self->is_ready == false);
	instances_counter_resonant_control++;
	self->is_ready = true;
	return (self);
}

uz_subspace_resonant_control* uz_subspace_resonant_control_init(struct uz_subspace_resonant_control_config config) {
	uz_subspace_resonant_control* self = uz_subspace_resonant_control_allocation();

	//uz_assert(config.max_modulation_index > 0.0f);
    struct uz_resonantController_config config_1 = {
        .antiwindup_gain = config.antiwindup_gain,
        .fundamental_frequency = 0.0f,
        .gain = config.gain_1,
        .harmonic_order = config.harmonic_order,
        .lower_limit = config.lower_limit,
        .upper_limit = config.upper_limit,
        .sampling_time = config.sampling_time,
        .in_measured_value = 0.0f,
        .in_reference_value = 0.0f};
    struct uz_resonantController_config config_2 = {
        .antiwindup_gain = config.antiwindup_gain,
        .fundamental_frequency = 0.0f,
        .gain = config.gain_2,
        .harmonic_order = config.harmonic_order,
        .lower_limit = config.lower_limit,
        .upper_limit = config.upper_limit,
        .sampling_time = config.sampling_time,
        .in_measured_value = 0.0f,
        .in_reference_value = 0.0f};

	self->resonant_1 = uz_resonantController_init(config_1);
	self->resonant_2 = uz_resonantController_init(config_2);
	self->config = config;
	return (self);
}

static void uz_subspace_resonant_control_step_controllers_general(uz_subspace_resonant_control* self, float actual1, float actual2, float ref1, float ref2, float* out1, float* out2, float omega_el_fundamental){
    *out1 = uz_resonantController_step(self->resonant_1, ref1, actual1, omega_el_fundamental);
    *out2 = uz_resonantController_step(self->resonant_2, ref2, actual2, omega_el_fundamental);
}

uz_3ph_dq_t uz_subspace_resonant_control_step_dq(uz_subspace_resonant_control* self, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t i_actual_Ampere, float omega_el_fundamental){
    uz_3ph_dq_t out;
    out.zero = 0.0f;
    uz_subspace_resonant_control_step_controllers_general(self, i_actual_Ampere.d, i_actual_Ampere.q, i_reference_Ampere.d, i_reference_Ampere.q, &out.d, &out.q, omega_el_fundamental);
    return out;
}

uz_3ph_alphabeta_t uz_subspace_resonant_control_step_alphabeta(uz_subspace_resonant_control* self, uz_3ph_alphabeta_t i_reference_Ampere, uz_3ph_alphabeta_t i_actual_Ampere, float omega_el_fundamental){
    uz_3ph_alphabeta_t out;
    out.gamma = 0.0f;
    uz_subspace_resonant_control_step_controllers_general(self, i_actual_Ampere.alpha, i_actual_Ampere.beta, i_reference_Ampere.alpha, i_reference_Ampere.beta, &out.alpha, &out.beta, omega_el_fundamental);
    return out;
}

void uz_subspace_resonant_control_reset(uz_subspace_resonant_control* self){
    uz_resonantController_reset(self->resonant_1);
    uz_resonantController_reset(self->resonant_2);
}
#endif
