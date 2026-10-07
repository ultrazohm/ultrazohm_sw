#include "uz_im_control.h"
#include "../uz_global_configuration.h"
#if UZ_IM_CONTROL_MAX_INSTANCES > 0U
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_ResonantController/uz_resonant_controller.h"
#include "../uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_CurrentControl/uz_space_vector_limitation.h"
#include <math.h>

struct uz_im_control_t {
    bool is_ready;
    bool enable;
    bool speed_control_enabled;
    enum uz_im_control_observer observer;
    enum uz_im_control_mode mode;
    enum uz_im_control_safe_operating_region_violation violation;
    struct uz_im_control_configuration_t control_config;
    uz_IM_t machine_config;
    struct uz_im_measurement_values measurements;
    struct uz_im_reference_values references;
    struct uz_im_actual_data actual;
    uz_PI_Controller *current_controller_d;
    uz_PI_Controller *current_controller_q;
    uz_PI_Controller *speed_controller;
    uz_dq_setpoint_filter *setpoint_filter_i_dq;
    uz_IIR_Filter_t *setpoint_filter_speed;
    uz_IIR_Filter_t *speed_filter;
    uz_resonantController_t *resonant_controller_d;
    uz_resonantController_t *resonant_controller_q;
    bool resonant_control_enabled;
    bool voltage_vector_saturated_last;
    uz_im_observer_t *observer_instance;
    uz_3ph_abc_t previous_applied_v_abc_V;
    float u_f_frequency_Hz;
    float u_f_angle_rad;
};

static uint32_t instance_counter;
static uz_im_control_t instances[UZ_IM_CONTROL_MAX_INSTANCES];

static void validate_configuration(struct uz_im_control_configuration_t control_config,
                                   uz_IM_t machine_config) {
    uz_assert(control_config.sample_time_s > 0.0f);
    uz_assert(control_config.current_controller_d_kp >= 0.0f);
    uz_assert(control_config.current_controller_d_ki >= 0.0f);
    uz_assert(control_config.current_controller_q_kp >= 0.0f);
    uz_assert(control_config.current_controller_q_ki >= 0.0f);
    uz_assert(control_config.speed_controller_kp >= 0.0f);
    uz_assert(control_config.speed_controller_ki >= 0.0f);
    uz_assert(control_config.u_f_ratio_V_per_Hz >= 0.0f);
    uz_assert(control_config.u_f_max_frequency_Hz > 0.0f);
    uz_assert(control_config.u_f_max_voltage_V > 0.0f);
    uz_assert(control_config.u_f_frequency_ramp_Hz_per_s > 0.0f);
    uz_assert(control_config.kalman_process_noise_A2_per_s >= 0.0f);
    uz_assert(control_config.kalman_flux_process_noise_Vs2_per_s >= 0.0f);
    uz_assert(control_config.kalman_measurement_noise_A2 > 0.0f);
    uz_assert(control_config.observer_pll_kp >= 0.0f);
    uz_assert(control_config.observer_pll_ki >= 0.0f);
    uz_assert(control_config.minimum_observer_flux_Vs > 0.0f);
    uz_assert(control_config.maximum_slip_frequency_Hz > 0.0f);
    uz_assert(control_config.maximum_flux_angle_step_rad > 0.0f);
    uz_assert(control_config.maximum_phase_current_sum_A > 0.0f);
    uz_assert(control_config.resonant_gain_d >= 0.0f);
    uz_assert(control_config.resonant_gain_q >= 0.0f);
    uz_assert(control_config.resonant_harmonic_order > 0.0f);
    uz_assert(control_config.resonant_antiwindup_gain >= 0.0f);
    uz_assert(control_config.resonant_voltage_limit_V > 0.0f);
    uz_assert(control_config.setpoint_limits.speed_controller_torque_in_Nm.upper_bound >= control_config.setpoint_limits.speed_controller_torque_in_Nm.lower_bound);
    uz_assert(control_config.setpoint_limits.i_d_in_A.upper_bound >= control_config.setpoint_limits.i_d_in_A.lower_bound);
    uz_assert(control_config.setpoint_limits.i_q_in_A.upper_bound >= control_config.setpoint_limits.i_q_in_A.lower_bound);
    uz_assert(control_config.setpoint_limits.speed_in_rpm.upper_bound >= control_config.setpoint_limits.speed_in_rpm.lower_bound);
    uz_assert(control_config.safe_operating_region.speed_in_rpm.upper_bound >= control_config.safe_operating_region.speed_in_rpm.lower_bound);
    uz_assert(control_config.safe_operating_region.i_d_in_A.upper_bound >= control_config.safe_operating_region.i_d_in_A.lower_bound);
    uz_assert(control_config.safe_operating_region.i_q_in_A.upper_bound >= control_config.safe_operating_region.i_q_in_A.lower_bound);
    uz_assert(control_config.safe_operating_region.i_abc_in_A.upper_bound >= control_config.safe_operating_region.i_abc_in_A.lower_bound);
    uz_assert(control_config.safe_operating_region.v_dc_in_V.upper_bound >= control_config.safe_operating_region.v_dc_in_V.lower_bound);
    uz_assert(control_config.safe_operating_region.i_dc_in_A.upper_bound >= control_config.safe_operating_region.i_dc_in_A.lower_bound);
    uz_assert(control_config.setpoint_filter_i_dq_cutoff_frequency >= 0.0f);
    uz_assert(control_config.setpoint_filter_speed_cutoff_frequency >= 0.0f);
    uz_assert(control_config.speed_actual_value_filter_cutoff_frequency >= 0.0f);
    uz_IM_config_assert(machine_config);
}

