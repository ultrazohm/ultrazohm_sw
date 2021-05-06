#ifdef TEST

#include "unity.h"
#include "uz_wavegen.h"
#include <math.h>
#include "mock_uz_SystemTime.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_wavegen_NeedToImplement(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement uz_wavegen");
    uz_SystemTime_GetGlobalTimeInSec_ExpectAndReturn(1);
}

#endif // TEST
