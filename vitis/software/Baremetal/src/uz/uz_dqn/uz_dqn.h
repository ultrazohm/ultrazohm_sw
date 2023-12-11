#ifndef UZ_DQN_H
#define UZ_DQN_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>
#include "../uz_nn/uz_nn.h"
#include "../uz_nn/uz_nn_layer.h"
#include "../uz_prng/uz_prng.h"
#include "uz_dqn_expirience_buffer.h"
#include "../uz_array/uz_array.h"

typedef struct uz_dqn_t uz_dqn_t;

struct uz_dqn_training_config_t
{
    float learn_rate;
    float discount_factor;
    uint32_t minibatch_size;
    uint32_t target_update_frequency;
    float target_smooth_factor;
    enum target_update update_mechanism;
};

struct uz_dqn_network_config_t
{
    struct uz_nn_layer_config* config_critic;
    struct uz_nn_layer_config* config_target;
    struct uz_nn_layer_config* config_copy;
    uint32_t number_of_layer;
};

struct uz_dqn_prng_config_t
{
    uint64_t random_seed;
    enum uz_prng_generator uz_prng_type;
};

struct uz_dqn_exploration_config_t
{
    float epsilon_start;
    float epsilon_min;
    float epsilon_decay;
};

struct uz_dqn_config_t
{
    float *observation_data;
    float *observation_k1_data;
    struct uz_dqn_experience_replay_config buffer_config;
    uint32_t length_of_buffer;
    float *error;
    struct uz_dqn_training_config_t training;
    struct uz_dqn_network_config_t network;
    struct uz_dqn_prng_config_t prng_init;
    struct uz_dqn_prng_config_t prng_exploration;
    struct uz_dqn_prng_config_t prng_training;
    struct uz_dqn_exploration_config_t exploration;
};

uz_dqn_t *uz_dqn_init(struct uz_dqn_config_t config);
// uz_dqn_t *uz_dqn_init(float *observation_data, float *observation_k1_data, float lernrate, float discount_factor, struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER], struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER], uint64_t random_seed, enum uz_prng_generator uz_prng_type, uint32_t number_of_layer, struct uz_dqn_experience_replay_config buffer_config, uint32_t length_of_buffer, uint32_t minibatch_size, uint32_t target_update_frequency, float target_smooth_factor, float epsilon_start, float epsilon_min, float epsilon_decay, enum target_update update_mechanism, float *error, struct uz_nn_layer_config config_copy[UZ_NN_MAX_LAYER]);

void uz_dqn_sample_observation_k_0(uz_dqn_t *self, uz_matrix_t *observation_k_0);
uint32_t uz_dqn_determine_action(uz_dqn_t *self);
void uz_dqn_sample_observation_k_1(uz_dqn_t *self, uz_matrix_t *observation_k_1);
void uz_dqn_set_reward(uz_dqn_t *self, float reward);
void uz_dqn_push_to_buffer(uz_dqn_t *self);
float uz_dqn_update(uz_dqn_t *self);

uint32_t uz_dqn_get_counterisfull(uz_dqn_t *self);
void uz_dqn_set_epsilon(uz_dqn_t *self, float epsilon, float epsilon_min, float epsilon_decay);
float uz_dqn_get_epsilon(uz_dqn_t *self);
uz_nn_t *uz_dqn_get_critic_net(uz_dqn_t *self);

void uz_dqn_copy_net(uz_dqn_t *self);
#endif // UZ_DQN_H
