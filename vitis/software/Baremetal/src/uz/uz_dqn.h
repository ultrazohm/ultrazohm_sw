#ifndef UZ_DQN_H
#define UZ_DQN_H

#include "../uz_matrix/uz_matrix.h"

typedef struct uz_dqn_t uz_dqn_t;

// struct uz_dqn_observations_t {

// };

// struct uz_dqn_actions_t {

// };

struct uz_dqn_expirience_replay_t{
   struct uz_matrix_t observations_k;
   struct uz_matrix_t observations_k_plus_one; 
   uint32_t action_k; 
   float reward_k; 
};

#define SIZE_OF_BUFFER 1000000

uint32_t index=0U;
struct uz_dqn_expirience_replay_t buffer[SIZE_OF_BUFFER]={0};

void dqn_push_to_buffer(struct uz_dqn_expirience_replay_t sample)
{
   if(index==(SIZE_OF_BUFFER-1)){
      index=0U;
   }
   buffer[index] = sample;
   index++;
}

void dqn_get_random_samples(){
   indexes[64]=randi(64);
   buffer[indexes]
   buffer_ptr=[&buffer[index(1) &buffer[index(2) ]         ]
}



#endif // UZ_DQN_H
