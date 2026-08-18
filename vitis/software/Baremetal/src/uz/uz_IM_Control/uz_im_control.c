#include "uz_im_control.h"
#include "../uz_global_configuration.h"
#if UZ_IM_CONTROL_MAX_INSTANCES > 0U
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_piController/uz_piController.h"
#include "../uz_ResonantController/uz_resonant_controller.h"
#include "../uz_controller_setpoint_filter/uz_controller_setpoint_filter.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>

struct uz_im_control_t {
    bool is_ready;
    bool enable;
    bool speed_control_enabled;
    bool u_f_observer_enabled;
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
    bool kalman_enabled_last;
    bool voltage_vector_saturated_last;
    float psi_alpha_Vs;
    float psi_beta_Vs;
    float kalman_i_alpha_A;
    float kalman_i_beta_A;
    float kalman_p_alpha_A2;
    float kalman_p_beta_A2;
    float u_f_frequency_Hz;
    float u_f_angle_rad;
    float previous_flux_angle_rad;
    bool previous_flux_angle_valid;
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
    uz_assert(control_config.kalman_measurement_noise_A2 > 0.0f);
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
    self->u_f_observer_enabled = false;
    self->observer = control_config.observer;
    self->resonant_control_enabled = control_config.enable_resonant_control;
    self->mode = uz_im_control_mode_foc;
    self->current_controller_d = create_pi(control_config.current_controller_d_kp, control_config.current_controller_d_ki, control_config.sample_time_s, control_config.safe_operating_region.v_dc_in_V.upper_bound, -control_config.safe_operating_region.v_dc_in_V.upper_bound);
    self->current_controller_q = create_pi(control_config.current_controller_q_kp, control_config.current_controller_q_ki, control_config.sample_time_s, control_config.safe_operating_region.v_dc_in_V.upper_bound, -control_config.safe_operating_region.v_dc_in_V.upper_bound);
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
    self->psi_alpha_Vs = 0.0f;
    self->psi_beta_Vs = 0.0f;
    self->kalman_i_alpha_A = 0.0f;
    self->kalman_i_beta_A = 0.0f;
    self->kalman_p_alpha_A2 = 1.0f;
    self->kalman_p_beta_A2 = 1.0f;
    self->kalman_enabled_last = false;
    self->u_f_frequency_Hz = 0.0f;
    self->u_f_angle_rad = 0.0f;
    self->previous_flux_angle_rad = 0.0f;
    self->previous_flux_angle_valid = false;
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
void uz_im_control_set_observer(uz_im_control_t *self, enum uz_im_control_observer observer) { uz_assert_not_NULL(self); self->observer = observer; }
void uz_im_control_enable_u_f_observer(uz_im_control_t *self, bool enable) { uz_assert_not_NULL(self); self->u_f_observer_enabled = enable; }
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
    uz_3ph_alphabeta_t current = uz_transformation_3ph_abc_to_alphabeta(self->measurements.i_abc_A);
    uz_3ph_alphabeta_t raw = current;
    if (self->observer == uz_im_control_observer_kalman_rotor_flux_model) {
        self->kalman_p_alpha_A2 += self->control_config.kalman_process_noise_A2_per_s * self->control_config.sample_time_s;
        self->kalman_p_beta_A2 += self->control_config.kalman_process_noise_A2_per_s * self->control_config.sample_time_s;
        float ka = self->kalman_p_alpha_A2 / (self->kalman_p_alpha_A2 + self->control_config.kalman_measurement_noise_A2);
        float kb = self->kalman_p_beta_A2 / (self->kalman_p_beta_A2 + self->control_config.kalman_measurement_noise_A2);
        self->actual.kalman_innovation_alpha_A = current.alpha - self->kalman_i_alpha_A;
        self->actual.kalman_innovation_beta_A = current.beta - self->kalman_i_beta_A;
        self->kalman_i_alpha_A += ka * self->actual.kalman_innovation_alpha_A;
        self->kalman_i_beta_A += kb * self->actual.kalman_innovation_beta_A;
        self->kalman_p_alpha_A2 *= 1.0f - ka;
        self->kalman_p_beta_A2 *= 1.0f - kb;
        current.alpha = self->kalman_i_alpha_A;
        current.beta = self->kalman_i_beta_A;
    } else {
        self->actual.kalman_innovation_alpha_A = 0.0f;
        self->actual.kalman_innovation_beta_A = 0.0f;
        if (self->kalman_enabled_last) {
            self->kalman_p_alpha_A2 = 1.0f;
            self->kalman_p_beta_A2 = 1.0f;
        }
        self->kalman_i_alpha_A = current.alpha;
        self->kalman_i_beta_A = current.beta;
    }
    self->kalman_enabled_last = self->observer == uz_im_control_observer_kalman_rotor_flux_model;
    float lr = uz_IM_config_get_Lr(self->machine_config);
    float inv_tr = self->machine_config.Rr_Ohm / lr;
    float omega_r = self->measurements.rotor_speed_rpm * (2.0f * UZ_PIf / 60.0f) * self->machine_config.polePairs;
    float dpsi_a = inv_tr * (self->machine_config.Lm_Henry * current.alpha - self->psi_alpha_Vs) - omega_r * self->psi_beta_Vs;
    float dpsi_b = inv_tr * (self->machine_config.Lm_Henry * current.beta - self->psi_beta_Vs) + omega_r * self->psi_alpha_Vs;
    self->psi_alpha_Vs += self->control_config.sample_time_s * dpsi_a;
    self->psi_beta_Vs += self->control_config.sample_time_s * dpsi_b;
    self->actual.rotor_flux_magnitude_Vs = hypotf(self->psi_alpha_Vs, self->psi_beta_Vs);
    self->actual.rotor_flux_angle_rad = atan2f(self->psi_beta_Vs, self->psi_alpha_Vs);
    bool const flux_valid = isfinite(self->actual.rotor_flux_magnitude_Vs)
        && (self->actual.rotor_flux_magnitude_Vs > self->control_config.minimum_observer_flux_Vs);
    self->actual.rotor_flux_valid = flux_valid ? 1.0f : 0.0f;
    self->actual.flux_angle_step_rad = 0.0f;
    if (flux_valid && self->previous_flux_angle_valid) {
        float const delta = self->actual.rotor_flux_angle_rad - self->previous_flux_angle_rad;
        self->actual.flux_angle_step_rad = atan2f(sinf(delta), cosf(delta));
    }
    self->actual.flux_angle_step_violation =
        (fabsf(self->actual.flux_angle_step_rad) > self->control_config.maximum_flux_angle_step_rad) ? 1.0f : 0.0f;
    self->previous_flux_angle_rad = self->actual.rotor_flux_angle_rad;
    self->previous_flux_angle_valid = flux_valid;
    self->actual.phase_current_sum_A = self->measurements.i_abc_A.a
        + self->measurements.i_abc_A.b + self->measurements.i_abc_A.c;
    self->actual.phase_current_sum_violation =
        (fabsf(self->actual.phase_current_sum_A) > self->control_config.maximum_phase_current_sum_A) ? 1.0f : 0.0f;
    self->actual.rotor_electrical_angle_rad = fmodf(self->machine_config.polePairs * self->measurements.rotor_mechanical_angle_rad, 2.0f * UZ_PIf);
    if (self->actual.rotor_electrical_angle_rad < 0.0f) self->actual.rotor_electrical_angle_rad += 2.0f * UZ_PIf;
    float const flux_rotor_angle_delta = self->actual.rotor_flux_angle_rad - self->actual.rotor_electrical_angle_rad;
    self->actual.flux_rotor_angle_difference_rad = atan2f(sinf(flux_rotor_angle_delta), cosf(flux_rotor_angle_delta));
    self->actual.i_dq_raw_A = uz_transformation_3ph_alphabeta_to_dq(raw, self->actual.rotor_flux_angle_rad);
    self->actual.i_dq_A = uz_transformation_3ph_alphabeta_to_dq(current, self->actual.rotor_flux_angle_rad);
    float slip = 0.0f;
    self->actual.slip_frequency_limited = 0.0f;
    if (flux_valid) {
        slip = (self->machine_config.Rr_Ohm * self->machine_config.Lm_Henry / lr)
            * self->actual.i_dq_A.q / self->actual.rotor_flux_magnitude_Vs;
        float const maximum_slip = 2.0f * UZ_PIf * self->control_config.maximum_slip_frequency_Hz;
        float const limited_slip = uz_signals_saturation(slip, maximum_slip, -maximum_slip);
        self->actual.slip_frequency_limited = (limited_slip != slip) ? 1.0f : 0.0f;
        slip = limited_slip;
    }
    self->actual.rotor_electrical_angular_speed_rad_per_s = omega_r;
    self->actual.slip_angular_frequency_rad_per_s = slip;
    self->actual.stator_angular_frequency_rad_per_s = omega_r + slip;
    self->actual.rotor_electrical_frequency_Hz = self->actual.rotor_electrical_angular_speed_rad_per_s / (2.0f * UZ_PIf);
    self->actual.slip_frequency_Hz = self->actual.slip_angular_frequency_rad_per_s / (2.0f * UZ_PIf);
    self->actual.stator_frequency_Hz = self->actual.stator_angular_frequency_rad_per_s / (2.0f * UZ_PIf);
    self->actual.slip_percent = fabsf(self->actual.stator_frequency_Hz) > 1.0e-3f
        ? 100.0f * self->actual.slip_frequency_Hz / self->actual.stator_frequency_Hz
        : 0.0f;
    if ((!isfinite(self->actual.rotor_flux_magnitude_Vs)) && (self->violation == uz_im_control_no_violation)) {
        self->violation = uz_im_control_observer_violation;
        self->actual.safe_operating_region_status = (uint32_t)self->violation;
    }
}

