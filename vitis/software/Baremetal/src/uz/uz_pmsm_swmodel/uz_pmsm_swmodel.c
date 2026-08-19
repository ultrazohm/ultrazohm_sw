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
    enum uz_pmsm_swmodel_integrator_state_t integrator_state;
    bool preload_flux_state;
    bool simulate_mechanical_system;
    float coulomb_friction_constant;
    float friction_coefficient;
    uz_3ph_dq_t integrator_state_k0; // electrical state at k=0: current (A) or flux (Vs) per integrator_state
    float omega_mech_1_s_k0;         // mechanical speed state at k=0 (only used if simulate_mechanical_system)
    float inverse_Ld;                // Precompute inductance for reducing divisions
    float inverse_Lq;                // Precompute inductance for reducing divisions
    float inverse_J;                 // Precomputed 1/J to avoid divisions per step; init asserts J > 0
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
    uz_assert(config.coulomb_friction_constant >= 0.0f);
    uz_assert(config.friction_coefficient >= 0.0f);
    uz_pmsm_swmodel_t *self = uz_pmsm_swmodel_allocation();
    self->pmsm_parameters = config.pmsm_parameters;
    self->sample_time = config.sample_time;
    self->integration_method = config.integration_method;
    self->integrator_state = config.integrator_state;
    self->preload_flux_state = config.preload_flux_state;
    self->simulate_mechanical_system = config.simulate_mechanical_system;
    self->coulomb_friction_constant = config.coulomb_friction_constant;
    self->friction_coefficient = config.friction_coefficient;
    self->inverse_Ld = 1.0f / config.pmsm_parameters.Ld_Henry;
    self->inverse_Lq = 1.0f / config.pmsm_parameters.Lq_Henry;
    self->inverse_J = 1.0f / config.pmsm_parameters.J_kg_m_squared;
    uz_pmsm_swmodel_reset(self);
    return (self);
}

void uz_pmsm_swmodel_reset(uz_pmsm_swmodel_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->omega_mech_1_s_k0 = 0.0f;
    if (self->preload_flux_state && self->integrator_state == uz_pmsm_swmodel_integrator_state_flux)
    {
        self->integrator_state_k0.d = self->pmsm_parameters.Psi_PM_Vs;
        self->integrator_state_k0.q = 0.0f;
    }
    else
    {
        self->integrator_state_k0.d = 0.0f;
        self->integrator_state_k0.q = 0.0f;
    }
    self->integrator_state_k0.zero = 0.0f;
}

/* Decoded electrical quantities: both current and flux, derived from the integrator state. */
struct swmodel_electrical_t
{
    uz_3ph_dq_t i_dq_A;
    uz_3ph_dq_t psi_dq_Vs;
};

/* Coupled state derivative: d/dt of the electrical integrator state and of the mechanical speed. */
struct swmodel_derivative_t
{
    uz_3ph_dq_t electrical;
    float omega_mech_1_s;
};

/*
 * Recover current and flux from the electrical integrator state, honouring the chosen
 * representation. In current mode psi = L*i + psi_PM is derived; in flux mode i = (psi - psi_PM)/L.
 */
static struct swmodel_electrical_t swmodel_decode(const uz_pmsm_swmodel_t *self, uz_3ph_dq_t electrical_state)
{
    struct swmodel_electrical_t electrical = {.i_dq_A = {0}, .psi_dq_Vs = {0}};
    if (self->integrator_state == uz_pmsm_swmodel_integrator_state_flux)
    {
        electrical.psi_dq_Vs = electrical_state;
        electrical.i_dq_A.d = (electrical_state.d - self->pmsm_parameters.Psi_PM_Vs) * self->inverse_Ld;
        electrical.i_dq_A.q = electrical_state.q * self->inverse_Lq;
    }
    else
    {
        electrical.i_dq_A = electrical_state;
        electrical.psi_dq_Vs.d = self->pmsm_parameters.Ld_Henry * electrical_state.d + self->pmsm_parameters.Psi_PM_Vs;
        electrical.psi_dq_Vs.q = self->pmsm_parameters.Lq_Henry * electrical_state.q;
    }
    return electrical;
}

static float swmodel_inner_torque_Nm(const uz_pmsm_swmodel_t *self, struct swmodel_electrical_t electrical)
{
    return 1.5f * self->pmsm_parameters.polePairs * (electrical.psi_dq_Vs.d * electrical.i_dq_A.q - electrical.psi_dq_Vs.q * electrical.i_dq_A.d);
}

/* Coulomb + viscous friction torque: M_F = sign(omega)*(M_R0 + mu*|omega|). */
static float swmodel_friction_torque_Nm(const uz_pmsm_swmodel_t *self, float omega_mech_1_s)
{
    float magnitude = omega_mech_1_s;
    if (omega_mech_1_s < 0.0f)
    {
        magnitude = -omega_mech_1_s;
    }
    const float friction_Nm = self->coulomb_friction_constant + self->friction_coefficient * magnitude;
    if (omega_mech_1_s > 0.0f)
    {
        return friction_Nm;
    }
    if (omega_mech_1_s < 0.0f)
    {
        return -friction_Nm;
    }
    return 0.0f;
}

/*
 * Right-hand side of the coupled ODE evaluated at a given state. The shared voltage balance
 * e = v - R*i + omega_el x psi feeds either the current derivative (e/L) or the flux derivative (e),
 * depending on the integrator state. The mechanical derivative follows the torque balance
 * dω/dt = (M_i - M_F - T_L)/J and is zero when the mechanical system is not simulated.
 * Pure helper so the Euler and Heun stages evaluate identical dynamics.
 */
