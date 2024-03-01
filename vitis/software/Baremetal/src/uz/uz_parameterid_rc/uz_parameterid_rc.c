#include "uz_parameterid_rc.h"

#include "../uz_global_configuration.h"
#if UZ_PARAMETERID_RC_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_parameterid_rc.h" 

struct uz_parameterid_rc_t{
    bool is_ready;
    bool is_first_call_to_sample;
    bool motormode;
    struct uz_parameterid_rc_config_t internal_config;
    struct uz_parameterid_rc_u_ind_t u_ind;
    struct uz_parameterid_rc_i_meas_t i_meas;
    struct uz_parameterid_rc_meas_out_t output;
    struct uz_parameterid_rc_counter_t counter;
    struct uz_parameterid_rc_sample_var_t sample;
    struct uz_parameterid_rc_u_meas_t u_meas;
    struct uz_parameterid_rc_calc_rc_t calc_mot;
    struct uz_parameterid_rc_calc_rc_t calc_gen;
    enum rc_state rc_state;
    float diff_u_ind_d;
    float diff_u_ind_q;
};




static uint32_t instance_counter = 0U;
static uz_parameterid_rc_t instances[UZ_PARAMETERID_RC_MAX_INSTANCES] = { 0 };

static uz_parameterid_rc_t* uz_parameterid_rc_allocation(void);

