#include "../uz_global_configuration.h"
#if UZ_DQN_MAX_INSTANCES > 0U
#if UZ_DQN_BUFFER_MAX_INSTANCES > 0U
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"

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

uz_dqn_t *uz_dqn_init(float *vecdata, float lernrate, float discount_factor, struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER],
                      struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER], uint32_t seed_number,
                      uint32_t number_of_layer,
                      struct uz_dqn_experience_replay_config buffer_config,
                      uint32_t length_of_buffer, struct uz_dqn_environment_config envconf)
{
    uz_assert_not_NULL(vecdata);
    uz_dqn_t *self = uz_dqn_allocation();
    self->inputvecnn = uz_matrix_init(&self->inputvecnn_matrix, vecdata, config_critic->number_of_inputs, 1, config_critic->number_of_inputs);
    self->randinstance = uz_mtwister_init(seed_number);
    self->critic = uz_nn_init_with_rand(config_critic, number_of_layer, self->randinstance, true);
    self->critic_target_net = uz_nn_init(config_target, number_of_layer, false);
    self->experience_buffer = uz_dqn_experience_replay_init(buffer_config, length_of_buffer);
    self->discount_factor = discount_factor;
    self->lernrate = lernrate;
    self->env = uz_dqn_environment_init(envconf);
    return (self);
}

void uz_dqn_simple_reset(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    for (uint32_t i = 0; i < self->critic->number_of_inputs; i++)
    {
        self->inputvecnn->data[i] = uz_mtwister_random_uniform_float(self->randinstance);
    }
}

void uz_dqn_sample_simple(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    uint32_t action;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start, self->env->epsilon_min, self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
        uz_matrix_copy(self->inputvecnn, self->env->inputfornn);
        uz_nn_ff(self->critic, self->inputvecnn);
        uz_matrix_t *outputdqn = uz_nn_get_output_data(self->critic);
        // randnumber and epsilon comparision
        if (uz_mtwister_random_uniform_float(self->randinstance) < self->env->epsilon_start)
        {
            action = uz_mtwister_random_uniform_uint32(self->randinstance, self->critic->number_of_outputs - 1);
        }
        else
        {
            action = uz_matrix_get_max_index(outputdqn);
        }
        // uz_dqn_simple_action(self->env,actionind);
        float reward = calculate_reward_simple(action);
        uz_dqn_push_to_buffer(self->experience_buffer, reward, action, self->env->inputfornn, self->env->inputfornn);
        self->env->cumreward = reward;
    }
}

float uz_dqn_step_adam_simple_no_array(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, adam_optimizer_t *adam)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    uz_matrix_t *outputcritic;
    uz_matrix_t *outputtarget;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start, self->env->epsilon_min, self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
        uz_matrix_copy(self->inputvecnn, self->env->inputfornn);
        uz_nn_ff(self->critic, self->inputvecnn);
        outputcritic = uz_nn_get_output_data(self->critic);
        // randnumber and epsilon comparision
        if (uz_mtwister_random_uniform_float(self->randinstance) < self->env->epsilon_start)
        {
            actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->critic->number_of_outputs - 1);
        }
        else
        {
            actionind = uz_matrix_get_max_index(outputcritic);
        }
        float stepreward = calculate_reward_simple(actionind);
        uz_dqn_push_to_buffer(self->experience_buffer, stepreward, actionind, self->inputvecnn, self->env->inputfornn);
        self->env->cumreward = stepreward;
        for (uint32_t j = 0; j < mbsize; j++)
        {
            uint32_t randomindex = 0U;
            if (uz_dqn_buffer_get_counterisfull(self->experience_buffer) > 0U)
            {
                randomindex = uz_mtwister_random_uniform_max_uint32(self->randinstance, uz_dqn_buffer_get_length(self->experience_buffer) - 1);
            }
            else
            {
                randomindex = uz_mtwister_random_uniform_max_uint32(self->randinstance, uz_dqn_buffer_get_head(self->experience_buffer) - 1);
            }
            uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1, self->env->inputfornn, randomindex);
            uz_nn_ff(self->critic_target_net, self->env->inputfornn);
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
            uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations, self->inputvecnn, randomindex);
            uz_nn_ff(self->critic, self->inputvecnn);
            outputcritic = uz_nn_get_output_data(self->critic);
            float qvaltrain = uz_matrix_get_element_zero_based(outputcritic, 0, actiontrain);
            loss = calculate_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
            dloss = calculate_derv_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
            error[actiontrain] = dloss;
            cum_loss += loss;

            uz_nn_backward_pass_mini_batch(self->critic, error, self->inputvecnn);
            resetFloatArray(error, self->critic->number_of_outputs);
        }
        cum_loss = cum_loss / (float)mbsize;
        adam_optimizer_step(adam, self->critic);
        uz_nn_set_gradients_zero(self->critic);
    }
    if (epoch % TARGET_UPDATE_FREQUENCY == 0)
    {
        uz_nn_target_update(self->critic, self->critic_target_net, periodic, targsmoothfact);
    }
    if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
    {
        return cum_loss;
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

void uz_dqn_act_bitenv_no_exploration(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    uint32_t actionind;
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
        uz_nn_ff(self->critic_target_net, self->env->inputfornn);
        uz_matrix_t *outputaction = uz_nn_get_output_data(self->critic_target_net);
        actionind = uz_matrix_get_max_index(outputaction);
        uz_dqn_bitflip_action(self->env, actionind);
        float reward = calculate_reward_bit(self->env);
        self->env->cumreward += reward;
        if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
        {
            // printf("Bitmuster gleich nach %d Schritten.\n",i);
            return;
        }
    }
}

