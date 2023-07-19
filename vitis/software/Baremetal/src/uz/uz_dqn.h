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
   struct uz_matrix_t reward_k; 
};


#endif // UZ_DQN_H
