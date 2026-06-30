#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"
#include "uz_pmsm_swmodel.h"
#include "uz_PMSM_config.h"
#include "uz_struct_helper.h"
#include "uz_integrator.h"
#include "uz_Transformation.h"
#include <stddef.h>
#include <stdio.h>

#include "export_struct_to_csv.h"

#define CSV_EXPORT 1

#define CSV_FIELD_DESCRIPTOR(struct_type, field_name, field_type) \
    {#field_name, offsetof(struct_type, field_name), field_type}

#define CSV_NESTED_FIELD_DESCRIPTOR(struct_type, nested_struct, field_name, field_type) \
    {#field_name, offsetof(struct_type, nested_struct) + offsetof(struct uz_PMSM_t, field_name), field_type}

#define CSV_DQ_FIELD_DESCRIPTOR(struct_type, nested_struct, field_name, field_type) \
    {#field_name, offsetof(struct_type, nested_struct) + offsetof(uz_3ph_dq_t, field_name), field_type}

#define UZ_PMSM_SWMODEL_RESULTS_CSV_PATH "../../../docs/ceedling_test_output/uz/uz_pmsm_swmodel/uz_pmsm_swmodel_results.csv"
#define UZ_PMSM_SWMODEL_CONFIG_CSV_PATH "../../../docs/ceedling_test_output/uz/uz_pmsm_swmodel/uz_pmsm_swmodel_config.csv"

const struct csv_field_descriptor_t output_fields[] = {
    CSV_DQ_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, i_dq_A, d, CSV_FIELD_FLOAT),
    CSV_DQ_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, i_dq_A, q, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, torque_Nm, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, omega_mech_1_s, CSV_FIELD_FLOAT)};

const struct csv_field_descriptor_t input_fields[] = {
    CSV_DQ_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_inputs_t, v_dq_V, d, CSV_FIELD_FLOAT),
    CSV_DQ_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_inputs_t, v_dq_V, q, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_inputs_t, omega_mech_1_s, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_inputs_t, load_torque, CSV_FIELD_FLOAT)};

const struct csv_field_descriptor_t config_fields[] = {
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, sample_time, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, pmsm_parameters, R_ph_Ohm, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, pmsm_parameters, Ld_Henry, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, pmsm_parameters, Lq_Henry, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, pmsm_parameters, Psi_PM_Vs, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, pmsm_parameters, polePairs, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, pmsm_parameters, J_kg_m_squared, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_config_t, pmsm_parameters, I_max_Ampere, CSV_FIELD_FLOAT)};

static const struct csv_field_descriptor_t empty_fields[] = {{NULL, 0U, CSV_FIELD_FLOAT}};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_uz_pmsm_swmodel_test_init(void)
{
    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 20000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 2.1f,
            .Ld_Henry = 0.03f,
            .Lq_Henry = 0.05f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 2.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f,
            .machine_id = 0U,
            .I_rated_Ampere = 8.0f,
            .Torque_rated_Nm = 1.2f,
            .Torque_max_Nm = 2.0f,
            .Torque_min_Nm = -2.0f,
            .speed_rated_rpm = 1000.0f,
            .speed_max_rpm = 1500.0f,
            .speed_min_rpm = -1500.0f,
            .V_dc_nominal_V = 24.0f,
            .I_d_max_A = 10.0f,
            .I_d_min_A = -10.0f,
            .I_q_max_A = 10.0f,
            .I_q_min_A = -10.0f}};
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
            .I_max_Ampere = 10.0f,
            .machine_id = 0U,
            .I_rated_Ampere = 8.0f,
            .Torque_rated_Nm = 1.2f,
            .Torque_max_Nm = 2.0f,
            .Torque_min_Nm = -2.0f,
            .speed_rated_rpm = 1000.0f,
            .speed_max_rpm = 1500.0f,
            .speed_min_rpm = -1500.0f,
            .V_dc_nominal_V = 24.0f,
            .I_d_max_A = 10.0f,
            .I_d_min_A = -10.0f,
            .I_q_max_A = 10.0f,
            .I_q_min_A = -10.0f}};
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);
    struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 0.0f, .q = 0.0f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};
    struct uz_pmsm_swmodel_outputs_t outputs = uz_pmsm_swmodel_step(model, inputs);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.i_dq_A.d);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.i_dq_A.q);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.torque_Nm);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs.omega_mech_1_s);
}