static struct uz_DutyCycle_t sample_u_f(uz_im_control_t *self, float target_Hz) {
    float target = fminf(fmaxf(target_Hz, -self->control_config.u_f_max_frequency_Hz), self->control_config.u_f_max_frequency_Hz);
    float step = self->control_config.u_f_frequency_ramp_Hz_per_s * self->control_config.sample_time_s;
    float error = target - self->u_f_frequency_Hz;
    self->u_f_frequency_Hz += fminf(fmaxf(error, -step), step);
    float const requested_line_voltage_rms_V = fminf(fabsf(self->u_f_frequency_Hz) * self->control_config.u_f_ratio_V_per_Hz + ((fabsf(self->u_f_frequency_Hz) > 0.1f) ? self->control_config.u_f_boost_voltage_V : 0.0f), self->control_config.u_f_max_voltage_V);
    float const requested_vector_magnitude_V = requested_line_voltage_rms_V * sqrtf(2.0f / 3.0f);
    float const voltage_vector_limit_V = self->measurements.v_dc_V / sqrtf(3.0f);
    float applied_vector_magnitude_V = requested_vector_magnitude_V;
    self->actual.voltage_vector_magnitude_V = requested_vector_magnitude_V;
    self->actual.voltage_vector_limit_V = voltage_vector_limit_V;
    self->actual.voltage_vector_saturated = requested_vector_magnitude_V > voltage_vector_limit_V ? 1.0f : 0.0f;
    if (self->control_config.enable_voltage_vector_limiting && (self->actual.voltage_vector_saturated != 0.0f)) {
        applied_vector_magnitude_V = voltage_vector_limit_V;
    }
    self->voltage_vector_saturated_last = self->actual.voltage_vector_saturated != 0.0f;
    self->u_f_angle_rad = fmodf(self->u_f_angle_rad + 2.0f * UZ_PIf * self->u_f_frequency_Hz * self->control_config.sample_time_s, 2.0f * UZ_PIf);
    if (self->u_f_angle_rad < 0.0f) self->u_f_angle_rad += 2.0f * UZ_PIf;
    self->actual.u_f_command_frequency_Hz = self->u_f_frequency_Hz;
    self->actual.u_f_electrical_angle_rad = self->u_f_angle_rad;
    self->actual.u_f_applied_voltage_V = applied_vector_magnitude_V * sqrtf(3.0f / 2.0f);
    self->references.v_dq_V = (uz_3ph_dq_t){.d = applied_vector_magnitude_V};
    return uz_Space_Vector_Modulation(self->references.v_dq_V, self->measurements.v_dc_V, self->u_f_angle_rad);
}

