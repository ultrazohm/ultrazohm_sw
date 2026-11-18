/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef UZ_ACTOR_PT1_EXAMPLE_H
#define UZ_ACTOR_PT1_EXAMPLE_H
#include "../uz_exported_actor.h"
/** @brief Simulated PT1 plant coupled to an exported actor; caller-owned storage. */
typedef struct uz_actor_pt1_example_t {
	uz_exported_actor_t actor;
	float output;
	float gain;
	float step_fraction;
} uz_actor_pt1_example_t;
/** @brief Initialize once with a persistent generated configuration. */
void uz_actor_pt1_example_init(uz_actor_pt1_example_t *self, const struct uz_exported_actor_config *config, float gain,
                               float time_constant);
/** @brief Reset plant and controller state between episodes. */
void uz_actor_pt1_example_reset(uz_actor_pt1_example_t *self, float initial_output);
/** @brief Execute one controller interval and advance the software plant. */
float uz_actor_pt1_example_step(uz_actor_pt1_example_t *self, float reference);
#endif
