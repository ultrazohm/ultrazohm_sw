#include "../uz_global_configuration.h"
#if UZ_PMSM_DIFFERENTIAL_INDUCTANCE_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "uz_pmsm_differential_inductance.h"
#include "../uz_HAL.h"
#include "../uz_LUT_2D/uz_LUT_2D.h"

struct uz_pmsm_differential_inductance_t
{
    bool is_ready;
    // The uz_array_float_t descriptors are stored by value so their addresses stay stable;
    // uz_LUT_2D_init keeps pointers to them. The underlying float data stays caller-owned.
    uz_array_float_t i_d_breakpoints_A;
    uz_array_float_t i_q_breakpoints_A;
    uz_array_float_t L_dd_H;
    uz_array_float_t L_dq_H;
    uz_array_float_t L_qd_H;
    uz_array_float_t L_qq_H;
    uz_LUT_2D_t *L_dd_lut;
    uz_LUT_2D_t *L_dq_lut;
    uz_LUT_2D_t *L_qd_lut;
    uz_LUT_2D_t *L_qq_lut;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_differential_inductance_t instances[UZ_PMSM_DIFFERENTIAL_INDUCTANCE_MAX_INSTANCES] = {0};

static uz_pmsm_differential_inductance_t *uz_pmsm_differential_inductance_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_DIFFERENTIAL_INDUCTANCE_MAX_INSTANCES);
    uz_pmsm_differential_inductance_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return self;
}

uz_pmsm_differential_inductance_t *uz_pmsm_differential_inductance_init(struct uz_pmsm_differential_inductance_config_t config)
{
    uz_assert_not_NULL(config.i_d_breakpoints_A.data);
    uz_assert_not_NULL(config.i_q_breakpoints_A.data);
    uz_assert_not_NULL(config.L_dd_H.data);
    uz_assert_not_NULL(config.L_dq_H.data);
    uz_assert_not_NULL(config.L_qd_H.data);
    uz_assert_not_NULL(config.L_qq_H.data);
    const uint32_t grid_length = config.i_d_breakpoints_A.length * config.i_q_breakpoints_A.length;
    uz_assert(config.L_dd_H.length == grid_length);
    uz_assert(config.L_dq_H.length == grid_length);
    uz_assert(config.L_qd_H.length == grid_length);
    uz_assert(config.L_qq_H.length == grid_length);

    uz_pmsm_differential_inductance_t *self = uz_pmsm_differential_inductance_allocation();
    self->i_d_breakpoints_A = config.i_d_breakpoints_A;
    self->i_q_breakpoints_A = config.i_q_breakpoints_A;
    self->L_dd_H = config.L_dd_H;
    self->L_dq_H = config.L_dq_H;
    self->L_qd_H = config.L_qd_H;
    self->L_qq_H = config.L_qq_H;
    // x-axis is i_d, y-axis is i_q; data is row-major with i_d fastest (matches uz_LUT_2D).
    self->L_dd_lut = uz_LUT_2D_init(&self->i_d_breakpoints_A, &self->i_q_breakpoints_A, &self->L_dd_H);
    self->L_dq_lut = uz_LUT_2D_init(&self->i_d_breakpoints_A, &self->i_q_breakpoints_A, &self->L_dq_H);
    self->L_qd_lut = uz_LUT_2D_init(&self->i_d_breakpoints_A, &self->i_q_breakpoints_A, &self->L_qd_H);
    self->L_qq_lut = uz_LUT_2D_init(&self->i_d_breakpoints_A, &self->i_q_breakpoints_A, &self->L_qq_H);
    return self;
}

float uz_pmsm_differential_inductance_get_L_dd_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_LUT_2D_get_value(self->L_dd_lut, i_dq_A.d, i_dq_A.q);
}

float uz_pmsm_differential_inductance_get_L_dq_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_LUT_2D_get_value(self->L_dq_lut, i_dq_A.d, i_dq_A.q);
}

float uz_pmsm_differential_inductance_get_L_qd_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_LUT_2D_get_value(self->L_qd_lut, i_dq_A.d, i_dq_A.q);
}

float uz_pmsm_differential_inductance_get_L_qq_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return uz_LUT_2D_get_value(self->L_qq_lut, i_dq_A.d, i_dq_A.q);
}

#endif
