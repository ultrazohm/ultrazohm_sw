#pragma once

#include "../../uz/uz_Transformation/uz_Transformation.h"

typedef struct uz_pmsm9ph_transformation_t uz_pmsm9ph_transformation_t;

/**
 * @brief Configuration struct for the PMSM model IP-Core driver
 * 
 */
struct uz_pmsm9ph_config_t{
    uint32_t base_address; /**< Base address of the IP-Core instance to which the driver is coupled */
    uint32_t ip_core_frequency_Hz; /**< Clock frequency of IP-Core */
};

/**
 * @brief Initialize an instance of the driver
 * 
 * @param config Config struct
 * @return uz_pmsm9ph_transformation_t* Pointer to an initialized instance of the driver
 */
uz_pmsm9ph_transformation_t* uz_pmsm9ph_transformation_init(struct uz_pmsm9ph_config_t config);

/**
 * @brief Returns the results of the inverse transformation (phase varivables)
 * 
 * @param self Pointer to driver instance
 * @return struct uz_9ph_abc_t Output values
 */
uz_9ph_abc_t uz_pmsm9ph_transformation_get_currents(uz_pmsm9ph_transformation_t* self);

/**
 * @brief Returns theta electric
 * 
 * @param self Pointer to driver instance
 * @return float theta electric
 */
float uz_pmsm9ph_transformation_get_theta_el(uz_pmsm9ph_transformation_t* self);