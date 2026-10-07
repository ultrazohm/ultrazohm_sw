#ifndef UZ_IM_OBSERVER_H
#define UZ_IM_OBSERVER_H

#include <stdbool.h>
#include "../uz_Transformation/uz_Transformation.h"
#include "../uz_IM_config/uz_IM_config.h"

/** @brief Opaque observer; normally owned by an IM-control instance. */
typedef struct uz_im_observer uz_im_observer_t;

/** @brief Rotor-flux observer implementation used for FOC feedback. */
enum uz_im_control_observer {
    uz_im_control_observer_rotor_flux_model = 0, /**< Tustin rotor-current model using measured currents directly. */
    uz_im_control_observer_kalman_rotor_flux_model, /**< Full four-state current and rotor-flux Kalman observer. */
    uz_im_control_observer_filtered_rotor_flux_model /**< Two scalar current Kalman filters followed by the Tustin flux model. */
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

/** @brief Observer-only settings; process-noise densities are multiplied by sample_time_s. */
struct uz_im_observer_config {
    float sample_time_s; /**< Time between observer calls in seconds; positive. */
    float kalman_process_noise_A2_per_s; /**< Current process-noise density; nonnegative. */
    float kalman_measurement_noise_A2; /**< Current measurement variance; positive. */
    float kalman_flux_process_noise_Vs2_per_s; /**< Four-state flux process-noise density; nonnegative. */
    float minimum_observer_flux_Vs; /**< Positive threshold for valid flux and dq feedback. */
    float maximum_flux_angle_step_rad; /**< Positive diagnostic limit for wrapped angle increments. */
    float maximum_phase_current_sum_A; /**< Positive diagnostic limit for abs(ia+ib+ic). */
    float maximum_slip_frequency_Hz; /**< Positive symmetric slip-frequency clamp. */
    float observer_pll_kp; /**< Nonnegative proportional gain for both flux-angle PLLs. */
    float observer_pll_ki; /**< Nonnegative integral gain for both flux-angle PLLs. */
    enum uz_im_control_observer observer; /**< Initial implementation; enum names retained for compatibility. */
};

/** @brief Synchronous current/rotor measurements and voltage from the previous interval. */
struct uz_im_observer_input {
    uz_3ph_abc_t i_abc_A; /**< Synchronous measured phase currents in amperes. */
    uz_3ph_abc_t v_abc_V; /**< Voltage applied during k-1 for the current sample at k; no internal delay. */
    float rotor_speed_rpm; /**< Signed mechanical rotor speed in rpm. */
    float rotor_mechanical_angle_rad; /**< Mechanical rotor angle in radians. */
};

/** @brief Derived observer outputs; fault latching and inverter shutdown belong to IM Control. */
struct uz_im_observer_output {
    float rotor_flux_angle_rad;             /**< Estimated rotor-flux angle. */
    float rotor_flux_magnitude_Vs;           /**< Estimated rotor-flux magnitude. */
    uz_3ph_dq_t i_dq_A;                    /**< Currents used by the controller. */
    float kalman_innovation_alpha_A;          /**< Alpha-current Kalman innovation. */
    float kalman_innovation_beta_A;           /**< Beta-current Kalman innovation. */
    float rotor_flux_valid;                   /**< 1 if flux is finite and exceeds minimum_observer_flux_Vs; otherwise controller i_dq feedback is forced to zero. */
    float estimated_electrical_torque_Nm;    /**< Estimated electromagnetic torque from rotor flux and q current. */
    float flux_angle_step_rad;                /**< Wrapped observer-angle change per step. */
    float flux_angle_step_violation;          /**< 1 if flux-angle step exceeds its limit. */
    float phase_current_sum_A;                /**< ia+ib+ic plausibility residual. */
    float phase_current_sum_violation;        /**< 1 if current-sum residual exceeds its limit. */
    float rotor_electrical_angle_rad;        /**< Electrical angle derived from measured rotor angle. */
    float flux_rotor_angle_difference_rad;   /**< Wrapped flux-angle minus rotor-angle difference. */
    uz_3ph_dq_t i_dq_raw_A;                /**< Unfiltered measured dq currents. */
    float slip_frequency_limited;             /**< 1 if the slip-frequency clamp is active. */
    float rotor_electrical_angular_speed_rad_per_s; /**< Electrical rotor angular speed. */
    float slip_angular_frequency_rad_per_s;  /**< Estimated slip angular frequency. */
    float stator_angular_frequency_rad_per_s;/**< Estimated synchronous angular frequency. */
    float rotor_electrical_frequency_Hz;     /**< Electrical rotor frequency. */
    float slip_frequency_Hz;                 /**< Estimated slip frequency. */
    float stator_frequency_Hz;               /**< Estimated synchronous stator frequency. */
    float slip_percent;                      /**< Slip relative to stator frequency. */
};

/** @brief Allocate one observer (pool size UZ_IM_CONTROL_MAX_INSTANCES); consumes two PLL instances. */
uz_im_observer_t *uz_im_observer_init(struct uz_im_observer_config config, uz_IM_t machine);
/** @brief Reset states, covariances, outputs and PLLs, retaining settings and selection. */
void uz_im_observer_reset(uz_im_observer_t *self);
/** @brief Change implementation and reset; selecting the same implementation preserves state. */
void uz_im_observer_set_mode(uz_im_observer_t *self, enum uz_im_control_observer observer);
/** @brief Execute the selected observer. Return false on numerical failure until reset or mode change; caller owns SOR handling.
 * A finite flux below the minimum threshold is not a numerical failure; check rotor_flux_valid separately.
 */
bool uz_im_observer_sample(uz_im_observer_t *self, struct uz_im_observer_input input);
/** @brief Read-only outputs owned by the observer instance. */
const struct uz_im_observer_output *uz_im_observer_get_output(const uz_im_observer_t *self);
/** @brief Read-only states and matrices owned by the observer instance. */
const struct uz_im_observer_diagnostics_t *uz_im_observer_get_diagnostics(const uz_im_observer_t *self);
/** @brief Update current process-noise density without resetting states or covariance. */
void uz_im_observer_set_process_noise(uz_im_observer_t *self, float value);
/** @brief Update current measurement variance without resetting states or covariance. */
void uz_im_observer_set_measurement_noise(uz_im_observer_t *self, float value);
/** @brief Update the minimum valid rotor-flux magnitude. */
void uz_im_observer_set_minimum_flux(uz_im_observer_t *self, float value);

#endif
