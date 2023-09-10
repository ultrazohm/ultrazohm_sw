#include "../uz_global_configuration.h"
#if UZ_DQN_MAX_INSTANCES > 0U
#if UZ_DQN_BUFFER_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include <stdio.h>
#include <stdbool.h>
#include "../uz_HAL.h"
#include "uz_dqn.h"


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
    self->qvalues = buf_config.qvalues;
    self->action = buf_config.actions;
    self->vectorforobs= uz_matrix_init(&self->vecobs_matrix,buf_config.obsvec,buf_config.columns_of_observations,1,buf_config.columns_of_observations);
    self->observations = uz_matrix_init(&self->observations_matrix,buf_config.observations,buf_config.length_of_buffer * buf_config.columns_of_observations,buf_config.length_of_buffer,buf_config.columns_of_observations);
    self->head = headind; // vorübergehend, für test, dass auf beliebigen index nach init zugegriffen werden kann, kann man später noch entfernenS
    self->counterisfull = 0;
    return (self);
}


uz_dqn_t *uz_dqn_init(struct uz_matrix_t input_vec_matrix, float *vecdata,float lernrate, float discount_factor,struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER],
struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER], struct uz_mtwister_config cfg, 
uint32_t number_of_layer,
 struct uz_dqn_experience_replay_config buffer_config,
uint32_t length_of_buffer, uint32_t headind)
{
    uz_dqn_t *self = uz_dqn_allocation();
    self->inputvecnn = uz_matrix_init(&input_vec_matrix, vecdata, config_critic->number_of_inputs, 1, config_critic->number_of_inputs);
    self->randinstance = init_mtwister(cfg); 
    self->critic = uz_nn_init_with_rand(config_critic, number_of_layer, self->randinstance ,true);
    self->critic_target_net = uz_nn_init(config_target, number_of_layer, false);
    self->experience_buffer = uz_dqn_experience_replay_init(buffer_config,length_of_buffer,headind);
    self->discount_factor = discount_factor;
    self->lernrate = lernrate;
    return (self);
}

uint32_t uz_dqn_get_action(uz_dqn_t* self,uz_matrix_t * input,float *epsilon_start,float *epsilon_min,float *epsilon_decay, uint32_t number_of_actions){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uint32_t action;
    //calc epsilon
    float epsilon = calc_epsilon_greedy(*epsilon_start, *epsilon_min, *epsilon_decay);
    //generate random number
    MTRand seed = seedRand(12);
    float n = (float)genRand(&seed);
    if (n < epsilon){
    action = (uint32_t)(genRand(&seed) * number_of_actions);
    }
    else{
    uz_nn_ff(self->critic,input);
    action = uz_matrix_get_max_index(uz_nn_get_output_data(self->critic));
    }
    return action;
}

void uz_dqn_sample(uz_dqn_t *self, float samplerate, bool penalty, uz_matrix_t *input)
{
    uz_nn_ff(self->critic,input);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(self->critic);
    float qvalue = uz_matrix_get_max_value(outputdqn);
    uint32_t action = uz_matrix_get_max_index(outputdqn);
    float reward = calculate_reward_dqn(samplerate,input,penalty);
    uz_dqn_push_to_buffer(self->experience_buffer,&reward,&qvalue,&action,input);
}

void uz_dqn_sample_bitenv(uz_dqn_t *self,uz_dqn_environment_t *env)
{
    uint32_t actionind;
    for (uint32_t i = 0; i < env->max_steps; i++)
    {
    env->epsilon_start = calc_epsilon_greedy(env->epsilon_start,env->epsilon_min,env->epsilon_decay);
    // randnumber and epsilon comparision
    if(genRand_float(&self->randinstance->seedRand)<env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,env->bitlength-1);
    }
    else{
    uz_nn_ff(self->critic,env->inputfornn);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(self->critic);
    actionind = uz_matrix_get_max_index(outputdqn);
    }
    uz_dqn_bitflip_action(env,actionind);
    // input for nn muss festgelegt werden und in einer uz_matrix gespeichert werden
    uz_nn_ff(self->critic,env->inputfornn);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(self->critic);
    float qvalue = uz_matrix_get_max_value(outputdqn);
    float reward = calculate_reward_bit(env);
    uz_dqn_push_to_buffer(self->experience_buffer,&reward,&qvalue,&actionind,env->inputfornn);
    if (arraysequal(env->bitinitial,env->bittarget,env->bitlength) == true){
    printf("Bitmuster gleich nach %d Schritten.\n",i);
    return;
    }
    } 
}

