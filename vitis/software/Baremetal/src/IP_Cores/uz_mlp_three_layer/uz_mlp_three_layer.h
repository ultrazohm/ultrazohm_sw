#ifndef UZ_MLP_THREE_LAYER_H
#define UZ_MLP_THREE_LAYER_H

#include "../../uz/uz_nn/uz_nn.h"
#include "../../uz/uz_matrix/uz_matrix.h"
#include "../../uz/uz_array/uz_array.h"
#include <stdint.h>
#include <stdbool.h>

typedef struct uz_mlp_three_layer_ip_t uz_mlp_three_layer_ip_t;

struct uz_mlp_three_layer_ip_config_t
{
    uint32_t base_address;
    bool use_axi_input;
    uz_nn_t *software_network;
};

uz_mlp_three_layer_ip_t *uz_mlp_three_layer_ip_init(struct uz_mlp_three_layer_ip_config_t config);
void uz_mlp_three_layer_write_bias(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *bias, uint32_t layer);
void uz_mlp_three_layer_write_weights(uz_mlp_three_layer_ip_t *self, uint32_t parallel_pcu, uz_matrix_t *weights, uint32_t layer);

void uz_mlp_three_layer_set_parameters(uz_mlp_three_layer_ip_t *self);
void uz_mlp_three_layer_calculate_forward_pass(uz_mlp_three_layer_ip_t *self, uz_array_float_t input_data, uz_array_float_t output_data);
void uz_mlp_three_layer_use_axi_input(uz_mlp_three_layer_ip_t *self,bool use_axi_input);



#endif // UZ_MLP_THREE_LAYER_H
