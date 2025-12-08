#include "../uz_global_configuration.h"
#if UZ_BUCK_CONTROL_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_buck_control.h" 

typedef struct uz_buck_control_t {
    bool is_ready;
    struct buck_control_config config;
    float duty_cycle;
    bool first_call;
    struct uz_buck_control_Controller_config controller_config;
    struct uz_PI_Controller* i_HS_Controller;
    struct uz_PI_Controller* u_UC_Controller;
    struct uz_PI_Controller* i_UC_Controller;
}uz_buck_control_t;

static uint32_t instance_counter = 0U;
static uz_buck_control_t instances[UZ_BUCK_CONTROL_MAX_INSTANCES] = { 0 };

static uz_buck_control_t* uz_buck_control_allocation(void);

static uz_buck_control_t* uz_buck_control_allocation(void){
    uz_assert(instance_counter < UZ_BUCK_CONTROL_MAX_INSTANCES);
    uz_buck_control_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->duty_cycle = 0.0f;
    self->config.control_mode = none;
    self->first_call = true;
    self->is_ready = true;
    return (self);
}

uz_buck_control_t* uz_buck_control_init(struct buck_control_config external_config) {
    uz_buck_control_t* self = uz_buck_control_allocation();
    self->config = external_config;
    //configure all PI controllers
    uz_buck_control_controller_config(self);
    // initialize all PI controllers
    uz_buck_control_controller_init(self);   
    return (self);
}

void uz_buck_control_controller_config(uz_buck_control_t* self) {
    // initialize all PI controllers
    // i_HS controller config
    self->controller_config.i_HS_controller_config.Kp = 1.0f;
    self->controller_config.i_HS_controller_config.Ki = 100.0f;
    self->controller_config.i_HS_controller_config.lower_limit = 0.0f;
    self->controller_config.i_HS_controller_config.upper_limit = 50.0f;
    self->controller_config.i_HS_controller_config.samplingTime_sec = 0.0001f;
    self->controller_config.i_HS_controller_config.type = UZ_PI_PARALLEL;

    // u_UC controller config
    self->controller_config.u_UC_controller_config.Kp = 10.0f;
    self->controller_config.u_UC_controller_config.Ki = 2.5;
    self->controller_config.u_UC_controller_config.lower_limit = -50.0f;
    self->controller_config.u_UC_controller_config.upper_limit = 50.0f;
    self->controller_config.u_UC_controller_config.samplingTime_sec = 0.0001f;
    self->controller_config.u_UC_controller_config.type = UZ_PI_PARALLEL;    

    // i_UC controller config
    self->controller_config.i_UC_controller_config.Kp = 0.01;
    self->controller_config.i_UC_controller_config.Ki = 0.2f;
    self->controller_config.i_UC_controller_config.lower_limit = -10.0f;
    self->controller_config.i_UC_controller_config.upper_limit = 10.0f;
    self->controller_config.i_UC_controller_config.samplingTime_sec = 0.0001f;
    self->controller_config.i_UC_controller_config.type = UZ_PI_PARALLEL;    
}

void uz_buck_control_controller_init(uz_buck_control_t* self) {
    // initialize all PI controllers
    self->i_HS_Controller = uz_PI_Controller_init(self->controller_config.i_HS_controller_config);
    self->u_UC_Controller = uz_PI_Controller_init(self->controller_config.u_UC_controller_config);
    self->i_UC_Controller = uz_PI_Controller_init(self->controller_config.i_UC_controller_config);
}

float uz_buck_control_sample(uz_buck_control_t* self, struct buck_control_ref_val ref_val, struct buck_control_act_val act_val) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_zero(act_val.u_BUS_V_meas);
    uz_assert_not_zero(act_val.u_UC_V_meas);
    if(self->first_call){
        self->first_call = false;
        self->duty_cycle = 0.0f;
        ref_val = (struct buck_control_ref_val){0};
        act_val = (struct buck_control_act_val){0};
    } else {
        if (self->config.control_mode == i_HS_control)
        {
            ref_val.u_UC_V_ref = uz_buck_i_HS_control(self, ref_val, act_val);
            ref_val.i_UC_A_ref = uz_buck_u_UC_control(self, ref_val, act_val);
            self->duty_cycle = uz_buck_i_UC_control(self, ref_val, act_val);
        } else if (self->config.control_mode == u_UC_control)
        {
            ref_val.i_UC_A_ref = uz_buck_u_UC_control(self, ref_val, act_val);
            self->duty_cycle = uz_buck_i_UC_control(self, ref_val, act_val);
        } 
        else if (self->config.control_mode == i_UC_control)
        {
            self->duty_cycle = uz_buck_i_UC_control(self, ref_val, act_val);
        } 
        else 
        {
            uz_assert(false);
        }
    }

    return (self->duty_cycle);
}


