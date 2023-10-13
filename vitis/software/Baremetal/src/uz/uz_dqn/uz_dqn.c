#include "../uz_global_configuration.h"
#if UZ_DQN_MAX_INSTANCES > 0U
#if UZ_DQN_BUFFER_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"

struct uz_dqn_t
{
    bool is_ready;
    uz_nn_t *critic;
    uz_nn_t *critic_target_net;
    uz_mtwister_t *randinstance;
    uz_dqn_experience_replay_t *experience_buffer;
    float discount_factor;
    float lernrate;
    uz_matrix_t *observation_k_0;
    uz_matrix_t *observation_k_1;
    struct uz_matrix_t observation_k0_matrix;
    struct uz_matrix_t observation_k1_matrix;
    adam_optimizer_t *adam;
    uint32_t minibatch_size;
    uint32_t target_update_frequency;
    float target_smooth_factor;
    enum target_update update_mechanism;
    float epsilon;
    float epsilon_min;
    float epsilon_decay;
    uint32_t number_of_actions;
    float *error;
};

static uint32_t instance_counter = 0U;
static uz_dqn_t instances[UZ_DQN_MAX_INSTANCES] = {0};
static uz_dqn_t *uz_dqn_allocation(void);

static uz_dqn_t *uz_dqn_allocation(void)
{
    uz_assert(instance_counter < UZ_DQN_MAX_INSTANCES);
    uz_dqn_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

float uz_dqn_update(uz_dqn_t *self);
uint32_t uz_dqn_determine_action(uz_dqn_t *self);

uz_dqn_t *uz_dqn_init(float *observation_data, float *observation_k1_data, float lernrate, float discount_factor, struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER], struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER], uint32_t random_seed, uint32_t number_of_layer, struct uz_dqn_experience_replay_config buffer_config, uint32_t length_of_buffer, uint32_t minibatch_size, uint32_t target_update_frequency, float target_smooth_factor, float epsilon_start, float epsilon_min, float epsilon_decay, enum target_update update_mechanism, float *error)
{
    uz_assert_not_NULL(observation_data);
    uz_dqn_t *self = uz_dqn_allocation();
    self->observation_k_0 = uz_matrix_init(&self->observation_k0_matrix, observation_data, config_critic->number_of_inputs, 1, config_critic->number_of_inputs);
    self->observation_k_1 = uz_matrix_init(&self->observation_k1_matrix, observation_k1_data, config_critic->number_of_inputs, 1, config_critic->number_of_inputs);
    self->randinstance = uz_mtwister_init(random_seed);

    // Init critic with random parameters and trainable and copies values to target net
    self->critic = uz_nn_init_with_rand(config_critic, number_of_layer, self->randinstance, true);
    self->critic_target_net = uz_nn_init(config_target, number_of_layer, false);
    uz_nn_copy(self->critic, self->critic_target_net);

    self->experience_buffer = uz_dqn_experience_replay_init(buffer_config, length_of_buffer);
    self->discount_factor = discount_factor;
    self->lernrate = lernrate;
    self->adam = uz_adam_init(lernrate / (float)minibatch_size);
    self->minibatch_size = minibatch_size;
    self->target_smooth_factor = target_smooth_factor;
    self->target_update_frequency = target_update_frequency;
    self->update_mechanism = update_mechanism;

    self->error = error;
    self->epsilon_decay = epsilon_decay;
    self->epsilon_min = epsilon_min;
    self->epsilon = epsilon_start;
    self->number_of_actions = uz_nn_get_number_of_outputs(self->critic);
    return (self);
}

// void uz_dqn_sample_simple(uz_dqn_t *self)
// {
//     uz_assert_not_NULL(self);
//     uint32_t action;
//     self->epsilon = epsilon_greedy_decay(self->epsilon, self->epsilon_min, self->epsilon_decay);
//     for (uint32_t i = 0; i < self->env->max_steps; i++)
//     {
//         uz_matrix_copy(self->observation_k_0, self->env->environment_state);
//         uz_nn_ff(self->critic, self->observation_k_0);
//         uz_matrix_t *outputdqn = uz_nn_get_output_data(self->critic);
//         // randnumber and epsilon comparision
//         if (uz_mtwister_random_uniform_float(self->randinstance) < self->epsilon)
//         {
//             action = uz_mtwister_random_uniform_uint32(self->randinstance, uz_nn_get_number_of_outputs(self->critic) - 1);
//         }
//         else
//         {
//             action = uz_matrix_get_max_index(outputdqn);
//         }
//         // uz_dqn_simple_action(self->env,actionind);
//         float reward = calculate_reward_simple(action);
//         uz_dqn_push_to_buffer(self->experience_buffer, reward, action, self->env->environment_state, self->env->environment_state);
//         self->env->cumreward = reward;
//     }
// }

