#ifdef TEST

#include "unity.h"

#include "uz_EnDat_hw.h"

#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_EnDat_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
    //ARE WE STILL USING C?????
    //"Ceedling is primarily targeted at Test-Driven Development in C"
}

void tearDown(void)
{
}


//WRITING

void test_uz_EnDat_hw_write_to_divider(void)
{
    int a=3;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+divider_Data_uz_EnDat,a);
    uz_EnDat_hw_write_divider(TEST_BASE_ADDRESS,a);

    
    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_divider(0,a))

}


void test_uz_EnDat_hw_write_to_FKT1DATAFLOW(void)
{
    int a=100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT1DATAFLOW_Data_uz_EnDat,a);
    uz_EnDat_hw_write_FKT1DATAFLOW(TEST_BASE_ADDRESS,a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT1DATAFLOW(0,a))
}

void test_uz_EnDat_hw_write_to_FKT2RECOVERYTIME(void)
{
    int a=100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT2RECOVERYTIME_Data_uz_EnDat,a);
    uz_EnDat_hw_write_FKT2RECOVERYTIME(TEST_BASE_ADDRESS,a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT2RECOVERYTIME(0,a))
}
void test_uz_EnDat_hw_write_to_FKT3INITIALOFF(void)
{
    int a=100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT3INITIALOFF_Data_uz_EnDat,a);
    uz_EnDat_hw_write_FKT3INITIALOFF(TEST_BASE_ADDRESS,a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT3INITIALOFF(0,a))

}
void test_uz_EnDat_hw_write_to_FKT4DATACLKSYNC(void)
{
    int a=100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT4DATACLKSYNC_Data_uz_EnDat,a);
    uz_EnDat_hw_write_FKT4DATACLKSYNC(TEST_BASE_ADDRESS,a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT4DATACLKSYNC(0,a))

}
void test_uz_EnDat_hw_write_to_FKT5TELEGRAMLEN(void)
{
    int a=100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT5TELEGRAMLEN_Data_uz_EnDat,a);
    uz_EnDat_hw_write_FKT5TELEGRAMLEN(TEST_BASE_ADDRESS,a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT5TELEGRAMLEN(0,a))

}
void test_uz_EnDat_hw_write_to_controlword(void)
{
    int a=0xA807;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+controlword_Data_uz_EnDat,a);
    uz_EnDat_hw_write_controlword(TEST_BASE_ADDRESS,a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_controlword(0,a))


}

////READING

void test_uz_myIP_hw_read_from_C(void)
/*{
    int c=101230;
    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+C_int32_Data_uz_axi_testIP,c);
    int c_readback=uz_myIP_hw_read_C(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c,c_readback);
}*/


#endif // TEST
