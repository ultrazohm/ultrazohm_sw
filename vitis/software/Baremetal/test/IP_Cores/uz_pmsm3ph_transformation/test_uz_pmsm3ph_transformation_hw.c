#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_pmsm3ph_trans_100mhz_addr.h"
#include "uz_pmsm3ph_transformation_hw.h"

#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}
void test_uz_pmsm3ph_transformation_hw_read_currents(void){
    struct uz_fixedpoint_definition_t fixed_out={
    		.is_signed=true,
    		.fractional_bits=18,
    		.integer_bits=(27-18)
    };
    uz_3ph_abc_t value_expect = {
        .a = 1.0f,
        .b = 2.0f,
        .c = 3.0f,};
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+x_abc_out_axi_Data_uz_threephase_VSD_transformation,fixed_out,value_expect.a);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+x_abc_out_axi_Data_uz_threephase_VSD_transformation+0x04,fixed_out,value_expect.b);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+x_abc_out_axi_Data_uz_threephase_VSD_transformation+0x08,fixed_out,value_expect.c);
    uz_3ph_abc_t value_out = uz_pmsm3ph_transformation_hw_read_currents(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a,value_out.a);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b,value_out.b);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c,value_out.c);
}


void test_uz_pmsm3ph_transformation_hw_read_theta_el(void)
{
    struct uz_fixedpoint_definition_t theta_def={
    		.is_signed=true,
			.fractional_bits=14,
			.integer_bits=4
    };
    float value_expect=4.2f;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+theta_el_axi_Data_uz_threephase_VSD_transformation,theta_def,value_expect);
    float value_out=uz_pmsm3ph_transformation_hw_read_theta_el(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(value_expect,value_out);
}

void test_uz_pmsm3ph_transformation_hw_trigger_output_strobe(void){
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+x_abc_out_axi_Strobe_uz_threephase_VSD_transformation,true);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+x_abc_out_axi_Strobe_uz_threephase_VSD_transformation,false);
    uz_pmsm3ph_transformation_hw_trigger_output_strobe(TEST_BASE_ADDRESS);
}

#endif // TEST
