#ifndef UZ_ENVIRONMENT_PT1_H
#define UZ_ENVIRONMENT_PT1_H

#include "../uz_matrix/uz_matrix.h"
#include "../uz_dqn/uz_dqn.h"

typedef struct uz_environment_pt1_t uz_environment_pt1_t;

uz_environment_pt1_t *uz_environment_pt1_init(float gain, float time_constant, float integration_time, float *input_array);
float uz_environment_pt1_step(uz_environment_pt1_t *self, float input);

void uz_environment_pt1_reset(uz_environment_pt1_t *self);
void uz_environment_pt1_dqn_step(uz_environment_pt1_t *self, uint32_t action, float set_point);
float uz_environment_pt1_get_output(uz_environment_pt1_t *self);
float uz_environment_pt1_get_reward(uz_environment_pt1_t *self);
float uz_environment_pt1_get_cumulative_reward(uz_environment_pt1_t *self);
float uz_environment_pt1_step_one_episode(uz_dqn_t *self, uint32_t max_steps, bool train, uz_environment_pt1_t *env, float set_point, bool logging, float *error, float *input, float *output, uint32_t number_of_timesteps_per_control_action);

uz_matrix_t *uz_environment_pt1_get_state(uz_environment_pt1_t *self);
float uz_environment_pt1_get_input(uz_environment_pt1_t *self);

#endif // UZ_ENVIRONMENT_PT1_H
