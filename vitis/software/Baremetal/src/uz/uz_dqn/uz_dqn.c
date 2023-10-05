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

uz_dqn_experience_replay_t *uz_dqn_experience_replay_init(struct uz_dqn_experience_replay_config buf_config, uint32_t length){
    uz_assert_not_NULL(buf_config.reward);
    uz_assert_not_NULL(buf_config.actions);
    uz_assert_not_NULL(buf_config.observations);
    uz_assert_not_NULL(buf_config.obsvec);
    uz_assert_not_NULL(buf_config.qvalues);
    uz_assert_not_NULL(buf_config.observations1);
    uz_assert_not_NULL(buf_config.obsvec1);
    uz_dqn_experience_replay_t *self = uz_dqn_experience_replay_allocation();
    self->length = length;
    self->reward = buf_config.reward;
    self->qvalues = buf_config.qvalues;
    self->action = buf_config.actions;
    self->vectorforobs= uz_matrix_init(&self->vecobs_matrix,buf_config.obsvec,buf_config.columns_of_observations,1,buf_config.columns_of_observations);
    self->vectorforobs1= uz_matrix_init(&self->vecobs_matrix1,buf_config.obsvec1,buf_config.columns_of_observations,1,buf_config.columns_of_observations);
    self->observations = uz_matrix_init(&self->observations_matrix,buf_config.observations,buf_config.length_of_buffer * buf_config.columns_of_observations,buf_config.length_of_buffer,buf_config.columns_of_observations);
    self->observations1 = uz_matrix_init(&self->observations_matrix_1,buf_config.observations1,buf_config.length_of_buffer * buf_config.columns_of_observations,buf_config.length_of_buffer,buf_config.columns_of_observations);
    self->head = 0;// steht immer auf 0 bei der init
    self->counterisfull = 0;
    return (self);
}


uz_dqn_t *uz_dqn_init(float *vecdata,float lernrate, float discount_factor,struct uz_nn_layer_config config_critic[UZ_NN_MAX_LAYER],
struct uz_nn_layer_config config_target[UZ_NN_MAX_LAYER], struct uz_mtwister_config cfg, 
uint32_t number_of_layer,
 struct uz_dqn_experience_replay_config buffer_config,
uint32_t length_of_buffer, struct uz_dqn_environment_config envconf)
{
    uz_assert_not_NULL(vecdata);
    uz_dqn_t *self = uz_dqn_allocation();
    self->inputvecnn = uz_matrix_init(&self->inputvecnn_matrix, vecdata, config_critic->number_of_inputs, 1, config_critic->number_of_inputs);
    self->randinstance = init_mtwister(cfg); 
    self->critic = uz_nn_init_with_rand(config_critic, number_of_layer, self->randinstance ,true);
    self->critic_target_net = uz_nn_init(config_target, number_of_layer, false);
    self->experience_buffer = uz_dqn_experience_replay_init(buffer_config,length_of_buffer);
    self->discount_factor = discount_factor;
    self->lernrate = lernrate;
    self->env = uz_dqn_environment_init(envconf);
    return (self);
}

uint32_t uz_dqn_get_action(uz_dqn_t* self,uz_matrix_t *input,float *epsilon_start,float *epsilon_min,float *epsilon_decay, uint32_t number_of_actions){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(input);
    uz_assert_not_NULL(epsilon_start);
    uz_assert_not_NULL(epsilon_min);
    uz_assert_not_NULL(epsilon_decay);
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

void uz_dqn_act_bitenv_no_exploration(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    uint32_t actionind;
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
    uz_nn_ff(self->critic_target_net,self->env->inputfornn);
    uz_matrix_t* outputaction=uz_nn_get_output_data(self->critic_target_net);
    actionind = uz_matrix_get_max_index(outputaction);
    uz_dqn_bitflip_action(self->env,actionind);
    float reward = calculate_reward_bit(self->env);
    self->env->cumreward+= reward;
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    //printf("Bitmuster gleich nach %d Schritten.\n",i);
    return;
    }  
    }

}

void uz_dqn_simple_reset(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    for (uint32_t i = 0; i < self->critic->number_of_inputs; i++)
    {
    self->inputvecnn->data[i] = genRand_float(&self->randinstance->seedRand);
    }
}

void uz_dqn_sample_simple(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    uint32_t action;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
    uz_matrix_copy(self->inputvecnn,self->env->inputfornn);
    uz_nn_ff(self->critic,self->inputvecnn);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(self->critic);
    // randnumber and epsilon comparision
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        action = genRand_uint32_t(&self->randinstance->seedRand,self->critic->number_of_outputs-1);
    }
    else{
    action = uz_matrix_get_max_index(outputdqn);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputdqn,0,action);
    //uz_dqn_simple_action(self->env,actionind);
    float reward = calculate_reward_simple(action);
    uz_dqn_push_to_buffer(self->experience_buffer,&reward,&qvalue,&action,self->env->inputfornn,self->env->inputfornn);
    self->env->cumreward= reward;
    } 
}

