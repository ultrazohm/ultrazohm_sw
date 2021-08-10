#ifndef UZ_LINEAR_DECOUPPLING_H
#define UZ_LINEAR_DECOUPPLING_H
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"

/**
 * @brief Configuration struct for linear decoupling.  Accessible by the user
 *
 */
struct uz_lin_decoupling_config{
    float Ld_Henry; /**< d-axis inductance in Henry. Must be greater than 0.0f */
    float Lq_Henry; /**<q-axis inductance in Henry. Must be greater than 0.0f */
    float Psi_PM_Vs;/**< permanent magnet flux linkage in Volt-seconds. Must be greater than or equal 0.0f */
};

/**
 * @brief function to calculate linear decoupling values for d- and q-axis
 *
 * @param config uz_lin_decouppling_config struct
 * @param i_actual_Ampere uz_dq_t struct with the measured d- and q-currents in ampere
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @return struct uz_dq_t outputs latest values
 */
struct uz_dq_t uz_FOC_linear_decoupling(struct uz_lin_decoupling_config config, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec);

#endif // UZ_LINEAR_DECOUPPLING_H
