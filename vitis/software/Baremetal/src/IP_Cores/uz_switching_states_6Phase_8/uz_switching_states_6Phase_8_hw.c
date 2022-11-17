#include "uz_switching_states_6Phase_8_hw.h"
#include "../../uz/uz_HAL.h"
#include "uz_switching_states_6Phase_8_hwAddresses.h"


int32_t uz_switching_states_6Phase_8_get_min_Index_(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    //int32
    return  uz_axi_read_int32(base_address + min_Index_AXI_Data_parallel_8_sim_switching_states);
}