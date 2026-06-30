#ifdef TEST

#include "unity.h"
#include "test_assert_with_exception.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "export_struct_to_csv.h"
#include "uz_PMSM_config.h"
#include "uz_Transformation/uz_Transformation.h"
#include "uz_math_constants.h"
#include "uz_pmsm_control.h"
#include "uz_pmsm_swmodel.h"
#include "uz_signals/uz_signals.h"

TEST_SOURCE_FILE("uz_signals_iir_filter.c")
TEST_SOURCE_FILE("uz_newton_raphson.c")
TEST_SOURCE_FILE("uz_piController.c")
TEST_SOURCE_FILE("uz_CurrentControl.c")
TEST_SOURCE_FILE("uz_linear_decoupling.c")
TEST_SOURCE_FILE("uz_static_nonlinear_decoupling.c")
TEST_SOURCE_FILE("uz_space_vector_limitation.c")
TEST_SOURCE_FILE("uz_space_vector_modulation.c")
TEST_SOURCE_FILE("uz_speedcontrol.c")
TEST_SOURCE_FILE("uz_setpoint.c")
TEST_SOURCE_FILE("uz_controller_setpoint_filter.c")
TEST_SOURCE_FILE("uz_integrator.c")

#define CSV_EXPORT 1

#define CSV_FIELD_DESCRIPTOR(struct_type, field_name, field_type) \
    {#field_name, offsetof(struct_type, field_name), field_type}

#define CSV_NESTED_FIELD_DESCRIPTOR(struct_type, nested_struct, field_name, field_type) \
    {#field_name, offsetof(struct_type, nested_struct) + offsetof(struct uz_PMSM_t, field_name), field_type}

#define UZ_PMSM_CONTROL_SWMODEL_RESULTS_CSV_PATH "../../../docs/ceedling_test_output/integration_tests/uz_pmsm_control_swmodel_profile.csv"
#define UZ_PMSM_CONTROL_SWMODEL_CONFIG_CSV_PATH "../../../docs/ceedling_test_output/integration_tests/uz_pmsm_control_swmodel_profile_config.csv"
#define UZ_PMSM_CONTROL_SWMODEL_RESULTS_DELAY_CSV_PATH "../../../docs/ceedling_test_output/integration_tests/uz_pmsm_control_swmodel_profile_measurement_delay.csv"
#define UZ_PMSM_CONTROL_SWMODEL_CONFIG_DELAY_CSV_PATH "../../../docs/ceedling_test_output/integration_tests/uz_pmsm_control_swmodel_profile_measurement_delay_config.csv"
#define UZ_PMSM_CONTROL_FREQUENCY_HZ 10000U
#define UZ_PMSM_SWMODEL_OVERSAMPLING_FACTOR 200U
#define UZ_PMSM_CONTROL_SWMODEL_SIMULATION_TIME_SECONDS 3U

struct uz_pmsm_control_swmodel_log_t
{
    float i_d_ref_A;
    float i_q_ref_A;
    float speed_ref_rpm;
    float speed_actual_rpm;
    float controller_active;
    float i_d_A;
    float i_q_A;
    float v_d_V;
    float v_q_V;
    float theta_mech_rad;
};

struct uz_pmsm_control_swmodel_config_export_t
{
    uint32_t control_frequency_Hz;
    uint32_t swmodel_oversampling_factor;
    float controller_sample_time;
    float swmodel_sample_time;
    float magnitude_optimum_tau_sigma_sec;
    float v_dc_V;
    struct uz_PMSM_t machine;
};

static const struct csv_field_descriptor_t pmsm_control_swmodel_log_fields[] = {
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, i_d_ref_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, i_q_ref_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, speed_ref_rpm, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, speed_actual_rpm, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, controller_active, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, i_d_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, i_q_A, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, v_d_V, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, v_q_V, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_log_t, theta_mech_rad, CSV_FIELD_FLOAT)};

static const struct csv_field_descriptor_t pmsm_control_swmodel_config_fields[] = {
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, control_frequency_Hz, CSV_FIELD_UINT32),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, swmodel_oversampling_factor, CSV_FIELD_UINT32),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, controller_sample_time, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, swmodel_sample_time, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, magnitude_optimum_tau_sigma_sec, CSV_FIELD_FLOAT),
    CSV_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, v_dc_V, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, R_ph_Ohm, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, Ld_Henry, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, Lq_Henry, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, Psi_PM_Vs, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, polePairs, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, J_kg_m_squared, CSV_FIELD_FLOAT),
    CSV_NESTED_FIELD_DESCRIPTOR(struct uz_pmsm_control_swmodel_config_export_t, machine, I_max_Ampere, CSV_FIELD_FLOAT)};

