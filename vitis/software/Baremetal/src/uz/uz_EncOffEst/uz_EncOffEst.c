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
#define OFFSET_ARRAYSIZE ((uint16_t) (2U*OFFSET_RANGE_RAD/OFFSET_STEP_RAD))

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

static const struct measurement zero_meas_struct = {
    .theta_offset = 0.0f,
    .psi_d_positive = 0.0f,
    .psi_d_negative = 0.0f};

typedef struct uz_EncOffEst_t {
    bool is_ready;
    //uz_filter_cumulativeavg_t *filter_i_d;
    //uz_filter_cumulativeavg_t *filter_i_q;
    //uz_filter_cumulativeavg_t *filter_u_d;
    uz_filter_cumulativeavg_t *filter_u_q;
    uz_filter_cumulativeavg_t *filter_omega_el;
    actualValues *actual;
    //uz_3ph_dq_t i_filtered;
    uz_3ph_dq_t u_filtered;
    float omega_el_filtered;
    uz_3ph_dq_t i_reference_Ampere;
    enum encoderoffset_states_low_level encoderoffset_current_state_ll;
    enum encoderoffset_states_high_level encoderoffset_current_state_hl;
    float setpoint_current;
    float theta_offset_inital;
    struct measurement measurement[OFFSET_ARRAYSIZE];
    float polepair;
}uz_EncOffEst_t;


static uint32_t instances_counter_EncOffEst = 0;

static uz_EncOffEst_t instances_EncOffEst[UZ_ENCOFFEST_MAX_INSTANCES] = {0};
static uz_EncOffEst_t* uz_EncOffEst_allocation(void);
static float uz_EncOffEst_single_direction(uz_EncOffEst_t* self, float setp_current);
static float uz_EncOffEst_find_best_theta(const struct measurement meas_struct[OFFSET_ARRAYSIZE]);

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
	//self->filter_i_d = uz_filter_cumulativeavg_init();
    //self->filter_i_q = uz_filter_cumulativeavg_init();
    //self->filter_u_d = uz_filter_cumulativeavg_init();
    self->filter_u_q = uz_filter_cumulativeavg_init();
    self->filter_omega_el = uz_filter_cumulativeavg_init();
    self->actual = config.actual;
    self->polepair = config.polepair;
    self->setpoint_current = config.setpoint_current;
    self->encoderoffset_current_state_ll = encoderoffset_ll_init;
    self->encoderoffset_current_state_hl = init_theta;
    self->i_reference_Ampere = zero_dq_struct;
	return (self);
}

uz_3ph_dq_t uz_EncOffEst_step(uz_EncOffEst_t* self){
    static float init_time = 0.0f;
    static struct measurement temp = {0};
    static uint16_t i = 0U;
    switch(self->encoderoffset_current_state_hl){
        case init_theta:{ // find initial theta with "wrong" method
            if(init_time == 0.0f){
                init_time = uz_SystemTime_GetGlobalTimeInSec();                                 // get start time
                self->i_reference_Ampere.d = self->setpoint_current;                            // set d-current
            }else if((uz_SystemTime_GetGlobalTimeInSec() - init_time) > 1.0f){                  // after one second
                self->theta_offset_inital = self->actual->theta_elec;                           // safe inital determined offset
                self->actual->theta_offset = self->actual->theta_elec - OFFSET_RANGE_RAD;       // use initial offset minus the ranges lower end to start search
                init_time = 0.0f;                                                               // reset init time
                self->encoderoffset_current_state_ll = encoderoffset_ll_init;                   // set substatemachine back init
                self->encoderoffset_current_state_hl = positive_setpoint;                       // activate next state
            }
            break;
        }
        case positive_setpoint:{
            temp.psi_d_positive = uz_EncOffEst_single_direction(self, self->setpoint_current);  // get psi with positive direction rotation
            if(self->encoderoffset_current_state_ll == encoderoffset_ll_finished){              // if substatemachine is finished
                self->encoderoffset_current_state_ll = encoderoffset_ll_init;                   // set substatemachine back to init
                self->encoderoffset_current_state_hl = negative_setpoint;                       // activate next step
            }
            break;
        }
        case negative_setpoint:{
            temp.psi_d_negative = uz_EncOffEst_single_direction(self, -self->setpoint_current); // get psi with negative direction rotation
            if(self->encoderoffset_current_state_ll == encoderoffset_ll_finished){              // if substatemachine is finished
                self->encoderoffset_current_state_ll = encoderoffset_ll_init;                   // set substatemachine back to init
                self->encoderoffset_current_state_hl = change_theta;                            // activate next step
            }
            break;
        }
        case change_theta:{
            self->measurement[i] = temp;                                                        // safe measurement to array
            if(i < OFFSET_ARRAYSIZE){                                                           // if not all points are measured yet
                self->actual->theta_offset = self->actual->theta_offset + OFFSET_STEP_RAD;      // step up theta offset
                i++;                                                                            // step up index
                temp = zero_meas_struct;                                                        // clean measurement struct
                self->encoderoffset_current_state_hl = positive_setpoint;                       // back to positive speed
                self->encoderoffset_current_state_ll = encoderoffset_ll_init;                   // set substatemachine back init
            } else{
                self->actual->theta_offset = uz_EncOffEst_find_best_theta(self->measurement);
                self->encoderoffset_current_state_hl = encoderoffset_finished;                  // if all points are measured, get to finished state
            }
            break;
        }
        default: break;
    }
    return (self->i_reference_Ampere);
}

