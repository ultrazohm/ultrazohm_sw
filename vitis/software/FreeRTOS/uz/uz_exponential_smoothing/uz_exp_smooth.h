#ifndef UZ_EXP_SMOOTH_H
#define UZ_EXP_SMOOTH_H

typedef struct uz_exp_smooth_t uz_exp_smooth_t;

/**
 * @brief Initialization of the simple exponential smoothing filter
 * 
 * @param alpha smoothing factor, 0 ≤ α ≤ 1
 * @return uz_exp_smooth_t* pointer instance
 */

uz_exp_smooth_t* uz_exp_smooth_init(float alpha);

/**
 * @brief Function to filter an input signal with exponential smoothing filter
	 *
 * @param self pointer instance of uz_exp_smooth_t*
 * @param input signal, which will be filtered
 * @return float filtered signal
 */
float uz_exp_smooth_sample(uz_exp_smooth_t* self, float input);

#endif // UZ_EXP_SMOOTH_H
