#include "../include/dqn_pt1_control.h"
#include "../IP_Cores/uz_plantPT1/uz_plantPT1.h"
#include "../uz/uz_dqn/uz_dqn_agent.h"
#include "xparameters.h"
#include "../uz/uz_HAL.h"
#include <stddef.h>

void dqn_pt1_control_init(DS_Data *data)
{
	uz_assert_not_zero_uint32(DQN_PT1_PLANT_BASE_ADDRESS);
    data->objects.dqn_agent = uz_dqn_agent_init();
    data->objects.plant_pt1 = NULL;

    data->av.dqn_pt1_actual = 0.0f;
    data->av.dqn_pt1_reference = DQN_PT1_INITIAL_SETPOINT;
    data->av.dqn_pt1_setpoint = DQN_PT1_INITIAL_SETPOINT;
    data->av.dqn_pt1_action = 0.0f;

    struct uz_plantPT1_config_t config = {
        .base_address = DQN_PT1_PLANT_BASE_ADDRESS,
        .ip_core_frequency_Hz = DQN_PT1_PLANT_IP_CORE_FREQUENCY_HZ,
        .gain = DQN_PT1_GAIN,
        .time_constant = DQN_PT1_TIME_CONSTANT_S,
    };

    data->objects.plant_pt1 = uz_plantPT1_init(config);
    uz_plantPT1_set_input(data->objects.plant_pt1, 0.0f);
    uz_plantPT1_reset_integrator(data->objects.plant_pt1);
}

void dqn_pt1_control_step(DS_Data *data)
{
    uz_assert_not_NULL(data->objects.plant_pt1);
    uz_assert_not_NULL(data->objects.dqn_agent);

    data->av.dqn_pt1_actual = uz_plantPT1_read_output(data->objects.plant_pt1);
    data->av.dqn_pt1_reference = data->av.dqn_pt1_setpoint;

    data->av.dqn_pt1_action = uz_dqn_agent_step(
        data->objects.dqn_agent,
        data->av.dqn_pt1_actual,
        data->av.dqn_pt1_reference);
    uz_plantPT1_set_input(data->objects.plant_pt1, data->av.dqn_pt1_action);
}

void dqn_pt1_control_stop(DS_Data *data)
{
    data->av.dqn_pt1_action = 0.0f;
    data->av.dqn_pt1_actual = uz_plantPT1_read_output(data->objects.plant_pt1);
    uz_plantPT1_set_input(data->objects.plant_pt1, 0.0f);
}
