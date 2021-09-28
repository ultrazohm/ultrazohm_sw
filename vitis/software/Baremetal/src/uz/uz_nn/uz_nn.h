#ifndef UZ_NN_H
#define UZ_NN_H

#define UZ_NN_MAX_LAYER 10
#include "uz_nn_layer.h"


typedef struct uz_nn_t uz_nn_t;

uz_nn_t* uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], size_t number_of_layer);


#endif // UZ_NN_H
