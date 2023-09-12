#include "../uz_global_configuration.h"
#if UZ_DQN_ENV_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <stdio.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"
#include "uz_environment.h"

static uint32_t instance_counterenv = 0U;
static uz_dqn_environment_t instancesenv[UZ_DQN_ENV_MAX_INSTANCES] = {0};
static uz_dqn_environment_t* uz_dqn_environment_allocation(void);

static uz_dqn_environment_t* uz_dqn_environment_allocation(void){
    uz_assert(instance_counterenv < UZ_DQN_BUFFER_MAX_INSTANCES);
    uz_dqn_environment_t* self = &instancesenv[instance_counterenv];
    uz_assert_false(self->is_ready);
    instance_counterenv++;
    self->is_ready = true;
    return (self);
}

uz_dqn_environment_t *uz_dqn_environment_init(struct uz_dqn_environment_config envconf){
    uz_dqn_environment_t *self = uz_dqn_environment_allocation();
    self->bitlength = envconf.bitlength;
    self->bitinitial = envconf.bitarray;
    self->bittarget = envconf.targetarray;
    self->inputfornn = uz_matrix_init(&self->inputfornn_matrix,envconf.inarray,2 * envconf.bitlength,1,2 * envconf.bitlength);
    self->epsilon_min = envconf.epsilon_min;
    self->epsilon_start = envconf.epsilon_start;
    self->epsilon_decay = envconf.epsilon_decay;
    if (envconf.max_steps == 0){
        self->max_steps = self->bitlength;
    }
    else{
        self->max_steps = envconf.max_steps;
    }
    return (self);
}

void uz_dqn_environment_reset(uz_dqn_environment_t *self,MTRand *seedRand){
for(uint32_t i=0; i<self->bitlength;i++){
    // self->bittarget[i]  = genRand_zero_one(seedRand);
    self->bitinitial[i] = genRand_zero_one(seedRand);
    self->inputfornn->data[i] = (float)self->bitinitial[i];
}
self->is_ready = true;
self->cumreward = 0.0f;
}

bool arraysequal(const uint32_t *inarray, const uint32_t *tararray, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (inarray[i] != tararray[i]) {
            return false; // Arrays are not equal
        }
    }
    return true; // Arrays are equal
}

float calculate_reward_bit(uz_dqn_environment_t *self)
{
    float r;
    bool z = arraysequal(self->bitinitial,self->bittarget,self->bitlength);
    if (z==true)
    {
    r = 0.0f;
    }
    else{
    r = -1.0f;
    }
    return r;
}

void uz_dqn_bitflip_action(uz_dqn_environment_t *self, uint32_t action)
{
    // flip bit
    if (self->bitinitial[action] == 1){
    self->bitinitial[action] = 0;
    self->inputfornn->data[action] = 0.0f;
    }
    else{
    self->bitinitial[action] = 1;
    self->inputfornn->data[action] = 1.0f;
    }
}

void flipbit(uz_dqn_environment_t *self, MTRand *seedRand)
{
    // get random index
    uint32_t x = genRand_uint32_t(seedRand,self->bitlength);
    // flip bit
    if (self->bitinitial[x] == 1){
    self->bitinitial[x] = 0;
    self->inputfornn->data[x] = 0.0f;
    }
    else{
    self->bitinitial[x] = 1;
    self->inputfornn->data[x] = 1.0f;
    }
}

void uz_dqn_environment_action(uz_dqn_environment_t *self, MTRand *seedRand)
{
    if (self->is_ready == true)
    // flipbit(self,seedRand);

    if(self->bittarget == self->bitinitial)
    self->is_ready = false;
}

#endif