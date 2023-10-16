#include "uz_environment_pt1.h"
#include "../uz_global_configuration.h"

#if UZ_ENVIRONMENT_PT1_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_environment_pt1.h"
#include "../uz_integrator/uz_integrator.h"
#include <math.h>

struct uz_environment_pt1_t
{
    bool is_ready;
    float time_constant;
    float gain;
    float integration_time;
    float old_integrator_value;
    float old_output;
    float cumulative_reward;
    float reward;
    float input;
    float output;
    float error;
    uint32_t max_steps;
    uz_matrix_t *environment_state;
    struct uz_matrix_t inputfornn_matrix;
};

static uint32_t instance_counter = 0U;
static uz_environment_pt1_t instances[UZ_ENVIRONMENT_PT1_MAX_INSTANCES] = {0};

static uz_environment_pt1_t *uz_environment_pt1_allocation(void);

static uz_environment_pt1_t *uz_environment_pt1_allocation(void)
{
    uz_assert(instance_counter < UZ_ENVIRONMENT_PT1_MAX_INSTANCES);
    uz_environment_pt1_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_environment_pt1_t *uz_environment_pt1_init(float gain, float time_constant, float integration_time, float *input_array)
{
    uz_environment_pt1_t *self = uz_environment_pt1_allocation();
    uz_assert(gain > 0.0f);
    uz_assert(time_constant > 0.0f);
    self->old_output = 0.0f;
    self->gain = gain;
    self->integration_time = integration_time;
    self->time_constant = time_constant;
    self->environment_state = uz_matrix_init(&self->inputfornn_matrix, input_array, 2U, 1U, 2U);

    return (self);
}

float uz_environment_pt1_step(uz_environment_pt1_t *self, float input)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    input= (input*self->gain)-self->old_output;
    float integrator_value=uz_integrator_eulerforward(input,self->old_integrator_value,self->integration_time,false);
    self->old_integrator_value=integrator_value;
    self->old_output = integrator_value * (1.0f / self->time_constant);
    return self->old_output;
}

void uz_environment_pt1_dqn_step(uz_environment_pt1_t *self, uint32_t action, float set_point){
    uz_assert_not_NULL(self);
    switch (action)
    {
    case 0:
        self->input=1.0f;
        break;
    case 1:
        self->input = 0.0f;
        break;
    case 2:
        self->input = -1.0f;
        break;
    default:
        break;
    }
    self->output = uz_environment_pt1_step(self, self->input);
    self->error=set_point-self->output;
    self->reward=-fabsf(self->error);
    self->cumulative_reward+=self->reward;
}

float uz_environment_pt1_get_output(uz_environment_pt1_t *self){
    uz_assert_not_NULL(self);
    return self->output;
}

    void uz_environment_pt1_reset(uz_environment_pt1_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->old_integrator_value=0.0f;
    self->old_output=0.0f;
    self->cumulative_reward=0.0f;
}

uz_matrix_t* uz_environment_pt1_get_state(uz_environment_pt1_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_matrix_set_element_zero_based(self->environment_state,self->error,0U,0U);
    uz_matrix_set_element_zero_based(self->environment_state,self->output,0U,1U);
   return (self->environment_state);
}

float uz_environment_pt1_get_reward(uz_environment_pt1_t *self)
{
    return self->reward;
}

float uz_environment_pt1_get_cumulative_reward(uz_environment_pt1_t *self)
{
    return self->cumulative_reward;
}

float uz_environment_pt1_step_one_episode(uz_dqn_t *self, uint32_t max_steps, bool train, uz_environment_pt1_t *env,float set_point, bool logging, float* error, float* input, float* output)
{
    uz_assert_not_NULL(self);
    float cum_loss = 0.0f;
    for (uint32_t t = 0; t < max_steps; t++)
    {
        // sample observation of the environment at k=0
        uz_matrix_t *env_state = uz_environment_pt1_get_state(env);
        uz_dqn_sample_observation_k_0(self, env_state);
        //  uz_dqn_environment_sample_observation(env, self->observation_k_0);
        // determine the action based on Q(s,a) with epsilon greedy exploration
        uint32_t action = uz_dqn_determine_action(self);
        // take the action, environment is now in k+1
        uz_environment_pt1_dqn_step(env, action,set_point);

    if(logging){
        error[t]=env->error;
        input[t]=env->input;
        output[t]=env->output;
    }

        env_state = uz_environment_pt1_get_state(env);
        // Sample environment at k+1
        uz_dqn_sample_observation_k_1(self, env_state);
        env->reward = uz_environment_pt1_get_reward(env);
        uz_dqn_set_reward(self, env->reward);
        uz_dqn_push_to_buffer(self);
        if (train)
        {
            cum_loss = uz_dqn_update(self);
        }
    }
    return cum_loss;
}

#endif