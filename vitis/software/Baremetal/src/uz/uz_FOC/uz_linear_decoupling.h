#ifndef UZ_LINEAR_DECOUPPLING_H
#define UZ_LINEAR_DECOUPPLING_H
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"

typedef struct uz_lin_decoupling_config{
    float Ld_Henry;
    float Lq_Henry;
    float Psi_PM_Vs;
}uz_lin_decoupling_config;

/**
 * @brief function to calculate linear decoupling values for d- and q-axis
 * 
 * @param i_dq_meas_Ampere u_dq_t struct with the measured d- and q-currents
 * @param config uz_lin_decouppling_config struct
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @return struct uz_dq_t outputs latest values
 */
struct uz_dq_t uz_FOC_linear_decoupling(struct uz_dq_t i_dq_meas_Ampere, uz_lin_decoupling_config config, float omega_el_rad_per_sec);

#endif // UZ_LINEAR_DECOUPPLING_H