// float uz_dqn_step_adam_simple_no_array(uz_dqn_t *self, float *error, uint32_t epoch)
// {
//     uz_assert_not_NULL(self);
//     uz_assert_not_NULL(error);
//     uint32_t actionind;
//     float qplus1 = 0.0f;
//     bool terminal = false;
//     float loss = 0.0f;
//     float cum_loss = 0.0f;
//     float dloss = 0.0f;
//     uz_matrix_t *outputcritic;
//     uz_matrix_t *outputtarget;
//     self->epsilon = epsilon_greedy_decay(self->epsilon, self->epsilon_min, self->epsilon_decay);
//     for (uint32_t i = 0; i < self->env->max_steps; i++)
//     {
//         // Determine action to take based on Q-value and epsilon-greedy
//         uz_matrix_copy(self->observation_k_0, self->env->environment_state);
//         uz_nn_ff(self->critic, self->observation_k_0);
//         outputcritic = uz_nn_get_output_data(self->critic);
//         // randnumber and epsilon comparision
//         if (uz_mtwister_random_uniform_float(self->randinstance) < self->epsilon)
//         {
//             actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, uz_nn_get_number_of_outputs(self->critic) - 1);
//         }
//         else
//         {
//             actionind = uz_matrix_get_max_index(outputcritic);
//         }

//         // Take the step
//         float stepreward = calculate_reward_simple(actionind);

//         // Wait till state=state+1 and push to buffer
//         uz_dqn_push_to_buffer(self->experience_buffer, stepreward, actionind, self->observation_k_0, self->env->environment_state);
//         self->env->cumreward = stepreward;

//         // Training step for one minibatch
//         for (uint32_t j = 0; j < self->minibatch_size; j++)
//         {
//             uint32_t randomindex = 0U;
//             if (uz_dqn_buffer_get_counterisfull(self->experience_buffer) > 0U)
//             {
//                 randomindex = uz_mtwister_random_uniform_max_uint32(self->randinstance, uz_dqn_buffer_get_length(self->experience_buffer) - 1);
//             }
//             else
//             {
//                 randomindex = uz_mtwister_random_uniform_max_uint32(self->randinstance, uz_dqn_buffer_get_head(self->experience_buffer) - 1);
//             }
//             uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1, self->env->environment_state, randomindex);
//             uz_nn_ff(self->critic_target_net, self->env->environment_state);
//             outputtarget = uz_nn_get_output_data(self->critic_target_net);
//             qplus1 = uz_matrix_get_max_value(outputtarget);
//             float rewardtrain = self->experience_buffer->reward[randomindex];
//             uint32_t actiontrain = self->experience_buffer->action[randomindex];
//             if (rewardtrain == 0.0f)
//             {
//                 terminal = true;
//             }
//             else
//             {
//                 terminal = false;
//             }
//             uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations, self->observation_k_0, randomindex);
//             uz_nn_ff(self->critic, self->observation_k_0);
//             outputcritic = uz_nn_get_output_data(self->critic);
//             float qvaltrain = uz_matrix_get_element_zero_based(outputcritic, 0, actiontrain);
//             loss = calculate_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
//             dloss = calculate_derv_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
//             error[actiontrain] = dloss;
//             cum_loss += loss;

//             uz_nn_backward_pass_mini_batch(self->critic, error, self->observation_k_0);
//             resetFloatArray(error, uz_nn_get_number_of_outputs(self->critic));
//         }
//         cum_loss = cum_loss / (float)self->minibatch_size;
//         adam_optimizer_step(self->adam, self->critic);
//         uz_nn_set_gradients_zero(self->critic);
//     }
//     if (epoch % self->target_update_frequency == 0)
//     {
//         uz_nn_target_update(self->critic, self->critic_target_net, periodic, self->target_smooth_factor);
//     }
//     if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
//     {
//         return cum_loss;
//     }
//     return cum_loss;
// }

