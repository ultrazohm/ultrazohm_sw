#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_dqn_environment_bitflip.h"

#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "uz_environment.h"

struct uz_env_config_t config = {
    .get_cumulative_reward = &uz_dqn_enviroment_get_cumulative_reward,
    .get_reward = uz_dqn_environment_get_reward,
    .
    };

void setUp(void)
{
}

void tearDown(void)
{
}

void test_dqn_environment_notest(void)
{
}

#endif // TEST

