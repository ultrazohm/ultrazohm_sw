#ifndef UZ_ACTOR_PMSM_EXAMPLE_H
#define UZ_ACTOR_PMSM_EXAMPLE_H
#include "../uz_exported_actor.h"
#include "../../uz_pmsm_swmodel/uz_pmsm_swmodel.h"
typedef struct {
    uz_exported_actor_t actor;
    uz_pmsm_swmodel_t *plant;
    struct uz_pmsm_swmodel_outputs_t output;
    uint32_t oversampling;
} uz_actor_pmsm_example_t;
void uz_actor_pmsm_example_init(uz_actor_pmsm_example_t *self, const struct uz_exported_actor_config *actor,
    struct uz_pmsm_swmodel_config_t plant, uint32_t oversampling);
void uz_actor_pmsm_example_reset(uz_actor_pmsm_example_t *self);
struct uz_pmsm_swmodel_outputs_t uz_actor_pmsm_example_step(uz_actor_pmsm_example_t *self, float id_reference, float iq_reference, float speed_rpm);
#endif
