#include "../../uz/uz_global_configuration.h"
#if UZ_ADCLTC2311_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_private_utilities.h"

struct uz_adcLtc2311_t {
    bool is_ready;
    struct uz_adcLtc2311_config_t config;
};

static size_t instance_counter = 0U;
static uz_adcLtc2311_t instances[UZ_ADCLTC2311_MAX_INSTANCES] = { 0 };

static uz_adcLtc2311_t* uz_adcLtc2311_allocation(void);

static uz_adcLtc2311_t* uz_adcLtc2311_allocation(void){
    uz_assert(instance_counter < UZ_ADCLTC2311_MAX_INSTANCES);
    uz_adcLtc2311_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_adcLtc2311_t* uz_adcLtc2311_init(struct uz_adcLtc2311_config_t config) {
    uz_adcLtc2311_t* self = uz_adcLtc2311_allocation();
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_assert_not_zero(config.base_address);
    self->config=config;
    return (self);
}

void uz_adcLtc2311_configure(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
}

void uz_adcLtc2311_set_master_select(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.master_select = value;
}

void uz_adcLtc2311_set_channel_select(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.channel_select = value;
}

void uz_adcLtc2311_set_conversion_factor(uz_adcLtc2311_t* self, int32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.conversion_factor = value;
}

void uz_adcLtc2311_set_offset(uz_adcLtc2311_t* self, int32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.offset = value;
}

void uz_adcLtc2311_set_samples(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.samples = value;
}

uint32_t uz_adcLtc2311_get_master_select(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.master_select);
}

uint32_t uz_adcLtc2311_get_channel_select(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.channel_select);
}

int32_t uz_adcLtc2311_get_conversion_factor(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.conversion_factor);
}

int32_t uz_adcLtc2311_get_offset(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.offset);
}

uint32_t uz_adcLtc2311_get_samples(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.samples);
}

// update functions

void uz_adcLtc2311_update_conversion_factor(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
}

#endif