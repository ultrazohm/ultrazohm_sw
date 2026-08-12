#ifndef IM_FOC_CONTROL_H_
#define IM_FOC_CONTROL_H_

#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include <stdbool.h>

typedef struct im_foc_control_t im_foc_control_t;

typedef struct {
    float current_kp_d;
    float current_ki_d;
    float current_kp_q;
    float current_ki_q;
    float kalman_q_A2_per_s;
    float kalman_r_A2;
    float resonant_gain_d;
    float resonant_gain_q;
    float resonant_harmonic_order;
    float resonant_antiwindup_gain;
    float resonant_voltage_limit_V;
    float slip_flux_minimum_Vs;
} im_foc_control_parameters_t;

typedef struct {
    uz_3ph_abc_t currents_A;
    float rotor_speed_rpm;
    float dc_link_voltage_V;
    float id_reference_A;
    float iq_reference_A;
    float sampling_time_s;
    bool enable_kalman_filter;
    bool enable_resonant_control;
    bool observer_only;
} im_foc_control_input_t;

typedef struct {
    struct uz_DutyCycle_t duty;
    float id_A;
    float iq_A;
    float id_raw_A;
    float iq_raw_A;
    float flux_angle_rad;
    float flux_magnitude_Vs;
    float rotor_electrical_frequency_Hz;
    float slip_frequency_Hz;
    float slip_percent;
    float stator_frequency_Hz;
    float kalman_innovation_alpha_A;
    float kalman_innovation_beta_A;
    float resonant_ud_V;
    float resonant_uq_V;
} im_foc_control_output_t;

im_foc_control_t *im_foc_control_init(float sampling_time_s);
void im_foc_control_reset(im_foc_control_t *self);
im_foc_control_parameters_t im_foc_control_get_parameters(im_foc_control_t *self);
void im_foc_control_set_parameters(im_foc_control_t *self, im_foc_control_parameters_t parameters);
im_foc_control_output_t im_foc_control_sample(im_foc_control_t *self,
                                               im_foc_control_input_t input);

#endif
