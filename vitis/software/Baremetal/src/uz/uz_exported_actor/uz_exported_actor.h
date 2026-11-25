/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef UZ_EXPORTED_ACTOR_H
#define UZ_EXPORTED_ACTOR_H

#include <stdbool.h>
#include <stdint.h>
#include "../uz_nn/uz_nn.h"
#include "../uz_matrix/uz_matrix.h"

#define UZ_EXPORTED_ACTOR_ABI 1U
#define UZ_EXPORTED_ACTOR_MAX_COMMANDS 2U
#define UZ_EXPORTED_ACTOR_MAX_DELAY_STEPS 2U

/** @brief Physical inputs before a control tick; PT1 uses output and reference[0]. */
struct uz_exported_actor_signals {
	float output;
	float current[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	float reference[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	float speed_rpm;
	float applied_voltage[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
};

/** @brief Controller state and actuator-delay history, owned by one actor. */
struct uz_exported_actor_state {
	float integral[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	float applied_voltage[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	float queue[UZ_EXPORTED_ACTOR_MAX_DELAY_STEPS][UZ_EXPORTED_ACTOR_MAX_COMMANDS];
};

enum uz_exported_actor_limiter {
	UZ_ACTOR_NO_LIMITER,
	UZ_ACTOR_AXIS_PRIORITY,
	UZ_ACTOR_RADIAL
};

/**
 * @brief Generated controller semantics and statically allocated NN buffers.
 * @details Configuration and backing arrays must outlive the actor. Initialize
 * each configuration once; serialize all calls and parameter writes. Callbacks
 * and backing arrays are validated at initialization. No heap allocation occurs.
 * The network references the layer weight/bias arrays directly. Stop inference
 * before updating them, and resume only after the complete parameter set is valid.
 */
struct uz_exported_actor_config {
	uint32_t abi;
	const char *contract_sha256;
	struct uz_nn_layer_config *layers;
	uint32_t layer_count;
	float *observations;
	uint32_t input_count;
	uint32_t output_count;
	uint32_t command_count;
	const float *discrete_actions; /* NULL for continuous; [output_count, command_count] otherwise */
	float control_frequency_hz;
	uint32_t delay_steps;
	enum uz_exported_actor_limiter limiter;
	bool limiter_reference_current;
	float voltage_limit;
	float initial_integral[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	void (*observe)(const struct uz_exported_actor_signals *signals, const struct uz_exported_actor_state *state, float *observations);
	void (*advance)(const struct uz_exported_actor_signals *signals, struct uz_exported_actor_state *state, bool saturated);
	void (*map_action)(const float *action, float *requested);
};

typedef struct uz_exported_actor_t {
	const struct uz_exported_actor_config *config;
	uz_nn_t *network;
	struct uz_matrix_t input_matrix;
	struct uz_exported_actor_state state;
	float requested[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	float limited[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	float applied[UZ_EXPORTED_ACTOR_MAX_COMMANDS];
	uint32_t action_index;
	bool saturated;
} uz_exported_actor_t;

/** @brief Initialize one instance per generated config. Call init once; reset between episodes.
 * actual_frequency_hz is checked against the exported sampling assumption.
 * Calls must be serialized; generated uz_nn output buffers are shared.
 */
void uz_exported_actor_init(uz_exported_actor_t *self, const struct uz_exported_actor_config *config,
                            float actual_frequency_hz);
/** @brief Reset controller state; NULL initial selects generated defaults. */
void uz_exported_actor_reset(uz_exported_actor_t *self, const struct uz_exported_actor_state *initial);
/** @brief Observe, infer, map, limit, advance state, and apply actuator delay once.
 * applied is the command for THIS plant interval after the configured queue.
 * A hardware scheduler must not add this delay a second time.
 */
void uz_exported_actor_sample(uz_exported_actor_t *self, struct uz_exported_actor_signals signals);
/** @brief Separate actuator operation also supports deterministic limiter conformance tests. */
void uz_exported_actor_limit(const struct uz_exported_actor_config *config,
                             const struct uz_exported_actor_signals *signals, const float requested[UZ_EXPORTED_ACTOR_MAX_COMMANDS],
                             float limited[UZ_EXPORTED_ACTOR_MAX_COMMANDS], bool *saturated);
#endif
