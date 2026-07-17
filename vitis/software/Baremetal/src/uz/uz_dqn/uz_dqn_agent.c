#include "../uz_global_configuration.h"
#if UZ_DQN_AGENT_MAX_INSTANCES > 0U

#include "uz_dqn_agent.h"
#include "../uz_HAL.h"
#include "../uz_matrix/uz_matrix.h"
#include "../uz_nn/uz_nn.h"

#include <stdbool.h>

#define UZ_DQN_AGENT_NUMBER_OF_INPUTS 2U

struct uz_dqn_agent_t
{
    bool is_ready;
    uz_nn_t *network;
    struct uz_matrix_t input_matrix;
    float input_data[UZ_DQN_AGENT_NUMBER_OF_INPUTS];
    const float *action_values;
    uint32_t number_of_actions;
};

static uint32_t instance_counter = 0U;
static uz_dqn_agent_t instances[UZ_DQN_AGENT_MAX_INSTANCES] = {0};

static uz_dqn_agent_t *uz_dqn_agent_allocation(void);

static uz_dqn_agent_t *uz_dqn_agent_allocation(void)
{
    uz_assert(instance_counter < UZ_DQN_AGENT_MAX_INSTANCES);
    uz_dqn_agent_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_dqn_agent_t *uz_dqn_agent_init(struct uz_dqn_agent_config config)
{
    uz_assert_not_NULL(config.layers);
    uz_assert_not_NULL(config.action_values);
    uz_assert(config.number_of_layers > 1U);
    uz_assert(config.number_of_actions > 0U);
    uz_assert(config.layers[0].number_of_inputs == UZ_DQN_AGENT_NUMBER_OF_INPUTS);
    uz_assert(config.layers[config.number_of_layers - 1U].length_of_output == config.number_of_actions);

    uz_dqn_agent_t *self = uz_dqn_agent_allocation();
    self->action_values = config.action_values;
    self->number_of_actions = config.number_of_actions;
    self->input_data[0] = 0.0f;
    self->input_data[1] = 0.0f;
    uz_matrix_init(&self->input_matrix, self->input_data, UZ_MATRIX_SIZE(self->input_data), 1U, UZ_DQN_AGENT_NUMBER_OF_INPUTS);
    self->network = uz_nn_init(config.layers, config.number_of_layers);
    return (self);
}

float uz_dqn_agent_step(uz_dqn_agent_t *self, float actual_value, float reference_value)
{
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->input_data[0] = actual_value;
    self->input_data[1] = reference_value;
    uz_nn_ff(self->network, &self->input_matrix);
    uint32_t action_index = uz_matrix_get_max_index(uz_nn_get_output_data(self->network));
    uz_assert(action_index < self->number_of_actions);
    return self->action_values[action_index];
}

#endif
