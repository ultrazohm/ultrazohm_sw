#ifdef TEST

#include "unity.h"

#include "uz_axiTestIP.h"

#include "uz_axiTestIP.h"
#include "uz_axiTestIP_private.h"
#include "uz_axiTestIP_hwAddresses.h"
#include "mock_uz_AXI.h"

#define TEST_BASE_ADDRESS 0x000F0000

static uz_axiTestIP axiTestIP_instance1 =
                	{
	                 .base_address = TEST_BASE_ADDRESS,
	                };

uz_axiTestIP_handle uz_axiTestIP_staticAllocator(void) {
	return (uz_axiTestIP_init(&axiTestIP_instance1));
}


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_axiTestIP_NeedToImplement(void)
{
    //TEST_IGNORE_MESSAGE("Need to Implement uz_axiTestIP");
	int testvalue=10;
	uz_axiTestIP_handle test=uz_axiTestIP_staticAllocator();
	uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+B_int32_Data_uz_axi_testIP,testvalue);
	uz_axiTestIP_set_B_int32(test, testvalue);
	uz_axi_write_int32_Expect(TEST_BASE_ADDRESS+A_int32_Data_uz_axi_testIP,testvalue);
	uz_axiTestIP_set_A_int32(test, testvalue);
	uz_axi_read_int32_ExpectAndReturn(TEST_BASE_ADDRESS+C_int32_Data_uz_axi_testIP,testvalue*testvalue);
	uz_axiTestIP_get_C_int32(test);

}

#endif // TEST
