#ifndef UZ_IM_DECOUPLING_H
#define UZ_IM_DECOUPLING_H

#include "../uz_IM_config/uz_IM_config.h"
#include "../uz_Transformation/uz_Transformation.h"

/**
 * @brief Rotor-flux-oriented induction-machine decoupling voltage.
 *
 * @param config IM parameters referred to the stator side
 * @param i_actual_Ampere measured dq currents in the rotor-flux frame
 * @param omega_s_rad_per_sec synchronous angular velocity of the flux frame
 * @param psi_r_Vs rotor-flux magnitude
 */
uz_3ph_dq_t uz_CurrentControl_IM_decoupling(uz_IM_t config,
                                            uz_3ph_dq_t i_actual_Ampere,
                                            float omega_s_rad_per_sec,
                                            float psi_r_Vs);

#endif
