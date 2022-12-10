#ifndef UZ_DELAY_COMPENSATION_8_HW_H
#define UZ_DELAY_COMPENSATION_8_HW_H

#include "stdint.h"

void uz_delay_compensation_8_set_psiPM(uint32_t base_address, float psiPM);
void uz_delay_compensation_8_set_Lq(uint32_t base_address, float Lq);
void uz_delay_compensation_8_set_Ld(uint32_t base_address, float Ld);
void uz_delay_compensation_8_set_Rs(uint32_t base_address, float Rs);
void uz_delay_compensation_8_set_SampleTime_div_Ld(uint32_t base_address, float SampleTime, float Ld);
void uz_delay_compensation_8_set_pole_pairs(uint32_t base_address, float pole_pairs);
void uz_delay_compensation_8_set_SampleTime_div_Lq(uint32_t base_address, float SampleTime, float Lq);
void uz_delay_compensation_8_set_SampleTime_div_Lx(uint32_t base_address, float SampleTime, float Lx);
void uz_delay_compensation_8_set_SampleTime_div_Ly(uint32_t base_address, float SampleTime, float Ly);
float uz_delay_compensation_8_get_id_k_1(uint32_t base_address);
float uz_delay_compensation_8_get_iq_k_1(uint32_t base_address);
float uz_delay_compensation_8_get_ix_k_1(uint32_t base_address);
float uz_delay_compensation_8_get_iy_k_1(uint32_t base_address);

#endif // UZ_DELAY_COMPENSATION_8_HW_H