float uz_dqn_step_adam_simple(uz_dqn_t *self,float *error,uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t *r, adam_optimizer_t *adam){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    uz_matrix_t* outputcritic;
    uz_matrix_t* outputtarget;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
    uz_matrix_copy(self->inputvecnn,self->env->inputfornn);
    uz_nn_ff(self->critic,self->inputvecnn);
    outputcritic = uz_nn_get_output_data(self->critic);
    // randnumber and epsilon comparision
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,self->critic->number_of_outputs-1);
    }
    else{
    actionind = uz_matrix_get_max_index(outputcritic);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputcritic,0,actionind);
    float stepreward = calculate_reward_simple(actionind);
    uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->inputvecnn,self->env->inputfornn);
    self->env->cumreward= stepreward;
    if (self->experience_buffer->counterisfull > 0U){
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)self->experience_buffer->length-1);
    }
    else{
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)self->experience_buffer->head-1);
    }
    uint32_t *rx;
    rx = r;
    for(uint32_t j=0; j<mbsize;j++){
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1,self->env->inputfornn,*rx);
        uz_nn_ff(self->critic_target_net,self->env->inputfornn);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        float rewardtrain = self->experience_buffer->reward[*rx];
        uint32_t actiontrain = self->experience_buffer->action[*rx];
        float qvaltrain = self->experience_buffer->qvalues[*rx];
        if (rewardtrain==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        loss = calculate_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        dloss = calculate_derv_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        error[actiontrain] = dloss; 
        cum_loss += loss; 
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations,self->inputvecnn,*rx);
        uz_nn_backward_pass_mini_batch(self->critic,error,self->inputvecnn);  
        resetFloatArray(error,self->critic->number_of_outputs);  
        rx++; 
    }
    cum_loss = cum_loss/(float)mbsize;
    adam_optimizer_step(adam,self->critic);
    uz_nn_set_gradients_zero(self->critic);
    }
    if (epoch % TARGET_UPDATE_FREQUENCY == 0){
        uz_nn_target_update(self->critic,self->critic_target_net,periodic, &targsmoothfact);
    }
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    return cum_loss;
    }
    return cum_loss;
} 

float uz_dqn_step_adam_simple_no_array(uz_dqn_t *self,float *error,uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, adam_optimizer_t *adam){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    uz_matrix_t* outputcritic;
    uz_matrix_t* outputtarget;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
    uz_matrix_copy(self->inputvecnn,self->env->inputfornn);
    uz_nn_ff(self->critic,self->inputvecnn);
    outputcritic = uz_nn_get_output_data(self->critic);
    // randnumber and epsilon comparision
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,self->critic->number_of_outputs-1);
    }
    else{
    actionind = uz_matrix_get_max_index(outputcritic);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputcritic,0,actionind);
    float stepreward = calculate_reward_simple(actionind);
    uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->inputvecnn,self->env->inputfornn);
    self->env->cumreward= stepreward;
    for(uint32_t j=0; j<mbsize;j++){
        uint32_t randomindex = 0U;
        if (self->experience_buffer->counterisfull > 0U){
        randomindex = genRand_uint32_t(&self->randinstance->seedRand,self->experience_buffer->length-1);
        }
        else{
        randomindex = genRand_uint32_t(&self->randinstance->seedRand,self->experience_buffer->head-1);
        }
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1,self->env->inputfornn,randomindex);
        uz_nn_ff(self->critic_target_net,self->env->inputfornn);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        float rewardtrain = self->experience_buffer->reward[randomindex];
        uint32_t actiontrain = self->experience_buffer->action[randomindex];
        float qvaltrain = self->experience_buffer->qvalues[randomindex];
        if (rewardtrain==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        loss = calculate_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        dloss = calculate_derv_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        error[actiontrain] = dloss; 
        cum_loss += loss; 
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations,self->inputvecnn,randomindex);
        uz_nn_backward_pass_mini_batch(self->critic,error,self->inputvecnn);  
        resetFloatArray(error,self->critic->number_of_outputs);  
    }
    cum_loss = cum_loss/(float)mbsize;
    adam_optimizer_step(adam,self->critic);
    uz_nn_set_gradients_zero(self->critic);
    }
    if (epoch % TARGET_UPDATE_FREQUENCY == 0){
        uz_nn_target_update(self->critic,self->critic_target_net,periodic, &targsmoothfact);
    }
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    return cum_loss;
    }
    return cum_loss;
} 
float uz_dqn_step_gd_simple(uz_dqn_t *self,float *error,uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t *r){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    uz_matrix_t* outputcritic;
    uz_matrix_t* outputtarget;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
    uz_matrix_copy(self->inputvecnn,self->env->inputfornn);
    uz_nn_ff(self->critic,self->inputvecnn);
    outputcritic=uz_nn_get_output_data(self->critic);
    // randnumber and epsilon comparision
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,self->critic->number_of_outputs-1);
    }
    else{
    actionind = uz_matrix_get_max_index(outputcritic);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputcritic,0,actionind);
    float stepreward = calculate_reward_simple(actionind);

    uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->env->inputfornn,self->env->inputfornn);
    self->env->cumreward= stepreward;
    if (self->experience_buffer->counterisfull > 0U){
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)self->experience_buffer->length-1);
    }
    else{
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)self->experience_buffer->head-1);
    }
    uint32_t *rx;
    rx = r;
    for(uint32_t j=0; j<mbsize;j++){
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1,self->env->inputfornn,*rx);
        uz_nn_ff(self->critic_target_net,self->env->inputfornn);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        float rewardtrain = self->experience_buffer->reward[*rx];
        uint32_t actiontrain = self->experience_buffer->action[*rx];
        float qvaltrain = self->experience_buffer->qvalues[*rx];
        if (rewardtrain==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        loss = calculate_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        dloss = calculate_derv_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        error[actiontrain] = dloss; 
        cum_loss += loss; 
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations,self->inputvecnn,*rx);
        uz_nn_backward_pass_mini_batch(self->critic,error,self->inputvecnn);  
        resetFloatArray(error,self->critic->number_of_outputs);  
        rx++; 
    }
    cum_loss = cum_loss/(float)mbsize;
    uz_nn_gradient_descent_mini_batch(self->critic,self->lernrate,mbsize);
    uz_nn_set_gradients_zero(self->critic);
    }
    if (epoch % TARGET_UPDATE_FREQUENCY == 0){
    uz_nn_target_update(self->critic,self->critic_target_net,smoothing, &targsmoothfact);
    }
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    return cum_loss;
    }
    return cum_loss;
} 

