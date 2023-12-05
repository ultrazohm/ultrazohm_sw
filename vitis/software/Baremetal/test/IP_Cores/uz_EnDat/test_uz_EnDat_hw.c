// "Copyright [year] <Copyright Owner>"
#ifdef TEST

#include "unity.h"  // NOLINT

#include "uz_EnDat_hw.h"

#include "test_assert_with_exception.h"  // NOLINT
#include "mock_uz_AXI.h"  // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_EnDat_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000FF0F  // random hex value that represents a fictional base address

void setUp(void) {
    // ARE WE STILL USING C?????
    // "Ceedling is primarily targeted at Test-Driven Development in C"
}

void tearDown(void) {
}


// WRITING

void test_uz_EnDat_hw_write_to_divider(void) {
    uint8_t a = 3;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+divider_Data_uz_EnDat, a);
    uz_EnDat_hw_write_divider(TEST_BASE_ADDRESS, a);


    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_divider(0, a))
}


void test_uz_EnDat_hw_write_to_FKT1DATAFLOW(void) {
    uint16_t a = 100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT1DATAFLOW_Data_uz_EnDat, a);
    uz_EnDat_hw_write_FKT1DATAFLOW(TEST_BASE_ADDRESS, a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT1DATAFLOW(0, a))
}

void test_uz_EnDat_hw_write_to_FKT2RECOVERYTIME(void) {
    uint16_t a = 100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT2RECOVERYTIME_Data_uz_EnDat, a);
    uz_EnDat_hw_write_FKT2RECOVERYTIME(TEST_BASE_ADDRESS, a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT2RECOVERYTIME(0, a))
}
void test_uz_EnDat_hw_write_to_FKT3INITIALOFF(void) {
    uint16_t a = 100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT3INITIALOFF_Data_uz_EnDat, a);
    uz_EnDat_hw_write_FKT3INITIALOFF(TEST_BASE_ADDRESS, a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT3INITIALOFF(0, a))
}
void test_uz_EnDat_hw_write_to_FKT4DATACLKSYNC(void) {
    uint16_t a = 100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT4DATACLKSYNC_Data_uz_EnDat, a);
    uz_EnDat_hw_write_FKT4DATACLKSYNC(TEST_BASE_ADDRESS, a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT4DATACLKSYNC(0, a))
}
void test_uz_EnDat_hw_write_to_FKT5TELEGRAMLEN(void) {
    uint16_t a = 100;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+FKT5TELEGRAMLEN_Data_uz_EnDat, a);
    uz_EnDat_hw_write_FKT5TELEGRAMLEN(TEST_BASE_ADDRESS, a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_FKT5TELEGRAMLEN(0, a))
}
void test_uz_EnDat_hw_write_to_controlword(void) {
    uint16_t a = 0xA807;
    // Test passes if uz_axi_write_int32 is called once with these arguments
    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+controlword_Data_uz_EnDat, a);
    uz_EnDat_hw_write_controlword(TEST_BASE_ADDRESS, a);

    // Tell the test that we do not care how often this function is called
    uz_axi_write_int32_Ignore();
    // Test passes if an assert fails in the function under test
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_write_controlword(0, a))
}

//// READING

void test_uz_EnDat_hw_read_from_statusword(void) {
    uint32_t c = 1;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+statusword_Data_uz_EnDat, c);
    uint32_t c_readback = uz_EnDat_hw_read_statusword(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_statusword(0));
}


void test_uz_EnDat_hw_read_from_POS0BUS(void) {
    uint32_t c = 2;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+POS0BUS_Data_uz_EnDat, c);
    uint32_t c_readback = uz_EnDat_hw_read_POS0BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_POS0BUS(0));
}


void test_uz_EnDat_hw_read_from_POS1BUS(void) {
    uint32_t c = 3;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+POS1BUS_Data_uz_EnDat, c);
    uint32_t c_readback = uz_EnDat_hw_read_POS1BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_POS1BUS(0));
}


void test_uz_EnDat_hw_read_from_POS2BUS(void) {
    uint32_t c = 4;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+POS2BUS_Data_uz_EnDat, c);
    uint32_t c_readback = uz_EnDat_hw_read_POS2BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_POS2BUS(0));
}



void test_uz_EnDat_hw_read_from_POS3BUS(void) {
    uint32_t c = 5;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+POS3BUS_Data_uz_EnDat, c);
    uint32_t c_readback = uz_EnDat_hw_read_POS3BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_POS3BUS(0));
}


void test_uz_EnDat_hw_read_from_POS4BUS(void) {
    uint32_t c = 6;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+POS4BUS_Data_uz_EnDat, c);
    uint32_t c_readback = uz_EnDat_hw_read_POS4BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_POS4BUS(0));
}


void test_uz_EnDat_hw_read_from_CRCFFSTORED(void) {
    uint8_t c = 7;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+CRCFFSTORED_Data_uz_EnDat, c);
    uint32_t c_readback = uz_EnDat_hw_read_CRCFFSTORED(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_CRCFFSTORED(0));
}


void test_uz_EnDat_hw_read_from_TIMEELASPEDT0T1BUS(void) {
    uint32_t c = 777;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+TIMEELASPEDT0T1BUS_Data_uz_EnDat, c);
    uint32_t c_readback = (uint32_t) uz_EnDat_hw_read_TIMEELASPEDT0T1BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_TIMEELASPEDT0T1BUS(0));
}

void test_uz_EnDat_hw_read_from_TIMEELASPEDT0T2BUS(void) {
    uint32_t c = 777;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+TIMEELASPEDT0T2BUS_Data_uz_EnDat, c);
    uint32_t c_readback = (uint32_t) uz_EnDat_hw_read_TIMEELASPEDT0T2BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_TIMEELASPEDT0T2BUS(0));
}

void test_uz_EnDat_hw_read_from_TIMEELASPEDT0T3BUS(void) {
    uint32_t c = 777;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+TIMEELASPEDT0T3BUS_Data_uz_EnDat, c);
    uint32_t c_readback = (uint32_t) uz_EnDat_hw_read_TIMEELASPEDT0T3BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_TIMEELASPEDT0T3BUS(0));
}

void test_uz_EnDat_hw_read_from_TIMEELASPEDT0T4BUS(void) {
    uint32_t c = 777;
    uz_axi_read_uint32_ExpectAndReturn(TEST_BASE_ADDRESS+TIMEELASPEDT0T4BUS_Data_uz_EnDat, c);
    uint32_t c_readback = (uint32_t) uz_EnDat_hw_read_TIMEELASPEDT0T4BUS(TEST_BASE_ADDRESS);
    TEST_ASSERT_EQUAL_INT(c, c_readback);

    // Ignores how often the read function is called and returns (c)
    uz_axi_read_uint32_IgnoreAndReturn(c);
    TEST_ASSERT_FAIL_ASSERT(uz_EnDat_hw_read_TIMEELASPEDT0T4BUS(0));
}


#endif  // TEST
