#ifdef TEST

#include "unity.h"

#include "uz_Space_Vector_Modulation_6ph.h"
#include "uz_Space_Vector_Modulation_6ph.c"
#include "../uz_HAL.h"
#include "../uz_complex/uz_complex.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_math_constants.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_svm_6ph_get_sector(void)
{
    int sector = uz_svm_6ph_get_sector(0.1f, 0.01f);
    TEST_ASSERT_EQUAL(1, sector);

}

#endif // TEST
