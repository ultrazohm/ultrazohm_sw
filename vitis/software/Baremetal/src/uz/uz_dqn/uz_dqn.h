#ifndef UZ_DQN_H
#define UZ_DQN_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>
#include "uz_nn.h"
#include "uz_environment.h"
#include "uz_mtwister.h"

typedef struct uz_dqn_t uz_dqn_t;
typedef struct uz_dqn_experience_replay_t uz_dqn_experience_replay_t;
struct uz_dqn_experience_replay_t {
    float *reward;
    float *qvalues;
    uint32_t *action;
    uz_matrix_t *observations;
    uz_matrix_t *vectorforobs;
    struct uz_matrix_t observations_matrix;
    struct uz_matrix_t vecobs_matrix;
    uint32_t head;
    uint32_t counterisfull;
    uint32_t length;
    bool is_full;
    bool is_ready;
};

struct uz_dqn_t {
    bool is_ready;
    uz_nn_t *critic;
    uz_nn_t *critic_target_net;
    uz_mtwister_t *randinstance;
    uz_dqn_experience_replay_t *experience_buffer;
    float discount_factor;
    float lernrate;
    uz_matrix_t *inputvecnn;
    struct uz_matrix_t inputvecnn_matrix;
    uz_dqn_environment_t *env;
};

struct uz_dqn_experience_replay_config{
    uint32_t columns_of_observations;
    uint32_t length_of_buffer;
    float *const reward;
    float *const observations;
    float *const obsvec;
    float *const qvalues;
    uint32_t *const actions;
};

uz_dqn_t *uz_dqn_init(float *vecdata,float lernrate, float discount_factor,struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER],
struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER], struct uz_mtwister_config cfg, 
uint32_t number_of_layer,
 struct uz_dqn_experience_replay_config buffer_config,
uint32_t length_of_buffer, uint32_t headind, struct uz_dqn_environment_config envconf);
uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, uint32_t length, uint32_t headind);
void uz_dqn_sample(uz_dqn_t *self, float samplerate, bool penalty, uz_matrix_t *input);
float uz_dqn_train(uz_dqn_t *self, float *rew, float *qval, uint32_t *act, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t mbsize, uint32_t numobs, uint32_t *indices,
uint32_t TARGET_UPDATE_FREQUENCY, uint32_t NUMBER_OF_EPOCHS, float targsmoothfact);
void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *qdata,uint32_t *actionindex, uz_matrix_t *obsdata);
void uz_dqn_get_obs_from_buffer(uz_dqn_experience_replay_t* self,uz_matrix_t *obsdata, uint32_t index);
void uz_dqn_get_q_value_from_buffer(uz_dqn_experience_replay_t* self,float *QValue, uint32_t index);
void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *QValue, uint32_t *actionindex, uz_matrix_t *obsdata, uint32_t index);
void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self);
float calculate_reward_pendulum (float samplerate, float theta, float position, float velocity, bool penalty);
float calculate_reward_dqn(float samplerate, uz_matrix_t *observations, bool penalty);
float calculate_loss_dqn(uz_dqn_t* self, float reward, float qval, float qvalplus1, bool terminal);
float calculate_derv_loss_dqn(uz_dqn_t* self, float reward, float qval, float qvalplus1, bool terminal);
void uz_dqn_get_minibatch_from_buffer(uz_dqn_experience_replay_t* self,float *reward,float *qvalue, uint32_t *actionindex, uz_matrix_t *obs,uz_matrix_t *obsvec, uz_matrix_t *obspl1,uint32_t minibatchsize,uint32_t numberofobs,  uint32_t *indizes);
uint32_t uz_dqn_get_action(uz_dqn_t* self,uz_matrix_t * input,float *epsilon_start,float *epsilon_min,float *epsilon_decay, uint32_t number_of_actions);
void uz_dqn_sample_bitenv(uz_dqn_t *self);
void uz_dqn_act_bitenv_no_exploration(uz_dqn_t *self);
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