
#ifndef UZ_JL_INVMODEL_IDEAL_HW_H
#define UZ_JL_INVMODEL_IDEAL_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_JL_invModel_ideal_hw_write_Udc(uint32_t base_address, float Udc);
float uz_JL_invModel_ideal_hw_read_out_Ua(uint32_t base_address);
float uz_JL_invModel_ideal_hw_read_out_Ub(uint32_t base_address);
float uz_JL_invModel_ideal_hw_read_out_Uc(uint32_t base_address);
void uz_JL_invModel_ideal_hw_trigger_output_strobe(uint32_t base_address);

#endif // UZ_JL_INVMODEL_IDEAL_HW_H
