
#include "../../uz/uz_global_configuration.h"
#if UZ_INVERTER_3PH_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_inverter_3ph.h"
#include "uz_inverter_3ph_hw.h"


struct uz_inverter_3ph_t{
    bool is_ready;
    struct uz_inverter_3ph_config_t config;
};

static size_t instance_counter = 0U;
static uz_inverter_3ph_t instances[UZ_INVERTER_3PH_MAX_INSTANCES] = {0};

static uz_inverter_3ph_t* uz_inverter_3ph_allocation(void);

static uz_inverter_3ph_t* uz_inverter_3ph_allocation(void){
    uz_assert(instance_counter < UZ_INVERTER_3PH_MAX_INSTANCES);
    uz_inverter_3ph_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

// private function declarations
static void write_config_to_pl(uz_inverter_3ph_t *self);

uz_inverter_3ph_t* uz_inverter_3ph_init(struct uz_inverter_3ph_config_t config){
    uz_assert(0U != config.base_address);
    uz_assert(0U != config.ip_core_frequency_Hz);
    uz_inverter_3ph_t* self = uz_inverter_3ph_allocation();
    self->config = config;
    write_config_to_pl(self);
    return (self);
}

struct uz_inverter_3ph_u_abc_ps_t uz_inverter_3ph_get_u_abc_ps(uz_inverter_3ph_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_inverter_3ph_u_abc_ps_t u_abc = {
        .u_ab = 0.0f,
        .u_bc = 0.0f,
        .u_ca = 0.0f
    };
    u_abc.u_ab = uz_inverter_3ph_hw_read_u_ab_ps(self->config.base_address);
    u_abc.u_bc =uz_inverter_3ph_hw_read_u_bc_ps(self->config.base_address);
    u_abc.u_ca =uz_inverter_3ph_hw_read_u_ca_ps(self->config.base_address);
    return u_abc;
}

void uz_inverter_3ph_trigger_u_abc_ps_strobe(uz_inverter_3ph_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_inverter_3ph_hw_trigger_u_abc_ps_strobe(self->config.base_address);
}

void uz_inverter_3ph_set_i_abc_ps(uz_inverter_3ph_t *self, struct uz_inverter_3ph_i_abc_ps_t i_abc){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_inverter_3ph_hw_write_i_a_ps(self->config.base_address, i_abc.i_a);
    uz_inverter_3ph_hw_write_i_b_ps(self->config.base_address, i_abc.i_b);
    uz_inverter_3ph_hw_write_i_c_ps(self->config.base_address, i_abc.i_c);
}

void uz_inverter_3ph_trigger_i_abc_ps_strobe(uz_inverter_3ph_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_inverter_3ph_hw_trigger_i_abc_ps_strobe(self->config.base_address);
}

void uz_inverter_3ph_set_gate_ps(uz_inverter_3ph_t *self, struct uz_inverter_3ph_gate_ps_t G){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    //memcpy( (void *)(self->config.base_address+G_Data_uz_inverter_3ph), &G,sizeof (struct uz_inverter_3ph_G_t) );
    uz_inverter_3ph_hw_write_gate1(self->config.base_address, G.gate1);
    uz_inverter_3ph_hw_write_gate2(self->config.base_address, G.gate2);
    uz_inverter_3ph_hw_write_gate3(self->config.base_address, G.gate3);
    uz_inverter_3ph_hw_write_gate4(self->config.base_address, G.gate4);
    uz_inverter_3ph_hw_write_gate5(self->config.base_address, G.gate5);
    uz_inverter_3ph_hw_write_gate6(self->config.base_address, G.gate6);
}

void uz_inverter_3ph_trigger_gate_ps_strobe(uz_inverter_3ph_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_inverter_3ph_hw_trigger_gate_ps_strobe(self->config.base_address);
}

static void write_config_to_pl(uz_inverter_3ph_t *self){
    uz_inverter_3ph_hw_write_switch_pspl_abc(self->config.base_address, self->config.switch_pspl_abc);
    uz_inverter_3ph_hw_write_switch_pspl_gate(self->config.base_address, self->config.switch_pspl_gate);
}

#endif
