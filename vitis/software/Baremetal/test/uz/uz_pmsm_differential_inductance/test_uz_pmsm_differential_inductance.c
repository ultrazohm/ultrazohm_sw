#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm_differential_inductance.h"
#include "uz_pmsm_differential_inductances_auto_generated.h"

TEST_SOURCE_FILE("src/uz/uz_LUT_2D/uz_LUT_2D.c")

// Storage for the dummy_motor/nominal_v1 differential inductances. The dummy flux map is linear, so
// the differential inductances are constant: L_dd = 0.002, L_dq = 0, L_qd = 0, L_qq = 0.003.
// Non-const because uz_array_float_t stores a non-const float*, matching existing uz_LUT_2D usage.
static float id_breakpoints[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_I_D_BREAKPOINTS_A;
static float iq_breakpoints[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_I_Q_BREAKPOINTS_A;
static float L_dd_data[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_DD_H;
static float L_dq_data[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_DQ_H;
static float L_qd_data[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_QD_H;
static float L_qq_data[] = UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_L_QQ_H;

static struct uz_pmsm_differential_inductance_config_t config = {0};

void setUp(void)
{
    config = (struct uz_pmsm_differential_inductance_config_t){
        .i_d_breakpoints_A = {.length = UZ_ARRAY_SIZE(id_breakpoints), .data = id_breakpoints},
        .i_q_breakpoints_A = {.length = UZ_ARRAY_SIZE(iq_breakpoints), .data = iq_breakpoints},
        .L_dd_H = {.length = UZ_ARRAY_SIZE(L_dd_data), .data = L_dd_data},
        .L_dq_H = {.length = UZ_ARRAY_SIZE(L_dq_data), .data = L_dq_data},
        .L_qd_H = {.length = UZ_ARRAY_SIZE(L_qd_data), .data = L_qd_data},
        .L_qq_H = {.length = UZ_ARRAY_SIZE(L_qq_data), .data = L_qq_data}};
}

void tearDown(void) {}

void test_uz_pmsm_differential_inductance_generated_dummy_grid_dimensions(void)
{
    TEST_ASSERT_EQUAL_UINT32(3U, UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_I_D_LENGTH);
    TEST_ASSERT_EQUAL_UINT32(3U, UZ_DIFFIND_DUMMY_MOTOR_NOMINAL_V1_I_Q_LENGTH);
    TEST_ASSERT_EQUAL_UINT32(9U, UZ_ARRAY_SIZE(L_dd_data));
    TEST_ASSERT_EQUAL_UINT32(9U, UZ_ARRAY_SIZE(L_qq_data));
}

void test_uz_pmsm_differential_inductance_returns_expected_values_at_breakpoint(void)
{
    uz_pmsm_differential_inductance_t *self = uz_pmsm_differential_inductance_init(config);
    uz_3ph_dq_t i_dq_A = {.d = 0.0f, .q = 0.0f};
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.002f, uz_pmsm_differential_inductance_get_L_dd_H(self, i_dq_A));
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.0f, uz_pmsm_differential_inductance_get_L_dq_H(self, i_dq_A));
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.0f, uz_pmsm_differential_inductance_get_L_qd_H(self, i_dq_A));
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.003f, uz_pmsm_differential_inductance_get_L_qq_H(self, i_dq_A));
}

void test_uz_pmsm_differential_inductance_constant_map_is_interpolation_invariant(void)
{
    uz_pmsm_differential_inductance_t *self = uz_pmsm_differential_inductance_init(config);
    // Constant grid -> any interpolated point returns the same values.
    uz_3ph_dq_t i_dq_A = {.d = -3.7f, .q = 6.2f};
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.002f, uz_pmsm_differential_inductance_get_L_dd_H(self, i_dq_A));
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.003f, uz_pmsm_differential_inductance_get_L_qq_H(self, i_dq_A));
}

void test_uz_pmsm_differential_inductance_clamps_out_of_range_inputs(void)
{
    uz_pmsm_differential_inductance_t *self = uz_pmsm_differential_inductance_init(config);
    uz_3ph_dq_t i_dq_A = {.d = 1000.0f, .q = -1000.0f};
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.002f, uz_pmsm_differential_inductance_get_L_dd_H(self, i_dq_A));
    TEST_ASSERT_FLOAT_WITHIN(1e-7f, 0.003f, uz_pmsm_differential_inductance_get_L_qq_H(self, i_dq_A));
}

void test_uz_pmsm_differential_inductance_init_asserts_on_grid_length_mismatch(void)
{
    config.L_qq_H.length = UZ_ARRAY_SIZE(L_qq_data) - 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_pmsm_differential_inductance_init(config));
}

void test_uz_pmsm_differential_inductance_init_asserts_on_null_data(void)
{
    config.L_qd_H.data = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_pmsm_differential_inductance_init(config));
}

#endif // TEST
