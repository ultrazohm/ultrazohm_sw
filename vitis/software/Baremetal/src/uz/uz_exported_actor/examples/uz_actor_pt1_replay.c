#include "../../uz_global_configuration.h"

#if UZ_PT1_REPLAY
#include "uz_actor_pt1_replay.h"
#include "uz_actor_pt1_example.h"
#include "pt1_ddpg/pt1_ddpg_config.h"
#include "pt1_dqn/pt1_dqn_config.h"
#include <stddef.h>
#include <string.h>
#include "../../uz_HAL.h"

/* Inputs and reset cadence of the two checked-in Ceedling PT1 fixtures. */
static const float references[] = {-1.0f, 0.0f, 0.5f, 0.1f, 0.2f, 1.0f};
static const uint32_t steps_per_episode = 500U;
static uz_actor_pt1_example_t dqn;
static uz_actor_pt1_example_t ddpg;
static enum uz_actor_pt1_replay_actor active_actor;
static enum uz_actor_pt1_replay_actor selected_actor = UZ_PT1_REPLAY_DQN;
static bool manual_mode;
static float manual_reference;
static uint32_t sample;

struct uz_actor_pt1_replay_signals uz_actor_pt1_replay_signals;

void uz_actor_pt1_replay_init(float control_frequency_hz)
{
    uz_assert(fabsf(control_frequency_hz - pt1_dqn_config.control_frequency_hz) <= 0.01f);
    uz_assert(fabsf(control_frequency_hz - pt1_ddpg_config.control_frequency_hz) <= 0.01f);
    uz_actor_pt1_example_init(&dqn, &pt1_dqn_config, 1.0f, 0.002f);
    uz_actor_pt1_example_init(&ddpg, &pt1_ddpg_config, 1.0f, 0.002f);
}

void uz_actor_pt1_replay_start(enum uz_actor_pt1_replay_actor actor)
{
    if (manual_mode || active_actor == UZ_PT1_REPLAY_IDLE) {
        selected_actor = actor;
        active_actor = actor;
        sample = 0U;
    }
}

void uz_actor_pt1_replay_stop(void)
{
    active_actor = UZ_PT1_REPLAY_IDLE;
    manual_mode = false;
    uz_actor_pt1_replay_signals.actor = (float)UZ_PT1_REPLAY_IDLE;
}

void uz_actor_pt1_replay_toggle_manual(void)
{
    if (manual_mode) {
        uz_actor_pt1_replay_stop();
    } else {
        manual_mode = true;
        uz_actor_pt1_replay_start(selected_actor);
    }
}

void uz_actor_pt1_replay_set_reference(float reference)
{
    if (isfinite(reference)) {
        manual_reference = reference;
    }
}

bool uz_actor_pt1_replay_is_manual(void)
{
    return manual_mode;
}

enum uz_actor_pt1_replay_actor uz_actor_pt1_replay_get_active_actor(void)
{
    return active_actor;
}

void uz_actor_pt1_replay_step(void)
{
    if (active_actor == UZ_PT1_REPLAY_IDLE) {
        return;
    }

    const uint32_t episode = manual_mode ? 0U : sample / steps_per_episode;
    if (episode >= sizeof(references) / sizeof(references[0])) {
        uz_actor_pt1_replay_stop();
        return;
    }

    const bool is_dqn = active_actor == UZ_PT1_REPLAY_DQN;
    uz_actor_pt1_example_t *example = is_dqn ? &dqn : &ddpg;
    const uint32_t step = manual_mode ? sample : sample % steps_per_episode;
    if (step == 0U) {
        uz_actor_pt1_example_reset(example, 0.0f);
    }

    const float reference = manual_mode ? manual_reference : references[episode];
    const float y = example->output;
    const float output = uz_actor_pt1_example_step(example, reference);
    const float error_after = reference - output;
    uz_actor_pt1_replay_signals = (struct uz_actor_pt1_replay_signals){
        // Actor IDs 3 and 4 keep manual samples separate from fixture replay.
        .actor = (float)((unsigned int)active_actor + (manual_mode ? 2U : 0U)),
        .time = (float)sample,
        .episode = (float)(episode + 1U),
        .episode_k = (float)step,
        .y = y,
        .reference = reference,
        .error = reference - y,
        .action_value = example->actor.requested[0],
        .reward = -error_after * error_after,
        .done = (float)(!manual_mode && step + 1U == steps_per_episode)
    };
    if (is_dqn) {
        const uz_matrix_t *raw = uz_nn_get_output_data(example->actor.network);
        uz_actor_pt1_replay_signals.action_index = (float)example->actor.action_index;
        for (uint32_t i = 0U; i < 3U; ++i) {
            uz_actor_pt1_replay_signals.q_values[i] = uz_matrix_get_element_zero_based(raw, 0U, i);
        }
    }
    ++sample;
}
#endif
