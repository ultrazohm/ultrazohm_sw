#ifndef UZ_SIGNALS_H
#define UZ_SIGNALS_H

/**
 * @brief Outputs zero, if signal is within the deadzone. Outputs input signal substracted by either the upper or lower threshold otherwise.
 *
 * @param input Input signal
 * @param upper_threshold Max limit for deadzone
 * @param lower_threshold min limit for deadzone
 * @return float Returns signal
 */
float uz_signals_dead_zone(float input, float upper_threshold, float lower_threshold);

/**
 * @brief Outputs 0.0f if input is 0. Outputs 1 if input is positive and -1 if input is negative.
 *
 * @param input any input signal
 * @return float Returns sign for last sample
 */
float uz_signals_get_sign_of_value(float input);

/**
 * @brief Returns one sample which either limits the input signal to the lower or upper limit, or passes the input signal through. Functions very similar to the saturation block in Simulink.
 * 
 * @param input Any input signal
 * @param upper_limit Upper limit of the saturation
 * @param lower_limit Lower limit of the saturation. upper_limit > lower_limit is required
 * @return Returns one sample of the adjusted input
 */
float uz_signals_saturation(float input, float upper_limit, float lower_limit);

#endif // UZ_SIGNALS_H
