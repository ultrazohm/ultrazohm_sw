/******************************************************************************
 * Copyright Contributors to the UltraZohm project.
 * Copyright 2025 Michael Hoerner
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
 * 
 * Special thanks the Department of Power Electronics and Electrical Drives, Paderborn University 
 * for sharing their implementation of the PLL algorithm.
 ******************************************************************************/

#include "../uz_global_configuration.h"
#if UZ_POS_TO_SPEED_PLL_MAX_INSTANCES > 0U

#include <stdbool.h> 
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "uz_pos_to_speed_pll.h"
#include "uz_codegen_pos_to_speed_pll_ert_rtw/uz_codegen_pos_to_speed_pll.h"

struct uz_pos_to_speed_pll_t {
    bool is_ready;
    ExtY output;
    ExtU input;
    DW rtDW;
    RT_MODEL modelData;
    RT_MODEL *PtrToModelData;
};

static uint32_t instance_counter = 0U;
static uz_pos_to_speed_pll_t instances[UZ_POS_TO_SPEED_PLL_MAX_INSTANCES] = { 0 };

static uz_pos_to_speed_pll_t* uz_pos_to_speed_pll_allocation(void);

static uz_pos_to_speed_pll_t* uz_pos_to_speed_pll_allocation(void){
    uz_assert(instance_counter < UZ_POS_TO_SPEED_PLL_MAX_INSTANCES);
    uz_pos_to_speed_pll_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_pos_to_speed_pll_t* uz_pos_to_speed_pll_init(struct uz_pos_to_speed_pll_config_t config) {
    uz_pos_to_speed_pll_t* self = uz_pos_to_speed_pll_allocation();
    self->PtrToModelData=&self->modelData;
    self->PtrToModelData->dwork=&self->rtDW;
    self->PtrToModelData->inputs=&self->input;
    self->PtrToModelData->outputs=&self->output;
    uz_pos_to_speed_pll_set_config(self, config);
    return(self);
}

void uz_pos_to_speed_pll_set_config(uz_pos_to_speed_pll_t* self, struct uz_pos_to_speed_pll_config_t config) {
    uz_assert(self->is_ready);
    uz_assert(config.machine_polepairs > 0.0f);
    uz_assert(config.kp_pll >= 0.0f);
    uz_assert(config.ki_pll >= 0.0f);
    uz_assert(config.sampling_time_in_seconds > 0.0f);
    self->input.pole_pairs=config.machine_polepairs;
    self->input.kp_pll=config.kp_pll;
    self->input.ki_pll=config.ki_pll;
    self->input.sampling_time_seconds=config.sampling_time_in_seconds;
}

void uz_pos_to_speed_pll_step(uz_pos_to_speed_pll_t* self, float position_mech_si) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(position_mech_si >= 0.0f);
    uz_assert(position_mech_si <= 2.0f*UZ_PIf);
    self->input.position_mech_SI=position_mech_si;
    uz_codegen_pos_to_speed_pll_step(self->PtrToModelData);
}

float uz_pos_to_speed_pll_get_omega_mech_si(uz_pos_to_speed_pll_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->output.omega_mech);
}

float uz_pos_to_speed_pll_get_omega_el_si(uz_pos_to_speed_pll_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->output.omega_el);
}


#endif