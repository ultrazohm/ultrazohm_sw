#include "../uz_global_configuration.h"
#if UZ_DQN_MAX_INSTANCES > 0U
#if UZ_DQN_BUFFER_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <stdio.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"

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


uz_dqn_t *uz_dqn_init(struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER],
struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER],
uint32_t number_of_layer,
 struct uz_dqn_experience_replay_config buffer_config,
uint32_t length_of_buffer, uint32_t headind)
{
// asserts
    uz_dqn_t *self = uz_dqn_allocation();
    self->critic = uz_nn_init(config_critic, number_of_layer, true);
    self->critic_target_net = uz_nn_init(config_target, number_of_layer, false);
    self->experience_buffer = uz_dqn_experience_replay_init(buffer_config,length_of_buffer,headind);
    return (self);
}

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

void uz_dqn_get_minibatch_from_buffer(uz_dqn_experience_replay_t* self,float *reward, int32_t *action, uz_matrix_t *obs, uint32_t minibatchsize, uint32_t *indizes)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(reward);
    uz_assert_not_NULL(action);
    uz_assert_not_NULL(obs);
    uz_assert_not_NULL(indizes);
    //uz_assert(minibatchsize=1);
    uz_assert(self->is_ready);
    float vecobs[minibatchsize];
    struct uz_matrix_t obsvec_matrix = {0};
    uz_matrix_t *obsvec = uz_matrix_init(&obsvec_matrix, vecobs, UZ_MATRIX_SIZE(vecobs),1, minibatchsize);
    for (uint32_t i = 0; i < minibatchsize; i++)
        {
        // schlechte zufallszahlengenerierung, aber für den start reichts
        //ind = rand() % self->length+1;
        uint32_t index = indizes[i];
        uz_dqn_get_from_buffer(self,reward,action,obsvec,index);
        uz_matrix_copy_row_to_matrix(obsvec,obs,i);
        reward++;
        action++;
        // obs++;
    }
}

float calculate_loss_dqn(uz_dqn_t* self, float *reward, float *gamma, uz_matrix_t *obs, uz_matrix_t *obsplus1, bool terminal){
    // berechne y_j
    float y_j = 0.0f;
    if(terminal==true)
    {
        y_j = *reward;
    }
    else{
        // berechne max_aQ(psi,a',theta)
        // sollte man sowohl die Aktion, als auch den index speichern? 
        // im nn object ist ja grad iwas enthalten nur nicht, der Aktionswert,
        // deshalb bringt ja der reine index hier nichts als aktion, schlauer wäre es
        // float action und uint action zu speichern, dass man beides hat
        // und evtl obs+1 und action(obs+1)
        uz_matrix_t* output_nn = uz_nn_get_output_data(self->critic);
		uint32_t action = uz_matrix_get_max_index(obs); // index
        y_j = *reward + *gamma * uz_matrix_get_max_value(obsplus1);
    }
    uz_matrix_t* output_nn = uz_nn_get_output_data(self->critic);
    float loss = (float)pow((y_j - uz_matrix_get_max_value(obs)),2.0f);
    return loss;
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

float calculate_reward_pendulum(float samplerate, float theta, float position, float velocity, bool penalty){
    // check, ob penalty nötig
    float z = 0.0f;
    if (penalty == true)
    {
        z = -1000.0f;
    }
    float r = -2.0f * samplerate * (100.0f * theta + position + 0.25f * (float)pow(velocity,2.0f)) + z;
    return r;
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