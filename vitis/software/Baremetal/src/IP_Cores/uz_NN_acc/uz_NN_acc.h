#ifndef UZ_NN_ACC_H
#define UZ_NN_ACC_H

#include "../../uz/uz_nn/uz_nn.h"
#include "../../uz/uz_matrix/uz_matrix.h"
#include <stdint.h>
#include <stdbool.h>

#define ARRAY_ALIGN __attribute__ ((__aligned__(32)))

/**
 * @brief Object definition of the IP-Core driver
 * 
 */
typedef struct uz_NN_acc_t uz_NN_acc_t;

struct uz_NN_acc_config_t
{
    uint32_t base_address; /**< Base address of IP-Core */
    uz_nn_t *software_network; /**< Pointer to a compatible uz_nn instance. This instance has to match the IP-Core regarding layer and neuron sizes. */
};

/**
 * @brief Initializes one driver instance of the IP-Core
 * 
 * @param config
 * @param input_data Pointer to input data
 * @param output_data Pointer to which the output data is written
 * @return uz_NN_acc_t* 
 */
uz_NN_acc_t *uz_NN_acc_init(struct uz_NN_acc_config_t config, uz_matrix_t const *const observation, uz_matrix_t const *const action);

/**
 * @brief Calculates one forward pass of the network.
 *        This function is blocking in the sense that data is written to the IP-Core, the is_done output flag is polled, and the output is read.
 *        I.e., this function waits for the IP-Core to finish the calculation.
 * 
 * @param self Pointer to IP-Core driver instance
 */
void uz_NN_acc_ff_blocking(uz_NN_acc_t *self);

#endif
