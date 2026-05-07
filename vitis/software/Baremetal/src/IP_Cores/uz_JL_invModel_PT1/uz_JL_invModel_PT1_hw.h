
#ifndef UZ_JL_INVMDODEL_PT1_HW_H
#define UZ_JL_INVMDODEL_PT1_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_JL_invModel_PT1_hw_write_reset(uint32_t base_address,bool reset);
void uz_JL_invModel_PT1_hw_write_time_constant(uint32_t base_address, float time_constant);
void uz_JL_invModel_PT1_hw_write_gain(uint32_t base_address,float gain);
void uz_JL_invModel_PT1_hw_write_Ualpha(uint32_t base_address, float input);
void uz_JL_invModel_PT1_hw_write_Ubeta(uint32_t base_address, float input);

#endif // UZ_JL_INVMDODEL_PT1_HW_H
