#ifndef UZ_TRANS_DQ_ALPHABETA_123_HW_H
#define UZ_TRANS_DQ_ALPHABETA_123_HW_H

#include "stdint.h"

void uz_trans_dq_alphabeta_123_hw_set_thetaOffset(uint32_t base_address, float thetaOffset);
void uz_trans_dq_alphabeta_123_hw_set_idref(uint32_t base_address, float idref);
void uz_trans_dq_alphabeta_123_hw_set_iqref(uint32_t base_address, float iqref);
float uz_trans_dq_alphabeta_123_hw_get_ialpha(uint32_t base_address);
float uz_trans_dq_alphabeta_123_hw_get_ibeta(uint32_t base_address);
float uz_trans_dq_alphabeta_123_hw_get_i1(uint32_t base_address);
float uz_trans_dq_alphabeta_123_hw_get_i2(uint32_t base_address);
float uz_trans_dq_alphabeta_123_hw_get_i3(uint32_t base_address);


#endif // UZ_TRANS_DQ_ALPHABETA_123_HW_H