static uz_PI_Controller *create_pi(float kp, float ki, float ts, float upper_limit, float lower_limit) {
    struct uz_PI_Controller_config pi_config = {
        .type = UZ_PI_PARALLEL,
        .Kp = kp,
        .Ki = ki,
        .samplingTime_sec = ts,
        .upper_limit = upper_limit,
        .lower_limit = lower_limit
    };
    return uz_PI_Controller_init(pi_config);
}

uz_im_control_t *uz_im_control_init(struct uz_im_control_configuration_t control_config,
                                    uz_IM_t machine_config) {
    validate_configuration(control_config, machine_config);
    uz_assert(instance_counter < UZ_IM_CONTROL_MAX_INSTANCES);
    uz_im_control_t *self = &instances[instance_counter++];
    uz_assert_false(self->is_ready);
    self->is_ready = true;
    self->control_config = control_config;
    self->machine_config = machine_config;
    self->speed_control_enabled = control_config.enable_speed_control;
    self->observer = control_config.observer;
    self->resonant_control_enabled = control_config.enable_resonant_control;
    self->mode = uz_im_control_mode_foc;
    self->current_controller_d = create_pi(control_config.current_controller_d_kp, control_config.current_controller_d_ki,
        control_config.sample_time_s, control_config.safe_operating_region.v_dc_in_V.upper_bound,
        -control_config.safe_operating_region.v_dc_in_V.upper_bound);
    self->current_controller_q = create_pi(control_config.current_controller_q_kp, control_config.current_controller_q_ki,
        control_config.sample_time_s, control_config.safe_operating_region.v_dc_in_V.upper_bound,
        -control_config.safe_operating_region.v_dc_in_V.upper_bound);
    self->speed_controller = create_pi(control_config.speed_controller_kp, control_config.speed_controller_ki, control_config.sample_time_s, control_config.setpoint_limits.i_q_in_A.upper_bound, control_config.setpoint_limits.i_q_in_A.lower_bound);
    if (control_config.setpoint_filter_i_dq_cutoff_frequency != 0.0f) {
        struct uz_IIR_Filter_config filter = {.selection = LowPass_first_order, .cutoff_frequency_Hz = control_config.setpoint_filter_i_dq_cutoff_frequency, .sample_frequency_Hz = 1.0f / control_config.sample_time_s};
        self->setpoint_filter_i_dq = uz_dq_setpoint_filter_init((struct uz_dq_setpoint_filter_config){.config_filter_d = filter, .config_filter_q = filter});
    }
    if (control_config.setpoint_filter_speed_cutoff_frequency != 0.0f) {
        self->setpoint_filter_speed = uz_signals_IIR_Filter_init((struct uz_IIR_Filter_config){.selection = LowPass_first_order, .cutoff_frequency_Hz = control_config.setpoint_filter_speed_cutoff_frequency, .sample_frequency_Hz = 1.0f / control_config.sample_time_s});
    }
    if (control_config.speed_actual_value_filter_cutoff_frequency != 0.0f) {
        self->speed_filter = uz_signals_IIR_Filter_init((struct uz_IIR_Filter_config){.selection = LowPass_first_order, .cutoff_frequency_Hz = control_config.speed_actual_value_filter_cutoff_frequency, .sample_frequency_Hz = 1.0f / control_config.sample_time_s});
    }
    struct uz_resonantController_config resonant_config = {
        .sampling_time = control_config.sample_time_s,
        .fundamental_frequency = 1.0f,
        .harmonic_order = control_config.resonant_harmonic_order,
        .antiwindup_gain = control_config.resonant_antiwindup_gain,
        .lower_limit = -control_config.resonant_voltage_limit_V,
        .upper_limit = control_config.resonant_voltage_limit_V,
    };
    resonant_config.gain = control_config.resonant_gain_d;
    self->resonant_controller_d = uz_resonantController_init(resonant_config);
    resonant_config.gain = control_config.resonant_gain_q;
    self->resonant_controller_q = uz_resonantController_init(resonant_config);
    self->observer_instance = uz_im_observer_init((struct uz_im_observer_config){
        .sample_time_s = control_config.sample_time_s,
        .kalman_process_noise_A2_per_s = control_config.kalman_process_noise_A2_per_s,
        .kalman_measurement_noise_A2 = control_config.kalman_measurement_noise_A2,
        .kalman_flux_process_noise_Vs2_per_s = control_config.kalman_flux_process_noise_Vs2_per_s,
        .minimum_observer_flux_Vs = control_config.minimum_observer_flux_Vs,
        .maximum_flux_angle_step_rad = control_config.maximum_flux_angle_step_rad,
        .maximum_phase_current_sum_A = control_config.maximum_phase_current_sum_A,
        .maximum_slip_frequency_Hz = control_config.maximum_slip_frequency_Hz,
        .observer_pll_kp = control_config.observer_pll_kp,
        .observer_pll_ki = control_config.observer_pll_ki,
        .observer = control_config.observer,
    }, machine_config);
    uz_im_control_reset(self);
    return self;
}

