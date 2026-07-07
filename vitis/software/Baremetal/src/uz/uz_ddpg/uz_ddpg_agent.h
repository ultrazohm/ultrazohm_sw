#ifndef UZ_DDPG_AGENT_H
#define UZ_DDPG_AGENT_H

typedef struct uz_ddpg_agent_t uz_ddpg_agent_t;

uz_ddpg_agent_t *uz_ddpg_agent_init(void);
float uz_ddpg_agent_step(uz_ddpg_agent_t *self, float actual_value, float reference_value);

#endif