uz_3ph_dq_t uz_im_control_sample_dq(uz_im_control_t *self, struct uz_im_measurement_values m, float speed_ref, uz_3ph_dq_t current_ref) {
    uz_assert_not_NULL(self);
    self->measurements = m;
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
    if ((!self->enable) || (self->violation != uz_im_control_no_violation) || (self->mode != uz_im_control_mode_foc)) return (uz_3ph_dq_t){0};
    if (self->speed_control_enabled) self->references.i_dq_A.q = uz_PI_Controller_sample(self->speed_controller, speed_ref, self->measurements.rotor_speed_rpm, false);
    if (self->actual.rotor_flux_valid == 0.0f) {
        /* Keep d-axis magnetization active for FOC startup, but do not request
         * torque before the rotor-flux direction is observable. */
        self->references.i_dq_A.q = 0.0f;
    }
    self->references.i_dq_A.d = uz_signals_saturation(self->references.i_dq_A.d, self->control_config.setpoint_limits.i_d_in_A.upper_bound, self->control_config.setpoint_limits.i_d_in_A.lower_bound);
    self->references.i_dq_A.q = uz_signals_saturation(self->references.i_dq_A.q, self->control_config.setpoint_limits.i_q_in_A.upper_bound, self->control_config.setpoint_limits.i_q_in_A.lower_bound);
    /* Keep the PI outputs inside the linear SVM voltage range of the measured
     * DC link. A fixed limit based on the SOR maximum can heavily overmodulate
     * the inverter when the testbench is operated at a lower DC voltage. */
    float const voltage_limit_V = self->measurements.v_dc_V / sqrtf(3.0f);
    uz_PI_Controller_update_limits(self->current_controller_d, voltage_limit_V, -voltage_limit_V);
    uz_PI_Controller_update_limits(self->current_controller_q, voltage_limit_V, -voltage_limit_V);
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
    self->actual.voltage_vector_saturated = 0.0f;
    if (self->control_config.enable_voltage_vector_limiting
        && (self->actual.voltage_vector_magnitude_V > voltage_limit_V)
        && (self->actual.voltage_vector_magnitude_V > 0.0f)) {
        float const scale = voltage_limit_V / self->actual.voltage_vector_magnitude_V;
        self->references.v_dq_V.d *= scale;
        self->references.v_dq_V.q *= scale;
        self->actual.voltage_vector_saturated = 1.0f;
    }
    self->voltage_vector_saturated_last = self->actual.voltage_vector_saturated != 0.0f;
    return self->references.v_dq_V;
}

