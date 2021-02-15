/******************************************************************************
* Copyright 2021 Eyke Liegmann, Peter Stolze
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

#include <math.h>
//control_toolbox.h
//Toolbox for transformations, integrators, PI controllers, filters etc

//Sinewave generator
//amplitude:			Amplitude of the output sinewave
//frequency:			Frequency of the output sinewave
//phase:				Initial phase angle [rad]
//sample:				Pointer to sample no.
//int_freq:				Interrupt frequency (i. e. frequency of the control algorithm)
//return value:			Sine output
float sinewave(const float amplitude, const float frequency, const float phase, long *const sample, const float int_freq);

//Blockwave generator
float blockwave(const float amp_p, const float amp_n, const float frequency, const float phase, long *const sample, const float int_freq);

//Periodic Ramp generator
float rampwave(const float amp_p, const float amp_n, const float frequency, const float phase, long *const sample, const float int_freq);

//Pulse generator
float pulse(const float amplitude, const float duty, const float frequency, const float phase, long *const sample, const float int_freq);

//Clarke transformation (abc to alpha beta)
//alpha:					Alpha "phase" after Clarke transformation
//beta:						Beta "phase" after Clarke transformation
//a:						Phase a before Clarke transformation
//b:						Phase b before Clarke transformation
//c:						Phase c before Clarke transformation
void Clarke(float *const alpha, float *const beta, const float a, const float b, const float c);

//Clarke transformation (abc to alpha beta) for a balanced system (a + b + c = 0)
//alpha:					Alpha "phase" after Clarke transformation
//beta:						Beta "phase" after Clarke transformation
//a:						Phase a before Clarke transformation
//b:						Phase b before Clarke transformation
void Clarke_balanced(float *const alpha, float *const beta, const float a, const float b);

//Inverse Clarke transformation (alpha beta to abc)
//alpha:					Alpha "phase" before inverse Clarke transformation
//beta:						Beta "phase" before inverse Clarke transformation
//a:						Phase a after inverse Clarke transformation
//b:						Phase b after inverse Clarke transformation
//c:						Phase c after inverse Clarke transformation
void Clarke_inv(const float alpha, const float beta, float *const a, float *const b, float *const c);

//Park transformation (alpha beta to dq)
//alpha:					Alpha "phase" before Park transformation
//beta:						Beta "phase" before Park transformation
//d:						d "phase" after Park transformation
//q:						q "phase" after Park transformation
//phi:						Flux angle for Park transformation (0...2*pi)
void Park(const float alpha, const float beta, float *const d, float *const q, const float phi);

//Inverse Park transformation (dq to alpha beta)
//alpha:					Alpha "phase" before inverse Park transformation
//beta:						Beta "phase" before inverse Park transformation
//d:						d "phase" after inverse Park transformation
//q:						q "phase" after inverse Park transformation
//phi:						Flux angle for inverse Park transformation (0...2*pi)
void Park_inv(float *const alpha, float *const beta, const float d, const float q, const float phi);

//PI controller with anti windup and output limitation
//error:			Control error (reference - actual value)
//error_sum:		Pointer to storage variable for the summed error
//anti_windup:		Pointer anti-windup flag: 0: no output saturation and anti-windup; 1: output saturation and anti-windup
//Kp:				Proportional gain of the controller
//Ki:				Integral gain of the controller
//output_limit:		Output limit for the controller (if in output saturation then anti-windup for integral part)
//return value:		PI controller output
float PI_Controller(const float error, float *const error_sum, int *const anti_windup, const float Kp, const float Ki, const float output_limit, const float TSampling);

//Get magnitude and angle of a 2D vector
void karth_polar(float *const magn, float *const angle, const float x, const float y);

/* 1st order Low Pass Filter */
//input:			signal that you want to be filtered
//in_mem:			Pointer to storage variable
//out_mem:			Pointer to storage variable
//Fs:				sampling frequency of the low-pass filter
//Fc:				crossover frequency of the low-pass filter
//return value:		filtered signal
float LPF1(const float input, float *const in_mem, float *const out_mem, const float Fs, const float Fc);

/* 1st order High Pass Filter */
//input:			signal that you want to be filtered
//in_mem:			Pointer to storage variable
//out_mem:			Pointer to storage variable
//Fs:				sampling frequency of the low-pass filter
//Fc:				crossover frequency of the low-pass filter
//return value:		filtered signal
float HPF1(const float input, float *const in_mem, float *const out_mem, const float Fs, const float Fc);

