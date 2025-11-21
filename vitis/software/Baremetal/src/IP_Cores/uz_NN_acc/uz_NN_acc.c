#include "../../uz/uz_global_configuration.h"
#if UZ_NN_ACC_IP_MAX_INSTANCES > 0U
#include "uz_NN_acc.h"
#include "uz_NN_acc_hw.h"

#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "xil_cache.h"


#define MAX_SIZE_OBSERVATION 24U
#define MAX_SIZE_ACTIONS 12U 
#define MAX_AMOUNT_OF_HIDDEN_LAYERS 5U //5 Hidden Layers 
#define FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER 64U

//Flush and Invalidate Size must be multiple of 32byte
//I.e. MAX_OBS and MAX_ACTION must be divisible by 4
#define FLUSH_SIZE MAX_SIZE_OBSERVATION*4U //sizeof(float)==4
#define INVALIDATE_SIZE MAX_SIZE_ACTIONS*4U+16U //sizeof(float)==4

struct uz_NN_acc_t {
    bool is_ready;
    bool copy_mats_flag;
    uz_matrix_t* observation;
	uz_matrix_t* action;
    uint32_t number_of_hidden_layers;
    float (*output_activation_function)(float);
    struct uz_NN_acc_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_NN_acc_t instances[UZ_NN_ACC_IP_MAX_INSTANCES] = {0};

static uz_NN_acc_t *UZ_NN_acc_allocation(void);

static uz_NN_acc_t *UZ_NN_acc_allocation(void)
{
    uz_assert(instance_counter < UZ_NN_ACC_IP_MAX_INSTANCES);
    uz_NN_acc_t *self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_NN_acc_t *uz_NN_acc_init(struct uz_NN_acc_config_t config, uz_matrix_t const *const observation, uz_matrix_t const *const action) {
    uz_NN_acc_t *self = UZ_NN_acc_allocation();
    uz_assert_not_zero_uint32(config.base_address);
    uz_assert_not_NULL(config.software_network);
    uz_assert_not_NULL(observation);
    uz_assert_not_NULL(action);

    //Assertions
    self->number_of_hidden_layers = (uz_nn_get_number_of_layer(config.software_network)) - 1U; //subtract 1 because of output layer
    uz_assert((self->number_of_hidden_layers)<=MAX_AMOUNT_OF_HIDDEN_LAYERS);
    uz_assert((self->number_of_hidden_layers)> 0U);
    uz_assert((uz_nn_get_number_of_inputs(config.software_network))<=MAX_SIZE_OBSERVATION);
    uz_assert((uz_nn_get_number_of_outputs(config.software_network))<=MAX_SIZE_ACTIONS);
    uz_assert(observation->columns <= MAX_SIZE_OBSERVATION);
    uz_assert(observation->rows == 1U);
    uz_assert(action->columns <= MAX_SIZE_ACTIONS);
    uz_assert(action->rows == 1U);
    

    uz_matrix_t* weights[MAX_AMOUNT_OF_HIDDEN_LAYERS +1U]; //+1 because of output layer  
    uz_matrix_t* biases[MAX_AMOUNT_OF_HIDDEN_LAYERS + 1U]; //+1 because of output layer  

    // Load weight- and bias-matrizes and write their address to HW
    for (uint32_t i = 0U; (i < self->number_of_hidden_layers +1U); ++i) {
        weights[i] = uz_nn_get_weight_matrix(config.software_network, i + 1U);
        biases[i] = uz_nn_get_bias_matrix(config.software_network, i + 1U);

        if(i < (self->number_of_hidden_layers)) {
            switch(i) {
                case 0:
                    //First Layer
                    uz_NN_acc_hw_set_L_1_Weights_Data(config.base_address, weights[i]->data);
                    uz_NN_acc_hw_set_L_1_Bias_Data(config.base_address, biases[i]->data);
                    break;
                case 1:
                    //Second Layer
                    uz_NN_acc_hw_set_L_2_Weights_Data(config.base_address, weights[i]->data);
                    uz_NN_acc_hw_set_L_2_Bias_Data(config.base_address, biases[i]->data);
                    break;
                case 2:
                    //Third Layer
                    uz_NN_acc_hw_set_L_3_Weights_Data(config.base_address, weights[i]->data);
                    uz_NN_acc_hw_set_L_3_Bias_Data(config.base_address, biases[i]->data);
                    break;
                case 3:
                    //Fourth Layer
                    uz_NN_acc_hw_set_L_4_Weights_Data(config.base_address, weights[i]->data);
                    uz_NN_acc_hw_set_L_4_Bias_Data(config.base_address, biases[i]->data);
                    break;
                case 4:
                    //Fifth Layer
                    uz_NN_acc_hw_set_L_5_Weights_Data(config.base_address, weights[i]->data);
                    uz_NN_acc_hw_set_L_5_Bias_Data(config.base_address, biases[i]->data);
                    break;
                default:
                    uz_assert(false);
                    break;
            }
    } else {
        // Output Layer
        uz_NN_acc_hw_set_L_Output_Weights_Data(config.base_address, weights[i]->data);
        uz_NN_acc_hw_set_L_Output_Bias_Data(config.base_address, biases[i]->data);
        uz_assert(weights[self->number_of_hidden_layers]->columns <= MAX_SIZE_ACTIONS);
        self->output_activation_function = uz_nn_get_activation_function(config.software_network, i+1U);
    }
}
    self->config = config;
    self->observation = observation;
    self->action = action;
    //Observation
    uz_NN_acc_hw_set_Observation_size(config.base_address,observation->columns);
    uz_NN_acc_hw_set_Observation_Data(config.base_address,observation->data);
    //Action
    uz_NN_acc_hw_set_Action_size(config.base_address, action->columns);
    uz_NN_acc_hw_set_Actions_Data(config.base_address, action->data);

    //Flush Action matrix so that it's definitely written to memory
    //and won't get "deleted" by the CacheInvalidation
    Xil_DCacheFlushRange(((INTPTR)((INTPTR*)self->action)),FLUSH_SIZE);

    //Trigger IP-Core once to write Weights&Bias to IP-Core
    self->copy_mats_flag = true;
    uz_NN_acc_hw_set_copy_mats_flag(self->config.base_address, self->copy_mats_flag);
    uz_NN_acc_hw_set_start(self->config.base_address);
    while(1) {
    	bool copy_flag_out = uz_NN_acc_hw_get_copy_flag_out(self->config.base_address);
    	bool matrices_updated_out = uz_NN_acc_hw_get_matrices_updated_out(self->config.base_address);
    	if (copy_flag_out && matrices_updated_out) {
    		self->copy_mats_flag = false;
    		uz_NN_acc_hw_set_copy_mats_flag(self->config.base_address, self->copy_mats_flag);
    		uz_NN_acc_hw_set_compute_flag(self->config.base_address, true);
    		break;
    	}
    }
    return(self);
}

void uz_NN_acc_ff_blocking(uz_NN_acc_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	//Flush Cache for input matrix
	Xil_DCacheFlushRange(((INTPTR)((INTPTR*)self->observation->data)),FLUSH_SIZE);
	uz_NN_acc_hw_set_start(self->config.base_address);
	while(1) {
		bool is_done = uz_NN_acc_hw_get_is_done_output(self->config.base_address);
		if(is_done) {
			//Invalidate CacheLine for output matrix
			Xil_DCacheInvalidateRange((INTPTR)((INTPTR*)self->action->data),INVALIDATE_SIZE);
			break;
		}
	}
	//IP-Core has fixed linear-output. Output activation function applied in software
    uz_matrix_apply_function_to_each_element(self->action,self->output_activation_function);
}

void uz_NN_acc_ff_non_blocking(uz_NN_acc_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	//Flush Cache for input matrix
	uz_NN_acc_hw_set_compute_flag(self->config.base_address, true);
	Xil_DCacheFlushRange(((INTPTR)((INTPTR*)self->observation->data)),FLUSH_SIZE);
	uz_NN_acc_hw_set_start(self->config.base_address);
}

void uz_NN_acc_get_result_blocking(uz_NN_acc_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	while(1) {
		bool is_done = uz_NN_acc_hw_get_is_done_output(self->config.base_address);
		if(is_done) {
			uz_NN_acc_hw_set_compute_flag(self->config.base_address, false);
			uz_NN_acc_hw_set_start(self->config.base_address);
			break;
		}
	}
	while(1) {
		bool is_done = uz_NN_acc_hw_get_is_done_output(self->config.base_address);
		if(is_done) {
			Xil_DCacheInvalidateRange((INTPTR)((INTPTR*)self->action->data),INVALIDATE_SIZE);
			break;
		}
	}
		//IP-Core has fixed linear-output. Output activation function applied in software
		uz_matrix_apply_function_to_each_element(self->action,self->output_activation_function);
}
#endif
