#include "uz_pmsm3ph_trans_100mhz_addr.h"
#include "../../uz/uz_HAL.h"
#include "../../uz/uz_AXI.h"
#include "uz_pmsm3ph_transformation_hw.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"


uz_3ph_abc_t uz_pmsm3ph_transformation_hw_read_currents(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_3ph_abc_t output_values={0};
    struct uz_fixedpoint_definition_t fixed_out={
    		.is_signed=true,
    		.fractional_bits=18,
    		.integer_bits=(27-18)
    };
    output_values.a=uz_fixedpoint_axi_read(base_address+x_abc_out_axi_Data_uz_threephase_VSD_transformation, fixed_out);
    output_values.b=uz_fixedpoint_axi_read(base_address+x_abc_out_axi_Data_uz_threephase_VSD_transformation+0x4, fixed_out);
    output_values.c=uz_fixedpoint_axi_read(base_address+x_abc_out_axi_Data_uz_threephase_VSD_transformation+0x8, fixed_out);
    return output_values;
}

void uz_pmsm3ph_transformation_hw_trigger_output_strobe(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);
    uz_axi_write_bool(base_address+x_abc_out_axi_Strobe_uz_threephase_VSD_transformation,true);
    uz_axi_write_bool(base_address+x_abc_out_axi_Strobe_uz_threephase_VSD_transformation,false);
}

float uz_pmsm3ph_transformation_hw_read_theta_el(uint32_t base_address){
    uz_assert_not_zero_uint32(base_address);

    struct uz_fixedpoint_definition_t theta_def={
    		.is_signed=true,
			.fractional_bits=14,
			.integer_bits=4
    };

    return uz_fixedpoint_axi_read(base_address+theta_el_axi_Data_uz_threephase_VSD_transformation,theta_def);

}