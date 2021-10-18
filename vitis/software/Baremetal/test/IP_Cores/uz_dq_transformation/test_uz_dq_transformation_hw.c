#ifdef TEST

#include "unity.h"

#include "uz_dq_transformation_hw.h"

#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)
#include "uz_dq_transformation_hwAddresses.h"
#define TEST_BASE_ADDRESS 0x00000000F // random hex value that represents a fictional base address

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_dq_transformation_hw_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_dq_transformation_hw");
}

#endif // TEST
