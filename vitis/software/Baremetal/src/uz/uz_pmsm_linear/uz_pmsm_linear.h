#ifndef UZ_PMSM_LINEAR_H
#define UZ_PMSM_LINEAR_H

#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_integrator/uz_integrator.h"
#include <stdbool.h>

typedef struct uz_pmsm_linear_t uz_pmsm_linear_t;

uz_pmsm_linear_t* uz_pmsm_linear_init(float R, float L_d, float L_q, float psi_pm, float ts);
uz_3ph_dq_t uz_pmsm_linear_step(uz_pmsm_linear_t *self, uz_3ph_dq_t v, float omega_el);

#endif // UZ_PMSM_LINEAR_H