void test_uz_pmsm_swmodel_steady_state_standstill(void)
{
    enum
    {
        STEADY_STATE_ITERATIONS = 1000U
    };

    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 10000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 1.0f,
            .Ld_Henry = 0.001f,
            .Lq_Henry = 0.0015f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 4.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f,
            .machine_id = 0U,
            .I_rated_Ampere = 8.0f,
            .Torque_rated_Nm = 1.2f,
            .Torque_max_Nm = 2.0f,
            .Torque_min_Nm = -2.0f,
            .speed_rated_rpm = 1000.0f,
            .speed_max_rpm = 1500.0f,
            .speed_min_rpm = -1500.0f,
            .V_dc_nominal_V = 24.0f,
            .I_d_max_A = 10.0f,
            .I_d_min_A = -10.0f,
            .I_q_max_A = 10.0f,
            .I_q_min_A = -10.0f}};

    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);

    struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 1.0f, .q = 0.5f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};
    struct uz_pmsm_swmodel_inputs_t inputs_k[STEADY_STATE_ITERATIONS] = {0};
    struct uz_pmsm_swmodel_outputs_t outputs[STEADY_STATE_ITERATIONS] = {0};

    inputs_k[0] = inputs;
    for (uint32_t i = 0U; i < STEADY_STATE_ITERATIONS; i++)
    {
        inputs_k[i] = inputs;
        outputs[i] = uz_pmsm_swmodel_step(model, inputs_k[i]);
    }
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_dq_V.d / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_dq_A.d);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_dq_V.q / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_dq_A.q);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[STEADY_STATE_ITERATIONS - 1].omega_mech_1_s);

#if CSV_EXPORT
    export_input_output_arrays_to_csv(UZ_PMSM_SWMODEL_RESULTS_CSV_PATH, inputs_k, sizeof(inputs_k[0]), input_fields, sizeof(input_fields) / sizeof(input_fields[0]), outputs, sizeof(outputs[0]), output_fields, sizeof(output_fields) / sizeof(output_fields[0]), STEADY_STATE_ITERATIONS, config.sample_time);
    export_input_output_arrays_to_csv(UZ_PMSM_SWMODEL_CONFIG_CSV_PATH, &config, sizeof(config), empty_fields, 0U, &config, sizeof(config), config_fields, sizeof(config_fields) / sizeof(config_fields[0]), 1U, 0.0f);
#endif
}

void test_uz_pmsm_swmodel_zero_after_reset(void)
{
    enum
    {
        STEADY_STATE_ITERATIONS = 1000U
    };

    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 10000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 1.0f,
            .Ld_Henry = 0.001f,
            .Lq_Henry = 0.0015f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 4.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f,
            .machine_id = 0U,
            .I_rated_Ampere = 8.0f,
            .Torque_rated_Nm = 1.2f,
            .Torque_max_Nm = 2.0f,
            .Torque_min_Nm = -2.0f,
            .speed_rated_rpm = 1000.0f,
            .speed_max_rpm = 1500.0f,
            .speed_min_rpm = -1500.0f,
            .V_dc_nominal_V = 24.0f,
            .I_d_max_A = 10.0f,
            .I_d_min_A = -10.0f,
            .I_q_max_A = 10.0f,
            .I_q_min_A = -10.0f}};

    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);

    struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 1.0f, .q = 0.5f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};
    struct uz_pmsm_swmodel_inputs_t inputs_k[STEADY_STATE_ITERATIONS] = {0};
    struct uz_pmsm_swmodel_outputs_t outputs[STEADY_STATE_ITERATIONS] = {0};

    inputs_k[0] = inputs;
    for (uint32_t i = 0U; i < STEADY_STATE_ITERATIONS; i++)
    {
        inputs_k[i] = inputs;
        outputs[i] = uz_pmsm_swmodel_step(model, inputs_k[i]);
    }
    // Not zero after reset
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_dq_V.d / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_dq_A.d);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_dq_V.q / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_dq_A.q);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[STEADY_STATE_ITERATIONS - 1].omega_mech_1_s);

    // Zero after reset
    inputs.v_dq_V.d = 0.0f;
    inputs.v_dq_V.q = 0.0f;
    inputs.v_dq_V.zero = 0.0f;
    inputs.omega_mech_1_s = 0.0f;
    uz_pmsm_swmodel_reset(model);
    struct uz_pmsm_swmodel_outputs_t outputs_after_reset = uz_pmsm_swmodel_step(model, inputs);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs_after_reset.i_dq_A.d);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs_after_reset.i_dq_A.q);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs_after_reset.torque_Nm);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs_after_reset.omega_mech_1_s);
}

