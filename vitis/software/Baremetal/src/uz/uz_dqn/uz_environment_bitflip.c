#include "../uz_global_configuration.h"
#if UZ_DQN_ENV_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"

#include "uz_environment_bitflip.h"

struct uz_environment_bitflip_t
{
    bool is_ready;
    uint32_t length_of_bitmask;
    uint32_t *current_bitmask;
    uint32_t *target_bitmask;
    uint32_t max_steps;
    uz_matrix_t *environment_state;
    struct uz_matrix_t inputfornn_matrix;
    float cumulative_reward;
    float reward;
};

bool arraysequal(const uint32_t *inarray, const uint32_t *tararray, size_t size);
void uz_environment_bitflip_calculate_reward(uz_environment_bitflip_t *self);
void uz_environment_bitflip_reset_cumulative_reward(uz_environment_bitflip_t *self);
void uz_environment_bitflip_step(uz_environment_bitflip_t *self, uint32_t action);
float calculate_reward_simple(uint32_t actionind);

static uint32_t instance_counterenv = 0U;
static uz_environment_bitflip_t instancesenv[UZ_DQN_ENV_MAX_INSTANCES] = {0};
static uz_environment_bitflip_t *uz_dqn_environment_allocation(void);

static uz_environment_bitflip_t *uz_dqn_environment_allocation(void)
{
    uz_assert(instance_counterenv < UZ_DQN_BUFFER_MAX_INSTANCES);
    uz_environment_bitflip_t *self = &instancesenv[instance_counterenv];
    uz_assert_false(self->is_ready);
    instance_counterenv++;
    self->is_ready = true;
    return (self);
}

uz_environment_bitflip_t *uz_environment_bitflip_init(struct uz_dqn_environment_config envconf)
{
    uz_environment_bitflip_t *self = uz_dqn_environment_allocation();
    self->length_of_bitmask = envconf.bitlength;
    self->current_bitmask = envconf.bitarray;
    self->target_bitmask = envconf.targetarray;
    self->environment_state = uz_matrix_init(&self->inputfornn_matrix, envconf.inarray, 2 * envconf.bitlength, 1, 2 * envconf.bitlength);
    if (envconf.max_steps == 0)
    {
        self->max_steps = self->length_of_bitmask;
    }
    else
    {
        self->max_steps = envconf.max_steps;
    }
    return (self);
}

void uz_environment_bitflip_reset(uz_environment_bitflip_t *self, uz_mtwister_t *random_generator)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(random_generator);
    for (uint32_t i = 0; i < self->length_of_bitmask; i++)
    {
        self->current_bitmask[i] = uz_mtwister_random_zero_or_one_uint32(random_generator);
        self->target_bitmask[i] = uz_mtwister_random_zero_or_one_uint32(random_generator);
        self->environment_state->data[i] = (float)self->current_bitmask[i];
        self->environment_state->data[self->length_of_bitmask + i] = (float)self->target_bitmask[i];
    }
    self->is_ready = true;
    self->cumulative_reward = 0.0f;
}

bool arraysequal(const uint32_t *inarray, const uint32_t *tararray, size_t size)
{
    uz_assert_not_NULL(inarray);
    uz_assert_not_NULL(tararray);
    for (size_t i = 0; i < size; i++)
    {
        if (inarray[i] != tararray[i])
        {
            return false; // Arrays are not equal
        }
    }
    return true; // Arrays are equal
}

void uz_environment_bitflip_calculate_reward(uz_environment_bitflip_t *self)
{
    uz_assert_not_NULL(self);
    float r;
    bool z = arraysequal(self->current_bitmask, self->target_bitmask, self->length_of_bitmask);
    if (z == true)
    {
        r = 1.0f;
    }
    else if (z == false)
    {
        r = 0.0f;
    }
    uz_environment_bitflip_add_to_cumulative_reward(self, r);
    self->reward = r;
}

float uz_environment_bitflip_get_reward(uz_environment_bitflip_t *self)
{
    uz_assert_not_NULL(self);
    return self->reward;
}

float calculate_reward_simple(uint32_t actionind)
{
    float r;
    if (actionind == 0)
    {
        r = 1.0f;
    }
    else if (actionind == 1)
    {
        r = 2.0f;
    }
    else if (actionind == 2)
    {
        r = 3.0f;
    }
    else
    {
        return -1;
    }
    return r;
}

void uz_environment_bitflip_step(uz_environment_bitflip_t *self, uint32_t action)
{
    uz_assert_not_NULL(self);
    // flip bit
    if (self->current_bitmask[action] == 1)
    {
        self->current_bitmask[action] = 0;
        self->environment_state->data[action] = 0.0f;
    }
    else
    {
        self->current_bitmask[action] = 1;
        self->environment_state->data[action] = 1.0f;
    }
    uz_environment_bitflip_calculate_reward(self);
}

void uz_environment_bitflip_save_values(float savecritic[], float savetarget[], float critic[], float target[], uint32_t step, uint32_t size)
{
    // Save values from the current step into the larger arrays
    for (uint32_t i = 0U; i < size; i++)
    {
        savecritic[step * size + i] = critic[i];
        savetarget[step * size + i] = target[i];
    }
}

bool uz_environment_bitflip_is_finished(uz_environment_bitflip_t *self)
{
    uz_assert_not_NULL(self);

    return (arraysequal(self->current_bitmask, self->target_bitmask, self->length_of_bitmask));
}

void uz_environment_bitflip_reset_cumulative_reward(uz_environment_bitflip_t *self)
{
    uz_assert_not_NULL(self);
    self->cumulative_reward = 0.0f;
}

void uz_environment_bitflip_add_to_cumulative_reward(uz_environment_bitflip_t *self, float added_reward)
{
    uz_assert_not_NULL(self);
    self->cumulative_reward += added_reward;
}

float uz_environment_bitflip_get_cumulative_reward(uz_environment_bitflip_t *self)
{
    uz_assert_not_NULL(self);
    return self->cumulative_reward;
}

uz_matrix_t *uz_environment_bitflip_get_state(uz_environment_bitflip_t *self)
{
    uz_assert_not_NULL(self);
    return self->environment_state;
}

float uz_environment_bitflip_step_one_episode(uz_dqn_t *self, uint32_t max_steps, bool train, uz_environment_bitflip_t *env)
{
    uz_assert_not_NULL(self);
    float cum_loss = 0.0f;
    for (uint32_t t = 0; t < max_steps; t++)
    {
        // sample observation of the environment at k=0
        uz_matrix_t *env_state = uz_environment_bitflip_get_state(env);
        uz_dqn_sample_observation_k_0(self, env_state);
        //  uz_dqn_environment_sample_observation(env, self->observation_k_0);
        // determine the action based on Q(s,a) with epsilon greedy exploration
        uint32_t action = uz_dqn_determine_action(self);
        // take the action, environment is now in k+1
        uz_environment_bitflip_step(env, action);
        env_state = uz_environment_bitflip_get_state(env);
        // Sample environment at k+1
        uz_dqn_sample_observation_k_1(self, env_state);
        env->reward = uz_environment_bitflip_get_reward(env);
        uz_dqn_set_reward(self, env->reward);
        uz_dqn_push_to_buffer(self);
        if (train)
        {
            cum_loss = uz_dqn_update(self);
        }
        if (uz_environment_bitflip_is_finished(env))
        {
            return cum_loss;
        }
    }
    return cum_loss;
}

#endif
