
#ifndef UZ_JL_SDDEMOD_HW_H
#define UZ_JL_SDDEMOD_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_JL_SDDemod_hw_write_R_axi(uint32_t base_address, uint16_t R_axi);
int32_t uz_JL_SDDemod_hw_read_data(uint32_t base_address);
void uz_JL_SDDemod_hw_write_clk_ratio(uint32_t base_address, uint16_t clk_ratio);
void uz_JL_SDDemod_hw_write_switch_clk(uint32_t base_address, bool switch_clk);
#endif // UZ_JL_SDDEMOD_HW_H