void test_uz_pmsm_swmodel_steady_state_zero_voltage_zero_speed(void)
{
    enum
    {
        STEADY_STATE_ITERATIONS = 1000U
    };

    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 10000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 1.0f,
            .Ld_Henry = 0.001f,
            .Lq_Henry = 0.0015f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 4.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f,
            .machine_id = 0U,
            .I_rated_Ampere = 8.0f,
            .Torque_rated_Nm = 1.2f,
            .Torque_max_Nm = 2.0f,
            .Torque_min_Nm = -2.0f,
            .speed_rated_rpm = 1000.0f,
            .speed_max_rpm = 1500.0f,
            .speed_min_rpm = -1500.0f,
            .V_dc_nominal_V = 24.0f,
            .I_d_max_A = 10.0f,
            .I_d_min_A = -10.0f,
            .I_q_max_A = 10.0f,
            .I_q_min_A = -10.0f}};

    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);

    struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 0.0f, .q = 0.0f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};
    struct uz_pmsm_swmodel_inputs_t inputs_k[STEADY_STATE_ITERATIONS] = {0};
    struct uz_pmsm_swmodel_outputs_t outputs[STEADY_STATE_ITERATIONS] = {0};

    inputs_k[0] = inputs;
    for (uint32_t i = 0U; i < STEADY_STATE_ITERATIONS; i++)
    {
        inputs_k[i] = inputs;
        outputs[i] = uz_pmsm_swmodel_step(model, inputs_k[i]);
    }

    for (uint32_t i = 0U; i < STEADY_STATE_ITERATIONS; i++)
    {
        TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[i].i_dq_A.d);
        TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[i].i_dq_A.q);
        TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[i].omega_mech_1_s);
        TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[i].torque_Nm);
    }
}

void test_uz_pmsm_swmodel_steady_state_rotating_no_voltage(void)
{
    enum
    {
        // With the (IP-core) machine parameters the electrical time constants are L/R ~ 14-24 ms;
        // run long enough (0.15 s) to actually reach the asserted steady state.
        STEADY_STATE_ITERATIONS = 3000U
    };

    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 20000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 2.1f,
            .Ld_Henry = 0.03f,
            .Lq_Henry = 0.05f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 2.0f,
            .J_kg_m_squared = 0.0001f,
            .I_max_Ampere = 10.0f,
            .machine_id = 0U,
            .I_rated_Ampere = 8.0f,
            .Torque_rated_Nm = 1.2f,
            .Torque_max_Nm = 2.0f,
            .Torque_min_Nm = -2.0f,
            .speed_rated_rpm = 1000.0f,
            .speed_max_rpm = 1500.0f,
            .speed_min_rpm = -1500.0f,
            .V_dc_nominal_V = 24.0f,
            .I_d_max_A = 10.0f,
            .I_d_min_A = -10.0f,
            .I_q_max_A = 10.0f,
            .I_q_min_A = -10.0f}};

    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);

    struct uz_pmsm_swmodel_inputs_t inputs = {
        // No applied voltage: this validates the rotating short-circuit steady state, which is what
        // expected_i_d_A / expected_i_q_A below derive (a nonzero v_dq shifts that operating point).
        .v_dq_V = {.d = 0.0f, .q = 0.0f, .zero = 0.0f},
        .omega_mech_1_s = 100.0f,
        .load_torque = 0.0f};
    struct uz_pmsm_swmodel_inputs_t inputs_k[STEADY_STATE_ITERATIONS] = {0};
    struct uz_pmsm_swmodel_outputs_t outputs[STEADY_STATE_ITERATIONS] = {0};

    inputs_k[0] = inputs;
    for (uint32_t i = 0U; i < STEADY_STATE_ITERATIONS; i++)
    {
        inputs_k[i] = inputs;
        outputs[i] = uz_pmsm_swmodel_step(model, inputs_k[i]);
    }
    const float omega_el_1_s = inputs.omega_mech_1_s * config.pmsm_parameters.polePairs;
    const float resistance = config.pmsm_parameters.R_ph_Ohm;
    const float denominator = 1.0f + ((omega_el_1_s * omega_el_1_s * config.pmsm_parameters.Ld_Henry * config.pmsm_parameters.Lq_Henry) / (resistance * resistance));
    const float expected_i_q_A = -(omega_el_1_s * config.pmsm_parameters.Psi_PM_Vs / resistance) / denominator;
    const float expected_i_d_A = (omega_el_1_s * config.pmsm_parameters.Lq_Henry / resistance) * expected_i_q_A;
    const float expected_psi_d_Vs = config.pmsm_parameters.Ld_Henry * expected_i_d_A + config.pmsm_parameters.Psi_PM_Vs;
    const float expected_psi_q_Vs = config.pmsm_parameters.Lq_Henry * expected_i_q_A;
    const float expected_torque_Nm = 1.5f * config.pmsm_parameters.polePairs * (expected_psi_d_Vs * expected_i_q_A - expected_psi_q_Vs * expected_i_d_A);

    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_i_d_A, outputs[STEADY_STATE_ITERATIONS - 1].i_dq_A.d);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_i_q_A, outputs[STEADY_STATE_ITERATIONS - 1].i_dq_A.q);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.omega_mech_1_s, outputs[STEADY_STATE_ITERATIONS - 1].omega_mech_1_s);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, expected_torque_Nm, outputs[STEADY_STATE_ITERATIONS - 1].torque_Nm);

