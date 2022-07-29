#ifndef UZ_MLP_THREE_LAYER_H
#define UZ_MLP_THREE_LAYER_H

#include "../../uz/uz_nn/uz_nn.h"
#include "../../uz/uz_matrix/uz_matrix.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Object definition of the IP-Core driver
 * 
 */
typedef struct uz_mlp_three_layer_ip_t uz_mlp_three_layer_ip_t;

/**
 * @brief Configuration struct for the IP-Core
 * 
 */
struct uz_mlp_three_layer_ip_config_t
{
    uint32_t base_address; /**< Base address of IP-Core */
    bool use_axi_input; /**< Flag to use inputs from axi (true), or from PL inputs (false) */
    uz_nn_t *software_network; /**< Pointer to a compatible uz_nn instance. This instance has to match the IP-Core regarding layer and neuron sizes. */
};

/**
 * @brief Initializes one driver instance of the IP-Core
 * 
 * @param config
 * @return uz_mlp_three_layer_ip_t* 
 */
uz_mlp_three_layer_ip_t *uz_mlp_three_layer_ip_init(struct uz_mlp_three_layer_ip_config_t config);

/**
 * @brief Calculates one forward pass of the network.
 *        This function is blocking in the sense that data is written to the IP-Core, the valid output flag is polled, and the output is read.
 *        I.e., this function waits for the IP-Core to finish the calculation.
 * 
 * @param self Pointer to IP-Core driver instance
 * @param input_data Pointer to input data
 * @param output_data Pointer to which the output data is written
 */
void uz_mlp_three_layer_ff_blocking(uz_mlp_three_layer_ip_t *self, uz_matrix_t* input_data, uz_matrix_t* output_data);

/**
 * @brief Triggers the calculation of one forward pass of the network.
 *        This function is not blocking and returns after the calculation is startet.
 *        This enables the concurrent execution of code on the processor while the IP-Core calculates the result of the network.
 * 
 * @param self 
 * @param input_data 
 */
void uz_mlp_three_layer_ff_trigger(uz_mlp_three_layer_ip_t *self, uz_matrix_t *input_data);

/**
 * @brief Returns the calculation result of the last forward pass of the network.
 *        User has to take care to trigger the calculation before getting the results.
 *        The function is blocking, i.e., the valid output flag of the IP-Core is polled and the first available valid data is read.
 *        Intended to use with uz_mlp_three_layer_ff_trigger to allow concurrent calculations on PS and PL.
 * 
 * @param self 
 * @param output_data 
 */
void uz_mlp_three_layer_ff_get_result_blocking(uz_mlp_three_layer_ip_t *self, uz_matrix_t *output_data);

/**
 * @brief Same functionality as uz_mlp_three_layer_ff_blocking but violates coding rules to improve calculation speed.
 *        Is approximately 30us faster than the safe version.
 *        Compare results of safe and unsafe version before usage!
 * 
 * @param self 
 * @param input_data 
 * @param output_data 
 */
void uz_mlp_three_layer_ff_blocking_unsafe(uz_mlp_three_layer_ip_t *self, uz_matrix_t *input_data, uz_matrix_t *output_data);

void uz_mlp_three_layer_ff_get_result_blocking_unsafe(uz_mlp_three_layer_ip_t *self, uz_matrix_t *output_data);
void uz_mlp_three_layer_ff_trigger_unsafe(uz_mlp_three_layer_ip_t *self, uz_matrix_t *input_data);

// Utility functions
void uz_mlp_three_layer_set_parameters(uz_mlp_three_layer_ip_t *self);
void uz_mlp_three_layer_set_bias(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *bias, uint32_t layer);
void uz_mlp_three_layer_set_weights(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *weights, uint32_t layer);
void uz_mlp_three_layer_set_use_axi_input(uz_mlp_three_layer_ip_t *self, bool use_axi_input);
void uz_mlp_three_layer_disable_pl_trigger(uz_mlp_three_layer_ip_t *self, bool disable_pl_trigger);
#endif // UZ_MLP_THREE_LAYER_H
