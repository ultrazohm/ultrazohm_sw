#ifndef UZ_PMSM_FLUX_MAP_H
#define UZ_PMSM_FLUX_MAP_H

#include "../uz_array/uz_array.h"
#include "../uz_Transformation/uz_Transformation.h"

/**
 * @brief Configuration for a PMSM nonlinear flux map backed by two 2D lookup tables.
 *
 * The four arrays are typically supplied by the macros in uz_pmsm_flux_maps_auto_generated.h.
 * The underlying float storage must outlive the flux-map instance: uz_LUT_2D stores pointers to
 * these arrays and does not copy them. Declare the arrays as static (e.g. from the generated
 * macros) at the call site.
 */
struct uz_pmsm_flux_map_config_t {
    uz_array_float_t i_d_breakpoints_A; /**< d-axis current breakpoints (LUT x-axis), strictly increasing, length >= 2 */
    uz_array_float_t i_q_breakpoints_A; /**< q-axis current breakpoints (LUT y-axis), strictly increasing, length >= 2 */
    uz_array_float_t psi_d_Vs;          /**< d-axis flux linkage grid, row-major with i_d changing fastest, length = i_d_len * i_q_len */
    uz_array_float_t psi_q_Vs;          /**< q-axis flux linkage grid, row-major with i_d changing fastest, length = i_d_len * i_q_len */
};

typedef struct uz_pmsm_flux_map_t uz_pmsm_flux_map_t;

/**
 * @brief Initializes a PMSM flux-map instance from breakpoint and flux-grid arrays.
 *
 * Internally builds two uz_LUT_2D instances (psi_d and psi_q), so each flux map consumes two
 * uz_LUT_2D instances. Ensure UZ_LUT_2D_MAX_INSTANCES >= 2 * UZ_PMSM_FLUX_MAP_MAX_INSTANCES.
 *
 * @param config Flux-map configuration. Array lengths and breakpoints are asserted.
 * @return Pointer to the initialized flux-map instance
 */
uz_pmsm_flux_map_t *uz_pmsm_flux_map_init(struct uz_pmsm_flux_map_config_t config);

/**
 * @brief Returns the interpolated flux linkages at a given dq current operating point.
 *
 * Bilinear interpolation via uz_LUT_2D; inputs outside the breakpoint range are clamped.
 *
 * @param self Flux-map instance
 * @param i_dq_A dq current operating point in Ampere (only d and q are used)
 * @return uz_3ph_dq_t with .d = psi_d in Vs, .q = psi_q in Vs, .zero = 0.0f
 */
uz_3ph_dq_t uz_pmsm_flux_map_get_psi_dq_Vs(uz_pmsm_flux_map_t *self, uz_3ph_dq_t i_dq_A);

/**
 * @brief Returns only the interpolated d-axis flux linkage at a given dq current operating point.
 *
 * Bilinear interpolation via uz_LUT_2D; inputs outside the breakpoint range are clamped. Use this
 * instead of uz_pmsm_flux_map_get_psi_dq_Vs when only psi_d is needed to skip the psi_q lookup.
 *
 * @param self Flux-map instance
 * @param i_dq_A dq current operating point in Ampere (only d and q are used)
 * @return psi_d in Vs
 */
float uz_pmsm_flux_map_get_psi_d_Vs(uz_pmsm_flux_map_t *self, uz_3ph_dq_t i_dq_A);

/**
 * @brief Returns only the interpolated q-axis flux linkage at a given dq current operating point.
 *
 * Bilinear interpolation via uz_LUT_2D; inputs outside the breakpoint range are clamped. Use this
 * instead of uz_pmsm_flux_map_get_psi_dq_Vs when only psi_q is needed to skip the psi_d lookup.
 *
 * @param self Flux-map instance
 * @param i_dq_A dq current operating point in Ampere (only d and q are used)
 * @return psi_q in Vs
 */
float uz_pmsm_flux_map_get_psi_q_Vs(uz_pmsm_flux_map_t *self, uz_3ph_dq_t i_dq_A);

#endif // UZ_PMSM_FLUX_MAP_H
