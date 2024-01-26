// "Copyright [year] <Copyright Owner>"
#include "uz_EnDat_hw.h"
#include "uz_EnDat_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_EnDat_hw_write_divider(uint32_t base_address, uint8_t divider) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+divider_Data_uz_EnDat, divider);
}

void uz_EnDat_hw_write_FKT1DATAFLOW(uint32_t base_address, uint16_t FKT1DATAFLOW) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT1DATAFLOW_Data_uz_EnDat, FKT1DATAFLOW);
}


void uz_EnDat_hw_write_FKT2RECOVERYTIME(uint32_t base_address, uint16_t FKT2RECOVERYTIME) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT2RECOVERYTIME_Data_uz_EnDat, FKT2RECOVERYTIME);
}
void uz_EnDat_hw_write_FKT3INITIALOFF(uint32_t base_address, uint16_t FKT3INITIALOFF) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT3INITIALOFF_Data_uz_EnDat, FKT3INITIALOFF);
}
void uz_EnDat_hw_write_FKT4DATACLKSYNC(uint32_t base_address, uint16_t FKT4DATACLKSYNC) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT4DATACLKSYNC_Data_uz_EnDat, FKT4DATACLKSYNC);
}
void uz_EnDat_hw_write_FKT5TELEGRAMLEN(uint32_t base_address, uint16_t FKT5TELEGRAMLEN) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT5TELEGRAMLEN_Data_uz_EnDat, FKT5TELEGRAMLEN);
}
void uz_EnDat_hw_write_controlword(uint32_t base_address, uint16_t controlword) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+controlword_Data_uz_EnDat, controlword);
}

uint16_t uz_EnDat_hw_read_statusword(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return ((uint16_t)uz_axi_read_uint32(base_address+statusword_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_POS0BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+POS0BUS_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_POS1BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+POS1BUS_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_POS2BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+POS2BUS_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_POS3BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+POS3BUS_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_POS4BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return (uz_axi_read_uint32(base_address+POS4BUS_Data_uz_EnDat));
}

uint8_t uz_EnDat_hw_read_CRCFFSTORED(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return ((uint8_t)uz_axi_read_uint32(base_address+CRCFFSTORED_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_TIMEELASPEDT0T1BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return ((uint32_t)uz_axi_read_uint32(base_address+TIMEELASPEDT0T1BUS_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_TIMEELASPEDT0T2BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return ((uint32_t)uz_axi_read_uint32(base_address+TIMEELASPEDT0T2BUS_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_TIMEELASPEDT0T3BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return ((uint32_t)uz_axi_read_uint32(base_address+TIMEELASPEDT0T3BUS_Data_uz_EnDat));
}

uint32_t uz_EnDat_hw_read_TIMEELASPEDT0T4BUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return ((uint32_t)uz_axi_read_uint32(base_address+TIMEELASPEDT0T4BUS_Data_uz_EnDat));
}

void uz_EnDat_hw_write_FKT6SYNCRESPONSE(uint32_t base_address, uint16_t FKT6SYNCRESPONSE) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT6SYNCRESPONSE_Data_uz_EnDat, FKT6SYNCRESPONSE);
}

void uz_EnDat_hw_write_FKT7EXTRASHIFT(uint32_t base_address, int8_t FKT7EXTRASHIFT) {
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address+FKT7EXTRASHIFT_Data_uz_EnDat, FKT7EXTRASHIFT);
}

uint8_t uz_EnDat_hw_read_RESPONSELENBUS(uint32_t base_address) {
    uz_assert_not_zero(base_address);
    return ((uint8_t)uz_axi_read_uint32(base_address+RESPONSELENBUS_Data_uz_EnDat));
}