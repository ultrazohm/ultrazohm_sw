#ifndef UZ_NN_H
#define UZ_NN_H

#define UZ_NN_MAX_LAYER 10
#include "uz_nn_layer.h"


typedef struct uz_nn_t uz_nn_t;

uz_nn_t* uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], size_t number_of_layer);
void uz_nn_ff(uz_nn_t* self, uz_matrix_t const*const input);

#endif // UZ_NN_H
