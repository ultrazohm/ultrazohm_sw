#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_temperaturecard.h"
#include "mock_uz_temperaturecard_hw.h" // Mock the _hw functions to isolate testing
#include <stdint.h>

#define TEST_BASE_ADDRESS 0x0000000A
#define TEST_IP_CORE_FRQ 100000000U

#include "uz_temperaturecard.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_temperaturecard_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_temperaturecard");
}

#endif // TEST
