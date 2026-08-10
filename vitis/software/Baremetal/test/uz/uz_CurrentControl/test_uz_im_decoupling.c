#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_im_decoupling.h"

static uz_IM_t im_config;
static uz_3ph_dq_t current;

void setUp(void)
{
    im_config = (uz_IM_t){
        .Rs_Ohm = 0.5f,
        .Rr_Ohm = 0.4f,
        .Lsigma_s_Henry = 0.01f,
        .Lsigma_r_Henry = 0.015f,
        .Lm_Henry = 0.1f,
        .polePairs = 2.0f,
        .J_kg_m_squared = 0.01f,
        .I_max_Ampere = 10.0f,
        .Psi_rated_Vs = 0.5f,
    };
    current = (uz_3ph_dq_t){.d = 2.0f, .q = 3.0f, .zero = 0.0f};
}

void tearDown(void) {}

void test_uz_CurrentControl_IM_decoupling_positive_speed(void)
{
    uz_3ph_dq_t const output =
        uz_CurrentControl_IM_decoupling(im_config, current, 100.0f, 0.5f);

    TEST_ASSERT_FLOAT_WITHIN(1.0e-4f, -6.9130435f, output.d);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-4f, 48.0869565f, output.q);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.zero);
}

void test_uz_CurrentControl_IM_decoupling_negative_speed_changes_sign(void)
{
    uz_3ph_dq_t const output =
        uz_CurrentControl_IM_decoupling(im_config, current, -100.0f, 0.5f);

    TEST_ASSERT_FLOAT_WITHIN(1.0e-4f, 6.9130435f, output.d);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-4f, -48.0869565f, output.q);
}

void test_uz_CurrentControl_IM_decoupling_zero_speed_is_zero(void)
{
    uz_3ph_dq_t const output =
        uz_CurrentControl_IM_decoupling(im_config, current, 0.0f, 0.5f);

    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.d);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, output.q);
}

void test_uz_CurrentControl_IM_decoupling_rejects_negative_flux(void)
{
    TEST_ASSERT_FAIL_ASSERT(
        uz_CurrentControl_IM_decoupling(im_config, current, 100.0f, -0.1f));
}

#endif
