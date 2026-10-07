#include "uz_im_observer.h"
#include "../uz_global_configuration.h"
#if UZ_IM_CONTROL_MAX_INSTANCES > 0U
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_pos_to_speed_pll/uz_pos_to_speed_pll.h"
#include <math.h>

struct uz_im_observer {
    struct uz_im_observer_config control_config;
    uz_IM_t machine_config;
    enum uz_im_control_observer observer;
    struct uz_im_observer_input measurements;
    struct uz_im_observer_output output;
    struct uz_im_observer_diagnostics_t observer_diagnostics;
    uz_pos_to_speed_pll_t *deterministic_observer_pll;
    uz_pos_to_speed_pll_t *kalman_observer_pll;
    float previous_flux_angle_rad;
    bool previous_flux_angle_valid;
    bool numerical_failure;
};
static uint32_t instance_counter;
static uz_im_observer_t instances[UZ_IM_CONTROL_MAX_INSTANCES];

uz_im_observer_t *uz_im_observer_init(struct uz_im_observer_config config, uz_IM_t machine) {
    uz_IM_config_assert(machine);
    uz_assert(config.sample_time_s > 0.0f);
    uz_assert(config.kalman_process_noise_A2_per_s >= 0.0f);
    uz_assert(config.kalman_measurement_noise_A2 > 0.0f);
    uz_assert(config.kalman_flux_process_noise_Vs2_per_s >= 0.0f);
    uz_assert(config.minimum_observer_flux_Vs > 0.0f);
    uz_assert(config.maximum_flux_angle_step_rad > 0.0f);
    uz_assert(config.maximum_phase_current_sum_A > 0.0f);
    uz_assert(config.maximum_slip_frequency_Hz > 0.0f);
    uz_assert(config.observer_pll_kp >= 0.0f);
    uz_assert(config.observer_pll_ki >= 0.0f);
    uz_assert((config.observer == uz_im_control_observer_rotor_flux_model)
        || (config.observer == uz_im_control_observer_kalman_rotor_flux_model)
        || (config.observer == uz_im_control_observer_filtered_rotor_flux_model));
    uz_assert(instance_counter < UZ_IM_CONTROL_MAX_INSTANCES);
    uz_im_observer_t *self = &instances[instance_counter++];
    self->control_config = config;
    self->machine_config = machine;
    self->observer = config.observer;
    struct uz_pos_to_speed_pll_config_t const pll_config = {
        .machine_polepairs = machine.polePairs,
        .kp_pll = config.observer_pll_kp,
        .ki_pll = config.observer_pll_ki,
        .sampling_time_in_seconds = config.sample_time_s,
    };
    self->deterministic_observer_pll = uz_pos_to_speed_pll_init(pll_config);
    self->kalman_observer_pll = uz_pos_to_speed_pll_init(pll_config);
    uz_im_observer_reset(self);
    return self;
}

void uz_im_observer_reset(uz_im_observer_t *self) {
    uz_assert_not_NULL(self);
    self->observer_diagnostics = (struct uz_im_observer_diagnostics_t){0};
    for (uint32_t i = 0U; i < 4U; i++) {
        self->observer_diagnostics.covariance[i][i] = 1.0f;
    }
    self->observer_diagnostics.simplified_current_covariance_alpha_A2 = 1.0f;
    self->observer_diagnostics.simplified_current_covariance_beta_A2 = 1.0f;
    uz_pos_to_speed_pll_reset(self->deterministic_observer_pll);
    uz_pos_to_speed_pll_reset(self->kalman_observer_pll);
    self->previous_flux_angle_rad = 0.0f;
    self->previous_flux_angle_valid = false;
    self->numerical_failure = false;
    self->output = (struct uz_im_observer_output){0};
}

void uz_im_observer_set_mode(uz_im_observer_t *self, enum uz_im_control_observer observer) {
    uz_assert_not_NULL(self);
    uz_assert((observer == uz_im_control_observer_rotor_flux_model)
        || (observer == uz_im_control_observer_kalman_rotor_flux_model)
        || (observer == uz_im_control_observer_filtered_rotor_flux_model));
    if (self->observer != observer) {
        self->observer = observer;
        uz_im_observer_reset(self);
    }
}

