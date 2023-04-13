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

#include "uz_encoder_offset_estimation.h"
#include "../uz_global_configuration.h"
#if UZ_ENCODER_OFFSET_ESTIMATION_MAX_INSTANCES > 0

#define OFFSET_RANGE_RAD 0.25f
#define OFFSET_STEP_RAD 0.01f
#define OFFSET_ARRAYSIZE ((uint16_t) (2U*OFFSET_RANGE_RAD/OFFSET_STEP_RAD))
#define OFFSET_DELAY_BETWEEN_SETPOINTS_SEC 1.0f
#define OFFSET_DELAY_REACH_SPEED_SEC 1.0f

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

static const uz_3ph_dq_t zero_dq_struct = {
    .d = 0.0f,
    .q = 0.0f,
    .zero = 0.0f};

typedef struct uz_encoder_offset_estimation_t {
    // general variables
    bool is_ready;                                                          // is ready
    uz_filter_cumulativeavg_t *filter_u_q;                                  // pointer to filter instance
    uz_filter_cumulativeavg_t *filter_omega_el;                             // pointer to filter instance
    enum encoderoffset_states_low_level encoderoffset_current_state_ll;     // current state of substatemachine
    enum encoderoffset_states_high_level encoderoffset_current_state_hl;    // current state of main statemachine
    uz_3ph_dq_t i_reference_Ampere;                                         // seetpoint current to controller
    // inputs from config
    actualValues *actual;
    float polepair;
    float setpoint_current;
    // mainstate variables
    float theta_offset_inital;                                              // initially predetermined encoder offset
    struct measurement meas_array[OFFSET_ARRAYSIZE];                        // measurement array
    uint32_t meas_array_counter;                                            // index for measurements array
    // substate variables
    float sub_init_time;                                                    // init time, set in several states
    float sub_max_speed;                                                    // maximum speed with given current
    float sub_u_q_filtered;                                                 // filtered uq
    float sub_omega_el_filtered;                                            // filtered omega electric
}uz_encoder_offset_estimation_t;


static uint32_t instances_counter_EncOffEst = 0;

static uz_encoder_offset_estimation_t instances_EncOffEst[UZ_ENCODER_OFFSET_ESTIMATION_MAX_INSTANCES] = {0};
static uz_encoder_offset_estimation_t* uz_encoder_offset_estimation_allocation(void);
static float uz_encoder_offset_estimation_single_direction(uz_encoder_offset_estimation_t* self, float setp_current);
static float uz_encoder_offset_estimation_find_best_theta(const struct measurement meas_struct[OFFSET_ARRAYSIZE]);
static void uz_encoder_offset_estimation_reset_substatemachine(uz_encoder_offset_estimation_t* self);

static uz_encoder_offset_estimation_t* uz_encoder_offset_estimation_allocation(void) {
	uz_assert(instances_counter_EncOffEst < UZ_ENCODER_OFFSET_ESTIMATION_MAX_INSTANCES);
	uz_encoder_offset_estimation_t* self = &instances_EncOffEst[instances_counter_EncOffEst];
	uz_assert(self->is_ready == false);
	instances_counter_EncOffEst++;
	self->is_ready = true;
	return (self);
}

uz_encoder_offset_estimation_t* uz_encoder_offset_estimation_init(struct uz_encoder_offset_estimation_config config) {
	uz_encoder_offset_estimation_t* self = uz_encoder_offset_estimation_allocation();
    self->filter_u_q = uz_filter_cumulativeavg_init();
    self->filter_omega_el = uz_filter_cumulativeavg_init();
    self->actual = config.actual;
    self->polepair = config.polepair;
    self->setpoint_current = config.setpoint_current;
    self->encoderoffset_current_state_ll = encoderoffset_ll_init;
    self->encoderoffset_current_state_hl = init_theta;
    self->actual->theta_offset = self->actual->theta_offset - OFFSET_RANGE_RAD;           // use initial offset minus the ranges lower end to start search
    self->i_reference_Ampere = zero_dq_struct;
	return (self);
}

uz_3ph_dq_t uz_encoder_offset_estimation_step(uz_encoder_offset_estimation_t* self){
    switch(self->encoderoffset_current_state_hl){
        case init_theta:{
            self->encoderoffset_current_state_hl = positive_setpoint;                           // activate next state
            break;
        }
        case positive_setpoint:{
            self->meas_array[self->meas_array_counter].psi_d_positive = uz_encoder_offset_estimation_single_direction(self, self->setpoint_current);  // get psi with positive direction rotation
            if(self->encoderoffset_current_state_ll == encoderoffset_ll_finished){              // if substatemachine is finished
                self->encoderoffset_current_state_ll = encoderoffset_ll_init;                   // set substatemachine back to init
                self->encoderoffset_current_state_hl = negative_setpoint;                       // activate next step
            }
            break;
        }
        case negative_setpoint:{
            self->meas_array[self->meas_array_counter].psi_d_negative = uz_encoder_offset_estimation_single_direction(self, -self->setpoint_current); // get psi with negative direction rotation
            if(self->encoderoffset_current_state_ll == encoderoffset_ll_finished){              // if substatemachine is finished
                self->encoderoffset_current_state_ll = encoderoffset_ll_init;                   // set substatemachine back to init
                self->encoderoffset_current_state_hl = change_theta;                            // activate next step
            }
            break;
        }
        case change_theta:{                               
            self->meas_array[self->meas_array_counter].theta_offset = self->actual->theta_offset;   // safe theta
            if(self->meas_array_counter < OFFSET_ARRAYSIZE){                                    // if not all points are measured yet
                self->actual->theta_offset = self->actual->theta_offset + OFFSET_STEP_RAD;      // step up theta offset
                self->meas_array_counter++;                                                     // step up index                                                      
                self->encoderoffset_current_state_hl = positive_setpoint;                       // back to positive speed
                self->encoderoffset_current_state_ll = encoderoffset_ll_init;                   // set substatemachine back init
            } else{
                self->actual->theta_offset = uz_encoder_offset_estimation_find_best_theta(self->meas_array);
                self->encoderoffset_current_state_hl = encoderoffset_finished;                  // if all points are measured, get to finished state
            }
            break;
        }
        default: break;
    }
    return (self->i_reference_Ampere);
}