static uz_parameterid_rc_t* uz_parameterid_rc_allocation(void){
    uz_assert(instance_counter < UZ_PARAMETERID_RC_MAX_INSTANCES);
    uz_parameterid_rc_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_parameterid_rc_t* uz_parameterid_rc_init(struct uz_parameterid_rc_config_t initial_config) {
    uz_parameterid_rc_t* self = uz_parameterid_rc_allocation();
    self->internal_config = initial_config;
    self->is_first_call_to_sample = true;
    self->counter.meas_max = (uint32_t)(self->internal_config.sample_time/self->internal_config.isr_steptime);
    self->counter.wait_max = (uint32_t)(self->internal_config.wait_time/self->internal_config.isr_steptime); 
    uz_assert(self->internal_config.n_ref >= 0.0f);
    uz_assert(self->internal_config.n_ref <= 1500.0f);
    uz_assert(fabsf(self->internal_config.id_ref) < 20.0f);
    uz_assert(fabsf(self->internal_config.iq_ref) < 20.0f);
    return (self);
}

struct uz_parameterid_rc_config_t uz_parameterid_rc_get_config(uz_parameterid_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->internal_config;
}

uz_parameterid_rc_t* uz_parameterid_rc_reset_meas(uz_parameterid_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->sample.sum_ud = 0.0f;
    self->sample.sum_uq = 0.0f;
    self->sample.sum_id = 0.0f;
    self->sample.sum_iq = 0.0f;
    self->sample.sum_n = 0.0f;  
    self->sample.mean_ud = 0.0f;
    self->sample.mean_uq = 0.0f;
    self->sample.mean_id = 0.0f;
    self->sample.mean_iq = 0.0f;
    self->sample.mean_n = 0.0f;
    self->counter.meas = 0U;
    self->output.finished = 0U;
    return(self);
}

uz_parameterid_rc_t* uz_parameterid_rc_reset(uz_parameterid_rc_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_parameterid_rc_reset_meas(self); 
    self->output.mot_rc_d = 0.0f;
    self->output.mot_rc_q = 0.0f;
    self->output.gen_rc_d = 0.0f;
    self->output.gen_rc_q = 0.0f;
    self->output.generator_mode = false;
    self->output.finished = 0U;
    self->output.set_out.id_set = 0.0f;
    self->output.set_out.iq_set = 0.0f;
    self->output.set_out.n_set = -1.0f * self->internal_config.n_ref;
    self->is_first_call_to_sample = true;
    return(self);
}

struct uz_parameterid_rc_meas_out_t uz_parameterid_rc_generate_outputs(uz_parameterid_rc_t* self, float ud, float uq, float id, float iq, float n){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    if(self->is_first_call_to_sample){
            self->motormode = false;
            self->output.finished = 0U;
            self->u_ind.gen_d = 0.0f;
            self->u_ind.gen_q = 0.0f;
            self->u_ind.mot_d = 0.0f;
            self->u_ind.mot_q = 0.0f;
            self->i_meas.gen_id = 0.0f;
            self->i_meas.gen_iq = 0.0f;
            self->i_meas.mot_id = 0.0f;
            self->i_meas.mot_iq = 0.0f;
            self->counter.wait = 0U;
            self->counter.meas = 0U;
            self->output.generator_mode = false;
            self->rc_state = rc_wait;
            self->output.set_out.id_set = 0.0f;
            self->output.set_out.iq_set = 0.0f;
            self->output.set_out.n_set = -1.0f * self->internal_config.n_ref;
            self->is_first_call_to_sample = false;
    } else {
        self->counter.isr++; 

        switch (self->rc_state)
        {

        case rc_start:
            self->output.set_out.id_set = self->internal_config.id_ref;
            self->output.set_out.iq_set = self->internal_config.iq_ref;
            self->rc_state = rc_wait;
            self->motormode = true; 
            break;

        case rc_wait:
            self->counter.wait++;
                if(self->counter.wait == self->counter.wait_max){
                    if((self->motormode == false) && (self->output.generator_mode == false)){
                        self->rc_state=rc_start;
                    } else {
                        self->rc_state=rc_sample;
                    }
                    self->counter.wait = 0U;
                }
            break;
            

        case rc_wait_uind:
            self->counter.wait++;
                if(self->counter.wait == self->counter.wait_max){
                	self->rc_state=rc_check_u_ind;
                    self->counter.wait = 0U;
                }
            break;

        case rc_sample:
            self->counter.meas++;
            self->sample.sum_ud = self->sample.sum_ud + ud;
            self->sample.sum_uq = self->sample.sum_uq + uq;
            self->sample.sum_id = self->sample.sum_id + id;
            self->sample.sum_iq = self->sample.sum_iq + iq;
            self->sample.sum_n = self->sample.sum_n + n;   
            if (self->counter.meas == self->counter.meas_max){
                if (self->motormode){
                self->rc_state=rc_calc_mot;
                } else {
                self->rc_state=rc_calc_gen;
                }               
            }
            break;

        case rc_calc_mot:
            self->sample.mean_ud = self->sample.sum_ud / self->counter.meas;
            self->sample.mean_uq = self->sample.sum_uq / self->counter.meas;
            self->sample.mean_id = self->sample.sum_id / self->counter.meas;
            self->sample.mean_iq = self->sample.sum_iq / self->counter.meas;
            self->sample.mean_n = self->sample.sum_n / self->counter.meas;

            self->sample.r_s = (1.75e-6f * self->sample.mean_n * self->sample.mean_n + 5.733e-4f * self->sample.mean_n + 28.4648f)/1000.0f;

            self->u_ind.mot_d = self->sample.mean_ud - self->sample.r_s * self->sample.mean_id;
            self->u_ind.mot_q = self->sample.mean_uq - self->sample.r_s * self->sample.mean_iq;
            self->u_meas.mot_ud = self->sample.mean_ud;
            self->u_meas.mot_uq = self->sample.mean_uq;
            self->i_meas.mot_id = self->sample.mean_id;
            self->i_meas.mot_iq = self->sample.mean_iq;
            uz_parameterid_rc_reset_meas(self);
            self->rc_state = rc_switch2gen;
            break;

        case rc_calc_gen:
            self->sample.mean_ud = self->sample.sum_ud / self->counter.meas;
            self->sample.mean_uq = self->sample.sum_uq / self->counter.meas;
            self->sample.mean_id = self->sample.sum_id / self->counter.meas;
            self->sample.mean_iq = self->sample.sum_iq / self->counter.meas;
            self->sample.mean_n = self->sample.sum_n / self->counter.meas;

            self->sample.r_s = (1.75e-6f * self->sample.mean_n * self->sample.mean_n + 5.733e-4f * self->sample.mean_n + 28.4648f)/1000.0f;

            self->u_ind.gen_d = self->sample.mean_ud - self->sample.r_s * self->sample.mean_id;
            self->u_ind.gen_q = self->sample.mean_uq - self->sample.r_s * self->sample.mean_iq;
            self->u_meas.gen_ud = self->sample.mean_ud;
            self->u_meas.gen_uq = self->sample.mean_uq;
            self->i_meas.gen_id = self->sample.mean_id;
            self->i_meas.gen_iq = self->sample.mean_iq;
            uz_parameterid_rc_reset_meas(self);
            self->rc_state = rc_calc_rc;
            break;

        case rc_switch2gen:

            self->output.set_out.id_set = -1.0f * self->u_ind.mot_d;
            self->output.set_out.iq_set = self->u_ind.mot_q;
            self->motormode = false;
            self->output.generator_mode = true;
            self->rc_state = rc_check_u_ind;
            break;

        case rc_check_u_ind:
        self->counter.meas++;;
            self->sample.sum_ud = self->sample.sum_ud + ud;
            self->sample.sum_uq = self->sample.sum_uq + uq;
            self->sample.sum_id = self->sample.sum_id + id;
            self->sample.sum_iq = self->sample.sum_iq + iq;
            if (self->counter.meas == self->counter.meas_max){
                self->sample.mean_ud = self->sample.sum_ud / self->counter.meas;
                self->sample.mean_uq = self->sample.sum_uq / self->counter.meas;
                self->sample.mean_id = self->sample.sum_id / self->counter.meas;
                self->sample.mean_iq = self->sample.sum_iq / self->counter.meas; 

                self->u_ind.gen_d = self->sample.mean_ud - self->sample.r_s * self->sample.mean_id;
                self->u_ind.gen_q = self->sample.mean_uq - self->sample.r_s * self->sample.mean_iq; 

                self->diff_u_ind_d = fabsf(fabsf(self->u_ind.mot_d)-fabsf(self->u_ind.gen_d));
                self->diff_u_ind_q = fabsf(fabsf(self->u_ind.mot_q)-fabsf(self->u_ind.gen_q));

                if ((self->diff_u_ind_d <= 0.01f) && (self->diff_u_ind_q <= 0.005f)){
                	self->rc_state = rc_sample;
                    uz_parameterid_rc_reset_meas(self);
                } else {
                    self->rc_state = rc_wait_uind;
                    uz_parameterid_rc_reset_meas(self);
                }

            }
            
            break;



        case rc_calc_rc:
            self->calc_mot.i_dm = (self->i_meas.mot_id + self->i_meas.gen_id)/2.0f; 
            self->calc_mot.i_qm = (self->i_meas.mot_iq - self->i_meas.gen_iq)/2.0f; 
            self->calc_gen.i_dm = (self->i_meas.mot_id + self->i_meas.gen_id)/2.0f; 
            self->calc_gen.i_qm = (self->i_meas.mot_iq - self->i_meas.gen_iq)/-2.0f;

            self->calc_mot.i_di = self->i_meas.mot_id - self->calc_mot.i_dm; 
            self->calc_mot.i_qi = self->i_meas.mot_iq - self->calc_mot.i_qm; 
            self->calc_gen.i_di = self->i_meas.gen_id - self->calc_gen.i_dm; 
            self->calc_gen.i_qi = self->i_meas.gen_iq - self->calc_gen.i_qm;

            self->output.mot_rc_d = (self->u_meas.mot_ud - self->sample.r_s * self->i_meas.mot_id ) / self->calc_mot.i_di;
            self->output.mot_rc_q = (self->u_meas.mot_uq - self->sample.r_s * self->i_meas.mot_iq ) / self->calc_mot.i_qi;
            self->output.gen_rc_d = (self->u_meas.gen_ud - self->sample.r_s * self->i_meas.gen_id ) / self->calc_gen.i_di;
            self->output.gen_rc_q = (self->u_meas.gen_uq - self->sample.r_s * self->i_meas.gen_iq ) / self->calc_gen.i_qi;
            self->rc_state = rc_finished;
            break;

        case rc_finished:
        	self->output.finished = 1U;
            break;

        default:
            break;
        }
     

    }


return self->output;
}


#endif
