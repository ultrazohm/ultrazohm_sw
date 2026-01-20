#ifdef TEST

#include "unity.h"

#include "uz_adcMax11331.h"
#include "mock_uz_adcMax11331_hw.h"
#include <stdint.h>
#include "../../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "test_assert_with_exception.h"
#include "mock_uz_AXI.h" // Tells Ceedling to create mock versions of the functions in uz_AXI (e.g., _Expect)

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_adcMax11331_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_adcMax11331");
}

#endif // TEST
