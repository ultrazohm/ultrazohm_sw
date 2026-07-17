#ifndef UZ_DDPG_AGENT_H
#define UZ_DDPG_AGENT_H

#include <stdint.h>
#include "../uz_nn/uz_nn.h"

/**
 * @brief Object definition for a DDPG (continuous-action) policy agent.
 */
typedef struct uz_ddpg_agent_t uz_ddpg_agent_t;

/**
 * @brief Configuration struct for uz_ddpg_agent.
 *
 * The caller owns the network layer configuration (and the weight/bias/output
 * buffers it points to, exactly as uz_nn requires). The actor output is a single
 * scalar that is clamped to [action_min, action_max]. The network architecture
 * is fully flexible per agent instance.
 */
struct uz_ddpg_agent_config
{
    struct uz_nn_layer_config *layers; /**< Array of length number_of_layers, forwarded to uz_nn_init. First layer must have two network inputs (actual value, reference value); the output layer must have a single neuron. */
    uint32_t number_of_layers;         /**< Number of layers (hidden + output), see uz_nn_init. */
    float action_min;                  /**< Lower clamp bound for the actor output. */
    float action_max;                  /**< Upper clamp bound for the actor output. */
};

/**
 * @brief Initialize a DDPG agent instance from a static instance pool.
 *
 * @param config Configuration struct
 * @return uz_ddpg_agent_t* Pointer to the initialized instance
 */
uz_ddpg_agent_t *uz_ddpg_agent_init(struct uz_ddpg_agent_config config);

/**
 * @brief Run one forward pass and return the clamped actor action.
 *
 * @param self Pointer to agent instance
 * @param actual_value Measured plant value (network input 0)
 * @param reference_value Reference/setpoint value (network input 1)
 * @return float Actor output clamped to [action_min, action_max]
 */
float uz_ddpg_agent_step(uz_ddpg_agent_t *self, float actual_value, float reference_value);

#endif
