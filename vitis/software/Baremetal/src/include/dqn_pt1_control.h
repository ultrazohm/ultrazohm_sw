#ifndef DQN_PT1_CONTROL_H
#define DQN_PT1_CONTROL_H

#include "pt1_control_config.h"
#include "../globalData.h"

void pt1_control_init(DS_Data *data);
void pt1_control_step(DS_Data *data);
void pt1_control_stop(DS_Data *data);
void pt1_control_start_eval_profile(DS_Data *data);

#define dqn_pt1_control_init pt1_control_init
#define dqn_pt1_control_step pt1_control_step
#define dqn_pt1_control_stop pt1_control_stop

#endif
