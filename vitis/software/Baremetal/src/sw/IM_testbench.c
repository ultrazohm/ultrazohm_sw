#include "../include/IM_testbench.h"
#include "../globalData.h"
#include "../include/testbenchsetup.h"
#include "../uz/uz_HAL.h"

typedef struct {
    float time_s;
    float frequency_Hz;
    enum uz_im_control_observer observer;
} im_validation_profile_point_t;

/* Keep synchronized with im_observer_validation_profile.csv. Frequency and
 * observer are applied as zero-order holds. Every observer executes the same
 * seven 5 s U/f reference plateaus for a directly comparable log. */
static const im_validation_profile_point_t im_validation_profile[] = {
    {0.0f, 0.0f, uz_im_control_observer_rotor_flux_model},
    {5.0f, 2.5f, uz_im_control_observer_rotor_flux_model},
    {10.0f, 5.0f, uz_im_control_observer_rotor_flux_model},
    {15.0f, 0.0f, uz_im_control_observer_rotor_flux_model},
    {20.0f, -2.5f, uz_im_control_observer_rotor_flux_model},
    {25.0f, -5.0f, uz_im_control_observer_rotor_flux_model},
    {30.0f, 0.0f, uz_im_control_observer_rotor_flux_model},

    {35.0f, 0.0f, uz_im_control_observer_filtered_rotor_flux_model},
    {40.0f, 2.5f, uz_im_control_observer_filtered_rotor_flux_model},
    {45.0f, 5.0f, uz_im_control_observer_filtered_rotor_flux_model},
    {50.0f, 0.0f, uz_im_control_observer_filtered_rotor_flux_model},
    {55.0f, -2.5f, uz_im_control_observer_filtered_rotor_flux_model},
    {60.0f, -5.0f, uz_im_control_observer_filtered_rotor_flux_model},
    {65.0f, 0.0f, uz_im_control_observer_filtered_rotor_flux_model},

    {70.0f, 0.0f, uz_im_control_observer_kalman_rotor_flux_model},
    {75.0f, 2.5f, uz_im_control_observer_kalman_rotor_flux_model},
    {80.0f, 5.0f, uz_im_control_observer_kalman_rotor_flux_model},
    {85.0f, 0.0f, uz_im_control_observer_kalman_rotor_flux_model},
    {90.0f, -2.5f, uz_im_control_observer_kalman_rotor_flux_model},
    {95.0f, -5.0f, uz_im_control_observer_kalman_rotor_flux_model},
    {100.0f, 0.0f, uz_im_control_observer_kalman_rotor_flux_model},
    {105.0f, 0.0f, uz_im_control_observer_kalman_rotor_flux_model},
};

#define IM_VALIDATION_PROFILE_POINT_COUNT \
    ((uint32_t)(sizeof(im_validation_profile) / sizeof(im_validation_profile[0])))

static void select_observer(DS_Data *data, enum uz_im_control_observer observer)
{
    data->rasv.im_enable_kalman_filter = observer != uz_im_control_observer_rotor_flux_model;
    data->rasv.im_use_simplified_kalman_filter =
        observer == uz_im_control_observer_filtered_rotor_flux_model;
    data->av.im_validation_observer_mode = (float)observer;
    uz_im_control_set_observer(data->objects.im_control, observer);
}

static void set_profile_frequency(DS_Data *data, float frequency_Hz)
{
    setpoint_trajectory_state_t * const trajectory = &data->objects.setpoint_trajectories[5];
    data->rasv.im_frequency_reference_Hz = frequency_Hz;
    data->av.snd_fld[6] = frequency_Hz;
    trajectory->start = frequency_Hz;
    trajectory->target = frequency_Hz;
    trajectory->active_target = frequency_Hz;
}

static void stop_validation_profile(DS_Data *data)
{
    data->rasv.im_validation_profile_active = false;
    data->rasv.im_validation_profile_has_started = false;
    data->rasv.im_validation_profile_elapsed_s = 0.0f;
    data->av.im_validation_profile_stage = 0.0f;
    set_profile_frequency(data, 0.0f);
}