bool uz_encoder_offset_estimation_get_finished(uz_encoder_offset_estimation_t* self){
    if(self->encoderoffset_current_state_hl == encoderoffset_finished){
        return true;
    } else{
        return false;
    }
}

static float uz_encoder_offset_estimation_find_best_theta(const struct measurement meas_struct[OFFSET_ARRAYSIZE]){
    float min_diff = INFINITY;
    uint16_t index_min_diff = 0U;
    for(uint16_t i = 0U; i < OFFSET_ARRAYSIZE; i++){
        if((float)(fabs(meas_struct[i].psi_d_positive-meas_struct[i].psi_d_negative)) < min_diff){
            index_min_diff = i;
            min_diff = (float)(fabs(meas_struct[i].psi_d_positive-meas_struct[i].psi_d_negative));
        }
    }
    return (meas_struct[index_min_diff].theta_offset);
}

static void uz_encoder_offset_estimation_reset_substatemachine(uz_encoder_offset_estimation_t* self){
    self->sub_init_time = 0.0f;
    self->sub_max_speed = 0.0f;
    self->sub_u_q_filtered = 0.0f;
    self->sub_omega_el_filtered = 0.0f;
}

static float uz_encoder_offset_estimation_single_direction(uz_encoder_offset_estimation_t* self, const float setp_current){
    float psi_d = 0.0f;
    switch (self->encoderoffset_current_state_ll){
        case encoderoffset_ll_init:{
            uz_filter_cumulativeavg_reset(self->filter_u_q);                    // reset filter
            uz_filter_cumulativeavg_reset(self->filter_omega_el);               // reset filter
            self->i_reference_Ampere = zero_dq_struct;                          // reset reference
            self->sub_init_time = uz_SystemTime_GetGlobalTimeInSec();           // get init time
            self->encoderoffset_current_state_ll = encoderoffset_ll_accelerate; // set next state
            break;
        }
        case encoderoffset_ll_accelerate:{
            self->i_reference_Ampere.q = setp_current;                               // set reference current
            if((uz_SystemTime_GetGlobalTimeInSec()-self->sub_init_time) > OFFSET_DELAY_REACH_SPEED_SEC && (fabsf(self->actual->mechanicalRotorSpeed)>100.0f)){ //after 1 second and when speed is high enough
                self->sub_max_speed = fabsf(self->actual->mechanicalRotorSpeed);     // measure max speed
                self->encoderoffset_current_state_ll = encoderoffset_ll_measurement; // set next state
            }
            break;
        }
        case encoderoffset_ll_measurement:{
            self->i_reference_Ampere = zero_dq_struct;                                              // reset reference
            self->sub_init_time = 0.0f;                                                             // reset init time
            if ((fabsf(self->actual->mechanicalRotorSpeed) > 0.3f*self->sub_max_speed) && (fabsf(self->actual->mechanicalRotorSpeed) < 0.8f*self->sub_max_speed)  ) {// measure as long as omega_el is not zero
                self->sub_u_q_filtered = uz_filter_cumulativeavg_step(self->filter_u_q, self->actual->U_q); // measure
                self->sub_omega_el_filtered = uz_filter_cumulativeavg_step(self->filter_omega_el, self->actual->mechanicalRotorSpeed * self->polepair * 2.0f * UZ_PIf / 60.0f);    // measure
            }else if(fabsf(self->actual->mechanicalRotorSpeed) < 0.15f*self->sub_max_speed){
                psi_d = self->sub_u_q_filtered/self->sub_omega_el_filtered;                         // calculate psi_d
                self->sub_init_time = uz_SystemTime_GetGlobalTimeInSec();                           // get init time
            }
            if(((uz_SystemTime_GetGlobalTimeInSec()-self->sub_init_time) > OFFSET_DELAY_BETWEEN_SETPOINTS_SEC) && self->sub_init_time != 0.0f){                                                     // wait before next step
                uz_encoder_offset_estimation_reset_substatemachine(self);                                           // set all substate variables to zero
                self->encoderoffset_current_state_ll = encoderoffset_ll_finished;                   // set finished state
            }
            break;
        }
        default: break;
    }
    return psi_d;
}

#endif
