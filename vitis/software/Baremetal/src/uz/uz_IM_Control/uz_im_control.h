#ifndef UZ_IM_CONTROL_H
#define UZ_IM_CONTROL_H

#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_Space_Vector_Modulation/uz_space_vector_modulation.h"
#include "../uz_IM_config/uz_IM_config.h"

typedef struct uz_im_control_t uz_im_control_t;

/** @brief Available control strategies. */
enum uz_im_control_mode {
    uz_im_control_mode_foc = 0,
    uz_im_control_mode_u_f
};

/** @brief Observer preprocessing used by the rotor-flux model. */
enum uz_im_control_observer {
    uz_im_control_observer_rotor_flux_model = 0,
    uz_im_control_observer_kalman_rotor_flux_model
};

/** @brief Latched safe-operating-region violations. */
enum uz_im_control_safe_operating_region_violation {
    uz_im_control_no_violation = 0,
    uz_im_control_speed_violation,
    uz_im_control_phase_current_violation,
    uz_im_control_dc_link_voltage_violation,
    uz_im_control_observer_violation
};

/** @brief Runtime limits checked before producing inverter commands. */
struct uz_im_control_limits_t {
    float speed_abs_max_rpm;
    float phase_current_abs_max_A;
    float dc_link_voltage_min_V;
    float dc_link_voltage_max_V;
};

/** @brief Complete configuration of the integrated IM controller. */
struct uz_im_control_configuration_t {
    float sample_time_s;
    float current_controller_d_kp;
    float current_controller_d_ki;
    float current_controller_q_kp;
    float current_controller_q_ki;
    float speed_controller_kp;
    float speed_controller_ki;
    float speed_controller_iq_limit_A;
    float u_f_ratio_V_per_Hz;
    float u_f_boost_voltage_V;
    float u_f_max_frequency_Hz;
    float u_f_max_voltage_V;
    float u_f_frequency_ramp_Hz_per_s;
    float kalman_process_noise_A2_per_s;
    float kalman_measurement_noise_A2;
    float minimum_observer_flux_Vs;
    struct uz_DutyCycle_t default_duty_cycle;
    struct uz_im_control_limits_t safe_operating_region;
    bool enable_speed_control;
    enum uz_im_control_observer observer;
};

/** @brief Measurements consumed by one control step. */
struct uz_im_measurement_values {
    uz_3ph_abc_t i_abc_A;             /**< Measured stator phase currents. */
    uz_3ph_abc_t v_abc_V;             /**< Measured stator phase voltages. */
    float v_dc_V;                     /**< Measured DC-link voltage. */
    float i_dc_A;                     /**< Measured DC-link current. */
    float rotor_speed_rpm;            /**< Mechanical rotor speed. */
    float rotor_mechanical_angle_rad; /**< Mechanical rotor angle in rad. */
};

/** @brief References and generated commands of the most recent step. */
struct uz_im_reference_values {
    float speed_rpm;
    uz_3ph_dq_t i_dq_A;
    float u_f_frequency_Hz;
    uz_3ph_dq_t v_dq_V;
    struct uz_DutyCycle_t duty_cycle;
};

