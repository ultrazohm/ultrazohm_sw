#ifdef TEST

#include "unity.h"

#include "uz_signals.h"
TEST_FILE("uz_signals_iir_filter.c")
#include "uz_controller_setpoint_filter.h"
#include "test_assert_with_exception.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_signals_IIR_Filter_dq_setpoint(void){
    uz_3ph_dq_t setpoint = {0};
    TEST_ASSERT_FAIL_ASSERT(uz_signals_IIR_Filter_dq_setpoint(NULL, NULL, setpoint));
}

#endif // TEST
