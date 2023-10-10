/******************************************************************************
* Copyright Contributors to the UltraZohm project.
* Copyright 2023 Robert Zipprich
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

#include "../uz_Trajectory/uz_Trajectory.h"

#include "../uz_global_configuration.h"
#include "../uz_signals/uz_signals.h"
#include "../uz_HAL.h"
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

#if UZ_TRAJECTORY_MAX_INSTANCES > 0
typedef struct uz_Trajectory_t {
	bool is_ready;
	struct uz_Trajectory_config config;
	bool is_runing;
	bool is_finished;
	uint32_t Trajectory_Counter;
	uint32_t Step_Counter;
	uint32_t Repeats_Counter;
	float Min_Step_Width;
}uz_Trajectory_t;

static uint32_t instance_counter = 0U;
static uz_Trajectory_t instances[UZ_TRAJECTORY_MAX_INSTANCES] = { 0 };

static uz_Trajectory_t* uz_Trajectory_allocation(void);

static uint32_t get_TimeBase(uz_Trajectory_t* self, uint32_t Step);

static uz_Trajectory_t* uz_Trajectory_allocation(void){
 uz_assert(instance_counter < UZ_TRAJECTORY_MAX_INSTANCES);
 uz_Trajectory_t* self = &instances[instance_counter];
 uz_assert_false(self->is_ready);
 instance_counter++;
 self->is_ready = true;
 return (self);
}

uz_Trajectory_t* uz_Trajectory_init(struct uz_Trajectory_config config){
	uz_Trajectory_t* self = uz_Trajectory_allocation();
	uz_assert(config.Number_Sample_Points < Max_Trajectory_Samples);
    self->config = config;
    self->is_runing = false;
    self->Trajectory_Counter = 0U;
    self->Step_Counter = 0U;
    self->Repeats_Counter = 0U;
    self->Min_Step_Width = 2*self->config.Stepwidth_ISR;
    return(self);
}

void uz_Trajectory_Start(uz_Trajectory_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    if(self->is_finished == false){
    	self->is_runing = true;
    }
}

void uz_Trajectory_Stop(uz_Trajectory_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->is_runing = false;
}

void uz_Trajectory_Reset(uz_Trajectory_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->is_runing = false;
    self->is_finished = false;
    self->Trajectory_Counter = 0U;
    self->Step_Counter = 0U;
    self->Repeats_Counter = 0U;
}

float uz_Trajectory_Step(uz_Trajectory_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    float Temp_Trajectory_out = 0.0f;

    // Check if Trajectory is Running
	if(self->is_runing == true && self->is_finished == false){

		if(self->config.RepeatStyle == Repeat_Times){
			if(self->Repeats_Counter < self->config.Repeats){
				if(self->Step_Counter < self->config.Number_Sample_Points){
					// Choose Interpolation-Style
					switch(self->config.selection_interpolation){
					case Zero_Order_Hold:
						// Calculate Indizies
						Temp_Trajectory_out = self->config.Sample_Amplitdue_X[self->Step_Counter];
						break;
					case Linear:
						// TO IMPLEMENT
						Temp_Trajectory_out = 0.0f;
						break;
					case Spline:
						// TO IMPLEMENT
						Temp_Trajectory_out = 0.0f;
						break;
					default:
						// Trigger an Assertion- this code should never be reached
						uz_assert(true);
						break;
					}
					// Increase Trajectory-Counter
					self->Trajectory_Counter++;
					// Calculate actual Step
					if(self->Trajectory_Counter >= get_TimeBase(self, self->Step_Counter)){
						// Increase-Step-Counter
						self->Step_Counter++;
						self->Trajectory_Counter = 0U;
					}
				}else{
					self->Repeats_Counter++;
					self->Step_Counter = 0U;
				}
			}else{
				//finished running
				self->is_runing = false;
				self->is_finished = true;
			}


		}else if(self->config.RepeatStyle == Repeat_Inf){

			if(self->Step_Counter < self->config.Number_Sample_Points){
				// Choose Interpolation-Style
				switch(self->config.selection_interpolation){
				case Zero_Order_Hold:
					// Calculate Indizies
					Temp_Trajectory_out = self->config.Sample_Amplitdue_X[self->Step_Counter];
					break;
				case Linear:
					// TO IMPLEMENT
					Temp_Trajectory_out = 0.0f;
					break;
				case Spline:
					// TO IMPLEMENT
					Temp_Trajectory_out = 0.0f;
					break;
				default:
					// Trigger an Assertion- this code should never be reached
					uz_assert(true);
					break;
				}
				// Increase Trajectory-Counter
				self->Trajectory_Counter++;
				// Calculate actual Step
				if(self->Trajectory_Counter >= get_TimeBase(self, self->Step_Counter)){
					// Increase-Step-Counter
					self->Step_Counter++;
					self->Trajectory_Counter = 0U;
				}
			}else{
				self->Step_Counter = 0U;
			}
		}

	}else{ // Trajectory not running

		switch(self->config.StopStyle){
			case ForceToZero:
				Temp_Trajectory_out = 0.0f;
				break;
			case HoldLast:
				Temp_Trajectory_out = self->config.Sample_Amplitdue_X[self->Step_Counter];
				break;
			default:
				// Trigger an Assertion- this code should never be reached
				uz_assert(true);
				Temp_Trajectory_out = 0.0f;
				break;
		}

	}
	return Temp_Trajectory_out;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//-----------------Internal Functions----------------------------------------------------------------------------------------------------------------

// returns the amount if Tickz to wait between each step
static uint32_t get_TimeBase(uz_Trajectory_t* self, uint32_t Step){
	// Default-Tickz set to 1
	uint32_t Tickz = 1U;
	switch(self->config.selection_YAxis){
		case ISR_Ticks:
			// Simply output the Number of Tickz from the Y-Array
			Tickz = (uint32_t)self->config.Sample_Duration_Y[Step];
			break;
		case MicroSeconds:
			Tickz = (uint32_t)((self->config.Sample_Duration_Y[Step] * 0.000001f ) / self->config.Stepwidth_ISR);
			break;
		case MilliSeconds:
			Tickz = (uint32_t)((self->config.Sample_Duration_Y[Step] * 0.001f) / self->config.Stepwidth_ISR);
			break;
		case Seconds:
			Tickz = (uint32_t)((self->config.Sample_Duration_Y[Step] * 1.0f) / self->config.Stepwidth_ISR);
			break;
		default:
			// Trigger an Assertion- this code should never be reached
			uz_assert(true);
	}
	uz_assert(Tickz>2U);
	return Tickz;
}

#endif
