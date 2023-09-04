#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_dqn.h"
#include "uz_matrix.h"
#include <stdlib.h>
#include "uz_mtwister.h"

uint32_t array = {0,1,0,0,1,1,1,0};
//conf envrionment
struct uz_dqn_environment_config configenv = {
    .bitlength = 8,
    .bitarray = bitarray,
    .max_steps = 200
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dqn_environment_init(void)
{
uz_dqn_environment_t *testenv=uz_dqn_environment_init(configenv);
}

void test_calc_reward_without_penalty(void)
{

}

#endif // TEST
