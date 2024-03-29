#include "uz_pmsm6ph_trans_100mhz_addr.h"
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"
#include "uz_pmsm6ph_transformation_hw.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"


uz_6ph_abc_t uz_pmsm6ph_transformation_hw_read_currents(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_6ph_abc_t output_values={0};
    struct uz_fixedpoint_definition_t fixed_out={
    		.is_signed=true,
    		.fractional_bits=18,
    		.integer_bits=(27-18)
    };
    output_values.a1=uz_fixedpoint_axi_read( (base_address+i_abc_out_axi_Data_uz_pmsm6ph_trans_100mhz), fixed_out);
    output_values.b1=uz_fixedpoint_axi_read( (base_address+i_abc_out_axi_Data_uz_pmsm6ph_trans_100mhz+0x4U), fixed_out);
    output_values.c1=uz_fixedpoint_axi_read( (base_address+i_abc_out_axi_Data_uz_pmsm6ph_trans_100mhz+0x8U), fixed_out);
    output_values.a2=uz_fixedpoint_axi_read( (base_address+i_abc_out_axi_Data_uz_pmsm6ph_trans_100mhz+0xCU), fixed_out);
    output_values.b2=uz_fixedpoint_axi_read( (base_address+i_abc_out_axi_Data_uz_pmsm6ph_trans_100mhz+0x10U), fixed_out);
    output_values.c2=uz_fixedpoint_axi_read( (base_address+i_abc_out_axi_Data_uz_pmsm6ph_trans_100mhz+0x14U), fixed_out);
    return output_values;
}

void uz_pmsm6ph_transformation_hw_trigger_output_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+i_abc_out_axi_Strobe_uz_pmsm6ph_trans_100mhz,true);
    uz_axi_write_bool(base_address+i_abc_out_axi_Strobe_uz_pmsm6ph_trans_100mhz,false);
}

float uz_pmsm6ph_transformation_hw_read_theta_el(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);

    struct uz_fixedpoint_definition_t theta_def={
    		.is_signed=true,
			.fractional_bits=14,
			.integer_bits=4
    };

    return uz_fixedpoint_axi_read(base_address+theta_el_axi_Data_uz_pmsm6ph_trans_100mhz,theta_def);

}