void uz_im_control_reset(uz_im_control_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_PI_Controller_reset(self->current_controller_d);
    uz_PI_Controller_reset(self->current_controller_q);
    uz_PI_Controller_reset(self->speed_controller);
    if (self->setpoint_filter_i_dq != NULL) uz_dq_setpoint_filter_reset(self->setpoint_filter_i_dq);
    if (self->setpoint_filter_speed != NULL) uz_signals_IIR_Filter_reset(self->setpoint_filter_speed);
    if (self->speed_filter != NULL) uz_signals_IIR_Filter_reset(self->speed_filter);
    uz_resonantController_reset(self->resonant_controller_d);
    uz_resonantController_reset(self->resonant_controller_q);
    uz_im_observer_reset(self->observer_instance);
    self->previous_applied_v_abc_V = (uz_3ph_abc_t){0};
    self->u_f_frequency_Hz = 0.0f;
    self->u_f_angle_rad = 0.0f;
    self->voltage_vector_saturated_last = false;
    self->references = (struct uz_im_reference_values){.duty_cycle = self->control_config.default_duty_cycle};
    self->actual = (struct uz_im_actual_data){0};
    self->actual.safe_operating_region_status = (uint32_t)self->violation;
}

void uz_im_control_enable(uz_im_control_t *self, bool enable) { uz_assert_not_NULL(self); self->enable = enable; if (!enable) uz_im_control_reset(self); }
void uz_im_control_set_mode(uz_im_control_t *self, enum uz_im_control_mode mode) {
    uz_assert_not_NULL(self);
    if (self->mode == mode) return;
    /* The observer runs in U/f as well. Preserve its flux state for takeover
     * and clear only controller states that may contain an old control error. */
    uz_PI_Controller_reset(self->current_controller_d);
    uz_PI_Controller_reset(self->current_controller_q);
    uz_PI_Controller_reset(self->speed_controller);
    uz_resonantController_reset(self->resonant_controller_d);
    uz_resonantController_reset(self->resonant_controller_q);
    if (self->setpoint_filter_i_dq != NULL) uz_dq_setpoint_filter_reset(self->setpoint_filter_i_dq);
    if (self->setpoint_filter_speed != NULL) uz_signals_IIR_Filter_reset(self->setpoint_filter_speed);
    self->mode = mode;
}
void uz_im_control_enable_speed_control(uz_im_control_t *self, bool enable) { uz_assert_not_NULL(self); self->speed_control_enabled = enable; uz_PI_Controller_reset(self->speed_controller); }
void uz_im_control_set_observer(uz_im_control_t *self, enum uz_im_control_observer observer) {
    uz_assert_not_NULL(self);
    uz_assert((observer == uz_im_control_observer_rotor_flux_model)
        || (observer == uz_im_control_observer_kalman_rotor_flux_model)
        || (observer == uz_im_control_observer_filtered_rotor_flux_model));
    if (self->observer != observer) {
        self->observer = observer;
        uz_im_observer_set_mode(self->observer_instance, observer);
        self->actual.i_dq_A = (uz_3ph_dq_t){0};
        self->actual.rotor_flux_angle_rad = 0.0f;
        self->actual.rotor_flux_magnitude_Vs = 0.0f;
        self->actual.estimated_electrical_torque_Nm = 0.0f;
        self->actual.flux_rotor_angle_difference_rad = 0.0f;
        self->actual.slip_angular_frequency_rad_per_s = 0.0f;
        self->actual.stator_angular_frequency_rad_per_s = 0.0f;
        self->actual.slip_frequency_Hz = 0.0f;
        self->actual.slip_percent = 0.0f;
        self->actual.stator_frequency_Hz = 0.0f;
        self->actual.kalman_innovation_alpha_A = 0.0f;
        self->actual.kalman_innovation_beta_A = 0.0f;
        self->actual.rotor_flux_valid = 0.0f;
        self->actual.slip_frequency_limited = 0.0f;
        self->actual.flux_angle_step_rad = 0.0f;
        self->actual.flux_angle_step_violation = 0.0f;
    }
}
void uz_im_control_enable_resonant_control(uz_im_control_t *self, bool enable) {
    uz_assert_not_NULL(self);
    if (self->resonant_control_enabled != enable) {
        uz_resonantController_reset(self->resonant_controller_d);
        uz_resonantController_reset(self->resonant_controller_q);
    }
    self->resonant_control_enabled = enable;
}