float uz_dqn_step_adam(uz_dqn_t *self,float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t *r, adam_optimizer_t *adam){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uz_assert_not_NULL(r);
    uz_matrix_t* outputcritic;
    uz_matrix_t* outputtarget;
    uint32_t actionind;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    for (uint32_t t = 0; t < self->env->max_steps; t++)
    {
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    uz_matrix_copy(self->env->inputfornn,self->experience_buffer->vectorforobs);
    uz_nn_ff(self->critic,self->env->inputfornn);
    outputcritic=uz_nn_get_output_data(self->critic);
    // randnumber and epsilon comparision
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,self->env->bitlength-1);
    }
    else{
    actionind = uz_matrix_get_max_index(outputcritic);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputcritic,0,actionind);
    uz_dqn_bitflip_action(self->env,actionind);
    float stepreward = calculate_reward_bit(self->env);
    uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->experience_buffer->vectorforobs,self->env->inputfornn);
    self->env->cumreward+= stepreward;
    if (self->experience_buffer->counterisfull > 0U){
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)self->experience_buffer->length-1);
    }
    else{
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)self->experience_buffer->head-1);
    }
    uint32_t *rx;
    rx = r;
    // uz_dqn_get_minibatch_from_buffer(self->experience_buffer,rew,qval,act,self->experience_buffer->vectorforobs,self->experience_buffer->vectorforobs1,obs,obspl1,mbsize,r);
    for(uint32_t j=0; j<mbsize;j++){
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1,self->experience_buffer->vectorforobs1,*rx);
        uz_nn_ff(self->critic_target_net,self->experience_buffer->vectorforobs1);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        float rewardtrain = self->experience_buffer->reward[*rx];
        uint32_t actiontrain = self->experience_buffer->action[*rx];
        float qvaltrain = self->experience_buffer->qvalues[*rx];
        if (rewardtrain==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        loss = calculate_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        dloss = calculate_derv_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        error[actiontrain] = dloss; 
        cum_loss += loss; 
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations,self->experience_buffer->vectorforobs,*rx);
        uz_nn_backward_pass_mini_batch(self->critic,error,self->experience_buffer->vectorforobs);  
        rx++;
        resetFloatArray(error,self->critic->number_of_outputs);   
    }
    cum_loss = cum_loss/(float)mbsize;
    adam_optimizer_step(adam,self->critic);
    uz_nn_set_gradients_zero(self->critic);
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    return cum_loss;
    }
    }
    if (epoch % TARGET_UPDATE_FREQUENCY == 0){
    uz_nn_target_update(self->critic,self->critic_target_net,smoothing, &targsmoothfact);
    }
    return cum_loss;
} 


