#include "uz_im_control.h"
#include "../uz_global_configuration.h"
#if UZ_IM_CONTROL_MAX_INSTANCES > 0U
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_piController/uz_piController.h"
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
    float psi_alpha_Vs;
    float psi_beta_Vs;
    float kalman_i_alpha_A;
    float kalman_i_beta_A;
    float kalman_p_alpha_A2;
    float kalman_p_beta_A2;
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
    uz_assert(control_config.speed_controller_iq_limit_A > 0.0f);
    uz_assert(control_config.u_f_ratio_V_per_Hz >= 0.0f);
    uz_assert(control_config.u_f_max_frequency_Hz > 0.0f);
    uz_assert(control_config.u_f_max_voltage_V > 0.0f);
    uz_assert(control_config.u_f_frequency_ramp_Hz_per_s > 0.0f);
    uz_assert(control_config.kalman_process_noise_A2_per_s >= 0.0f);
    uz_assert(control_config.kalman_measurement_noise_A2 > 0.0f);
    uz_assert(control_config.minimum_observer_flux_Vs > 0.0f);
    uz_assert(control_config.safe_operating_region.speed_abs_max_rpm > 0.0f);
    uz_assert(control_config.safe_operating_region.phase_current_abs_max_A > 0.0f);
    uz_assert(control_config.safe_operating_region.dc_link_voltage_min_V >= 0.0f);
    uz_assert(control_config.safe_operating_region.dc_link_voltage_max_V > control_config.safe_operating_region.dc_link_voltage_min_V);
    uz_IM_config_assert(machine_config);
}

