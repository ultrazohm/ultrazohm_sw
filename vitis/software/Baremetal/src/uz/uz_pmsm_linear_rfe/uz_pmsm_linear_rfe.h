#ifndef UZ_PMSMK_LIENAR_RFE_H
#define UZ_PMSMK_LIENAR_RFE_H

#include "../uz_Transformation/uz_Transformation.h"
#include <stdbool.h>

typedef struct uz_pmsm_linear_rfe_t uz_pmsm_linear_rfe_t;

uz_pmsm_linear_rfe_t *uz_pmsm_linear_rfe_init(float R, float L_d, float L_q, float rfe_d, float rfe_q, float ts);
uz_3ph_dq_t uz_pmsm_linear_rfe_step(uz_pmsm_linear_rfe_t *self, uz_3ph_dq_t v, float omega_el);


#endif // UZ_PMSMK_LIENAR_RFE_H
