#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_IM_config.h"

void setUp(void) {}
void tearDown(void) {}

void test_uz_IM_config_get_selected_motor_matches_selected_preset(void)
{
    uz_IM_t const config = uz_IM_config_get_selected_motor();

    TEST_ASSERT_EQUAL_FLOAT(MOTOR_Rs_Ohm, config.Rs_Ohm);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_Rr_Ohm, config.Rr_Ohm);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_Lsigma_s_H, config.Lsigma_s_Henry);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_Lsigma_r_H, config.Lsigma_r_Henry);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_Lm_H, config.Lm_Henry);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_PolePairs, config.polePairs);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_J_kgm2, config.J_kg_m_squared);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_Control_current_max_A, config.I_max_Ampere);
    TEST_ASSERT_EQUAL_FLOAT(MOTOR_Psi_rated_Vs, config.Psi_rated_Vs);
}

void test_uz_IM_config_get_selected_motor_is_valid(void)
{
    uz_IM_t const config = uz_IM_config_get_selected_motor();
    TEST_ASSERT_PASS_ASSERT(uz_IM_config_assert(config));
}

#endif
