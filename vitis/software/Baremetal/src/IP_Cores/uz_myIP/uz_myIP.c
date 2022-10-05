#include "../../uz/uz_global_configuration.h"
#if UZ_MYIP_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_myIP.h"
#include "uz_myIP_hw.h"

struct uz_myIP_t {
    bool is_ready;
    struct uz_myIP_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_myIP_t instances[UZ_MYIP_MAX_INSTANCES] = { 0 };

static uz_myIP_t* uz_myIP_allocation(void);

static uz_myIP_t* uz_myIP_allocation(void){
    uz_assert(instance_counter < UZ_MYIP_MAX_INSTANCES);
    uz_myIP_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_myIP_t* uz_myIP_init(struct uz_myIP_config_t config){
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_myIP_t* self = uz_myIP_allocation();
    self->config=config;
    return (self);
}

int32_t uz_myIP_multiply(uz_myIP_t* self, int32_t A, int32_t B){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_myIP_hw_write_A(self->config.base_address,A);
    uz_myIP_hw_write_B(self->config.base_address,B);
    return (uz_myIP_hw_read_C(self->config.base_address));
}

#endif
