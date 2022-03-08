#ifndef UZ_DQ_TRANSFORMATION_H
#define UZ_DQ_TRANSFORMATION_H

#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the dq IP-Core driver
 *
 */
typedef struct uz_dqIPcore_t uz_dqIPcore_t;

struct uz_dqIPcore_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_offset; /**< Offset of encoder to alpha-axis */
};

/**
 * @brief Initialize an instance of the driver for the dq-IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_dqIPcore_t* Pointer to an initialized instance of the driver
 */
uz_dqIPcore_t* uz_dqIPcore_init(struct uz_dqIPcore_config_t config);

/**
 * @brief Read the output currents id and iq from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_dq_t
 */
uz_3ph_dq_t uz_dqIPcore_get_id_iq(uz_dqIPcore_t* self);

/**
 * @brief Read the input currents i1, i2, and i3 from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_UVW_t
 */
uz_3ph_abc_t uz_dqIPcore_get_i_uvw(uz_dqIPcore_t* self);

#endif // UZ_DQ_TRANSFORMATION_H
