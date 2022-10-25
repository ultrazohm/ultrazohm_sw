/******************************************************************************
* Copyright Contributors to the UltraZohm project.
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
	float circularBuffer[MAX_FILTERLENGTH];	//array to save the last [MAX_FILTERLENGTH] input-samples of the filter
	int bufferindex;						//index in circularBuffer where to put new samples
	int filterLength;
	int old_filterLength;
	float sum;
}uz_movingAverageFilter_t;

static uint32_t instance_movingAverageFilter_counter = 0U;

static uz_movingAverageFilter_t instances_movingAverageFilter[UZ_MOVINGAVERAGEFILTER_MAX_INSTANCES] = { 0 };

static uz_movingAverageFilter_t* uz_movingAverageFilter_allocation(void);


static uz_movingAverageFilter_t* uz_movingAverageFilter_allocation(void){
 uz_assert(instance_movingAverageFilter_counter < UZ_MOVINGAVERAGEFILTER_MAX_INSTANCES);
 uz_movingAverageFilter_t* self = &instances_movingAverageFilter[instance_movingAverageFilter_counter];
 instance_movingAverageFilter_counter = instance_movingAverageFilter_counter + 1;
 uz_assert_false(self->is_ready);
 self->is_ready = true;
 return (self);
}

uz_movingAverageFilter_t* uz_movingAverageFilter_init(struct uz_movingAverageFilter_config config){
	uz_movingAverageFilter_t* self = uz_movingAverageFilter_allocation();
	self->bufferindex = 0;
	uz_assert(config.filterLength <= MAX_FILTERLENGTH);
	self->filterLength = config.filterLength;


	self->sum = 0.0f;
	int i = 0;
	for (i = 0; i<self->filterLength; i++){
		self->circularBuffer[i] = 0;
	}


    return(self);
}


float uz_movingAverageFilter_sample_variable_length(uz_movingAverageFilter_t* self, float sample){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);

	//add new sample to circular buffer
	self->circularBuffer[self->bufferindex] = sample;
	int index = 0;
	int firstsample = 0;

	float output = 0.0f;

	if(self->filterLength == self->old_filterLength){
		//Only add newest value and delete oldest one
		firstsample = (self->bufferindex - self->filterLength);
		if (firstsample < 0){
			firstsample = firstsample + MAX_FILTERLENGTH;
		}
		output = self->sum + self->circularBuffer[self->bufferindex] - self->circularBuffer[firstsample];
	//Only use different calculation, if it results in less loop-iterations
	} else if(abs(self->filterLength - self->old_filterLength) <= self->filterLength) {
		//Increasing filter length
		if(self->filterLength > self->old_filterLength) {
			output = self->sum;
			if(self->filterLength - self->old_filterLength == 1) {
				output = output + self->circularBuffer[self->bufferindex];
			} else {
				output = output + self->circularBuffer[self->bufferindex];
				int start = (((self->bufferindex - self->filterLength)+1 + MAX_FILTERLENGTH) % MAX_FILTERLENGTH);
				int end = (start - 2 + (self->filterLength - self->old_filterLength) + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
				if (start > end) {
					//Because the for-loop would wrap around around the max_length, for loop has to be split up
					for(int i = start; i < MAX_FILTERLENGTH; i++){
						index = (i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
						output = output + self->circularBuffer[index];
					}
					for(int i = 0; i <= end; i++){
						index = (i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
						output = output + self->circularBuffer[index];
					}
				} else {
					for(int i = start; i <= end; i++){
						index = (i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
						output = output + self->circularBuffer[index];
					}
				}
			}
		//Decreasing filter length
		} else if((self->filterLength < self->old_filterLength)) {
			output = self->sum;
			//Add newest value to avarage
			output = output + self->circularBuffer[self->bufferindex];
			//Delete oldest values, which are not part of the average anymore
			int end = (((self->bufferindex - self->filterLength) + MAX_FILTERLENGTH) % MAX_FILTERLENGTH);
			int start = (end - (self->old_filterLength - self->filterLength) + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
			if (start > end) {
				//Because the for-loop would wrap around the max_length, for loop has to be split up
				for(int i = start; i < MAX_FILTERLENGTH; i++){
					index = (i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
					output = output - self->circularBuffer[index];
				}
				for(int i = 0; i <= end; i++){
					index = (i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
					output = output - self->circularBuffer[index];
				}
			} else {
				for(int i = start; i <= end; i++){
					index = (i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
					output = output - self->circularBuffer[index];
				}
			}
		}
	} else {
		//Traditional looping, if the other cases result in no faster calculation
		output = 0.0f;
		for(int i = 0; i < self->filterLength; i++){
			int index = (self->bufferindex - i + MAX_FILTERLENGTH) % MAX_FILTERLENGTH;
			output = output + self->circularBuffer[index];
		}
	}

	self->sum = output;
	self->old_filterLength = self->filterLength;
	output = output/((float)self->filterLength);
	//modulo-increment of buffer-index
	self->bufferindex = (self->bufferindex + 1) % MAX_FILTERLENGTH;

	return(output);

}

float uz_movingAverageFilter_sample(uz_movingAverageFilter_t* self, float sample){
	uz_assert_not_NULL(self);
	float output = 0.0f;
	// add sample to buffer
	
	self->circularBuffer[self->bufferindex] = sample/((float)self->filterLength);
	// find oldest sample in current sum

	int firstsample = (self->bufferindex - self->filterLength);
	if (firstsample < 0){
	}
		firstsample = firstsample + MAX_FILTERLENGTH - 1;

	self->sum = self->sum + self->circularBuffer[self->bufferindex] - self->circularBuffer[firstsample];
	// add new input to sum, subtract oldest sample from sum

	output = self->sum;


	//modulo-increment of buffer-index
	self->bufferindex = (self->bufferindex + 1) % MAX_FILTERLENGTH;

	return output;
}

void uz_movingAverageFilter_reset(uz_movingAverageFilter_t* self){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	for(int i = 0; i < MAX_FILTERLENGTH; i++){
		self->circularBuffer[i] = 0.0f;
	}
	self->bufferindex = 0;
	self->old_filterLength = 0;
	self->sum = 0.0f;

}

void uz_movingAverageFilter_set_filterLength(uz_movingAverageFilter_t* self, int new_filterLength){
	uz_assert_not_NULL(self);
	uz_assert(self->is_ready);
	if(new_filterLength > MAX_FILTERLENGTH){
		new_filterLength = MAX_FILTERLENGTH;
	}
	self->filterLength = new_filterLength;
}
