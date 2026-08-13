#include "../include/IM_testbench.h"
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
    data->rasv.im_siemens_1LA7073_enable_foc = false;
    data->rasv.im_siemens_1LA7073_enable_kalman_filter = false;
    data->rasv.im_siemens_1LA7073_enable_resonant_control = false;

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
    data->rasv.im_siemens_1LA7073_enable_foc = !data->rasv.im_siemens_1LA7073_enable_foc;
    uz_im_control_set_mode(data->objects.im_control, data->rasv.im_siemens_1LA7073_enable_foc
        ? uz_im_control_mode_foc : uz_im_control_mode_u_f);
}

void IM_testbench_toggle_kalman_filter(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_siemens_1LA7073_enable_kalman_filter = !data->rasv.im_siemens_1LA7073_enable_kalman_filter;
    uz_im_control_set_observer(data->objects.im_control, data->rasv.im_siemens_1LA7073_enable_kalman_filter
        ? uz_im_control_observer_kalman_rotor_flux_model : uz_im_control_observer_rotor_flux_model);
}

void IM_testbench_toggle_resonant_control(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_siemens_1LA7073_enable_resonant_control = !data->rasv.im_siemens_1LA7073_enable_resonant_control;
    uz_im_control_enable_resonant_control(data->objects.im_control,
        data->rasv.im_siemens_1LA7073_enable_resonant_control);
}

void IM_testbench_reset(DS_Data *data)
{
    uz_assert_not_NULL(data);
    data->rasv.im_siemens_1LA7073_enable_foc = false;
    data->rasv.im_siemens_1LA7073_enable_kalman_filter = false;
    data->rasv.im_siemens_1LA7073_enable_resonant_control = false;
    uz_im_control_acknowledge_and_reset_error(data->objects.im_control);
    uz_im_control_set_mode(data->objects.im_control, uz_im_control_mode_u_f);
    uz_im_control_set_observer(data->objects.im_control, uz_im_control_observer_rotor_flux_model);
    uz_im_control_enable_resonant_control(data->objects.im_control, false);
}
