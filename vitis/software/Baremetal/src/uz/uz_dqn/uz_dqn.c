#include "../uz_global_configuration.h"
#if UZ_DQN_MAX_INSTANCES > 0U
#if UZ_DQN_BUFFER_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <stdio.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"
#include "../uz_nn/uz_nn.h"
#include "../uz_matrix/uz_matrix.h"
#define EXPERIENCE_BUFFER_LENGTH 3
struct uz_dqn_experience_replay_t {
    float *reward;
    uint32_t *action;
    uz_matrix_t *observations;
    struct uz_matrix_t observations_matrix;
    size_t head;
    size_t tail;
    size_t length;
    bool is_full;
    bool is_ready;
};

struct uz_dqn_t {
    bool is_ready;
    uz_nn_t* critic;
    uz_matrix_t observations;
    uz_nn_t *critic_target_net;
    struct uz_dqn_experience_replay_t experience_buffer;
};

static uint32_t instance_counterbuf = 0U;
static uz_dqn_experience_replay_t instancesbuf[UZ_DQN_BUFFER_MAX_INSTANCES] = {0};
static uz_dqn_experience_replay_t* uz_dqn_experience_replay_allocation(void);
static uint32_t instance_counter = 0U;
static uz_dqn_t instances[UZ_DQN_MAX_INSTANCES] = {0};
static uz_dqn_t* uz_dqn_allocation(void);

static uz_dqn_t* uz_dqn_allocation(void){
    uz_assert(instance_counter < UZ_DQN_MAX_INSTANCES);
    uz_dqn_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_dqn_t* uz_dqn_init() {
    uz_dqn_t* self = uz_dqn_allocation();
    return (self);
}

static uz_dqn_experience_replay_t* uz_dqn_experience_replay_allocation(void){
    uz_assert(instance_counterbuf < UZ_DQN_BUFFER_MAX_INSTANCES);
    uz_dqn_experience_replay_t* self = &instancesbuf[instance_counterbuf];
    uz_assert_false(self->is_ready);
    instance_counterbuf++;
    self->is_ready = true;
    return (self);
}

uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, size_t length){
    uz_assert_not_NULL(buf_config.reward);
    uz_assert_not_NULL(buf_config.actions);
    uz_assert_not_NULL(buf_config.observations);
    uz_dqn_experience_replay_t *self = uz_dqn_experience_replay_allocation();
    self->length = length;
    self->reward = buf_config.reward;
    self->action = buf_config.actions;
    self->observations = uz_matrix_init(&self->observations_matrix,buf_config.observations,buf_config.length_of_buffer * buf_config.columns_of_observations,buf_config.length_of_buffer,buf_config.columns_of_observations);
    return (self);
}

void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    resetFloatArray(self->reward,EXPERIENCE_BUFFER_LENGTH);
    resetUintArray(self->action,EXPERIENCE_BUFFER_LENGTH);
    uz_matrix_set_zero(self->observations);
}

void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float rewarddata,uint32_t actiondata, float obsdata[]){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->reward[self->head]= rewarddata;
    // Aktionen in Buffer schreiben
    self->action[self->head] = actiondata;
    //Observationen in Buffer schreiben
    uint32_t index = self->head*EXPERIENCE_BUFFER_LENGTH;  
    for (int i = 0; i < EXPERIENCE_BUFFER_LENGTH; i++) {
    self->observations->data[index+i] = obsdata[i];
    }
    //counter +1 for next write operation
    self->head++;
    // check first if counter is full, set counter to zero again and write then
    if(self->head==(EXPERIENCE_BUFFER_LENGTH)){
      self->head=0U;
    }
}

void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float rewarddata,uint32_t actiondata, float obsdata[]){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    // calculate indizes
    // write reward data to buf
    rewarddata = *self->reward;
    //write action data to buf
    actiondata = *self->action;
    //write obs data to buf
    for (int i = 0; i < EXPERIENCE_BUFFER_LENGTH; i++) {
       obsdata[i] = self->observations->data[i];
    }
}

void uz_dqn_get_float_from_buffer(uz_dqn_experience_replay_t* self, uint32_t index, float *feedback){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
}

// helpers
void resetFloatArray(float *arr, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        arr[i] = 0.0f;
    }
}

void resetUintArray(uint32_t *arr, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        arr[i] = 0;
    }
}
#endif
#endif