struct uz_DutyCycle_t uz_im_control_sample_duty(uz_im_control_t *self, struct uz_im_measurement_values m, float speed_ref, uz_3ph_dq_t current_ref, float u_f_ref) {
    self->references.u_f_frequency_Hz = u_f_ref;
    if (self->mode == uz_im_control_mode_u_f) {
        self->measurements = m;
        if (self->speed_filter != NULL) self->measurements.rotor_speed_rpm = uz_signals_IIR_Filter_sample(self->speed_filter, m.rotor_speed_rpm);
        if (self->u_f_observer_enabled) {
            update_observers(self);
        }
        check_safe_operating_region(self);
        if ((!self->enable) || (self->violation != uz_im_control_no_violation)) return self->control_config.default_duty_cycle;
        self->references.duty_cycle = sample_u_f(self, u_f_ref);
    }
    else {
        uz_3ph_dq_t v = uz_im_control_sample_dq(self, m, speed_ref, current_ref);
        if ((!self->enable) || (self->violation != uz_im_control_no_violation)) return self->control_config.default_duty_cycle;
        self->references.duty_cycle = uz_Space_Vector_Modulation(v, m.v_dc_V, self->actual.rotor_flux_angle_rad);
    }
    return self->references.duty_cycle;
}

const struct uz_im_actual_data *uz_im_control_get_actual_data(uz_im_control_t *self) { uz_assert_not_NULL(self); return &self->actual; }
const struct uz_im_reference_values *uz_im_control_get_reference_values(uz_im_control_t *self) { uz_assert_not_NULL(self); return &self->references; }
const struct uz_im_measurement_values *uz_im_control_get_im_measurement_values(uz_im_control_t *self) { uz_assert_not_NULL(self); return &self->measurements; }
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
}
void uz_im_control_set_kalman_measurement_noise(uz_im_control_t *self, float value) {
    uz_assert_not_NULL(self); uz_assert(value > 0.0f); self->control_config.kalman_measurement_noise_A2 = value;
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
}

#endif
