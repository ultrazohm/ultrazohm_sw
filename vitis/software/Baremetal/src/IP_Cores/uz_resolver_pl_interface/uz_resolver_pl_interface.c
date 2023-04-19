#include "uz_resolver_pl_interface.h"

#include "../../uz_global_configuration.h"
#if UZ_RESOLVER_PL_INTERFACE_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz_HAL.h"
#include "uz_resolver_pl_interface.h"
#include "uz_resolver_pl_interface_hw.h" 

struct uz_resolver_pl_interface_t {
    bool is_ready;
    struct uz_resolver_pl_interface_config_t config;
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

uz_resolver_pl_interface_t* uz_resolver_pl_interface_init(struct uz_resolver_pl_interface_config_t config) {
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_resolver_pl_interface_t* self = uz_resolver_pl_interface_allocation();
    self->config=config;
    return (self);
}
#endif