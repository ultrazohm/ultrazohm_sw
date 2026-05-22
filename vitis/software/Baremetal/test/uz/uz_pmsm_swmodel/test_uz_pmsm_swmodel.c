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

#define CSV_FIELD_DESCRIPTOR(struct_type, field_name, field_type) \
    {#field_name, offsetof(struct_type, field_name), field_type}

#define CSV_NESTED_FIELD_DESCRIPTOR(struct_type, nested_struct, field_name, field_type) \
    {#field_name, offsetof(struct_type, nested_struct) + offsetof(struct uz_PMSM_t, field_name), field_type}

#ifndef UZ_PMSM_SWMODEL_RESULTS_CSV_PATH
#define UZ_PMSM_SWMODEL_RESULTS_CSV_PATH "../../../docs/ceedling_test_output/uz/uz_pmsm_swmodel/uz_pmsm_swmodel_results.csv"
#endif

#ifndef UZ_PMSM_SWMODEL_CONFIG_CSV_PATH
#define UZ_PMSM_SWMODEL_CONFIG_CSV_PATH "../../../docs/ceedling_test_output/uz/uz_pmsm_swmodel/uz_pmsm_swmodel_config.csv"
#endif

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


#define STEADY_STATE_ITERATIONS 1000U

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
    struct uz_pmsm_swmodel_inputs_t inputs_k[STEADY_STATE_ITERATIONS] = {0};
    inputs_k[0] = inputs;
        struct uz_pmsm_swmodel_outputs_t outputs[STEADY_STATE_ITERATIONS] = {0};
    for (uint32_t i = 0U; i < STEADY_STATE_ITERATIONS; i++)
    {
        inputs_k[i] = inputs;
        outputs[i] = uz_pmsm_swmodel_step(model, inputs_k[i]);
    }
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_d_V / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_d_A);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, inputs.v_q_V / config.pmsm_parameters.R_ph_Ohm, outputs[STEADY_STATE_ITERATIONS - 1].i_q_A);
    //TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[STEADY_STATE_ITERATIONS - 1].torque_Nm);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, outputs[STEADY_STATE_ITERATIONS - 1].omega_mech_1_s);

    const struct csv_field_descriptor_t output_fields[] = {
        CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, i_d_A, CSV_FIELD_FLOAT),
        CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, i_q_A, CSV_FIELD_FLOAT),
        CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, torque_Nm, CSV_FIELD_FLOAT),
        CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_outputs_t, omega_mech_1_s, CSV_FIELD_FLOAT)};

    const struct csv_field_descriptor_t input_fields[] = {
        CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_inputs_t, v_d_V, CSV_FIELD_FLOAT),
        CSV_FIELD_DESCRIPTOR(struct uz_pmsm_swmodel_inputs_t, v_q_V, CSV_FIELD_FLOAT),
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

    export_input_output_arrays_to_csv(UZ_PMSM_SWMODEL_RESULTS_CSV_PATH,
                                      inputs_k,
                                      sizeof(inputs_k[0]),
                                      input_fields,
                                      sizeof(input_fields) / sizeof(input_fields[0]),
                                      outputs,
                                      sizeof(outputs[0]),
                                      output_fields,
                                      sizeof(output_fields) / sizeof(output_fields[0]),
                                      STEADY_STATE_ITERATIONS);

    export_input_output_arrays_to_csv(UZ_PMSM_SWMODEL_CONFIG_CSV_PATH,
                                      &config,
                                      sizeof(config),
                                      empty_fields,
                                      0U,
                                      &config,
                                      sizeof(config),
                                      config_fields,
                                      sizeof(config_fields) / sizeof(config_fields[0]),
                                      1U);
}




#endif // TEST
