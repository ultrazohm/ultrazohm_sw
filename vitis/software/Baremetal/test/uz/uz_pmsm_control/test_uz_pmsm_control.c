#ifdef TEST

#include "unity.h"
#include <stdbool.h>
#include "uz_pmsm_control.h"
#include "uz_HAL.h"
#include "uz_math_constants.h"
#include "uz_signals/uz_signals.h"
#include "uz_piController/uz_piController.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "uz_SpeedControl/uz_speedcontrol.h"
#include "uz_CurrentControl/uz_CurrentControl.h"
#include "uz_setpoint/uz_setpoint.h"
#include "uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"

#include "test_assert_with_exception.h"
#include "uz_CurrentControl.h"
#include "uz_piController/uz_piController.h"
#include "uz_signals/uz_signals.h"
#include "uz_linear_decoupling.h"
#include "uz_static_nonlinear_decoupling.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_space_vector_limitation.h"
#include "uz_pmsm_swmodel.h"
#include "export_struct_to_csv.h"
#include <math.h>
#include <stddef.h>

#include "../uz_PMSM_config/uz_PMSM_config.h"
#include "../uz_integrator/uz_integrator.h"
TEST_SOURCE_FILE("uz_signals_iir_filter.c")
TEST_SOURCE_FILE("uz_newton_raphson.c")

void setUp(void)
{
}

void tearDown(void)
{
}

#define SETPOINT_FILTER_CUTTOFF_FREQUENCY 100.0f
#define CSV_EXPORT 1

#define CSV_FIELD_DESCRIPTOR(struct_type, field_name, field_type) \
    {#field_name, offsetof(struct_type, field_name), field_type}

#define CSV_NESTED_FIELD_DESCRIPTOR(struct_type, nested_struct, field_name, field_type) \
    {#field_name, offsetof(struct_type, nested_struct) + offsetof(struct uz_PMSM_t, field_name), field_type}

#define UZ_PMSM_CONTROL_SWMODEL_RESULTS_CSV_PATH "../../../docs/ceedling_test_output/uz/uz_pmsm_control/uz_pmsm_control_swmodel_iq_step.csv"
#define UZ_PMSM_CONTROL_SWMODEL_CONFIG_CSV_PATH "../../../docs/ceedling_test_output/uz/uz_pmsm_control/uz_pmsm_control_swmodel_iq_step_config.csv"

struct uz_pmsm_control_swmodel_inputs_t
{
    float i_d_ref_A;
    float i_q_ref_A;
    float speed_ref_rpm;
    float trigger_controller;
};

struct uz_pmsm_control_swmodel_outputs_t
{
    float i_d_A;
    float i_q_A;
    float v_d_V;
    float v_q_V;
    float omega_mech_rad_per_sec;
    float theta_mech_rad;
};

struct uz_pmsm_control_swmodel_config_export_t
{
    float sample_time;
    struct uz_PMSM_t machine;
};

const struct csv_field_descriptor_t pmsm_control_swmodel_input_fields[] = {
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_inputs_t, i_d_ref_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_inputs_t, i_q_ref_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_inputs_t, speed_ref_rpm, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_inputs_t, trigger_controller, CSV_FIELD_FLOAT)};

const struct csv_field_descriptor_t pmsm_control_swmodel_output_fields[] = {
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_outputs_t, i_d_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_outputs_t, i_q_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_outputs_t, v_d_V, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_outputs_t, v_q_V, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_outputs_t, omega_mech_rad_per_sec, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_outputs_t, theta_mech_rad, CSV_FIELD_FLOAT)};

const struct csv_field_descriptor_t pmsm_control_swmodel_config_fields[] = {
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, sample_time, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, R_ph_Ohm, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, Ld_Henry, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, Lq_Henry, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, Psi_PM_Vs, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, polePairs, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, J_kg_m_squared, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, I_max_Ampere, CSV_FIELD_FLOAT)};

static const struct csv_field_descriptor_t empty_fields[] = {{NULL, 0U, CSV_FIELD_FLOAT}};

