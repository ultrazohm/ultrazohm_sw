#include "uz_resolverIP_hw.h"
#include "uz_resolverIP_hwAddresses.h"

#include "../../uz/uz_AXI.h"

#include "../../uz/uz_HAL.h"




void uz_resolverIP_hw_write_RESCON(uint32_t base_address, int32_t val){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + RESCON_Data_uz_axi_testIP, val);
}

void uz_resolverIP_hw_write_RESDAT(uint32_t base_address, int32_t val){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + RESDAT_Data_uz_axi_testIP, val);
}

void uz_resolverIP_hw_write_RESADR(uint32_t base_address, int32_t val){
    uz_assert_not_zero(base_address);
    uz_axi_write_int32(base_address + RESADR_Data_uz_axi_testIP, val);
}

int32_t uz_resolverIP_hw_read_RESCON(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESCON_Data_uz_axi_testIP));
}

int32_t uz_resolverIP_hw_read_RESDAT(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESDAT_Data_uz_axi_testIP));
}
int32_t uz_resolverIP_hw_read_RESRDA(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESRDA_Data_uz_axi_testIP));
}

int32_t uz_resolverIP_hw_read_RESADR(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return (uz_axi_read_int32(base_address + RESADR_Data_uz_axi_testIP));
}