#include "interleaved_hw.h"
#include "interleaved_hwAddresses.h"
#include "../../uz/uz_AXI.h"
#include "../../uz/uz_HAL.h"


void interleaved_set_i1(uint32_t base_address, float i){
	uz_assert_not_zero(base_address);
	uz_axi_write_int32(base_address + AXI_INTERLEAVED_BOOST_I1, uz_convert_float_to_sfixed(i, INTERLEAVED_BOOST_NUM_FRACTIONAL_BITS));
}

void interleaved_set_i2(uint32_t base_address, float i){
	uz_assert_not_zero(base_address);
	uz_axi_write_int32(base_address + AXI_INTERLEAVED_BOOST_I2, uz_convert_float_to_sfixed(i, INTERLEAVED_BOOST_NUM_FRACTIONAL_BITS));
}

void interleaved_set_vout(uint32_t base_address, float v){
	uz_assert_not_zero(base_address);
	uz_axi_write_int32(base_address + AXI_INTERLEAVED_BOOST_V, uz_convert_float_to_sfixed(v, INTERLEAVED_BOOST_NUM_FRACTIONAL_BITS));
}


bool interleaved_get_u1(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_bool(base_address + AXI_INTERLEAVED_BOOST_U1));
}

bool interleaved_get_u2(uint32_t base_address){
    uz_assert_not_zero(base_address);
    return(uz_axi_read_bool(base_address + AXI_INTERLEAVED_BOOST_U2));
}
