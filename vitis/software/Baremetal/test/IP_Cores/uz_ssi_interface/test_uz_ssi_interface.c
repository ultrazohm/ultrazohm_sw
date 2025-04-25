#ifdef TEST

#include "test_assert_with_exception.h"
#include "uz_ssi_interface.h"
#include "mock_uz_ssi_interface_hw.h" // Mock the _hw functions to isolate testing
#include "unity.h"
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_ssi_interface_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_ssi_interface");
}

#endif // TEST
