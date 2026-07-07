#ifndef DQN_PT1_CONTROL_H
#define DQN_PT1_CONTROL_H

#include "../globalData.h"

#ifndef DQN_PT1_PLANT_BASE_ADDRESS
#define DQN_PT1_PLANT_BASE_ADDRESS XPAR_UZ_USER_UZ_PLANTMODEL_PT1_0_BASEADDR
#endif

#define DQN_PT1_PLANT_IP_CORE_FREQUENCY_HZ 100000000U
#define DQN_PT1_CONTROL_DECIMATION 100U
#define DQN_PT1_GAIN 1.0f
#define DQN_PT1_TIME_CONSTANT_S 0.2f
#define DQN_PT1_INITIAL_SETPOINT 0.0f

void dqn_pt1_control_init(DS_Data *data);
void dqn_pt1_control_step(DS_Data *data);
void dqn_pt1_control_stop(DS_Data *data);

#endif
