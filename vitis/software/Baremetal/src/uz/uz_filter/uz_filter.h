#ifndef UZ_FILTER_H
#define UZ_FILTER_H

#define UZ_FILTER_MAX_INSTANCES 12
#define BUFFERLENGTH_FILTER 50


#include <stdbool.h>

/**
 * @brief Object definition for uz_Filter_t
 *
 */
typedef struct uz_filter_t{
	bool is_ready;
	int bufferPointer;
	float* circularBufferInput;
	float* circularBufferOutput;
	float* filterParameterA;
	float* filterParameterB;
	int filterLength;
}uz_filter_t;



/**
 * @brief Configuration struct for filter. Accessible by the user
 */
struct uz_filter_config {
	int filterLength;
	float* filterParameterA;
	float* filterParameterB;
	float* circularBufferInput;
	float* circularBufferOutput;
};

/*
 * @brief init function for the filter
 *
 * @param uz_filter_config config struct for the filter
 * @return uz_filter_t* pointer to the initilized filter
 */
uz_filter_t* uz_filter_init(struct uz_filter_config config);

/*
 *
 */
float uz_filter_sample(uz_filter_t* self, float sample);

/*
 * @brief reset function for the filter
 *
 * @param uz_filter_t* pointer to the filter
 */
void uz_filter_reset(uz_filter_t* self);



#endif //UZ_FILTER_H