static uz_PI_Controller *create_pi(float kp, float ki, float ts, float limit) {
    struct uz_PI_Controller_config pi_config = {
        .type = UZ_PI_PARALLEL,
        .Kp = kp,
        .Ki = ki,
        .samplingTime_sec = ts,
        .upper_limit = limit,
        .lower_limit = -limit
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
    self->mode = uz_im_control_mode_foc;
    self->current_controller_d = create_pi(control_config.current_controller_d_kp, control_config.current_controller_d_ki, control_config.sample_time_s, control_config.safe_operating_region.dc_link_voltage_max_V);
    self->current_controller_q = create_pi(control_config.current_controller_q_kp, control_config.current_controller_q_ki, control_config.sample_time_s, control_config.safe_operating_region.dc_link_voltage_max_V);
    self->speed_controller = create_pi(control_config.speed_controller_kp, control_config.speed_controller_ki, control_config.sample_time_s, control_config.speed_controller_iq_limit_A);
    uz_im_control_reset(self);
    return self;
}

void uz_im_control_reset(uz_im_control_t *self) {
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    uz_PI_Controller_reset(self->current_controller_d);
    uz_PI_Controller_reset(self->current_controller_q);
    uz_PI_Controller_reset(self->speed_controller);
    self->psi_alpha_Vs = 0.0f;
    self->psi_beta_Vs = 0.0f;
    self->kalman_i_alpha_A = 0.0f;
    self->kalman_i_beta_A = 0.0f;
    self->kalman_p_alpha_A2 = 1.0f;
    self->kalman_p_beta_A2 = 1.0f;
    self->u_f_frequency_Hz = 0.0f;
    self->u_f_angle_rad = 0.0f;
    self->references = (struct uz_im_reference_values){.duty_cycle = self->control_config.default_duty_cycle};
    self->actual = (struct uz_im_actual_data){0};
}

void uz_im_control_enable(uz_im_control_t *self, bool enable) { uz_assert_not_NULL(self); self->enable = enable; if (!enable) uz_im_control_reset(self); }
void uz_im_control_set_mode(uz_im_control_t *self, enum uz_im_control_mode mode) { uz_assert_not_NULL(self); self->mode = mode; uz_im_control_reset(self); }
void uz_im_control_enable_speed_control(uz_im_control_t *self, bool enable) { uz_assert_not_NULL(self); self->speed_control_enabled = enable; uz_PI_Controller_reset(self->speed_controller); }
void uz_im_control_set_observer(uz_im_control_t *self, enum uz_im_control_observer observer) { uz_assert_not_NULL(self); self->observer = observer; }

static void check_safe_operating_region(uz_im_control_t *self) {
    struct uz_im_control_limits_t l = self->control_config.safe_operating_region;
    if (fabsf(self->measurements.rotor_speed_rpm) > l.speed_abs_max_rpm) self->violation = uz_im_control_speed_violation;
    if ((fabsf(self->measurements.i_abc_A.a) > l.phase_current_abs_max_A) || (fabsf(self->measurements.i_abc_A.b) > l.phase_current_abs_max_A) || (fabsf(self->measurements.i_abc_A.c) > l.phase_current_abs_max_A)) self->violation = uz_im_control_phase_current_violation;
    if ((self->measurements.v_dc_V < l.dc_link_voltage_min_V) || (self->measurements.v_dc_V > l.dc_link_voltage_max_V)) self->violation = uz_im_control_dc_link_voltage_violation;
}

static void update_observers(uz_im_control_t *self) {
    uz_3ph_alphabeta_t current = uz_transformation_3ph_abc_to_alphabeta(self->measurements.i_abc_A);
    uz_3ph_alphabeta_t raw = current;
    if (self->observer == uz_im_control_observer_kalman_rotor_flux_model) {
        self->kalman_p_alpha_A2 += self->control_config.kalman_process_noise_A2_per_s * self->control_config.sample_time_s;
        self->kalman_p_beta_A2 += self->control_config.kalman_process_noise_A2_per_s * self->control_config.sample_time_s;
        float ka = self->kalman_p_alpha_A2 / (self->kalman_p_alpha_A2 + self->control_config.kalman_measurement_noise_A2);
        float kb = self->kalman_p_beta_A2 / (self->kalman_p_beta_A2 + self->control_config.kalman_measurement_noise_A2);
        self->kalman_i_alpha_A += ka * (current.alpha - self->kalman_i_alpha_A);
        self->kalman_i_beta_A += kb * (current.beta - self->kalman_i_beta_A);
        self->kalman_p_alpha_A2 *= 1.0f - ka;
        self->kalman_p_beta_A2 *= 1.0f - kb;
        current.alpha = self->kalman_i_alpha_A;
        current.beta = self->kalman_i_beta_A;
    } else {
        self->kalman_i_alpha_A = current.alpha;
        self->kalman_i_beta_A = current.beta;
    }
    float lr = uz_IM_config_get_Lr(self->machine_config);
    float inv_tr = self->machine_config.Rr_Ohm / lr;
    float omega_r = self->measurements.rotor_speed_rpm * (2.0f * UZ_PIf / 60.0f) * self->machine_config.polePairs;
    float dpsi_a = inv_tr * (self->machine_config.Lm_Henry * current.alpha - self->psi_alpha_Vs) - omega_r * self->psi_beta_Vs;
    float dpsi_b = inv_tr * (self->machine_config.Lm_Henry * current.beta - self->psi_beta_Vs) + omega_r * self->psi_alpha_Vs;
    self->psi_alpha_Vs += self->control_config.sample_time_s * dpsi_a;
    self->psi_beta_Vs += self->control_config.sample_time_s * dpsi_b;
    self->actual.rotor_flux_magnitude_Vs = hypotf(self->psi_alpha_Vs, self->psi_beta_Vs);
    self->actual.rotor_flux_angle_rad = atan2f(self->psi_beta_Vs, self->psi_alpha_Vs);
    self->actual.i_dq_raw_A = uz_transformation_3ph_alphabeta_to_dq(raw, self->actual.rotor_flux_angle_rad);
    self->actual.i_dq_A = uz_transformation_3ph_alphabeta_to_dq(current, self->actual.rotor_flux_angle_rad);
    float slip = 0.0f;
    if (self->actual.rotor_flux_magnitude_Vs > self->control_config.minimum_observer_flux_Vs) slip = (self->machine_config.Rr_Ohm * self->machine_config.Lm_Henry / lr) * self->actual.i_dq_A.q / self->actual.rotor_flux_magnitude_Vs;
    self->actual.rotor_electrical_frequency_Hz = omega_r / (2.0f * UZ_PIf);
    self->actual.slip_frequency_Hz = slip / (2.0f * UZ_PIf);
    self->actual.stator_frequency_Hz = (omega_r + slip) / (2.0f * UZ_PIf);
    if (!isfinite(self->actual.rotor_flux_magnitude_Vs)) self->violation = uz_im_control_observer_violation;
}

static struct uz_DutyCycle_t sample_u_f(uz_im_control_t *self, float target_Hz) {
    float target = fminf(fmaxf(target_Hz, -self->control_config.u_f_max_frequency_Hz), self->control_config.u_f_max_frequency_Hz);
    float step = self->control_config.u_f_frequency_ramp_Hz_per_s * self->control_config.sample_time_s;
    float error = target - self->u_f_frequency_Hz;
    self->u_f_frequency_Hz += fminf(fmaxf(error, -step), step);
    float magnitude = fminf(fabsf(self->u_f_frequency_Hz) * self->control_config.u_f_ratio_V_per_Hz + ((fabsf(self->u_f_frequency_Hz) > 0.1f) ? self->control_config.u_f_boost_voltage_V : 0.0f), self->control_config.u_f_max_voltage_V);
    self->u_f_angle_rad = fmodf(self->u_f_angle_rad + 2.0f * UZ_PIf * self->u_f_frequency_Hz * self->control_config.sample_time_s, 2.0f * UZ_PIf);
    self->actual.u_f_applied_voltage_V = magnitude;
    self->references.v_dq_V = (uz_3ph_dq_t){.d = magnitude * sqrtf(2.0f / 3.0f)};
    return uz_Space_Vector_Modulation(self->references.v_dq_V, self->measurements.v_dc_V, self->u_f_angle_rad);
}

uz_3ph_dq_t uz_im_control_sample_dq(uz_im_control_t *self, struct uz_im_measurement_values m, float speed_ref, uz_3ph_dq_t current_ref) {
    uz_assert_not_NULL(self);
    self->measurements = m;
    self->references.speed_rpm = speed_ref;
    self->references.i_dq_A = current_ref;
    check_safe_operating_region(self);
    update_observers(self);
    if ((!self->enable) || (self->violation != uz_im_control_no_violation) || (self->mode != uz_im_control_mode_foc)) return (uz_3ph_dq_t){0};
    if (self->speed_control_enabled) self->references.i_dq_A.q = uz_PI_Controller_sample(self->speed_controller, speed_ref, m.rotor_speed_rpm, false);
    float vd = uz_PI_Controller_sample(self->current_controller_d, self->references.i_dq_A.d, self->actual.i_dq_A.d, false);
    float vq = uz_PI_Controller_sample(self->current_controller_q, self->references.i_dq_A.q, self->actual.i_dq_A.q, false);
    float ls = uz_IM_config_get_Ls(self->machine_config);
    float lr = uz_IM_config_get_Lr(self->machine_config);
    float sigma_ls = uz_IM_config_get_sigma(self->machine_config) * ls;
    float omega_s = 2.0f * UZ_PIf * self->actual.stator_frequency_Hz;
    self->references.v_dq_V = (uz_3ph_dq_t){.d = vd - omega_s * sigma_ls * self->actual.i_dq_A.q, .q = vq + omega_s * sigma_ls * self->actual.i_dq_A.d + omega_s * (self->machine_config.Lm_Henry / lr) * self->actual.rotor_flux_magnitude_Vs};
    return self->references.v_dq_V;
}

struct uz_DutyCycle_t uz_im_control_sample_duty(uz_im_control_t *self, struct uz_im_measurement_values m, float speed_ref, uz_3ph_dq_t current_ref, float u_f_ref) {
    self->references.u_f_frequency_Hz = u_f_ref;
    if (self->mode == uz_im_control_mode_u_f) {
        self->measurements = m;
        check_safe_operating_region(self);
        update_observers(self);
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

#endif
