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
    enum uz_pmsm_swmodel_integration_method_t integration_method;
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
    uz_pmsm_swmodel_t *self = uz_pmsm_swmodel_allocation();
    self->pmsm_parameters = config.pmsm_parameters;
    self->sample_time = config.sample_time;
    self->integration_method = config.integration_method;
    self->inverse_Ld = 1.0f / config.pmsm_parameters.Ld_Henry;
    self->inverse_Lq = 1.0f / config.pmsm_parameters.Lq_Henry;
    return (self);
}

void uz_pmsm_swmodel_reset(uz_pmsm_swmodel_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->i_dq_A_k0.d = 0.0f;
    self->i_dq_A_k0.q = 0.0f;
    self->i_dq_A_k0.zero = 0.0f;

}

/*
 * Right-hand side of the electrical dq current ODE: did/dt and diq/dt for a given
 * current, applied voltage and (ZOH-constant) electrical speed. Pure helper so both
 * the Euler and the Heun stages evaluate the exact same dynamics. The flux linkages
 * psi_d = Ld*i_d + psi_PM and psi_q = Lq*i_q are recomputed from the passed current,
 * which is what lets Heun capture the within-step current->flux->derivative coupling.
 */
static uz_3ph_dq_t swmodel_didq_dt(const uz_pmsm_swmodel_t *self, uz_3ph_dq_t i_dq, uz_3ph_dq_t v_dq, float omega_el)
{
    const float psi_d_Vs = self->pmsm_parameters.Ld_Henry * i_dq.d + self->pmsm_parameters.Psi_PM_Vs;
    const float psi_q_Vs = self->pmsm_parameters.Lq_Henry * i_dq.q;
    uz_3ph_dq_t didq_dt = {
        .d = (v_dq.d - self->pmsm_parameters.R_ph_Ohm * i_dq.d + psi_q_Vs * omega_el) * self->inverse_Ld,
        .q = (v_dq.q - self->pmsm_parameters.R_ph_Ohm * i_dq.q - psi_d_Vs * omega_el) * self->inverse_Lq,
        .zero = 0.0f};
    return didq_dt;
}

struct uz_pmsm_swmodel_outputs_t uz_pmsm_swmodel_step(uz_pmsm_swmodel_t *self, struct uz_pmsm_swmodel_inputs_t inputs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    struct uz_pmsm_swmodel_outputs_t outputs = {
        .i_dq_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f},
        .torque_Nm = 0.0f,
        .omega_mech_1_s = 0.0f};

    const float omega_el_1_s = inputs.omega_mech_1_s * self->pmsm_parameters.polePairs;
    const uz_3ph_dq_t didq_dt_k0 = swmodel_didq_dt(self, self->i_dq_A_k0, inputs.v_dq_V, omega_el_1_s);

    uz_3ph_dq_t i_dq_A_k1 = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
    if (self->integration_method == uz_pmsm_swmodel_heun)
    {
        // Euler predictor, re-evaluate the derivative at the predicted current (flux psi(i) is
        // recomputed there), then trapezoidal corrector via Heun's method.
        const uz_3ph_dq_t i_dq_A_predicted = {
            .d = uz_integrator_eulerforward(didq_dt_k0.d, self->i_dq_A_k0.d, self->sample_time, false),
            .q = uz_integrator_eulerforward(didq_dt_k0.q, self->i_dq_A_k0.q, self->sample_time, false),
            .zero = 0.0f};
        const uz_3ph_dq_t didq_dt_predicted = swmodel_didq_dt(self, i_dq_A_predicted, inputs.v_dq_V, omega_el_1_s);
        i_dq_A_k1.d = uz_integrator_heun(didq_dt_k0.d, didq_dt_predicted.d, self->i_dq_A_k0.d, self->sample_time, false);
        i_dq_A_k1.q = uz_integrator_heun(didq_dt_k0.q, didq_dt_predicted.q, self->i_dq_A_k0.q, self->sample_time, false);
    }
    else
    {
        i_dq_A_k1.d = uz_integrator_eulerforward(didq_dt_k0.d, self->i_dq_A_k0.d, self->sample_time, false);
        i_dq_A_k1.q = uz_integrator_eulerforward(didq_dt_k0.q, self->i_dq_A_k0.q, self->sample_time, false);
    }

    const float psi_d_Vs_k1 = self->pmsm_parameters.Ld_Henry * i_dq_A_k1.d + self->pmsm_parameters.Psi_PM_Vs;
    const float psi_q_Vs_k1 = self->pmsm_parameters.Lq_Henry * i_dq_A_k1.q;
    outputs.torque_Nm = 1.5f * self->pmsm_parameters.polePairs * (psi_d_Vs_k1 * i_dq_A_k1.q - psi_q_Vs_k1 * i_dq_A_k1.d);
    outputs.i_dq_A = i_dq_A_k1;
    outputs.omega_mech_1_s = inputs.omega_mech_1_s;
    self->i_dq_A_k0 = i_dq_A_k1;
    return outputs;
}

#endif