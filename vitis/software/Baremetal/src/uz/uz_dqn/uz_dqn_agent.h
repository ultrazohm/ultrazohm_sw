#ifndef UZ_DQN_AGENT_H
#define UZ_DQN_AGENT_H

#include <stdint.h>
#include "../uz_nn/uz_nn.h"

/**
 * @brief Object definition for a DQN (discrete-action) policy agent.
 */
typedef struct uz_dqn_agent_t uz_dqn_agent_t;

/**
 * @brief Configuration struct for uz_dqn_agent.
 *
 * The caller owns the network layer configuration (and the weight/bias/output
 * buffers it points to, exactly as uz_nn requires) as well as the action-value
 * table. This keeps the network architecture and the number of discrete actions
 * fully flexible per agent instance.
 */
struct uz_dqn_agent_config
{
    struct uz_nn_layer_config *layers; /**< Array of length number_of_layers, forwarded to uz_nn_init. First layer must have two network inputs (actual value, reference value). */
    uint32_t number_of_layers;         /**< Number of layers (hidden + output), see uz_nn_init. */
    const float *action_values;        /**< Array of length number_of_actions mapping the greedy output index to a control action. */
    uint32_t number_of_actions;        /**< Number of discrete actions == number of neurons in the output layer. */
};

/**
 * @brief Initialize a DQN agent instance from a static instance pool.
 *
 * @param config Configuration struct
 * @return uz_dqn_agent_t* Pointer to the initialized instance
 */
uz_dqn_agent_t *uz_dqn_agent_init(struct uz_dqn_agent_config config);

/**
 * @brief Run one forward pass and return the greedy action value.
 *
 * @param self Pointer to agent instance
 * @param actual_value Measured plant value (network input 0)
 * @param reference_value Reference/setpoint value (network input 1)
 * @return float Selected action value from the configured action table
 */
float uz_dqn_agent_step(uz_dqn_agent_t *self, float actual_value, float reference_value);

#endif
