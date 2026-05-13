
#ifdef TEST

#include "unity.h"
#include "uz_Deadbeat_hw.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h"
#include "uz_Deadbeat_hwAddresses.h"
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000F

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_Deadbeat_hw_write_id_ref(void)
{
    int32_t id_ref = 1000;

    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS + id_ref_Data_uz_Deadbeat_ip, id_ref);

    uz_Deadbeat_hw_write_id_ref(TEST_BASE_ADDRESS, id_ref);
}

void test_uz_Deadbeat_hw_write_iq_ref(void)
{
    int32_t iq_ref = 2000;

    uz_axi_write_int32_Expect(TEST_BASE_ADDRESS + iq_ref_Data_uz_Deadbeat_ip, iq_ref);

    uz_Deadbeat_hw_write_iq_ref(TEST_BASE_ADDRESS, iq_ref);
}

void test_uz_Deadbeat_hw_read_ua_0(void)
{
    int32_t val = 555;

    uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS + ua_0_Data_uz_Deadbeat_ip, val);

    int32_t result = uz_Deadbeat_hw_read_ua_0(TEST_BASE_ADDRESS);

    TEST_ASSERT_EQUAL_INT32(val, result);
}

void test_uz_Deadbeat_hw_write_id_ref_zero_base(void)
{
    uz_axi_write_int32_Ignore();
    TEST_ASSERT_FAIL_ASSERT(uz_Deadbeat_hw_write_id_ref(0, 100));
}

void test_uz_Deadbeat_hw_read_ua_0_zero_base(void)
{
    uz_axi_read_int32_IgnoreAndReturn(0);
    TEST_ASSERT_FAIL_ASSERT(uz_Deadbeat_hw_read_ua_0(0));
}

#endif // TEST
