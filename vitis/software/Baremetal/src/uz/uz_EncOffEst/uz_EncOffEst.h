#ifndef UZ_ENCOFFEST_H
#define UZ_ENCOFFEST_H

#include "../uz_SystemTime/uz_SystemTime.h"
#include "../uz_filter_cumulativeavg/uz_filter_cumulativeavg.h"
#include "../../globalData.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"


struct uz_EncOffEst_config {
    actualValues *actual;
    float polepair;
    float setpoint_current;
};

typedef struct uz_EncOffEst_t uz_EncOffEst_t;

uz_EncOffEst_t* uz_EncOffEst_init(struct uz_EncOffEst_config);
uz_3ph_dq_t uz_EncOffEst_step(uz_EncOffEst_t* self);
bool uz_EncOffEst_get_finished(uz_EncOffEst_t* self);

#endif // UZ_ENCOFFEST_H
