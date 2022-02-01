#ifndef UZ_MLP_THREE_LAYER_H
#define UZ_MLP_THREE_LAYER_H

#include "../../uz/uz_matrix/uz_matrix.h"
#include <stdint.h>

void uz_mlp_three_layer_write_bias(uint32_t parallel_pcu, uz_matrix_t bias, uint32_t layer);



#endif // UZ_MLP_THREE_LAYER_H
