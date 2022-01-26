#include "uz_errorhandler_hw.h"
#include "uz_errorhandler_hwAddresses.h"
#include "../../uz/uz_AXI.h"

void uz_errorhandler_hw_write_ERROR(uint32_t base_address,int32_t ERROR){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_int32(base_address+ERROR_uint32_Data_uz_axi_errorHandler,ERROR);
}

void uz_errorhandler_hw_write_MASK(uint32_t base_address,int32_t MASK){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_int32(base_address+MASK_uint32_Data_uz_axi_errorHandler,MASK);
}

int32_t uz_errorhandler_hw_read_ERROR(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return (uz_axi_read_int32(base_address+ERROR_uint32_Data_uz_axi_errorHandler));
}

int32_t uz_errorhandler_hw_read_MASK(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    return (uz_axi_read_int32(base_address+MASK_uint32_Data_uz_axi_errorHandler));
}
