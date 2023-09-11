#ifndef UZ_ENV_H
#define UZ_ENV_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include <stdio.h>
#include "uz_nn.h"
#include "uz_mtwister.h"

typedef struct uz_dqn_environment_t uz_dqn_environment_t;
struct uz_dqn_environment_t {
    bool is_ready;
    uint32_t bitlength;
    uint32_t *bitinitial;
    uint32_t *bittarget;
    uint32_t max_steps;
    uz_matrix_t *inputfornn;
    struct uz_matrix_t inputfornn_matrix;
    float epsilon_start;
    float epsilon_min;
    float epsilon_decay;
    float cumreward;
};
struct uz_dqn_environment_config{
    uint32_t bitlength;
    uint32_t *const bitarray;
    float *const inarray;
    uint32_t *const targetarray;
    uint32_t max_steps;
    float epsilon_start;
    float epsilon_min;
    float epsilon_decay;
};

uz_dqn_environment_t *uz_dqn_environment_init(struct uz_dqn_environment_config envconf);
void uz_dqn_environment_reset(uz_dqn_environment_t *self,MTRand *seedRand);
void flipbit(uz_dqn_environment_t *self, MTRand *seedRand);
float calculate_reward_bit(uz_dqn_environment_t *self);
void uz_dqn_bitflip_action(uz_dqn_environment_t *self, uint32_t action);
#endif // UZ_DQN_H