float uz_dqn_train(uz_dqn_t *self, float *rew, float *qval, uint32_t *act, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t mbsize, uint32_t numobs, uint32_t *indices,
uz_matrix_t *X, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t NUMBER_OF_EPOCHS, float targsmoothfact)
{
float qplus1 = 0.0f;
bool terminal = false;
float loss = 0.0f;
float dloss = 0.0f;
uz_matrix_t* outputtarget;
    for(uint32_t j=0; j<mbsize;j++){
        uz_dqn_get_minibatch_from_buffer(self->experience_buffer,rew,qval,act,obs,self->experience_buffer->vectorforobs,obspl1,mbsize,numobs,indices);
        uz_matrix_get_row_vector_zero_based(obspl1,X,j);
        uz_nn_ff(self->critic_target_net,X);
        outputtarget=uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        loss = calculate_loss_dqn(self,*rew,*qval,qplus1,terminal);
        dloss = calculate_derv_loss_dqn(self,*rew,*qval,qplus1,terminal);
        uz_nn_backward_pass_mini_batch(self->critic,&dloss,X);  
    }
    uz_nn_gradient_descent_mini_batch(self->critic,self->lernrate,mbsize);
    uz_nn_set_gradients_zero(self->critic);
    // Targetupdate 
    if (TARGET_UPDATE_FREQUENCY % NUMBER_OF_EPOCHS == 0){
    uz_nn_target_update(self->critic,self->critic_target_net,periodic_smoothing, &targsmoothfact);
    }
// printf("dLoss %.3f \n",(double)dloss);
printf("Loss %.3f \n",(double)loss);
return loss;
}
//pseudocode set current

// void uz_dqn_set_current(uz_dqn_t* self, uint32_t action, void *data, float action_current)
// uz_assert_not_NULL(self);
// uz_assert(self->is_ready);	            
// switch (action){
//     case 0: data->rasv.dq_reference_current.q =action_current;
//     break;
//     case 1:	Global_Data.rasv.dq_reference_current.q=action_current/2.0f;
//     break;
//     case 2: Global_Data.rasv.dq_reference_current.q=0.0f;
//     break;
//     case 3:	Global_Data.rasv.dq_reference_current.q=-action_current/2.0f;
//     break;
//     case 4: Global_Data.rasv.dq_reference_current.q=-action_current;
//     break;
//     default: uz_assert(0);
// }

void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->head = 0U;
    resetFloatArray(self->reward,self->length);
    resetFloatArray(self->qvalues,self->length);
    resetintArray(self->action,self->length);
    uz_matrix_set_zero(self->observations);
}

void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *qdata,uint32_t *actionindex, uz_matrix_t *obsdata){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(rewarddata);
    uz_assert_not_NULL(actionindex);
    uz_assert_not_NULL(qdata);
    uz_assert_not_NULL(obsdata);
    uz_assert(self->is_ready);
    self->is_full = false;
    // check first if counter is full, set counter to zero again and write then, set is_full true
    if(self->head==(self->length)){
      self->is_full = true;
      self->head=0U;
      self->counterisfull++;
    }
    self->reward[self->head]= *rewarddata;
    self->action[self->head] = *actionindex;
    self->qvalues[self->head] = *qdata;
    uz_matrix_copy_row_to_matrix(obsdata,self->observations,self->head);
    self->head++;
}

void uz_dqn_get_minibatch_from_buffer(uz_dqn_experience_replay_t* self,float *reward,float *qvalue, uint32_t *actionindex, uz_matrix_t *obs,uz_matrix_t *obsvec, uz_matrix_t *obspl1,uint32_t minibatchsize,uint32_t numberofobs,  uint32_t *indizes)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(reward);
    uz_assert_not_NULL(actionindex);
    uz_assert_not_NULL(obs);
    uz_assert_not_NULL(indizes);
    uz_assert(self->is_ready);
    uint32_t indexpl = 0;
    for (uint32_t i = 0; i < minibatchsize; i++)
    {
    uint32_t index = indizes[i];
    // logik implementieren, dass plus1 immer richtig aus dem buffer kommt
    if (self->counterisfull == 0){
        if(index==self->head){
            index = self->head -1;
        }
    }
    // wenn buffer voll muss als index+1 der index 0 gesampelt werden
    if (index==(self->length-1)){
        indexpl = 0;
    }
    else{
        indexpl = index + 1;
    }
        uz_dqn_get_from_buffer(self,reward,qvalue,actionindex,obsvec,index);
        uz_matrix_copy_row_to_matrix(obsvec,obs,i);
        uz_dqn_get_obs_from_buffer(self,obsvec,indexpl);
        uz_matrix_copy_row_to_matrix(obsvec,obspl1,i);
        reward++;
        actionindex++;
        qvalue++;
    }
}


