#ifndef UZ_ENV_H
#define UZ_ENV_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include "uz_nn.h"
#include "../uz_mtwister/uz_mtwister.h"

typedef struct uz_dqn_environment_t uz_dqn_environment_t;

struct uz_dqn_environment_config
{
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
void uz_dqn_environment_reset(uz_dqn_environment_t *self, uz_mtwister_t *random_generator);
float uz_dqn_environment_get_reward(uz_dqn_environment_t *self);
void uz_dqn_environment_step(uz_dqn_environment_t *self, uint32_t action);
bool arraysequal(const uint32_t *inarray, const uint32_t *tararray, size_t size);
float calculate_reward_simple(uint32_t actionind);

bool uz_dqn_environment_is_finished(uz_dqn_environment_t *self);

void uz_dqn_enviroment_reset_cumulative_reward(uz_dqn_environment_t *self);
void uz_dqn_enviroment_add_to_cumulative_reward(uz_dqn_environment_t *self, float added_reward);
float uz_dqn_enviroment_get_cumulative_reward(uz_dqn_environment_t *self);

uz_matrix_t *uz_dqn_environment_get_state(uz_dqn_environment_t *self);

void save_values(float savecritic[], float savetarget[], float critic[], float target[], uint32_t step, uint32_t size);

#endif // UZ_DQN_H