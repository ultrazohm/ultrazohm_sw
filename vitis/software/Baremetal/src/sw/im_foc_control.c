#include "../include/im_foc_control.h"
#include "../include/im_siemens_1LA7073.h"
#include "../uz/uz_piController/uz_piController.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz/uz_HAL.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_ResonantController/uz_resonant_controller.h"
#include <math.h>

/* Siemens 1LA7073-4AB10-Z, star-equivalent equivalent-circuit data. */
#define IM_RS_OHM          7.05f
#define IM_RR_OHM          6.23f
#define IM_LM_H            0.271f
#define IM_LSIGMA_S_H      31.3e-3f
#define IM_LSIGMA_R_H      35.6e-3f
#define IM_POLE_PAIRS      2.0f
#define IM_CURRENT_KP_SCALE 0.1f
#define IM_CURRENT_KI_SCALE 0.2f
#define IM_KF_Q_CURRENT_A2  1.0e-5f
#define IM_KF_R_CURRENT_A2  5.0e-2f
#define IM_RESONANT_GAIN_SCALE 0.3f

struct im_foc_control_t {
    uz_PI_Controller *id_controller;
    uz_PI_Controller *iq_controller;
    float psi_alpha_Vs;
    float psi_beta_Vs;
    float kf_i_alpha_A;
    float kf_i_beta_A;
    float kf_p_alpha_A2;
    float kf_p_beta_A2;
    uz_resonantController_t *resonant_id;
    uz_resonantController_t *resonant_iq;
    bool kalman_enabled_last;
    bool resonant_enabled_last;
};

static im_foc_control_t instance;
static bool initialized;

im_foc_control_t *im_foc_control_init(float sampling_time_s)
{
    uz_assert(sampling_time_s > 0.0f);
    if (!initialized) {
        float const ls = IM_LM_H + IM_LSIGMA_S_H;
        float const lr = IM_LM_H + IM_LSIGMA_R_H;
        float const sigma_ls = (1.0f - (IM_LM_H * IM_LM_H) / (ls * lr)) * ls;
        struct uz_PI_Controller_config const cfg = {
            .type = UZ_PI_PARALLEL,
            .Kp = IM_CURRENT_KP_SCALE * sigma_ls / (2.0f * sampling_time_s),
            .Ki = IM_CURRENT_KI_SCALE * IM_RS_OHM / (2.0f * sampling_time_s),
            .samplingTime_sec = sampling_time_s,
            .upper_limit = IM_1LA7073_VDC_MAX_V,
            .lower_limit = -IM_1LA7073_VDC_MAX_V,
        };
        instance.id_controller = uz_PI_Controller_init(cfg);
        instance.iq_controller = uz_PI_Controller_init(cfg);
        struct uz_resonantController_config const resonant_cfg = {
            .sampling_time = sampling_time_s,
            .gain = IM_RESONANT_GAIN_SCALE * cfg.Kp,
            .harmonic_order = 6.0f,
            .fundamental_frequency = 1.0f,
            .lower_limit = -100.0f,
            .upper_limit = 100.0f,
            .antiwindup_gain = 10.0f,
            .in_reference_value = 0.0f,
            .in_measured_value = 0.0f,
        };
        instance.resonant_id = uz_resonantController_init(resonant_cfg);
        instance.resonant_iq = uz_resonantController_init(resonant_cfg);
        initialized = true;
    }
    im_foc_control_reset(&instance);
    return &instance;
}

void im_foc_control_reset(im_foc_control_t *self)
{
    uz_assert_not_NULL(self);
    uz_PI_Controller_reset(self->id_controller);
    uz_PI_Controller_reset(self->iq_controller);
    self->psi_alpha_Vs = 0.0f;
    self->psi_beta_Vs = 0.0f;
    self->kf_i_alpha_A = 0.0f;
    self->kf_i_beta_A = 0.0f;
    self->kf_p_alpha_A2 = 1.0f;
    self->kf_p_beta_A2 = 1.0f;
    self->kalman_enabled_last = false;
    self->resonant_enabled_last = false;
    uz_resonantController_reset(self->resonant_id);
    uz_resonantController_reset(self->resonant_iq);
}