void IM_testbench_init(DS_Data *data)
{
    uz_assert_not_NULL(data);
    uz_assert(data->av.isr_samplerate_s > 0.0f);

    struct testbenchsetup_im_t const setup = testbenchsetup_create_im(data->av.isr_samplerate_s);
    struct uz_im_control_configuration_t const config = setup.control;

    data->objects.im_control = uz_im_control_init(config, setup.machine);
    uz_im_control_set_mode(data->objects.im_control, uz_im_control_mode_u_f);
    data->rasv.im_enable_foc = false;
    data->rasv.im_enable_kalman_filter = false;
    data->rasv.im_use_simplified_kalman_filter = false;
    data->rasv.im_enable_resonant_control = false;
    data->rasv.im_validation_profile_active = false;
    data->rasv.im_validation_profile_has_started = false;
    data->rasv.im_validation_profile_elapsed_s = 0.0f;
    data->av.im_validation_profile_stage = 0.0f;
    select_observer(data, uz_im_control_observer_rotor_flux_model);

    data->av.snd_fld[7] = config.current_controller_d_kp;
    data->av.snd_fld[8] = config.current_controller_d_ki;
    data->av.snd_fld[9] = config.current_controller_q_kp;
    data->av.snd_fld[10] = config.current_controller_q_ki;
    data->av.snd_fld[11] = config.kalman_process_noise_A2_per_s;
    data->av.snd_fld[12] = config.kalman_measurement_noise_A2;
    data->av.snd_fld[13] = config.resonant_gain_d;
    data->av.snd_fld[14] = config.resonant_gain_q;
    data->av.snd_fld[15] = config.resonant_harmonic_order;
    data->av.snd_fld[16] = config.resonant_antiwindup_gain;
    data->av.snd_fld[17] = config.resonant_voltage_limit_V;
    data->av.snd_fld[18] = config.minimum_observer_flux_Vs;
}

void IM_testbench_toggle_control_mode(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_enable_foc = !data->rasv.im_enable_foc;
    if (data->rasv.im_enable_foc) {
        /* FOC always starts with its configured magnetizing current. Keep the
         * trajectory state synchronized so no pending ramp can overwrite it. */
        setpoint_trajectory_state_t * const i_d_trajectory = &data->objects.setpoint_trajectories[3];
        i_d_trajectory->start = MOTOR_Default_i_d_reference_A;
        i_d_trajectory->target = MOTOR_Default_i_d_reference_A;
        i_d_trajectory->active_target = MOTOR_Default_i_d_reference_A;
        uz_Trajectory_Stop(i_d_trajectory->instance);
        uz_Trajectory_Reset(i_d_trajectory->instance);
        data->rasv.im_i_d_reference_A = MOTOR_Default_i_d_reference_A;
        data->av.snd_fld[4] = MOTOR_Default_i_d_reference_A;
    }
    uz_im_control_set_mode(data->objects.im_control, data->rasv.im_enable_foc
        ? uz_im_control_mode_foc : uz_im_control_mode_u_f);
}

void IM_testbench_toggle_kalman_filter(DS_Data *data)
{
    uz_assert_not_NULL(data);
    bool const enable = !data->rasv.im_enable_kalman_filter;
    enum uz_im_control_observer const observer = !enable
        ? uz_im_control_observer_rotor_flux_model
        : (data->rasv.im_use_simplified_kalman_filter
            ? uz_im_control_observer_filtered_rotor_flux_model
            : uz_im_control_observer_kalman_rotor_flux_model);
    select_observer(data, observer);
}

void IM_testbench_toggle_kalman_mode(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_use_simplified_kalman_filter =
        !data->rasv.im_use_simplified_kalman_filter;
    if (data->rasv.im_enable_kalman_filter) {
        select_observer(data,
            data->rasv.im_use_simplified_kalman_filter
                ? uz_im_control_observer_filtered_rotor_flux_model
                : uz_im_control_observer_kalman_rotor_flux_model);
    }
}

void IM_testbench_toggle_resonant_control(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_enable_resonant_control = !data->rasv.im_enable_resonant_control;
    uz_im_control_enable_resonant_control(data->objects.im_control,
        data->rasv.im_enable_resonant_control);
}

void IM_testbench_toggle_validation_profile(DS_Data *data)
{
    uz_assert_not_NULL(data);
    if (data->rasv.im_validation_profile_active) {
        stop_validation_profile(data);
        return;
    }

    data->rasv.im_enable_foc = false;
    data->rasv.im_enable_resonant_control = false;
    data->rasv.im_validation_profile_active = true;
    data->rasv.im_validation_profile_has_started = false;
    data->rasv.im_validation_profile_elapsed_s = 0.0f;
    data->av.im_validation_profile_stage = 1.0f;
    uz_im_control_reset(data->objects.im_control);
    uz_im_control_set_mode(data->objects.im_control, uz_im_control_mode_u_f);
    uz_im_control_enable_resonant_control(data->objects.im_control, false);
    select_observer(data, uz_im_control_observer_rotor_flux_model);
    set_profile_frequency(data, 0.0f);
}

