#ifndef UZ_ENCOFFEST_H
#define UZ_ENCOFFEST_H

#include "../uz_SystemTime/uz_SystemTime.h"
#include "../uz_filter_cumulativeavg/uz_filter_cumulativeavg.h"
#include "../../globalData.h"
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_HAL.h"


struct uz_EncOffEst_config {
    actualValues *actual;
};

typedef struct uz_EncOffEst_t uz_EncOffEst_t;

uz_EncOffEst_t* uz_EncOffEst_init(struct uz_EncOffEst_config);
bool uz_EncOffEst_step(uz_EncOffEst_t* self);

#endif // UZ_ENCOFFEST_H
