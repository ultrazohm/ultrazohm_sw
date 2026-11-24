/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef UZ_ACTOR_PMSM_EXAMPLE_H
#define UZ_ACTOR_PMSM_EXAMPLE_H
#include "../uz_exported_actor.h"
#include "../../uz_pmsm_swmodel/uz_pmsm_swmodel.h"

/** @brief PMSM software model coupled to an exported actor; caller-owned storage. */
typedef struct uz_actor_pmsm_example_t {
	uz_exported_actor_t actor;
	uz_pmsm_swmodel_t *plant;
	struct uz_pmsm_swmodel_outputs_t output;
	uint32_t oversampling;
} uz_actor_pmsm_example_t;

/** @brief Initialize once with a persistent generated configuration. */
void uz_actor_pmsm_example_init(uz_actor_pmsm_example_t *self, const struct uz_exported_actor_config *actor,
                                struct uz_pmsm_swmodel_config_t plant, uint32_t oversampling);

/** @brief Reset plant and controller state between episodes. */
void uz_actor_pmsm_example_reset(uz_actor_pmsm_example_t *self);

/** @brief Execute one controller interval and advance the software plant. */
struct uz_pmsm_swmodel_outputs_t uz_actor_pmsm_example_step(uz_actor_pmsm_example_t *self, float id_reference_A,
                                                            float iq_reference_A, float speed_rpm);
#endif
