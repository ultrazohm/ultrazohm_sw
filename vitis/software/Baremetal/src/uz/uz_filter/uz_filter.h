#ifndef UZ_FILTER_H
#define UZ_FILTER_H

#define UZ_FILTER_MAX_INSTANCES 6




/**
 * @brief Object definition for uz_Filter_t
 *
 */
typedef struct uz_filter_t uz_filter_t;


/**
 * @brief Configuration struct for filter. Accessible by the user
 */
struct uz_filter_config {
	int filterLength;
	double* filterParameterA;
	double* filterParameterB;
	double* circularBufferInput;
	double* circularBufferOutput;
};

/*
 *
 */
uz_filter_t* uz_filter_init(struct uz_filter_config config);

/*
 *
 */
double uz_filter_sample(uz_filter_t* self, double sample);

/*
 *
 */
void uz_filter_reset(uz_filter_t* self);



#endif //UZ_FILTER_H
