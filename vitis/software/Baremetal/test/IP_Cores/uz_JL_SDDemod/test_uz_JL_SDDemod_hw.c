
#ifdef TEST

#include "unity.h"
#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_JL_SDDemod_hw.h"
#include "uz_JL_SDDemod_hwAddresses.h"

#define BASE_ADDRESS 0x00000000FU // random hex value that represents a fictional base address


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_JL_SDDemod_hw_write_dezi_U(void){
    uint16_t test_val=500;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+Dezimation_U_Data_uz_JL_SDDemod,test_val);
    uz_JL_SDDemod_hw_write_dezi_U(BASE_ADDRESS,test_val);
}

void test_uz_JL_SDDemod_hw_write_dezi_I(void){
    uint16_t test_val=500;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+Dezimation_I_Data_uz_JL_SDDemod,test_val);
    uz_JL_SDDemod_hw_write_dezi_I(BASE_ADDRESS,test_val);
}

void test_uz_JL_SDDemod_hw_write_switch_edge(void){
    bool test_val=true;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+switch_edge_Data_uz_JL_SDDemod,test_val);
    uz_JL_SDDemod_hw_write_switch_edge(BASE_ADDRESS,test_val);
}

void test_uz_JL_SDDemod_hw_write_clk_ratio(void){
    uint16_t test_val=100;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+clk_ratio_Data_uz_JL_SDDemod,test_val);
    uz_JL_SDDemod_hw_write_clk_ratio(BASE_ADDRESS,test_val);
}

void test_uz_JL_SDDemod_hw_read_data_out_ps_U(void){
    int32_t expect_val=30;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+data_out_ps_U_Data_uz_JL_SDDemod,expect_val);
    int32_t val_read=uz_JL_SDDemod_hw_read_data_out_ps_U(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}

void test_uz_JL_SDDemod_hw_read_data_out_ps_PH1(void)
{
    int32_t expect_val=30;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+data_out_ps_PH1_Data_uz_JL_SDDemod,expect_val);
    int32_t val_read=uz_JL_SDDemod_hw_read_data_out_ps_PH1(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}
void test_uz_JL_SDDemod_hw_read_data_out_ps_PH2(void)
{
    int32_t expect_val=30;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+data_out_ps_PH2_Data_uz_JL_SDDemod,expect_val);
    int32_t val_read=uz_JL_SDDemod_hw_read_data_out_ps_PH2(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}

void test_uz_JL_SDDemod_hw_read_data_out_ps_PH3(void)
{
    int32_t expect_val=30;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+data_out_ps_PH3_Data_uz_JL_SDDemod,expect_val);
    int32_t val_read=uz_JL_SDDemod_hw_read_data_out_ps_PH3(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}

void test_uz_JL_SDDemod_hw_read_data_out_ps_PH4(void)
{
    int32_t expect_val=30;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+data_out_ps_PH4_Data_uz_JL_SDDemod,expect_val);
    int32_t val_read=uz_JL_SDDemod_hw_read_data_out_ps_PH4(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}

#endif // TEST
