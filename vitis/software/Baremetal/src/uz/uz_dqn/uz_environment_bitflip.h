#pragma once

#include "../uz_matrix/uz_matrix.h"
#include "../uz_HAL.h"
#include <stdbool.h>
#include "uz_nn.h"
#include "../uz_mtwister/uz_mtwister.h"
#include "uz_dqn.h"

typedef struct uz_environment_bitflip_t uz_environment_bitflip_t;

struct uz_dqn_environment_config
{
    uint32_t bitlength;
    uint32_t *const bitarray;
    float *const inarray;
    uint32_t *const targetarray;
    uint32_t max_steps;
};

uz_environment_bitflip_t *uz_environment_bitflip_init(struct uz_dqn_environment_config envconf);
void uz_environment_bitflip_reset(uz_environment_bitflip_t *self, uz_mtwister_t *random_generator);
float uz_environment_bitflip_get_reward(uz_environment_bitflip_t *self);

bool uz_environment_bitflip_is_finished(uz_environment_bitflip_t *self);

void uz_environment_bitflip_add_to_cumulative_reward(uz_environment_bitflip_t *self, float added_reward);
float uz_environment_bitflip_get_cumulative_reward(uz_environment_bitflip_t *self);

void uz_environment_bitflip_save_values(float savecritic[], float savetarget[], float critic[], float target[], uint32_t step, uint32_t size);

uz_matrix_t *uz_environment_bitflip_get_state(uz_environment_bitflip_t *self);
float uz_environment_bitflip_step_one_episode(uz_dqn_t *self, uint32_t max_steps, bool train, uz_environment_bitflip_t *env);
