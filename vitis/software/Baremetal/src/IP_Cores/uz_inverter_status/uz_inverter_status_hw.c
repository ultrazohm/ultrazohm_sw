#include "uz_inverter_status_hw.h"
#include "uz_inverter_status_hwAddresses.h"
#include "../../uz/uz_AXI.h"

uint32_t uz_inverter_status_hw_get_RDY(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_RDY_Data_uz_inverter_status_ip));
}

uint32_t uz_inverter_status_hw_get_FLT(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_uint32(base_address + AXI_FLT_Data_uz_inverter_status_ip));
}

void uz_inverter_status_hw_set_GateDriverEnable(uint32_t base_address, uint8_t GateDriverEnable, uint8_t useFLTlogic){
    uz_assert_not_zero(base_address);

    uint32_t tmp_GateDriverEnable;

    if(useFLTlogic) {
    	tmp_GateDriverEnable = GateDriverEnable | (1<<1);
    } else {
    	tmp_GateDriverEnable = GateDriverEnable;
    }

    uz_axi_write_uint32(base_address + EN_GateDriver_Data_uz_inverter_status_ip, tmp_GateDriverEnable);
}


