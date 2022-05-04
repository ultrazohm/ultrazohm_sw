#ifndef UZ_DQ_TRANSFORMATION_HW_H
#define UZ_DQ_TRANSFORMATION_HW_H

#include "stdint.h"

void uz_dqTransformation_hw_set_thetaOffset(uint32_t base_address, float thetaOffset);
float uz_dqTransformation_hw_read_id(uint32_t base_address);

float uz_dqTransformation_hw_get_id(uint32_t base_address);
float uz_dqTransformation_hw_get_iq(uint32_t base_address);

float uz_dqTransformation_hw_get_ialpha(uint32_t base_address);
float uz_dqTransformation_hw_get_ibeta(uint32_t base_address);

float uz_dqTransformation_hw_get_i1(uint32_t base_address);
float uz_dqTransformation_hw_get_i2(uint32_t base_address);
float uz_dqTransformation_hw_get_i3(uint32_t base_address);


#endif // UZ_DQ_TRANSFORMATION_HW_H
