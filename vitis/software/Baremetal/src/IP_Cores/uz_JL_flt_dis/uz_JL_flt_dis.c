
#include "../../uz/uz_global_configuration.h"
#if UZ_JL_FLT_DIS_MAX_INSTANCES > 0U
#include "uz_JL_flt_dis.h"
#include "uz_JL_flt_dis_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

struct uz_JL_flt_dis_t {
    bool is_ready;
    struct uz_JL_flt_dis_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_JL_flt_dis_t instances[UZ_JL_FLT_DIS_MAX_INSTANCES] = {0};

static uz_JL_flt_dis_t *uz_JL_flt_dis_allocation(void);

static uz_JL_flt_dis_t *uz_JL_flt_dis_allocation(void)
{
    uz_assert(instance_counter < UZ_JL_FLT_DIS_MAX_INSTANCES);
    uz_JL_flt_dis_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_JL_flt_dis_t *uz_JL_flt_dis_init(struct uz_JL_flt_dis_config_t config)
{
    uz_assert_not_zero(config.ip_core_frequency_Hz);
    uz_assert_not_zero(config.base_address);
    uz_JL_flt_dis_t *self = uz_JL_flt_dis_allocation();
    self->config = config;
    uz_JL_flt_dis_set_use_flt_dis(self, config.use_flt_dis);
    return (self);
}

void uz_JL_flt_dis_set_FLT_PS(uz_JL_flt_dis_t *self, bool flt_ps)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_JL_flt_dis_hw_write_FLT_PS(self->config.base_address, flt_ps);
}

void uz_JL_flt_dis_set_use_flt_dis(uz_JL_flt_dis_t *self, bool use_flt_dis)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->config.use_flt_dis = use_flt_dis;
    uz_JL_flt_dis_hw_write_use_flt_dis(self->config.base_address, use_flt_dis);
}

void uz_JL_flt_dis_reset_fault(uz_JL_flt_dis_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Reset the latched fault by forcing a rising/falling edge on FLT_RST
    uz_JL_flt_dis_hw_write_FLT_RST(self->config.base_address, true);
    uz_JL_flt_dis_hw_write_FLT_RST(self->config.base_address, false);
}

enum uz_JL_flt_dis_fault uz_JL_flt_dis_get_fault(uz_JL_flt_dis_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return (enum uz_JL_flt_dis_fault)uz_JL_flt_dis_hw_read_FLT_ps(self->config.base_address);
}
#endif
