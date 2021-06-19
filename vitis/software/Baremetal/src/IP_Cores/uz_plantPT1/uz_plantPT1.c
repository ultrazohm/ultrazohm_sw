//#include "../../uz/uz_global_configuration.h"
#define UZ_PLANTPT1_MAX_INSTANCES 6U
#if UZ_PLANTPT1_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_plantPT1.h"
#include "uz_plantPT1_hw.h"

struct uz_plantPT1_t
{
    bool is_ready;
    struct uz_plantPT1_config_t config;
};

static size_t instance_counter = 0U;
static uz_plantPT1_t instances[UZ_PLANTPT1_MAX_INSTANCES] = {0};

static uz_plantPT1_t *uz_plantPT1_allocation(void);

static uz_plantPT1_t *uz_plantPT1_allocation(void)
{
    uz_assert(instance_counter < UZ_PLANTPT1_MAX_INSTANCES);
    uz_plantPT1_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_plantPT1_t *uz_plantPT1_init(struct uz_plantPT1_config_t config)
{
    uz_assert_not_zero(config.ip_core_frequency_Hz);
    uz_assert_not_zero(config.base_address);
    uz_assert(config.time_constant>0.0f);
    uz_plantPT1_t *self = uz_plantPT1_allocation();
    self->config = config;
    uz_plantPT1_set_time_constant(self, config.time_constant);
    uz_plantPT1_set_gain(self, config.gain);
    return (self);
}

void uz_plantPT1_reset_integrator(uz_plantPT1_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Reset integrator by forcing a rising edge from low to high
    uz_plantPT1_hw_write_reset(self->config.base_address, false);
    uz_sleep_useconds(1);
    uz_plantPT1_hw_write_reset(self->config.base_address, true);
    uz_sleep_useconds(1);
    uz_plantPT1_hw_write_reset(self->config.base_address, false);
    uz_sleep_useconds(1);
}

void uz_plantPT1_set_input(uz_plantPT1_t *self, float input_value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_plantPT1_hw_write_input(self->config.base_address, input_value);
}

void uz_plantPT1_set_gain(uz_plantPT1_t *self, float gain)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.gain=gain;
    uz_plantPT1_hw_write_gain(self->config.base_address, self->config.gain);
}

void uz_plantPT1_set_time_constant(uz_plantPT1_t *self, float time_constant)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
     // the time constant is inverted since the IP-Core expects 1/time_constant in the hardware register
    self->config.time_constant=(1.0f/time_constant);
    uz_plantPT1_hw_write_time_constant(self->config.base_address, self->config.time_constant);
}

float uz_plantPT1_read_output(uz_plantPT1_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (uz_plantPT1_hw_read_output(self->config.base_address));
}

#endif
