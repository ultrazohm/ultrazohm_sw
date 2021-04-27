#ifdef TEST

#include "unity.h"
#include <stdint.h>
#include "uz_axiTestIP2_hw.h"
#include "mock_uz_AXI.h"

#define base_address 0x0000000F
void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_axiTestIP2_hw_write_to_A_int32(void)
{
    int a=10;
    uz_axi_write_int32_Expect(base_address+A_int32_Data_uz_axi_testIP, a);
    uz_axiTestIP2_hw_write_A_int32(base_address,a);
}

void test_uz_axiTestIP2_hw_write_to_B_int32(void)
{
    int b=10;
    uz_axi_write_int32_Expect(base_address+B_int32_Data_uz_axi_testIP, b);
    uz_axiTestIP2_hw_write_B_int32(base_address,b);
}


void test_uz_axiTestIP2_hw_read_C_int32(void)
{
    int a=20;
    int b=-10;
    uz_axi_read_int32_ExpectAndReturn(base_address+C_int32_Data_uz_axi_testIP,a*b);
    int c=uz_axiTestIP2_hw_read_C_int32(base_address);
    TEST_ASSERT_EQUAL_INT(a*b,c);
}

#endif // TEST
