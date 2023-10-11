#pragma once

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"

typedef struct uz_dqn_experience_replay_t uz_dqn_experience_replay_t;

struct uz_dqn_experience_replay_config
{
    uint32_t columns_of_observations;
    uint32_t length_of_buffer;
    float *const reward;
    float *const observations;
    float *const observations1;
    float *const obsvec;
    float *const obsvec1;
    uint32_t *const actions;
};

struct uz_dqn_experience_replay_t
{
    float *reward;
    uint32_t *action;
    uz_matrix_t *observations;
    uz_matrix_t *observations1;
    uz_matrix_t *vectorforobs;
    uz_matrix_t *vectorforobs1;
    struct uz_matrix_t vecobs_matrix1;
    struct uz_matrix_t vecobs_matrix;
    struct uz_matrix_t observations_matrix;
    struct uz_matrix_t observations_matrix_1;
    uint32_t head;
    uint32_t counterisfull;
    uint32_t length;
    bool is_full;
    bool is_ready;
};

uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, uint32_t length);


void uz_dqn_get_minibatch_from_buffer(uz_dqn_experience_replay_t *self, float *reward, uint32_t *actionindex, uz_matrix_t *obsvec, uz_matrix_t *obsvec1, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t minibatchsize, uint32_t *indizes);
void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t *self, float rewarddata, uint32_t actionindex, uz_matrix_t *obsdata, uz_matrix_t *obsdata1);
void uz_dqn_get_obs_from_buffer(uz_dqn_experience_replay_t *self, uz_matrix_t *obsdata, uint32_t index);
void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t *self, float *rewarddata, uint32_t *actiondata, uz_matrix_t *obsdata, uz_matrix_t *obsdata1, uint32_t index);
void uz_dqn_reset_buffer(uz_dqn_experience_replay_t *self);
uint32_t uz_dqn_buffer_get_counterisfull(uz_dqn_experience_replay_t *self);
uint32_t uz_dqn_buffer_get_head(uz_dqn_experience_replay_t *self);
uint32_t uz_dqn_buffer_get_length(uz_dqn_experience_replay_t *self);
uz_matrix_t *uz_dqn_buffer_get_vectorforobs(uz_dqn_experience_replay_t *self);
uz_matrix_t *uz_dqn_buffer_get_vectorforobs1(uz_dqn_experience_replay_t *self);

float uz_dqn_buffer_get_reward(uz_dqn_experience_replay_t *self,uint32_t index);
uint32_t uz_dqn_buffer_get_action(uz_dqn_experience_replay_t *self,uint32_t index);




