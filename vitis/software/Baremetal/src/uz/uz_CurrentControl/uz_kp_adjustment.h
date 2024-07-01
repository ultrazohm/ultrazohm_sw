#ifndef UZ_KP_ADJUSTMENT_H
#define UZ_KP_ADJUSTMENT_H
#include "../uz_Transformation/uz_Transformation.h"


/**
 * @brief function to calculate linear decoupling values for d- and q-axis
 *
 * @param i_actual_Ampere uz_dq_t struct with the measured d- and q-currents in ampere
 * @param i_actual_Ampere uz_dq_t struct with the reference d- and q-currents in ampere
 * @param flux_approx uz_dq_t struct with the flux approximation d- and q-components
 * @param flux_ref uz_dq_t struct with the flux approximation d- and q-components
 * @param sample_time sample_time
 * @param BO_factor Magnitude optimum factor
 * @return uz_dq_t outputs latest values
 */
uz_3ph_dq_t uz_CurrentControl_kp_adjustment(uz_3ph_dq_t i_actual_Ampere, uz_3ph_dq_t i_reference_Ampere, uz_3ph_dq_t flux_approx, uz_3ph_dq_t flux_ref, float sample_time, float BO_factor);

#endif // UZ_KP_ADJUSTMENT_H