float uz_dqn_step_one_episode(uz_dqn_t *self, uint32_t max_steps, bool train, uz_dqn_environment_t *env)
{
    uz_assert_not_NULL(self);
    float cum_loss = 0.0f;
    for (uint32_t t = 0; t < max_steps; t++)
    {
        // sample observation of the environment at k=0
        uz_matrix_t *env_state = uz_dqn_environment_get_state(env);
        uz_dqn_sample_observation_k_0(self, env_state);
        //  uz_dqn_environment_sample_observation(env, self->observation_k_0);
        // determine the action based on Q(s,a) with epsilon greedy exploration
        uint32_t action = uz_dqn_determine_action(self);
        // take the action, environment is now in k+1
        uz_dqn_environment_step(env, action);
        env_state = uz_dqn_environment_get_state(env);
        // Sample environment at k+1
        uz_dqn_sample_observation_k_1(self, env_state);
        float reward = uz_dqn_environment_get_reward(env);
        uz_dqn_push_to_buffer(self->experience_buffer, reward, action, self->observation_k_0, self->observation_k_1);
        if (train)
        {
            cum_loss = uz_dqn_update(self);
        }
        if (uz_dqn_environment_is_finished(env))
        {
            return cum_loss;
        }
    }
    return cum_loss;
}

void uz_dqn_sample_observation_k_0(uz_dqn_t *self, uz_matrix_t *observation_k_0)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(observation_k_0);
    uz_matrix_copy(observation_k_0, self->observation_k_0);
}

void uz_dqn_sample_observation_k_1(uz_dqn_t *self, uz_matrix_t *observation_k_1)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(observation_k_1);
    uz_matrix_copy(observation_k_1, self->observation_k_1);
}

uint32_t uz_dqn_determine_action(uz_dqn_t *self)
{
    self->epsilon = epsilon_greedy_decay(self->epsilon, self->epsilon_min, self->epsilon_decay);
    uint32_t actionind = 0;
    uz_nn_ff(self->critic, self->observation_k_0);
    uz_matrix_t *outputcritic = uz_nn_get_output_data(self->critic);
    if (uz_mtwister_random_uniform_float(self->randinstance) < self->epsilon)
    {
        actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->number_of_actions - 1U);
    }
    else
    {
        actionind = uz_matrix_get_max_index(outputcritic);
    }
    return actionind;
}

float uz_dqn_update(uz_dqn_t *self)
{
    uint32_t randomindex = 0U;
    uz_matrix_t *outputcritic;
    uz_matrix_t *outputtarget;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float dloss = 0.0f;
    float cum_loss = 0.0f;
    for (uint32_t j = 0; j < self->minibatch_size; j++)
    {

        if (self->experience_buffer->counterisfull > 0U)
        {
            randomindex = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->experience_buffer->length - 1);
        }
        else
        {
            randomindex = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->experience_buffer->head - 1);
        }
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1, self->experience_buffer->vectorforobs1, randomindex);
        uz_nn_ff(self->critic_target_net, self->experience_buffer->vectorforobs1);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        float rewardtrain = self->experience_buffer->reward[randomindex];
        uint32_t actiontrain = self->experience_buffer->action[randomindex];
        if (rewardtrain == 0.0f)
        {
            terminal = true;
        }
        else
        {
            terminal = false;
        }
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations, self->experience_buffer->vectorforobs, randomindex);
        uz_nn_ff(self->critic, self->experience_buffer->vectorforobs);
        outputcritic = uz_nn_get_output_data(self->critic);
        float qvaltrain = uz_matrix_get_element_zero_based(outputcritic, 0, actiontrain);
        loss = calculate_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
        dloss = calculate_derv_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
        self->error[actiontrain] += dloss;
        cum_loss += loss;
        uz_nn_backward_pass_mini_batch(self->critic, self->error, self->experience_buffer->vectorforobs);
        resetFloatArray(self->error, uz_nn_get_number_of_outputs(self->critic));
    }
    cum_loss = cum_loss / (float)self->minibatch_size;
    adam_optimizer_step(self->adam, self->critic);
    uz_nn_set_gradients_zero(self->critic);
    if (adam_get_number_of_updates(self->adam) % self->target_update_frequency == 0)
    {
        uz_nn_target_update(self->critic, self->critic_target_net, self->update_mechanism, self->target_smooth_factor);
    }
    return cum_loss;
}