static void check_safe_operating_region(uz_im_control_t *self) {
    if (self->violation != uz_im_control_no_violation) return;
    struct uz_im_safe_operating_region_t l = self->control_config.safe_operating_region;
    float speed = self->measurements.rotor_speed_rpm;
    if (speed < l.speed_in_rpm.lower_bound) self->violation = uz_im_control_underspeed;
    else if (speed > l.speed_in_rpm.upper_bound) self->violation = uz_im_control_overspeed;
    else if (self->measurements.v_dc_V > l.v_dc_in_V.upper_bound) self->violation = uz_im_control_dc_overvoltage;
    else if (self->measurements.v_dc_V < l.v_dc_in_V.lower_bound) self->violation = uz_im_control_dc_undervoltage;
    else if (self->measurements.i_dc_A > l.i_dc_in_A.upper_bound) self->violation = uz_im_control_dc_overcurrent;
    else if (self->measurements.i_dc_A < l.i_dc_in_A.lower_bound) self->violation = uz_im_control_dc_undercurrent;
    else if (self->actual.i_dq_A.d > l.i_d_in_A.upper_bound) self->violation = uz_im_control_i_d_overcurrent;
    else if (self->actual.i_dq_A.d < l.i_d_in_A.lower_bound) self->violation = uz_im_control_i_d_undercurrent;
    else if (self->actual.i_dq_A.q > l.i_q_in_A.upper_bound) self->violation = uz_im_control_i_q_overcurrent;
    else if (self->actual.i_dq_A.q < l.i_q_in_A.lower_bound) self->violation = uz_im_control_i_q_undercurrent;
    else if ((self->measurements.i_abc_A.a > l.i_abc_in_A.upper_bound) || (self->measurements.i_abc_A.b > l.i_abc_in_A.upper_bound) || (self->measurements.i_abc_A.c > l.i_abc_in_A.upper_bound)) self->violation = uz_im_control_phase_overcurrent;
    else if ((self->measurements.i_abc_A.a < l.i_abc_in_A.lower_bound) || (self->measurements.i_abc_A.b < l.i_abc_in_A.lower_bound) || (self->measurements.i_abc_A.c < l.i_abc_in_A.lower_bound)) self->violation = uz_im_control_phase_undercurrent;
    self->actual.safe_operating_region_status = (uint32_t)self->violation;
}