/** @brief Observer and controller diagnostics of the most recent step. */
struct uz_im_actual_data {
    uz_3ph_dq_t i_dq_A;                    /**< Currents used by the controller. */
    uz_3ph_dq_t i_dq_raw_A;                /**< Unfiltered measured dq currents. */
    uz_3ph_dq_t current_pi_voltage_dq_V;    /**< Separate d/q current-PI outputs. */
    uz_3ph_dq_t decoupling_voltage_dq_V;    /**< Rotor-flux-oriented decoupling voltages. */
    float rotor_flux_angle_rad;             /**< Estimated rotor-flux angle. */
    float rotor_flux_magnitude_Vs;           /**< Estimated rotor-flux magnitude. */
    float rotor_electrical_angle_rad;        /**< Electrical angle derived from measured rotor angle. */
    float flux_rotor_angle_difference_rad;   /**< Wrapped flux-angle minus rotor-angle difference. */
    float rotor_electrical_angular_speed_rad_per_s; /**< Electrical rotor angular speed. */
    float slip_angular_frequency_rad_per_s;  /**< Estimated slip angular frequency. */
    float stator_angular_frequency_rad_per_s;/**< Estimated synchronous angular frequency. */
    float rotor_electrical_frequency_Hz;     /**< Electrical rotor frequency. */
    float slip_frequency_Hz;                 /**< Estimated slip frequency. */
    float slip_percent;                      /**< Slip relative to stator frequency. */
    float stator_frequency_Hz;               /**< Estimated synchronous stator frequency. */
    float kalman_innovation_alpha_A;          /**< Alpha-current Kalman innovation. */
    float kalman_innovation_beta_A;           /**< Beta-current Kalman innovation. */
    float u_f_command_frequency_Hz;           /**< Ramped U/f stator-frequency command. */
    float u_f_electrical_angle_rad;           /**< U/f rotating-voltage-vector angle. */
    float u_f_applied_voltage_V;              /**< U/f voltage magnitude before SVM. */
};

/** @brief Initialize one self-contained induction-machine controller. */
uz_im_control_t *uz_im_control_init(struct uz_im_control_configuration_t control_config,
                                    uz_IM_t machine_config);
/** @brief Enable or disable inverter command generation. */
void uz_im_control_enable(uz_im_control_t *self, bool enable);
/** @brief Select rotor-flux-oriented control or scalar U/f control. */
void uz_im_control_set_mode(uz_im_control_t *self, enum uz_im_control_mode mode);
/** @brief Enable or disable the internal speed PI controller. */
void uz_im_control_enable_speed_control(uz_im_control_t *self, bool enable);
/** @brief Select the observer path used for feedback and diagnostics. */
void uz_im_control_set_observer(uz_im_control_t *self, enum uz_im_control_observer observer);
/** @brief Reset all three PI controllers, U/f state and observer state. */
void uz_im_control_reset(uz_im_control_t *self);

/** @brief Execute one control step and return inverter duty cycles. */
struct uz_DutyCycle_t uz_im_control_sample_duty(
    uz_im_control_t *self,
    struct uz_im_measurement_values measurements,
    float speed_reference_rpm,
    uz_3ph_dq_t current_references_A,
    float u_f_frequency_reference_Hz);

/** @brief Execute one FOC step and return its dq voltage command. */
uz_3ph_dq_t uz_im_control_sample_dq(
    uz_im_control_t *self,
    struct uz_im_measurement_values measurements,
    float speed_reference_rpm,
    uz_3ph_dq_t current_references_A);

/** @brief Return read-only observer and controller diagnostics. */
const struct uz_im_actual_data *uz_im_control_get_actual_data(uz_im_control_t *self);
/** @brief Return read-only references and generated commands. */
const struct uz_im_reference_values *uz_im_control_get_reference_values(uz_im_control_t *self);
/** @brief Return read-only latest measurements. */
const struct uz_im_measurement_values *uz_im_control_get_im_measurement_values(uz_im_control_t *self);
/** @brief Return the currently latched safety violation. */
enum uz_im_control_safe_operating_region_violation uz_im_control_get_safe_operating_area_violation(uz_im_control_t *self);
/** @brief Clear a latched violation and reset all dynamic states. */
void uz_im_control_acknowledge_and_reset_error(uz_im_control_t *self);

void uz_im_control_current_control_set_Kp_id(uz_im_control_t *self, float Kp_id);
void uz_im_control_current_control_set_Ki_id(uz_im_control_t *self, float Ki_id);
void uz_im_control_current_control_set_Kp_iq(uz_im_control_t *self, float Kp_iq);
void uz_im_control_current_control_set_Ki_iq(uz_im_control_t *self, float Ki_iq);
void uz_im_control_speed_control_set_Kp_speed(uz_im_control_t *self, float Kp_speed);
void uz_im_control_speed_control_set_Ki_speed(uz_im_control_t *self, float Ki_speed);

#endif
