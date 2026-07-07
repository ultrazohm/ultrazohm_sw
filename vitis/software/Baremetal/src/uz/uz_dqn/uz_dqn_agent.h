#ifndef UZ_DQN_AGENT_H
#define UZ_DQN_AGENT_H

#include <stdint.h>

typedef struct uz_dqn_agent_t uz_dqn_agent_t;

uz_dqn_agent_t *uz_dqn_agent_init(void);
float uz_dqn_agent_step(uz_dqn_agent_t *self, float actual_value, float reference_value);

#endif
