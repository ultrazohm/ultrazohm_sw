#include "../../uz/uz_global_configuration.h"
#if UZ_ADCLTC2311_MAX_INSTANCES > 0U
#include <stdbool.h>
#include <stdint.h>
#include "../../uz/uz_HAL.h"
#include "uz_adcLtc2311.h"
#include "uz_adcLtc2311_private_utilities.h"
#include "uz_adcLtc2311_hw.h"

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

void uz_adcLtc2311_set_max_attempts(uz_adcLtc2311_t* self, uint32_t value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.max_attempts = value;
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

uint32_t uz_adcLtc2311_get_max_attempts(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return(self->config.max_attempts);
}

// update functions

int32_t uz_adcLtc2311_update_conversion_factor(uz_adcLtc2311_t* self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    int32_t return_value = UZ_SUCCESS;
    // Get the current state of the control register
    uint32_t adc_cr = uz_adcLtc2311_hw_read_cr(self->config.base_address);

    // Reset all bits that determine the meaning of the value
    adc_cr &= ~(UZ_ADCLTC2311_CR_CONFIG_VALUE_0 | UZ_ADCLTC2311_CR_CONFIG_VALUE_1 | UZ_ADCLTC2311_CR_CONFIG_VALUE_2);
    // Set the LSB. This means, that the config value is the conversion factor
    // Set the VALUE_VALID bit as well to trigger the update
    adc_cr |= UZ_ADCLTC2311_CR_CONV_VALUE_VALID | UZ_ADCLTC2311_CR_CONFIG_VALUE_0;

    // Perform the actual writing to the hardware registers
    // Selection, which channels shall be updated
    uz_adcLtc2311_hw_write_master_channel(self->config.base_address, self->config.master_select);
	uz_adcLtc2311_hw_write_channel(self->config.base_address, self->config.channel_select);
    // Write the desired factor
    uz_adcLtc2311_hw_write_value(self->config.base_address, self->config.conversion_factor);
	// Trigger the update
    uz_adcLtc2311_hw_write_cr(self->config.base_address, adc_cr);

    // Wait for the acknowledgement
    return_value = uz_adcLtc2311_cr_wait_for_value_acknowledgement(self->config.base_address, self->config.max_attempts);

    return return_value;
}

#endif