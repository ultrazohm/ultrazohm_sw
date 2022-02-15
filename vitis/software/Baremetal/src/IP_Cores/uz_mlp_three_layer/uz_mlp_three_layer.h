#ifndef UZ_MLP_THREE_LAYER_H
#define UZ_MLP_THREE_LAYER_H

#include "../../uz/uz_matrix/uz_matrix.h"
#include <stdint.h>

typedef struct uz_mlp_three_layer_ip_t uz_mlp_three_layer_ip_t;

struct uz_mlp_three_layer_ip_config_t{
    uint32_t base_address;
};


uz_mlp_three_layer_ip_t* uz_mlp_three_layer_ip_init(struct uz_mlp_three_layer_ip_config_t config);
void uz_mlp_three_layer_write_bias(uz_mlp_three_layer_ip_t* self,uint32_t parallel_pcu, uz_matrix_t *bias, uint32_t layer);
void uz_mlp_three_layer_write_weights(uz_mlp_three_layer_ip_t* self,uint32_t parallel_pcu, uz_matrix_t *weights, uint32_t layer);



#endif // UZ_MLP_THREE_LAYER_H
