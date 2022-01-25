#ifndef UZ_MLP_THREE_LAYER_HW_H
#define UZ_MLP_THREE_LAYER_HW_H

#include "uz_mlp_three_layer_addr.h"
#include "../uz/uz_fixedpoint/uz_fixedpoint.h"
#include <stdint.h>
#include <stdbool.h>

void uz_mlp_three_layer_hw_write_enable_nn(uint32_t base_address,bool trigger_conversion);
void uz_mlp_three_layer_hw_write_bias_data(uint32_t base_address, float value, struct uz_fixedpoint_definition_t uz_fixedpoint_definition);
void uz_mlp_three_layer_hw_write_weight_data(uint32_t base_address, float value, struct uz_fixedpoint_definition_t uz_fixedpoint_definition);
void uz_mlp_three_layer_hw_write_weight_address(uint32_t base_address,uint32_t weight_address);



#endif // UZ_MLP_THREE_LAYER_HW_H