void setUp(void)
{
}

void tearDown(void)
{
}

/*
 * Shared body for the profile integration tests. When
 * delay_measurements_one_control_step is true, the controller is fed the
 * measurements sampled at the *previous* controller tick (a one-control-step
 * sampling delay) instead of the current ones; everything else is identical.
 */
static void run_uz_pmsm_swmodel_uz_pmsm_control_profile(bool delay_measurements_one_control_step,
                                                        const char *results_csv_path,
                                                        const char *config_csv_path)
{
    enum
    {
        CONTROLLER_ITERATIONS = UZ_PMSM_CONTROL_FREQUENCY_HZ * UZ_PMSM_CONTROL_SWMODEL_SIMULATION_TIME_SECONDS,
        MODEL_ITERATIONS_PER_SECOND = UZ_PMSM_CONTROL_FREQUENCY_HZ * UZ_PMSM_SWMODEL_OVERSAMPLING_FACTOR,
        TOTAL_MODEL_ITERATIONS = CONTROLLER_ITERATIONS * UZ_PMSM_SWMODEL_OVERSAMPLING_FACTOR
    };

    struct uz_PMSM_t machine_config = UZ_PMSM_BECKHOFF_AM8141_0J00_000_MEASURED_PSI_DQ_AVERAGED_800_RPM_INIT;
    struct uz_pmsm_control_configuration_t controller_config = {
        .theta_el_offset = 0.0f,
        .sample_time = 1.0f / (float)UZ_PMSM_CONTROL_FREQUENCY_HZ,
        .enable_speed_control = false,
        .speed_controller_kp = 0.0f,
        .speed_controller_ki = 0.0f,
        .current_controller_d_kp = 1.0f,
        .current_controller_d_ki = 1.0f,
        .current_controller_q_kp = 1.0f,
        .current_controller_q_ki = 1.0f,
        .setpoint_limits = {
            .speed_controller_torque_in_Nm = {
                .upper_bound = machine_config.Torque_max_Nm,
                .lower_bound = machine_config.Torque_min_Nm
            },
            .i_d_in_A = {
                .upper_bound = machine_config.I_d_max_A,
                .lower_bound = machine_config.I_d_min_A
            },
            .i_q_in_A = {
                .upper_bound = machine_config.I_q_max_A,
                .lower_bound = machine_config.I_q_min_A
            },
            .speed_in_rpm = {
                .upper_bound = machine_config.speed_max_rpm,
                .lower_bound = machine_config.speed_min_rpm
            },
            .disturbance_input_in_Nm = {
                .upper_bound = machine_config.Torque_max_Nm,
                .lower_bound = machine_config.Torque_min_Nm
            }
        },
        .safe_operating_region = {
            .speed_in_rpm = {
                .upper_bound = machine_config.speed_max_rpm,
                .lower_bound = machine_config.speed_min_rpm
            },
            .i_d_in_A = {
                .upper_bound = machine_config.I_d_max_A,
                .lower_bound = machine_config.I_d_min_A
            },
            .i_q_in_A = {
                .upper_bound = machine_config.I_q_max_A,
                .lower_bound = machine_config.I_q_min_A
            },
            .i_abc_in_A = {
                .upper_bound = machine_config.I_max_Ampere,
                .lower_bound = -machine_config.I_max_Ampere
            },
            .v_dc_in_V = {
                .upper_bound = 60.0f,
                .lower_bound = 1.0f
            },
            .i_dc_in_A = {
                .upper_bound = machine_config.I_max_Ampere,
                .lower_bound = -machine_config.I_max_Ampere
            }},
        .decoupling_method = linear_decoupling,
        .setpoint_filter_i_dq_cutoff_frequency = 0.0f,
        .setpoint_filter_speed_cutoff_frequency = 0.0f,
        .motor_type = SMPMSM,
        .enable_field_weakening = false,
        .relative_torque_tolerance = 0.1f,
        .speed_actual_value_filter_cutoff_frequency = 0.0f,
        .theta_sampling_compensation = 0.0f,
        .theta_svm_delay_compensation = 0.0f,
        .voltage_theta_shift = 0.0f,
        .default_duty_cycle = {.DutyCycle_A = 0.0f, .DutyCycle_B = 0.0f, .DutyCycle_C = 0.0f},
    };

    uz_pmsm_control_t *controller = uz_pmsm_control_init(controller_config, machine_config);
    const float magnitude_optimum_tau_sigma_sec = 1.0f * controller_config.sample_time;
    uz_pmsm_control_current_control_tune_magnitude_optimum(controller, magnitude_optimum_tau_sigma_sec);
    uz_pmsm_control_enable(controller, true);

    struct uz_pmsm_swmodel_config_t swmodel_config = {
        .sample_time = controller_config.sample_time / (float)UZ_PMSM_SWMODEL_OVERSAMPLING_FACTOR,
        .pmsm_parameters = machine_config};
    uz_pmsm_swmodel_t *model = uz_pmsm_swmodel_init(swmodel_config);

    static struct uz_pmsm_control_swmodel_log_t sim_log[TOTAL_MODEL_ITERATIONS] = {0};

    float theta_mech_rad = 0.0f;
    uz_3ph_dq_t model_i_dq_A = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};
    uz_3ph_dq_t applied_v_dq_V = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

    /* Holds the measurements from the previous controller tick for the delayed variant.
     * Initialised to the (all-zero) start-up state with nominal DC-link voltage, which
     * equals the measurements computed at i == 0, so the first controller tick matches. */
    struct uz_pmsm_measurement_values delayed_measurements = {0};
    delayed_measurements.v_dc_in_V = machine_config.V_dc_nominal_V;

    for (uint32_t i = 0U; i < TOTAL_MODEL_ITERATIONS; i++)
    {
        const float time_s = (float)i * swmodel_config.sample_time;
        const bool controller_active = (i % UZ_PMSM_SWMODEL_OVERSAMPLING_FACTOR) == 0U;
        float speed_ref_rpm = 0.0f;
        float speed_actual_rpm = 0.0f;
        uz_3ph_dq_t reference_currents = {.d = 0.0f, .q = 0.0f, .zero = 0.0f};

        if (time_s > 1.0f)
        {
            reference_currents.d = 0.0f;
            reference_currents.q = 1.0f;
        }

        if (time_s > 2.0f)
        {
            speed_ref_rpm = 500.0f;
            speed_actual_rpm = 500.0f;
        }

        const float omega_mech_rad_per_sec = speed_actual_rpm * (2.0f * UZ_PIf) / 60.0f;
        const float theta_el_rad = theta_mech_rad * machine_config.polePairs;
        const struct uz_pmsm_measurement_values measurements = {
            .i_abc_in_A = uz_transformation_3ph_dq_to_abc(model_i_dq_A, theta_el_rad),
            .v_abc_in_V = uz_transformation_3ph_dq_to_abc(applied_v_dq_V, theta_el_rad),
            .omega_mech_rad_per_sec = omega_mech_rad_per_sec,
            .theta_mech = theta_mech_rad,
            .v_dc_in_V = machine_config.V_dc_nominal_V,
            .i_dc_in_A = 0.0f};

        if (controller_active)
        {
            const struct uz_pmsm_measurement_values controller_measurements =
                delay_measurements_one_control_step ? delayed_measurements : measurements;
            applied_v_dq_V = uz_pmsm_control_sample_dq(controller, controller_measurements, speed_ref_rpm, reference_currents, 0.0f);
            delayed_measurements = measurements;
        }

        const struct uz_pmsm_swmodel_inputs_t swmodel_inputs = {
            .v_dq_V = applied_v_dq_V,
            .omega_mech_1_s = omega_mech_rad_per_sec,
            .load_torque = 0.0f};
        const struct uz_pmsm_swmodel_outputs_t swmodel_outputs = uz_pmsm_swmodel_step(model, swmodel_inputs);

        model_i_dq_A = swmodel_outputs.i_dq_A;
        model_i_dq_A.zero = 0.0f;
        theta_mech_rad = uz_signals_wrap(theta_mech_rad + swmodel_outputs.omega_mech_1_s * swmodel_config.sample_time, 2.0f * UZ_PIf);

        sim_log[i] = (struct uz_pmsm_control_swmodel_log_t){
            .i_d_ref_A = reference_currents.d,
            .i_q_ref_A = reference_currents.q,
            .speed_ref_rpm = speed_ref_rpm,
            .speed_actual_rpm = speed_actual_rpm,
            .controller_active = controller_active ? 1.0f : 0.0f,
            .i_d_A = model_i_dq_A.d,
            .i_q_A = model_i_dq_A.q,
            .v_d_V = applied_v_dq_V.d,
            .v_q_V = applied_v_dq_V.q,
            .theta_mech_rad = theta_mech_rad};
    }

    TEST_ASSERT_FLOAT_WITHIN(0.05f, 0.0f, sim_log[MODEL_ITERATIONS_PER_SECOND - 1U].i_q_A);
    TEST_ASSERT_FLOAT_WITHIN(0.20f, 1.0f, sim_log[TOTAL_MODEL_ITERATIONS - 1U].i_q_A);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 500.0f, sim_log[TOTAL_MODEL_ITERATIONS - 1U].speed_actual_rpm);
    TEST_ASSERT_EQUAL(uz_pmsm_control_no_violation, uz_pmsm_control_get_safe_operating_area_violation(controller));