#if CSV_EXPORT
    export_input_output_arrays_to_csv("../../../docs/ceedling_test_output/uz/uz_pmsm_swmodel/uz_pmsm_swmodel_results_steady_state_rotating_no_voltage.csv", inputs_k, sizeof(inputs_k[0]), input_fields, sizeof(input_fields) / sizeof(input_fields[0]), outputs, sizeof(outputs[0]), output_fields, sizeof(output_fields) / sizeof(output_fields[0]), STEADY_STATE_ITERATIONS, config.sample_time);
#endif
}

// A valid base configuration (matches the IP-core machine parameters: Ld != Lq so the
// flux/current equivalence is a non-trivial check). Tests tweak the fields they care about.
static struct uz_pmsm_swmodel_config_t base_swmodel_config(void)
{
    struct uz_pmsm_swmodel_config_t config = {
        .sample_time = 1.0f / 20000.0f,
        .pmsm_parameters = {
            .R_ph_Ohm = 2.1f,
            .Ld_Henry = 0.03f,
            .Lq_Henry = 0.05f,
            .Psi_PM_Vs = 0.05f,
            .polePairs = 2.0f,
            .J_kg_m_squared = 0.001f,
            .I_max_Ampere = 10.0f,
            .machine_id = 0U,
            .I_rated_Ampere = 8.0f,
            .Torque_rated_Nm = 1.2f,
            .Torque_max_Nm = 2.0f,
            .Torque_min_Nm = -2.0f,
            .speed_rated_rpm = 1000.0f,
            .speed_max_rpm = 1500.0f,
            .speed_min_rpm = -1500.0f,
            .V_dc_nominal_V = 24.0f,
            .I_d_max_A = 10.0f,
            .I_d_min_A = -10.0f,
            .I_q_max_A = 10.0f,
            .I_q_min_A = -10.0f}};
    return config;
}

