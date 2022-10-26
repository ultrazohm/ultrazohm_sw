#ifndef UZ_EXP_SMOOTH_H
#define UZ_EXP_SMOOTH_H

typedef struct UZ_EXP_SMOOTH_t UZ_EXP_SMOOTH_t;

/**
 * @brief Initialization of the simple exponential smoothing filter
 * 
 * @param alpha smoothing factor \alpha, 0 ≤ α ≤ 1
 * @return UZ_EXP_SMOOTH_t* pointer instance
 */

UZ_EXP_SMOOTH_t* uz_EXP_SMOOTH_init(float alpha);

/**
 * @brief Function to filter an input signal with exponential smoothing filter
	 *
 * @param self pointer instance of UZ_EXP_SMOOTH_t*
 * @param input signal, which will be filtered
 * @return float filtered signal
 */
float uz_EXP_SMOOTH_sample(UZ_EXP_SMOOTH_t* self, float input);

#endif // UZ_EXP_SMOOTH_H