// float uz_dqn_step_gd_simple(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t *r)
// {
//     uz_assert_not_NULL(self);
//     uz_assert_not_NULL(error);
//     uint32_t actionind;
//     float qplus1 = 0.0f;
//     bool terminal = false;
//     float loss = 0.0f;
//     float cum_loss = 0.0f;
//     float dloss = 0.0f;
//     uz_matrix_t *outputcritic;
//     uz_matrix_t *outputtarget;
//     self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start, self->env->epsilon_min, self->env->epsilon_decay);
//     for (uint32_t i = 0; i < self->env->max_steps; i++)
//     {
//         uz_matrix_copy(self->inputvecnn, self->env->inputfornn);
//         uz_nn_ff(self->critic, self->inputvecnn);
//         outputcritic = uz_nn_get_output_data(self->critic);
//         // randnumber and epsilon comparision
//         if (uz_mtwister_random_uniform_float(self->randinstance) < self->env->epsilon_start)
//         {
//             actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->critic->number_of_outputs - 1);
//         }
//         else
//         {
//             actionind = uz_matrix_get_max_index(outputcritic);
//         }
//         float stepreward = calculate_reward_simple(actionind);
//         uz_dqn_push_to_buffer(self->experience_buffer, stepreward, actionind, self->env->inputfornn, self->env->inputfornn);
//         self->env->cumreward = stepreward;
//         if (self->experience_buffer->counterisfull > 0U)
//         {
//             uz_mtwister_random_uniform_uint32_array(self->randinstance, r, mbsize, (float)self->experience_buffer->length - 1);
//         }
//         else
//         {
//             uz_mtwister_random_uniform_uint32_array(self->randinstance, r, mbsize, (float)self->experience_buffer->head - 1);
//         }
//         uint32_t *rx;
//         rx = r;
//         for (uint32_t j = 0; j < mbsize; j++)
//         {
//             uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1, self->env->inputfornn, *rx);
//             uz_nn_ff(self->critic_target_net, self->env->inputfornn);
//             outputtarget = uz_nn_get_output_data(self->critic_target_net);
//             qplus1 = uz_matrix_get_max_value(outputtarget);
//             float rewardtrain = self->experience_buffer->reward[*rx];
//             uint32_t actiontrain = self->experience_buffer->action[*rx];
//             if (rewardtrain == 0.0f)
//             {
//                 terminal = true;
//             }
//             else
//             {
//                 terminal = false;
//             }
//             uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations, self->inputvecnn, *rx);
//             uz_nn_ff(self->critic, self->inputvecnn);
//             outputcritic = uz_nn_get_output_data(self->critic);
//             float qvaltrain = uz_matrix_get_element_zero_based(outputcritic, 0, actiontrain);
//             loss = calculate_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
//             dloss = calculate_derv_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
//             error[actiontrain] = dloss;
//             cum_loss += loss;
//             uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations, self->inputvecnn, *rx);
//             uz_nn_backward_pass_mini_batch(self->critic, error, self->inputvecnn);
//             resetFloatArray(error, self->critic->number_of_outputs);
//             rx++;
//         }
//         cum_loss = cum_loss / (float)mbsize;
//         uz_nn_gradient_descent_mini_batch(self->critic, self->lernrate, mbsize);
//         uz_nn_set_gradients_zero(self->critic);
//     }
//     if (epoch % TARGET_UPDATE_FREQUENCY == 0)
//     {
//         uz_nn_target_update(self->critic, self->critic_target_net, smoothing, &targsmoothfact);
//     }
//     if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
//     {
//         return cum_loss;
//     }
//     return cum_loss;
// }

