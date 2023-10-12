#ifndef UZ_DQN_H
#define UZ_DQN_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>
#include "../uz_nn/uz_nn.h"
#include "../uz_nn/uz_nn_layer.h"
#include "uz_environment.h"
#include "uz_mtwister.h"
#include "uz_dqn_expirience_buffer.h"

typedef struct uz_dqn_t uz_dqn_t;

uz_dqn_t *uz_dqn_init(float *observation_data, float *observation_k1_data, float lernrate, float discount_factor, struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER], struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER], uint32_t random_seed, uint32_t number_of_layer, struct uz_dqn_experience_replay_config buffer_config, uint32_t length_of_buffer, struct uz_dqn_environment_config envconf, uint32_t minibatch_size, uint32_t target_update_frequency, float target_smooth_factor, float epsilon_start, float epsilon_min, float epsilon_decay, enum target_update update_mechanism);
float uz_dqn_step_adam(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t *r, adam_optimizer_t *adam);

float uz_dqn_step_adam_no_array(uz_dqn_t *self, float *error, uint32_t max_steps, bool train, uz_dqn_environment_t *env);

    float uz_dqn_step_gd_simple(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t *r);
float uz_dqn_step_adam_simple(uz_dqn_t *self, float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t *r, adam_optimizer_t *adam);
float uz_dqn_step_adam_simple_no_array(uz_dqn_t *self, float *error, uint32_t epoch);
void uz_dqn_sample(uz_dqn_t *self, float samplerate, bool penalty, uz_matrix_t *input);
float uz_dqn_train_gd(uz_dqn_t *self, float *error, float *rew, uint32_t *act, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact);
float uz_dqn_train_adam(uz_dqn_t *self, float *error, float *rew, uint32_t *act, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, adam_optimizer_t *adam);


float calculate_reward_pendulum(float samplerate, float theta, float position, float velocity, bool penalty);
float calculate_reward_dqn(float samplerate, uz_matrix_t *observations, bool penalty);
float calculate_loss_dqn(uz_dqn_t *self, float samplereward, float qval, float qvalplus1, bool terminal);
float calculate_derv_loss_dqn(uz_dqn_t *self, float samplereward, float qval, float qvalplus1, bool terminal);
uint32_t uz_dqn_get_action(uz_dqn_t *self, uz_matrix_t *input, float *epsilon_start, float *epsilon_min, float *epsilon_decay, uint32_t number_of_actions);
/**
 * @brief Calculates epsilon-greedy exploration value for epsilon-greedy exploration for Deep Q-Networks.
 *
 * @param epsilon_start Float start value for epsilon, <1.0f
 * @param epsilon_min Float minimum value
 * @param epsilon_decay Float decay rate of epsilon_greedy
 * @return float
 */
float epsilon_greedy_decay(float epsilon_start, float epsilon_min, float epsilon_decay);
void exportFloatArrayToCSV(const char *filename, const float *array, int size);
void resetuintArray(uint32_t *arr, uint32_t size);
void resetFloatArray(float *arr, uint32_t size);

uint32_t uz_dqn_get_counterisfull(uz_dqn_t *self);

void uz_dqn_set_epsilon(uz_dqn_t *self, float epsilon, float epsilon_min, float epsilon_decay);
float uz_dqn_get_epsilon(uz_dqn_t *self);

uz_nn_t * uz_dqn_get_critic_net(uz_dqn_t *self);

#endif // UZ_DQN_H