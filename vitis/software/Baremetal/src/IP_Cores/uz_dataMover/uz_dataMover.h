#ifndef UZ_DATAMOVER_H
#define UZ_DATAMOVER_H
#include "../../uz/uz_array/uz_array.h"

/**
 * @brief Returns an array with a direct pointer into the BTCM. The values of the array change independend of the software.
 *
 * @return uz_array_int16_t 
 */
uz_array_int16_t uz_dataMover_get_data_by_pointer(void);

/**
 * @brief Copies all data from TCM to buffer and retruns the buffered data.
 * 
 * @return uz_array_int16_t 
 */
uz_array_int16_t uz_dataMover_update_buffer_and_get_data(void);

/**
 * @brief Copies all data from BTCM to a buffer in the PS.
 *
 * @return void
 */
void uz_dataMover_update_buffer(void);

/**
 * @brief Returns an array with a pointer to the buffered data. The buffer is only updated by explicitly calling the update_buffer function.
 *
 * @return uz_array_int16_t Buffered data
 */
uz_array_int16_t uz_dataMover_get_data_from_buffer(void);

#endif // UZ_DATAMOVER_H