#ifdef TEST

#include "unity.h"
#include "uz_pmsm9ph_transformation_hw.h"
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_pmsm9ph_trans_100mhz_addr.h"
#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}





void test_uz_pmsm9ph_transformation_hw_read_theta_el(void)
{
    struct uz_fixedpoint_definition_t theta_def={
    		.is_signed=true,
			.fractional_bits=14,
			.integer_bits=4
    };
    float value_expect=4.2f;
    uz_fixedpoint_axi_read_ExpectAndReturn(BASE_ADDRESS+theta_el_axi_Data_uz_pmsm9ph_trans_100mhz,theta_def,value_expect);
    float value_out=uz_pmsm9ph_transformation_hw_read_theta_el(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(value_expect,value_out);
}


void test_uz_pmsm9ph_transformation_hw_trigger_output_strobe(void){
    uz_axi_write_bool_Expect(BASE_ADDRESS+i_abc_out_axi_Strobe_uz_pmsm9ph_trans_100mhz,true);
    uz_axi_write_bool_Expect(BASE_ADDRESS+i_abc_out_axi_Strobe_uz_pmsm9ph_trans_100mhz,false);
    uz_pmsm9ph_transformation_hw_trigger_output_strobe(BASE_ADDRESS);
}

#endif // TEST