float uz_dqn_step_adam_no_array(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, adam_optimizer_t *adam)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    uz_matrix_t *outputcritic;
    uz_matrix_t *outputtarget;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    uint32_t randomindex = 0U;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start, self->env->epsilon_min, self->env->epsilon_decay);
    for (uint32_t t = 0; t < self->env->max_steps; t++)
    {
        uz_matrix_copy(self->env->inputfornn, self->experience_buffer->vectorforobs);
        uz_nn_ff(self->critic, self->env->inputfornn);
        outputcritic = uz_nn_get_output_data(self->critic);
        if (uz_mtwister_random_uniform_float(self->randinstance) < self->env->epsilon_start)
        {
            actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->env->bitlength - 1);
        }
        else
        {
            actionind = uz_matrix_get_max_index(outputcritic);
        }
        uz_dqn_bitflip_action(self->env, actionind);
        float stepreward = calculate_reward_bit(self->env);
        uz_dqn_push_to_buffer(self->experience_buffer, stepreward, actionind, self->experience_buffer->vectorforobs, self->env->inputfornn);
        self->env->cumreward += stepreward;
        for (uint32_t j = 0; j < mbsize; j++)
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
            error[actiontrain] += dloss;
            cum_loss += loss;
            uz_nn_backward_pass_mini_batch(self->critic, error, self->experience_buffer->vectorforobs);
            resetFloatArray(error, self->critic->number_of_outputs);
        }
        cum_loss = cum_loss / (float)mbsize;
        adam_optimizer_step(adam, self->critic);
        uz_nn_set_gradients_zero(self->critic);
        if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
        {
            return cum_loss;
        }
    }
    if (epoch % TARGET_UPDATE_FREQUENCY == 0)
    {
        uz_nn_target_update(self->critic, self->critic_target_net, smoothing, targsmoothfact);
    }
    return cum_loss;
}