#if CSV_EXPORT
    const struct uz_pmsm_control_swmodel_config_export_t export_config = {
        .control_frequency_Hz = UZ_PMSM_CONTROL_FREQUENCY_HZ,
        .swmodel_oversampling_factor = UZ_PMSM_SWMODEL_OVERSAMPLING_FACTOR,
        .controller_sample_time = controller_config.sample_time,
        .swmodel_sample_time = swmodel_config.sample_time,
        .magnitude_optimum_tau_sigma_sec = magnitude_optimum_tau_sigma_sec,
        .v_dc_V = machine_config.V_dc_nominal_V,
        .machine = machine_config};

    export_array_of_struct_to_csv_fast(results_csv_path,
                                       sim_log,
                                       sizeof(sim_log[0]),
                                       pmsm_control_swmodel_log_fields,
                                       sizeof(pmsm_control_swmodel_log_fields) / sizeof(pmsm_control_swmodel_log_fields[0]),
                                       TOTAL_MODEL_ITERATIONS,
                                       swmodel_config.sample_time);
    export_array_of_struct_to_csv(config_csv_path,
                                  &export_config,
                                  sizeof(export_config),
                                  pmsm_control_swmodel_config_fields,
                                  sizeof(pmsm_control_swmodel_config_fields) / sizeof(pmsm_control_swmodel_config_fields[0]),
                                  1U,
                                  0.0f);
#endif

}

void test_integration_uz_pmsm_swmodel_uz_pmsm_control_profile(void)
{
    run_uz_pmsm_swmodel_uz_pmsm_control_profile(false,
                                                UZ_PMSM_CONTROL_SWMODEL_RESULTS_CSV_PATH,
                                                UZ_PMSM_CONTROL_SWMODEL_CONFIG_CSV_PATH);
}

void test_integration_uz_pmsm_swmodel_uz_pmsm_control_profile_measurement_delay(void)
{
    run_uz_pmsm_swmodel_uz_pmsm_control_profile(true,
                                                UZ_PMSM_CONTROL_SWMODEL_RESULTS_DELAY_CSV_PATH,
                                                UZ_PMSM_CONTROL_SWMODEL_CONFIG_DELAY_CSV_PATH);
}

#endif // TEST
