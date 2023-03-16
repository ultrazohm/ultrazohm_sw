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

#define OFFSET_RANGE_RAD 0.5f
#define OFFSET_STEP_RAD 0.1f
#define OFFSET_ARRAYSIZE ((uint16_t) 2U*OFFSET_RANGE_RAD/OFFSET_STEP_RAD)

enum encoderoffset_states_low_level
{
    encoderoffset_ll_init = 0,
    encoderoffset_ll_accelerate,
    encoderoffset_ll_measurement,
    encoderoffset_ll_finished
};

enum encoderoffset_states_high_level
{
    encoderoffset_init = 0,
    init_theta,
    positive_setpoint,
    negative_setpoint,
    change_theta,
    encoderoffset_finished
};

struct measurement{
    float theta_offset;
    float psi_d_positive;
    float psi_d_negative;
};


typedef struct uz_EncOffEst_t {
    bool is_ready;
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
    enum encoderoffset_states_low_level encoderoffset_current_state_ll;
    enum encoderoffset_states_high_level encoderoffset_current_state_hl;
    bool state_machine_finished;
    float max_speed;
    uz_3ph_dq_t psi_measured_pos;
    uz_3ph_dq_t psi_measured_neg;
    float setpoint_current;
    float theta_offset_inital;
    struct measurement measurement[10U];
}uz_EncOffEst_t;


static uint32_t instances_counter_EncOffEst = 0;

static uz_EncOffEst_t instances_EncOffEst[UZ_ENCOFFEST_MAX_INSTANCES] = {0};
static uz_EncOffEst_t* uz_EncOffEst_allocation(void);
static float uz_EncOffEst_single_direction(uz_EncOffEst_t* self, float setp_current);
static void uz_EncOffEst_statemaschine_init(uz_EncOffEst_t* self);
static void uz_EncOffEst_statemaschine_accelerate(uz_EncOffEst_t* self, float setp_current);
static float uz_EncOffEst_statemaschine_measurement(uz_EncOffEst_t* self);

static uz_EncOffEst_t* uz_EncOffEst_allocation(void) {
	uz_assert(instances_counter_EncOffEst < UZ_ENCOFFEST_MAX_INSTANCES);
	uz_EncOffEst_t* self = &instances_EncOffEst[instances_counter_EncOffEst];
	uz_assert(self->is_ready == false);
	instances_counter_EncOffEst++;
	self->is_ready = true;
	return (self);
}

uz_EncOffEst_t* uz_EncOffEst_init(struct uz_EncOffEst_config config) {
	uz_EncOffEst_t* self = uz_EncOffEst_allocation();
	self->filter_i_d = uz_filter_cumulativeavg_init();
    self->filter_i_q = uz_filter_cumulativeavg_init();
    self->filter_u_d = uz_filter_cumulativeavg_init();
    self->filter_u_q = uz_filter_cumulativeavg_init();
    self->filter_omega_el = uz_filter_cumulativeavg_init();
    self->actual = config.actual;
    self->omega_el_filtered = 0.0f;
    self->init_time = 0.0f;
    self->encoderoffset_current_state_ll = encoderoffset_ll_init;
    self->state_machine_finished = false;
    self->max_speed = 0.0f;
	return (self);
}

bool uz_EncOffEst_step(uz_EncOffEst_t* self){
    static struct measurement temp = {0};
    static uint16_t i = 0U;
    switch(self->encoderoffset_current_state_hl)
    {
        case init_theta:
        {
            self->i_reference_Ampere.d = self->setpoint_current;
            self->init_time = uz_SystemTime_GetGlobalTimeInSec();
            if((uz_SystemTime_GetGlobalTimeInSec() - self->init_time) > 1.0f)
            {
                self->theta_offset_inital = self->actual->theta_elec;
                self->actual->theta_offset = self->actual->theta_elec - OFFSET_RANGE_RAD;
            }
            self->encoderoffset_current_state_hl = positive_setpoint;
            break;
        }
        case positive_setpoint:
        {
            temp.psi_d_positive = uz_EncOffEst_single_direction(self, self->setpoint_current);
            break;
        }
        case negative_setpoint:
        {
            temp.psi_d_negative = uz_EncOffEst_single_direction(self, -self->setpoint_current);
            break;
        }
        case change_theta:
        {
            self->measurement[i] = temp;
            if(i < OFFSET_ARRAYSIZE){
                self->actual->theta_offset = self->actual->theta_offset + OFFSET_STEP_RAD;
                i++;
            }
            else{
                self->encoderoffset_current_state_hl = encoderoffset_finished;
            }
            break;
        }
        default: break;
    }
    return true;
}

static float uz_EncOffEst_single_direction(uz_EncOffEst_t* self, float setp_current){
    float psi_d = 0.0f;
    switch (self->encoderoffset_current_state_ll)
    {
        case encoderoffset_ll_init:{
            uz_EncOffEst_statemaschine_init(self);
            break;
        }
        case encoderoffset_ll_accelerate:{
            uz_EncOffEst_statemaschine_accelerate(self, setp_current);
            break;
        }
        case encoderoffset_ll_measurement:{
            psi_d = uz_EncOffEst_statemaschine_measurement(self);
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
    self->encoderoffset_current_state_ll = encoderoffset_ll_accelerate;
}

static void uz_EncOffEst_statemaschine_accelerate(uz_EncOffEst_t* self, float setp_current){
    self->i_reference_Ampere.q = setp_current;
    if( (uz_SystemTime_GetGlobalTimeInSec() - self->init_time) > 1.0f && (fabsf(self->actual->mechanicalRotorSpeed)>100.0f)){
        self->max_speed = fabsf(self->actual->mechanicalRotorSpeed); // measure max speed
        self->encoderoffset_current_state_ll = encoderoffset_ll_measurement;
    }
}

static float uz_EncOffEst_statemaschine_measurement(uz_EncOffEst_t* self){
    float psi_d = 0.0f;
    self->i_reference_Ampere.q = 0.0f;
    self->i_reference_Ampere.d = 0.0f;
    if ( ( fabsf(self->actual->mechanicalRotorSpeed) > 0.3f*self->max_speed) && ( fabsf(self->actual->mechanicalRotorSpeed) < 0.8f*self->max_speed)  ) {// measure as long as omega_el is not zero
        // measure
        self->i_filtered.q = uz_filter_cumulativeavg_step(self->filter_i_q, self->actual->I_q);
        self->i_filtered.d = uz_filter_cumulativeavg_step(self->filter_i_d, self->actual->I_d);
        self->u_filtered.d = uz_filter_cumulativeavg_step(self->filter_u_d, self->actual->U_d);
        self->u_filtered.q = uz_filter_cumulativeavg_step(self->filter_u_q, self->actual->U_q);
        self->omega_el_filtered = uz_filter_cumulativeavg_step(self->filter_omega_el, 0.0f);
    }else if(fabsf(self->actual->mechanicalRotorSpeed) < 0.15f*self->max_speed){
        psi_d = self->u_filtered.q/self->omega_el_filtered;
        self->encoderoffset_current_state_ll = encoderoffset_ll_finished;
    }
    return psi_d;
}


#endif