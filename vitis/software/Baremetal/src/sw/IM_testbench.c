#include "../include/IM_testbench.h"
#include "../include/error_checks.h"
#include "../globalData.h"
#include "../include/testbenchsetup.h"
#include "../uz/uz_HAL.h"

void IM_testbench_init(DS_Data *data)
{
    uz_assert_not_NULL(data);
    uz_assert(data->av.isr_samplerate_s > 0.0f);

    struct testbenchsetup_im_t const setup = testbenchsetup_create_im(data->av.isr_samplerate_s);
    struct uz_im_control_configuration_t const config = setup.control;

    data->objects.im_control = uz_im_control_init(config, setup.machine);
    uz_im_control_set_mode(data->objects.im_control, uz_im_control_mode_u_f);
    data->rasv.im_enable_foc = false;
    data->rasv.im_enable_speed_control = false;
    data->rasv.im_enable_kalman_filter = false;
    data->rasv.im_enable_resonant_control = false;
	data->rasv.im_enable_u_f_observer = false;
	uz_im_control_enable_u_f_observer(data->objects.im_control, false);
	data->rasv.im_use_filtered_v_dc = false;

    data->av.snd_fld[1] = data->rasv.im_i_d_reference_A;
    data->av.snd_fld[2] = data->rasv.im_i_q_reference_A;
    data->av.snd_fld[3] = data->rasv.im_frequency_reference_Hz;
    data->av.snd_fld[4] = data->rasv.im_speed_reference_rpm;
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

void IM_testbench_toggle_speed_control(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_enable_speed_control = !data->rasv.im_enable_speed_control;
    uz_im_control_enable_speed_control(data->objects.im_control, data->rasv.im_enable_speed_control);
}

void IM_testbench_toggle_control_mode(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_enable_foc = !data->rasv.im_enable_foc;
    if (data->rasv.im_enable_foc) {
        /* FOC always starts with its configured magnetizing current. Keep the
         * trajectory state synchronized so no pending ramp can overwrite it. */
        setpoint_trajectory_state_t * const i_d_trajectory = &data->objects.setpoint_trajectories[0];
        i_d_trajectory->start = MOTOR_Default_i_d_reference_A;
        i_d_trajectory->target = MOTOR_Default_i_d_reference_A;
        i_d_trajectory->active_target = MOTOR_Default_i_d_reference_A;
        uz_Trajectory_Stop(i_d_trajectory->instance);
        uz_Trajectory_Reset(i_d_trajectory->instance);
        data->rasv.im_i_d_reference_A = MOTOR_Default_i_d_reference_A;
        data->av.snd_fld[1] = MOTOR_Default_i_d_reference_A;
    }
    uz_im_control_set_mode(data->objects.im_control, data->rasv.im_enable_foc
        ? uz_im_control_mode_foc : uz_im_control_mode_u_f);
}

void IM_testbench_toggle_kalman_filter(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_enable_kalman_filter = !data->rasv.im_enable_kalman_filter;
    uz_im_control_set_observer(data->objects.im_control, data->rasv.im_enable_kalman_filter
        ? uz_im_control_observer_kalman_rotor_flux_model : uz_im_control_observer_rotor_flux_model);
}

void IM_testbench_toggle_resonant_control(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_enable_resonant_control = !data->rasv.im_enable_resonant_control;
    uz_im_control_enable_resonant_control(data->objects.im_control,
        data->rasv.im_enable_resonant_control);
}

static void reset_setpoints_and_trajectories(DS_Data *data)
{
    data->rasv.im_frequency_reference_Hz = 0.0f;
    data->rasv.im_i_d_reference_A = 0.0f;
    data->rasv.im_i_q_reference_A = 0.0f;
    data->rasv.im_speed_reference_rpm = 0.0f;
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
    /* Reset dynamic controller/observer states, but keep the selected mode and
     * feature switches so a subsequent start uses the user's selection. */
    uz_im_control_reset(data->objects.im_control);
}

void IM_testbench_reset(DS_Data *data)
{
    uz_assert_not_NULL(data);
    reset_setpoints_and_trajectories(data);
    data->rasv.im_enable_foc = false;
    data->rasv.im_enable_speed_control = false;
    data->rasv.im_enable_kalman_filter = false;
    data->rasv.im_enable_resonant_control = false;
	data->rasv.im_enable_u_f_observer = false;
	data->rasv.im_use_filtered_v_dc = false;
    uz_im_control_acknowledge_and_reset_error(data->objects.im_control);
	data->av.im_control_violation = uz_im_control_no_violation;
	data->av.im_control_violation_code = 0.0f;
	error_checks_reset();
    uz_im_control_set_mode(data->objects.im_control, uz_im_control_mode_u_f);
    uz_im_control_set_observer(data->objects.im_control, uz_im_control_observer_rotor_flux_model);
    uz_im_control_enable_speed_control(data->objects.im_control, false);
    uz_im_control_enable_resonant_control(data->objects.im_control, false);
	uz_im_control_enable_u_f_observer(data->objects.im_control, false);
}