float uz_dqn_step_adam_no_array(uz_dqn_t *self,float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, adam_optimizer_t *adam){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    uz_matrix_t* outputcritic;
    uz_matrix_t* outputtarget;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    uint32_t randomindex = 0U;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    for (uint32_t t = 0; t < self->env->max_steps; t++)
    {
    uz_matrix_copy(self->env->inputfornn,self->experience_buffer->vectorforobs);
    uz_nn_ff(self->critic,self->env->inputfornn);
    outputcritic=uz_nn_get_output_data(self->critic);
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,self->env->bitlength-1);
    }
    else{
    actionind = uz_matrix_get_max_index(outputcritic);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputcritic,0,actionind);
    uz_dqn_bitflip_action(self->env,actionind);
    float stepreward = calculate_reward_bit(self->env);
    uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->experience_buffer->vectorforobs,self->env->inputfornn);
    self->env->cumreward+= stepreward;
    for(uint32_t j=0; j<mbsize;j++){

        if (self->experience_buffer->counterisfull > 0U){
        randomindex = genRand_uint32_t(&self->randinstance->seedRand,self->experience_buffer->length-1);
        }
        else{
        randomindex = genRand_uint32_t(&self->randinstance->seedRand,self->experience_buffer->head-1);
        }
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1,self->experience_buffer->vectorforobs1,randomindex);
        uz_nn_ff(self->critic_target_net,self->experience_buffer->vectorforobs1);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        float rewardtrain = self->experience_buffer->reward[randomindex];
        uint32_t actiontrain = self->experience_buffer->action[randomindex];
        //float qvaltrain = self->experience_buffer->qvalues[randomindex];
        if (rewardtrain==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations,self->experience_buffer->vectorforobs,randomindex);
        uz_nn_ff(self->critic,self->experience_buffer->vectorforobs);
        outputcritic = uz_nn_get_output_data(self->critic);
        float qvaltrain = uz_matrix_get_element_zero_based(outputcritic,0,actiontrain);
        loss = calculate_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        dloss = calculate_derv_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        error[actiontrain] += dloss; 
        cum_loss += loss; 
        uz_nn_backward_pass_mini_batch(self->critic,error,self->experience_buffer->vectorforobs);  
        resetFloatArray(error,self->critic->number_of_outputs);   
    }
    cum_loss = cum_loss/(float)mbsize;
    adam_optimizer_step(adam,self->critic);
    uz_nn_set_gradients_zero(self->critic);
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    return cum_loss;
    }
    }
    if (epoch % TARGET_UPDATE_FREQUENCY == 0){
    uz_nn_target_update(self->critic,self->critic_target_net,smoothing, &targsmoothfact);
    }
    return cum_loss;
} 


float uz_dqn_step_gd(uz_dqn_t *self,float *error, uint32_t mbsize,uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, uint32_t bufferlength, uint32_t *r){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uint32_t actionind;
    uz_matrix_t* outputtarget;
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    for (uint32_t t = 0; t < self->env->max_steps; t++)
    {
    uz_matrix_copy(self->env->inputfornn,self->inputvecnn);
    uz_nn_ff(self->critic,self->env->inputfornn);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(self->critic);
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,self->env->bitlength-1);
    }
    else{
    actionind = uz_matrix_get_max_index(outputdqn);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputdqn,0,actionind);
    uz_dqn_bitflip_action(self->env,actionind);
    float stepreward = calculate_reward_bit(self->env);
    uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->inputvecnn,self->env->inputfornn);
    self->env->cumreward+= stepreward;
    if (self->experience_buffer->counterisfull > 0U){
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)bufferlength-1);
    }
    else{
    genRand_uint32_t_array(r,&self->randinstance->seedRand,mbsize,0.0f,(float)self->experience_buffer->head-1);
    }
    uint32_t *rx;
    rx = r;
    // uz_dqn_get_minibatch_from_buffer(self->experience_buffer,rew,qval,act,self->experience_buffer->vectorforobs,self->experience_buffer->vectorforobs1,obs,obspl1,mbsize,r);
    for(uint32_t j=0; j<mbsize;j++){
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1,self->env->inputfornn,*rx);
        uz_nn_ff(self->critic_target_net,self->env->inputfornn);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        float rewardtrain = self->experience_buffer->reward[*rx];
        uint32_t actiontrain = self->experience_buffer->action[*rx];
        float qvaltrain = self->experience_buffer->qvalues[*rx];
        if (rewardtrain==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        loss = calculate_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        dloss = calculate_derv_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
        error[actiontrain] = dloss; 
        cum_loss += loss; 
        uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations,self->inputvecnn,*rx);
        uz_nn_backward_pass_mini_batch(self->critic,error,self->inputvecnn);  
        rx++;
        resetFloatArray(error,self->critic->number_of_outputs);   
    }
    cum_loss = cum_loss/(float)mbsize;
    uz_nn_gradient_descent_mini_batch(self->critic,self->lernrate,mbsize);
    uz_nn_set_gradients_zero(self->critic);
    }
    // Targetupdate 
    if (epoch % TARGET_UPDATE_FREQUENCY == 0){
    uz_nn_target_update(self->critic,self->critic_target_net,periodic, &targsmoothfact);
    }
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    return cum_loss;
    }
    return cum_loss;
} 