// float uz_dqn_step_gd(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t bufferlength, uint32_t *r)
// {
//     uz_assert_not_NULL(self);
//     uz_assert_not_NULL(error);
//     uint32_t actionind;
//     uz_matrix_t *outputtarget;
//     uz_matrix_t *outputcritic;
//     float qplus1 = 0.0f;
//     bool terminal = false;
//     float loss = 0.0f;
//     float cum_loss = 0.0f;
//     float dloss = 0.0f;
//     self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start, self->env->epsilon_min, self->env->epsilon_decay);
//     for (uint32_t t = 0; t < self->env->max_steps; t++)
//     {
//         uz_matrix_copy(self->env->inputfornn, self->inputvecnn);
//         uz_nn_ff(self->critic, self->env->inputfornn);
//         uz_matrix_t *outputdqn = uz_nn_get_output_data(self->critic);
//         if (uz_mtwister_random_uniform_float(self->randinstance) < self->env->epsilon_start)
//         {
//             actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->env->bitlength - 1);
//         }
//         else
//         {
//             actionind = uz_matrix_get_max_index(outputdqn);
//         }
//         uz_dqn_bitflip_action(self->env, actionind);
//         float stepreward = calculate_reward_bit(self->env);
//         uz_dqn_push_to_buffer(self->experience_buffer, stepreward, actionind, self->inputvecnn, self->env->inputfornn);
//         self->env->cumreward += stepreward;
//         if (self->experience_buffer->counterisfull > 0U)
//         {
//             uz_mtwister_random_uniform_uint32_array(self->randinstance, r, mbsize, (float)bufferlength - 1);
//         }
//         else
//         {
//             uz_mtwister_random_uniform_uint32_array(self->randinstance, r, mbsize, (float)self->experience_buffer->head - 1);
//         }
//         uint32_t *rx;
//         rx = r;
//         for (uint32_t j = 0; j < mbsize; j++)
//         {
//             uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1, self->env->inputfornn, *rx);
//             uz_nn_ff(self->critic_target_net, self->env->inputfornn);
//             outputtarget = uz_nn_get_output_data(self->critic_target_net);
//             qplus1 = uz_matrix_get_max_value(outputtarget);
//             float rewardtrain = self->experience_buffer->reward[*rx];
//             uint32_t actiontrain = self->experience_buffer->action[*rx];
//             if (rewardtrain == 0.0f)
//             {
//                 terminal = true;
//             }
//             else
//             {
//                 terminal = false;
//             }
//             uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations, self->inputvecnn, *rx);
//             uz_nn_ff(self->critic, self->inputvecnn);
//             outputcritic = uz_nn_get_output_data(self->critic);
//             float qvaltrain = uz_matrix_get_element_zero_based(outputcritic, 0, actiontrain);
//             loss = calculate_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
//             dloss = calculate_derv_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
//             error[actiontrain] = dloss;
//             cum_loss += loss;

//             uz_nn_backward_pass_mini_batch(self->critic, error, self->inputvecnn);
//             rx++;
//             resetFloatArray(error, self->critic->number_of_outputs);
//         }
//         cum_loss = cum_loss / (float)mbsize;
//         uz_nn_gradient_descent_mini_batch(self->critic, self->lernrate, mbsize);
//         uz_nn_set_gradients_zero(self->critic);
//     }
//     // Targetupdate
//     if (epoch % TARGET_UPDATE_FREQUENCY == 0)
//     {
//         uz_nn_target_update(self->critic, self->critic_target_net, periodic, targsmoothfact);
//     }
//     if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
//     {
//         return cum_loss;
//     }
//     return cum_loss;
// }

// float uz_dqn_train_gd(uz_dqn_t *self, float *error, float *rew, uint32_t *act, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact)
// {
//     uz_assert_not_NULL(self);
//     uz_assert_not_NULL(error);
//     uz_assert_not_NULL(rew);
//     uz_assert_not_NULL(obs);
//     uz_assert_not_NULL(obspl1);
//     float qplus1 = 0.0f;
//     bool terminal = false;
//     float loss = 0.0f;
//     float cum_loss = 0.0f;
//     float dloss = 0.0f;
//     uz_matrix_t *outputtarget;
//     uz_matrix_t *outputcritic;
//     for (uint32_t j = 0; j < mbsize; j++)
//     {
//         uz_matrix_get_row_vector_zero_based(obspl1, self->env->inputfornn, j);
//         uz_nn_ff(self->critic_target_net, self->env->inputfornn);
//         outputtarget = uz_nn_get_output_data(self->critic_target_net);
//         qplus1 = uz_matrix_get_max_value(outputtarget);
//         if (*rew == 0.0f)
//         {
//             terminal = true;
//         }
//         else
//         {
//             terminal = false;
//         }
//         uz_nn_ff(self->critic, obs);
//         outputcritic = uz_nn_get_output_data(self->critic);
//         float qval = uz_matrix_get_element_zero_based(outputcritic, 0, *act);
//         loss = calculate_loss_dqn(self, *rew, qval, qplus1, terminal);
//         dloss = calculate_derv_loss_dqn(self, *rew, qval, qplus1, terminal);
//         error[*act] = dloss;
//         cum_loss += loss;
//         uz_matrix_get_row_vector_zero_based(obs, self->inputvecnn, j);
//         uz_nn_backward_pass_mini_batch(self->critic, error, self->inputvecnn);
//         rew++;
//         qval++;
//         act++;
//         resetFloatArray(error, self->critic->number_of_outputs);
//     }
//     cum_loss = cum_loss / (float)mbsize;
//     uz_nn_gradient_descent_mini_batch(self->critic, self->lernrate, mbsize);
//     uz_nn_set_gradients_zero(self->critic);
//     if (epoch % TARGET_UPDATE_FREQUENCY == 0)
//     {
//         uz_nn_target_update(self->critic, self->critic_target_net, periodic, &targsmoothfact);
//     }
//     return cum_loss;
// }

