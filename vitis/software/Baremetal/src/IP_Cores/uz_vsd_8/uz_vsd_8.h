#ifndef UZ_VSD_8_H
#define UZ_VSD_8_H

#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the vsd_8 IP-Core driver
 *
 */
typedef struct uz_vsd_8_t uz_vsd_8_t;

struct uz_vsd_8_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_offset; /**< Offset of encoder to alpha-axis */
};

/**
 * @brief Initialize an instance of the driver for the vsd_8 IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_vsd_8_t* Pointer to an initialized instance of the driver
 */
uz_vsd_8_t* uz_vsd_8_init(struct uz_vsd_8_config_t config);

/**
 * @brief Read the input currents ia1, ib1, ic1, ia2, ib2 and ic2 from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_6ph_abc_t
 */
uz_6ph_abc_t uz_vsd_8_get_ia1_ib1_ic1_ia2_ib2_ic2(uz_vsd_8_t* self);

#endif // UZ_VSD_8_H
