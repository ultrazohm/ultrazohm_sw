#ifndef UZ_LINEAR_DECOUPPLING_H
#define UZ_LINEAR_DECOUPPLING_H
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"


/**
 * @brief function to calculate linear decoupling values for d- and q-axis
 *
 * @param config uz_PMSM_t_config struct
 * @param i_actual_Ampere uz_dq_t struct with the measured d- and q-currents in ampere
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @return struct uz_dq_t outputs latest values
 */
struct uz_dq_t uz_FOC_linear_decoupling(struct uz_PMSM_t config, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec);

/**
 * @brief function to calculate no decoupling values. No assertion for input parameters.
 * 
 * @return struct uz_dq_t output with 0 for all values
 */
struct uz_dq_t uz_FOC_no_decoupling(struct uz_PMSM_t config, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec);
#endif // UZ_LINEAR_DECOUPPLING_H
