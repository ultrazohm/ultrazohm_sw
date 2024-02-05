#ifdef TEST

#include "unity.h"

#include "uz_pmsm_r_fe.h"
TEST_FILE("uz_pmsm_rfe_data.c")
#include "uz_pmsm_rfe_ert_rtw/uz_pmsm_rfe.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsm_rfe_NeedToImplement(void)
{
    uz_pmsm_r_fe_init();
}

#endif // TEST
