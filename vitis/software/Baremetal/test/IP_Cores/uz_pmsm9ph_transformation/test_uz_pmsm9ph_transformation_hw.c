#ifdef TEST

#include "unity.h"
#include "uz_struct_helper.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "mock_uz_fixedpoint.h"
#include "uz_pmsm9ph_trans_100mhz_addr.h"
#include "uz_pmsm9ph_transformation_hw.h"

#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}
void test_uz_pmsm9ph_transformation_hw_read_currents(void){
    struct uz_fixedpoint_definition_t fixed_out={
    		.is_signed=true,
    		.fractional_bits=18,
    		.integer_bits=(27-18)
    };
    uz_9ph_abc_t value_expect = {
        .a1 = 1.0f,
        .b1 = 2.0f,
        .c1 = 3.0f,
        .a2 = 4.0f,
        .b2 = 5.0f,
        .c2 = 6.0f,
        .a3 = 7.0f,
        .b3 = 8.0f,
        .c3 = 9.0f};
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz,fixed_out,value_expect.a1);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0x04,fixed_out,value_expect.b1);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0x08,fixed_out,value_expect.c1);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0xC,fixed_out,value_expect.a2);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0x10,fixed_out,value_expect.b2);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0x14,fixed_out,value_expect.c2);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0x18,fixed_out,value_expect.a3);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0x1C,fixed_out,value_expect.b3);
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+i_abc_out_axi_Data_uz_pmsm9ph_trans_100mhz+0x20,fixed_out,value_expect.c3);
    uz_9ph_abc_t value_out = uz_pmsm9ph_transformation_hw_read_currents(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a1,value_out.a1);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b1,value_out.b1);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c1,value_out.c1);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a2,value_out.a2);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b2,value_out.b2);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c2,value_out.c2);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.a3,value_out.a3);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.b3,value_out.b3);
    TEST_ASSERT_EQUAL_FLOAT(value_expect.c3,value_out.c3);
}


void test_uz_pmsm9ph_transformation_hw_read_theta_el(void)
{
    struct uz_fixedpoint_definition_t theta_def={
    		.is_signed=true,
			.fractional_bits=14,
			.integer_bits=4
    };
    float value_expect=4.2f;
    uz_fixedpoint_axi_read_ExpectAndReturn(TEST_BASE_ADDRESS+theta_el_axi_Data_uz_pmsm9ph_trans_100mhz,theta_def,value_expect);
    float value_out=uz_pmsm9ph_transformation_hw_read_theta_el(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(value_expect,value_out);
}

void test_uz_pmsm9ph_transformation_hw_trigger_output_strobe(void){
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+i_abc_out_axi_Strobe_uz_pmsm9ph_trans_100mhz,true);
    uz_axi_write_bool_Expect(TEST_BASE_ADDRESS+i_abc_out_axi_Strobe_uz_pmsm9ph_trans_100mhz,false);
    uz_pmsm9ph_transformation_hw_trigger_output_strobe(TEST_BASE_ADDRESS);
}

#endif // TEST
