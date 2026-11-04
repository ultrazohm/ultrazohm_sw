
#include "../../uz/uz_global_configuration.h"
#if UZ_JL_FLT_DIS_MAX_INSTANCES > 0U
#include "uz_JL_flt_dis.h"
#include "uz_JL_flt_dis_hw.h"
#include <stdbool.h>
#include "../../uz/uz_HAL.h"

#define WATCHDOG_MAX_CNTS_LIMIT 0xFFFFFU // 20-bit counter in the IP core (2^20 - 1)

struct uz_JL_flt_dis_t {
    bool is_ready;
    struct uz_JL_flt_dis_config_t config;
    bool watchdog_trig_state; // tracked state of the Watchdog_trig bit, toggled on every trigger call
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
    uz_assert_not_zero(config.isr_frequency_Hz);
    uz_assert_not_zero(config.watchdog_timeout_ISR_periods);
    // Watchdog timeout: the IP core counter increments by 1 per FPGA clock. The fault latches when
    // count > Max_Cnts, so Max_Cnts = f_clk / f_ISR * N (N = allowed ISR periods without a trigger).
    // Division first keeps the intermediate value small and avoids a uint32 overflow.
    uint32_t max_cnts = (config.ip_core_frequency_Hz / config.isr_frequency_Hz) * config.watchdog_timeout_ISR_periods;
    uz_assert(max_cnts <= WATCHDOG_MAX_CNTS_LIMIT); // timeout must fit into the 20-bit counter
    uz_JL_flt_dis_t *self = uz_JL_flt_dis_allocation();
    self->config = config;
    self->watchdog_trig_state = false;
    uz_JL_flt_dis_set_use_flt_dis(self, config.use_flt_dis);
    uz_JL_flt_dis_hw_write_Watchdog_Periods_Max_Cnts(config.base_address, max_cnts);
    // Resting state of Watchdog_Rst: high disables the watchdog, low arms it.
    uz_JL_flt_dis_hw_write_Watchdog_Rst(config.base_address, config.disable_watchdog);
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

void uz_JL_flt_dis_watchdog_trigger(uz_JL_flt_dis_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Toggle the trigger bit to create an edge, which resets the watchdog counter in the IP core.
    self->watchdog_trig_state = !self->watchdog_trig_state;
    uz_JL_flt_dis_hw_write_Watchdog_trig(self->config.base_address, self->watchdog_trig_state);
}

void uz_JL_flt_dis_watchdog_reset(uz_JL_flt_dis_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // Pulse the reset high to clear a latched watchdog fault, then return to the configured resting
    // state (high keeps a config-disabled watchdog disabled, low re-arms an active watchdog).
    uz_JL_flt_dis_hw_write_Watchdog_Rst(self->config.base_address, true);
    uz_JL_flt_dis_hw_write_Watchdog_Rst(self->config.base_address, self->config.disable_watchdog);
}
#endif
