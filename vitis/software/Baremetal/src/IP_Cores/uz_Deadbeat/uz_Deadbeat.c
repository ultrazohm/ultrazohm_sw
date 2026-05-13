#include "uz_Deadbeat.h"
#include "uz_Deadbeat_hw.h"
#include "../../uz/uz_HAL.h"
#include <stdbool.h>
#include <stdint.h>

struct uz_Deadbeat_t {
    bool is_ready;
    struct uz_Deadbeat_config_t config;
};

static int32_t to_sfix24_En16(float x)
{
    return (int32_t)(x * 65536.0f);
}

static int32_t to_sfix24_En20(float x)
{
    return (int32_t)(x * 1048576.0f);
}

static int32_t to_sfix24_En8(float x)
{
    return (int32_t)(x * 256.0f);
}

static float from_sfix24_En16(int32_t x)
{
    return ((float)x) / 65536.0f;
}

uz_Deadbeat_t* uz_Deadbeat_init(struct uz_Deadbeat_config_t config)
{
    uz_assert_not_zero(config.base_address);
    uz_assert_not_zero(config.ip_clk_frequency_Hz);

    static uz_Deadbeat_t instance;
    instance.config = config;
    instance.is_ready = true;

    return &instance;
}

void uz_Deadbeat_write_inputs(
    uz_Deadbeat_t* self,
    const struct uz_Deadbeat_inputs_t* inputs
)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_assert_not_NULL(inputs);

    uint32_t base = self->config.base_address;

    uz_Deadbeat_hw_write_id_ref(base, to_sfix24_En16(inputs->id_ref));
    uz_Deadbeat_hw_write_iq_ref(base, to_sfix24_En16(inputs->iq_ref));
    uz_Deadbeat_hw_write_id(base, to_sfix24_En16(inputs->id));
    uz_Deadbeat_hw_write_iq(base, to_sfix24_En16(inputs->iq));

    uz_Deadbeat_hw_write_theta(base, to_sfix24_En20(inputs->theta));
    uz_Deadbeat_hw_write_theta_0(base, to_sfix24_En20(inputs->theta_0));
    uz_Deadbeat_hw_write_w_e(base, to_sfix24_En8(inputs->w_e));

    uz_Deadbeat_hw_write_ua_0(base, to_sfix24_En16(inputs->ua_0_input));
    uz_Deadbeat_hw_write_ub_0(base, to_sfix24_En16(inputs->ub_0_input));
    uz_Deadbeat_hw_write_uc_0(base, to_sfix24_En16(inputs->uc_0_input));
}

struct uz_Deadbeat_outputs_t uz_Deadbeat_read_outputs(
    uz_Deadbeat_t* self
)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    uint32_t base = self->config.base_address;

    struct uz_Deadbeat_outputs_t out;

    out.ua_0 = from_sfix24_En16(uz_Deadbeat_hw_read_ua_0(base));
    out.ub_o = from_sfix24_En16(uz_Deadbeat_hw_read_ub_o(base));
    out.uc_0 = from_sfix24_En16(uz_Deadbeat_hw_read_uc_0(base));

    return out;
}
