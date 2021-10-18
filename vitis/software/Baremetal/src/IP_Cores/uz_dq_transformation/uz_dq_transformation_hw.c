#include "uz_dq_transformation_hw.h"
#include "uz_HAL.h"

#include "uz_dq_transformation_hwAddresses.h"

void uz_dqTransformation_hw_write_thetaOffset(uint32_t base_address, float thetaOffset)
{
    uz_assert(thetaOffset<8.0f);
    uz_assert(thetaOffset>-8.0f);
    const int fractionalBits = 20;
    uint32_t thetaOffset_int = uz_convert_float_to_sfixed(thetaOffset,fractionalBits);
    uz_axi_write_uint32(base_address+theta_offset_AXI_Data_Trans_123_dq_V12_ip,thetaOffset_int);
} 