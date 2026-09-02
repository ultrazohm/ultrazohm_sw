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

/** @brief Rotor-flux observer implementation used for FOC feedback. */
enum uz_im_control_observer {
    uz_im_control_observer_rotor_flux_model = 0, /**< Tustin rotor-current model using measured currents directly. */
    uz_im_control_observer_kalman_rotor_flux_model, /**< Full four-state current and rotor-flux Kalman observer. */
    uz_im_control_observer_filtered_rotor_flux_model /**< Two scalar current Kalman filters followed by the Tustin flux model. */
};

/** @brief Latched safe-operating-region violations. */
enum uz_im_control_safe_operating_region_violation {
    uz_im_control_no_violation = 0,          /**< No violation. */
    uz_im_control_underspeed = 1,            /**< Mechanical speed below its lower bound. */
    uz_im_control_overspeed = 2,             /**< Mechanical speed above its upper bound. */
    uz_im_control_dc_overvoltage = 3,        /**< DC-link voltage above its upper bound. */
    uz_im_control_dc_undervoltage = 4,       /**< DC-link voltage below its lower bound. */
    uz_im_control_dc_overcurrent = 5,        /**< DC-link current above its upper bound. */
    uz_im_control_dc_undercurrent = 6,       /**< DC-link current below its lower bound. */
    uz_im_control_i_d_overcurrent = 7,       /**< d-current above its upper bound. */
    uz_im_control_i_d_undercurrent = 8,      /**< d-current below its lower bound. */
    uz_im_control_i_q_overcurrent = 9,       /**< q-current above its upper bound. */
    uz_im_control_i_q_undercurrent = 10,     /**< q-current below its lower bound. */
    uz_im_control_phase_overcurrent = 11,    /**< At least one phase current above its upper bound. */
    uz_im_control_phase_undercurrent = 12,   /**< At least one phase current below its lower bound. */
    uz_im_control_observer_violation = 13    /**< Observer generated a non-finite flux value. */
};

/** @brief Lower and upper bound of one control quantity. */
struct uz_im_control_limits_t {
    float upper_bound;
    float lower_bound;
};

/** @brief Limits applied to external references before filtering and control. */
struct uz_im_setpoint_limits_t {
    struct uz_im_control_limits_t speed_controller_torque_in_Nm; /**< Reserved for a future torque-to-current setpoint stage. */
    struct uz_im_control_limits_t i_d_in_A;
    struct uz_im_control_limits_t i_q_in_A;
    struct uz_im_control_limits_t speed_in_rpm;
};

/** @brief Measurement limits checked before producing inverter commands. */
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
    float kalman_process_noise_A2_per_s; /**< Current-state process-noise density; per-step Q is this value times sample_time_s. */
    float kalman_flux_process_noise_Vs2_per_s; /**< Rotor-flux-state process-noise density; per-step Q is this value times sample_time_s. */
    float kalman_measurement_noise_A2; /**< Alpha/beta current measurement variance. */
    float observer_pll_kp; /**< Flux-angle PLL proportional gain. */
    float observer_pll_ki; /**< Flux-angle PLL integral gain. */
    float minimum_observer_flux_Vs;
    float maximum_slip_frequency_Hz;       /**< Absolute limit of estimated slip frequency. */
    float maximum_flux_angle_step_rad;     /**< Plausible flux-angle change per control step. */
    float maximum_phase_current_sum_A;     /**< Plausibility limit for abs(ia+ib+ic). */
    float resonant_gain_d; /**< Resonant-controller gain for the d axis. */
    float resonant_gain_q; /**< Resonant-controller gain for the q axis. */
    float resonant_harmonic_order; /**< Controlled harmonic order; must be greater than zero. */
    float resonant_antiwindup_gain; /**< Resonant-controller anti-windup gain. */
    float resonant_voltage_limit_V; /**< Symmetric voltage limit of each resonant controller. */
    struct uz_DutyCycle_t default_duty_cycle;
    struct uz_im_setpoint_limits_t setpoint_limits;
    struct uz_im_safe_operating_region_t safe_operating_region;
    float setpoint_filter_i_dq_cutoff_frequency; /**< Current-reference low-pass cutoff in Hz; zero disables it. */
    float setpoint_filter_speed_cutoff_frequency; /**< Speed-reference low-pass cutoff in Hz; zero disables it. */
    float speed_actual_value_filter_cutoff_frequency; /**< Measured-speed low-pass cutoff in Hz; zero disables it. */
    bool enable_speed_control;
    bool enable_resonant_control; /**< Enable the two resonant current controllers at initialization. */
    enum uz_im_control_observer observer;
};