static void update_observers(uz_im_control_t *self) {
    /* Current at k and voltage reconstructed/stored by IM Control in k-1. */
    bool const valid = uz_im_observer_sample(self->observer_instance,
        (struct uz_im_observer_input){
            .i_abc_A = self->measurements.i_abc_A,
            .v_abc_V = self->measurements.v_abc_V,
            .rotor_speed_rpm = self->measurements.rotor_speed_rpm,
            .rotor_mechanical_angle_rad = self->measurements.rotor_mechanical_angle_rad,
        });
    const struct uz_im_observer_output *output = uz_im_observer_get_output(self->observer_instance);
    self->actual.rotor_flux_angle_rad = output->rotor_flux_angle_rad;
    self->actual.rotor_flux_magnitude_Vs = output->rotor_flux_magnitude_Vs;
    self->actual.i_dq_A = output->i_dq_A;
    self->actual.kalman_innovation_alpha_A = output->kalman_innovation_alpha_A;
    self->actual.kalman_innovation_beta_A = output->kalman_innovation_beta_A;
    self->actual.rotor_flux_valid = output->rotor_flux_valid;
    self->actual.estimated_electrical_torque_Nm = output->estimated_electrical_torque_Nm;
    self->actual.flux_angle_step_rad = output->flux_angle_step_rad;
    self->actual.flux_angle_step_violation = output->flux_angle_step_violation;
    self->actual.phase_current_sum_A = output->phase_current_sum_A;
    self->actual.phase_current_sum_violation = output->phase_current_sum_violation;
    self->actual.rotor_electrical_angle_rad = output->rotor_electrical_angle_rad;
    self->actual.flux_rotor_angle_difference_rad = output->flux_rotor_angle_difference_rad;
    self->actual.i_dq_raw_A = output->i_dq_raw_A;
    self->actual.slip_frequency_limited = output->slip_frequency_limited;
    self->actual.rotor_electrical_angular_speed_rad_per_s = output->rotor_electrical_angular_speed_rad_per_s;
    self->actual.slip_angular_frequency_rad_per_s = output->slip_angular_frequency_rad_per_s;
    self->actual.stator_angular_frequency_rad_per_s = output->stator_angular_frequency_rad_per_s;
    self->actual.rotor_electrical_frequency_Hz = output->rotor_electrical_frequency_Hz;
    self->actual.slip_frequency_Hz = output->slip_frequency_Hz;
    self->actual.stator_frequency_Hz = output->stator_frequency_Hz;
    self->actual.slip_percent = output->slip_percent;
    if (!valid) {
        self->violation = uz_im_control_observer_violation;
        self->actual.safe_operating_region_status = (uint32_t)self->violation;
    }
}

static struct uz_DutyCycle_t sample_u_f(uz_im_control_t *self, float target_Hz) {
    float target = fminf(fmaxf(target_Hz, -self->control_config.u_f_max_frequency_Hz), self->control_config.u_f_max_frequency_Hz);
    float step = self->control_config.u_f_frequency_ramp_Hz_per_s * self->control_config.sample_time_s;
    float error = target - self->u_f_frequency_Hz;
    self->u_f_frequency_Hz += fminf(fmaxf(error, -step), step);
    float magnitude = fminf(fabsf(self->u_f_frequency_Hz) * self->control_config.u_f_ratio_V_per_Hz + ((fabsf(self->u_f_frequency_Hz) > 0.1f) ? self->control_config.u_f_boost_voltage_V : 0.0f), self->control_config.u_f_max_voltage_V);
    self->u_f_angle_rad = fmodf(self->u_f_angle_rad + 2.0f * UZ_PIf * self->u_f_frequency_Hz * self->control_config.sample_time_s, 2.0f * UZ_PIf);
    if (self->u_f_angle_rad < 0.0f) self->u_f_angle_rad += 2.0f * UZ_PIf;
    self->actual.u_f_command_frequency_Hz = self->u_f_frequency_Hz;
    self->actual.u_f_electrical_angle_rad = self->u_f_angle_rad;
    self->actual.u_f_applied_voltage_V = magnitude;
    self->references.v_dq_V = (uz_3ph_dq_t){.d = magnitude * sqrtf(2.0f / 3.0f)};
    return uz_Space_Vector_Modulation(self->references.v_dq_V, self->measurements.v_dc_V, self->u_f_angle_rad);
}

