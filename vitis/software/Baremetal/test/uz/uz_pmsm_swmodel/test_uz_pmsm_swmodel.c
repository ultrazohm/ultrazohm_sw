#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm_swmodel.h"
#include "uz_PMSM_config.h"
#include "uz_struct_helper.h"
#include "uz_integrator.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsm_swmodel_test_init(void)
{
    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 10000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 0.5f,
            .Ld_Henry = 0.001f,
            .Lq_Henry = 0.0015f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 4.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f}};
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);
    TEST_ASSERT_NOT_NULL(model);
}

void test_uz_pmsm_swmodel_all_zeros(void)
{
    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 10000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 0.5f,
            .Ld_Henry = 0.001f,
            .Lq_Henry = 0.0015f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 4.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f}};
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);
    struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_d_V = 0.0f,
        .v_q_V = 0.0f,
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};
    struct uz_pmsm_swmodel_outputs_t outputs = uz_pmsm_swmodel_step(model, inputs);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.i_d_A);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.i_q_A);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.torque_Nm);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.omega_mech_1_s);
}


#define STEADY_STATE_ITERATIONS 10000U

void test_uz_pmsm_swmodel_steady_state(void)
{
    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 10000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 1.0f,
            .Ld_Henry = 0.001f,
            .Lq_Henry = 0.0015f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 4.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f}};
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);
    struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_d_V = 1.0f,
        .v_q_V = 0.5f,
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};

    struct uz_pmsm_swmodel_outputs_t outputs[STEADY_STATE_ITERATIONS] = {0};
    for (uint32_t i = 0U; i < STEADY_STATE_ITERATIONS; i++)
    {
        outputs[i] = uz_pmsm_swmodel_step(model, inputs);
    }
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_d_V / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_d_A);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_q_V / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_q_A);
    //TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[STEADY_STATE_ITERATIONS - 1].torque_Nm);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[STEADY_STATE_ITERATIONS - 1].omega_mech_1_s);
}

#endif // TEST