im_foc_control_output_t im_foc_control_sample(im_foc_control_t *self,
                                               im_foc_control_input_t input)
{
    uz_assert_not_NULL(self);
    im_foc_control_output_t output = {
        .duty = {.DutyCycle_A = 0.5f, .DutyCycle_B = 0.5f, .DutyCycle_C = 0.5f}
    };
    if ((!isfinite(input.dc_link_voltage_V)) ||
        (input.dc_link_voltage_V < IM_1LA7073_VDC_MIN_V)) {
        im_foc_control_reset(self);
        return output;
    }

    uz_3ph_alphabeta_t i_ab = uz_transformation_3ph_abc_to_alphabeta(input.currents_A);
    if (input.enable_kalman_filter) {
        self->kf_p_alpha_A2 += IM_KF_Q_CURRENT_A2;
        self->kf_p_beta_A2 += IM_KF_Q_CURRENT_A2;
        output.kalman_innovation_alpha_A = i_ab.alpha - self->kf_i_alpha_A;
        output.kalman_innovation_beta_A = i_ab.beta - self->kf_i_beta_A;
        float const gain_alpha = self->kf_p_alpha_A2 / (self->kf_p_alpha_A2 + IM_KF_R_CURRENT_A2);
        float const gain_beta = self->kf_p_beta_A2 / (self->kf_p_beta_A2 + IM_KF_R_CURRENT_A2);
        self->kf_i_alpha_A += gain_alpha * output.kalman_innovation_alpha_A;
        self->kf_i_beta_A += gain_beta * output.kalman_innovation_beta_A;
        self->kf_p_alpha_A2 *= 1.0f - gain_alpha;
        self->kf_p_beta_A2 *= 1.0f - gain_beta;
        i_ab.alpha = self->kf_i_alpha_A;
        i_ab.beta = self->kf_i_beta_A;
    } else {
        if (self->kalman_enabled_last) {
            self->kf_p_alpha_A2 = 1.0f;
            self->kf_p_beta_A2 = 1.0f;
        }
        self->kf_i_alpha_A = i_ab.alpha;
        self->kf_i_beta_A = i_ab.beta;
    }
    self->kalman_enabled_last = input.enable_kalman_filter;
    float const lr = IM_LM_H + IM_LSIGMA_R_H;
    float const inv_tr = IM_RR_OHM / lr;
    float const omega_r_el = input.rotor_speed_rpm * (2.0f * UZ_PIf / 60.0f) * IM_POLE_PAIRS;

    /* Rotor-current-model observer in stationary alpha/beta coordinates. */
    float const dpsi_alpha = inv_tr * (IM_LM_H * i_ab.alpha - self->psi_alpha_Vs)
                             - omega_r_el * self->psi_beta_Vs;
    float const dpsi_beta = inv_tr * (IM_LM_H * i_ab.beta - self->psi_beta_Vs)
                            + omega_r_el * self->psi_alpha_Vs;
    self->psi_alpha_Vs += input.sampling_time_s * dpsi_alpha;
    self->psi_beta_Vs += input.sampling_time_s * dpsi_beta;

    output.flux_magnitude_Vs = hypotf(self->psi_alpha_Vs, self->psi_beta_Vs);
    output.flux_angle_rad = atan2f(self->psi_beta_Vs, self->psi_alpha_Vs);
    uz_3ph_dq_t const i_dq = uz_transformation_3ph_alphabeta_to_dq(i_ab, output.flux_angle_rad);
    output.id_A = i_dq.d;
    output.iq_A = i_dq.q;

    float const voltage_limit = input.dc_link_voltage_V * 0.57735026919f;
    uz_PI_Controller_update_limits(self->id_controller, voltage_limit, -voltage_limit);
    uz_PI_Controller_update_limits(self->iq_controller, voltage_limit, -voltage_limit);
    float const ud_pi = uz_PI_Controller_sample(self->id_controller, input.id_reference_A, i_dq.d, false);
    float const uq_pi = uz_PI_Controller_sample(self->iq_controller, input.iq_reference_A, i_dq.q, false);

    float const ls = IM_LM_H + IM_LSIGMA_S_H;
    float const sigma_ls = (1.0f - (IM_LM_H * IM_LM_H) / (ls * lr)) * ls;
    float omega_slip = 0.0f;
    if (output.flux_magnitude_Vs > 0.02f) {
        omega_slip = (IM_RR_OHM * IM_LM_H / lr) * i_dq.q / output.flux_magnitude_Vs;
    }
    float const omega_s = omega_r_el + omega_slip;
    if (input.enable_resonant_control) {
        float const resonant_frequency = fmaxf(fabsf(omega_s), 1.0f);
        output.resonant_ud_V = uz_resonantController_step(self->resonant_id,
                                                          input.id_reference_A,
                                                          i_dq.d,
                                                          resonant_frequency);
        output.resonant_uq_V = uz_resonantController_step(self->resonant_iq,
                                                          input.iq_reference_A,
                                                          i_dq.q,
                                                          resonant_frequency);
    } else if (self->resonant_enabled_last) {
        uz_resonantController_reset(self->resonant_id);
        uz_resonantController_reset(self->resonant_iq);
    }
    self->resonant_enabled_last = input.enable_resonant_control;
    uz_3ph_dq_t const voltage_dq = {
        .d = ud_pi + output.resonant_ud_V - omega_s * sigma_ls * i_dq.q,
        .q = uq_pi + output.resonant_uq_V + omega_s * sigma_ls * i_dq.d
             + omega_s * (IM_LM_H / lr) * output.flux_magnitude_Vs,
        .zero = 0.0f,
    };
    output.duty = uz_Space_Vector_Modulation(voltage_dq,
                                             input.dc_link_voltage_V,
                                             output.flux_angle_rad);
    return output;
}
