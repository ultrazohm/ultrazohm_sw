#include "../uz_global_configuration.h"
#if UZ_DQN_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_dqn.h"
#include "../uz_nn/uz_nn.h"

#define EXPIRIENCE_BUFFER_LENGTH 100000U

struct uz_dqn_t {
    bool is_ready;
    uz_nn_t* critic;
    uz_matrix_t observations;
    uz_nn_t *critic_target_net;
    struct uz_dqn_expirience_replay_t expirience_buffer[EXPIRIENCE_BUFFER_LENGTH];
};

struct uz_dqn_training_data_t{

};

static uint32_t instance_counter = 0U;
static uz_dqn_t instances[UZ_DQN_MAX_INSTANCES] = { 0 };

static uz_dqn_t* uz_dqn_allocation(void);

static uz_dqn_t* uz_dqn_allocation(void){
    uz_assert(instance_counter < UZ_DQN_MAX_INSTANCES);
    uz_dqn_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_dqn_t* uz_dqn_init() {
    uz_dqn_t* self = uz_dqn_allocation();
    return (self);
}
#endif