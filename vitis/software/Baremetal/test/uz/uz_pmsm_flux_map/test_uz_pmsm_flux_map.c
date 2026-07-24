#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm_flux_map.h"
#include "uz_pmsm_flux_maps_auto_generated.h"

TEST_SOURCE_FILE("src/uz/uz_LUT_2D/uz_LUT_2D.c")

// Storage for the dummy_motor/nominal_v1 flux map (linear: psi_d = 0.002*i_d + 0.042, psi_q = 0.003*i_q).
// Non-const because uz_array_float_t stores a non-const float*, matching existing uz_LUT_2D usage.
static float id_breakpoints[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_D_BREAKPOINTS_A;
static float iq_breakpoints[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_Q_BREAKPOINTS_A;
static float psi_d_data[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_PSI_D_VS;
static float psi_q_data[] = UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_PSI_Q_VS;

static struct uz_pmsm_flux_map_config_t config = {0};

void setUp(void)
{
    config = (struct uz_pmsm_flux_map_config_t){
        .i_d_breakpoints_A = {.length = UZ_ARRAY_SIZE(id_breakpoints), .data = id_breakpoints},
        .i_q_breakpoints_A = {.length = UZ_ARRAY_SIZE(iq_breakpoints), .data = iq_breakpoints},
        .psi_d_Vs = {.length = UZ_ARRAY_SIZE(psi_d_data), .data = psi_d_data},
        .psi_q_Vs = {.length = UZ_ARRAY_SIZE(psi_q_data), .data = psi_q_data}};
}

void tearDown(void) {}

void test_uz_pmsm_flux_map_generated_dummy_grid_dimensions(void)
{
    TEST_ASSERT_EQUAL_UINT32(3U, UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_D_LENGTH);
    TEST_ASSERT_EQUAL_UINT32(3U, UZ_FLUXMAP_DUMMY_MOTOR_NOMINAL_V1_I_Q_LENGTH);
    TEST_ASSERT_EQUAL_UINT32(9U, UZ_ARRAY_SIZE(psi_d_data));
    TEST_ASSERT_EQUAL_UINT32(9U, UZ_ARRAY_SIZE(psi_q_data));
}

void test_uz_pmsm_flux_map_returns_exact_values_at_breakpoints(void)
{
    uz_pmsm_flux_map_t *self = uz_pmsm_flux_map_init(config);
    uz_3ph_dq_t psi = uz_pmsm_flux_map_get_psi_dq_Vs(self, (uz_3ph_dq_t){.d = 0.0f, .q = 0.0f});
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.042f, psi.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.0f, psi.q);

    psi = uz_pmsm_flux_map_get_psi_dq_Vs(self, (uz_3ph_dq_t){.d = -10.0f, .q = 10.0f});
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.022f, psi.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.03f, psi.q);
}

void test_uz_pmsm_flux_map_bilinear_interpolation_on_linear_grid(void)
{
    uz_pmsm_flux_map_t *self = uz_pmsm_flux_map_init(config);
    // Linear map -> bilinear interpolation is exact. At (i_d=5, i_q=5): psi_d=0.052, psi_q=0.015.
    uz_3ph_dq_t psi = uz_pmsm_flux_map_get_psi_dq_Vs(self, (uz_3ph_dq_t){.d = 5.0f, .q = 5.0f});
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.052f, psi.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.015f, psi.q);
}

void test_uz_pmsm_flux_map_single_axis_getters_match_dq_getter(void)
{
    uz_pmsm_flux_map_t *self = uz_pmsm_flux_map_init(config);
    uz_3ph_dq_t i_dq_A = {.d = 5.0f, .q = 5.0f};
    uz_3ph_dq_t psi = uz_pmsm_flux_map_get_psi_dq_Vs(self, i_dq_A);
    TEST_ASSERT_EQUAL_FLOAT(psi.d, uz_pmsm_flux_map_get_psi_d_Vs(self, i_dq_A));
    TEST_ASSERT_EQUAL_FLOAT(psi.q, uz_pmsm_flux_map_get_psi_q_Vs(self, i_dq_A));
    // Linear map -> exact values (psi_d = 0.052, psi_q = 0.015 at (5, 5)).
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.052f, uz_pmsm_flux_map_get_psi_d_Vs(self, i_dq_A));
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.015f, uz_pmsm_flux_map_get_psi_q_Vs(self, i_dq_A));
}

void test_uz_pmsm_flux_map_clamps_out_of_range_inputs(void)
{
    uz_pmsm_flux_map_t *self = uz_pmsm_flux_map_init(config);
    // Beyond the (10,10) corner -> clamped to the corner: psi_d=0.062, psi_q=0.03.
    uz_3ph_dq_t psi = uz_pmsm_flux_map_get_psi_dq_Vs(self, (uz_3ph_dq_t){.d = 100.0f, .q = 100.0f});
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.062f, psi.d);
    TEST_ASSERT_FLOAT_WITHIN(1e-6f, 0.03f, psi.q);
}

void test_uz_pmsm_flux_map_init_asserts_on_grid_length_mismatch(void)
{
    config.psi_d_Vs.length = UZ_ARRAY_SIZE(psi_d_data) - 1U;
    TEST_ASSERT_FAIL_ASSERT(uz_pmsm_flux_map_init(config));
}

void test_uz_pmsm_flux_map_init_asserts_on_null_data(void)
{
    config.psi_q_Vs.data = NULL;
    TEST_ASSERT_FAIL_ASSERT(uz_pmsm_flux_map_init(config));
}

#endif // TEST
