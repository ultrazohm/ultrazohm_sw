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

struct uz_dqn_experience_replay_t {
    float *reward;
    int32_t *action;
    uz_matrix_t *observations;
    struct uz_matrix_t observations_matrix;
    uint32_t head;
    uint32_t length;
    bool is_full;
    bool is_ready;
};

struct uz_dqn_t {
    bool is_ready;
    uz_nn_t *critic;
    uz_nn_t *critic_target_net;
    uz_dqn_experience_replay_t *experience_buffer;
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

static uz_dqn_experience_replay_t* uz_dqn_experience_replay_allocation(void){
    uz_assert(instance_counterbuf < UZ_DQN_BUFFER_MAX_INSTANCES);
    uz_dqn_experience_replay_t* self = &instancesbuf[instance_counterbuf];
    uz_assert_false(self->is_ready);
    instance_counterbuf++;
    self->is_ready = true;
    return (self);
}

uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, uint32_t length, uint32_t headind){
    uz_assert_not_NULL(buf_config.reward);
    uz_assert_not_NULL(buf_config.actions);
    uz_assert_not_NULL(buf_config.observations);
    uz_dqn_experience_replay_t *self = uz_dqn_experience_replay_allocation();
    self->length = length;
    self->reward = buf_config.reward;
    self->action = buf_config.actions;
    self->observations = uz_matrix_init(&self->observations_matrix,buf_config.observations,buf_config.length_of_buffer * buf_config.columns_of_observations,buf_config.length_of_buffer,buf_config.columns_of_observations);
    self->head = headind; // vorübergehend, für test, dass auf beliebigen index nach init zugegriffen werden kann, kann man später noch entfernenS
    return (self);
}


// uz_dqn_t *uz_dqn_init() {
//     // uz_assert_not_NULL(buf_config.observations);
//     uz_dqn_t *self = uz_dqn_allocation();
//     self->critic = uz_nn_init(config_target, number_of_layer, true);
//     self->critic_target_net = uz_nn_init(config_target, number_of_layer, false);
//     self->experience_buffer = uz_dqn_experience_replay_init(buffer_config,length_of_buffer,headind);
//     return (self);
// }

void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->head = 0U;
    resetFloatArray(self->reward,self->length);
    resetintArray(self->action,self->length);
    uz_matrix_set_zero(self->observations);
}

void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,int32_t *actiondata, uz_matrix_t *obsdata){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(rewarddata);
    uz_assert_not_NULL(actiondata);
    uz_assert_not_NULL(obsdata);
    uz_assert(self->is_ready);
    // check first if counter is full, set counter to zero again and write then, set is_full true
    if(self->head==(self->length)){
      self->is_full = true;
      self->head=0U;
    }
    self->reward[self->head]= *rewarddata;
    self->action[self->head] = *actiondata;
    uz_matrix_copy_row_to_matrix(obsdata,self->observations,self->head);
    self->head++;
}

void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float *rewarddata, int32_t *actiondata, uz_matrix_t *obsdata, uint32_t index){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(rewarddata);
    uz_assert_not_NULL(actiondata);
    uz_assert_not_NULL(obsdata);
    uz_assert(self->is_ready);
    uz_assert(index<self->length); // assert, wenn index größer als die länge des buffers
    *rewarddata = self->reward[index];
    *actiondata = self->action[index];
    uz_matrix_copy_row_from_matrix(self->observations,obsdata,index);
}

// helpers
void resetFloatArray(float *arr, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        arr[i] = 0.0f;
    }
}

void resetintArray(int32_t *arr, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        arr[i] = 0;
    }
}
#endif
#endif