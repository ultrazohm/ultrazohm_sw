#include "../uz_global_configuration.h"
#if UZ_ENV_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_dqn_environment_bitflip.h"

struct uz_env_t {
    bool is_ready;
    float (*get_reward)(void);
    uz_matrix_t* (*get_state)(void);
    void (*reset)(void);
    void (*step)(uint32_t action);
    float (*get_cumulative_reward)(void);
};

static uint32_t instance_counter = 0U;
static uz_env_t instances[UZ_ENV_MAX_INSTANCES] = { 0 };

static uz_env_t* uz_env_allocation(void);

static uz_env_t* uz_env_allocation(void){
    uz_assert(instance_counter < UZ_ENV_MAX_INSTANCES);
    uz_env_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_env_t *uz_env_init(struct uz_env_config_t env_config)
{
    uz_env_t* self = uz_env_allocation();
    return (self);
}

#endif


