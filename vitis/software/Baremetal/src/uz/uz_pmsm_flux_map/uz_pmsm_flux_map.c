#include "../uz_global_configuration.h"
#if UZ_PMSM_FLUX_MAP_MAX_INSTANCES > 0U

#include <stdbool.h>
#include "uz_pmsm_flux_map.h"
#include "../uz_HAL.h"
#include "../uz_LUT_2D/uz_LUT_2D.h"

struct uz_pmsm_flux_map_t
{
    bool is_ready;
    // The uz_array_float_t descriptors are stored by value so their addresses stay stable;
    // uz_LUT_2D_init keeps pointers to them. The underlying float data stays caller-owned.
    uz_array_float_t i_d_breakpoints_A;
    uz_array_float_t i_q_breakpoints_A;
    uz_array_float_t psi_d_Vs;
    uz_array_float_t psi_q_Vs;
    uz_LUT_2D_t *psi_d_lut;
    uz_LUT_2D_t *psi_q_lut;
};

static uint32_t instance_counter = 0U;
static uz_pmsm_flux_map_t instances[UZ_PMSM_FLUX_MAP_MAX_INSTANCES] = {0};

static uz_pmsm_flux_map_t *uz_pmsm_flux_map_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_FLUX_MAP_MAX_INSTANCES);
    uz_pmsm_flux_map_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return self;
}

uz_pmsm_flux_map_t *uz_pmsm_flux_map_init(struct uz_pmsm_flux_map_config_t config)
{
    uz_assert_not_NULL(config.i_d_breakpoints_A.data);
    uz_assert_not_NULL(config.i_q_breakpoints_A.data);
    uz_assert_not_NULL(config.psi_d_Vs.data);
    uz_assert_not_NULL(config.psi_q_Vs.data);
    const uint32_t grid_length = config.i_d_breakpoints_A.length * config.i_q_breakpoints_A.length;
    uz_assert(config.psi_d_Vs.length == grid_length);
    uz_assert(config.psi_q_Vs.length == grid_length);

    uz_pmsm_flux_map_t *self = uz_pmsm_flux_map_allocation();
    self->i_d_breakpoints_A = config.i_d_breakpoints_A;
    self->i_q_breakpoints_A = config.i_q_breakpoints_A;
    self->psi_d_Vs = config.psi_d_Vs;
    self->psi_q_Vs = config.psi_q_Vs;
    // x-axis is i_d, y-axis is i_q; data is row-major with i_d fastest (matches uz_LUT_2D).
    self->psi_d_lut = uz_LUT_2D_init(&self->i_d_breakpoints_A, &self->i_q_breakpoints_A, &self->psi_d_Vs);
    self->psi_q_lut = uz_LUT_2D_init(&self->i_d_breakpoints_A, &self->i_q_breakpoints_A, &self->psi_q_Vs);
    return self;
}

uz_3ph_dq_t uz_pmsm_flux_map_get_psi_dq_Vs(uz_pmsm_flux_map_t *self, uz_3ph_dq_t i_dq_A)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_3ph_dq_t psi_dq_Vs = {
        .d = uz_LUT_2D_get_value(self->psi_d_lut, i_dq_A.d, i_dq_A.q),
        .q = uz_LUT_2D_get_value(self->psi_q_lut, i_dq_A.d, i_dq_A.q),
        .zero = 0.0f};
    return psi_dq_Vs;
}

#endif
