#ifdef TEST

#include "unity.h"
#include "uz_dqn.h"
#include "uz_nn.h"
#include "uz_nn_layer.h"
#include "uz_nn_activation_functions.h"
#include "uz_matrix.h"
#include "uz_mtwister.h"
#include "uz_environment.h"

#define NUMBEROFBITS 4
uint32_t array[NUMBEROFBITS] = {0,1,0,0};
uint32_t tararray[NUMBEROFBITS] = {0,0,1,0};
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


#endif // TEST
