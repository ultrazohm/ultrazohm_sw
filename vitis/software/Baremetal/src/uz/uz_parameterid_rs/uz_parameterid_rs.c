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
    struct uz_parameterid_rs_config_t internal_config;
    struct uz_parameterid_rs_increments_t calc_increments;
    struct uz_parameterid_output set_values;
    struct uz_parameterid_rs_counter_t counter;
    float isr_counter;
    enum state state;
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
    self->is_first_call_to_generate_outputs = true;
    self->calc_increments.n_increment = (initial_config.n_end_rpm - initial_config.n_start_rpm)/initial_config.n_steps;
    self->state = start; 
    self->set_values.id_ref_Amps = 0.0f;
    self->set_values.n_ref_rpm = 0.0f;
	uz_assert(initial_config.n_start_rpm >= 0.0f);
	uz_assert(initial_config.n_end_rpm > 0.0f);
	uz_assert(initial_config.n_end_rpm > initial_config.n_start_rpm);
	uz_assert(initial_config.n_steps > 0.0f);
	uz_assert(initial_config.i_repeats > 0.0f);
    uz_assert(initial_config.i_neg_Amps < 0.0f);
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

enum state uz_parameterid_rs_get_current_state(uz_parameterid_rs_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->state;
}

void uz_parameterid_rs_reset(uz_parameterid_rs_t* self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    self->is_first_call_to_generate_outputs = true;
    self->set_values.id_ref_Amps = 0.0f;
    self->set_values.n_ref_rpm = 0.0f;
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
	if (self->is_first_call_to_generate_outputs) {
        self->starts_generating_outputs = true;
        self->state = start;
        self->set_values.id_ref_Amps = 0.0f;
        self->set_values.n_ref_rpm = 0.0f;
        self->set_values.isr_stepcounter = 0.0f; 
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
        self->set_values.isr_stepcounter = self->isr_counter; 

            switch (self->state){

            case start:
                self->set_values.n_ref_rpm = self->internal_config.n_start_rpm;
                self->set_values.id_ref_Amps = 0.0f;
                self->set_values.iq_ref_Amps = 0.0f;
                self->state = wait; 
                break;
            
            case wait:
            self->counter.wait++;
                if(self->counter.wait == self->counter.wait_max){
                    self->state=i_pos_Amps;
                    self->counter.wait = 0U;
                }
                break;
            
            case i_pos_Amps:
                self->counter.i++; 
                self->set_values.id_ref_Amps = self->internal_config.i_pos_Amps;
                if (self->counter.i >= (uint32_t)(0.5f/self->internal_config.isr_steptime))
                {
                    self->set_values.data_valid = 1.0f;
                }
                
                if(self->counter.i == self->counter.i_max){
                    self->state=i_neg_Amps;
                    self->counter.i = 0U;
                    self->set_values.data_valid = 0.0f;
                }
                break;

            case i_neg_Amps:
                self->counter.i++; 
                self->set_values.id_ref_Amps = self->internal_config.i_neg_Amps ;
                if (self->counter.i >= (uint32_t)(0.5f/self->internal_config.isr_steptime))
                {
                    self->set_values.data_valid = 1.0f;
                }
                if(self->counter.i == self->counter.i_max){
                    self->counter.i_repeat++; 
                    if(self->counter.i_repeat == self->internal_config.i_repeats){
                        self->counter.i_repeat = 0U;
                        self->counter.i = 0U;
                        self->state = n_increment; 
                        self->set_values.data_valid = 0.0f;
                        break;
                    }
                    self->state = i_pos_Amps;
                    self->counter.i = 0U;
                    self->set_values.data_valid = 0.0f;
                }
                break; 

            case n_increment:
                 self->counter.n++;
                 self->set_values.id_ref_Amps = 0.0f;
                 self->set_values.n_ref_rpm = self->internal_config.n_start_rpm + (float)(self->counter.n)*self->calc_increments.n_increment; 
                 if(self->counter.n > (self->internal_config.n_steps)){
                    self->state = finished;
                 } else {
                    self->state = wait;
                 }
                    
                break;

            case finished:
                self->set_values.id_ref_Amps = 0.0f;
                self->set_values.n_ref_rpm = 0.0f;
                break;

            default:
                self->set_values.id_ref_Amps = 0.0f;
                self->set_values.n_ref_rpm = 0.0f;
                break;
        }
    output = self->set_values;
    }
    return output;
}

#endif



