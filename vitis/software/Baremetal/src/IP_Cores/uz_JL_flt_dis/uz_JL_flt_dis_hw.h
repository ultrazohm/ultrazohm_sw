
#ifndef UZ_JL_FLT_DIS_HW_H
#define UZ_JL_FLT_DIS_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_JL_flt_dis_hw_write_FLT_PS(uint32_t base_address, bool flt_ps);
void uz_JL_flt_dis_hw_write_FLT_RST(uint32_t base_address, bool reset);
void uz_JL_flt_dis_hw_write_use_flt_dis(uint32_t base_address, bool use_flt_dis);
uint32_t uz_JL_flt_dis_hw_read_FLT_ps(uint32_t base_address);
void uz_JL_flt_dis_hw_write_Watchdog_Rst(uint32_t base_address, bool reset);
void uz_JL_flt_dis_hw_write_Watchdog_trig(uint32_t base_address, bool trig);
void uz_JL_flt_dis_hw_write_Watchdog_Periods_Max_Cnts(uint32_t base_address, uint32_t max_cnts);

#endif // UZ_JL_FLT_DIS_HW_H
