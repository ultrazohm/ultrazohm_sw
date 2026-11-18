/*
 * Copyright Contributors to the UltraZohm project.
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef UZ_ACTOR_PT1_REPLAY_H
#define UZ_ACTOR_PT1_REPLAY_H

#include <stdbool.h>
#include <stdint.h>

#define UZ_ACTOR_PT1_UPDATE_FIELD_LAYER 2U
#define UZ_ACTOR_PT1_UPDATE_FIELD_TYPE 3U
#define UZ_ACTOR_PT1_UPDATE_FIELD_INDEX 4U
#define UZ_ACTOR_PT1_UPDATE_FIELD_VALUE 5U
#define UZ_ACTOR_PT1_UPDATE_FIELD_TARGET 6U

enum uz_actor_pt1_replay_actor {
	UZ_PT1_REPLAY_IDLE = 0,
	UZ_PT1_REPLAY_DQN = 1,
	UZ_PT1_REPLAY_DDPG = 2
};

struct uz_actor_pt1_replay_signals {
	float actor;
	float time;
	float episode;
	float episode_k;
	float y;
	float reference;
	float error;
	float action_value;
	float reward;
	float action_index;
	float q_values[3];
	float done;
};

/* Read-only to consumers; writable storage is required by JavaScope. */
extern struct uz_actor_pt1_replay_signals uz_actor_pt1_replay_signals;

/** @brief Float telemetry mirrors; consumers must not use them as control state. */
struct uz_actor_pt1_update_status {
	float active;
	float received;
	float error;  /* 0 OK, 1 invalid selector, 2 wrong order, 3 non-finite,
                     4 incomplete upload, 5 aborted */
	float target; /* 1 DQN, 2 DDPG */
	float expected;
};
extern struct uz_actor_pt1_update_status uz_actor_pt1_update_status;

/** @brief Stop inference and begin a complete ordered parameter upload. */
void uz_actor_pt1_update_begin(void);
/** @brief Accept a complete upload and leave the controller stopped. */
void uz_actor_pt1_update_finish(void);
/** @brief Report update mode using the internal boolean state, not telemetry. */
bool uz_actor_pt1_update_is_active(void);
/* Fields 2..5 are layer (zero-based), type (0 weights / 1 bias), index, value.
 * Field 6 selects the target before beginning an upload. */
void uz_actor_pt1_update_field(uint32_t field, float value);

/** @brief Initialize both networks once at the actual ISR frequency. */
void uz_actor_pt1_replay_init(float control_frequency_hz);
/* Controls called by the JavaScope command handler in the control ISR. */
void uz_actor_pt1_replay_start(enum uz_actor_pt1_replay_actor actor);
/** @brief Stop inference and invalidate any interrupted upload. */
void uz_actor_pt1_replay_stop(void);
/** @brief Toggle continuous reference-driven simulation. */
void uz_actor_pt1_replay_toggle_manual(void);
/** @brief Accept a finite manual reference; ignore nonfinite inputs. */
void uz_actor_pt1_replay_set_reference(float reference);
/** @brief Report manual mode from the internal boolean state. */
bool uz_actor_pt1_replay_is_manual(void);
/** @brief Return the actor currently executing, or idle. */
enum uz_actor_pt1_replay_actor uz_actor_pt1_replay_get_active_actor(void);

/* Called immediately before publishing the scope sample in the control ISR. */
void uz_actor_pt1_replay_step(void);

#endif