// Drives identical inputs through a current-state and a flux-state model and asserts they
// produce the same currents and torque for the given integration method (constant-L equivalence).
static void assert_flux_matches_current(enum uz_pmsm_swmodel_integration_method_t method)
{
    struct uz_pmsm_swmodel_config_t config = base_swmodel_config();
    config.integration_method = method;
    config.integrator_state = uz_pmsm_swmodel_integrator_state_current;
    uz_pmsm_swmodel_t *current_model = uz_pmsm_swmodel_init(config);
    config.integrator_state = uz_pmsm_swmodel_integrator_state_flux;
    uz_pmsm_swmodel_t *flux_model = uz_pmsm_swmodel_init(config);

    const struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = -2.0f, .q = 5.0f, .zero = 0.0f},
        .omega_mech_1_s = 50.0f,
        .load_torque = 0.0f};

    for (uint32_t i = 0U; i < 1000U; i++)
    {
        const struct uz_pmsm_swmodel_outputs_t current_out = uz_pmsm_swmodel_step(current_model, inputs);
        const struct uz_pmsm_swmodel_outputs_t flux_out = uz_pmsm_swmodel_step(flux_model, inputs);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, current_out.i_dq_A.d, flux_out.i_dq_A.d);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, current_out.i_dq_A.q, flux_out.i_dq_A.q);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, current_out.torque_Nm, flux_out.torque_Nm);
    }
}

void test_uz_pmsm_swmodel_flux_state_matches_current_state_euler(void)
{
    assert_flux_matches_current(uz_pmsm_swmodel_euler_forward);
}

void test_uz_pmsm_swmodel_flux_state_matches_current_state_heun(void)
{
    assert_flux_matches_current(uz_pmsm_swmodel_heun);
}

void test_uz_pmsm_swmodel_mechanical_speed_ramps_up_and_passthrough_when_off(void)
{
    enum { ITERATIONS = 2000U };
    // Friction-free, no load: a positive q-voltage from rest must spin the rotor up.
    struct uz_pmsm_swmodel_config_t config = base_swmodel_config();
    config.simulate_mechanical_system = true;
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);

    const struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 0.0f, .q = 5.0f, .zero = 0.0f},
        .omega_mech_1_s = 999.0f, // ignored while simulating
        .load_torque = 0.0f};

    float omega_early = 0.0f;
    float omega_final = 0.0f;
    for (uint32_t i = 0U; i < ITERATIONS; i++)
    {
        const struct uz_pmsm_swmodel_outputs_t out = uz_pmsm_swmodel_step(model, inputs);
        if (i == 100U)
        {
            omega_early = out.omega_mech_1_s;
        }
        omega_final = out.omega_mech_1_s;
    }
    TEST_ASSERT_TRUE(omega_early > 0.0f);            // accelerated from rest
    TEST_ASSERT_TRUE(omega_final > omega_early);     // still speeding up
    TEST_ASSERT_TRUE(omega_final < 999.0f);          // input speed was ignored, not passed through

    // With the mechanical system off, the input speed is passed straight through.
    config.simulate_mechanical_system = false;
    uz_pmsm_swmodel_t *passthrough_model = uz_pmsm_swmodel_init(config);
    const struct uz_pmsm_swmodel_outputs_t passthrough_out = uz_pmsm_swmodel_step(passthrough_model, inputs);
    TEST_ASSERT_EQUAL_FLOAT(999.0f, passthrough_out.omega_mech_1_s);
}

void test_uz_pmsm_swmodel_mechanical_angular_impulse_equals_momentum(void)
{
    enum { ITERATIONS = 1000U };
    // Euler, friction-free, no load: J*omega(N) must equal the accumulated angular impulse
    // Ts * sum of the per-step (start-of-step) torques. Because the reported torque is post-update,
    // sum(outputs[0..N-2].torque) equals that stage-torque sum (the first stage torque is zero).
    struct uz_pmsm_swmodel_config_t config = base_swmodel_config();
    config.simulate_mechanical_system = true;
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);

    const struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 0.0f, .q = 5.0f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};

    static struct uz_pmsm_swmodel_outputs_t outputs[ITERATIONS] = {0};
    for (uint32_t i = 0U; i < ITERATIONS; i++)
    {
        outputs[i] = uz_pmsm_swmodel_step(model, inputs);
    }

    float torque_impulse_Nm_s = 0.0f;
    for (uint32_t i = 0U; i + 1U < ITERATIONS; i++)
    {
        torque_impulse_Nm_s += outputs[i].torque_Nm * config.sample_time;
    }
    const float angular_momentum = config.pmsm_parameters.J_kg_m_squared * outputs[ITERATIONS - 1U].omega_mech_1_s;
    TEST_ASSERT_TRUE(outputs[ITERATIONS - 1U].omega_mech_1_s > 0.0f);
    TEST_ASSERT_FLOAT_WITHIN(1.0e-4f, torque_impulse_Nm_s, angular_momentum);
}

