#include "uz_resolver_pl_interface.h"

#include "../../uz_global_configuration.h"
#if UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz_HAL.h"
#include "uz_resolver_pl_interface.h"
#include "uz_resolver_pl_interface_hw.h" 

// Datasheet values of AD2S1210 needed fpr internal calculations of the IP-Core
// Maximum representable rounds per second according to resolver resolution setting
#define RPS_MAX_16BIT  125U
#define RPS_MAX_14BIT  500U
#define RPS_MAX_12BIT 1000U
#define RPS_MAX_10BIT 2500U
// Calculation factor for results in rounds per second from raw value
#define BIT_TO_RPS_FACTOR_16BIT 0.003814697f // RPS_MAX_xxBIT/(2^(xx-1))
#define BIT_TO_RPS_FACTOR_14BIT 0.061035156f
#define BIT_TO_RPS_FACTOR_12BIT 0.488281250f
#define BIT_TO_RPS_FACTOR_10BIT 4.882812500f

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

void uz_resolver_pl_interface_set_theta_m_offset_rad(uz_resolver_pl_interface_t *self, float theta_m_offset_rad) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.theta_m_offset_rad = theta_m_offset_rad;
    uz_resolver_pl_interface_hw_write_theta_m_offset_rad(self->config.base_address, self->config.theta_m_offset_rad);
}
#endif