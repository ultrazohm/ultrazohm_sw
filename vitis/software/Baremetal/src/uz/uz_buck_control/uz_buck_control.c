#include "../uz_global_configuration.h"
#if UZ_BUCK_CONTROL_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_buck_control.h" 

struct uz_buck_control_t {
    bool is_ready;
    struct buck_control_config config;
};

static uint32_t instance_counter = 0U;
static uz_buck_control_t instances[UZ_BUCK_CONTROL_MAX_INSTANCES] = { 0 };

static uz_buck_control_t* uz_buck_control_allocation(void);

static uz_buck_control_t* uz_buck_control_allocation(void){
    uz_assert(instance_counter < UZ_BUCK_CONTROL_MAX_INSTANCES);
    uz_buck_control_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_buck_control_t* uz_buck_control_init(struct buck_control_config config) {
    uz_buck_control_t* self = uz_buck_control_allocation();
    self->config = config;
    return (self);
}


float uz_buck_control_sample(uz_buck_control_t* self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert((self->config.i_HS_control + self->config.u_UC_control + self->config.i_UC_control) == 1);
    //To be implemented
    return (0.0f);
}





/*
uz_buck_i_HS_control(uz_buck_control_t* self, struct buck_control_ref_val i_HS_A_ref, struct buck_control_act_val i_HS_A_act, struct buck_control_config i_HS_control) {
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    


    //To be implemented
    // return(u_UC_V_ref);
}


uz_buck_u_UC_control(uz_buck_control_t* self, struct buck_control_ref_val u_UC_V_ref, struct buck_control_act_val u_UC_V_act, struct buck_control_config u_UC_control, struct buck_control_config i_dcdc_upper_lim_abs, struct buck_control_config i_dcdc_lower_lim_abs){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    //To be implemented
}

uz_buck_i_UC_control(uz_buck_control_t* self, struct buck_control_ref_val i_UC_A_ref, struct buck_control_act_val i_UC_A_act, struct buck_control_config i_UC_control, struct buck_control_config max_duty_cycle, struct buck_control_config min_duty_cycle, struct buck_control_config u_BUS_V_nominal){
    uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
    //To be implemented
}

*/


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