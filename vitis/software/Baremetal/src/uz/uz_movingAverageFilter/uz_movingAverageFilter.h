#ifndef UZ_MOVINGAVERAGE_H
#define UZ_MOVINGAVERAGE_H

/**
 * @brief Maximum length of moving average filter
 */
#define MAX_FILTERLENGTH 450

/**
 * @brief Object definition for uz_movingAverageFilter_t
 *
 */
typedef struct uz_movingAverageFilter_t uz_movingAverageFilter_t;


/**
 * @brief Configuration struct for movingAverageFilter. Accessible by the user.
 */
struct uz_movingAverageFilter_config{
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
 * @return float output of the filter
 */
float uz_movingAverageFilter_sample(uz_movingAverageFilter_t* self, float sample);


/**
 * @brief Calculates one sample of the moving average filter in a more efficient way, not suitable for dynamic change of filter-length during operation without reset
 *
 * @param self pointer to uz_movingAverageFilter_t instance
 * @param foat sample input of the moving average filter
 * @return float output of the filter
 */
float uz_movingAverageFilter_sample_efficient(uz_movingAverageFilter_t* self, float sample);

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
void uz_movingAverageFilter_set_filterLength(uz_movingAverageFilter_t* self, int new_filterLength);



#endif //UZ_MOVINGAVERAGE_H