float uz_buck_i_HS_control(uz_buck_control_t* self, struct buck_control_ref_val buck_control_ref_val, struct buck_control_act_val buck_control_act_val) {
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    //PI controller for i_HS control
    buck_control_ref_val.u_UC_V_ref = uz_PI_Controller_sample(self->i_HS_Controller, buck_control_ref_val.i_HS_A_ref, buck_control_act_val.i_HS_A_meas, false);
    return(buck_control_ref_val.u_UC_V_ref);
}

float uz_buck_u_UC_control(uz_buck_control_t* self, struct buck_control_ref_val buck_control_ref_val, struct buck_control_act_val buck_control_act_val) {
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);

    //adds actual voltage to the reference voltage
    buck_control_ref_val.u_UC_V_ref += buck_control_act_val.u_UC_V_meas;
    //limits the reference voltage to the allowed voltage limits
    if (buck_control_ref_val.u_UC_V_ref > self->config.i_dcdc_upper_lim_A) {
        buck_control_ref_val.u_UC_V_ref = self->config.i_dcdc_upper_lim_A;
    } else if (buck_control_ref_val.u_UC_V_ref < self->config.i_dcdc_lower_lim_A) {
        buck_control_ref_val.u_UC_V_ref = self->config.i_dcdc_lower_lim_A;
    }
    //PI controller for u_UC control
    buck_control_ref_val.i_UC_A_ref = uz_PI_Controller_sample(self->u_UC_Controller, buck_control_ref_val.u_UC_V_ref, buck_control_act_val.u_UC_V_meas, false);
    return(buck_control_ref_val.i_UC_A_ref);
}

float uz_buck_i_UC_control(uz_buck_control_t* self, struct buck_control_ref_val buck_control_ref_val, struct buck_control_act_val buck_control_act_val) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    //PI controller for i_UC control. output is delta duty cycle whic is added to the precalculated dutycycle
    self->duty_cycle = uz_PI_Controller_sample(self->i_UC_Controller, buck_control_ref_val.i_UC_A_ref, buck_control_act_val.i_UC_V_meas, false);
    // add ratio of nominal bus voltage to actual bus voltage to duty cycle
    self->duty_cycle += (buck_control_act_val.u_UC_V_meas / buck_control_act_val.u_BUS_V_meas);
    //limit duty cycle to max and min values
    if (self->duty_cycle > self->config.max_duty_cycle) {
        self->duty_cycle = self->config.max_duty_cycle;
    } else if (self->duty_cycle < self->config.min_duty_cycle) {
        self->duty_cycle = self->config.min_duty_cycle;
    }
    uz_assert(!isnan(self->duty_cycle));
    uz_assert(self->duty_cycle >= 0.0f && self->duty_cycle <= 1.0f);
    return(self->duty_cycle);
}


/*  
Ablaufplan:

3 Fälle: i_HS_control, u_UC_control und i_UC_control
-> soll im Betrieb zwischen den Modi umgeschalten werden können?

1. i_HS_ref - i_HS_act
2. PI regler auf i_HS Fehler
3. Ausgabe des Reglers u_UC_ref
4. Addiere u_UC_act auf u_UC_ref
4. Wenn U_UC_control = true, dann u_UC_ref_extern = u_UC_ref  
5. Begrenzung von u_UC_ref auf max. zulässige Spannung 
6. u_UC_ref - u_UC_act
7. PI regler auf u_UC Fehler, Ausgabe des Reglers i_UC_ref
8. Wenn i_UC_control = true, dann i_UC_ref_extern = i_UC_ref
9. i_UC_ref - i_UC_act
10. PI regler auf i_UC Fehler, Ausgabe des Reglers Duty_cycle
11. Begrenzung des Duty_cycle auf max. zulässiges Tastverhältnis [0 1] 
*/



#endif