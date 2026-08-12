#ifdef TEST
#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_IM_config.h"

static uz_IM_t valid_config = {
    .Rs_Ohm = 2.0f,
    .Rr_Ohm = 1.5f,
    .Lsigma_s_Henry = 0.01f,
    .Lsigma_r_Henry = 0.01f,
    .Lm_Henry = 0.2f,
    .polePairs = 2.0f,
    .J_kg_m_squared = 0.01f,
    .I_max_Ampere = 10.0f,
    .Psi_rated_Vs = 0.5f
};

void setUp(void) {}
void tearDown(void) {}

void test_uz_IM_config_assert_accepts_valid_config(void) {
    TEST_ASSERT_PASS_ASSERT(uz_IM_config_assert(valid_config));
}

void test_uz_IM_config_assert_rejects_zero_stator_resistance(void) {
    uz_IM_t config = valid_config;
    config.Rs_Ohm = 0.0f;
    TEST_ASSERT_FAIL_ASSERT(uz_IM_config_assert(config));
}

void test_uz_IM_config_derived_values(void) {
    TEST_ASSERT_EQUAL_FLOAT(0.21f, uz_IM_config_get_Ls(valid_config));
    TEST_ASSERT_EQUAL_FLOAT(0.21f, uz_IM_config_get_Lr(valid_config));
    TEST_ASSERT_TRUE(uz_IM_config_get_sigma(valid_config) > 0.0f);
    TEST_ASSERT_EQUAL_FLOAT(0.14f, uz_IM_config_get_rotor_time_constant(valid_config));
}
#endif
