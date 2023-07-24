#ifndef UZ_SIGNALS_H
#define UZ_SIGNALS_H
#include "../uz_math_constants.h"

/*! enum for readable configuring for type of 1st order filter */
enum uz_IIR_Filter_selection {
	LowPass_first_order = 0,
    HighPass_first_order
};

/**
 * @brief Configuration struct for a 1st order filter. Low- and HighPass filter is possible.
 *
 */
struct uz_IIR_Filter_config {
	enum uz_IIR_Filter_selection selection; /**< Filter selection \n */
    float cutoff_frequency_Hz; /**< cutoff frequency in Hz of the filter */
	float sample_frequency_Hz; /**< sample frequency in Hz of the signal */
};


typedef struct uz_IIR_Filter_t uz_IIR_Filter_t;
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
 * @brief Passes the input signal through if it is inside the hysteresis band limited by the upper or lower limit, otherwise the output is zero
 * 
 * @param input Any input signal
 * @param upper_limit Upper limit of the hysteresis band
 * @param lower_limit Lower limit of the hysteresis band (needs to be smaller than the upper limit)
 * @return float filtered signal
 */
float uz_signals_hysteresisband_filter(float input, float upper_limit, float lower_limit);

/**
 * @brief Initialization of the filter 1st order object
 * 
 * @param config uz_Filter_1st_config configuration struct
 * @return uz_IIR_Filter_t* pointer instance
 */
uz_IIR_Filter_t* uz_signals_IIR_Filter_init(struct uz_IIR_Filter_config config);

/**
 * @brief Function to filter an input signal with either an LowPass or HighPass filter
	 *
 * @param self pointer instance of uz_IIR_Filter_t
 * @param input signal, which will be filtered
 * @return float filtered signal
 */
float uz_signals_IIR_Filter_sample(uz_IIR_Filter_t* self, float input);

/**
 * @brief Function to reverse the filter of the input signal with either an LowPass or HighPass filter
	 *
 * @param self pointer instance of uz_IIR_Filter_t
 * @param input filtered signal
 * @return float unfiltered signal
 */
float uz_signals_IIR_Filter_reverse_sample(uz_IIR_Filter_t* self, float input);

/**
 * @brief wraps a number to the range of [0, limit] 
 * 
 * @param number number to wrap
 * @param limit defines the wrapping limit of [0, limit]
 * @return wrapped number
 */
float uz_signals_wrap(float number, float limit);

#endif // UZ_SIGNALS_H

/**
 * @brief Evaluates the input. sets the output to one if the input is bigger than the threshold value otherwise to zero
 * 
 * @param input Any input signal
 * @param threshold Threshold value for evaluation
 * @return float evaluation value (0 or 1)
 */
float uz_signals_threshold_Evaluation(float input, float threshold);