#ifndef UZ_SOGIPLL_H
#define UZ_SOGIPLL_H

#include <stdint.h>

/** @brief Opaque, statically allocated SOGI PLL instance. */
typedef struct uz_sogipll_t uz_sogipll_t;

/** @brief Configuration for the generated 200-cycle, free-running IP. */
struct uz_sogipll_config_t {
	uint32_t base_address; /**< Nonzero, word-aligned AXI base address. */
	uint32_t ip_clk_frequency_Hz; /**< Must be 100000000 Hz for this driver. */
	float omega_feedforward_rad_per_s; /**< Finite, positive angular frequency. */
	float sogi_gain; /**< Finite, positive SOGI gain. */
	float proportional_gain; /**< Finite, nonnegative PLL proportional gain. */
	float integral_gain; /**< Finite, nonnegative PLL integral gain. */
	float voltage_scaling; /**< Finite, nonzero multiplier; may invert polarity. */
};

/**
 * @brief Sequentially read estimates; fields need not belong to the same step.
 * Voltage quantities use the units resulting from input voltage times scaling.
 */
struct uz_sogipll_outputs_t {
	float voltage_estimate; /**< In-phase SOGI estimate in scaled voltage units. */
	float quadrature_voltage_estimate; /**< Quadrature SOGI estimate in scaled voltage units. */
	float voltage_d; /**< Direct-axis component in scaled voltage units. */
	float voltage_q; /**< Quadrature-axis component in scaled voltage units. */
	float theta_rad; /**< Estimated phase in radians. */
	float omega_rad_per_s; /**< Estimated angular frequency in rad/s. */
};

/**
 * @brief Allocate, reset and configure an IP; start it with zero input voltage.
 * Sets the integration step to 2 us, matching 200 clocks at 100 MHz.
 * Asserts algorithm reset while writing configuration, then releases it.
 * Leaves wrapper reset and enable untouched; requires the default enable high.
 * Call before starting the ISR.
 * Initialization is not reentrant; each hardware base address may be used once.
 * Instances persist for the lifetime of the program; no dynamic allocation.
 * @param config Hardware address, clock and algorithm parameters.
 * @return Initialized instance. Invalid configuration or exhausted pool asserts.
 */
uz_sogipll_t *uz_sogipll_init(struct uz_sogipll_config_t config);

/**
 * @brief Write the held input voltage. This does not trigger a calculation.
 * The enabled IP advances every 2 us, reusing this value until the next write.
 * @param self Initialized instance, exclusively owned by the caller.
 * @param voltage_V Finite input voltage in volts, before scaling.
 */
void uz_sogipll_set_voltage(const uz_sogipll_t *self, float voltage_V);

/**
 * @brief Reset algorithm state while preserving parameters and held voltage.
 * Writes algorithm reset high, then low, without delays or polling.
 * Do not call concurrently with other operations on this instance.
 * Assumes the IP clock is running and the core remains enabled.
 * Outputs are not guaranteed to be zero or settled on return.
 * @param self Initialized instance.
 */
void uz_sogipll_reset(const uz_sogipll_t *self);

/**
 * @brief Read all six estimates without waiting or freezing the running IP.
 * This is not an atomic snapshot and does not indicate PLL lock.
 * @param self Initialized instance.
 * @return Latest individually read estimates.
 */
struct uz_sogipll_outputs_t uz_sogipll_read_outputs(const uz_sogipll_t *self);

#endif // UZ_SOGIPLL_H
