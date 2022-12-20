/******************************************************************************
* Copyright Contributors to the UltraZohm project.

* Copyright 2022 Josef Knoblach, Dennis Hufnagel

* Copyright 2022 Josef Knoblach
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and limitations under the License.
******************************************************************************/

#include "uz_movingAverageFilter.h"
#include "../uz_global_configuration.h"
#include "../uz_HAL.h"
#include <stdlib.h>

typedef struct uz_movingAverageFilter_t{
	bool is_ready;
	uz_array_float_t circularBuffer;
	uint32_t bufferindex;						//index in circularBuffer where to put new samples
	uint32_t filterLength;
	uint32_t MAX_LENGTH;
	uint32_t old_filterLength;
	float old_value;							//previous value at bufferindex, before being overwritten
	float sum;
	float circularBuffer[MAX_FILTERLENGTH];	//array to save the last [MAX_FILTERLENGTH] input-samples of the filter
	int bufferPointer;						//index in circularBuffer where to put new samples
	int filterLength;
}uz_movingAverageFilter_t;

static uint32_t instance_movingAverageFilter_counter = 0U;

static uz_movingAverageFilter_t instances_movingAverageFilter[UZ_MOVINGAVERAGEFILTER_MAX_INSTANCES] = { 0 };

static uz_movingAverageFilter_t* uz_movingAverageFilter_allocation(void);


static uz_movingAverageFilter_t* uz_movingAverageFilter_allocation(void){
 	uz_assert(instance_movingAverageFilter_counter < UZ_MOVINGAVERAGEFILTER_MAX_INSTANCES);
 	uz_movingAverageFilter_t* self = &instances_movingAverageFilter[instance_movingAverageFilter_counter];
  	instance_movingAverageFilter_counter = instance_movingAverageFilter_counter + 1U;
 	uz_assert_false(self->is_ready);
 	self->is_ready = true;
 	return (self);
}

uz_movingAverageFilter_t* uz_movingAverageFilter_init(struct uz_movingAverageFilter_config config, uz_array_float_t circularBuffer){
	uz_movingAverageFilter_t* self = uz_movingAverageFilter_allocation();
	self->bufferindex = 0U;
	self->MAX_LENGTH = circularBuffer.length;
	uz_assert(config.filterLength <= self->MAX_LENGTH);
	self->filterLength = config.filterLength;
 	self->circularBuffer = circularBuffer;
    return(self);
}


float uz_movingAverageFilter_sample_variable_length(uz_movingAverageFilter_t* self, float sample){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);

	//add new sample to circular buffer
	self->circularBuffer.data[self->bufferindex] = sample;
	uint32_t index = 0U;
	float output = 0.0f;
	if(self->filterLength == self->old_filterLength){
		//Only add newest value and delete oldest one
		if(self->filterLength == self->MAX_LENGTH) {
			//Use old value at circularBuffer[bufferindex], because it was overwritten
			output = self->sum + self->circularBuffer.data[self->bufferindex] - self->old_value;
		} else {
			uint32_t firstsample = ((self->bufferindex - self->filterLength) + self->MAX_LENGTH) % self->MAX_LENGTH;
			output = self->sum + self->circularBuffer.data[self->bufferindex] - self->circularBuffer.data[firstsample];
		}

	//Increasing filter length
	} else if(self->filterLength > self->old_filterLength) {
		//Increasing filter length
		output = self->sum;
		if((self->filterLength - self->old_filterLength) == 1U) {
			//If length increases by 1, only add the newest value
			output = output + self->circularBuffer.data[self->bufferindex];
		} else {
			//Add newest value to average
			output = output + self->circularBuffer.data[self->bufferindex];
			//Determine the start and end indicies for the values, which will be added with the new filterlength
			uint32_t start = (((self->bufferindex - self->filterLength)+1U + self->MAX_LENGTH) % self->MAX_LENGTH);
			uint32_t end = (start - 2U + (self->filterLength - self->old_filterLength) + self->MAX_LENGTH) % self->MAX_LENGTH;
			if (start > end) {
				//Additional break-conditions to include edge-case, when the filterlength wraps around the MAX_LENGTH
				for(uint32_t i = start; ( (i <= self->MAX_LENGTH) && (i > (end + 1U)) ) || (i <= end); i = (i + 1U) % self->MAX_LENGTH){
					index = (i + self->MAX_LENGTH) % self->MAX_LENGTH;
					output = output + self->circularBuffer.data[index];
				}
			} else {
				for(uint32_t i = start; i <= end; i++){
				index = (i + self->MAX_LENGTH) % self->MAX_LENGTH;
				output = output + self->circularBuffer.data[index];
				}
			}
		}
	//Decreasing filter length
	//Only use different approach, if it results in less loop-iterations
	} else if((self->old_filterLength - self->filterLength) <= (self->filterLength)) {
		output = self->sum;
		//Add newest value to average
		output = output + self->circularBuffer.data[self->bufferindex];
		//Determine the start and end indicies for the values, which got dropped with the new filterlength
		uint32_t end = (((self->bufferindex - self->filterLength) + self->MAX_LENGTH) % self->MAX_LENGTH);
		uint32_t start = (end - (self->old_filterLength - self->filterLength) + self->MAX_LENGTH) % self->MAX_LENGTH;
		//Additional break-conditions to include edge-case, when the filterlength wraps around the MAX_LENGTH
		if (start > end) {
			//Additional break-conditions to include edge-case, when the filterlength wraps around the MAX_LENGTH
			for(uint32_t i = start; ( (i <= self->MAX_LENGTH) && (i > (end + 1U)) ) || (i <= end); i = (i + 1U) % self->MAX_LENGTH){
				index = (i + self->MAX_LENGTH) % self->MAX_LENGTH;
				output = output - self->circularBuffer.data[index];
			}
		} else {
			for(uint32_t i = start; i <= end; i++){
				index = (i + self->MAX_LENGTH) % self->MAX_LENGTH;
				output = output - self->circularBuffer.data[index];
			}
		}
	} else {
		//Traditional looping, if the other cases result in no faster calculation
		output = 0.0f;
		for(uint32_t i = 0U; i < self->filterLength; i++){
			index = (self->bufferindex - i + self->MAX_LENGTH) % self->MAX_LENGTH;
			output = output + self->circularBuffer.data[index];
		}
	}

	self->sum = output;
	self->old_filterLength = self->filterLength;
	output = output/((float)self->filterLength);
	//modulo-increment of buffer-index
	self->bufferindex = (self->bufferindex + 1U) % self->MAX_LENGTH;
	//Safe "old" value at new bufferindex. Needed, when the filterlength==self->MAX_LENGTH
	self->old_value= self->circularBuffer.data[self->bufferindex];

	return(output);
 uz_assert(instance_movingAverageFilter_counter < UZ_MOVINGAVERAGEFILTER_MAX_INSTANCES);
 uz_movingAverageFilter_t* self = &instances_movingAverageFilter[instance_movingAverageFilter_counter];
 instance_movingAverageFilter_counter = instance_movingAverageFilter_counter + 1;
 uz_assert_false(self->is_ready);
 self->is_ready = true;
 return (self);
}

