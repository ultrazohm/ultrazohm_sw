#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"
#include "uz_dqn_expirience_buffer.h"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "uz_mtwister.h"
#include "uz_environment.h"
#include "uz_array.h"

#define NUMBEROFBITS 8
uint32_t array[NUMBEROFBITS] = {0, 1, 0, 0, 1, 0, 1, 0};
uint32_t tararray[NUMBEROFBITS] = {0, 1, 0, 0, 1, 0, 1, 0};
uint32_t array2[NUMBEROFBITS] = {0, 1, 0, 0, 1, 0, 1, 0};
uint32_t tararray2[NUMBEROFBITS] = {0, 1, 0, 0, 1, 0, 1, 0};
float inarray[NUMBEROFBITS] = {0.0f};

// conf envrionment
struct uz_dqn_environment_config configenv = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array,
    .targetarray = tararray,
    .inarray = inarray,
    .max_steps = 2000};

struct uz_dqn_environment_config configenv2 = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array2,
    .targetarray = tararray2,
    .inarray = inarray};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dqn_environment_reward_calc(void)
{
    uz_environment_bitflip_t *testenv3 = uz_dqn_environment_init(configenv2);
    float reward = uz_dqn_environment_get_reward(testenv3);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, reward); // arrays sind gleich
    array2[0] = 1;
    reward = uz_dqn_environment_get_reward(testenv3);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, reward); // arrays sind ungleich
}


#endif // TEST
