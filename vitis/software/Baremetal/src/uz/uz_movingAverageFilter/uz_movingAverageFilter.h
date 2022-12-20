#ifndef UZ_MOVINGAVERAGE_H
#define UZ_MOVINGAVERAGE_H
<<<<<<< HEAD
#include <stdint.h> 
#include "../uz_array/uz_array.h"
=======

/**
 * @brief Maximum length of moving average filter
 */
#define MAX_FILTERLENGTH 150

>>>>>>> feature/Test_6Phase_FCS_MPC
/**
 * @brief Object definition for uz_movingAverageFilter_t
 *
 */
typedef struct uz_movingAverageFilter_t uz_movingAverageFilter_t;


/**
 * @brief Configuration struct for movingAverageFilter. Accessible by the user.
 */
struct uz_movingAverageFilter_config{
<<<<<<< HEAD
	uint32_t filterLength; /**<Length of the filter. Must be larger than 0 and smaller or equal to the length of the cirucularBuffer array*/
};

/**
 * @brief Initialization of the moving Average Filter object
 * 
 * @param config uz_movingAverageFilter_config configuration struct
 * @param circularBuffer circularBuffer array. The length of the array will be the MAX_LENGTH of the filter
 * @return uz_movingAverageFilter_t* pointer to uz_movingAverageFilter_t instance
 */
uz_movingAverageFilter_t* uz_movingAverageFilter_init(struct uz_movingAverageFilter_config config, uz_array_float_t circularBuffer);

/**
 * @brief Calculates one sample of the moving average filter. The filter length can be changed dynamically during runtime. It uses different approaches to calculate the result with the least amount of loop-iterations possible.
 * 
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param sample sample input of the moving average filter
 * @return float output of the filter
 */
float uz_movingAverageFilter_sample_variable_length(uz_movingAverageFilter_t* self, float sample);

/**
 * @brief Calculates one sample of the moving average filter with fixed filter length
 *
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param sample sample input of the moving average filter
=======
	int filterLength;
};

/*
 * @brief Initialization of the moving Average Filter object
 * @param config uz_movingAverageFilter_config configuration struct
 * @return pointer to uz_movingAverageFilter_t instance
 */
uz_movingAverageFilter_t* uz_movingAverageFilter_init(struct uz_movingAverageFilter_config config);

/**
 * @brief Calculates one sample of the moving average filter
 *
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param foat sample input of the moving average filter
>>>>>>> feature/Test_6Phase_FCS_MPC
 * @return float output of the filter
 */
float uz_movingAverageFilter_sample(uz_movingAverageFilter_t* self, float sample);

/**
 * @brief Resets the moving average filter
 *
 * @param self uz_movingAverageFilter_t instance
 */
void uz_movingAverageFilter_reset(uz_movingAverageFilter_t* self);

<<<<<<< HEAD
/**
 * @brief Sets a new filter length
 * 
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param new_filterLength new value for the filter length
 */
void uz_movingAverageFilter_set_filterLength(uz_movingAverageFilter_t* self, uint32_t new_filterLength);
=======
/*
 * @brief Sets a new filter length
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param new_filterLength int for the new filter length
 */
void uz_movingAverageFilter_set_filterLength(uz_movingAverageFilter_t* self, int new_filterLength);


>>>>>>> feature/Test_6Phase_FCS_MPC

#endif //UZ_MOVINGAVERAGE_H
