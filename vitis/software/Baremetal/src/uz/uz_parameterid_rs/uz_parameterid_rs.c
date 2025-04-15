#include "uz_parameterid_rs.h"

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_RS_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../uz_HAL.h"
#include "uz_parameterid_rs.h" 
#include "../uz_SystemTime/uz_SystemTime.h"

struct uz_parameterid_rs_t {
    bool is_ready;
    bool starts_generating_outputs;
    bool is_first_call_to_generate_outputs;
    bool is_first_call_to_sample;
    struct uz_parameterid_rs_config_t internal_config;
    struct uz_parameterid_rs_increments_t calc_increments;
    struct uz_parameterid_output act_vals;
    struct uz_parameterid_rs_counter_t counter;
    struct uz_parameterid_rs_sample_var sample;
    struct uz_parameterid_rs_sample_output sample_out;
    float isr_counter;
    enum state state;
    enum sample sample_state;

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
    self->state = start; 
    self->act_vals.i_sample = 0.0f;
    self->act_vals.n_sample = 0.0f;
	uz_assert(initial_config.n_start >= 0.0f);
	uz_assert(initial_config.n_end > 0.0f);
	uz_assert(initial_config.n_end > initial_config.n_start);
	uz_assert(initial_config.n_steps > 0.0f);
	uz_assert(initial_config.i_repeats > 0.0f);
    uz_assert(initial_config.i_diff > 0.0f);
    uz_assert(initial_config.i_steptime > 0.5f);
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

struct uz_parameterid_rs_sample_output uz_parameterid_rs_get_rs(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->sample_out;
}

enum state uz_parameterid_rs_get_current_state(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->state;
}




enum sample uz_parameterid_rs_get_current_sample_state(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->sample_state;
}

void uz_parameterid_rs_reset(uz_parameterid_rs_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	self->is_first_call_to_sample = true;
    self->is_first_call_to_generate_outputs = true;
    self->act_vals.i_sample = 0.0f;
    self->act_vals.n_sample = 0.0f;
}


float uz_parameterid_rs_get_isr_counter(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->isr_counter;
}

struct uz_parameterid_output uz_parameterid_rs_generate_outputs(uz_parameterid_rs_t* self, float ud, float id){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    struct uz_parameterid_output output;
	if (self->is_first_call_to_generate_outputs) {
        self->starts_generating_outputs = true;
        self->state = start;
        self->sample_state = sample_off;
        self->act_vals.i_sample = 0.0f;
        self->act_vals.n_sample = 0.0f;
        self->act_vals.isr_stepcounter = 0.0f; 
		self->isr_counter = 0.0f;
        self->counter.wait = 0U;
        self->counter.i = 0U;
        self->counter.n = 0U; 
        self->counter.i_repeat = 0U;
        self->counter.wait_max = (uint32_t)(self->internal_config.wait_time/self->internal_config.isr_steptime); 
        self->counter.i_max =(uint32_t)(self->internal_config.i_steptime/self->internal_config.isr_steptime);
        self->is_first_call_to_generate_outputs = false;
    } else {
        self->isr_counter++; 
        self->act_vals.isr_stepcounter = self->isr_counter; 

            switch (self->state){

            case start:
                self->act_vals.n_sample = self->internal_config.n_start;
                self->act_vals.i_sample = 0.0f;
                self->state = wait; 
                break;
            
            case wait:
            self->counter.wait++;
                if(self->counter.wait == self->counter.wait_max){
                    self->state=i_start;
                    self->counter.wait = 0U;
                }
                break;
            
            case i_start:
                self->counter.i++; 
                self->act_vals.i_sample = self->internal_config.i_start;
                if (self->counter.i >= (uint32_t)(0.5f/self->internal_config.isr_steptime))
                {
                    self->sample_state = sample_on;
                }
                
                if(self->counter.i == self->counter.i_max){
                    self->state=i_increment;
                    self->sample_state=calc;
                    self->counter.i = 0U;
                }
                break;

            case i_increment:
                self->counter.i++; 
                self->act_vals.i_sample = self->internal_config.i_start + self->internal_config.i_diff;
                if (self->counter.i >= (uint32_t)(0.5f/self->internal_config.isr_steptime))
                {
                    self->sample_state = sample_on;
                }
                if(self->counter.i == self->counter.i_max){
                    self->counter.i_repeat++; 
                    if(self->counter.i_repeat == self->internal_config.i_repeats){
                        self->counter.i_repeat = 0U;
                        self->counter.i = 0U;
                        self->state = n_increment;
                        self->sample_state = calc; 
                        break;
                    }
                    self->state = i_start;
                    self->sample_state = calc;
                    self->counter.i = 0U;
                }
                break; 

            case n_increment:
                 self->sample_state = rs_write;
                 self->counter.n++;
                 self->act_vals.i_sample = 0.0f;
                 self->act_vals.n_sample = self->internal_config.n_start + (float)(self->counter.n)*self->calc_increments.n_increment; 
                 if(self->counter.n > (self->internal_config.n_steps+1)){
                    self->state = finished;
                 } else {
                    self->state = wait;
                 }
                    
                break;

            case finished:
                self->act_vals.i_sample = 0.0f;
                self->act_vals.n_sample = 0.0f;
                break;

            default:
                self->act_vals.i_sample = 0.0f;
                self->act_vals.n_sample = 0.0f;
                break;
        }
    output = self->act_vals;
    uz_parameterid_rs_sample(self, ud, id);
    }
    return output;
}

void uz_parameterid_rs_sample(uz_parameterid_rs_t* self, float ud, float id){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    uz_assert(self->starts_generating_outputs);
    uint32_t ind = 0U;
    if (self->is_first_call_to_sample) {
        self->sample.sum_ud = 0.0f;
        self->sample.sum_id = 0.0f;
        self->counter.meas = 0U;
        self->sample.mean_ud = 0.0f;
        self->sample.mean_id = 0.0f;
        self->sample.ref_ud = 0.0f;
        self->sample.ref_id = 0.0f;
        self->sample.rs = 0.0f;
        self->sample.sum_rs = 0.0f;
        self->counter.rs = 0U;
        self->is_first_call_to_sample = false;
    } else {
        switch (self->sample_state)
        {
        case sample_on:
            self->sample.sum_ud = self->sample.sum_ud + ud;
            self->sample.sum_id = self->sample.sum_id + id;
            self->counter.meas++; 
            break;

        case calc:
            if (self->counter.i_repeat == 0U)
            {
                self->sample.mean_ud = self->sample.sum_ud/(float)(self->counter.meas);
                self->sample.mean_id = self->sample.sum_id/(float)(self->counter.meas);
                self->sample_state = sample_off;
            } else {
                self->sample.ref_ud = self->sample.mean_ud;
                self->sample.ref_id = self->sample.mean_id;
                self->sample.mean_ud = self->sample.sum_ud/(float)(self->counter.meas);
                self->sample.mean_id = self->sample.sum_id/(float)(self->counter.meas);
                self->sample.rs = fabsf(self->sample.ref_ud - self->sample.mean_ud)/fabsf(self->sample.ref_id - self->sample.mean_id);
                self->sample.sum_rs = self->sample.sum_rs + self->sample.rs;
                self->counter.rs++; 
                self->sample_state = sample_off;
            }
            break;

        case sample_off:
            self->sample.sum_ud = 0.0f;
            self->sample.sum_id = 0.0f;
            self->counter.meas = 0U;
            break;

        case rs_write:            
            ind = self->counter.n-1;
            if (ind <= self->internal_config.n_steps){
            uint32_t max_size_rs_calc =  sizeof(self->sample_out.rs_calc) / sizeof(float);
            uz_assert(ind < max_size_rs_calc );
            uint32_t max_size_rs_speeds =  sizeof(self->sample_out.rs_speeds) / sizeof(float);
            uz_assert(ind < max_size_rs_speeds );
            self->sample_out.rs_calc[ind] = self->sample.sum_rs/(float)(self->counter.rs);
            self->sample_out.rs_speeds[ind] = self->internal_config.n_start + (float)ind * self->calc_increments.n_increment;            
            self->sample.sum_ud = 0.0f;
            self->sample.sum_id = 0.0f;
            self->sample.mean_ud = 0.0f;
            self->sample.mean_id = 0.0f;
            self->counter.meas = 0U; 
            self->sample.rs = 0.0f;
            self->sample.sum_rs = 0.0f;
            self->counter.rs = 0U;
            self->sample_state = sample_off;   
            break;
            } else {
            self->sample_state = sample_finished; 
            self->sample_state = finished;
            }

        case sample_finished:
            break;
            
        default:
            break;
        }

    }
    return; 

}

#endif