static float observer_pll_step(uz_pos_to_speed_pll_t *pll, float flux_angle_rad) {
    float wrapped_angle = flux_angle_rad;
    if (wrapped_angle < 0.0f) wrapped_angle += 2.0f * UZ_PIf;
    wrapped_angle = fminf(fmaxf(wrapped_angle, 0.0f), 2.0f * UZ_PIf);
    uz_pos_to_speed_pll_step(pll, wrapped_angle);
    /* Preserve the direction estimated from the flux-angle rotation. Taking
     * the absolute value here makes the stator frequency always positive and
     * therefore produces an incorrect slip for reverse rotation. */
    return uz_pos_to_speed_pll_get_omega_mech_si(pll) / (2.0f * UZ_PIf);
}

static void update_deterministic_observer(uz_im_observer_t *self, uz_3ph_alphabeta_t current) {
    struct uz_im_observer_diagnostics_t *diagnostics = &self->observer_diagnostics;
    float const ts = self->control_config.sample_time_s;
    float const lr = uz_IM_config_get_Lr(self->machine_config);
    float const inverse_tau_r = self->machine_config.Rr_Ohm / lr;
    float const omega_r = self->measurements.rotor_speed_rpm * (2.0f * UZ_PIf / 60.0f)
        * self->machine_config.polePairs;
    float const half_ts = 0.5f * ts;
    float const m00 = 1.0f + half_ts * inverse_tau_r;
    float const m01 = half_ts * omega_r;
    float const m10 = -half_ts * omega_r;
    float const m11 = m00;
    float const n00 = 1.0f - half_ts * inverse_tau_r;
    float const n01 = -half_ts * omega_r;
    float const n10 = half_ts * omega_r;
    float const n11 = n00;
    float const current_gain = ts * self->machine_config.Lm_Henry * inverse_tau_r;
    float const rhs_alpha = n00 * diagnostics->deterministic_flux_alpha_Vs
        + n01 * diagnostics->deterministic_flux_beta_Vs + current_gain * current.alpha;
    float const rhs_beta = n10 * diagnostics->deterministic_flux_alpha_Vs
        + n11 * diagnostics->deterministic_flux_beta_Vs + current_gain * current.beta;
    float const determinant = m00 * m11 - m01 * m10;
    if (fabsf(determinant) < 1.0e-12f) {
        diagnostics->deterministic_flux_alpha_Vs = 0.0f;
        diagnostics->deterministic_flux_beta_Vs = 0.0f;
        self->numerical_failure = true;
        return;
    }
    diagnostics->deterministic_flux_alpha_Vs = (m11 * rhs_alpha - m01 * rhs_beta) / determinant;
    diagnostics->deterministic_flux_beta_Vs = (-m10 * rhs_alpha + m00 * rhs_beta) / determinant;
    self->output.rotor_flux_angle_rad = atan2f(diagnostics->deterministic_flux_beta_Vs,
        diagnostics->deterministic_flux_alpha_Vs);
    self->output.rotor_flux_magnitude_Vs = hypotf(diagnostics->deterministic_flux_alpha_Vs,
        diagnostics->deterministic_flux_beta_Vs);
    diagnostics->deterministic_stator_frequency_Hz = observer_pll_step(self->deterministic_observer_pll,
        self->output.rotor_flux_angle_rad);
    self->output.i_dq_A = uz_transformation_3ph_alphabeta_to_dq(current, self->output.rotor_flux_angle_rad);
}

static uz_3ph_alphabeta_t update_simplified_current_kalman(
    uz_im_observer_t *self, uz_3ph_alphabeta_t measured_current) {
    struct uz_im_observer_diagnostics_t *diagnostics = &self->observer_diagnostics;
    float const process_noise = self->control_config.kalman_process_noise_A2_per_s
        * self->control_config.sample_time_s;
    diagnostics->simplified_current_covariance_alpha_A2 += process_noise;
    diagnostics->simplified_current_covariance_beta_A2 += process_noise;
    float const gain_alpha = diagnostics->simplified_current_covariance_alpha_A2
        / (diagnostics->simplified_current_covariance_alpha_A2
            + self->control_config.kalman_measurement_noise_A2);
    float const gain_beta = diagnostics->simplified_current_covariance_beta_A2
        / (diagnostics->simplified_current_covariance_beta_A2
            + self->control_config.kalman_measurement_noise_A2);
    diagnostics->innovation[0] = measured_current.alpha - diagnostics->simplified_current_alpha_A;
    diagnostics->innovation[1] = measured_current.beta - diagnostics->simplified_current_beta_A;
    diagnostics->simplified_current_alpha_A += gain_alpha * diagnostics->innovation[0];
    diagnostics->simplified_current_beta_A += gain_beta * diagnostics->innovation[1];
    diagnostics->simplified_current_covariance_alpha_A2 *= 1.0f - gain_alpha;
    diagnostics->simplified_current_covariance_beta_A2 *= 1.0f - gain_beta;
    self->output.kalman_innovation_alpha_A = diagnostics->innovation[0];
    self->output.kalman_innovation_beta_A = diagnostics->innovation[1];
    return (uz_3ph_alphabeta_t){
        .alpha = diagnostics->simplified_current_alpha_A,
        .beta = diagnostics->simplified_current_beta_A,
    };
}

