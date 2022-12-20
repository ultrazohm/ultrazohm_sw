#ifndef UZ_VSD_AND_PARK_TRANSFORMATION_6PHASE_H
#define UZ_VSD_AND_PARK_TRANSFORMATION_6PHASE_H

#include "../../uz/uz_Transformation/uz_Transformation.h"

/**
 * @brief Object data type definition of the vsd_and_park_transformation_6phase IP-Core driver
 *
 */
typedef struct uz_vsd_and_park_transformation_6phase_t uz_vsd_and_park_transformation_6phase_t;

struct uz_vsd_and_park_transformation_6phase_config_t{
    uint32_t base_address; /**< Base address of the IP-Core */
    uint32_t ip_clk_frequency_Hz; /**< Clock frequency of the IP-Core */
    float theta_offset; /**< Offset of encoder to alpha-axis */
};

/**
 * @brief Initialize an instance of the driver for the dq-IP-Core
 *
 * @param config Configuration struct for the instance
 * @return uz_vsd_and_park_transformation_6phase_t* Pointer to an initialized instance of the driver
 */
uz_vsd_and_park_transformation_6phase_t* uz_vsd_and_park_transformation_6phase_init(struct uz_vsd_and_park_transformation_6phase_config_t config);

/**
 * @brief Read the output currents id and iq from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_dq_t
 */
uz_3ph_dq_t uz_vsd_and_park_transformation_6phase_get_id_iq(uz_vsd_and_park_transformation_6phase_t* self);

/**
 * @brief Read the input currents ialpha, ibeta, ix, iy, i0plus and i0minus from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_6ph_alphabeta_t
 */
uz_6ph_alphabeta_t uz_vsd_and_park_transformation_6phase_get_ialpha_ibeta_ix_iy_i0plus_i0minus(uz_vsd_and_park_transformation_6phase_t* self);

/**
 * @brief Read the input currents ia1, ib1, ic1, ia2, ib2 and ic2 from the IP-Core and return them
 *
 * @param self Pointer to driver instance
 * @return uz_6ph_abc_t
 */
uz_6ph_abc_t uz_vsd_and_park_transformation_6phase_get_ia1_ib1_ic1_ia2_ib2_ic2(uz_vsd_and_park_transformation_6phase_t* self);


#endif // UZ_VSD_AND_PARK_TRANSFORMATION_6PHASE_H
