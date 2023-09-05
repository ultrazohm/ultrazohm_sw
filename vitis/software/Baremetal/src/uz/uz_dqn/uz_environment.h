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
    uint32_t *bit;
    uint32_t max_steps;
};
struct uz_dqn_environment_config{
    uint32_t bitlength;
    uint32_t *const bitarray;
    uint32_t max_steps;
};
uz_dqn_environment_t *uz_dqn_environment_init(struct uz_dqn_environment_config envconf);
uz_dqn_environment_reset(uz_dqn_environment_t *self,MTRand *seedRand);
#endif // UZ_DQN_H