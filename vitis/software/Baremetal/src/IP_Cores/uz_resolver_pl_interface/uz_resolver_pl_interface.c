#include "uz_resolver_pl_interface.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz/uz_HAL.h"
#include "uz_resolver_pl_interface.h"
#include "uz_resolver_pl_interface_hw.h" 

struct uz_resolver_pl_interface_t {
    bool is_ready;
    struct uz_resolver_pl_interface_config_t config;
    struct uz_resolver_pl_interface_outputs_t outputs;
};

static uint32_t instance_counter = 0U;
static uz_resolver_pl_interface_t instances[UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES] = { 0 };

static uz_resolver_pl_interface_t* uz_resolver_pl_interface_allocation(void);

static uz_resolver_pl_interface_t* uz_resolver_pl_interface_allocation(void){
    uz_assert(instance_counter < UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES);
    uz_resolver_pl_interface_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_resolver_pl_interface_t* uz_resolver_pl_interface_init(struct uz_resolver_pl_interface_config_t config, struct uz_resolver_pl_interface_outputs_t outputs) {
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_assert_not_zero(config.resolver_polepairs);
    uz_assert_not_zero(config.machine_polepairs);
    uz_assert_not_zero(config.position_intmax);
    uz_resolver_pl_interface_t* self = uz_resolver_pl_interface_allocation();
    self->config=config;
    self->outputs=outputs;
    uz_resolver_pl_interface_set_config(self);
    uz_resolver_pl_interface_reset(self);
    return (self);
}

void uz_resolver_pl_interface_set_config(uz_resolver_pl_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_resolver_pl_interface_hw_write_machine_polepairs(self->config.base_address, self->config.machine_polepairs);
    uz_resolver_pl_interface_hw_write_resolver_polepairs(self->config.base_address, self->config.resolver_polepairs);
    uz_resolver_pl_interface_hw_write_position_intmax(self->config.base_address, self->config.position_intmax);
    uz_resolver_pl_interface_hw_write_bitToRPS_factor(self->config.base_address, self->config.bitToRPS_factor);
    uz_resolver_pl_interface_set_theta_m_offset_rad(self, self->config.theta_m_offset_rad);
}

struct uz_resolver_pl_interface_outputs_t uz_resolver_pl_interface_get_outputs(uz_resolver_pl_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->outputs.revolution_counter = uz_resolver_pl_interface_hw_read_revolution_cnt(self->config.base_address);
    self->outputs.position_mech_2pi = uz_resolver_pl_interface_hw_read_pos_mech_2pi(self->config.base_address);
    self->outputs.position_el_2pi = uz_resolver_pl_interface_hw_read_pos_el_2pi(self->config.base_address);
    self->outputs.omega_mech_rad_s = uz_resolver_pl_interface_hw_read_omega_mech_rad_s(self->config.base_address);
    self->outputs.n_mech_rpm = uz_resolver_pl_interface_hw_read_n_mech_rpm(self->config.base_address);
    return(self->outputs);
}

void uz_resolver_pl_interface_set_theta_m_offset_rad(uz_resolver_pl_interface_t *self, float theta_m_offset_rad) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.theta_m_offset_rad = theta_m_offset_rad;
    uz_resolver_pl_interface_hw_write_theta_m_offset_rad(self->config.base_address, self->config.theta_m_offset_rad);
}

void uz_resolver_pl_interface_reset(uz_resolver_pl_interface_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_resolver_pl_interface_hw_write_cnt_reset(self->config.base_address, true);
    uz_resolver_pl_interface_hw_write_cnt_reset(self->config.base_address, false);    
}
#endif
