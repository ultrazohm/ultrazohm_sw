#pragma once

#include "../uz_matrix/uz_matrix.h"
#include <stdint.h>

typedef struct uz_env_t uz_env_t;

struct uz_env_config_t
{
    float (*get_reward)(void);
    uz_matrix_t *(*get_state)(void);
    void (*reset)(void);
    void (*step)(uint32_t action);
    float (*get_cumulative_reward)(void);
};

uz_env_t *uz_env_init(struct uz_env_config_t env_config);