struct uz_pmsm_control_configuration_t pmsm_controller_config = {
    .theta_el_offset = 1.56f,
    .sample_time = 1.0f / 10000.0f,
    .enable_speed_control = true,
    .speed_controller_kp = 0.01f,
    .speed_controller_ki = 0.05f,
    .current_controller_d_kp = 5.8333f,
    .current_controller_d_ki = 1500.0f,
    .current_controller_q_kp = 5.8333f,
    .current_controller_q_ki = 1500.0f,
    .setpoint_limits = {
        .speed_controller_torque_in_Nm = {.upper_bound = 2.0f, .lower_bound = -2.0f},
        .i_d_in_A = {.upper_bound = 0.5f, .lower_bound = -5.0f},
        .i_q_in_A = {.upper_bound = 5.0f, .lower_bound = -5.0f},
        .speed_in_rpm = {.upper_bound = 1100.0f, .lower_bound = -1100.0f},
        .disturbance_input_in_Nm = {.upper_bound = 10.0f, .lower_bound = -10.0f}},
    .error_upper_bound_speed_in_rpm = 1500.0f,
    .error_lower_bound_speed_in_rpm = -1500.0f,
    .decoupling_method = linear_decoupling,
    .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
    .setpoint_filter_speed_cutoff_frequency = SETPOINT_FILTER_CUTTOFF_FREQUENCY,
    .motor_type = SMPMSM,
    .enable_field_weakening = false,
    .relative_torque_tolerance = 0.1f,
    .speed_actual_value_filter_cutoff_frequency = 0.0f,
    .theta_sampling_compensation = 0.0f,
    .theta_svm_delay_compensation = 1.5f,
    .voltage_theta_shift = 0.0f,
    .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
};

struct uz_PMSM_t machine_config = {
    .R_ph_Ohm = 0.51f,
    .Ld_Henry = 0.002f,
    .Lq_Henry = 0.002f,
    .Psi_PM_Vs = 0.042f,
    .polePairs = 4.0f,
    .J_kg_m_squared = 0.000108f,
    .I_max_Ampere = 12.0f};

void test_uz_pmsm_control_call_init(void)
{
    uz_pmsm_control_t *controller = uz_pmsm_control_init(pmsm_controller_config, machine_config);
    struct uz_pmsm_actual_data *actual_data = uz_pmsm_control_get_actual_data(controller);
    struct uz_pmsm_reference_values *reference_values = uz_pmsm_control_get_reference_values(controller);
    struct uz_pmsm_measurement_values *measurement_values = uz_pmsm_control_get_pmsm_measurement_values(controller);
    // Put to javascope like so:
    // js_ch_observable[JSO_dut_iq] = &actual_data->i_dq_in_A.q;
}

void test_uz_pmsm_control_get_safe_area(void)
{
    uz_pmsm_control_t *controller = uz_pmsm_control_init(pmsm_controller_config, machine_config);
    bool safe_operating_violation = uz_pmsm_control_get_safe_operating_area_violation(controller);
    // use a if construct to check if violation is present
}

void test_uz_pmsm_control_sample(void)
{
    uz_pmsm_control_t *controller = uz_pmsm_control_init(pmsm_controller_config, machine_config);

    struct uz_pmsm_measurement_values measurements = {
        .i_abc_in_A = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
        .v_abc_in_V = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
        .omega_mech_rad_per_sec = 1.0f,
        .theta_mech = 1.56f,
        .v_dc_in_V = 12.0f,
        .i_dc_in_A = 1.0f};

    float reference_speed_in_rpm = 1.0f;
    uz_3ph_dq_t reference_currents = {
        .d = 0.0f,
        .q = 0.0f,
        .zero = 0.0f};
    float disturbance_input_in_Nm = 0.0f;
    struct uz_DutyCycle_t duty_d2 = uz_pmsm_control_sample_duty(controller, measurements, reference_speed_in_rpm, reference_currents, disturbance_input_in_Nm);
}

void test_uz_pmsm_set_enable(void)
{
    uz_pmsm_control_t *controller = uz_pmsm_control_init(pmsm_controller_config, machine_config);
    uz_pmsm_control_enable(controller, true);
}

void test_uz_pmsm_reset_error(void)
{
    uz_pmsm_control_t *controller = uz_pmsm_control_init(pmsm_controller_config, machine_config);

    struct uz_pmsm_measurement_values measurements = {
        .i_abc_in_A = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
        .v_abc_in_V = {.a = 0.0f, .b = 0.0f, .c = 0.0f},
        .omega_mech_rad_per_sec = 1.0f,
        .theta_mech = 1.56f,
        .v_dc_in_V = 12.0f,
        .i_dc_in_A = 1.0f};

    uz_pmsm_control_acknowledge_and_reset_error(controller, measurements);
}

