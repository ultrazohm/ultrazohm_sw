#include "uz_dq_transformation_hw.h"
#include "../../uz/uz_HAL.h"

#include "uz_dq_transformation_hwAddresses.h"

void uz_dqTransformation_hw_write_thetaOffset(uint32_t base_address, float thetaOffset){
    //sfix24_En20
    const int fractionalBits = 20;
    const int integerBits    =  3;
    const int signedness     =  1; // 0=no sign, 1=sign

    float const value_max = 1<<integerBits;
    float const value_min = value_max * signedness * (-1);
    uz_assert(thetaOffset < value_max);
    uz_assert(thetaOffset > value_min);
    uz_assert_not_zero_uint32(base_address);

    uint32_t thetaOffset_int = uz_convert_float_to_sfixed(thetaOffset, fractionalBits);
    uz_axi_write_uint32(base_address + theta_offset_AXI_Data_Trans_123_dq_V12_ip, thetaOffset_int);
} 

float uz_dqTransformation_hw_get_id(uint32_t base_address){
    const int fractionalBits = 11;     // sfix18_En11
    float const value_max = 64.0f;
    float const value_min = -64.0f;

    uz_assert_not_zero_uint32(base_address);
    int32_t tmp = uz_axi_read_int32(base_address + id_AXI_Data_Trans_123_dq_V12_ip);
    float id =  uz_convert_sfixed_to_float(tmp,  fractionalBits);

    uz_assert(id < value_max);
    uz_assert(id > value_min);

    return id;
} 

float uz_dqTransformation_hw_get_iq(uint32_t base_address){
    // sfix18_En11
    const int fractionalBits = 11;
    float const value_max = 64.0f;
    float const value_min = -64.0f;

    uz_assert_not_zero_uint32(base_address);
    int32_t tmp = uz_axi_read_int32(base_address + iq_AXI_Data_Trans_123_dq_V12_ip);
    float iq =  uz_convert_sfixed_to_float(tmp,  fractionalBits);

    uz_assert(iq < value_max);
    uz_assert(iq > value_min);

    return iq;
} 