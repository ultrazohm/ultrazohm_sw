#include "uz_ParameterID_rc.h"

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_RC_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"


struct uz_parameterID_rc_t {
    bool is_ready;
    bool first_call;
    enum rc_state rc_state;
    enum rc_state rc_previous_state;
    struct uz_parameterID_rc_max_steps_t max_steps;
    struct uz_parameterID_rc_config_t internal_config;
    struct uz_parameterID_rc_ref_val_t output_ref_values; 
    struct uz_parameterID_rc_set_values_t set_values;
    struct uz_parameterid_rc_counter_t counter;
    struct uz_parameterid_rc_size_increments_t stepsize_increment;
};

static uint32_t instance_counter = 0U;
static uz_parameterID_rc_t instances[UZ_PARAMETERID_RC_MAX_INSTANCES] = { 0 };

static uz_parameterID_rc_t* uz_parameterID_rc_allocation(void);

static uz_parameterID_rc_t* uz_parameterID_rc_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_RC_MAX_INSTANCES);
    uz_parameterID_rc_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_parameterID_rc_t* uz_parameterID_rc_init(struct uz_parameterID_rc_config_t initial_config) {
    uz_parameterID_rc_t* self = uz_parameterID_rc_allocation();
    self->internal_config = initial_config;
    self->first_call = true;
    self->rc_state = rc_idle;
    self->rc_previous_state = rc_idle;
    self->max_steps.id = self->internal_config.id_steps + 1U;
    self->max_steps.iq = self->internal_config.iq_steps + 1U;
    self->counter.increment_id = 0U;
    self->counter.increment_iq = 0U;
    self->counter.increment_n = 0U;
    uz_assert(self->internal_config.id_start_Amps <= 0.0f && self->internal_config.id_stop_Amps <= 0.0f);
    uz_assert(self->internal_config.id_start_Amps > self->internal_config.id_stop_Amps);
    uz_assert(self->internal_config.iq_start_Amps < self->internal_config.iq_stop_Amps);
    return (self);
}

struct uz_parameterID_rc_config_t uz_parameterID_rc_get_config(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->internal_config;
}

struct uz_parameterid_rc_counter_t uz_parameterID_rc_get_counter(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->counter;
}

uz_parameterID_rc_t* uz_parameterID_rc_get_all(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self;
}

struct uz_parameterID_rc_ref_val_t uz_parameterID_rc_generate_idq_ref(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    if(self->first_call){
        self->set_values.id_set_Amps = 0.0f;
        self->set_values.iq_set_Amps = 0.0f;
        self->set_values.n_set_rpm = self->internal_config.n_start_rpm;
        self->first_call = false;
        self->counter.isr ++;
        self->rc_state = rc_wait;
    } else {
        self->counter.isr++;

        switch (self->rc_state)
        {
        case rc_set_idq:
            self->set_values.id_set_Amps = self->internal_config.id_start_Amps + self->counter.increment_id * self->stepsize_increment.id_Amps;
            self->set_values.iq_set_Amps = self->internal_config.iq_start_Amps + self->counter.increment_iq * self->stepsize_increment.iq_Amps;
            self->rc_previous_state = self->rc_state;
            self->rc_state = rc_wait;
            
            break;
        
        case rc_wait: 
            self->counter.wait++;
            if(self->counter.wait == 2000U){
                if (self->rc_previous_state == rc_set_idq){
                    self->rc_state = rc_sample_on;
                }
                else if (self->rc_previous_state == rc_sample_on){
                    self->rc_state = rc_sample_off;
                }
                self->counter.wait = 0U;
            }
            break;

        case rc_sample_on:
            self->output_ref_values.data_valid = true; 
            self->rc_previous_state = self->rc_state;
            self->rc_state = rc_wait;
        break;

        case rc_sample_off:
            self->output_ref_values.data_valid = false; 
            self->rc_previous_state = self->rc_state;
            self->rc_state = rc_increment;
        break;
        
        case rc_increment:
            uz_parameterID_rc_set_next_workingpoint(self);
            self->rc_state = rc_set_idq;
        break;

        case rc_finished:
            break; 

        default:
            break;
        }
    }

self->output_ref_values.id_ref_Amps = self->set_values.id_set_Amps;
self->output_ref_values.iq_ref_Amps = self->set_values.iq_set_Amps;
self->output_ref_values.n_ref_rpm = self->set_values.n_set_rpm;
return self->output_ref_values;

}

void uz_parameterID_rc_set_next_workingpoint(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->counter.working_points ++;
    if (self->counter.working_points == (self->max_steps.id* self->max_steps.iq)){
        self->rc_state = rc_finished;
        self->counter.increment_id = 0U;
        self->counter.increment_iq = 0U;
    } else
        self->counter.increment_id ++;
        if (self->counter.increment_id > self->internal_config.id_steps){
            self->counter.increment_id = 0U;
            self->counter.increment_iq ++;
        } 
    
}

#endif