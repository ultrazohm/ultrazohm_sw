/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Tobias Schindler, Valentin Hoppe
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

#include "uz_EncOffEst.h"
#include "../uz_global_configuration.h"
#if UZ_ENCOFFEST_MAX_INSTANCES > 0

enum encoderoffset_states
{
    encoderoffset_init = 0,
    encoderoffset_accelerate,
    encoderoffset_i0,
    encoderoffset_measurement,
};

typedef struct uz_EncOffEst_t {
    uz_filter_cumulativeavg_t *filter_i_d;
    uz_filter_cumulativeavg_t *filter_i_q;
    uz_filter_cumulativeavg_t *filter_u_d;
    uz_filter_cumulativeavg_t *filter_u_q;
    uz_filter_cumulativeavg_t *filter_omega_el;
    actualValues *actual;
    uz_3ph_dq_t i_filtered;
    uz_3ph_dq_t u_filtered;
    float omega_el_filtered;
    uz_3ph_dq_t i_reference_Ampere;
    float init_time;
    enum encoderoffset_states encoderoffset_current_state;
    bool state_machine_finished;
    float max_speed;
    uz_3ph_dq_t psi_measured_pos;
    uz_3ph_dq_t psi_measured_neg;
}uz_EncOffEst_t;

static uint32_t instances_counter_EncOffEst = 0;

static uz_EncOffEst_t instances_EncOffEst[UZ_ENCOFFEST_MAX_INSTANCES] = {0};
static uz_EncOffEst_t* uz_EncOffEst_allocation(void);
static void uz_EncOffEst_statemaschine_init(uz_EncOffEst_t* self);
static void uz_EncOffEst_statemaschine_accelerate(uz_EncOffEst_t* self, float setp_current);
static void uz_EncOffEst_statemaschine_i0(uz_EncOffEst_t* self);

static uz_EncOffEst_t* uz_EncOffEst_allocation(void) {
	uz_assert(instances_counter_EncOffEst < UZ_ENCOFFEST_MAX_INSTANCES);
	uz_EncOffEst_t* self = &instances_EncOffEst[instances_counter_EncOffEst];
	uz_assert(self->is_ready == false);
	instances_counter_EncOffEst++;
	self->is_ready = true;
	return (self);
}

uz_EncOffEst_t* uz_EncOffEst_init(struct uz_CurrentControl_config config) {
	uz_EncOffEst_t* self = uz_EncOffEst_allocation();
	self->filter_i_d = uz_filter_cumulativeavg_init();
    self->filter_i_q = uz_filter_cumulativeavg_init();
    self->filter_u_d = uz_filter_cumulativeavg_init();
    self->filter_u_q = uz_filter_cumulativeavg_init();
    self->filter_omega_el = uz_filter_cumulativeavg_init();
    self->actual = config->actual;
    self->i_filtered = {0};
    self->u_filtered = {0};
    self->omega_el_filtered = 0.0f;
    self->i_reference_Ampere = {0};
    self->init_time = 0.0f;
    self->encoderoffset_current_state = encoderoffset_init;
    self->state_machine_finished = false;
    self->max_speed = 0.0f;
    self->psi_measured_pos = {0};
    self->psi_measured_neg = {0};
	return (self);
}

void step_theta_off(uz_EncOffEst_t* self){
    geteUdUq_thetaOff(self, 100.0f, &self->psi_measured_pos);
    geteUdUq_thetaOff(self, -100.0f, &self->psi_measured_neg);
}

void geteUdUq_thetaOff(uz_EncOffEst_t* self, float setp_current, uz_3ph_dq_t *psi_measured){
    switch (encoderoffset_current_state)
    {
        case encoderoffset_init:{
            uz_EncOffEst_statemaschine_init(self);
            break;
        }
        case encoderoffset_accelerate:{
            uz_EncOffEst_statemaschine_accelerate(self, setp_current);
            break;
        }
        case encoderoffset_i0:{
            uz_EncOffEst_statemaschine_i0(self);
            break;
        }
        case encoderoffset_measurement:{
            psi_measured->d = self->u_filtered.q/self->omega_el_filtered;
    	    psi_measured->q = -1.0f*self->u_filtered.d/self->omega_el_filtered;
    	    self->state_machine_finished=true;
    	    self->encoderoffset_current_state=encoderoffset_init;
            break;
        }
        default: break;
    }
}

static void uz_EncOffEst_statemaschine_init(uz_EncOffEst_t* self){
    self->state_machine_finished = false;
    uz_filter_cumulativeavg_reset(self->filter_i_d);
    uz_filter_cumulativeavg_reset(self->filter_i_q);
    uz_filter_cumulativeavg_reset(self->filter_u_d);
    uz_filter_cumulativeavg_reset(self->filter_u_q);
    uz_filter_cumulativeavg_reset(self->filter_omega_el);
    self->i_reference_Ampere.q = 0.0f;
    self->i_reference_Ampere.d = 0.0f;
    self->init_time = uz_SystemTime_GetGlobalTimeInSec();
    self->encoderoffset_current_state = encoderoffset_accelerate;
}

static void uz_EncOffEst_statemaschine_accelerate(uz_EncOffEst_t* self, float setp_current){
    self->i_reference_Ampere.q = setp_current;
    float new_time = uz_SystemTime_GetGlobalTimeInSec();
    if( (new_time - self->init_time) > 1.0f && (fabsf(self->actual->mechanicalRotorSpeed)>100.0f)){
        self->max_speed = fabsf(self->actual->mechanicalRotorSpeed); // measure max speed
        self->encoderoffset_current_state = encoderoffset_i0;
    }
}

static void uz_EncOffEst_statemaschine_i0(uz_EncOffEst_t* self){
    self->i_reference_Ampere.q = 0.0f;
    self->i_reference_Ampere.d = 0.0f;
    if ( ( fabsf(self->actual->mechanicalRotorSpeed) > 0.3f*self->max_speed) && ( fabsf(self->actual->mechanicalRotorSpeed) < 0.8f*self->max_speed)  ) {// measure as long as omega_el is not zero
        // measure
        self->i_filtered.q = uz_filter_cumulativeavg_step(self->filter_i_q, self->actual->I_q);
        self->i_filtered.d = uz_filter_cumulativeavg_step(self->filter_i_d, self->actual->I_d);
        self->u_filtered.d = uz_filter_cumulativeavg_step(self->filter_u_d, self->actual->U_d);
        self->u_filtered.q = uz_filter_cumulativeavg_step(self->filter_u_q, self->actual->U_q);
        self->omega_el_filtered = uz_filter_cumulativeavg_step(self->filter_omega_el, el_speed);
    }
    if( fabsf(self->actual->mechanicalRotorSpeed) < 0.15f*self->max_speed){
        self->encoderoffset_current_state = encoderoffset_measurement; // measurement is finished
    }
}


#endif