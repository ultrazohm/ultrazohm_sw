#ifndef UZ_NN_ACC_H
#define UZ_NN_ACC_H

#include "../../uz/uz_nn/uz_nn.h"
#include "../../uz/uz_matrix/uz_matrix.h"
#include <stdint.h>
#include <stdbool.h>

//Necessary define to align all arrays and uz_matrix_t objects 
#define MEMORY_ALIGN __attribute__ ((__aligned__(32)))

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
 * @param config configuration struct
 * @param observation Pointer from which the input data is read
 * @param action Pointer to which the output data is written
 * @return uz_NN_acc_t* 
 */
uz_NN_acc_t *uz_NN_acc_init(struct uz_NN_acc_config_t config, uz_matrix_t const *const observation, uz_matrix_t const *const action);

/**
 * @brief Calculates one forward pass of the network and reads out the data.
 *        This function is blocking in the sense that data is written to the IP-Core, the is_done output flag is polled, and the output is read.
 *        I.e., this function waits for the IP-Core to finish the calculation.
 * 
 * @param self Pointer to IP-Core driver instance
 */
void uz_NN_acc_ff_blocking(uz_NN_acc_t *self);

/**
 * @brief Returns the calculation result of the last forward pass of the network.
 *        User has to take care to trigger the calculation before getting the results.
 *        The function is blocking, i.e., the is_done output flag of the IP-Core is polled.
 *        Intended to use with uz_NN_acc_ff_non_blocking to allow concurrent calculations on PS and PL.
 *
 * @param self Pointer to IP-Core driver instance
 */
void uz_NN_acc_get_result_blocking(uz_NN_acc_t *self);

/**
 * @brief Triggers the calculation of one forward pass of the network.
 *        This function is not blocking and returns after the calculation is started.
 *        This enables the concurrent execution of code on the processor while the IP-Core calculates the result of the network.
 *
 * @param self Pointer to IP-Core driver instance
 */
void uz_NN_acc_ff_non_blocking(uz_NN_acc_t *self);
#endif
