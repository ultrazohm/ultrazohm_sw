#ifndef UZ_MIN_COST_FUNCTION_8_H
#define UZ_MIN_COST_FUNCTION_8_H
#include <stdint.h>
#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the MIN_COST_FUNCTION_8 IP-Core driver
 *
 */
typedef struct uz_min_cost_function_8_t uz_min_cost_function_8_t;

struct uz_min_cost_function_8_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
};

/**
 * @brief Initialize an instance of the driver for the MIN_COST_FUNCTION_8 IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_min_cost_function_8_t* Pointer to an initialized instance of the driver
 */
uz_min_cost_function_8_t* uz_min_cost_function_8_init(struct uz_min_cost_function_8_config_t config);

/**
 * @brief Read the Index of the minimum of the cost function from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return int32_t
 */
int32_t uz_min_cost_function_8_read_Index_out(uz_min_cost_function_8_t* self);

/**
 * @brief Read the J of the minimum of the cost function from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return float
 */
float uz_min_cost_function_8_get_J_out_AXI(uz_min_cost_function_8_t* self);
#endif // UZ_MIN_COST_FUNCTION_8_H