float calculate_loss_dqn(uz_dqn_t *self, float samplereward, float qval, float qvalplus1, bool terminal)
{
    uz_assert_not_NULL(self);
    // berechne y_j
    float y_j = 0.0f;
    if (terminal == true)
    {
        y_j = samplereward;
    }
    else
    {
        y_j = samplereward + (self->discount_factor * qvalplus1);
    }
    float loss = ((y_j - qval) * (y_j - qval));
    return loss;
}

float calculate_derv_loss_dqn(uz_dqn_t *self, float samplereward, float qval, float qvalplus1, bool terminal)
{
    uz_assert_not_NULL(self);
    float y_j = 0.0f;
    if (terminal == true)
    {
        y_j = samplereward;
    }
    else
    {
        y_j = samplereward + (self->discount_factor * qvalplus1);
    }
    float dloss = -2.0f * (y_j - qval);

    if (dloss > 1.0f)
    {
        dloss = 1.0f;
    }
    if (dloss < -1.0f)
    {
        dloss = -1.0f;
    }
    return dloss;
}

float calculate_reward_dqn(float samplerate, uz_matrix_t *observations, bool penalty)
{
    // hardcoded defines for the reward
    float pos_max = 0.35f;
    // check, ob penalty nötig
    float z = 0.0f;
    if (penalty == true)
    {
        z = -1000.0f;
    }
    float r = -2.0f * samplerate * (100.0f * asinf(fabsf(observations->data[0]) / (2.0f * (float)M_PI)) + fabsf(observations->data[3] / pos_max) + (0.25f * (observations->data[4] * observations->data[4]))) + z;
    return r;
}

float calculate_reward_pendulum(float samplerate, float theta, float position, float velocity, bool penalty)
{
    float z = 0.0f;
    if (penalty == true)
    {
        z = -1000.0f;
    }
    float r = -2.0f * samplerate * (100.0f * theta + position + 0.25f * (float)pow(velocity, 2.0f)) + z;
    return r;
}

void uz_dqn_set_epsilon(uz_dqn_t *self, float epsilon, float epsilon_min, float epsilon_decay)
{
    uz_assert_not_NULL(self);
    uz_assert(epsilon <= 1.0f);
    uz_assert(epsilon_decay <= 1.0f);
    uz_assert(epsilon >= 0.0f);
    uz_assert(epsilon_decay >= 0.0f);
    self->epsilon = epsilon;
    self->epsilon_min = epsilon_min;
    self->epsilon_decay = epsilon_decay;
}

float epsilon_greedy_decay(float epsilon_start, float epsilon_min, float epsilon_decay)
{
    uz_assert(epsilon_start <= 1.0f);
    uz_assert(epsilon_decay <= 1.0f);
    uz_assert(epsilon_start >= 0.0f);
    uz_assert(epsilon_decay >= 0.0f);
    uz_assert(epsilon_start >= epsilon_min);
    float epsilon = epsilon_start;
    epsilon = epsilon * (1.0f - epsilon_decay);
    if (epsilon < epsilon_min)
    {
        epsilon = epsilon_min;
    }
    return epsilon;
}

// helpers
void resetFloatArray(float *arr, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        arr[i] = 0.0f;
    }
}

void resetuintArray(uint32_t *arr, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

void exportFloatArrayToCSV(const char *filename, const float *array, int size)
{
    // Check if the file can be opened for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Unable to create the CSV file");
        return;
    }

    // Write the array to the file in CSV format
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%.8f", (double)array[i]); // Assuming 2 decimal places, adjust as needed
        if (i < size - 1)
        {
            fprintf(file, ",");
        }
        else
        {
            fprintf(file, "\n");
        }
    }

    // Close the file
    fclose(file);
}

uint32_t uz_dqn_get_counterisfull(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    return uz_dqn_buffer_get_counterisfull(self->experience_buffer);
}

float uz_dqn_get_epsilon(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    return self->epsilon;
}

uz_nn_t *uz_dqn_get_critic_net(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    return self->critic;
}

#endif
#endif