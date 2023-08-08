#ifndef UZ_DQN_H
#define UZ_DQN_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct uz_dqn_t uz_dqn_t;
typedef struct uz_dqn_experience_replay_t  uz_dqn_experience_replay_t;

struct uz_dqn_experience_replay_config{
    uint32_t columns_of_observations;
    uint32_t length_of_buffer;
    float *const reward;
    float *const observations;
    uint32_t *const actions;
};

uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, size_t length);
void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,uint32_t *actiondata, uz_matrix_t *obsdata);
void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,uint32_t *actiondata, uz_matrix_t *obsdata);
void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self);

// #define SIZE_OF_BUFFER 1000000

// uint32_t index=0U;
// struct uz_dqn_experience_replay_t buffer[SIZE_OF_BUFFER]={0};

// void dqn_push_to_buffer(struct uz_dqn_experience_replay_t sample)
// {
//    if(index==(SIZE_OF_BUFFER-1)){
//       index=0U;
//    }
//    buffer[index] = sample;
//    index++;
// }

// void dqn_get_random_samples(){
//    indexes[64]=randi(64);
//    buffer[indexes];
//    buffer_ptr=[&buffer[index(1),&buffer[index(2)]];
// }



#endif // UZ_DQN_H
