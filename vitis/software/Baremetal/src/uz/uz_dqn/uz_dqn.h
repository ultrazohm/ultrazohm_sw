#ifndef UZ_DQN_H
#define UZ_DQN_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>
#include "uz_nn.h"
#include "mtwister.h"

typedef struct uz_dqn_t uz_dqn_t;
typedef struct uz_dqn_experience_replay_t uz_dqn_experience_replay_t;

struct uz_dqn_experience_replay_config{
    uint32_t columns_of_observations;
    uint32_t length_of_buffer;
    float *const reward;
    float *const observations;
    float *const qvalues;
    int32_t *const actions;
};

uz_dqn_t *uz_dqn_init(float *lernrate, float *discount_factor,struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER],
struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER],
uint32_t number_of_layer,
 struct uz_dqn_experience_replay_config buffer_config,
uint32_t length_of_buffer, uint32_t headind);
uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, uint32_t length, uint32_t headind);
void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *qdata,int32_t *actiondata, uz_matrix_t *obsdata);
void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *QValue, int32_t *actiondata, uz_matrix_t *obsdata, uint32_t index);
void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self);
float calculate_reward_pendulum (float samplerate, float theta, float position, float velocity, bool penalty);
float calculate_loss_dqn(uz_dqn_t* self, float *gamma,float *reward, float *qval, float * qvalplus1,  uz_matrix_t *obs, bool terminal);
float calculate_derv_loss_dqn(uz_dqn_t* self, float *gamma,float *reward, float *qval, float * qvalplus1,  uz_matrix_t *obs, bool terminal);
void uz_dqn_get_minibatch_from_buffer(uz_dqn_experience_replay_t* self,float *reward,float *qvalue,float *qvalueplus1, int32_t *action, uz_matrix_t *obs, uint32_t minibatchsize,uint32_t numberofobs,  uint32_t *indizes);
uint32_t uz_dqn_get_action(uz_dqn_t* self,float *epsilon_start,float *epsilon_min,float *epsilon_decay);
/**
 * @brief Calculates epsilon-greedy exploration value for epsilon-greedy exploration for Deep Q-Networks.
 * 
 * @param epsilon_start Float start value for epsilon, <1.0f
 * @param epsilon_min Float minimum value
 * @param epsilon_decay Float decay rate of epsilon_greedy
 * @return float
 */
float calc_epsilon_greedy(float epsilon_start, float epsilon_min, float epsilon_decay);
#endif // UZ_DQN_H
