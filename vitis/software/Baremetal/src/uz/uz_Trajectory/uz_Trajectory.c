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
	bool is_running;
	bool is_finished;
	uint32_t Trajectory_Counter;
	uint32_t Step_Counter;
	uint32_t Repeats_Counter;
	float Interploation_Coefficients[4][Max_Trajectory_Samples-1];		// Dimensions are prepared for spline-interpolaten
	float Min_Step_Width;
}uz_Trajectory_t;

static uint32_t instance_counter = 0U;
static uz_Trajectory_t instances[UZ_TRAJECTORY_MAX_INSTANCES] = { 0 };

static uz_Trajectory_t* uz_Trajectory_allocation(void);

static uint32_t get_TimeBase(uz_Trajectory_t* self, uint32_t Step);
static uint32_t get_TimeBase_init(struct uz_Trajectory_config config, uint32_t Step);

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
    self->is_running = false;
    self->Trajectory_Counter = 0U;
    self->Step_Counter = 0U;
    self->Repeats_Counter = 0U;
    self->Min_Step_Width = 2*self->config.Stepwidth_ISR;

    float Sum_Timeaxis = 0.0f;
    if(config.selection_interpolation == Linear){ 	// create interpolation-coefficients for linear interpolation
    	for(int i = 0; i < (Max_Trajectory_Samples-1);i++){
    		Sum_Timeaxis = Sum_Timeaxis + get_TimeBase_init(config, config.Sample_Duration_X[i]);
    		self->Interploation_Coefficients[3][i] = 0.0f;	// not needed
    		self->Interploation_Coefficients[2][i] = 0.0f;	// not needed
    		self->Interploation_Coefficients[1][i] = (config.Sample_Amplitude_Y[i+1] - config.Sample_Amplitude_Y[i])/(get_TimeBase_init(config, config.Sample_Duration_X[i]));	// represents the slope
    		self->Interploation_Coefficients[0][i] = config.Sample_Amplitude_Y[i+1] - self->Interploation_Coefficients[1][i]*Sum_Timeaxis;	// represents the ordinate section
    	}
    }else if(config.selection_interpolation == Spline){ 													// create interpolation-coefficients for spline interpolation
    	for(int i = 0; i < (Max_Trajectory_Samples-1);i++){
			self->Interploation_Coefficients[3][i] = 0.0f;
			self->Interploation_Coefficients[2][i] = 0.0f;
			self->Interploation_Coefficients[1][i] = 0.0f;
			self->Interploation_Coefficients[0][i] = 0.0f;
    	}
    }														// no need for interpolation if zero-order-hold is selected
    return(self);
}

void uz_Trajectory_Start(uz_Trajectory_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    if(self->is_finished == false){
    	self->is_running = true;
    }
}

void uz_Trajectory_Stop(uz_Trajectory_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->is_running = false;
}

void uz_Trajectory_Reset(uz_Trajectory_t* self){
    uz_assert_not_NULL(self);
    uz_assert(self->is_ready);
    self->is_running = false;
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
	if(self->is_running == true && self->is_finished == false){

		if(self->config.RepeatStyle == Repeat_Times){
			if(self->Repeats_Counter < self->config.Repeats){
				if(self->Step_Counter < self->config.Number_Sample_Points){
					// Choose Interpolation-Style
					switch(self->config.selection_interpolation){
					case Zero_Order_Hold:
						// Use Indizies
						Temp_Trajectory_out = self->config.Sample_Amplitude_Y[self->Step_Counter];
						break;
					case Linear:
						// Calculate linear equation
						Temp_Trajectory_out = (self->Interploation_Coefficients[1][self->Step_Counter] * self->Trajectory_Counter + self->config.Sample_Amplitude_Y[self->Step_Counter]);
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
				self->is_running = false;
				self->is_finished = true;
			}


		}else if(self->config.RepeatStyle == Repeat_Inf){

			if(self->Step_Counter < self->config.Number_Sample_Points){
				// Choose Interpolation-Style
				switch(self->config.selection_interpolation){
				case Zero_Order_Hold:
					// Use Indizies
					Temp_Trajectory_out = self->config.Sample_Amplitude_Y[self->Step_Counter];
					break;
				case Linear:
					// Calculate linear equation
					Temp_Trajectory_out = (self->Interploation_Coefficients[1][self->Step_Counter] * self->Trajectory_Counter + self->config.Sample_Amplitude_Y[self->Step_Counter]);
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
				switch(self->config.selection_interpolation){
					case Zero_Order_Hold:
						// Use Indizies
						Temp_Trajectory_out = self->config.Sample_Amplitude_Y[self->Step_Counter];
						break;
					case Linear:
						// Calculate linear equation
						Temp_Trajectory_out = (self->Interploation_Coefficients[1][self->Step_Counter] * self->Trajectory_Counter + self->config.Sample_Amplitude_Y[self->Step_Counter]);
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
			Tickz = (uint32_t)self->config.Sample_Duration_X[Step];
			break;
		case MicroSeconds:
			Tickz = (uint32_t)((self->config.Sample_Duration_X[Step] * 0.000001f ) / self->config.Stepwidth_ISR);
			break;
		case MilliSeconds:
			Tickz = (uint32_t)((self->config.Sample_Duration_X[Step] * 0.001f) / self->config.Stepwidth_ISR);
			break;
		case Seconds:
			Tickz = (uint32_t)((self->config.Sample_Duration_X[Step] * 1.0f) / self->config.Stepwidth_ISR);
			break;
		default:
			// Trigger an Assertion- this code should never be reached
			uz_assert(true);
	}
	return Tickz;
}

static uint32_t get_TimeBase_init(struct uz_Trajectory_config config, uint32_t Duration){
	// Default-Tickz set to 1
	uint32_t Tickz = 1U;
	switch(config.selection_YAxis){
		case ISR_Ticks:
			// Simply output the Number of Tickz from the Y-Array
			Tickz = (uint32_t)Duration;
			break;
		case MicroSeconds:
			Tickz = (uint32_t)((Duration * 0.000001f ) / config.Stepwidth_ISR);
			break;
		case MilliSeconds:
			Tickz = (uint32_t)((Duration * 0.001f) / config.Stepwidth_ISR);
			break;
		case Seconds:
			Tickz = (uint32_t)((Duration * 1.0f) / config.Stepwidth_ISR);
			break;
		default:
			// Trigger an Assertion- this code should never be reached
			uz_assert(true);
	}
	return Tickz;
}



#endif
