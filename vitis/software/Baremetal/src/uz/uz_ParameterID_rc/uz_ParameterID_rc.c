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
    enum rc_mode rc_mode;
    struct uz_parameterID_rc_max_steps_t max_increment_counter;
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
    self->max_increment_counter.motor = (self->internal_config.id_steps + 1U) * (self->internal_config.iq_steps + 1U);
    self->max_increment_counter.generator = 2U * (self->internal_config.id_steps + 1U) * (self->internal_config.iq_steps + 1U);
    self->stepsize_increment.id_Amps = (self->internal_config.id_stop_Amps - self->internal_config.id_start_Amps)/self->internal_config.id_steps;  
    self->stepsize_increment.iq_Amps = (self->internal_config.iq_stop_Amps - self->internal_config.iq_start_Amps)/self->internal_config.iq_steps;
    self->stepsize_increment.n_rpm = (self->internal_config.n_stop_rpm - self->internal_config.n_start_rpm)/self->internal_config.n_steps;
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
        self->rc_mode = motor;
        self->counter.isr ++;
        self->rc_state = rc_wait;
        self->rc_previous_state = rc_idle;
    } else {
        self->counter.isr++;

        switch (self->rc_state)
        {
        case rc_set_idq:
            self->set_values.id_set_Amps = self->internal_config.id_start_Amps + self->counter.increment_id * self->stepsize_increment.id_Amps;
            if (self->rc_mode == motor){
                self->set_values.iq_set_Amps = self->internal_config.iq_start_Amps + self->counter.increment_iq * self->stepsize_increment.iq_Amps;
            } else if (self->rc_mode == generator) {
                self->set_values.iq_set_Amps = self->internal_config.iq_start_Amps - self->counter.increment_iq * self->stepsize_increment.iq_Amps;
            }
            
            self->rc_previous_state = self->rc_state;
            self->rc_state = rc_wait;
            break;
        
        case rc_wait: 
            self->counter.wait++;
            if(self->counter.wait == 1U){
                if (self->rc_previous_state == rc_set_idq){
                    self->rc_state = rc_sample_on;
                }
                else if (self->rc_previous_state == rc_sample_on){
                    self->rc_state = rc_sample_off;
                } else if (self->rc_previous_state == rc_idle){
                    self->rc_state = rc_set_idq;
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
            self->rc_state = rc_increment_idq;
        break;
        
        case rc_increment_idq:
            uz_parameterID_rc_set_next_operating_point_idq(self);
        break;

        case rc_increment_n:
            uz_parameterID_rc_set_next_operating_point_n(self);
        break;

        case rc_finished:
        self->set_values.id_set_Amps = 0.0f;
        self->set_values.iq_set_Amps = 0.0f;
        self->set_values.n_set_rpm = 0.0f;
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


// increases either idq for the next operating point 
void uz_parameterID_rc_set_next_operating_point_idq(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->counter.operating_points_idq < self->max_increment_counter.generator);
    self->counter.operating_points_idq ++;
    if (self->counter.operating_points_idq == self->max_increment_counter.motor){
        self->rc_mode = generator;
        self->rc_state = rc_set_idq;
        self->counter.increment_id = 0U;
        self->counter.increment_iq = 0U;
    } else if (self->counter.operating_points_idq == self->max_increment_counter.generator) {
            self->rc_state = rc_increment_n;
            self->counter.increment_id = 0U;
            self->counter.increment_iq = 0U;
            self->counter.operating_points_idq = 0U;
    } else {
        self->counter.increment_id ++;
        self->rc_state = rc_set_idq;
        if (self->counter.increment_id > self->internal_config.id_steps){
            self->counter.increment_id = 0U;
            self->counter.increment_iq ++;
        }    
    }
}

void uz_parameterID_rc_set_next_operating_point_n(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    if (self->internal_config.n_steps == 0U)
    {
        self->rc_state = rc_finished;
    } else{
        self->counter.operating_points_n ++;
        self->set_values.n_set_rpm = self->internal_config.n_start_rpm + self->counter.operating_points_n * self->stepsize_increment.n_rpm;
        self->set_values.id_set_Amps = 0.0f;
        self->set_values.iq_set_Amps = 0.0f;
        self->rc_state = rc_set_idq;
        self->rc_mode = motor;
    }
}
#endif