#ifndef UZ_HLS_TESTIP_HW_H
#define UZ_HLS_TESTIP_HW_H
#include <stdint.h>

void uz_HLS_testIP_hw_write_A(uint32_t base_address,int32_t A);
void uz_HLS_testIP_hw_write_B(uint32_t base_address,int32_t B);
int32_t uz_HLS_testIP_hw_read_result(uint32_t base_address);

#endif // UZ_HLS_TESTIP_HW_H