bool uz_EncOffEst_get_finished(uz_EncOffEst_t* self){
    if(self->encoderoffset_current_state_hl == encoderoffset_finished){
        return true;
    } else{
        return false;
    }
}

static float uz_EncOffEst_find_best_theta(const struct measurement meas_struct[OFFSET_ARRAYSIZE]){
    float min_diff = INFINITY;
    uint16_t index_min_diff = 0U;
    for(uint16_t i = 0U; i < OFFSET_ARRAYSIZE; i++){
        if(fabs(meas_struct[i].psi_d_positive-meas_struct[i].psi_d_negative) < min_diff){
            index_min_diff = i;
            min_diff = fabs(meas_struct[i].psi_d_positive-meas_struct[i].psi_d_negative);
        }
    }
    return (meas_struct[index_min_diff].theta_offset);
}

static float uz_EncOffEst_single_direction(uz_EncOffEst_t* self, const float setp_current){
    float psi_d = 0.0f;
    static float init_time = 0.0f;
    static float max_speed = 0.0f;
    switch (self->encoderoffset_current_state_ll){
        case encoderoffset_ll_init:{
            //uz_filter_cumulativeavg_reset(self->filter_i_d);                    // reset filter
            //uz_filter_cumulativeavg_reset(self->filter_i_q);                    // reset filter
            //uz_filter_cumulativeavg_reset(self->filter_u_d);                    // reset filter
            uz_filter_cumulativeavg_reset(self->filter_u_q);                    // reset filter
            uz_filter_cumulativeavg_reset(self->filter_omega_el);               // reset filter
            self->i_reference_Ampere = zero_dq_struct;                          // reset reference
            init_time = uz_SystemTime_GetGlobalTimeInSec();                     // get init time
            self->encoderoffset_current_state_ll = encoderoffset_ll_accelerate; // set next state
            break;
        }
        case encoderoffset_ll_accelerate:{
            self->i_reference_Ampere.q = setp_current;                               // set reference current
            if((uz_SystemTime_GetGlobalTimeInSec()-init_time) > 1.0f && (fabsf(self->actual->mechanicalRotorSpeed)>100.0f)){ //after 1 second and when speed is high enough
                max_speed = fabsf(self->actual->mechanicalRotorSpeed);               // measure max speed
                self->encoderoffset_current_state_ll = encoderoffset_ll_measurement; // set next state
            }
            break;
        }
        case encoderoffset_ll_measurement:{
            self->i_reference_Ampere = zero_dq_struct;                                                  // reset reference
            if ((fabsf(self->actual->mechanicalRotorSpeed) > 0.3f*max_speed) && (fabsf(self->actual->mechanicalRotorSpeed) < 0.8f*max_speed)  ) {// measure as long as omega_el is not zero
                //self->i_filtered.q = uz_filter_cumulativeavg_step(self->filter_i_q, self->actual->I_q); // measure
                //self->i_filtered.d = uz_filter_cumulativeavg_step(self->filter_i_d, self->actual->I_d); // measure
                //self->u_filtered.d = uz_filter_cumulativeavg_step(self->filter_u_d, self->actual->U_d); // measure
                self->u_filtered.q = uz_filter_cumulativeavg_step(self->filter_u_q, self->actual->U_q); // measure
                self->omega_el_filtered = uz_filter_cumulativeavg_step(self->filter_omega_el, self->actual->mechanicalRotorSpeed * self->polepair * 2.0f * UZ_PIf / 60.0f);    // measure
            }else if(fabsf(self->actual->mechanicalRotorSpeed) < 0.15f*max_speed){
                psi_d = self->u_filtered.q/self->omega_el_filtered;                                     // calculate psi_d
                self->encoderoffset_current_state_ll = encoderoffset_ll_finished;                       // set finished state
            }
            break;
        }
        default: break;
    }
    return psi_d;
}

#endif