#ifndef UZ_MOVINGAVERAGE_H
#define UZ_MOVINGAVERAGE_H
#include <stdint.h> 
#include "../uz_array/uz_array.h"
/**
 * @brief Maximum length of moving average filter
 */
#define MAX_FILTERLENGTH 150

/**
 * @brief Object definition for uz_movingAverageFilter_t
 *
 */
typedef struct uz_movingAverageFilter_t uz_movingAverageFilter_t;


/**
 * @brief Configuration struct for movingAverageFilter. Accessible by the user.
 */
struct uz_movingAverageFilter_config{
	uint32_t filterLength;
};

/*
 * @brief Initialization of the moving Average Filter object
 * @param config uz_movingAverageFilter_config configuration struct
 * @return pointer to uz_movingAverageFilter_t instance
 */
uz_movingAverageFilter_t* uz_movingAverageFilter_init(struct uz_movingAverageFilter_config config, uz_array_float_t circularBuffer);

/**
 * @brief Calculates one sample of the moving average filter. The filter length can be changed dynamically during runtime
 *
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param foat sample input of the moving average filter
 * @return float output of the filter
 */
float uz_movingAverageFilter_sample_variable_length(uz_movingAverageFilter_t* self, float sample);


/**
 * @brief Calculates one sample of the moving average filter a efficient way. The filter length is fixed and can't be changed
 *
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param foat sample input of the moving average filter
 * @return float output of the filter
 */
float uz_movingAverageFilter_sample(uz_movingAverageFilter_t* self, float sample);

/**
 * @brief Resets the moving average filter
 *
 * @param self uz_movingAverageFilter_t instance
 */
void uz_movingAverageFilter_reset(uz_movingAverageFilter_t* self);

/*
 * @brief Sets a new filter length
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param new_filterLength int for the new filter length
 */
void uz_movingAverageFilter_set_filterLength(uz_movingAverageFilter_t* self, uint32_t new_filterLength);

#endif //UZ_MOVINGAVERAGE_H
