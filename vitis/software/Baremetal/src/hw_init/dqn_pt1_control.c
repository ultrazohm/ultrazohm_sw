#include "../include/dqn_pt1_control.h"
#include "../uz/uz_global_configuration.h"

#if (UZ_APP != UZ_APP_DESKBENCH)
#include "../IP_Cores/uz_plantPT1/uz_plantPT1.h"
#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DDPG)
#include "../uz/uz_ddpg/uz_ddpg_agent.h"
#else
#include "../uz/uz_dqn/uz_dqn_agent.h"
#endif
#include "xparameters.h"
#include "../uz/uz_HAL.h"
#include <stddef.h>

void pt1_control_init(DS_Data *data)
{
    uz_assert_not_zero_uint32(PT1_CONTROL_PLANT_BASE_ADDRESS);
    data->objects.plant_pt1 = NULL;
    data->objects.dqn_agent = NULL;
    data->objects.ddpg_agent = NULL;

#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DDPG)
    data->objects.ddpg_agent = uz_ddpg_agent_init();
#else
    data->objects.dqn_agent = uz_dqn_agent_init();
#endif

    data->av.dqn_pt1_actual = 0.0f;
    data->av.dqn_pt1_reference = PT1_CONTROL_INITIAL_SETPOINT;
    data->av.dqn_pt1_setpoint = PT1_CONTROL_INITIAL_SETPOINT;
    data->av.dqn_pt1_action = 0.0f;

    struct uz_plantPT1_config_t config = {
        .base_address = PT1_CONTROL_PLANT_BASE_ADDRESS,
        .ip_core_frequency_Hz = PT1_CONTROL_PLANT_IP_CORE_FREQUENCY_HZ,
        .gain = PT1_CONTROL_GAIN,
        .time_constant = PT1_CONTROL_TIME_CONSTANT_S,
    };

    data->objects.plant_pt1 = uz_plantPT1_init(config);
    uz_plantPT1_set_input(data->objects.plant_pt1, 0.0f);
    uz_plantPT1_reset_integrator(data->objects.plant_pt1);
}

void pt1_control_step(DS_Data *data)
{
    uz_assert_not_NULL(data->objects.plant_pt1);

    data->av.dqn_pt1_actual = uz_plantPT1_read_output(data->objects.plant_pt1);
    data->av.dqn_pt1_reference = data->av.dqn_pt1_setpoint;

#if (PT1_CONTROL_AGENT == PT1_CONTROL_AGENT_DDPG)
    uz_assert_not_NULL(data->objects.ddpg_agent);
    data->av.dqn_pt1_action = uz_ddpg_agent_step(
        data->objects.ddpg_agent,
        data->av.dqn_pt1_actual,
        data->av.dqn_pt1_reference);
#else
    uz_assert_not_NULL(data->objects.dqn_agent);
    data->av.dqn_pt1_action = uz_dqn_agent_step(
        data->objects.dqn_agent,
        data->av.dqn_pt1_actual,
        data->av.dqn_pt1_reference);
#endif
    uz_plantPT1_set_input(data->objects.plant_pt1, data->av.dqn_pt1_action);
}

void pt1_control_stop(DS_Data *data)
{
    uz_assert_not_NULL(data->objects.plant_pt1);
    data->av.dqn_pt1_action = 0.0f;
    data->av.dqn_pt1_actual = uz_plantPT1_read_output(data->objects.plant_pt1);
    uz_plantPT1_set_input(data->objects.plant_pt1, 0.0f);
}

#else

void pt1_control_init(DS_Data *data)
{
    (void)data;
}

void pt1_control_step(DS_Data *data)
{
    (void)data;
}

void pt1_control_stop(DS_Data *data)
{
    (void)data;
}

#endif
