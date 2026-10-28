#include "uz_resolver_pos_mt.h"

#include "../../uz/uz_global_configuration.h"
#if UZ_RESOLVER_POS_MT_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "uz_resolver_pos_mt_hw.h"

struct uz_resolver_pos_mt_t {
    bool is_ready;
    struct uz_resolver_pos_mt_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_resolver_pos_mt_t instances[UZ_RESOLVER_POS_MT_MAX_INSTANCES] = { 0 };

static uz_resolver_pos_mt_t* uz_resolver_pos_mt_allocation(void);

static uz_resolver_pos_mt_t* uz_resolver_pos_mt_allocation(void) {
    uz_assert(instance_counter < UZ_RESOLVER_POS_MT_MAX_INSTANCES);
    uz_resolver_pos_mt_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_resolver_pos_mt_t* uz_resolver_pos_mt_init(struct uz_resolver_pos_mt_config_t config) {
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_clk_frequency_Hz);
    uz_resolver_pos_mt_t* self = uz_resolver_pos_mt_allocation();
    self->config = config;
    return (self);
}

struct uz_resolver_pos_mt_outputs_t uz_resolver_pos_mt_get_outputs(uz_resolver_pos_mt_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_resolver_pos_mt_outputs_t outputs = { 0 };
    outputs.multiturn_position = uz_resolver_pos_mt_hw_read_multiturn_position(self->config.base_address);
    outputs.turns_cnt = uz_resolver_pos_mt_hw_read_turns_cnt(self->config.base_address);
    outputs.pos_mt_valid = uz_resolver_pos_mt_hw_read_pos_mt_valid(self->config.base_address);
    outputs.turns = (int32_t)(outputs.multiturn_position >> 16);
    outputs.singleturn_raw = (uint16_t)((uint64_t)outputs.multiturn_position & 0xFFFFU);
    return (outputs);
}

void uz_resolver_pos_mt_reset(uz_resolver_pos_mt_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_resolver_pos_mt_hw_write_reset(self->config.base_address, true);
    uz_resolver_pos_mt_hw_write_reset(self->config.base_address, false);
}

void uz_resolver_pos_mt_load_preset(uz_resolver_pos_mt_t *self, int64_t pos_mt_preset) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Preset value must be stable before the load pulse
    uz_resolver_pos_mt_hw_write_pos_mt_preset(self->config.base_address, pos_mt_preset);
    uz_resolver_pos_mt_hw_write_load_position(self->config.base_address, true);
    uz_resolver_pos_mt_hw_write_load_position(self->config.base_address, false);
}
#endif
