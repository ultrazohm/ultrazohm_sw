#ifndef UZ_LINEAR_DECOUPPLING_H
#define UZ_LINEAR_DECOUPPLING_H
#include "uz_Transformation.h"

struct uz_PMSM_t{
    float R_ph_Ohm;/**< phase resitance inductance in Ohm. Must be greater than 0.0f */
    float Ld_Henry; /**< d-axis inductance in Henry. Must be greater than 0.0f */
    float Lq_Henry;/**< q-axis inductance in Henry. Must be greater than 0.0f */
    float Psi_PM_Vs;/**< permanent magnet flux linkage in Volt-seconds. Must be greater or equal than 0.0f */
    float polePairs; /**< number of polePairs of the machine. Must be greater than 0.0f. Must be no decimal value (i.e. 2.5f is not allowed) */
    float J_kg_m_squared; /**< inertia of the PMSM. Must be greater than 0.0f */
    float I_max_Ampere; /**< max allowed current per phase. Must be greater than 0.0f */
};

/**
 * @brief function to calculate linear decoupling values for d- and q-axis
 *
 * @param config uz_PMSM_t_config struct
 * @param i_actual_Ampere uz_dq_t struct with the measured d- and q-currents in ampere
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @return struct uz_dq_t outputs latest values
 */
struct uz_dq_t uz_FOC_linear_decoupling(struct uz_PMSM_t config, struct uz_dq_t i_actual_Ampere, float omega_el_rad_per_sec);

#endif // UZ_LINEAR_DECOUPPLING_H
