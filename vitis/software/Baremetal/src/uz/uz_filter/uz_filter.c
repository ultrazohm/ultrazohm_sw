#include "uz_filter.h"

#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include "../uz_math_constants.h"
#include "../uz_signals/uz_signals.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFERLENGTH_FILTER 50


typedef struct uz_filter_t{
	bool is_ready;
	int bufferPointer;
	double* circularBufferInput;
	double* circularBufferOutput;
	double* filterParameterA;
	double* filterParameterB;
	int filterLength;
}uz_filter_t;

static uint32_t instance_filter_counter = 0U;
static uz_filter_t instances_filter[UZ_FILTER_MAX_INSTANCES] = { 0 };

static uz_filter_t* uz_filter_allocation(void);


static uz_filter_t* uz_filter_allocation(void){
 uz_assert(instance_filter_counter < UZ_FILTER_MAX_INSTANCES);
 uz_filter_t* self = &instances_filter[instance_filter_counter];
 instance_filter_counter = instance_filter_counter + 1;
 uz_assert_false(self->is_ready);
 self->is_ready = true;
 return (self);
}

uz_filter_t* uz_filter_init(struct uz_filter_config config){
	uz_filter_t* self = uz_filter_allocation();
	self->bufferPointer = 0;
	uz_assert(config.filterLength <= BUFFERLENGTH_FILTER);
	self->filterLength = config.filterLength;
	self->filterParameterA = config.filterParameterA;
	self->filterParameterB = config.filterParameterB;
	self->circularBufferInput = config.circularBufferInput;
	self->circularBufferOutput = config.circularBufferOutput;
    return(self);
}


double uz_filter_sample(uz_filter_t* self, double sample){
	uz_assert_not_NULL(self);

	//add new sample to circular input buffer
	self->circularBufferInput[self->bufferPointer] = sample;

	double b = 0.0;
	double a = 0.0;

	for(int i = 0; i < self->filterLength; i++){
		int index = (self->bufferPointer - i + self->filterLength) % self->filterLength;
		b = b +  self->filterParameterB[i] * self->circularBufferInput[index];
	}


	//without a0
	for(int i = 1; i < self->filterLength; i++){
		int index = (self->bufferPointer - i + self->filterLength) % self->filterLength;
		a = a + self->filterParameterA[i] * self->circularBufferOutput[index];
	}


	double output = 1/(self->filterParameterA[0]) * (b - a);		//a0 normally is 1, but to be certain it is included in this equation


	self->circularBufferOutput[self->bufferPointer] = output;



	//modulo-increment of buffer-pointer
	self->bufferPointer = (self->bufferPointer + 1) % self->filterLength;

	return output;
}


void uz_filter_reset(uz_filter_t* self){
	uz_assert_not_NULL(self);
	for(int i = 0; i < self->filterLength; i++){
		self->circularBufferInput[i] = 0.0f;
		self->circularBufferOutput[i] = 0.0f;
	}
	self->bufferPointer = 0;

}
