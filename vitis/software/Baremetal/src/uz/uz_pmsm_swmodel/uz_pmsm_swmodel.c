#include "../uz_global_configuration.h"
#if UZ_PMSM_SWMODEL_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_pmsm_swmodel.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_integrator/uz_integrator.h"

struct uz_pmsm_swmodel_t
{
    bool is_ready;
    float sample_time;
    struct uz_PMSM_t pmsm_parameters;
    uz_3ph_dq_t i_dq_A_k0;
    float inverse_Ld; // Precompute inductance for reducing divisions
    float inverse_Lq; // Precompute inductance for reducing divisions
};

static uint32_t instance_counter = 0U;
static uz_pmsm_swmodel_t instances[UZ_PMSM_SWMODEL_MAX_INSTANCES] = {0};

static uz_pmsm_swmodel_t *uz_pmsm_swmodel_allocation(void);

static uz_pmsm_swmodel_t *uz_pmsm_swmodel_allocation(void)
{
    uz_assert(instance_counter < UZ_PMSM_SWMODEL_MAX_INSTANCES);
    uz_pmsm_swmodel_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_pmsm_swmodel_t *uz_pmsm_swmodel_init(struct uz_pmsm_swmodel_config_t config)
{
    uz_PMSM_config_assert(config.pmsm_parameters);
    uz_assert(config.sample_time > 0.0f);
    uz_assert(config.pmsm_parameters.Ld_Henry > 0.0f);
    uz_assert(config.pmsm_parameters.Lq_Henry > 0.0f);
    uz_pmsm_swmodel_t *self = uz_pmsm_swmodel_allocation();
    self->pmsm_parameters = config.pmsm_parameters;
    self->sample_time = config.sample_time;
    self->inverse_Ld = 1.0f / config.pmsm_parameters.Ld_Henry;
    self->inverse_Lq = 1.0f / config.pmsm_parameters.Lq_Henry;
    return (self);
}

struct uz_pmsm_swmodel_outputs_t uz_pmsm_swmodel_step(uz_pmsm_swmodel_t *self, struct uz_pmsm_swmodel_inputs_t inputs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_pmsm_swmodel_outputs_t outputs = {
        .i_d_A = 0.0f,
        .i_q_A = 0.0f,
        .torque_Nm = 0.0f,
        .omega_mech_1_s = 0.0f};

    const float omega_el_1_s_k0 = inputs.omega_mech_1_s * self->pmsm_parameters.polePairs;
    const float psi_d_Vs_k0 = self->pmsm_parameters.Ld_Henry * self->i_dq_A_k0.d + self->pmsm_parameters.Psi_PM_Vs;
    const float psi_q_Vs_k0 = self->pmsm_parameters.Lq_Henry * self->i_dq_A_k0.q;
    const float did_dt = (inputs.v_d_V - self->pmsm_parameters.R_ph_Ohm * self->i_dq_A_k0.d + psi_q_Vs_k0 * omega_el_1_s_k0) * self->inverse_Ld;
    const float diq_dt = (inputs.v_q_V - self->pmsm_parameters.R_ph_Ohm * self->i_dq_A_k0.q - psi_d_Vs_k0 * omega_el_1_s_k0) * self->inverse_Lq;
    uz_3ph_dq_t i_dq_A_k1={
        .d = uz_integrator_eulerforward(did_dt, self->i_dq_A_k0.d, self->sample_time, false),
        .q = uz_integrator_eulerforward(diq_dt, self->i_dq_A_k0.q, self->sample_time, false),
        .zero = 0.0f
    };
    const float psi_d_Vs_k1 = self->pmsm_parameters.Ld_Henry * i_dq_A_k1.d + self->pmsm_parameters.Psi_PM_Vs;
    const float psi_q_Vs_k1 = self->pmsm_parameters.Lq_Henry * i_dq_A_k1.q;
    outputs.torque_Nm = 1.5f * self->pmsm_parameters.polePairs * (psi_d_Vs_k1 * i_dq_A_k1.q - psi_q_Vs_k1 * i_dq_A_k1.d);
    outputs.i_d_A = i_dq_A_k1.d;
    outputs.i_q_A = i_dq_A_k1.q;
    outputs.omega_mech_1_s = inputs.omega_mech_1_s;
    self->i_dq_A_k0 = i_dq_A_k1;
    return outputs;
}

#endif