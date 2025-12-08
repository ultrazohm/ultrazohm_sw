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

enum bc_state{
    none,
    i_HS_control,
    u_UC_control,
    i_UC_control,
};
struct buck_control_config{
    float max_duty_cycle;
    float min_duty_cycle;
    float u_BUS_V_nominal;
    float i_dcdc_upper_lim_A;
    float i_dcdc_lower_lim_A;
    enum bc_state control_mode;
};




struct uz_buck_control_Controller_config{
    struct uz_PI_Controller_config i_HS_controller_config;
    struct uz_PI_Controller_config u_UC_controller_config;
    struct uz_PI_Controller_config i_UC_controller_config;
};



uz_buck_control_t* uz_buck_control_init(struct buck_control_config external_config);

float uz_buck_control_sample(uz_buck_control_t* self, struct buck_control_ref_val ref_val, struct buck_control_act_val act_val);

void uz_buck_control_controller_config(uz_buck_control_t* self);
void uz_buck_control_controller_init(uz_buck_control_t* self);


float uz_buck_i_HS_control(uz_buck_control_t* self, struct buck_control_ref_val buck_control_ref_val, struct buck_control_act_val buck_control_act_val);
float uz_buck_u_UC_control(uz_buck_control_t* self, struct buck_control_ref_val buck_control_ref_val, struct buck_control_act_val buck_control_act_val);
float uz_buck_i_UC_control(uz_buck_control_t* self, struct buck_control_ref_val buck_control_ref_val, struct buck_control_act_val buck_control_act_val);

#endif // UZ_BUCK_CONTROL_H