#ifndef UZ_SPACE_VECTOR_LIMITATION_H
#define UZ_SPACE_VECTOR_LIMITATION_H
#include <stdbool.h>

struct uz_dq_t uz_FOC_SpaceVector_Limitation(struct uz_dq_t u_dq_ref_Volts, float U_zk_Volts, float omega_el_rad_per_sec, struct uz_dq_t i_dq_meas_Ampere, bool* ext_clamping);

#endif // UZ_SPACE_VECTOR_LIMITATION_H
