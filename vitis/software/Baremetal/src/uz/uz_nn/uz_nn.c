#include "../uz_global_configuration.h"
#if UZ_NN_MAX_INSTANCES > 0U
#include <stdbool.h> 
#include "../uz_HAL.h"
#include "uz_nn.h" 
#include "../uz_matrix/uz_matrix.h"

struct uz_nn_t {
    bool is_ready;
    uz_nn_layer_t *layer[UZ_NN_MAX_LAYER];
};

static size_t instance_counter = 0U;
static uz_nn_t instances[UZ_NN_MAX_INSTANCES] = { 0 };

static uz_nn_t* uz_nn_allocation(void);

static uz_nn_t* uz_nn_allocation(void){
    uz_assert(instance_counter < UZ_NN_MAX_INSTANCES);
    uz_nn_t* self = &instances[instance_counter];
    uz_assert_false(self->is_ready);
    instance_counter++;
    self->is_ready = true;
    return (self);
}

uz_nn_t* uz_nn_init(struct uz_nn_layer_config config[UZ_NN_MAX_LAYER], size_t number_of_layer){
    uz_assert(number_of_layer<UZ_NN_MAX_LAYER);
    uz_assert(number_of_layer>1);
    uz_nn_t* self = uz_nn_allocation();

    for(size_t i=0;i<number_of_layer;i++){
        self->layer[i]=uz_nn_layer_init(config[i]);
    }
    return (self);
}
#endif