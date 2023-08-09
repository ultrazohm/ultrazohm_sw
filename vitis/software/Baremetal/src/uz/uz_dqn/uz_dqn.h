#ifndef UZ_DQN_H
#define UZ_DQN_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>
#include "uz_nn.h"

typedef struct uz_dqn_t uz_dqn_t;
typedef struct uz_dqn_experience_replay_t uz_dqn_experience_replay_t;

struct uz_dqn_experience_replay_config{
    uint32_t columns_of_observations;
    uint32_t length_of_buffer;
    float *const reward;
    float *const observations;
    int32_t *const actions;
};
uz_dqn_t *uz_dqn_init(struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER],
struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER],
uint32_t number_of_layer,
 struct uz_dqn_experience_replay_config buffer_config,
uint32_t length_of_buffer, uint32_t headind);
uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, uint32_t length, uint32_t headind);
void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,int32_t *actiondata, uz_matrix_t *obsdata);
void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,int32_t *actiondata, uz_matrix_t *obsdata, uint32_t index);
void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self);


#endif // UZ_DQN_H
