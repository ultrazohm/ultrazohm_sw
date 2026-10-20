#include "../../uz_global_configuration.h"
#if (UZ_NN_MAX_INSTANCES > 0U) && (UZ_PMSM_SWMODEL_MAX_INSTANCES > 0U)
#include "uz_actor_pmsm_example.h"
#include "../../uz_HAL.h"
#include <math.h>
#include <stddef.h>
void uz_actor_pmsm_example_init(uz_actor_pmsm_example_t *self, const struct uz_exported_actor_config *actor,
    struct uz_pmsm_swmodel_config_t plant, uint32_t oversampling) {
    uz_assert(oversampling > 0U);
    uz_assert(actor->command_count == 2U);
    uz_assert(!plant.simulate_mechanical_system);
    uz_assert(plant.integrator_state == uz_pmsm_swmodel_integrator_state_current);
    uz_exported_actor_init(&self->actor, actor, 1.0f/(plant.sample_time*(float)oversampling));
    self->plant = uz_pmsm_swmodel_init(plant);
    self->oversampling = oversampling;
    uz_actor_pmsm_example_reset(self);
}
void uz_actor_pmsm_example_reset(uz_actor_pmsm_example_t *self) {
    uz_pmsm_swmodel_reset(self->plant);
    uz_exported_actor_reset(&self->actor, NULL);
    self->output = (struct uz_pmsm_swmodel_outputs_t){0};
}
struct uz_pmsm_swmodel_outputs_t uz_actor_pmsm_example_step(uz_actor_pmsm_example_t *self, float id_reference, float iq_reference, float speed_rpm) {
    struct uz_exported_actor_signals signals = {.current={self->output.i_dq_A.d, self->output.i_dq_A.q},
        .reference={id_reference, iq_reference}, .speed_rpm=speed_rpm};
    uz_exported_actor_sample(&self->actor, signals);
    struct uz_pmsm_swmodel_inputs_t inputs = {.v_dq_V={.d=self->actor.applied[0], .q=self->actor.applied[1]},
        .omega_mech_1_s=speed_rpm*(6.2831853071795864769f/60.0f), .load_torque=0.0f};
    for (uint32_t i = 0U; i < self->oversampling; ++i) { self->output = uz_pmsm_swmodel_step(self->plant, inputs); }
    return self->output;
}
#endif
