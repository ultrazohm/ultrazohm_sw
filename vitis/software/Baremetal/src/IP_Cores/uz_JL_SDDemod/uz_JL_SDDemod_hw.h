
#ifndef UZ_JL_SDDEMOD_HW_H
#define UZ_JL_SDDEMOD_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_JL_SDDemod_hw_write_dezi_U(uint32_t base_address, uint16_t dezimation);
void uz_JL_SDDemod_hw_write_dezi_I(uint32_t base_address, uint16_t dezimation);
void uz_JL_SDDemod_hw_write_switch_edge(uint32_t base_address, bool switch_edge);
void uz_JL_SDDemod_hw_write_clk_ratio(uint32_t base_address, uint16_t clk_ratio);
void uz_JL_SDDemod_hw_write_calib_ads_en(uint32_t base_address, bool calib_en);
void uz_JL_SDDemod_hw_write_data_delay(uint32_t base_address, uint16_t filt_input_delay);
void uz_JL_SDDemod_hw_write_clk_dsw_en(uint32_t base_address, bool dsw_clk_en);
void uz_JL_SDDemod_hw_write_clk_dutycycle(uint32_t base_address, float dutycycle);
int32_t uz_JL_SDDemod_hw_read_data_out_ps_U(uint32_t base_address);
int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH1(uint32_t base_address);
int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH2(uint32_t base_address);
int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH3(uint32_t base_address);
int32_t uz_JL_SDDemod_hw_read_data_out_ps_PH4(uint32_t base_address);


#endif // UZ_JL_SDDEMOD_HW_H
