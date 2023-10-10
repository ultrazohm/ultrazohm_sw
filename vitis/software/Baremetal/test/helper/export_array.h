#include <stdint.h>
#include "uz_matrix.h"

void export_histogram(float *array, uint32_t size, char filepath[]);

/**
 * @brief Save weights from c to .csv data for comparison reasons
 *
 * @param self
 * @param fname char pointer, that determines the .csv data name, where the weights should be stored
 */
void uz_nn_layer_matrix_export(uz_matrix_t const *const self, char *fname);
