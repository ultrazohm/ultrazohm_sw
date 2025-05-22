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

#include "../uz/uz_global_configuration.h"
#if UZ_FLUSSSCHAETZER_MAX_INSTANCES > 0U
#include "Flussschaetzer_ert_rtw/Flussschaetzer.h"
#include <stdbool.h>
#include "uz_flussschaetzer.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
struct uz_Flussschaetzer_t
{

	  ExtU_Flussschaetzer input;
	  ExtY_Flussschaetzer outputs;
	  DW_Flussschaetzer dwork;
	  RT_MODEL_Flussschaetzer modelData;
	  RT_MODEL_Flussschaetzer *PtrToModelData;
	  bool is_ready;
};

static uint32_t instances_counter_Flussschaetzer = 0;

static uz_Flussschaetzer_t instances_Flussschaetzer[UZ_FLUSSSCHAETZER_MAX_INSTANCES] = {0};

static uz_Flussschaetzer_t *uz_Flussschaetzer_allocation(void);

static uz_Flussschaetzer_t *uz_Flussschaetzer_allocation(void)
{
    uz_assert(instances_counter_Flussschaetzer < UZ_FLUSSSCHAETZER_MAX_INSTANCES);
    uz_Flussschaetzer_t *self = &instances_Flussschaetzer[instances_counter_Flussschaetzer];
    uz_assert(self->is_ready == false);
    instances_counter_Flussschaetzer++;
    self->is_ready = true;
    return (self);
}

uz_Flussschaetzer_t *uz_Flussschaetzer_init(struct uz_Flussschaetzer_config config)
{
    uz_Flussschaetzer_t *self = uz_Flussschaetzer_allocation();
    self->PtrToModelData = &self->modelData;
    self->PtrToModelData->dwork = &self->dwork;
    self->PtrToModelData->inputs = &self->input;
    self->PtrToModelData->outputs = &self->outputs;
    Flussschaetzer_initialize(self->PtrToModelData);


    return (self);
}

Flussschaetzer_output_data uz_Flussschaetzer_step(uz_Flussschaetzer_t *self,uz_3ph_alphabeta_t u_alphabeta_ref,uz_3ph_alphabeta_t i_alphabeta_meas,float integrator_reset)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    self->input.u_alphabeta[0] = u_alphabeta_ref.alpha;
    self->input.u_alphabeta[1] = u_alphabeta_ref.beta;
    self->input.u_alphabeta[2] = u_alphabeta_ref.gamma;
    self->input.i_alphabeta[0] = i_alphabeta_meas.alpha;
    self->input.i_alphabeta[1] = i_alphabeta_meas.beta;
    self->input.i_alphabeta[2] = i_alphabeta_meas.gamma;
    self->input.integrator_reset = integrator_reset;

    Flussschaetzer_step(self->PtrToModelData);
    Flussschaetzer_output_data out;
    	 out.theta_el_kor = self->outputs.theta_el_kor;
    	 out.omega_m_est = self->outputs.omega_m_est;
    	 out.psi_beta_filt = self ->outputs.psi_alpha_filt;
    	 out.psi_alpha_filt = self->outputs.psi_alpha_filt;
    	 out.theta_el_est = self->outputs.theta_el_est;
    	 out.psi_beta = self->outputs.psi_beta;
    	 out.psi_alpha = self->outputs.psi_alpha;
    	 out.omega_el_raw = self->outputs.omega_el_raw;
        return out;

}

void uz_Flussschaetzer_reset(uz_Flussschaetzer_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_3ph_alphabeta_t u_alphabeta_ref = {0,0,0};
    uz_3ph_alphabeta_t i_alphabeta_meas = {0,0,0};
   uz_Flussschaetzer_step(self, u_alphabeta_ref, i_alphabeta_meas,1);

}

Flussschaetzer_output_data uz_Flussschaetzer_get_output(uz_Flussschaetzer_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    Flussschaetzer_output_data out;
	 out.theta_el_kor = self->outputs.theta_el_kor;
	 out.omega_m_est = self->outputs.omega_m_est;
	 out.psi_beta_filt = self ->outputs.psi_alpha_filt;
	 out.psi_alpha_filt = self->outputs.psi_alpha_filt;
	 out.theta_el_est = self->outputs.theta_el_est;
	 out.psi_beta = self->outputs.psi_beta;
	 out.psi_alpha = self->outputs.psi_alpha;
    return out;
}

void uz_Flussschaetzer_set_config(uz_Flussschaetzer_t *self, struct uz_Flussschaetzer_config config)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);



}



#endif
