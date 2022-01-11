#include "../../uz/uz_global_configuration.h"
#if UZ_RESOLVERIP_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "uz_HAL.h"
#include "uz_resolverIP.h"
#include "uz_resolverIP_hw.h"

struct uz_resolverIP_t {
    bool is_ready;
    struct uz_resolverIP_config_t config;
};

static size_t instance_counter = 0U;
static uz_resolverIP_t instances[UZ_RESOLVERIP_MAX_INSTANCES] = { 0 };

static uz_resolverIP_t* uz_resolverIP_allocation(void);

static uz_resolverIP_t* uz_resolverIP_allocation(void){
    uz_assert(instance_counter < UZ_RESOLVERIP_MAX_INSTANCES);
    uz_resolverIP_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_resolverIP_t* uz_resolverIP_init(struct uz_resolverIP_config_t config) {
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_resolverIP_t* self = uz_resolverIP_allocation();
    self->config=config;
    return (self);
}

int32_t uz_resolverIP_multiply(uz_resolverIP_t* self, int32_t A, int32_t B){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_resolverIP_hw_write_A(self->config.base_address,A);
    uz_resolverIP_hw_write_B(self->config.base_address,B);
    return (uz_resolverIP_hw_read_C(self->config.base_address));
}

#endif