uz_3ph_dq_t uz_im_control_sample_dq(uz_im_control_t *self, struct uz_im_measurement_values m, float speed_ref, uz_3ph_dq_t current_ref) {
    uz_assert_not_NULL(self);
    self->measurements = m;
    self->measurements.v_abc_V = self->previous_applied_v_abc_V;
    if (self->speed_filter != NULL) self->measurements.rotor_speed_rpm = uz_signals_IIR_Filter_sample(self->speed_filter, m.rotor_speed_rpm);
    speed_ref = uz_signals_saturation(speed_ref, self->control_config.setpoint_limits.speed_in_rpm.upper_bound, self->control_config.setpoint_limits.speed_in_rpm.lower_bound);
    current_ref.d = uz_signals_saturation(current_ref.d, self->control_config.setpoint_limits.i_d_in_A.upper_bound, self->control_config.setpoint_limits.i_d_in_A.lower_bound);
    current_ref.q = uz_signals_saturation(current_ref.q, self->control_config.setpoint_limits.i_q_in_A.upper_bound, self->control_config.setpoint_limits.i_q_in_A.lower_bound);
    if (self->setpoint_filter_speed != NULL) speed_ref = uz_signals_IIR_Filter_sample(self->setpoint_filter_speed, speed_ref);
    if (self->setpoint_filter_i_dq != NULL) current_ref = uz_signals_IIR_Filter_dq_setpoint(self->setpoint_filter_i_dq, current_ref);
    self->references.speed_rpm = speed_ref;
    self->references.i_dq_A = current_ref;
    update_observers(self);
    check_safe_operating_region(self);
    if ((!self->enable) || (self->violation != uz_im_control_no_violation) || (self->mode != uz_im_control_mode_foc)) {
        self->previous_applied_v_abc_V = (uz_3ph_abc_t){0};
        return (uz_3ph_dq_t){0};
    }
    if (self->speed_control_enabled) self->references.i_dq_A.q = uz_PI_Controller_sample(self->speed_controller, speed_ref, self->measurements.rotor_speed_rpm, false);
    if (self->actual.rotor_flux_valid == 0.0f) {
        /* Keep d-axis magnetization active for FOC startup, but do not request
         * torque before the rotor-flux direction is observable. */
        self->references.i_dq_A.q = 0.0f;
    }
    self->references.i_dq_A.d = uz_signals_saturation(self->references.i_dq_A.d, self->control_config.setpoint_limits.i_d_in_A.upper_bound, self->control_config.setpoint_limits.i_d_in_A.lower_bound);
    self->references.i_dq_A.q = uz_signals_saturation(self->references.i_dq_A.q, self->control_config.setpoint_limits.i_q_in_A.upper_bound, self->control_config.setpoint_limits.i_q_in_A.lower_bound);
    /* The static PI limits provide an additional SOR-derived plausibility
     * bound. The tighter Current Control space-vector limiter below constrains
     * the combined PI, IM-decoupling and resonant voltage and feeds its state
     * back for integrator clamping. */
    float const voltage_limit_V = self->measurements.v_dc_V / sqrtf(3.0f);
    float vd = uz_PI_Controller_sample(self->current_controller_d, self->references.i_dq_A.d,
        self->actual.i_dq_A.d, self->voltage_vector_saturated_last);
    float vq = uz_PI_Controller_sample(self->current_controller_q, self->references.i_dq_A.q,
        self->actual.i_dq_A.q, self->voltage_vector_saturated_last);
    float ls = uz_IM_config_get_Ls(self->machine_config);
    float lr = uz_IM_config_get_Lr(self->machine_config);
    float sigma_ls = uz_IM_config_get_sigma(self->machine_config) * ls;
    float omega_s = 2.0f * UZ_PIf * self->actual.stator_frequency_Hz;
    self->actual.current_pi_voltage_dq_V = (uz_3ph_dq_t){.d = vd, .q = vq};
    self->actual.decoupling_voltage_dq_V = (uz_3ph_dq_t){0};
    if (self->actual.rotor_flux_valid != 0.0f) {
        self->actual.decoupling_voltage_dq_V = (uz_3ph_dq_t){
            .d = -omega_s * sigma_ls * self->actual.i_dq_A.q,
            .q = omega_s * sigma_ls * self->actual.i_dq_A.d + omega_s * (self->machine_config.Lm_Henry / lr) * self->actual.rotor_flux_magnitude_Vs
        };
    }
    self->actual.resonant_voltage_dq_V = (uz_3ph_dq_t){0};
    if (self->resonant_control_enabled) {
        float const omega = fmaxf(fabsf(omega_s), 1.0f);
        self->actual.resonant_voltage_dq_V.d = uz_resonantController_step(self->resonant_controller_d,
            self->references.i_dq_A.d, self->actual.i_dq_raw_A.d, omega);
        self->actual.resonant_voltage_dq_V.q = uz_resonantController_step(self->resonant_controller_q,
            self->references.i_dq_A.q, self->actual.i_dq_raw_A.q, omega);
    }
    self->references.v_dq_V = (uz_3ph_dq_t){
        .d = self->actual.current_pi_voltage_dq_V.d + self->actual.decoupling_voltage_dq_V.d + self->actual.resonant_voltage_dq_V.d,
        .q = self->actual.current_pi_voltage_dq_V.q + self->actual.decoupling_voltage_dq_V.q + self->actual.resonant_voltage_dq_V.q
    };
    self->actual.voltage_vector_limit_V = voltage_limit_V;
    self->actual.voltage_vector_magnitude_V = hypotf(self->references.v_dq_V.d, self->references.v_dq_V.q);
    bool current_control_clamping = false;
    self->references.v_dq_V = uz_CurrentControl_SpaceVector_Limitation(
        self->references.v_dq_V,
        self->measurements.v_dc_V,
        1.0f / sqrtf(3.0f),
        omega_s,
        self->references.i_dq_A,
        &current_control_clamping);
    self->actual.voltage_vector_saturated = current_control_clamping ? 1.0f : 0.0f;
    self->voltage_vector_saturated_last = self->actual.voltage_vector_saturated != 0.0f;
    self->previous_applied_v_abc_V = uz_transformation_3ph_dq_to_abc(
        self->references.v_dq_V, self->actual.rotor_flux_angle_rad);
    return self->references.v_dq_V;
}

