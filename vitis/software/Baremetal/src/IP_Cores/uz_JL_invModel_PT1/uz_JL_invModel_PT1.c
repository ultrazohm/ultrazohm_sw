
#include "../../uz_global_configuration.h"
#if UZ_JL_INVMODEL_PT1_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../../uz_HAL.h"
#include "uz_JL_invModel_PT1.h" 
#include "uz_JL_invModel_PT1_hw.h" 

struct uz_JL_invModel_PT1_t {
    bool is_ready;
    struct uz_JL_invModel_PT1_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_JL_invModel_PT1_t instances[UZ_JL_INVMODEL_PT1_MAX_INSTANCES] = { 0 };

static uz_JL_invModel_PT1_t* uz_JL_invModel_PT1_allocation(void);

static uz_JL_invModel_PT1_t* uz_JL_invModel_PT1_allocation(void)
{
    uz_assert(instance_counter < UZ_JL_INVMODEL_PT1_MAX_INSTANCES);
    uz_JL_invModel_PT1_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_JL_invModel_PT1_t* uz_JL_invModel_PT1_init(struct uz_JL_invModel_PT1_config_t config) 
{
    uz_assert_not_zero(config.ip_core_frequency_Hz);
    uz_assert_not_zero(config.base_adress);
    uz_assert(config.time_constant>0.0f);
    uz_JL_invModel_PT1_t* self = uz_JL_invModel_PT1_allocation();
    self->config = config;
    uz_JL_invModel_PT1_set_time_constant(self, config.time_constant);
    uz_JL_invModel_PT1_set_gain(self, config.gain);
    return (self);
}

void uz_JL_invModel_PT1_reset_integrator(uz_JL_invModel_PT1_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Reset integrator by forcing a rising edge from low to high
    uz_JL_invModel_PT1_hw_write_reset(self->config.base_adress, false);
    uz_sleep_useconds(1);
    uz_JL_invModel_PT1_hw_write_reset(self->config.base_adress, true);
    uz_sleep_useconds(1);
    uz_JL_invModel_PT1_hw_write_reset(self->config.base_adress, false);
    uz_sleep_useconds(1);
}

void uz_JL_invModel_PT1_set_input(uz_JL_invModel_PT1_t *self, float Ualpha, float Ubeta)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_invModel_PT1_hw_write_Ualpha(self->config.base_adress, Ualpha);
    uz_JL_invModel_PT1_hw_write_Ubeta(self->config.base_adress, Ubeta);
}

void uz_JL_invModel_PT1_set_gain(uz_JL_invModel_PT1_t *self, float gain)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.gain=gain;
    uz_JL_invModel_PT1_hw_write_gain(self->config.base_adress, self->config.gain);
}

void uz_JL_invModel_PT1_set_time_constant(uz_JL_invModel_PT1_t *self, float time_constant)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
     // the time constant is inverted since the IP-Core expects 1/time_constant in the hardware register
    self->config.time_constant=(1.0f/time_constant);
    uz_JL_invModel_PT1_hw_write_time_constant(self->config.base_adress, self->config.time_constant);
}

#endif