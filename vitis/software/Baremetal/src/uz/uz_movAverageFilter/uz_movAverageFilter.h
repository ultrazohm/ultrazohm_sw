#ifndef UZ_MOVAVERAGE_H
#define UZ_MOVAVERAGE_H

#define UZ_MOVAVERAGEFILTER_MAX_INSTANCES 2
#define maxFilterLength 100



/**
 * @brief Object definition for uz_movAverageFilter_t
 *
 */
typedef struct uz_movAverageFilter_t uz_movAverageFilter_t;


/**
 * @brief Configuration struct for movAverageFilter. Accessible by the user
 */
struct uz_movAverageFilter_config {
	int filterLength;
};

/*
 *
 */
uz_movAverageFilter_t* uz_movAverageFilter_init(struct uz_movAverageFilter_config config);

/*
 *
 */
float uz_movAverageFilter_sample(uz_movAverageFilter_t* self, float sample);

/*
 *
 */
void uz_uz_movAverageFilter_reset(uz_movAverageFilter_t* self);

/*
 *
 */
void uz_uz_movAverageFilter_set_filterLength(uz_movAverageFilter_t* self, int new_filterLength);



#endif //UZ_MOVAVERAGE_H
