#include "uz_pmsm_swmodel.h"
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
    float i_d_A;    /**< Current in d-axis in A */
    float i_q_A;    /**< Current in q-Axis in A */
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
    self->i_d_A = 0.0f;
    self->i_q_A = 0.0f;
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


        // Hier gibts einen bug mit i_k0 und i_k1 -> neue Variablen
        // dq data type nutzen.
    const float omega_el_1_s = inputs.omega_mech_1_s * self->pmsm_parameters.polePairs;
    float psi_d_Vs = self->pmsm_parameters.Ld_Henry * self->i_d_A + self->pmsm_parameters.Psi_PM_Vs;
    float psi_q_Vs = self->pmsm_parameters.Lq_Henry * self->i_q_A;
    float did_dt = (inputs.v_d_V - self->pmsm_parameters.R_ph_Ohm * self->i_d_A + psi_q_Vs * omega_el_1_s) / self->pmsm_parameters.Ld_Henry;
    float diq_dt = (inputs.v_q_V - self->pmsm_parameters.R_ph_Ohm * self->i_q_A - psi_d_Vs * omega_el_1_s) / self->pmsm_parameters.Lq_Henry;
    self->i_d_A = uz_integrator_eulerforward(did_dt, self->i_d_A, self->sample_time, false);
    self->i_q_A = uz_integrator_eulerforward(diq_dt, self->i_q_A, self->sample_time, false);
    outputs.torque_Nm = 1.5f * self->pmsm_parameters.polePairs * (psi_d_Vs * self->i_q_A - psi_q_Vs * self->i_d_A);
    outputs.i_d_A = self->i_d_A;
    outputs.i_q_A = self->i_q_A;
    outputs.omega_mech_1_s = inputs.omega_mech_1_s;
    return outputs;
}

#endif