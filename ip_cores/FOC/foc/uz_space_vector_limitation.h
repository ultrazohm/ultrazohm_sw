#ifndef UZ_SPACE_VECTOR_LIMITATION_H
#define UZ_SPACE_VECTOR_LIMITATION_H
#include <stdbool.h>
//#include "../uz_HAL.h"
#include "uz_Transformation.h"
#include "uz_signals.h"

/**
 * @brief function to limit the voltages of a give control algorithm
 *
 * @param u_input_Volts uz_dq_t struct with the voltages, which shall be limited
 * @param V_dc_volts DC-link voltage
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param ext_clamping flag which states, if the SVL is active
 * @return struct uz_dq_t
 */
struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_input_Volts, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t i_actual_Ampere, bool* ext_clamping);
float uz_FOC_SpaceVector_Limitation_d(struct uz_dq_t u_input_Volts, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t i_actual_Ampere, bool* ext_clamping);
float uz_FOC_SpaceVector_Limitation_q(struct uz_dq_t u_input_Volts, float V_dc_volts, float omega_el_rad_per_sec, struct uz_dq_t i_actual_Ampere, bool* ext_clamping);

#endif // UZ_SPACE_VECTOR_LIMITATION_H