static struct swmodel_derivative_t swmodel_derivative(const uz_pmsm_swmodel_t *self, uz_3ph_dq_t electrical_state, float omega_mech_1_s, uz_3ph_dq_t v_dq_V, float load_torque_Nm)
{
    const float omega_el_1_s = omega_mech_1_s * self->pmsm_parameters.polePairs;
    const struct swmodel_electrical_t electrical = swmodel_decode(self, electrical_state);

    const float e_d = v_dq_V.d - self->pmsm_parameters.R_ph_Ohm * electrical.i_dq_A.d + omega_el_1_s * electrical.psi_dq_Vs.q;
    const float e_q = v_dq_V.q - self->pmsm_parameters.R_ph_Ohm * electrical.i_dq_A.q - omega_el_1_s * electrical.psi_dq_Vs.d;

    struct swmodel_derivative_t derivative = {.electrical = {0}, .omega_mech_1_s = 0.0f};
    if (self->integrator_state == uz_pmsm_swmodel_integrator_state_flux)
    {
        derivative.electrical.d = e_d;
        derivative.electrical.q = e_q;
    }
    else
    {
        derivative.electrical.d = e_d * self->inverse_Ld;
        derivative.electrical.q = e_q * self->inverse_Lq;
    }

    if (self->simulate_mechanical_system)
    {
        const float torque_Nm = swmodel_inner_torque_Nm(self, electrical);
        const float friction_Nm = swmodel_friction_torque_Nm(self, omega_mech_1_s);
        derivative.omega_mech_1_s = (torque_Nm - friction_Nm - load_torque_Nm) * self->inverse_J;
    }
    return derivative;
}

struct uz_pmsm_swmodel_outputs_t uz_pmsm_swmodel_step(uz_pmsm_swmodel_t *self, struct uz_pmsm_swmodel_inputs_t inputs)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);

    const bool simulate_mechanical_system = self->simulate_mechanical_system;
    const uz_3ph_dq_t state_k0 = self->integrator_state_k0;
    // When simulating, the rotor speed is a state; otherwise it is taken from the input (passthrough).
    float omega_mech_1_s_k0 = inputs.omega_mech_1_s;
    if (simulate_mechanical_system)
    {
        omega_mech_1_s_k0 = self->omega_mech_1_s_k0;
    }

    const struct swmodel_derivative_t derivative_k0 = swmodel_derivative(self, state_k0, omega_mech_1_s_k0, inputs.v_dq_V, inputs.load_torque);

    uz_3ph_dq_t state_k1 = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
    float omega_mech_1_s_k1 = omega_mech_1_s_k0;
    if (self->integration_method == uz_pmsm_swmodel_heun)
    {
        // Euler predictor for the whole coupled state, re-evaluate the derivative there (recomputing
        // flux psi(i), torque and friction), then trapezoidal corrector via Heun's method.
        const uz_3ph_dq_t state_predicted = {
            .d = uz_integrator_eulerforward(derivative_k0.electrical.d, state_k0.d, self->sample_time, false),
            .q = uz_integrator_eulerforward(derivative_k0.electrical.q, state_k0.q, self->sample_time, false),
            .zero = 0.0f};
        float omega_predicted = omega_mech_1_s_k0;
        if (simulate_mechanical_system)
        {
            omega_predicted = uz_integrator_eulerforward(derivative_k0.omega_mech_1_s, omega_mech_1_s_k0, self->sample_time, false);
        }
        const struct swmodel_derivative_t derivative_predicted = swmodel_derivative(self, state_predicted, omega_predicted, inputs.v_dq_V, inputs.load_torque);
        state_k1.d = uz_integrator_heun(derivative_k0.electrical.d, derivative_predicted.electrical.d, state_k0.d, self->sample_time, false);
        state_k1.q = uz_integrator_heun(derivative_k0.electrical.q, derivative_predicted.electrical.q, state_k0.q, self->sample_time, false);
        if (simulate_mechanical_system)
        {
            omega_mech_1_s_k1 = uz_integrator_heun(derivative_k0.omega_mech_1_s, derivative_predicted.omega_mech_1_s, omega_mech_1_s_k0, self->sample_time, false);
        }
    }
    else
    {
        state_k1.d = uz_integrator_eulerforward(derivative_k0.electrical.d, state_k0.d, self->sample_time, false);
        state_k1.q = uz_integrator_eulerforward(derivative_k0.electrical.q, state_k0.q, self->sample_time, false);
        if (simulate_mechanical_system)
        {
            omega_mech_1_s_k1 = uz_integrator_eulerforward(derivative_k0.omega_mech_1_s, omega_mech_1_s_k0, self->sample_time, false);
        }
    }

    // Post-update outputs (k=1), single precision, matching the swmodel convention.
    const struct swmodel_electrical_t electrical_k1 = swmodel_decode(self, state_k1);
    struct uz_pmsm_swmodel_outputs_t outputs = {
        .i_dq_A = electrical_k1.i_dq_A,
        .torque_Nm = swmodel_inner_torque_Nm(self, electrical_k1),
        .omega_mech_1_s = inputs.omega_mech_1_s};
    if (simulate_mechanical_system)
    {
        outputs.omega_mech_1_s = omega_mech_1_s_k1;
    }

    self->integrator_state_k0 = state_k1;
    if (simulate_mechanical_system)
    {
        self->omega_mech_1_s_k0 = omega_mech_1_s_k1;
    }
    return outputs;
}

#endif
