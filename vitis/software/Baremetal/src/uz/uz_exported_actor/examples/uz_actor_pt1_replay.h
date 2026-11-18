#ifndef UZ_ACTOR_PT1_REPLAY_H
#define UZ_ACTOR_PT1_REPLAY_H

#include <stdbool.h>

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

extern struct uz_actor_pt1_replay_signals uz_actor_pt1_replay_signals;

void uz_actor_pt1_replay_init(float control_frequency_hz);
/* Controls called by the JavaScope command handler in the control ISR. */
void uz_actor_pt1_replay_start(enum uz_actor_pt1_replay_actor actor);
void uz_actor_pt1_replay_stop(void);
void uz_actor_pt1_replay_toggle_manual(void);
void uz_actor_pt1_replay_set_reference(float reference);
bool uz_actor_pt1_replay_is_manual(void);
enum uz_actor_pt1_replay_actor uz_actor_pt1_replay_get_active_actor(void);

/* Called immediately before publishing the scope sample in the control ISR. */
void uz_actor_pt1_replay_step(void);

#endif
