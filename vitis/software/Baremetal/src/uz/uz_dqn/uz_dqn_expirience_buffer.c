#include "../uz_global_configuration.h"
#if UZ_DQN_BUFFER_MAX_INSTANCES > 0U

#include "uz_dqn_expirience_buffer.h"
#include <stdbool.h>
#include "../uz_HAL.h"

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

static uint32_t instance_counterbuf = 0U;
static uz_dqn_experience_replay_t instancesbuf[UZ_DQN_BUFFER_MAX_INSTANCES] = {0};
static uz_dqn_experience_replay_t *uz_dqn_experience_replay_allocation(void);

static uz_dqn_experience_replay_t *uz_dqn_experience_replay_allocation(void)
{
    uz_assert(instance_counterbuf < UZ_DQN_BUFFER_MAX_INSTANCES);
    uz_dqn_experience_replay_t *self = &instancesbuf[instance_counterbuf];
    uz_assert_false(self->is_ready);
    instance_counterbuf++;
    self->is_ready = true;
    return (self);
}

uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, uint32_t length)
{
    uz_assert_not_NULL(buf_config.reward);
    uz_assert_not_NULL(buf_config.actions);
    uz_assert_not_NULL(buf_config.observations);
    uz_assert_not_NULL(buf_config.obsvec);
    uz_assert_not_NULL(buf_config.observations1);
    uz_assert_not_NULL(buf_config.obsvec1);
    uz_dqn_experience_replay_t *self = uz_dqn_experience_replay_allocation();
    self->length = length;
    self->reward = buf_config.reward;
    self->action = buf_config.actions;
    self->vectorforobs = uz_matrix_init(&self->vecobs_matrix, buf_config.obsvec, buf_config.columns_of_observations, 1, buf_config.columns_of_observations);
    self->vectorforobs1 = uz_matrix_init(&self->vecobs_matrix1, buf_config.obsvec1, buf_config.columns_of_observations, 1, buf_config.columns_of_observations);
    self->observations = uz_matrix_init(&self->observations_matrix, buf_config.observations, buf_config.length_of_buffer * buf_config.columns_of_observations, buf_config.length_of_buffer, buf_config.columns_of_observations);
    self->observations1 = uz_matrix_init(&self->observations_matrix_1, buf_config.observations1, buf_config.length_of_buffer * buf_config.columns_of_observations, buf_config.length_of_buffer, buf_config.columns_of_observations);
    self->head = 0; // steht immer auf 0 bei der init
    self->counterisfull = 0;
    return (self);
}

void uz_dqn_get_minibatch_from_buffer(uz_dqn_experience_replay_t *self, float *reward, uint32_t *actionindex, uz_matrix_t *obsvec, uz_matrix_t *obsvec1, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t minibatchsize, uint32_t *indizes)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(reward);
    uz_assert_not_NULL(actionindex);
    uz_assert_not_NULL(obsvec);
    uz_assert_not_NULL(obsvec1);
    uz_assert_not_NULL(obspl1);
    uz_assert_not_NULL(obs);
    uz_assert_not_NULL(indizes);
    uz_assert(self->is_ready);
    for (uint32_t i = 0; i < minibatchsize; i++)
    {
        uint32_t index = indizes[i];
        if (self->counterisfull == 0)
        {
            if (index >= self->head)
            {
                index = self->head;
            }
        }
        uz_dqn_get_from_buffer(self, reward, actionindex, obsvec, obsvec1, index);
        uz_matrix_copy_row_to_matrix(obsvec, obs, i);
        uz_matrix_copy_row_to_matrix(obsvec1, obspl1, i);
        reward++;
        actionindex++;
    }
}

void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t *self, float rewarddata, uint32_t actionindex, uz_matrix_t *obsdata, uz_matrix_t *obsdata1)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(obsdata);
    uz_assert_not_NULL(obsdata1);
    uz_assert(self->is_ready);
    self->is_full = false;
    if (self->head == (self->length))
    {
        self->is_full = true;
        self->head = 0U;
        self->counterisfull++;
    }
    self->reward[self->head] = rewarddata;
    self->action[self->head] = actionindex;
    uz_matrix_copy_row_to_matrix(obsdata, self->observations, self->head);
    uz_matrix_copy_row_to_matrix(obsdata1, self->observations1, self->head);
    self->head++;
}

void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t *self, float *rewarddata, uint32_t *actiondata, uz_matrix_t *obsdata, uz_matrix_t *obsdata1, uint32_t index)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(obsdata);
    uz_assert_not_NULL(obsdata1);
    uz_assert(self->is_ready);
    uz_assert(index < self->length);
    *rewarddata = self->reward[index];
    *actiondata = self->action[index];
    uz_matrix_copy_row_from_matrix(self->observations, obsdata, index);
    uz_matrix_copy_row_from_matrix(self->observations1, obsdata1, index);
}

void uz_dqn_get_obs_from_buffer(uz_dqn_experience_replay_t *self, uz_matrix_t *obsdata, uint32_t index)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(obsdata);
    uz_assert(self->is_ready);
    uz_assert(index < self->length);
    uz_matrix_copy_row_from_matrix(self->observations, obsdata, index);
}

void uz_dqn_reset_buffer(uz_dqn_experience_replay_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->head = 0U;
    resetFloatArray(self->reward, self->length);
    resetuintArray(self->action, self->length);
    uz_matrix_set_zero(self->observations);
    uz_matrix_set_zero(self->observations1);
    uz_matrix_set_zero(self->vectorforobs);
    uz_matrix_set_zero(self->vectorforobs1);
}

uint32_t uz_dqn_buffer_get_counterisfull(uz_dqn_experience_replay_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->counterisfull;
}



uint32_t uz_dqn_buffer_get_head(uz_dqn_experience_replay_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->head;
}

uint32_t uz_dqn_buffer_get_length(uz_dqn_experience_replay_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->length;
}

uz_matrix_t *uz_dqn_buffer_get_vectorforobs(uz_dqn_experience_replay_t *self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->vectorforobs;
}

uz_matrix_t *uz_dqn_buffer_get_vectorforobs1(uz_dqn_experience_replay_t *self)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    return self->vectorforobs1;
}

#endif