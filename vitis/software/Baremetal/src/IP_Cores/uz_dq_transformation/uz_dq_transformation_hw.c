#include "uz_dq_transformation_hw.h"
#include "../../uz/uz_HAL.h"

#include "uz_dq_transformation_hwAddresses.h"

void uz_dqTransformation_hw_write_thetaOffset(uint32_t base_address, float thetaOffset)
{
    uz_assert_not_zero_uint32(base_address);
    uz_assert(thetaOffset<8.0f); // Data type of thetaOffset can only represent signed 8
    uz_assert(thetaOffset>-8.0f);
    const int fractionalBits = 20;
    uint32_t thetaOffset_int = uz_convert_float_to_sfixed(thetaOffset,fractionalBits);
    uz_axi_write_uint32(base_address+theta_offset_AXI_Data_Trans_123_dq_V12_ip,thetaOffset_int);
} 

float uz_dqTransformation_hw_read_id(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
   uint32_t id_read=uz_axi_read_uint32(base_address+id_AXI_Data_Trans_123_dq_V12_ip);
   int fractionalBits=11;
   return uz_convert_unsigned_fixed_to_float(id_read,fractionalBits);
}