static bool update_kalman_observer(uz_im_observer_t *self, uz_3ph_alphabeta_t measured_current) {
    struct uz_im_observer_diagnostics_t *diagnostics = &self->observer_diagnostics;
    float const ts = self->control_config.sample_time_s;
    float const ls = uz_IM_config_get_Ls(self->machine_config);
    float const lr = uz_IM_config_get_Lr(self->machine_config);
    float const sigma_ls = uz_IM_config_get_sigma(self->machine_config) * ls;
    float const lm = self->machine_config.Lm_Henry;
    float const rr = self->machine_config.Rr_Ohm;
    float const omega_r = self->measurements.rotor_speed_rpm * (2.0f * UZ_PIf / 60.0f)
        * self->machine_config.polePairs;
    float const a = -(self->machine_config.Rs_Ohm / sigma_ls
        + lm * lm * rr / (sigma_ls * lr * lr));
    float const b = lm * rr / (sigma_ls * lr * lr);
    float const c = lm / (sigma_ls * lr);
    float const d = lm * rr / lr;
    float const e = rr / lr;
    float A[4][4] = {
        {1.0f + a * ts, 0.0f, b * ts, c * omega_r * ts},
        {0.0f, 1.0f + a * ts, -c * omega_r * ts, b * ts},
        {d * ts, 0.0f, 1.0f - e * ts, -omega_r * ts},
        {0.0f, d * ts, omega_r * ts, 1.0f - e * ts},
    };
    float const input_gain = ts / sigma_ls;
    float const voltage_input[4] = {
        input_gain * ((2.0f / 3.0f) * self->measurements.v_abc_V.a
            - (1.0f / 3.0f) * self->measurements.v_abc_V.b
            - (1.0f / 3.0f) * self->measurements.v_abc_V.c),
        input_gain * ((self->measurements.v_abc_V.b - self->measurements.v_abc_V.c) / sqrtf(3.0f)),
        0.0f,
        0.0f,
    };
    float predicted_state[4] = {0};
    float AP[4][4] = {{0}};
    float predicted_covariance[4][4] = {{0}};
    for (uint32_t row = 0U; row < 4U; row++) {
        predicted_state[row] = voltage_input[row];
        for (uint32_t column = 0U; column < 4U; column++) {
            predicted_state[row] += A[row][column] * diagnostics->state[column];
            for (uint32_t k = 0U; k < 4U; k++) {
                AP[row][column] += A[row][k] * diagnostics->covariance[k][column];
            }
        }
    }
    float const current_process_noise = self->control_config.kalman_process_noise_A2_per_s * ts;
    float const flux_process_noise = self->control_config.kalman_flux_process_noise_Vs2_per_s * ts;
    for (uint32_t row = 0U; row < 4U; row++) {
        for (uint32_t column = 0U; column < 4U; column++) {
            for (uint32_t k = 0U; k < 4U; k++) {
                predicted_covariance[row][column] += AP[row][k] * A[column][k];
            }
        }
        predicted_covariance[row][row] += (row < 2U) ? current_process_noise : flux_process_noise;
    }
    diagnostics->innovation[0] = measured_current.alpha - predicted_state[0];
    diagnostics->innovation[1] = measured_current.beta - predicted_state[1];
    diagnostics->innovation_covariance[0][0] = predicted_covariance[0][0]
        + self->control_config.kalman_measurement_noise_A2;
    diagnostics->innovation_covariance[0][1] = predicted_covariance[0][1];
    diagnostics->innovation_covariance[1][0] = predicted_covariance[1][0];
    diagnostics->innovation_covariance[1][1] = predicted_covariance[1][1]
        + self->control_config.kalman_measurement_noise_A2;
    float const determinant = diagnostics->innovation_covariance[0][0]
        * diagnostics->innovation_covariance[1][1]
        - diagnostics->innovation_covariance[0][1] * diagnostics->innovation_covariance[1][0];
    if ((!isfinite(determinant)) || (fabsf(determinant) < 1.0e-10f)) return false;
    float const inverse_determinant = 1.0f / determinant;
    float const inverse_S[2][2] = {
        {diagnostics->innovation_covariance[1][1] * inverse_determinant,
            -diagnostics->innovation_covariance[0][1] * inverse_determinant},
        {-diagnostics->innovation_covariance[1][0] * inverse_determinant,
            diagnostics->innovation_covariance[0][0] * inverse_determinant},
    };
    for (uint32_t row = 0U; row < 4U; row++) {
        diagnostics->kalman_gain[row][0] = predicted_covariance[row][0] * inverse_S[0][0]
            + predicted_covariance[row][1] * inverse_S[1][0];
        diagnostics->kalman_gain[row][1] = predicted_covariance[row][0] * inverse_S[0][1]
            + predicted_covariance[row][1] * inverse_S[1][1];
        diagnostics->state[row] = predicted_state[row]
            + diagnostics->kalman_gain[row][0] * diagnostics->innovation[0]
            + diagnostics->kalman_gain[row][1] * diagnostics->innovation[1];
    }
    for (uint32_t row = 0U; row < 4U; row++) {
        for (uint32_t column = 0U; column < 4U; column++) {
            diagnostics->covariance[row][column] = predicted_covariance[row][column]
                - diagnostics->kalman_gain[row][0] * predicted_covariance[0][column]
                - diagnostics->kalman_gain[row][1] * predicted_covariance[1][column];
        }
        if ((!isfinite(diagnostics->state[row])) || (!isfinite(diagnostics->covariance[row][row]))) return false;
    }
    self->output.rotor_flux_angle_rad = atan2f(diagnostics->state[3], diagnostics->state[2]);
    self->output.rotor_flux_magnitude_Vs = hypotf(diagnostics->state[2], diagnostics->state[3]);
    self->output.i_dq_A = uz_transformation_3ph_alphabeta_to_dq(
        (uz_3ph_alphabeta_t){.alpha = diagnostics->state[0], .beta = diagnostics->state[1]},
        self->output.rotor_flux_angle_rad);
    self->output.kalman_innovation_alpha_A = diagnostics->innovation[0];
    self->output.kalman_innovation_beta_A = diagnostics->innovation[1];
    return true;
}

