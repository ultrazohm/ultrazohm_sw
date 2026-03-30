#ifndef UZ_STATIC_NONLINEAR_DECOUPLING_H
#define UZ_STATIC_NONLINEAR_DECOUPLING_H
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_PMSM_config/uz_PMSM_config.h"


/**
 * @brief function to calculate static_nonlinear decoupling values for d- and q-axis
 *
 * @param omega_el_rad_per_sec electrical rotational speed in rad/s
 * @param flux_approx uz_dq_t struct with the approximated flux linkages
 * @return uz_dq_t outputs latest values
 */
uz_3ph_dq_t uz_CurrentControl_static_nonlinear_decoupling(uz_3ph_dq_t flux_approx, float omega_el_rad_per_sec);


#endif // UZ_STATIC_NONLINEAR_DECOUPLING_H
