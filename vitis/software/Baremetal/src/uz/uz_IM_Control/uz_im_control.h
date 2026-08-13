#ifndef UZ_IM_CONTROL_H
#define UZ_IM_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
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
    uz_im_control_underspeed = 1,
    uz_im_control_overspeed = 2,
    uz_im_control_dc_overvoltage = 3,
    uz_im_control_dc_undervoltage = 4,
    uz_im_control_dc_overcurrent = 5,
    uz_im_control_dc_undercurrent = 6,
    uz_im_control_i_d_overcurrent = 7,
    uz_im_control_i_d_undercurrent = 8,
    uz_im_control_i_q_overcurrent = 9,
    uz_im_control_i_q_undercurrent = 10,
    uz_im_control_phase_overcurrent = 11,
    uz_im_control_phase_undercurrent = 12,
    uz_im_control_observer_violation = 13
};

/** @brief Lower and upper bound of one control quantity. */
struct uz_im_control_limits_t {
    float upper_bound;
    float lower_bound;
};

struct uz_im_setpoint_limits_t {
    struct uz_im_control_limits_t speed_controller_torque_in_Nm;
    struct uz_im_control_limits_t i_d_in_A;
    struct uz_im_control_limits_t i_q_in_A;
    struct uz_im_control_limits_t speed_in_rpm;
};

struct uz_im_safe_operating_region_t {
    struct uz_im_control_limits_t speed_in_rpm;
    struct uz_im_control_limits_t i_d_in_A;
    struct uz_im_control_limits_t i_q_in_A;
    struct uz_im_control_limits_t i_abc_in_A;
    struct uz_im_control_limits_t v_dc_in_V;
    struct uz_im_control_limits_t i_dc_in_A;
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
    float u_f_ratio_V_per_Hz;
    float u_f_boost_voltage_V;
    float u_f_max_frequency_Hz;
    float u_f_max_voltage_V;
    float u_f_frequency_ramp_Hz_per_s;
    float kalman_process_noise_A2_per_s;
    float kalman_measurement_noise_A2;
    float minimum_observer_flux_Vs;
    float maximum_slip_frequency_Hz;       /**< Absolute limit of estimated slip frequency. */
    float maximum_flux_angle_step_rad;     /**< Plausible flux-angle change per control step. */
    float maximum_phase_current_sum_A;     /**< Plausibility limit for abs(ia+ib+ic). */
    float resonant_gain_d;
    float resonant_gain_q;
    float resonant_harmonic_order;
    float resonant_antiwindup_gain;
    float resonant_voltage_limit_V;
    struct uz_DutyCycle_t default_duty_cycle;
    struct uz_im_setpoint_limits_t setpoint_limits;
    struct uz_im_safe_operating_region_t safe_operating_region;
    float setpoint_filter_i_dq_cutoff_frequency;
    float setpoint_filter_speed_cutoff_frequency;
    float speed_actual_value_filter_cutoff_frequency;
    bool enable_speed_control;
    bool enable_resonant_control;
    bool enable_voltage_vector_limiting;   /**< Limit final dq voltage to Vdc/sqrt(3). */
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
    uint32_t safe_operating_region_status;
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
    uz_3ph_dq_t resonant_voltage_dq_V;        /**< Resonant-controller voltage contribution. */
    float rotor_flux_valid;                   /**< 1 if flux exceeds the configured minimum. */
    float slip_frequency_limited;             /**< 1 if the slip-frequency clamp is active. */
    float flux_angle_step_rad;                /**< Wrapped observer-angle change per step. */
    float flux_angle_step_violation;          /**< 1 if flux-angle step exceeds its limit. */
    float phase_current_sum_A;                /**< ia+ib+ic plausibility residual. */
    float phase_current_sum_violation;        /**< 1 if current-sum residual exceeds its limit. */
    float voltage_vector_magnitude_V;         /**< Magnitude before final vector saturation. */
    float voltage_vector_limit_V;             /**< Available linear SVM voltage magnitude. */
    float voltage_vector_saturated;           /**< 1 if final dq vector was scaled. */
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
void uz_im_control_enable_resonant_control(uz_im_control_t *self, bool enable);
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
void uz_im_control_set_kalman_process_noise(uz_im_control_t *self, float value);
void uz_im_control_set_kalman_measurement_noise(uz_im_control_t *self, float value);
void uz_im_control_set_resonant_parameters(uz_im_control_t *self, float gain_d, float gain_q,
    float harmonic_order, float antiwindup_gain, float voltage_limit_V);
void uz_im_control_set_minimum_observer_flux(uz_im_control_t *self, float value);

#endif