void test_uz_pmsm_enable_speed_control(void)
{
    uz_pmsm_control_t *controller = uz_pmsm_control_init(pmsm_controller_config, machine_config);
    uz_pmsm_control_enable_speed_control(controller, true);
}

void test_uz_pmsm_control_swmodel_iq_step_after_1s_oversampled(void)
{
    enum
    {
        CONTROLLER_OVERSAMPLING_FACTOR = 20U,
        PRE_STEP_CONTROLLER_ITERATIONS = 10000U,
        POST_STEP_CONTROLLER_ITERATIONS = 10000U,
        TOTAL_CONTROLLER_ITERATIONS = PRE_STEP_CONTROLLER_ITERATIONS + POST_STEP_CONTROLLER_ITERATIONS,
        PRE_STEP_MODEL_ITERATIONS = PRE_STEP_CONTROLLER_ITERATIONS * CONTROLLER_OVERSAMPLING_FACTOR,
        POST_STEP_MODEL_ITERATIONS = POST_STEP_CONTROLLER_ITERATIONS * CONTROLLER_OVERSAMPLING_FACTOR,
        TOTAL_MODEL_ITERATIONS = PRE_STEP_MODEL_ITERATIONS + POST_STEP_MODEL_ITERATIONS
    };

    struct uz_pmsm_control_configuration_t controller_config = pmsm_controller_config;
    controller_config.enable_speed_control = false;
    controller_config.theta_el_offset = 0.0f;
    controller_config.theta_sampling_compensation = 0.0f;
    controller_config.theta_svm_delay_compensation = 0.0f;

    uz_pmsm_control_t *controller = uz_pmsm_control_init(controller_config, machine_config);
    uz_pmsm_control_current_control_tune_magnitude_optimum(controller, 0.4f * controller_config.sample_time);
    uz_pmsm_control_enable(controller, true);

    struct uz_pmsm_swmodel_config_t swmodel_config = {
        .sample_time = controller_config.sample_time / (float)CONTROLLER_OVERSAMPLING_FACTOR,
        .pmsm_parameters = machine_config};
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(swmodel_config);

    static struct uz_pmsm_control_swmodel_inputs_t sim_inputs[TOTAL_MODEL_ITERATIONS] = {0};
    static struct uz_pmsm_control_swmodel_outputs_t sim_outputs[TOTAL_MODEL_ITERATIONS] = {0};

    float theta_mech_rad = 0.0f;
    float omega_mech_rad_per_sec = 10.0f;
    uz_3ph_dq_t model_i_dq_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
    uz_3ph_dq_t applied_v_dq_V = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

    for (uint32_t i = 0U; i < TOTAL_MODEL_ITERATIONS; i++)
    {
        const float i_q_ref_A = (i < PRE_STEP_MODEL_ITERATIONS) ? 0.0f : 1.0f;
        const bool trigger_controller = (i % CONTROLLER_OVERSAMPLING_FACTOR) == 0U;
        const float theta_el_rad = theta_mech_rad * machine_config.polePairs;
        struct uz_pmsm_measurement_values measurements = {
            .i_abc_in_A = uz_transformation_3ph_dq_to_abc(model_i_dq_A, theta_el_rad),
            .v_abc_in_V = uz_transformation_3ph_dq_to_abc(applied_v_dq_V, theta_el_rad),
            .omega_mech_rad_per_sec = omega_mech_rad_per_sec,
            .theta_mech = theta_mech_rad,
            .v_dc_in_V = 12.0f,
            .i_dc_in_A = 0.0f};

        uz_3ph_dq_t reference_currents = {
            .d = 0.0f,
            .q = i_q_ref_A,
            .zero = 0.0f};

        if (trigger_controller)
        {
            applied_v_dq_V = uz_pmsm_control_sample_dq(controller, measurements, 0.0f, reference_currents, 0.0f);
        }

        struct uz_pmsm_swmodel_inputs_t swmodel_inputs = {
            .v_d_V = applied_v_dq_V.d,
            .v_q_V = applied_v_dq_V.q,
            .omega_mech_1_s = omega_mech_rad_per_sec,
            .load_torque = 0.0f};

        struct uz_pmsm_swmodel_outputs_t swmodel_outputs = uz_pmsm_swmodel_step(model, swmodel_inputs);

        model_i_dq_A.d = swmodel_outputs.i_d_A;
        model_i_dq_A.q = swmodel_outputs.i_q_A;
        model_i_dq_A.zero = 0.0f;
        omega_mech_rad_per_sec = swmodel_outputs.omega_mech_1_s;
        theta_mech_rad = uz_signals_wrap(theta_mech_rad + omega_mech_rad_per_sec * swmodel_config.sample_time, 2.0f * UZ_PIf);

        sim_inputs[i] = (struct uz_pmsm_control_swmodel_inputs_t){
            .i_d_ref_A = reference_currents.d,
            .i_q_ref_A = reference_currents.q,
            .speed_ref_rpm = 0.0f,
            .trigger_controller = trigger_controller ? 1.0f : 0.0f};

        sim_outputs[i] = (struct uz_pmsm_control_swmodel_outputs_t){
            .i_d_A = model_i_dq_A.d,
            .i_q_A = model_i_dq_A.q,
            .v_d_V = applied_v_dq_V.d,
            .v_q_V = applied_v_dq_V.q,
            .omega_mech_rad_per_sec = omega_mech_rad_per_sec,
            .theta_mech_rad = theta_mech_rad};
    }

    TEST_ASSERT_FLOAT_WITHIN(0.05f, 0.0f, sim_outputs[PRE_STEP_MODEL_ITERATIONS - 1U].i_q_A);
    TEST_ASSERT_FLOAT_WITHIN(0.20f, 1.0f, sim_outputs[TOTAL_MODEL_ITERATIONS - 1U].i_q_A);

#if CSV_EXPORT
    struct uz_pmsm_control_swmodel_config_export_t export_config = {
        .sample_time = controller_config.sample_time,
        .machine = machine_config};
    export_input_output_arrays_to_csv("../../../docs/ceedling_test_output/uz/uz_pmsm_control/uz_pmsm_control_swmodel_iq_step_oversampled.csv",
                                      sim_inputs,
                                      sizeof(sim_inputs[0]),
                                      pmsm_control_swmodel_input_fields,
                                      sizeof(pmsm_control_swmodel_input_fields) / sizeof(pmsm_control_swmodel_input_fields[0]),
                                      sim_outputs,
                                      sizeof(sim_outputs[0]),
                                      pmsm_control_swmodel_output_fields,
                                      sizeof(pmsm_control_swmodel_output_fields) / sizeof(pmsm_control_swmodel_output_fields[0]),
                                      TOTAL_MODEL_ITERATIONS,
                                      swmodel_config.sample_time);
    export_input_output_arrays_to_csv(UZ_PMSM_CONTROL_SWMODEL_CONFIG_CSV_PATH,
                                      &export_config,
                                      sizeof(export_config),
                                      empty_fields,
                                      0U,
                                      &export_config,
                                      sizeof(export_config),
                                      pmsm_control_swmodel_config_fields,
                                      sizeof(pmsm_control_swmodel_config_fields) / sizeof(pmsm_control_swmodel_config_fields[0]),
                                      1U,
                                      0.0f);
#endif
}

