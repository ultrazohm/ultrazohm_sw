#include "uz_SS_Debug_hw.h"
#include "uz_SS_Debug_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_SS_Debug_set(uint32_t base_address, bool switchStates []){
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + AXI_SS0_in_Data_SS_Debug, switchStates[0]);
	uz_axi_write_uint32(base_address + AXI_SS1_in_Data_SS_Debug, switchStates[1]);
	uz_axi_write_uint32(base_address + AXI_SS2_in_Data_SS_Debug, switchStates[2]);
	uz_axi_write_uint32(base_address + AXI_SS3_in_Data_SS_Debug, switchStates[3]);
}

void uz_SS_Debug_get(uint32_t base_address, bool switchStates []){
	uz_assert_not_zero_uint32(base_address);
	switchStates[0] = uz_axi_read_uint32(base_address + AXI_SS0_out_Data_SS_Debug);
	switchStates[1] = uz_axi_read_uint32(base_address + AXI_SS1_out_Data_SS_Debug);
	switchStates[2] = uz_axi_read_uint32(base_address + AXI_SS2_out_Data_SS_Debug);
	switchStates[3] = uz_axi_read_uint32(base_address + AXI_SS3_out_Data_SS_Debug);
}
