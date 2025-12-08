#ifndef UZ_BUCK_CONTROL_H
#define UZ_BUCK_CONTROL_H

#include <stdbool.h>
#include "../uz_piController/uz_piController.h"

typedef struct uz_buck_control_t uz_buck_control_t;


struct buck_control_act_val{
    float i_HS_A_meas;
    float u_UC_V_meas;
    float i_UC_V_meas;
    float u_BUS_V_meas;
};

struct buck_control_ref_val{
    float i_HS_A_ref;
    float u_UC_V_ref;
    float i_UC_A_ref;
};

struct buck_control_config{
    float max_duty_cycle;
    float min_duty_cycle;
    float u_BUS_V_nominal;
    float i_dcdc_upper_lim_A;
    float i_dcdc_lower_lim_A;
    bool i_HS_control;
    bool u_UC_control;
    bool i_UC_control;
};


enum bc_state{
    i_HS_control,
    u_UC_control,
    i_UC_control,
};

struct uz_buck_control_Controller_config{
    struct uz_PI_Controller_config i_HS_controller_config;
    struct uz_PI_Controller_config u_UC_controller_config;
    struct uz_PI_Controller_config i_UC_controller_config;
};



uz_buck_control_t* uz_buck_control_init(struct buck_control_config external_config);

float uz_buck_control_sample(uz_buck_control_t* self, enum bc_state set_control_mode);

void uz_buck_control_controller_config(uz_buck_control_t* self);
void uz_buck_control_controller_init(uz_buck_control_t* self);

/*
float uz_buck_i_HS_control(uz_buck_control_t* self, buck_control_ref_val i_HS_A_ref, buck_control_act_val i_HS_A_act, buck_control_config i_HS_control);
float uz_buck_u_UC_control(uz_buck_control_t* self, buck_control_ref_val u_UC_V_ref, buck_control_act_val u_UC_V_act, buck_control_config u_UC_control, buck_control_config i_dcdc_upper_lim_As, buck_control_config i_dcdc_lower_lim_A);
float uz_buck_i_UC_control(uz_buck_control_t* self, buck_control_ref_val i_UC_A_ref, buck_control_act_val i_UC_A_act, buck_control_config i_UC_control, buck_control_config max_duty_cycle, buck_control_config min_duty_cycle, buck_control_config u_BUS_V_nominal);
*/


#endif // UZ_BUCK_CONTROL_H