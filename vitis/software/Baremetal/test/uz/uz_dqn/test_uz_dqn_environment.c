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
uint32_t array[NUMBEROFBITS] = {0,1,0,0,1,0,1,0};
uint32_t tararray[NUMBEROFBITS] = {0,0,1,0,1,1,1,1};
uint32_t array2[NUMBEROFBITS] = {0,1,0,0,1,0,1,0};
uint32_t tararray2[NUMBEROFBITS] = {0,1,0,0,1,0,1,0};
float inarray2[NUMBEROFBITS] = {0.0f};

 //conf envrionment
struct uz_dqn_environment_config configenv = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array,
    .targetarray = tararray,
    .max_steps = 4000
};
struct uz_dqn_environment_config configenv2 = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array
};

struct uz_dqn_environment_config configenv3 = {
    .bitlength = NUMBEROFBITS,
    .bitarray = array2,
    .targetarray = tararray2,
    .inputarray = inarray2,
    .max_steps = 2000
};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dqn_environment_check_max_steps(void)
{
uz_dqn_environment_t *testenv2 = uz_dqn_environment_init(configenv2);
TEST_ASSERT_EQUAL_UINT32(testenv2->bitlength,testenv2->max_steps);
}
void test_uz_dqn_environment_init_reset_and_flip_bits(void)
{
uz_dqn_environment_t *testenv = uz_dqn_environment_init(configenv);
MTRand seed = seedRand(1);
uz_dqn_environment_reset(testenv,&seed);
for(uint32_t j=0; j<testenv->max_steps;j++){
    flipbit(testenv, &seed);
    // check if arrays are the same
    uint32_t counter = 0;
    for(uint32_t i=0; i<testenv->bitlength;i++){
    if(testenv->bitinitial[i] == testenv->bittarget[i])
    {
        counter++;
    }
    if(counter==testenv->bitlength)
        printf("Bitmuster ist gleich nach Episode %.0d \n",(int)j);  
    }
    }
}

void test_uz_dqn_environment_reward_calc(void)
{
uz_dqn_environment_t *testenv3 = uz_dqn_environment_init(configenv3);
float reward = calculate_reward_bit(testenv3);
TEST_ASSERT_EQUAL_FLOAT(0.0f,reward); // arrays sind gleich
array2[0] = 1;
reward = calculate_reward_bit(testenv3);
TEST_ASSERT_EQUAL_FLOAT(-1.0f,reward); // arrays sind ungleich
}
#endif // TEST
