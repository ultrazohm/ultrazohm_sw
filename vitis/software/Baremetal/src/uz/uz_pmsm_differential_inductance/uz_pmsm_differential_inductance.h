#ifndef UZ_PMSM_DIFFERENTIAL_INDUCTANCE_H
#define UZ_PMSM_DIFFERENTIAL_INDUCTANCE_H

#include "../uz_array/uz_array.h"
#include "../uz_Transformation/uz_Transformation.h"

/**
 * @brief Configuration for a PMSM differential-inductance map backed by four 2D lookup tables.
 *
 * The six arrays are typically supplied by the macros in
 * uz_pmsm_differential_inductances_auto_generated.h. The underlying float storage must outlive the
 * instance: uz_LUT_2D stores pointers to these arrays and does not copy them. Declare the arrays as
 * static (e.g. from the generated macros) at the call site.
 */
struct uz_pmsm_differential_inductance_config_t {
    uz_array_float_t i_d_breakpoints_A; /**< d-axis current breakpoints (LUT x-axis), strictly increasing, length >= 2 */
    uz_array_float_t i_q_breakpoints_A; /**< q-axis current breakpoints (LUT y-axis), strictly increasing, length >= 2 */
    uz_array_float_t L_dd_H;            /**< dpsi_d/di_d grid, row-major with i_d changing fastest, length = i_d_len * i_q_len */
    uz_array_float_t L_dq_H;            /**< dpsi_d/di_q grid, same layout */
    uz_array_float_t L_qd_H;            /**< dpsi_q/di_d grid, same layout */
    uz_array_float_t L_qq_H;            /**< dpsi_q/di_q grid, same layout */
};

/*
 * The four entries relate the flux-linkage derivative to the current derivative:
 * [dpsi_d/dt; dpsi_q/dt] = [[L_dd, L_dq]; [L_qd, L_qq]] * [di_d/dt; di_q/dt].
 * Each entry has its own getter because the full matrix is rarely needed at once.
 */

typedef struct uz_pmsm_differential_inductance_t uz_pmsm_differential_inductance_t;

/**
 * @brief Initializes a PMSM differential-inductance instance from breakpoint and inductance arrays.
 *
 * Internally builds four uz_LUT_2D instances (L_dd, L_dq, L_qd, L_qq), so each instance consumes
 * four uz_LUT_2D instances. Ensure UZ_LUT_2D_MAX_INSTANCES >= 4 * UZ_PMSM_DIFFERENTIAL_INDUCTANCE_MAX_INSTANCES
 * (plus any used by other modules such as uz_pmsm_flux_map).
 *
 * @param config Differential-inductance configuration. Array lengths and breakpoints are asserted.
 * @return Pointer to the initialized instance
 */
uz_pmsm_differential_inductance_t *uz_pmsm_differential_inductance_init(struct uz_pmsm_differential_inductance_config_t config);

/**
 * @brief Returns the interpolated L_dd = dpsi_d/di_d at a dq current operating point.
 *
 * Bilinear interpolation via uz_LUT_2D; inputs outside the breakpoint range are clamped.
 *
 * @param self Differential-inductance instance
 * @param i_dq_A dq current operating point in Ampere (only d and q are used)
 * @return L_dd in Henry
 */
float uz_pmsm_differential_inductance_get_L_dd_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A);

/**
 * @brief Returns the interpolated L_dq = dpsi_d/di_q at a dq current operating point.
 *
 * Bilinear interpolation via uz_LUT_2D; inputs outside the breakpoint range are clamped.
 *
 * @param self Differential-inductance instance
 * @param i_dq_A dq current operating point in Ampere (only d and q are used)
 * @return L_dq in Henry
 */
float uz_pmsm_differential_inductance_get_L_dq_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A);

/**
 * @brief Returns the interpolated L_qd = dpsi_q/di_d at a dq current operating point.
 *
 * Bilinear interpolation via uz_LUT_2D; inputs outside the breakpoint range are clamped.
 *
 * @param self Differential-inductance instance
 * @param i_dq_A dq current operating point in Ampere (only d and q are used)
 * @return L_qd in Henry
 */
float uz_pmsm_differential_inductance_get_L_qd_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A);

/**
 * @brief Returns the interpolated L_qq = dpsi_q/di_q at a dq current operating point.
 *
 * Bilinear interpolation via uz_LUT_2D; inputs outside the breakpoint range are clamped.
 *
 * @param self Differential-inductance instance
 * @param i_dq_A dq current operating point in Ampere (only d and q are used)
 * @return L_qq in Henry
 */
float uz_pmsm_differential_inductance_get_L_qq_H(uz_pmsm_differential_inductance_t *self, uz_3ph_dq_t i_dq_A);

#endif // UZ_PMSM_DIFFERENTIAL_INDUCTANCE_H
