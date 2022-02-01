#ifndef UZ_MLP_THREE_LAYER_HW_H
#define UZ_MLP_THREE_LAYER_HW_H

#include "uz_mlp_three_layer_addr.h"
#include "../../uz/uz_array/uz_array.h"
#include <stdint.h>
#include <stdbool.h>

void uz_mlp_three_layer_hw_write_enable_nn(uint32_t base_address, bool trigger_conversion);
void uz_mlp_three_layer_hw_write_bias_data(uint32_t base_address, float value);
void uz_mlp_three_layer_hw_write_weight_data(uint32_t base_address, float value);
void uz_mlp_three_layer_hw_write_weight_address(uint32_t base_address, uint32_t weight_address);
void uz_mlp_three_layer_hw_write_bias_address(uint32_t base_address, uint32_t bias_address);
void uz_mlp_three_layer_hw_write_enable_bias(uint32_t base_address, uint32_t write_enable_bias_parallel_mac_number);
void uz_mlp_three_layer_hw_write_enable_weights(uint32_t base_address, uint32_t write_enable_bias_parallel_mac_number);
void uz_mlp_three_layer_hw_write_layerNr(uint32_t base_address, uint32_t layerNr);
void uz_mlp_three_layer_hw_write_use_axi_input(uint32_t base_address, bool use_axi_input);
bool uz_mlp_three_layer_hw_read_valid_output(uint32_t base_address);
void uz_mlp_three_layer_hw_write_number_of_inputs(uint32_t base_address, uint32_t number_of_inputs);
void uz_mlp_three_layer_hw_write_number_of_outputs(uint32_t base_address, uint32_t number_of_outputs);

/**
 * @brief This function writes the input values to the neural network and triggers the strobe register
 *        The length of input_data determines how many input values are written to the network.
 *        The minimum length is 2, the maximum length is 16.
 *        Takes ~30us for writing 16 values.
 *        Takes ~20 us for writing 8 values.
 * 
 * @param base_address Base address of the neural network IP-Core instance
 * @param input_data Input data array
 */
void uz_mlp_three_layer_hw_write_input(uint32_t base_address, uz_array_float_t input_data);

/**
 * @brief This function triggers the output strobe and reads the output values of the neural network.
 *        The function writes the output data to the uz_array that is supplied as an input to the function!
 *        Depending on the length of output_data, either 2,4,6, or 8 outputs are read.
 *        Reading out 8 outputs takes ~12 us.
 *        All other length lead to an assertion!
 * 
 * @param base_address Base address of the neural network IP-Core instance
 * @param output_data Array to which the output is written to
 */
void uz_mlp_three_layer_hw_read_output(uint32_t base_address,uz_array_float_t output_data);

/**
 * @brief This function triggers the output strobe and reads the output values of the neural network using unsafe methods.
 *        This function does not have tests and violates coding rules.
 *        However, it is about 6us faster then the safe variant for 8 outputs.
 *        Function takes ~6us.
 * 
 * @param base_address 
 * @param output_data 
 */
void uz_mlp_three_layer_hw_read_output_unsafe(uint32_t base_address, uz_array_float_t output_data);

// Takes 6 us for <9 input values
// Takes 11 us for >9 <17 values

/**
 * @brief This function writes the inputs to the network and triggers the strobe using unsafe methods.
 *        This function does not have tests and violates coding rules.
 *        However, it is ~30us faster than the safe version.
 *        Takes 6us for less than 9 input values, takes 11 us for more than 9 input values.
 * 
 * @param base_address 
 * @param input_data 
 */
void uz_mlp_three_layer_hw_write_input_unsafe(uint32_t base_address, uz_array_float_t input_data);

#endif // UZ_MLP_THREE_LAYER_HW_H
