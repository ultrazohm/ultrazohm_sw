#include "../uz_global_configuration.h"
#if UZ_DDPG_AGENT_MAX_INSTANCES > 0U

#include "uz_ddpg_agent.h"
#include "../uz_HAL.h"
#include "../uz_matrix/uz_matrix.h"
#include "../uz_nn/uz_nn.h"

#include <stdbool.h>

#define UZ_DDPG_AGENT_NUMBER_OF_INPUTS 2U
#define UZ_DDPG_AGENT_NUMBER_OF_OUTPUTS 1U

struct uz_ddpg_agent_t
{
    bool is_ready;
    uz_nn_t *network;
    struct uz_matrix_t input_matrix;
    float input_data[UZ_DDPG_AGENT_NUMBER_OF_INPUTS];
    float action_min;
    float action_max;
};

static uint32_t instance_counter = 0U;
static uz_ddpg_agent_t instances[UZ_DDPG_AGENT_MAX_INSTANCES] = {0};

static uz_ddpg_agent_t *uz_ddpg_agent_allocation(void);

static uz_ddpg_agent_t *uz_ddpg_agent_allocation(void)
{
    uz_assert(instance_counter < UZ_DDPG_AGENT_MAX_INSTANCES);
    uz_ddpg_agent_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

static float clamp_action(uz_ddpg_agent_t *self, float action)
{
    if (action > self->action_max)
    {
        return self->action_max;
    }
    if (action < self->action_min)
    {
        return self->action_min;
    }
    return action;
}

uz_ddpg_agent_t *uz_ddpg_agent_init(struct uz_ddpg_agent_config config)
{
    uz_assert_not_NULL(config.layers);
    uz_assert(config.number_of_layers > 1U);
    uz_assert(config.action_max >= config.action_min);
    uz_assert(config.layers[0].number_of_inputs == UZ_DDPG_AGENT_NUMBER_OF_INPUTS);
    uz_assert(config.layers[config.number_of_layers - 1U].length_of_output == UZ_DDPG_AGENT_NUMBER_OF_OUTPUTS);

    uz_ddpg_agent_t *self = uz_ddpg_agent_allocation();
    self->action_min = config.action_min;
    self->action_max = config.action_max;
    self->input_data[0] = 0.0f;
    self->input_data[1] = 0.0f;
    uz_matrix_init(&self->input_matrix, self->input_data, UZ_MATRIX_SIZE(self->input_data), 1U, UZ_DDPG_AGENT_NUMBER_OF_INPUTS);
    self->network = uz_nn_init(config.layers, config.number_of_layers);
    return (self);
}

float uz_ddpg_agent_step(uz_ddpg_agent_t *self, float actual_value, float reference_value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input_data[0] = actual_value;
    self->input_data[1] = reference_value;
    uz_nn_ff(self->network, &self->input_matrix);

    uz_matrix_t *actor_output = uz_nn_get_output_data(self->network);
    const float action = uz_matrix_get_element_zero_based(actor_output, 0U, 0U);
    return clamp_action(self, action);
}

#endif
