#ifndef UZ_ENDAT_HW_H
#define UZ_ENDAT_HW_H


#include <stdint.h>
void uz_EnDat_hw_write_divider(uint32_t base_address,int32_t divider);
void uz_EnDat_hw_write_FKT1DATAFLOW(uint32_t base_address,int32_t FKT1DATAFLOW);
void uz_EnDat_hw_write_FKT2RECOVERYTIME(uint32_t base_address,int32_t FKT2RECOVERYTIME);
void uz_EnDat_hw_write_FKT3INITIALOFF(uint32_t base_address,int32_t FKT3INITIALOFF);
void uz_EnDat_hw_write_FKT4DATACLKSYNC(uint32_t base_address,int32_t FKT4DATACLKSYNC);
void uz_EnDat_hw_write_FKT5TELEGRAMLEN(uint32_t base_address,int32_t FKT5TELEGRAMLEN);
void uz_EnDat_hw_write_controlword(uint32_t base_address,int32_t controlword);

int32_t uz_myIP_hw_read_C(uint32_t base_address);

#endif // UZ_ENDAT_HW_H