void uz_dqn_sample_bitenv(uz_dqn_t *self)
{
    uz_assert_not_NULL(self);
    uint32_t actionind;
    self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
    for (uint32_t i = 0; i < self->env->max_steps; i++)
    {
    uz_matrix_copy(self->env->inputfornn,self->inputvecnn);
    uz_nn_ff(self->critic,self->env->inputfornn);
    uz_matrix_t* outputdqn=uz_nn_get_output_data(self->critic);
    // randnumber and epsilon comparision
    if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
        actionind = genRand_uint32_t(&self->randinstance->seedRand,self->env->bitlength-1);
    }
    else{
    actionind = uz_matrix_get_max_index(outputdqn);
    }
    float qvalue = uz_matrix_get_element_zero_based(outputdqn,0,actionind);
    uz_dqn_bitflip_action(self->env,actionind);
    float stepreward = calculate_reward_bit(self->env);
    uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->inputvecnn,self->env->inputfornn);
    self->env->cumreward+= stepreward;
    if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
    // printf("Bitmuster gleich nach %d Schritten.\n",i);
    return;
    }
    } 
}


float uz_dqn_train(uz_dqn_t *self,float *error, float *rew, float *qval, uint32_t *act, uz_matrix_t *obs, uz_matrix_t *obspl1, uint32_t mbsize,
uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(error);
    uz_assert_not_NULL(rew);
    uz_assert_not_NULL(qval);
    uz_assert_not_NULL(obs);
    uz_assert_not_NULL(obspl1);
    float qplus1 = 0.0f;
    bool terminal = false;
    float loss = 0.0f;
    float cum_loss = 0.0f;
    float dloss = 0.0f;
    uz_matrix_t* outputtarget;
    for(uint32_t j=0; j<mbsize;j++){
        uz_matrix_get_row_vector_zero_based(obspl1,self->env->inputfornn,j);
        uz_nn_ff(self->critic_target_net,self->env->inputfornn);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        // uz_matrix_get_row_vector_zero_based(obs,self->inputvecnn,j);
        // uz_nn_ff(self->critic,self->inputvecnn);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        if (*rew==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        loss = calculate_loss_dqn(self,*rew,*qval,qplus1,terminal);
        // hier andere berechnung einfügen für dloss sollte ein array entstehen
        dloss = calculate_derv_loss_dqn(self,*rew,*qval,qplus1,terminal);
        error[*act] = dloss; 
        cum_loss += loss; 
        uz_matrix_get_row_vector_zero_based(obs,self->inputvecnn,j);
        uz_nn_backward_pass_mini_batch(self->critic,error,self->inputvecnn);  
        rew++;
        qval++;
        act++;
        resetFloatArray(error,self->critic->number_of_outputs);   
    }
    cum_loss = cum_loss/(float)mbsize;
    uz_nn_gradient_descent_mini_batch(self->critic,self->lernrate,mbsize);
    uz_nn_set_gradients_zero(self->critic);
    // Targetupdate 
    if (epoch % TARGET_UPDATE_FREQUENCY  == 0){
    uz_nn_target_update(self->critic,self->critic_target_net,periodic, &targsmoothfact);
    }
return cum_loss;
}

float uz_dqn_train4(uz_dqn_t *self,float *error, float *rew, float *qval, uint32_t *act,uz_matrix_t *obs,  uz_matrix_t *obspl1, uint32_t mbsize,
uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, adam_optimizer_t *adam)
{
uz_assert_not_NULL(self);
uz_assert_not_NULL(error);
uz_assert_not_NULL(rew);
uz_assert_not_NULL(qval);
uz_assert_not_NULL(obs);
uz_assert_not_NULL(obspl1);
float qplus1 = 0.0f;
bool terminal = false;
float loss = 0.0f;
float cum_loss = 0.0f;
float dloss = 0.0f;
uz_matrix_t* outputtarget;
for(uint32_t j=0; j<mbsize;j++){
        uz_matrix_get_row_vector_zero_based(obspl1,self->env->inputfornn,j);
        uz_nn_ff(self->critic_target_net,self->env->inputfornn);
        outputtarget = uz_nn_get_output_data(self->critic_target_net);
        qplus1 = uz_matrix_get_max_value(outputtarget);
        if (*rew==0.0f)
        {
            terminal = true;
        }
        else{
            terminal = false;
        }
        loss = calculate_loss_dqn(self,*rew,*qval,qplus1,terminal);
        // hier andere berechnung einfügen für dloss sollte ein array entstehen
        dloss = calculate_derv_loss_dqn(self,*rew,*qval,qplus1,terminal);
        error[*act] = dloss; 
        cum_loss += loss; 
        uz_matrix_get_row_vector_zero_based(obs,self->inputvecnn,j);
        uz_nn_backward_pass_mini_batch(self->critic,error,self->inputvecnn);  
        rew++;
        qval++;
        act++;
        resetFloatArray(error,self->critic->number_of_outputs);   
    }
    cum_loss = cum_loss/(float)mbsize;
    adam_optimizer_step(adam,self->critic);
    uz_nn_set_gradients_zero(self->critic);
    // Targetupdate 
    if (epoch % TARGET_UPDATE_FREQUENCY  == 0){
    uz_nn_target_update(self->critic,self->critic_target_net,smoothing, &targsmoothfact);
    }
return cum_loss;
}