struct uz_DutyCycle_t uz_im_control_sample_duty(uz_im_control_t *self, struct uz_im_measurement_values m, float speed_ref, uz_3ph_dq_t current_ref, float u_f_ref) {
    uz_assert_not_NULL(self);
    self->references.u_f_frequency_Hz = u_f_ref;
    struct uz_DutyCycle_t duty = self->control_config.default_duty_cycle;
    if (self->mode == uz_im_control_mode_u_f) {
        self->measurements = m;
        self->measurements.v_abc_V = self->previous_applied_v_abc_V;
        if (self->speed_filter != NULL) self->measurements.rotor_speed_rpm = uz_signals_IIR_Filter_sample(self->speed_filter, m.rotor_speed_rpm);
        update_observers(self);
        check_safe_operating_region(self);
        if (self->enable && (self->violation == uz_im_control_no_violation)) {
            duty = sample_u_f(self, u_f_ref);
        }
    }
    else {
        uz_3ph_dq_t v = uz_im_control_sample_dq(self, m, speed_ref, current_ref);
        if (self->enable && (self->violation == uz_im_control_no_violation)) {
            duty = uz_Space_Vector_Modulation(v, m.v_dc_V, self->actual.rotor_flux_angle_rad);
        }
    }
    self->references.duty_cycle = duty;
    /* Reconstruct the average inverter pole voltages. Their common-mode
     * component cancels in the observer's Clarke transformation. Keeping the
     * vector here guarantees that cycle k+1 uses the voltage applied in k. */
    self->previous_applied_v_abc_V = (uz_3ph_abc_t){
        .a = duty.DutyCycle_A * m.v_dc_V,
        .b = duty.DutyCycle_B * m.v_dc_V,
        .c = duty.DutyCycle_C * m.v_dc_V,
    };
    return duty;
}

