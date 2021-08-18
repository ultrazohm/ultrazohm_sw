#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_PMSM_config.h"

struct uz_PMSM_t config = {0};
void setUp(void)
{
    config.R_ph_Ohm = 0.08f;
    config.Ld_Henry = 0.00027f;
    config.Lq_Henry = 0.00027f;
    config.Psi_PM_Vs = 0.0082f;
    config.polePairs = 4.0f;
    config.J_kg_m_squared = 0.00001773f;
}


void test_uz_PMSM_config_assert_R_ph(void){
    setUp();
    config.R_ph_Ohm = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.R_ph_Ohm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_Ld(void){
    setUp();
    config.Ld_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.Ld_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_Lq(void){
    setUp();
    config.Lq_Henry = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.Lq_Henry = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_Psi_PM(void){
    setUp();
    config.Psi_PM_Vs = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_polePairs(void){
    setUp();
    config.polePairs = -2.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.polePairs = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.polePairs = 0.5f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}

void test_uz_PMSM_config_assert_J(void){
    setUp();
    config.J_kg_m_squared = -0.08f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
    config.J_kg_m_squared = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_PMSM_config_assert(config));
}
#endif // TEST