uz_movingAverageFilter_t* uz_movingAverageFilter_init(struct uz_movingAverageFilter_config config){
	uz_movingAverageFilter_t* self = uz_movingAverageFilter_allocation();
	self->bufferPointer = 0;
	uz_assert(config.filterLength <= MAX_FILTERLENGTH);
	self->filterLength = config.filterLength;

/*
	self->sum = 0;
	int i = 0;
	for (i = 0; i<self->filterLength; i++){
		self->circularBuffer[i] = 0;
	}
*/

    return(self);
}


float uz_movingAverageFilter_sample(uz_movingAverageFilter_t* self, float sample){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	//NXOR. Assert that the filter length hasn't changed. Exception for when the filter was reset (old_filterlength == 0)
	uz_assert((self->filterLength == self->old_filterLength) != (self->old_filterLength == 0U));
	float output = 0.0f;

	// add sample to buffer
	self->circularBuffer.data[self->bufferindex] = sample/((float)self->filterLength);
	
	// find oldest sample in current sum
	uint32_t firstsample = ((self->bufferindex - self->filterLength) + self->MAX_LENGTH) % self->MAX_LENGTH;
	
	// add new input to sum, subtract oldest sample from sum
	if(self->filterLength == self->MAX_LENGTH) {
		//Adds special case, since firstsample calculation breaks otherwise
		self->sum = self->sum + self->circularBuffer.data[self->bufferindex] - self->old_value;
	} else {
		self->sum = self->sum + self->circularBuffer.data[self->bufferindex] - self->circularBuffer.data[firstsample];
	}
	
	
	output = self->sum;
	//modulo-increment of buffer-index
	self->bufferindex = (self->bufferindex + 1U) % self->MAX_LENGTH;
	self->old_value = self->circularBuffer.data[self->bufferindex];
	self->old_filterLength = self->filterLength;

	//add new sample to circular buffer
	self->circularBuffer[self->bufferPointer] = sample;

	float output = 0.0f;

	//calculate filter output: sum of i samples in circular buffer, i = current length of the filter
	for(int i = 0; i < self->filterLength; i++){
		int index = (self->bufferPointer - i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
		output = output + self->circularBuffer[index];
	}

	output = output/(float)self->filterLength;


	/*
	// add sample to buffer
	self->circularBuffer[self->bufferPointer] = sample/((float)self->filterLength);

	// find oldest sample in current sum
	int firstsample = (self->bufferPointer - filterLength +1);
	if (firstsample < 0){
		firstsample = firstsample + MAX_FILTERLENGTH;
	}

	self->sum = self->sum + self->circularBuffer[self->bufferPointer] - self->circularBuffer[firstsample];

	output = self->sum;
*/

	//modulo-increment of buffer-pointer
	self->bufferPointer = (self->bufferPointer + 1) % MAX_FILTERLENGTH;

	return output;
}


void uz_movingAverageFilter_reset(uz_movingAverageFilter_t* self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	for(uint32_t i = 0U; i < self->MAX_LENGTH; i++){
		self->circularBuffer.data[i] = 0.0f;
	}
	self->bufferindex = 0U;
	self->old_filterLength = 0U;
	self->sum = 0.0f; 
	self->old_value = 0.0f;

}

void uz_movingAverageFilter_set_filterLength(uz_movingAverageFilter_t* self, uint32_t new_filterLength){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	uz_assert(new_filterLength <= self->MAX_LENGTH);
	uz_assert(new_filterLength > 0U);
	for(int i = 0; i < MAX_FILTERLENGTH; i++){
		self->circularBuffer[i] = 0.0f;
	}
	self->bufferPointer = 0;

}

void uz_movingAverageFilter_set_filterLength(uz_movingAverageFilter_t* self, int new_filterLength){
	uz_assert_not_NULL(self);
	if(new_filterLength > MAX_FILTERLENGTH){
		new_filterLength = MAX_FILTERLENGTH;
	}
	self->filterLength = new_filterLength;
}