void uz_dqn_reset_buffer(uz_dqn_experience_replay_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->head = 0U;
    resetFloatArray(self->reward,self->length);
    resetFloatArray(self->qvalues,self->length);
    resetuintArray(self->action,self->length);
    uz_matrix_set_zero(self->observations);
    uz_matrix_set_zero(self->observations1);
    uz_matrix_set_zero(self->vectorforobs);
    uz_matrix_set_zero(self->vectorforobs1);
}

void uz_dqn_push_to_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *qdata,uint32_t *actionindex, uz_matrix_t *obsdata,uz_matrix_t *obsdata1){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(rewarddata);
    uz_assert_not_NULL(actionindex);
    uz_assert_not_NULL(qdata);
    uz_assert_not_NULL(obsdata);
    uz_assert_not_NULL(obsdata1);
    uz_assert(self->is_ready);
    self->is_full = false;
    if(self->head==(self->length)){
      self->is_full = true;
      self->head=0U;
      self->counterisfull++;
    }
    self->reward[self->head]= *rewarddata;
    self->action[self->head] = *actionindex;
    self->qvalues[self->head] = *qdata;
    uz_matrix_copy_row_to_matrix(obsdata,self->observations,self->head);
    uz_matrix_copy_row_to_matrix(obsdata1,self->observations1,self->head);
    self->head++;
}

void uz_dqn_get_minibatch_from_buffer(uz_dqn_experience_replay_t* self,float *reward,float *qvalue, uint32_t *actionindex,uz_matrix_t *obsvec,uz_matrix_t *obsvec1,uz_matrix_t *obs, uz_matrix_t *obspl1,uint32_t minibatchsize, uint32_t *indizes)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(reward);
    uz_assert_not_NULL(actionindex);
    uz_assert_not_NULL(obsvec);
    uz_assert_not_NULL(obsvec1);
    uz_assert_not_NULL(obspl1);
    uz_assert_not_NULL(obs);
    uz_assert_not_NULL(indizes);
    uz_assert(self->is_ready);
    for (uint32_t i = 0; i < minibatchsize; i++)
    {
    uint32_t index = indizes[i];
    if (self->counterisfull == 0){
        if(index>=self->head){
            index = self->head;
        }
    }
        uz_dqn_get_from_buffer(self,reward,qvalue,actionindex,obsvec,obsvec1,index);
        uz_matrix_copy_row_to_matrix(obsvec,obs,i);
        uz_matrix_copy_row_to_matrix(obsvec1,obspl1,i);
        reward++;
        actionindex++;
        qvalue++;
    }
}

float calculate_loss_dqn(uz_dqn_t* self, float samplereward, float qval, float qvalplus1, bool terminal){
    uz_assert_not_NULL(self);
    // berechne y_j
    float y_j = 0.0f;
    if(terminal==true)
    {
        y_j = samplereward;
    }
    else{
        y_j = samplereward + (self->discount_factor * qvalplus1);
    }
    float loss = ((y_j - qval) * (y_j - qval));
    return loss;
}

float calculate_derv_loss_dqn(uz_dqn_t* self, float samplereward, float qval, float qvalplus1, bool terminal){
    uz_assert_not_NULL(self);
    float y_j = 0.0f;
    if(terminal==true)
    {
        y_j = samplereward;
    }
    else{
        y_j = samplereward + (self->discount_factor * qvalplus1);
    }
    float dloss = -2.0f*(y_j - qval);

    if (dloss > 1.0f){
        dloss = 1.0f;
    }
    if(dloss < -1.0f){
        dloss = -1.0f;
    }
    return dloss;
}

void uz_dqn_get_from_buffer(uz_dqn_experience_replay_t* self,float *rewarddata,float *QValue, uint32_t *actiondata, uz_matrix_t *obsdata,uz_matrix_t *obsdata1, uint32_t index)
{
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(rewarddata);
    uz_assert_not_NULL(QValue);
    uz_assert_not_NULL(actiondata);
    uz_assert_not_NULL(obsdata);
    uz_assert_not_NULL(obsdata1);
    uz_assert(self->is_ready);
    uz_assert(index<self->length);
    *rewarddata = self->reward[index];
    *QValue = self->qvalues[index];
    *actiondata = self->action[index];
    uz_matrix_copy_row_from_matrix(self->observations,obsdata,index);
    uz_matrix_copy_row_from_matrix(self->observations1,obsdata1,index);
}

