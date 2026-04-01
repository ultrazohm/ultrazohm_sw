#ifndef UZ_COUNT_SWITCHING_HW_H
#define UZ_COUNT_SWITCHING_HW_H

#include <stdint.h>
#include <stdbool.h>

void uz_count_switching_hw_reset(uint32_t base_address,bool reset);
uint32_t uz_count_switching_hw_read_count_0(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_1(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_2(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_3(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_4(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_5(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_6(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_7(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_8(uint32_t base_address);
uint32_t uz_count_switching_hw_read_count_sum(uint32_t base_address);


#endif // UZ_COUNT_SWITCHING_HW_H
