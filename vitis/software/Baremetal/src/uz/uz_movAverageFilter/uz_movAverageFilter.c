#include "uz_movAverageFilter.h"

#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct uz_movAverageFilter_t{
	bool is_ready;
	int bufferPointer;
	float circularBuffer[MAX_FILTERLENGTH];
	int filterLength;
}uz_movAverageFilter_t;

static uint32_t instance_movAverageFilter_counter = 0U;
static uz_movAverageFilter_t instances_movAverageFilter[UZ_MOVAVERAGEFILTER_MAX_INSTANCES] = { 0 };

static uz_movAverageFilter_t* uz_movAverageFilter_allocation(void);


static uz_movAverageFilter_t* uz_movAverageFilter_allocation(void){
 uz_assert(instance_movAverageFilter_counter < UZ_MOVAVERAGEFILTER_MAX_INSTANCES);
 uz_movAverageFilter_t* self = &instances_movAverageFilter[instance_movAverageFilter_counter];
 instance_movAverageFilter_counter = instance_movAverageFilter_counter + 1;
 uz_assert_false(self->is_ready);
 self->is_ready = true;
 return (self);
}

uz_movAverageFilter_t* uz_movAverageFilter_init(struct uz_movAverageFilter_config config){
	uz_movAverageFilter_t* self = uz_movAverageFilter_allocation();
	self->bufferPointer = 0;
	uz_assert(config.filterLength <= MAX_FILTERLENGTH);
	self->filterLength = config.filterLength;
    return(self);
}


float uz_movAverageFilter_sample(uz_movAverageFilter_t* self, float sample){
	uz_assert_not_NULL(self);

	//add new sample to circular buffer
	self->circularBuffer[self->bufferPointer] = sample;

	float output = 0.0f;

	//calculate filter output: sum of n samples in circular buffer, n = current length of the filter
	for(int i = 0; i < self->filterLength; i++){
		int index = (self->bufferPointer - i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
		output = output + self->circularBuffer[index];
	}

	output = output/(float)self->filterLength;


	//modulo-increment of buffer-pointer
	self->bufferPointer = (self->bufferPointer + 1) % MAX_FILTERLENGTH;

	return output;
}


void uz_movAverageFilter_reset(uz_movAverageFilter_t* self){
	uz_assert_not_NULL(self);
	for(int i = 0; i < MAX_FILTERLENGTH; i++){
		self->circularBuffer[i] = 0.0f;
	}
	self->bufferPointer = 0;

}

void uz_movAverageFilter_set_filterLength(uz_movAverageFilter_t* self, int new_filterLength){
	uz_assert_not_NULL(self);
	if(new_filterLength > MAX_FILTERLENGTH){
		new_filterLength = MAX_FILTERLENGTH;
	}
	self->filterLength = new_filterLength;
}