float uz_dqn_step_gd(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t bufferlength, uint32_t *r)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    uz_matrix_t *outputtarget;
    uz_matrix_t *outputcritic;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start, self->env->epsilon_min, self->env->epsilon_decay);
    for (uint32_t t = 0; t < self->env->max_steps; t++)
    {
        uz_matrix_copy(self->env->inputfornn, self->inputvecnn);
        uz_nn_ff(self->critic, self->env->inputfornn);
        uz_matrix_t *outputdqn = uz_nn_get_output_data(self->critic);
        if (uz_mtwister_random_uniform_float(self->randinstance) < self->env->epsilon_start)
        {
            actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->env->bitlength - 1);
        }
        else
        {
            actionind = uz_matrix_get_max_index(outputdqn);
        }
        uz_dqn_bitflip_action(self->env, actionind);
        float stepreward = calculate_reward_bit(self->env);
        uz_dqn_push_to_buffer(self->experience_buffer, stepreward, actionind, self->inputvecnn, self->env->inputfornn);
        self->env->cumreward += stepreward;
        if (self->experience_buffer->counterisfull > 0U)
        {
            uz_mtwister_random_uniform_uint32_array(self->randinstance, r, mbsize, (float)bufferlength - 1);
        }
        else
        {
            uz_mtwister_random_uniform_uint32_array(self->randinstance, r, mbsize, (float)self->experience_buffer->head - 1);
        }
        uint32_t *rx;
        rx = r;
        for (uint32_t j = 0; j < mbsize; j++)
        {
            uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1, self->env->inputfornn, *rx);
            uz_nn_ff(self->critic_target_net, self->env->inputfornn);
            outputtarget = uz_nn_get_output_data(self->critic_target_net);
            qplus1 = uz_matrix_get_max_value(outputtarget);
            float rewardtrain = self->experience_buffer->reward[*rx];
            uint32_t actiontrain = self->experience_buffer->action[*rx];
            if (rewardtrain == 0.0f)
            {
                terminal = true;
            }
            else
            {
                terminal = false;
            }
            uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations, self->inputvecnn, *rx);
            uz_nn_ff(self->critic, self->inputvecnn);
            outputcritic = uz_nn_get_output_data(self->critic);
            float qvaltrain = uz_matrix_get_element_zero_based(outputcritic, 0, actiontrain);
            loss = calculate_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
            dloss = calculate_derv_loss_dqn(self, rewardtrain, qvaltrain, qplus1, terminal);
            error[actiontrain] = dloss;
            cum_loss += loss;

            uz_nn_backward_pass_mini_batch(self->critic, error, self->inputvecnn);
            rx++;
            resetFloatArray(error, self->critic->number_of_outputs);
        }
        cum_loss = cum_loss / (float)mbsize;
        uz_nn_gradient_descent_mini_batch(self->critic, self->lernrate, mbsize);
        uz_nn_set_gradients_zero(self->critic);
    }
    // Targetupdate
    if (epoch % TARGET_UPDATE_FREQUENCY == 0)
    {
        uz_nn_target_update(self->critic, self->critic_target_net, periodic, targsmoothfact);
    }
    if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
    {
        return cum_loss;
    }
    return cum_loss;
}

void uz_dqn_sample_bitenv(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    uint32_t actionind;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start, self->env->epsilon_min, self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
        uz_matrix_copy(self->env->inputfornn, self->inputvecnn);
        uz_nn_ff(self->critic, self->env->inputfornn);
        uz_matrix_t *outputdqn = uz_nn_get_output_data(self->critic);
        if (uz_mtwister_random_uniform_float(self->randinstance) < self->env->epsilon_start)
        {
            actionind = uz_mtwister_random_uniform_max_uint32(self->randinstance, self->env->bitlength - 1);
        }
        else
        {
            actionind = uz_matrix_get_max_index(outputdqn);
        }
        uz_dqn_bitflip_action(self->env, actionind);
        float stepreward = calculate_reward_bit(self->env);
        uz_dqn_push_to_buffer(self->experience_buffer, stepreward, actionind, self->inputvecnn, self->env->inputfornn);
        self->env->cumreward += stepreward;
        if (arraysequal(self->env->bitinitial, self->env->bittarget, self->env->bitlength) == true)
        {
            // printf("Bitmuster gleich nach %d Schritten.\n",i);
            return;
        }
    }
}

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

float calc_epsilon_greedy(float epsilon_start, float epsilon_min, float epsilon_decay)
{
    uz_assert(epsilon_start < 1.0f);
    uz_assert(epsilon_decay < 1.0f);
    uz_assert(epsilon_start > 0.0f);
    uz_assert(epsilon_decay > 0.0f);
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
    return uz_dqn_buffer_get_counterisfull(self->experience_buffer);
}

#endif
#endif