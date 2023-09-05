#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "uz_mtwister.h"
#include "uz_environment.h"

#define NUMBEROFBITS 8
uint32_t array[NUMBEROFBITS] = {0,1,0,0,1,1,1,0};
 //conf envrionment
struct uz_dqn_environment_config configenv = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array,
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
uz_dqn_environment_t *testenv = uz_dqn_environment_init(configenv);
MTRand seed = seedRand(1);
uz_dqn_environment_reset(testenv,&seed);
float est = 2.0f;
}


#endif // TEST
