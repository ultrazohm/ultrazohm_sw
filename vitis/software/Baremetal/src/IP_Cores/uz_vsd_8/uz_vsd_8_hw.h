#ifndef UZ_VSD_8_HW_H
#define UZ_VSD_8_HW_H

#include "stdint.h"

void uz_vsd_8_hw_set_thetaOffset(uint32_t base_address, float thetaOffset);
float uz_vsd_8_hw_get_i_a1(uint32_t base_address);
float uz_vsd_8_hw_get_i_b1(uint32_t base_address);
float uz_vsd_8_hw_get_i_c1(uint32_t base_address);
float uz_vsd_8_hw_get_i_a2(uint32_t base_address);
float uz_vsd_8_hw_get_i_b2(uint32_t base_address);
float uz_vsd_8_hw_get_i_c2(uint32_t base_address);

#endif // UZ_VSD_8_HW_H