float calculate_loss_dqn(uz_dqn_t* self, float reward, float qval, float qvalplus1, bool terminal){
    uz_assert_not_NULL(self);
    // berechne y_j
    float y_j = 0.0f;
    if(terminal==true)
    {
        y_j = reward;
    }
    else{
        // berechne max_aQ(psi,a',theta)
        // sollte man sowohl die Aktion, als auch den index speichern? 
        // im nn object ist nur der index, nicht der Aktionswert,
        // deshalb bringt ja der reine index hier nichts als aktion, schlauer wäre es
        // float action und uint action zu speichern, dass man beides hat
        // und evtl obs+1 und action(obs+1)
        // uz_matrix_t* output_nn = uz_nn_get_output_data(self->critic);
		// uint32_t action = uz_matrix_get_max_index(obs); // index
        y_j = reward + (self->discount_factor * qvalplus1);
    }
    // uz_matrix_t* output_nn = uz_nn_get_output_data(self->critic);
    float loss = ((y_j - qval) * (y_j - qval));
    return loss;
}

float calculate_derv_loss_dqn(uz_dqn_t* self, float reward, float qval, float qvalplus1, bool terminal){
    uz_assert_not_NULL(self);
    // berechne y_j
    float y_j = 0.0f;
    if(terminal==true)
    {
        y_j = reward;
    }
    else{
        y_j = reward + (self->discount_factor * qvalplus1);
    }
    float loss = -2.0f*(y_j - qval);
    return loss;
}
void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *QValue, uint32_t *actiondata, uz_matrix_t *obsdata, uint32_t index){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(rewarddata);
    uz_assert_not_NULL(actiondata);
    uz_assert_not_NULL(obsdata);
    uz_assert(self->is_ready);
    uz_assert(index<self->length); // assert, wenn index größer als die länge des buffers
    *rewarddata = self->reward[index];
    *QValue = self->qvalues[index];
    *actiondata = self->action[index];
    uz_matrix_copy_row_from_matrix(self->observations,obsdata,index);
}
void uz_dqn_get_obs_from_buffer(uz_dqn_experience_replay_t* self,uz_matrix_t *obsdata, uint32_t index){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(obsdata);
    uz_assert(self->is_ready);
    uz_assert(index<self->length); // assert, wenn index größer als die länge des buffers
    uz_matrix_copy_row_from_matrix(self->observations,obsdata,index);
}

void uz_dqn_get_q_value_from_buffer(uz_dqn_experience_replay_t* self,float *QValue, uint32_t index){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(QValue);
    uz_assert(self->is_ready);
    uz_assert(index<self->length); // assert, wenn index größer als die länge des buffers
    *QValue = self->qvalues[index];
}
float calculate_reward_dqn(float samplerate, uz_matrix_t *observations, bool penalty)
{
    //hardcoded defines for the reward
    float pos_max = 0.35f;
    // check, ob penalty nötig
    float z = 0.0f;
    if (penalty == true)
    {
        z = -1000.0f;
    }
    float r = -2.0f * samplerate * (100.0f * asinf(fabsf(observations->data[0])/(2.0f * (float)M_PI)) + fabsf(observations->data[3]/pos_max)  + (0.25f * (observations->data[4] *observations->data[4]))) + z;
    return r;
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

float calc_epsilon_greedy(float epsilon_start, float epsilon_min, float epsilon_decay)
{
uz_assert(epsilon_start<1.0f);
uz_assert(epsilon_decay<1.0f);
uz_assert(epsilon_start>0.0f);
uz_assert(epsilon_decay>0.0f);
uz_assert(epsilon_start>=epsilon_min);
float epsilon = epsilon_start;
epsilon = epsilon*(1.0f-epsilon_decay);
if (epsilon < epsilon_min)
{
epsilon = epsilon_min;
}
return epsilon;
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