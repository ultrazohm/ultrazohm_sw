#include "uz_InterlockDeadtime3L_hw.h"
#include "uz_InterlockDeadtime3L_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"

void uz_InterlockDeadtime3L_hw_enable_output(uint32_t base_address, bool en){
	uz_assert_not_zero_uint32(base_address);
	uz_axi_write_uint32(base_address + AXI_EnableOutput_Data_Interlock_ip, en);
}

void uz_InterlockDeadtime3L_hw_set_mode(uint32_t base_address, uint8_t mode){
	uz_assert_not_zero_uint32(base_address);
	if (mode < 1 || mode > 3){
		mode = 2; // if out of range type is set to NPC with DC/2 rating, since its the most conservatice interlock detection
	}
	uz_axi_write_uint32(base_address + AXI_Type_Data_Interlock_ip, mode);
}

void uz_InterlockDeadtime3L_hw_set_delay_ns(uint32_t base_address, uint32_t delay_ns){
	uz_assert_not_zero_uint32(base_address);
	uint32_t delay_cycles;
	delay_cycles = delay_ns/10; //IP core runs at 100MHz -> one clock cycle takes 10ns
	uz_axi_write_uint32(base_address + AXI_DelayCycles_Data_Interlock_ip, delay_cycles);
}
