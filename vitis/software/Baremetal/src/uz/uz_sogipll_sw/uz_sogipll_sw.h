#ifndef UZ_SOGIPLL_SW_H
#define UZ_SOGIPLL_SW_H

#include <stdbool.h>

/** @brief Opaque software SOGI PLL instance with statically allocated storage. */
typedef struct uz_sogipll_sw_t uz_sogipll_sw_t;

/** @brief Configuration of the software SOGI PLL. */
struct uz_sogipll_sw_config_t {
	float sample_time_s; /**< Positive call period and integration step in seconds; use 0.0001f for 10 kHz. */
	float omega_feedforward_rad_per_s; /**< Positive feedforward angular frequency. */
	float sogi_gain; /**< Positive SOGI gain k. */
	float proportional_gain; /**< Nonnegative PLL proportional gain. */
	float integral_gain; /**< Nonnegative PLL integral gain. */
	float voltage_scaling; /**< Nonzero input multiplier; negative values invert polarity. */
	bool rescale_voltage_outputs; /**< Divide all four voltage outputs by voltage_scaling when true. */
};

/**
 * @brief Outputs evaluated before advancing the four integrator states.
 * Voltage quantities are in volts when rescale_voltage_outputs is true.
 * Otherwise, voltage quantities equal physical voltage times voltage_scaling.
 */
struct uz_sogipll_sw_outputs_t {
	float voltage_estimate; /**< In-phase SOGI state at the start of this sample. */
	float quadrature_voltage_estimate; /**< Quadrature SOGI state at the start of this sample. */
	float voltage_d; /**< Direct-axis component computed using the current phase. */
	float voltage_q; /**< Quadrature-axis voltage; the PI uses its internally scaled value. */
	float theta_rad; /**< Current phase in [0, 2*pi), in radians. */
	float omega_rad_per_s; /**< Current feedforward plus PI output. */
};

/**
 * @brief Allocate and configure an instance with all integrator states zero.
 * Uses UZ_SOGIPLL_SW_MAX_INSTANCES in uz_global_configuration.h. No deallocation.
 * Each PLL also consumes one UZ_PI_CONTROLLER_MAX_INSTANCES slot.
 * Initialization is not reentrant. Invalid parameters or exhaustion assert.
 * @param config Algorithm parameters. All numeric inputs must be finite.
 * @return Initialized instance.
 */
uz_sogipll_sw_t *uz_sogipll_sw_init(struct uz_sogipll_sw_config_t config);

/**
 * @brief Evaluate outputs and advance exactly one algorithm sample.
 * Uses forward Euler for the in-phase SOGI state and phase integration.
 * The quadrature SOGI state uses backward Euler with the updated in-phase state.
 * Uses uz_transformation_3ph_alphabeta_to_dq, uz_PI_Controller in parallel mode,
 * and uz_signals_wrap for phase wrapping into [0, 2*pi).
 * Call at sample_time_s intervals; the default example uses 0.0001 s (10 kHz).
 * @param self Initialized instance; calls on the same instance must be serialized.
 * @param voltage_V Finite input voltage in volts, before scaling.
 * @return Outputs of this sample, before the new integrator states take effect.
 */
struct uz_sogipll_sw_outputs_t uz_sogipll_sw_sample(uz_sogipll_sw_t *self, float voltage_V);

/**
 * @brief Clear both SOGI states, the PI integral and phase, preserving parameters.
 * Call before sampling to restart from zero states.
 * @param self Initialized instance.
 */
void uz_sogipll_sw_reset(uz_sogipll_sw_t *self);

#endif // UZ_SOGIPLL_SW_H
