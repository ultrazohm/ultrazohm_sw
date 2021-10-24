#include "stdint.h"

#ifndef UZ_DQ_TRANSFORMATION_HW_H
#define UZ_DQ_TRANSFORMATION_HW_H

void uz_dqTransformation_hw_write_thetaOffset(uint32_t base_address, float thetaOffset);

float uz_dqTransformation_hw_get_id(uint32_t base_address);
float uz_dqTransformation_hw_get_iq(uint32_t base_address);


#endif // UZ_DQ_TRANSFORMATION_HW_H