void test_uz_pmsm_swmodel_mechanical_load_torque_decelerates(void)
{
    enum { ITERATIONS = 1000U };
    struct uz_pmsm_swmodel_config_t config = base_swmodel_config();
    config.simulate_mechanical_system = true;

    struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 0.0f, .q = 5.0f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};

    uz_pmsm_swmodel_t *no_load_model = uz_pmsm_swmodel_init(config);
    uz_pmsm_swmodel_t *load_model = uz_pmsm_swmodel_init(config);

    float omega_no_load = 0.0f;
    float omega_load = 0.0f;
    for (uint32_t i = 0U; i < ITERATIONS; i++)
    {
        inputs.load_torque = 0.0f;
        omega_no_load = uz_pmsm_swmodel_step(no_load_model, inputs).omega_mech_1_s;
        inputs.load_torque = 0.3f; // opposing load
        omega_load = uz_pmsm_swmodel_step(load_model, inputs).omega_mech_1_s;
    }
    TEST_ASSERT_TRUE(omega_load < omega_no_load); // load torque slows the rotor down
}

void test_uz_pmsm_swmodel_mechanical_viscous_steady_state_balance(void)
{
    enum { ITERATIONS = 12000U };
    // Viscous friction only: at steady state the inner torque must balance the friction torque,
    // M_i = mu * omega (no load), i.e. d(omega)/dt = 0.
    struct uz_pmsm_swmodel_config_t config = base_swmodel_config();
    config.simulate_mechanical_system = true;
    config.coulomb_friction_constant = 0.0f;
    config.friction_coefficient = 0.02f;
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(config);

    const struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = 0.0f, .q = 5.0f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.0f};

    struct uz_pmsm_swmodel_outputs_t out = {0};
    for (uint32_t i = 0U; i < ITERATIONS; i++)
    {
        out = uz_pmsm_swmodel_step(model, inputs);
    }
    TEST_ASSERT_TRUE(out.omega_mech_1_s > 0.0f);
    TEST_ASSERT_FLOAT_WITHIN(0.005f, config.friction_coefficient * out.omega_mech_1_s, out.torque_Nm);
}

void test_uz_pmsm_swmodel_mechanical_flux_matches_current(void)
{
    enum { ITERATIONS = 1000U };
    // The mechanical model must give the same speed/current trajectory regardless of the
    // electrical integrator representation.
    struct uz_pmsm_swmodel_config_t config = base_swmodel_config();
    config.simulate_mechanical_system = true;
    config.friction_coefficient = 0.01f;
    config.coulomb_friction_constant = 0.05f;

    config.integrator_state = uz_pmsm_swmodel_integrator_state_current;
    uz_pmsm_swmodel_t *current_model = uz_pmsm_swmodel_init(config);
    config.integrator_state = uz_pmsm_swmodel_integrator_state_flux;
    uz_pmsm_swmodel_t *flux_model = uz_pmsm_swmodel_init(config);

    const struct uz_pmsm_swmodel_inputs_t inputs = {
        .v_dq_V = {.d = -1.0f, .q = 5.0f, .zero = 0.0f},
        .omega_mech_1_s = 0.0f,
        .load_torque = 0.1f};

    for (uint32_t i = 0U; i < ITERATIONS; i++)
    {
        const struct uz_pmsm_swmodel_outputs_t current_out = uz_pmsm_swmodel_step(current_model, inputs);
        const struct uz_pmsm_swmodel_outputs_t flux_out = uz_pmsm_swmodel_step(flux_model, inputs);
        TEST_ASSERT_FLOAT_WITHIN(0.002f, current_out.i_dq_A.d, flux_out.i_dq_A.d);
        TEST_ASSERT_FLOAT_WITHIN(0.002f, current_out.i_dq_A.q, flux_out.i_dq_A.q);
        TEST_ASSERT_FLOAT_WITHIN(0.002f, current_out.omega_mech_1_s, flux_out.omega_mech_1_s);
    }
}

#endif // TEST
