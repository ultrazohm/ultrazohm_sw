#include "../../uz/uz_global_configuration.h"
#if UZ_MLP_NN_ACC_IP_MAX_INSTANCES > 0U
#include "uz_NN_acc.h"
#include "uz_NN_acc_hw.h"

#include <stdbool.h>
#include "../../uz/uz_HAL.h"
#include "xil_cache.h"


#define MAX_SIZE_OBSERVATION 24U
#define MAX_SIZE_ACTIONS 12U 
#define FIXED_AMOUNT_OF_LAYERS 3U
#define FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER 64U

struct uz_NN_acc_t {
    bool is_ready;
    bool copy_mats_flag;
    uz_matrix_t* observation;
	uz_matrix_t* action;
    struct uz_NN_acc_config_t config;
};

static uint32_t instance_counter = 0U;
static uz_NN_acc_t instances[UZ_MLP_NN_ACC_IP_MAX_INSTANCES] = {0};

static uz_NN_acc_t *UZ_NN_acc_allocation(void);

static uz_NN_acc_t *UZ_NN_acc_allocation(void)
{
    uz_assert(instance_counter < UZ_MLP_NN_ACC_IP_MAX_INSTANCES);
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

    //Get Data
    uz_matrix_t *L1_Weights = uz_nn_get_weight_matrix(config.software_network, 1U);
    uz_matrix_t *L1_Bias = uz_nn_get_bias_matrix(config.software_network, 1U);
    uz_matrix_t *L2_Weights = uz_nn_get_weight_matrix(config.software_network, 2U);
    uz_matrix_t *L2_Bias = uz_nn_get_bias_matrix(config.software_network, 2U);
    uz_matrix_t *L3_Weights = uz_nn_get_weight_matrix(config.software_network, 3U);
    uz_matrix_t *L3_Bias = uz_nn_get_bias_matrix(config.software_network, 3U);
    uz_matrix_t *L_Output_Weights = uz_nn_get_weight_matrix(config.software_network, 4U);
    uz_matrix_t *L_Output_Bias = uz_nn_get_bias_matrix(config.software_network, 4U);

    //Assertions
    uz_assert((uz_nn_get_number_of_layer(config.software_network))==FIXED_AMOUNT_OF_LAYERS);
    uz_assert((uz_nn_get_number_of_inputs(config.software_network))<=MAX_SIZE_OBSERVATION);
    uz_assert((uz_nn_get_number_of_outputs(config.software_network))<=MAX_SIZE_ACTIONS);
    uz_assert(observation->columns <= MAX_SIZE_OBSERVATION);
    uz_assert(observation->rows == 1U);
    //First Layer
    uz_assert(L1_Weights->columns <= MAX_SIZE_OBSERVATION);
    uz_assert(L1_Weights->rows == FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER);
    //Second Layer
    uz_assert(L2_Weights->columns == FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER);
    uz_assert(L2_Weights->rows == FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER);
    //Third Layer
    uz_assert(L3_Weights->columns == FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER);
    uz_assert(L3_Weights->rows == FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER);
    //Output Layer
    uz_assert(L_Output_Weights->columns <= MAX_SIZE_ACTIONS);
    uz_assert(L_Output_Weights->rows == FIXED_AMOUNT_OF_NEURONS_HIDDEN_LAYER);
    uz_assert(action->columns <= MAX_SIZE_ACTIONS);
    uz_assert(action->rows == 1U);

    self->config = config;
    //Set Data
    //Observation
    uz_NN_acc_hw_set_Observation_size(config.base_address,observation->columns);
    uz_NN_acc_hw_set_Observation_Data(config.base_address,observation->data);
    //First Layer
    uz_NN_acc_hw_set_L_1_Weights_Data(config.base_address,L1_Weights->data);
    uz_NN_acc_hw_set_L_1_Bias_Data(config.base_address,L1_Bias->data);
    //Second Layer
    uz_NN_acc_hw_set_L_2_Weights_Data(config.base_address,L2_Weights->data);
    uz_NN_acc_hw_set_L_2_Bias_Data(config.base_address,L2_Bias->data);
    //Third Layer
    uz_NN_acc_hw_set_L_3_Weights_Data(config.base_address,L3_Weights->data);
    uz_NN_acc_hw_set_L_3_Bias_Data(config.base_address,L3_Bias->data);
    //Output Layer
    uz_NN_acc_hw_set_L_Output_Weights_Data(config.base_address,L_Output_Weights->data);
    uz_NN_acc_hw_set_L_Output_Bias_Data(config.base_address,L_Output_Bias->data);
    //Action
    uz_NN_acc_hw_set_Action_size(config.base_address, action->columns);
    uz_NN_acc_hw_set_Actions_Data(config.base_address, action->data);

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
    		break;
    	}
    }
    return(self);
}

void uz_NN_acc_ff_blocking(uz_NN_acc_t *self) {
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	//Flush Cache for input matrix
	Xil_DCacheFlushRange(((uint32_t)((uint32_t*)self->observation->data)),sizeof(self->observation->data));
	uz_NN_acc_hw_set_start(self->config.base_address);
	while(1) {
		bool is_done = uz_NN_acc_hw_get_is_done_output(self->config.base_address);
		if(is_done) {
			//Invalidate CacheLine for output matrix
			Xil_DCacheInvalidateLine((uint32_t)((uint32_t*)self->action->data));
			break;
		}
	}
}

#endif
