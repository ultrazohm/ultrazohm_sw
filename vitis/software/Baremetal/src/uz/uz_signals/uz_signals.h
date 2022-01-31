#ifndef UZ_SIGNALS_H
#define UZ_SIGNALS_H

/*! enum for readable configuring for type of 1st order filter */
enum Filter_selection {
	LowPass = 0,
    HighPass
};

/**
 * @brief Configuration struct for a 1st order filter. Low- and HighPass filter is possible.
 *
 */
struct uz_Filter_1st_config {
	enum Filter_selection selection; /**< Filter selection \n
                                        0 = LowPass \n
                                        1 = HighPass*/

    float cutoff_frequency_Hz; /**< cutoff frequency in Hz of the filter */
	float sample_frequency_Hz; /**< sample frequency in Hz of the signal */
};


typedef struct uz_Filter_1st_t uz_Filter_1st_t;
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

/**
 * @brief Initialization of the filter 1st order object
 * 
 * @param config uz_Filter_1st_config configuration struct
 * @return uz_Filter_1st_t* pointer instance
 */
uz_Filter_1st_t* uz_Filter_1st_init(struct uz_Filter_1st_config config);

/**
 * @brief Function to filter an input signal with either an LowPass or HighPass filter
	 *
 * @param self pointer instance of uz_Filter_1st_t
 * @param input signal, which will be filtered
 * @return float filtered signal
 */
float uz_signals_Filter_1st_sample(uz_Filter_1st_t* self, float input);
#endif // UZ_SIGNALS_H
