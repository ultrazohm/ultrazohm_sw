#ifndef UZ_ACTOR_PT1_EXAMPLE_H
#define UZ_ACTOR_PT1_EXAMPLE_H
#include "../uz_exported_actor.h"
typedef struct {
    uz_exported_actor_t actor;
    float output;
    float gain;
    float step_fraction;
} uz_actor_pt1_example_t;
void uz_actor_pt1_example_init(uz_actor_pt1_example_t *self, const struct uz_exported_actor_config *config, float gain, float time_constant);
void uz_actor_pt1_example_reset(uz_actor_pt1_example_t *self, float initial_output);
float uz_actor_pt1_example_step(uz_actor_pt1_example_t *self, float reference);
#endif
