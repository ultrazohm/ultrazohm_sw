#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_ssi_interface_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address
#include "uz_ssi_interface_hw.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_ssi_interface_hw_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_ssi_interface_hw");
}

#endif // TEST