/** @brief Measurements consumed by one control step. */
struct uz_im_measurement_values {
    uz_3ph_abc_t i_abc_A;             /**< Measured stator phase currents. */
    uz_3ph_abc_t v_abc_V;             /**< Internally overwritten with the reconstructed phase voltages used by the observer. */
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
    uint32_t safe_operating_region_status;       /**< Latched SOR code for JavaScope; see uz_im_control_safe_operating_region_violation. */
    uz_3ph_dq_t i_dq_A;                    /**< Currents used by the controller. */
    uz_3ph_dq_t i_dq_raw_A;                /**< Unfiltered measured dq currents. */
    uz_3ph_dq_t current_pi_voltage_dq_V;    /**< Separate d/q current-PI outputs. */
    uz_3ph_dq_t decoupling_voltage_dq_V;    /**< Rotor-flux-oriented decoupling voltages. */
    uz_3ph_dq_t resonant_voltage_dq_V;      /**< Resonant-controller voltage contribution. */
    float rotor_flux_angle_rad;             /**< Estimated rotor-flux angle. */
    float rotor_flux_magnitude_Vs;           /**< Estimated rotor-flux magnitude. */
    float estimated_electrical_torque_Nm;    /**< Estimated electromagnetic torque from rotor flux and q current. */
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
    float rotor_flux_valid;                   /**< 1 if flux is finite and exceeds minimum_observer_flux_Vs; otherwise controller i_dq feedback is forced to zero. */
    float slip_frequency_limited;             /**< 1 if the slip-frequency clamp is active. */
    float flux_angle_step_rad;                /**< Wrapped observer-angle change per step. */
    float flux_angle_step_violation;          /**< 1 if flux-angle step exceeds its limit. */
    float phase_current_sum_A;                /**< ia+ib+ic plausibility residual. */
    float phase_current_sum_violation;        /**< 1 if current-sum residual exceeds its limit. */
    float voltage_vector_magnitude_V;         /**< Magnitude before final vector saturation. */
    float voltage_vector_limit_V;             /**< Available linear-SVM voltage magnitude. */
    float voltage_vector_saturated;           /**< 1 if the final d/q vector was scaled. */
};

/** @brief Complete read-only diagnostics of all integrated rotor-flux observers. */
struct uz_im_observer_diagnostics_t {
    float state[4];                 /**< [i_alpha, i_beta, psi_r_alpha, psi_r_beta]. */
    float covariance[4][4];         /**< State-estimation covariance P. */
    float innovation[2];            /**< Alpha/beta current innovation. */
    float innovation_covariance[2][2]; /**< Innovation covariance S. */
    float kalman_gain[4][2];        /**< Kalman gain K. */
    float deterministic_flux_alpha_Vs;
    float deterministic_flux_beta_Vs;
    float kalman_stator_frequency_Hz;
    float deterministic_stator_frequency_Hz;
    float simplified_current_alpha_A; /**< Scalar-Kalman filtered alpha current. */
    float simplified_current_beta_A;  /**< Scalar-Kalman filtered beta current. */
    float simplified_current_covariance_alpha_A2; /**< Scalar alpha-current covariance. */
    float simplified_current_covariance_beta_A2;  /**< Scalar beta-current covariance. */
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
/** @brief Enable or disable both resonant current controllers and reset their states on a change. */
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
/** @brief Return all dynamic observer states and Kalman matrices. */
const struct uz_im_observer_diagnostics_t *uz_im_control_get_observer_diagnostics(uz_im_control_t *self);
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
/** @brief Update the current-state Kalman process-noise density; the per-step Q value is value * sample_time_s. */
void uz_im_control_set_kalman_process_noise(uz_im_control_t *self, float value);
/** @brief Update the Kalman measurement noise at runtime. */
void uz_im_control_set_kalman_measurement_noise(uz_im_control_t *self, float value);
/** @brief Update both resonant controllers at runtime. */
void uz_im_control_set_resonant_parameters(uz_im_control_t *self, float gain_d, float gain_q,
    float harmonic_order, float antiwindup_gain, float voltage_limit_V);
/** @brief Update the minimum flux required for valid FOC feedback. */
void uz_im_control_set_minimum_observer_flux(uz_im_control_t *self, float value);

#endif
