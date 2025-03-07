/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2022 Josef Knoblach
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

#include "../uz_global_configuration.h"
#if UZ_RESONANT_CONTROLLER_MAX_INSTANCES > 0U
#include "Resonant_Controller_ert_rtw/Resonant_Controller.h"
#include <stdbool.h>
#include "uz_resonant_controller.h"
#include "../uz_HAL.h"

struct uz_resonantController_t
{
    ExtU_Resonant_Controller_T input;  /**< Input struct of the resonant controller*/
    ExtY_Resonant_Controller_T output; /**< Output struct of the resonant controller*/
    DW_Resonant_Controller_T dwork;
    RT_MODEL_Resonant_Controller_T modelData;
    RT_MODEL_Resonant_Controller_T *PtrToModelData;
    bool is_ready;
};

static uint32_t instances_counter_ResonantController = 0;

static uz_resonantController_t instances_ResonantController[UZ_RESONANT_CONTROLLER_MAX_INSTANCES] = {0};

static uz_resonantController_t *uz_ResonantController_allocation(void);

static uz_resonantController_t *uz_ResonantController_allocation(void)
{
    uz_assert(instances_counter_ResonantController < UZ_RESONANT_CONTROLLER_MAX_INSTANCES);
    uz_resonantController_t *self = &instances_ResonantController[instances_counter_ResonantController];
    uz_assert(self->is_ready == false);
    instances_counter_ResonantController++;
    self->is_ready = true;
    return (self);
}

uz_resonantController_t *uz_resonantController_init(struct uz_resonantController_config config)
{
    uz_resonantController_t *self = uz_ResonantController_allocation();
    self->PtrToModelData = &self->modelData;
    self->PtrToModelData->dwork = &self->dwork;
    self->PtrToModelData->inputs = &self->input;
    self->PtrToModelData->outputs = &self->output;
    Resonant_Controller_initialize(self->PtrToModelData);

    uz_assert(config.sampling_time >= 0.0f);
    uz_assert(config.upper_limit > config.lower_limit);
    uz_assert(config.lower_limit < config.upper_limit);

    self->input.T_sw = config.sampling_time;
    self->input.VR = config.gain;
    self->input.h = config.harmonic_order;
    self->input.omega_el = config.fundamental_frequency;
    self->input.lower_limit = config.lower_limit;
    self->input.upper_limit = config.upper_limit;
    self->input.Klim = config.antiwindup_gain;
    self->input.in_ref = config.in_reference_value;
    self->input.in_m = config.in_measured_value;
    return (self);
}

float uz_resonantController_step(uz_resonantController_t *self, float in_ref, float in_m, float omega_el)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input.in_ref = in_ref;
    self->input.in_m = in_m;
    self->input.omega_el = omega_el;
    Resonant_Controller_step(self->PtrToModelData);
    return self->output.out;
}

void uz_resonantController_reset(uz_resonantController_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->PtrToModelData->inputs->Reset = 1.0f;
    self->PtrToModelData->inputs->in_m = 0.0f;
    self->PtrToModelData->inputs->in_ref = 0.0f;
    Resonant_Controller_step(self->PtrToModelData);
    self->PtrToModelData->inputs->Reset = 0.0f;
}

float uz_resonantController_get_output(uz_resonantController_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->output.out;
}

void uz_resonantController_set_config(uz_resonantController_t *self, struct uz_resonantController_config config)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(config.sampling_time >= 0.0f);
    uz_assert(config.upper_limit > config.lower_limit);
    uz_assert(config.lower_limit < config.upper_limit);

    self->input.T_sw = config.sampling_time;
    self->input.VR = config.gain;
    self->input.h = config.harmonic_order;
    self->input.omega_el = config.fundamental_frequency;
    self->input.lower_limit = config.lower_limit;
    self->input.upper_limit = config.upper_limit;
    self->input.Klim = config.antiwindup_gain;
    self->input.in_ref = config.in_reference_value;
    self->input.in_m = config.in_measured_value;
}

void uz_resonantController_set_gain(uz_resonantController_t *self, float gain){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(gain > 0.0f);
    self->input.VR = gain;
}

void uz_resonantController_set_harmonic_order(uz_resonantController_t *self, float harmonic_order){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(harmonic_order > 0.0f);
    self->input.h = harmonic_order;
}

#endif
