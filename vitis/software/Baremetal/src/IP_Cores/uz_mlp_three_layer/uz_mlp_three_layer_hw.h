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
void uz_mlp_three_layer_hw_write_enable_bias(uint32_t base_address, bool write_enable_bias);
void uz_mlp_three_layer_hw_write_enable_weights(uint32_t base_address, bool write_enable_weights);
void uz_mlp_three_layer_hw_write_layerNr(uint32_t base_address, uint32_t layerNr);
void uz_mlp_three_layer_hw_write_use_axi_input(uint32_t base_address, bool use_axi_input);
bool uz_mlp_three_layer_hw_read_valid_output(uint32_t base_address);
void uz_mlp_three_layer_hw_write_number_of_inputs(uint32_t base_address, uint32_t number_of_inputs);
void uz_mlp_three_layer_hw_write_number_of_outputs(uint32_t base_address, uint32_t number_of_outputs);


void uz_mlp_three_layer_hw_write_input(uint32_t base_address, uz_array_float_t input_data);


#endif // UZ_MLP_THREE_LAYER_HW_H
