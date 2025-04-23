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
    self->max_increment_counter.operatingpoints_idq = (2U * (self->internal_config.id_steps + 1U) * (self->internal_config.iq_steps + 1U)) - (self->internal_config.id_steps + 1U);
    self->stepsize_increment.id_Amps = (self->internal_config.abs_id_max_Amps )/self->internal_config.id_steps;
    self->stepsize_increment.iq_Amps = (self->internal_config.abs_iq_max_Amps )/self->internal_config.iq_steps;
    self->stepsize_increment.n_rpm = (self->internal_config.n_stop_rpm - self->internal_config.n_start_rpm)/self->internal_config.n_steps;
    self->counter.increment_id = 0U;
    self->counter.increment_iq = 0U;
    self->counter.increment_n = 0U;
    self->output_ref_values.operating_points_all = 0.0f;
    self->counter.operating_points_n = 0U;
    self->counter.operating_points_idq = 0U;
    // insert assertions
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
        self->rc_previous_state = rc_idle;
    } else {
        self->counter.isr++;

        switch (self->rc_state)
        {

            // sets values for idq depending on the increment counters, then switches to wait state
        case rc_set_idq:
            self->set_values.id_set_Amps = 0.0f  - self->counter.increment_id * self->stepsize_increment.id_Amps;
            self->set_values.iq_set_Amps = self->internal_config.abs_iq_max_Amps  - self->counter.increment_iq * self->stepsize_increment.iq_Amps;
            self->rc_previous_state = self->rc_state;
            self->rc_state = rc_wait;
            break;
        

        // wait function: lets xx isr-cycles pass without changing anything. Switches to the following state after the wait time depending on the previous state
        case rc_wait: 
            self->counter.wait++;
            if(self->counter.wait == 60000U){
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

        // sets a flag that indicates that data is valid, then switches to wait state
        case rc_sample_on:
            self->output_ref_values.data_valid = 1.0f;
            self->output_ref_values.operating_points_all++;
            self->rc_previous_state = self->rc_state;
            self->rc_state = rc_wait;
        break;

        // resets the data valid flag, then switches to state that increments idq
        case rc_sample_off:
            self->output_ref_values.data_valid = 0.0f;
            self->rc_previous_state = self->rc_state;
            self->rc_state = rc_increment_idq;
        break;
        
        // calls function that increments idq
        case rc_increment_idq:
            uz_parameterID_rc_set_next_operating_point_idq(self);
        break;


        // calls function that increments idq
        case rc_increment_n:
            uz_parameterID_rc_set_next_operating_point_n(self);
        break;

        // routine is finished. idq and n are set to zero
        case rc_finished:
        self->set_values.id_set_Amps = 0.0f;
        self->set_values.iq_set_Amps = 0.0f;
        self->set_values.n_set_rpm = 0.0f;
            break; 

        default:
            break;
        }
    }

// sets the output of the function to the correct values
self->output_ref_values.id_ref_Amps = self->set_values.id_set_Amps;
self->output_ref_values.iq_ref_Amps = self->set_values.iq_set_Amps;
self->output_ref_values.n_ref_rpm = self->set_values.n_set_rpm;
return self->output_ref_values;

}


// increases either idq for the next operating point 
void uz_parameterID_rc_set_next_operating_point_idq(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert(self->counter.operating_points_idq < self->max_increment_counter.operatingpoints_idq);
    self->counter.operating_points_idq ++;
    if (self->counter.operating_points_idq == self->max_increment_counter.operatingpoints_idq) {
            self->rc_state = rc_increment_n;
            self->counter.increment_id = 0U;
            self->counter.increment_iq = 0U;
            self->counter.operating_points_idq = 0U;
    } else {
        self->counter.increment_id ++;
        if (self->counter.increment_id > self->internal_config.id_steps){
            self->counter.increment_id = 0U;
            self->counter.increment_iq ++;
        }    
        self->rc_state = rc_set_idq;
    }
}

void uz_parameterID_rc_set_next_operating_point_n(uz_parameterID_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    if (self->internal_config.n_steps == 0U){
        self->rc_state = rc_finished;
    } else if (self->counter.operating_points_n == self->internal_config.n_steps){
        self->rc_state = rc_finished;
    } else {
        self->counter.operating_points_n ++;
        self->set_values.n_set_rpm = self->internal_config.n_start_rpm + self->counter.operating_points_n * self->stepsize_increment.n_rpm;
        self->set_values.id_set_Amps = 0.0f;
        self->set_values.iq_set_Amps = 0.0f;
        self->rc_state = rc_set_idq;
    }
}
#endif
