#include "uz_EnDat_hw.h"
#include "uz_EnDat_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_EnDat_hw_write_divider(uint32_t base_address,int32_t divider)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+divider_Data_uz_EnDat,divider);
}

void uz_EnDat_hw_write_FKT1DATAFLOW(uint32_t base_address,int32_t FKT1DATAFLOW)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT1DATAFLOW_Data_uz_EnDat,FKT1DATAFLOW);
}


void uz_EnDat_hw_write_FKT2RECOVERYTIME(uint32_t base_address,int32_t FKT2RECOVERYTIME)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT2RECOVERYTIME_Data_uz_EnDat,FKT2RECOVERYTIME);
}
void uz_EnDat_hw_write_FKT3INITIALOFF(uint32_t base_address,int32_t FKT3INITIALOFF)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT3INITIALOFF_Data_uz_EnDat,FKT3INITIALOFF);
}
void uz_EnDat_hw_write_FKT4DATACLKSYNC(uint32_t base_address,int32_t FKT4DATACLKSYNC)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT4DATACLKSYNC_Data_uz_EnDat,FKT4DATACLKSYNC);
}
void uz_EnDat_hw_write_FKT5TELEGRAMLEN(uint32_t base_address,int32_t FKT5TELEGRAMLEN)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT5TELEGRAMLEN_Data_uz_EnDat,FKT5TELEGRAMLEN);
}
void uz_EnDat_hw_write_controlword(uint32_t base_address,int32_t controlword)
{
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+controlword_Data_uz_EnDat,controlword);
}