void test_uz_pmsm_control_swmodel_iq_step_after_1s(void)
{
    enum
    {
        PRE_STEP_ITERATIONS = 10000U,
        POST_STEP_ITERATIONS = 10000U,
        TOTAL_ITERATIONS = PRE_STEP_ITERATIONS + POST_STEP_ITERATIONS
    };

    struct uz_pmsm_control_configuration_t controller_config = pmsm_controller_config;
    controller_config.enable_speed_control = false;
    controller_config.theta_el_offset = 0.0f;
    controller_config.theta_sampling_compensation = 0.0f;
    controller_config.theta_svm_delay_compensation = 0.0f;

    uz_pmsm_control_t *controller = uz_pmsm_control_init(controller_config, machine_config);
    uz_pmsm_control_current_control_tune_magnitude_optimum(controller, 0.5f * controller_config.sample_time);
    uz_pmsm_control_enable(controller, true);

    struct uz_pmsm_swmodel_config_t swmodel_config = {
        .sample_time = controller_config.sample_time,
        .pmsm_parameters = machine_config};
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(swmodel_config);

    struct uz_pmsm_control_swmodel_inputs_t sim_inputs[TOTAL_ITERATIONS] = {0};
    struct uz_pmsm_control_swmodel_outputs_t sim_outputs[TOTAL_ITERATIONS] = {0};

    float theta_mech_rad = 0.0f;
    float omega_mech_rad_per_sec = 10.0f;
    uz_3ph_dq_t model_i_dq_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
    uz_3ph_dq_t applied_v_dq_V = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

    for (uint32_t i = 0U; i < TOTAL_ITERATIONS; i++)
    {
        const float i_q_ref_A = (i < PRE_STEP_ITERATIONS) ? 0.0f : 1.0f;
        const float theta_el_rad = theta_mech_rad * machine_config.polePairs;
        struct uz_pmsm_measurement_values measurements = {
            .i_abc_in_A = uz_transformation_3ph_dq_to_abc(model_i_dq_A, theta_el_rad),
            .v_abc_in_V = uz_transformation_3ph_dq_to_abc(applied_v_dq_V, theta_el_rad),
            .omega_mech_rad_per_sec = omega_mech_rad_per_sec,
            .theta_mech = theta_mech_rad,
            .v_dc_in_V = 12.0f,
            .i_dc_in_A = 0.0f};

        uz_3ph_dq_t reference_currents = {
            .d = 0.0f,
            .q = i_q_ref_A,
            .zero = 0.0f};

        applied_v_dq_V = uz_pmsm_control_sample_dq(controller, measurements, 0.0f, reference_currents, 0.0f);

        struct uz_pmsm_swmodel_inputs_t swmodel_inputs = {
            .v_d_V = applied_v_dq_V.d,
            .v_q_V = applied_v_dq_V.q,
            .omega_mech_1_s = omega_mech_rad_per_sec,
            .load_torque = 0.0f};
        struct uz_pmsm_swmodel_outputs_t swmodel_outputs = uz_pmsm_swmodel_step(model, swmodel_inputs);

        model_i_dq_A.d = swmodel_outputs.i_d_A;
        model_i_dq_A.q = swmodel_outputs.i_q_A;
        model_i_dq_A.zero = 0.0f;
        omega_mech_rad_per_sec = swmodel_outputs.omega_mech_1_s;
        theta_mech_rad = uz_signals_wrap(theta_mech_rad + omega_mech_rad_per_sec * controller_config.sample_time, 2.0f * UZ_PIf);

        sim_inputs[i] = (struct uz_pmsm_control_swmodel_inputs_t){
            .i_d_ref_A = reference_currents.d,
            .i_q_ref_A = reference_currents.q,
            .speed_ref_rpm = 0.0f};

        sim_outputs[i] = (struct uz_pmsm_control_swmodel_outputs_t){
            .i_d_A = model_i_dq_A.d,
            .i_q_A = model_i_dq_A.q,
            .v_d_V = applied_v_dq_V.d,
            .v_q_V = applied_v_dq_V.q,
            .omega_mech_rad_per_sec = omega_mech_rad_per_sec,
            .theta_mech_rad = theta_mech_rad};
    }

    TEST_ASSERT_FLOAT_WITHIN(0.05f, 0.0f, sim_outputs[PRE_STEP_ITERATIONS - 1U].i_q_A);
    TEST_ASSERT_FLOAT_WITHIN(0.20f, 1.0f, sim_outputs[TOTAL_ITERATIONS - 1U].i_q_A);

#if CSV_EXPORT
    struct uz_pmsm_control_swmodel_config_export_t export_config = {
        .sample_time = controller_config.sample_time,
        .machine = machine_config};
    export_input_output_arrays_to_csv(UZ_PMSM_CONTROL_SWMODEL_RESULTS_CSV_PATH,
                                      sim_inputs,
                                      sizeof(sim_inputs[0]),
                                      pmsm_control_swmodel_input_fields,
                                      sizeof(pmsm_control_swmodel_input_fields) / sizeof(pmsm_control_swmodel_input_fields[0]),
                                      sim_outputs,
                                      sizeof(sim_outputs[0]),
                                      pmsm_control_swmodel_output_fields,
                                      sizeof(pmsm_control_swmodel_output_fields) / sizeof(pmsm_control_swmodel_output_fields[0]),
                                      TOTAL_ITERATIONS,
                                      controller_config.sample_time);
    export_input_output_arrays_to_csv(UZ_PMSM_CONTROL_SWMODEL_CONFIG_CSV_PATH,
                                      &export_config,
                                      sizeof(export_config),
                                      empty_fields,
                                      0U,
                                      &export_config,
                                      sizeof(export_config),
                                      pmsm_control_swmodel_config_fields,
                                      sizeof(pmsm_control_swmodel_config_fields) / sizeof(pmsm_control_swmodel_config_fields[0]),
                                      1U,
                                      0.0f);
#endif
}

#endif // TEST