bool uz_im_observer_sample(uz_im_observer_t *self, struct uz_im_observer_input input) {
    uz_assert_not_NULL(self);
    self->measurements = input;
    uz_3ph_alphabeta_t const raw_current = uz_transformation_3ph_abc_to_alphabeta(self->measurements.i_abc_A);
    float const omega_r = self->measurements.rotor_speed_rpm * (2.0f * UZ_PIf / 60.0f)
        * self->machine_config.polePairs;
    bool observer_valid = true;
    if (self->observer == uz_im_control_observer_kalman_rotor_flux_model) {
        observer_valid = update_kalman_observer(self, raw_current);
    } else if (self->observer == uz_im_control_observer_filtered_rotor_flux_model) {
        update_deterministic_observer(self, update_simplified_current_kalman(self, raw_current));
        observer_valid = !self->numerical_failure;
    } else {
        self->output.kalman_innovation_alpha_A = 0.0f;
        self->output.kalman_innovation_beta_A = 0.0f;
        update_deterministic_observer(self, raw_current);
        observer_valid = !self->numerical_failure;
    }
    if (!observer_valid) {
        self->numerical_failure = true;
        self->output.rotor_flux_angle_rad = 0.0f;
        self->output.rotor_flux_magnitude_Vs = 0.0f;
        self->output.i_dq_A = (uz_3ph_dq_t){0};
    }
    if (observer_valid && (self->observer == uz_im_control_observer_kalman_rotor_flux_model)) {
        /* Keep the PLL call outside update_kalman_observer: the Kalman matrix
         * temporaries have left the ISR stack before the PLL evaluates sin/cos. */
        self->observer_diagnostics.kalman_stator_frequency_Hz = observer_pll_step(
            self->kalman_observer_pll, self->output.rotor_flux_angle_rad);
    }
    bool const flux_valid = isfinite(self->output.rotor_flux_magnitude_Vs)
        && (self->output.rotor_flux_magnitude_Vs > self->control_config.minimum_observer_flux_Vs);
    self->output.rotor_flux_valid = flux_valid ? 1.0f : 0.0f;
    if (!flux_valid) {
        self->output.i_dq_A = (uz_3ph_dq_t){0};
    }
    float const lr = uz_IM_config_get_Lr(self->machine_config);
    self->output.estimated_electrical_torque_Nm = flux_valid
        ? 1.5f * self->machine_config.polePairs * (self->machine_config.Lm_Henry / lr)
            * self->output.rotor_flux_magnitude_Vs * self->output.i_dq_A.q
        : 0.0f;
    self->output.flux_angle_step_rad = 0.0f;
    if (flux_valid && self->previous_flux_angle_valid) {
        float const delta = self->output.rotor_flux_angle_rad - self->previous_flux_angle_rad;
        self->output.flux_angle_step_rad = atan2f(sinf(delta), cosf(delta));
    }
    self->output.flux_angle_step_violation =
        (fabsf(self->output.flux_angle_step_rad) > self->control_config.maximum_flux_angle_step_rad) ? 1.0f : 0.0f;
    self->previous_flux_angle_rad = self->output.rotor_flux_angle_rad;
    self->previous_flux_angle_valid = flux_valid;
    self->output.phase_current_sum_A = self->measurements.i_abc_A.a
        + self->measurements.i_abc_A.b + self->measurements.i_abc_A.c;
    self->output.phase_current_sum_violation =
        (fabsf(self->output.phase_current_sum_A) > self->control_config.maximum_phase_current_sum_A) ? 1.0f : 0.0f;
    self->output.rotor_electrical_angle_rad = fmodf(self->machine_config.polePairs * self->measurements.rotor_mechanical_angle_rad, 2.0f * UZ_PIf);
    if (self->output.rotor_electrical_angle_rad < 0.0f) self->output.rotor_electrical_angle_rad += 2.0f * UZ_PIf;
    float const flux_rotor_angle_delta = self->output.rotor_flux_angle_rad - self->output.rotor_electrical_angle_rad;
    self->output.flux_rotor_angle_difference_rad = atan2f(sinf(flux_rotor_angle_delta), cosf(flux_rotor_angle_delta));
    self->output.i_dq_raw_A = uz_transformation_3ph_alphabeta_to_dq(raw_current, self->output.rotor_flux_angle_rad);
    float slip = 0.0f;
    self->output.slip_frequency_limited = 0.0f;
    if (flux_valid) {
        slip = ((self->observer == uz_im_control_observer_kalman_rotor_flux_model)
            ? self->observer_diagnostics.kalman_stator_frequency_Hz
            : self->observer_diagnostics.deterministic_stator_frequency_Hz) * (2.0f * UZ_PIf) - omega_r;
        float const maximum_slip = 2.0f * UZ_PIf * self->control_config.maximum_slip_frequency_Hz;
        float const limited_slip = uz_signals_saturation(slip, maximum_slip, -maximum_slip);
        self->output.slip_frequency_limited = (limited_slip != slip) ? 1.0f : 0.0f;
        slip = limited_slip;
    }
    self->output.rotor_electrical_angular_speed_rad_per_s = omega_r;
    self->output.slip_angular_frequency_rad_per_s = slip;
    self->output.stator_angular_frequency_rad_per_s = omega_r + slip;
    self->output.rotor_electrical_frequency_Hz = self->output.rotor_electrical_angular_speed_rad_per_s / (2.0f * UZ_PIf);
    self->output.slip_frequency_Hz = self->output.slip_angular_frequency_rad_per_s / (2.0f * UZ_PIf);
    self->output.stator_frequency_Hz = self->output.stator_angular_frequency_rad_per_s / (2.0f * UZ_PIf);
    self->output.slip_percent = fabsf(self->output.stator_frequency_Hz) > 1.0e-3f
        ? 100.0f * self->output.slip_frequency_Hz / self->output.stator_frequency_Hz
        : 0.0f;
    if ((!isfinite(self->output.rotor_flux_magnitude_Vs)) && (!self->numerical_failure)) {
        self->numerical_failure = true;
    }
    return !self->numerical_failure;
}

const struct uz_im_observer_output *uz_im_observer_get_output(const uz_im_observer_t *self) {
    uz_assert_not_NULL(self);
    return &self->output;
}
const struct uz_im_observer_diagnostics_t *uz_im_observer_get_diagnostics(const uz_im_observer_t *self) {
    uz_assert_not_NULL(self);
    return &self->observer_diagnostics;
}
void uz_im_observer_set_process_noise(uz_im_observer_t *self, float value) {
    uz_assert_not_NULL(self); uz_assert(value >= 0.0f);
    self->control_config.kalman_process_noise_A2_per_s = value;
}
void uz_im_observer_set_measurement_noise(uz_im_observer_t *self, float value) {
    uz_assert_not_NULL(self); uz_assert(value > 0.0f);
    self->control_config.kalman_measurement_noise_A2 = value;
}
void uz_im_observer_set_minimum_flux(uz_im_observer_t *self, float value) {
    uz_assert_not_NULL(self); uz_assert(value > 0.0f);
    self->control_config.minimum_observer_flux_Vs = value;
}
#endif