const struct uz_im_actual_data *uz_im_control_get_actual_data(uz_im_control_t *self) { uz_assert_not_NULL(self); return &self->actual; }
const struct uz_im_reference_values *uz_im_control_get_reference_values(uz_im_control_t *self) { uz_assert_not_NULL(self); return &self->references; }
const struct uz_im_measurement_values *uz_im_control_get_im_measurement_values(uz_im_control_t *self) { uz_assert_not_NULL(self); return &self->measurements; }
const struct uz_im_observer_diagnostics_t *uz_im_control_get_observer_diagnostics(uz_im_control_t *self) { uz_assert_not_NULL(self); return uz_im_observer_get_diagnostics(self->observer_instance); }
enum uz_im_control_safe_operating_region_violation uz_im_control_get_safe_operating_area_violation(uz_im_control_t *self) { uz_assert_not_NULL(self); return self->violation; }
void uz_im_control_acknowledge_and_reset_error(uz_im_control_t *self) { uz_assert_not_NULL(self); self->violation = uz_im_control_no_violation; uz_im_control_reset(self); }

void uz_im_control_current_control_set_Kp_id(uz_im_control_t *self, float value) { uz_assert_not_NULL(self); uz_PI_Controller_set_Kp(self->current_controller_d, value); }
void uz_im_control_current_control_set_Ki_id(uz_im_control_t *self, float value) { uz_assert_not_NULL(self); uz_PI_Controller_set_Ki(self->current_controller_d, value); }
void uz_im_control_current_control_set_Kp_iq(uz_im_control_t *self, float value) { uz_assert_not_NULL(self); uz_PI_Controller_set_Kp(self->current_controller_q, value); }
void uz_im_control_current_control_set_Ki_iq(uz_im_control_t *self, float value) { uz_assert_not_NULL(self); uz_PI_Controller_set_Ki(self->current_controller_q, value); }
void uz_im_control_speed_control_set_Kp_speed(uz_im_control_t *self, float value) { uz_assert_not_NULL(self); uz_PI_Controller_set_Kp(self->speed_controller, value); }
void uz_im_control_speed_control_set_Ki_speed(uz_im_control_t *self, float value) { uz_assert_not_NULL(self); uz_PI_Controller_set_Ki(self->speed_controller, value); }
void uz_im_control_set_kalman_process_noise(uz_im_control_t *self, float value) {
    uz_assert_not_NULL(self); uz_assert(value >= 0.0f); self->control_config.kalman_process_noise_A2_per_s = value;
    uz_im_observer_set_process_noise(self->observer_instance, value);
}
void uz_im_control_set_kalman_measurement_noise(uz_im_control_t *self, float value) {
    uz_assert_not_NULL(self); uz_assert(value > 0.0f); self->control_config.kalman_measurement_noise_A2 = value;
    uz_im_observer_set_measurement_noise(self->observer_instance, value);
}
void uz_im_control_set_resonant_parameters(uz_im_control_t *self, float gain_d, float gain_q,
    float harmonic_order, float antiwindup_gain, float voltage_limit_V) {
    uz_assert_not_NULL(self); uz_assert(gain_d >= 0.0f); uz_assert(gain_q >= 0.0f);
    uz_assert(harmonic_order > 0.0f); uz_assert(antiwindup_gain >= 0.0f); uz_assert(voltage_limit_V > 0.0f);
    struct uz_resonantController_config config = {
        .sampling_time = self->control_config.sample_time_s, .fundamental_frequency = 1.0f,
        .harmonic_order = harmonic_order, .antiwindup_gain = antiwindup_gain,
        .lower_limit = -voltage_limit_V, .upper_limit = voltage_limit_V,
    };
    config.gain = gain_d; uz_resonantController_set_config(self->resonant_controller_d, config);
    config.gain = gain_q; uz_resonantController_set_config(self->resonant_controller_q, config);
    self->control_config.resonant_gain_d = gain_d; self->control_config.resonant_gain_q = gain_q;
    self->control_config.resonant_harmonic_order = harmonic_order;
    self->control_config.resonant_antiwindup_gain = antiwindup_gain;
    self->control_config.resonant_voltage_limit_V = voltage_limit_V;
}
void uz_im_control_set_minimum_observer_flux(uz_im_control_t *self, float value) {
    uz_assert_not_NULL(self); uz_assert(value > 0.0f); self->control_config.minimum_observer_flux_Vs = value;
    uz_im_observer_set_minimum_flux(self->observer_instance, value);
}

#endif