void uz_dqn_get_obs_from_buffer(uz_dqn_experience_replay_t* self,uz_matrix_t *obsdata, uint32_t index){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(obsdata);
    uz_assert(self->is_ready);
    uz_assert(index<self->length);
    uz_matrix_copy_row_from_matrix(self->observations,obsdata,index);
}

void uz_dqn_get_q_value_from_buffer(uz_dqn_experience_replay_t* self,float *QValue, uint32_t index){
    uz_assert_not_NULL(self);
    uz_assert_not_NULL(QValue);
    uz_assert(self->is_ready);
    uz_assert(index<self->length);
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

void resetuintArray(uint32_t *arr, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        arr[i] = 0;
    }
}

void exportFloatArrayToCSV(const char *filename, const float *array, int size) {
    // Check if the file can be opened for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to create the CSV file");
        return;
    }

    // Write the array to the file in CSV format
    for (int i = 0; i < size; i++) {
        fprintf(file, "%.2f", (double)array[i]); // Assuming 2 decimal places, adjust as needed
        if (i < size - 1) {
            fprintf(file, ",");
        } else {
            fprintf(file, "\n");
        }
    }

    // Close the file
    fclose(file);
}



// float uz_dqn_step_adam_no_array(uz_dqn_t *self,float *error, uint32_t mbsize, uint32_t TARGET_UPDATE_FREQUENCY, uint32_t epoch, float targsmoothfact, adam_optimizer_t *adam){
//     uz_assert_not_NULL(self);
//     uz_assert_not_NULL(error);
//     uint32_t actionind;
//     uz_matrix_t* outputcritic;
//     uz_matrix_t* outputtarget;
//     float qplus1 = 0.0f;
//     bool terminal = false;
//     float loss = 0.0f;
//     float cum_loss = 0.0f;
//     float dloss = 0.0f;
//     uint32_t randomindex = 0U;
//     self->env->epsilon_start = calc_epsilon_greedy(self->env->epsilon_start,self->env->epsilon_min,self->env->epsilon_decay);
//     for (uint32_t t = 0; t < self->env->max_steps; t++)
//     {
//     uz_matrix_copy(self->env->inputfornn,self->experience_buffer->vectorforobs);
//     uz_nn_ff(self->critic,self->env->inputfornn);
//     outputcritic=uz_nn_get_output_data(self->critic);
//     if(genRand_float(&self->randinstance->seedRand)<self->env->epsilon_start){
//         actionind = genRand_uint32_t(&self->randinstance->seedRand,self->env->bitlength-1);
//     }
//     else{
//     actionind = uz_matrix_get_max_index(outputcritic);
//     }
//     float qvalue = uz_matrix_get_element_zero_based(outputcritic,0,actionind);
//     uz_dqn_bitflip_action(self->env,actionind);
//     float stepreward = calculate_reward_bit(self->env);
//     uz_dqn_push_to_buffer(self->experience_buffer,&stepreward,&qvalue,&actionind,self->experience_buffer->vectorforobs,self->env->inputfornn);
//     self->env->cumreward+= stepreward;
//     for(uint32_t j=0; j<mbsize;j++){

//         if (self->experience_buffer->counterisfull > 0U){
//         randomindex = genRand_uint32_t(&self->randinstance->seedRand,self->experience_buffer->length-1);
//         }
//         else{
//         randomindex = genRand_uint32_t(&self->randinstance->seedRand,self->experience_buffer->head-1);
//         }
//         uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations1,self->experience_buffer->vectorforobs1,randomindex);
//         uz_nn_ff(self->critic_target_net,self->experience_buffer->vectorforobs1);
//         outputtarget = uz_nn_get_output_data(self->critic_target_net);
//         qplus1 = uz_matrix_get_max_value(outputtarget);
//         float rewardtrain = self->experience_buffer->reward[randomindex];
//         uint32_t actiontrain = self->experience_buffer->action[randomindex];
//         float qvaltrain = self->experience_buffer->qvalues[randomindex];
//         if (rewardtrain==0.0f)
//         {
//             terminal = true;
//         }
//         else{
//             terminal = false;
//         }
//         loss = calculate_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
//         dloss = calculate_derv_loss_dqn(self,rewardtrain,qvaltrain,qplus1,terminal);
//         error[actiontrain] = dloss; 
//         cum_loss += loss; 
//         uz_matrix_get_row_vector_zero_based(self->experience_buffer->observations,self->experience_buffer->vectorforobs,randomindex);
//         uz_nn_backward_pass_mini_batch(self->critic,error,self->experience_buffer->vectorforobs);  
//         resetFloatArray(error,self->critic->number_of_outputs);   
//     }
//     cum_loss = cum_loss/(float)mbsize;
//     adam_optimizer_step(adam,self->critic);
//     uz_nn_set_gradients_zero(self->critic);
//     if (arraysequal(self->env->bitinitial,self->env->bittarget,self->env->bitlength) == true){
//     return cum_loss;
//     }
//     }
//     if (epoch % TARGET_UPDATE_FREQUENCY == 0){
//     uz_nn_target_update(self->critic,self->critic_target_net,smoothing, &targsmoothfact);
//     }
//     return cum_loss;
// } 
// void make_directory(const char* name) {
//    #ifdef __linux__
//        mkdir(name, 777); 
//    #else
//        _mkdir(name);
//    #endif
// }

