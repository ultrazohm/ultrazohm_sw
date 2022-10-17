#include "uz_filter_cumulativeavg.h"

#include "../uz_global_configuration.h"
#if UZ_FILTER_CUMULATIVEAVG_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_filter_cumulativeavg.h"

struct uz_filter_cumulativeavg_t
{
    bool is_ready;
    float number_of_samples;
    float cumulative_sum;
};

static uint32_t instance_counter = 0U;
static uz_filter_cumulativeavg_t instances[UZ_FILTER_CUMULATIVEAVG_MAX_INSTANCES] = {0};

static uz_filter_cumulativeavg_t *uz_filter_cumulativeavg_allocation(void);

static uz_filter_cumulativeavg_t *uz_filter_cumulativeavg_allocation(void)
{
    uz_assert(instance_counter < UZ_FILTER_CUMULATIVEAVG_MAX_INSTANCES);
    uz_filter_cumulativeavg_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_filter_cumulativeavg_t *uz_filter_cumulativeavg_init(void)
{
    uz_filter_cumulativeavg_t *self = uz_filter_cumulativeavg_allocation();
    self->number_of_samples = 0.0f;
    self->cumulative_sum = 0.0f;
    return (self);
}

float uz_filter_cumulativeavg_step(uz_filter_cumulativeavg_t *self, float current_value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->number_of_samples += 1.0f;
    self->cumulative_sum += current_value;
    return (self->cumulative_sum/ self->number_of_samples);
}

void uz_filter_cumulativeavg_reset(uz_filter_cumulativeavg_t *self)
{
    uz_assert_not_NULL(self);
    self->number_of_samples = 0.0f;
    self->cumulative_sum = 0.0f;
}

#endif