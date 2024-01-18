#include "uz_parameterid_rs.h"

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_RS_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <stdint.h>
#include "../uz_HAL.h"
#include "uz_parameterid_rs.h" 
#include "../uz_SystemTime/uz_SystemTime.h"

struct uz_parameterid_rs_t {
    bool is_ready;
    bool starts_generating_outputs;
    bool is_first_call_to_generate_outputs;
    bool is_first_call_to_sample;
	float elapsed_time_since_start;
    struct uz_parameterid_rs_config_t internal_config;
    struct uz_parameterid_rs_increments_t calc_increments;
    float isr_counter;
    float i_counter;
    float n_counter;
    float end_time;
    float duration;
};


static uint32_t instance_counter = 0U;
static uz_parameterid_rs_t instances[UZ_PARAMETERID_RS_MAX_INSTANCES] = { 0 };

static uz_parameterid_rs_t* uz_parameterid_rs_allocation(void);

static uz_parameterid_rs_t* uz_parameterid_rs_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_RS_MAX_INSTANCES);
    uz_parameterid_rs_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_parameterid_rs_t* uz_parameterid_rs_init(struct uz_parameterid_rs_config_t initial_config)
{
    uz_parameterid_rs_t* self = uz_parameterid_rs_allocation();
    self->internal_config = initial_config;
    self->is_first_call_to_sample = true;
    self->is_first_call_to_generate_outputs = true;
    self->calc_increments.n_increment = (initial_config.n_end - initial_config.n_start)/initial_config.n_steps;
	uz_assert(initial_config.n_start > 0.0f);
	uz_assert(initial_config.n_end > 0.0f);
	uz_assert(initial_config.n_end > initial_config.n_start);
	uz_assert(initial_config.n_steps > 0.0f);
	uz_assert(initial_config.i_steps > 0.0f);
    uz_assert(initial_config.i_diff > 0.0f);
    return (self);
}

struct uz_parameterid_rs_config_t uz_parameterid_rs_get_current_config(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->internal_config;
}

struct uz_parameterid_rs_increments_t uz_parameterid_rs_get_current_increments(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->calc_increments;
}

float uz_parameterid_rs_get_end_time(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->end_time;
}

void uz_parameterid_rs_reset(uz_parameterid_rs_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->is_first_call_to_sample = true;
	self->elapsed_time_since_start = 0.0f;

}

float uz_parameterid_rs_get_elapsed_time(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->elapsed_time_since_start;
}

float uz_parameterid_rs_get_isr_counter(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->isr_counter;
}


struct uz_parameterid_output uz_parameterid_rs_generate_outputs(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    struct uz_parameterid_output output;
	// If its the first call, we take the current time as the initial time to have small numbers at start with 0
	if (self->is_first_call_to_generate_outputs) {
        self->starts_generating_outputs = true;
        output.i_sample = 0.0f;
        output.n_sample = 0.0f;
        output.isr_stepcounter = 0.0f; 
		self->isr_counter = 0.0f;
        self->elapsed_time_since_start = 0.0f; // holds the time that has passed since the first call of the function
		self->is_first_call_to_generate_outputs = false;
        self->end_time = (self->internal_config.i_steps+3.0f)*(self->internal_config.n_steps+1.0f)*2.0f;
	    self->duration = ((self->internal_config.i_steps+3.0f)*2.0f);
    } else {
        self->isr_counter++; 
        output.isr_stepcounter = self->isr_counter; 
        self->elapsed_time_since_start = self->isr_counter * self->internal_config.isr_steptime;
        
        if (self->elapsed_time_since_start<=self->end_time){
                self->n_counter = (int)(self->elapsed_time_since_start/((self->internal_config.i_steps+3.0f)*2.0f));
                self->i_counter = (int)(self->elapsed_time_since_start/2.0f);
                if(self->elapsed_time_since_start > self->duration*self->n_counter && self->elapsed_time_since_start < self->duration*self->n_counter + 4.0f){
                output.i_sample = 0.0f;
                output.n_sample = self->internal_config.n_start + self->n_counter * self->calc_increments.n_increment;
                return output;
                } else {
                output.i_sample = self->internal_config.i_start + fmodf(self->i_counter,2.0f) * self->internal_config.i_diff;
                output.n_sample = self->internal_config.n_start + self->n_counter * self->calc_increments.n_increment;
                return output;
                }

        } else {
            output.i_sample = 0.0f;
            output.n_sample = 0.0f;
            return output;
        }
    }
}

/*float uz_parameterid_rs_sample(uz_parameterid_rs_t* self, struct uz_parameterid_output input, float ud, float id, float n){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    uz_assert(self->starts_generating_outputs);
    float test = 1.0;
    return test; 

}*/

#endif



