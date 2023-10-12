#include "../uz_global_configuration.h"
#if UZ_DQN_ENV_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"

#include "uz_environment.h"

static uint32_t instance_counterenv = 0U;
static uz_dqn_environment_t instancesenv[UZ_DQN_ENV_MAX_INSTANCES] = {0};
static uz_dqn_environment_t *uz_dqn_environment_allocation(void);

static uz_dqn_environment_t *uz_dqn_environment_allocation(void)
{
    uz_assert(instance_counterenv < UZ_DQN_BUFFER_MAX_INSTANCES);
    uz_dqn_environment_t *self = &instancesenv[instance_counterenv];
    uz_assert_false(self->is_ready);
    instance_counterenv++;
    self->is_ready = true;
    return (self);
}

uz_dqn_environment_t *uz_dqn_environment_init(struct uz_dqn_environment_config envconf)
{
    uz_dqn_environment_t *self = uz_dqn_environment_allocation();
    self->bitlength = envconf.bitlength;
    self->bitinitial = envconf.bitarray;
    self->bittarget = envconf.targetarray;
    self->environment_state = uz_matrix_init(&self->inputfornn_matrix, envconf.inarray, 2 * envconf.bitlength, 1, 2 * envconf.bitlength);
    if (envconf.max_steps == 0)
    {
        self->max_steps = self->bitlength;
    }
    else
    {
        self->max_steps = envconf.max_steps;
    }
    return (self);
}

void uz_dqn_environment_reset(uz_dqn_environment_t *self, uz_mtwister_t *random_generator)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(random_generator);
    for (uint32_t i = 0; i < self->bitlength; i++)
    {
        // self->bitinitial[i] = 1U;
        // self->bittarget[i] = 0U;
        // self->inputfornn->data[i] = 1.0f;
        // self->inputfornn->data[self->bitlength+i] = 0.0f;
        self->bitinitial[i] = uz_mtwister_random_zero_or_one_uint32(random_generator);
        self->bittarget[i] = uz_mtwister_random_zero_or_one_uint32(random_generator);
        self->environment_state->data[i] = (float)self->bitinitial[i];
        self->environment_state->data[self->bitlength + i] = (float)self->bittarget[i];
    }
    self->is_ready = true;
    self->cumreward = 0.0f;
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

float calculate_reward_bit(uz_dqn_environment_t *self)
{
    uz_assert_not_NULL(self);
    float r;
    bool z = arraysequal(self->bitinitial, self->bittarget, self->bitlength);
    if (z == true)
    {
        r = 1.0f;
    }
    else if (z == false)
    {
        r = 0.0f;
    }
    return r;
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

void uz_dqn_bitflip_action(uz_dqn_environment_t *self, uint32_t action)
{
    uz_assert_not_NULL(self);
    // flip bit
    if (self->bitinitial[action] == 1)
    {
        self->bitinitial[action] = 0;
        self->environment_state->data[action] = 0.0f;
    }
    else
    {
        self->bitinitial[action] = 1;
        self->environment_state->data[action] = 1.0f;
    }
}

void save_values(float savecritic[], float savetarget[], float critic[], float target[], uint32_t step, uint32_t size)
{
    // Save values from the current step into the larger arrays
    for (uint32_t i = 0U; i < size; i++)
    {
        savecritic[step * size + i] = critic[i];
        savetarget[step * size + i] = target[i];
    }
}



void uz_dqn_environment_sample_observation(uz_dqn_environment_t *self, uz_matrix_t* sample_destination){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(sample_destination);
    uz_matrix_copy(self->environment_state, sample_destination);
}

bool uz_dqn_environment_is_finished(uz_dqn_environment_t *self){
    uz_assert_not_NULL(self);

    return (arraysequal(self->bitinitial, self->bittarget, self->bitlength));
}

void uz_dqn_enviroment_reset_cumulative_reward(uz_dqn_environment_t *self){
    uz_assert_not_NULL(self);
    self->cumreward=0.0f;
}

void uz_dqn_enviroment_add_to_cumulative_reward(uz_dqn_environment_t *self, float added_reward){
    uz_assert_not_NULL(self);
    self->cumreward +=added_reward;
}

float uz_dqn_enviroment_get_cumulative_reward(uz_dqn_environment_t *self){
    uz_assert_not_NULL(self);
    return self->cumreward;
}

#endif