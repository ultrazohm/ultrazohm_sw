
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

void test_uz_JL_SDDemod_hw_write_R_axi(void){
    uint16_t test_val=500;
    uz_axi_write_uint32_Expect(BASE_ADDRESS+R_axi_Data_uz_JL_SDDemod,test_val);
    uz_JL_SDDemod_hw_write_R_axi(BASE_ADDRESS,test_val);
}

void test_uz_JL_SDDemod_hw_read_data(void)
{
    int32_t expect_val=30;
    uz_axi_read_int32_ExpectAndReturn(BASE_ADDRESS+data_out_ps_Data_uz_JL_SDDemod,expect_val);
    int32_t val_read=uz_JL_SDDemod_hw_read_data(BASE_ADDRESS);
    TEST_ASSERT_EQUAL_FLOAT(expect_val,val_read);
}
#endif // TEST