// float uz_dqn_train2(uz_dqn_t *self, float *rew, float *qval, uint32_t *act, uz_matrix_t *obspl1, uint32_t mbsize,
// uint32_t TARGET_UPDATE_FREQUENCY, uint32_t NUMBER_OF_EPOCHS, float targsmoothfact)
// {
// float qplus1 = 0.0f;
// bool terminal = false;
// float loss = 0.0f;
// float cum_loss = 0.0f;
// float dloss = 0.0f;
// uz_matrix_t* outputtarget;
// for(uint32_t j=0; j<mbsize;j++){
//         uz_matrix_get_row_vector_zero_based(obspl1,self->inputvecnn,j);
//         uz_nn_ff(self->critic_target_net,self->inputvecnn);
//         outputtarget = uz_nn_get_output_data(self->critic_target_net);
//         qplus1 = uz_matrix_get_max_value(outputtarget);
//         if (*rew==0.0f)
//         {
//             terminal = true;
//         }
//         else{
//             terminal = false;
//         }
//         loss = calculate_loss_dqn(self,*rew,*qval,qplus1,terminal);
//         dloss = calculate_derv_loss_dqn(self,*rew,*qval,qplus1,terminal);
//         cum_loss += loss; 
//         uz_nn_backward_pass(self->critic,&dloss,self->inputvecnn);
//         uz_nn_gradient_descent(self->critic,self->lernrate);
//         // uz_nn_backward_pass_mini_batch(self->critic,&dloss,self->inputvecnn);  
//         rew++;
//         qval++;
//         act++;
//     }
//     // dloss mitteln
//     cum_loss = cum_loss/(float)mbsize;
//     // uz_nn_backward_pass(self->critic,&cum_loss,self->inputvecnn);
//     // uz_nn_gradient_descent(self->critic,self->lernrate);
//     // uz_nn_gradient_descent_mini_batch(self->critic,self->lernrate,mbsize);
//     // uz_nn_set_gradients_zero(self->critic);
//     // Targetupdate 
//     if (NUMBER_OF_EPOCHS % TARGET_UPDATE_FREQUENCY  == 0){
//     uz_nn_target_update(self->critic,self->critic_target_net,periodic, &targsmoothfact);
//     }
// return cum_loss;
// }

// float uz_dqn_train3(uz_dqn_t *self, float *rew, float *qval, uint32_t *act, uz_matrix_t *obspl1, uint32_t mbsize,
// uint32_t TARGET_UPDATE_FREQUENCY, uint32_t NUMBER_OF_EPOCHS, float targsmoothfact)
// {
// float qplus1 = 0.0f;
// bool terminal = false;
// float dloss = 0.0f;
// float cum_loss = 0.0f;
// uz_matrix_t* outputtarget;
// for(uint32_t j=0; j<mbsize;j++){
//         uz_matrix_get_row_vector_zero_based(obspl1,self->inputvecnn,j);
//         uz_nn_ff(self->critic_target_net,self->inputvecnn);
//         outputtarget = uz_nn_get_output_data(self->critic_target_net);
//         qplus1 = uz_matrix_get_max_value(outputtarget);
//         if (*rew==0.0f)
//         {
//             terminal = true;
//         }
//         else{
//             terminal = false;
//         }
//         dloss = calculate_derv_loss_dqn(self,*rew,*qval,qplus1,terminal);
//         cum_loss += dloss;  
//         rew++;
//         qval++;
//         act++;
//     }
//     // dloss mitteln
//     cum_loss = cum_loss/(float)mbsize;
//     uz_nn_backward_pass(self->critic,&cum_loss,self->inputvecnn);
//     uz_nn_gradient_descent(self->critic,self->lernrate);
//     uz_nn_set_gradients_zero(self->critic);
//     // Targetupdate 
//     if (NUMBER_OF_EPOCHS % TARGET_UPDATE_FREQUENCY  == 0){
//     uz_nn_target_update(self->critic,self->critic_target_net,periodic, &targsmoothfact);
//     }
// return cum_loss;
// }

#endif
#endif