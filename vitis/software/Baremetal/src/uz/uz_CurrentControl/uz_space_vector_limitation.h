#ifndef UZ_SPACE_VECTOR_LIMITATION_H
#define UZ_SPACE_VECTOR_LIMITATION_H
#include <stdbool.h>
#include "../uz_HAL.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_signals/uz_signals.h"

/**
 * @brief function to limit the voltages of a give control algorithm
 *
 * @param v_input_Volts uz_dq_t struct with the voltages, which shall be limited
 * @param V_dc_volts DC-link voltage
 * @param max_modulation_index Max possible modulation index for the chosen modulation method. I.e. 1/sqrt(3) for Space-Vector-Modulation
 * @param omega_el_rad_per_sec electrical rotational speed in 1/rad
 * @param i_actual_Ampere uz_dq_t struct for measured dq-currents in Ampere
 * @param ext_clamping flag which states, if the SVL is active
 * @return uz_dq_t
 */
uz_3ph_dq_t uz_CurrentControl_SpaceVector_Limitation(uz_3ph_dq_t v_input_Volts, float V_dc_volts, float max_modulation_index, float omega_el_rad_per_sec, uz_3ph_dq_t i_actual_Ampere, bool* ext_clamping);

#endif // UZ_SPACE_VECTOR_LIMITATION_H