void IM_testbench_update_validation_profile(DS_Data *data, bool control_active)
{
    uz_assert_not_NULL(data);
    if (!data->rasv.im_validation_profile_active) {
        return;
    }
    if (!control_active) {
        if (data->rasv.im_validation_profile_has_started) {
            stop_validation_profile(data);
        } else {
            set_profile_frequency(data, 0.0f);
        }
        return;
    }

    data->rasv.im_validation_profile_has_started = true;
    float const elapsed_s = data->rasv.im_validation_profile_elapsed_s;
    float const block_start_s = (elapsed_s >= 70.0f) ? 70.0f
        : ((elapsed_s >= 35.0f) ? 35.0f : 0.0f);
    float const block_time_s = elapsed_s - block_start_s;
    if (block_time_s < 5.0f) {
        data->av.im_validation_profile_stage = 2.0f; /* initialization at zero */
    } else if (block_time_s < 20.0f) {
        data->av.im_validation_profile_stage = 3.0f; /* positive-frequency sequence */
    } else if (block_time_s < 30.0f) {
        data->av.im_validation_profile_stage = 4.0f; /* negative-frequency sequence */
    } else {
        data->av.im_validation_profile_stage = 5.0f; /* final zero-frequency hold */
    }
    uint32_t upper = 1U;
    while ((upper < IM_VALIDATION_PROFILE_POINT_COUNT)
        && (elapsed_s >= im_validation_profile[upper].time_s)) {
        upper++;
    }
    if (upper >= IM_VALIDATION_PROFILE_POINT_COUNT) {
        stop_validation_profile(data);
        return;
    }

    im_validation_profile_point_t const lower_point = im_validation_profile[upper - 1U];
    set_profile_frequency(data, lower_point.frequency_Hz);

    if ((uint32_t)data->av.im_validation_observer_mode != (uint32_t)lower_point.observer) {
        select_observer(data, lower_point.observer);
    }
    data->rasv.im_validation_profile_elapsed_s += data->av.isr_samplerate_s;
}

static void reset_setpoints_and_trajectories(DS_Data *data)
{
    data->rasv.va_speed_reference_rpm = 0.0f;
    data->rasv.va_current_reference_A = (uz_3ph_dq_t){0};
    data->rasv.va_disturbance_torque_Nm = 0.0f;
    data->rasv.va_acknowledge_error = false;
    data->rasv.im_frequency_reference_Hz = 0.0f;
    data->rasv.im_i_d_reference_A = 0.0f;
    data->rasv.im_i_q_reference_A = 0.0f;
    for (uint32_t trajectory = 0U; trajectory < SETPOINT_TRAJECTORY_COUNT; trajectory++) {
        setpoint_trajectory_state_t * const state = &data->objects.setpoint_trajectories[trajectory];
        state->start = 0.0f;
        state->target = 0.0f;
        state->active_target = 0.0f;
        data->av.snd_fld[trajectory + 1U] = 0.0f;
        uz_Trajectory_Stop(state->instance);
        uz_Trajectory_Reset(state->instance);
    }
}

void IM_testbench_reset_idle(DS_Data *data)
{
    uz_assert_not_NULL(data);
    reset_setpoints_and_trajectories(data);
    uz_pmsm_control_reset(data->objects.va_control);
    /* Reset dynamic controller/observer states, but keep the selected mode and
     * feature switches so a subsequent start uses the user's selection. */
    uz_im_control_reset(data->objects.im_control);
}

void IM_testbench_reset(DS_Data *data)
{
    uz_assert_not_NULL(data);
    stop_validation_profile(data);
    reset_setpoints_and_trajectories(data);
    data->rasv.va_enable_speed_control = false;
    data->rasv.im_enable_foc = false;
    data->rasv.im_enable_resonant_control = false;
    uz_pmsm_control_reset(data->objects.va_control);
    uz_im_control_acknowledge_and_reset_error(data->objects.im_control);
    uz_im_control_set_mode(data->objects.im_control, uz_im_control_mode_u_f);
    select_observer(data, uz_im_control_observer_rotor_flux_model);
    uz_im_control_enable_resonant_control(data->objects.im_control, false);
}
