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

//toolbox.c
//Toolbox for transformations, integrators, PI controllers, filters etc.
#include "control_toolbox.h"

// General comment about const and pointers:
// const *const x: 	Has to be read backwards: Constant pointer to constant variable
// const *const x: 	Both address and value cannot be manipulated
// const * x: 		The address can be changed but not the value
// *const x: 		The value can be changed but not the address

//Sinewave generator
//amplitude:			Amplitude of the output sinewave
//frequency:			Frequency of the output sinewave
//phase:				Initial phase angle [rad]
//sample:				Pointer to sample no.
//int_freq:				Interrupt frequency (i. e. frequency of the control algorithm)
//return value:			Sine output
float sinewave(const float amplitude, const float frequency, const float phase, long *const sample, const float int_freq)
{
	//Variables
	float angle;

	//Go back to 1st sample if end of sinewave is reached
	if(*sample >= int_freq/frequency - 1)
		*sample = 0;

	//Calculate angle and increase sample
	angle = 2.0*M_PI*frequency/int_freq*((float)(*sample));
	angle += phase;
	*sample += 1;

	return(amplitude*sin(angle));
}

//Blockwave generator
float blockwave(const float amp_p, const float amp_n, const float frequency, const float phase, long *const sample, const float int_freq)
{
	float angle;

	if(*sample >= int_freq/frequency - 1)
		*sample = 0;

	angle = 2.0*M_PI*frequency/int_freq*((float)(*sample));
	angle += phase;
	*sample += 1;
	angle = sin(angle);

	if(angle > 0.0)
		angle = amp_p;
	else
		angle = amp_n;

	return(angle);
}

//Periodic Ramp generator
float rampwave(const float amp_p, const float amp_n, const float frequency, const float phase, long *const sample, const float int_freq)
{
	float angle;
	if(*sample >= int_freq/frequency - 1)
		*sample = 0;

	angle =M_PI*frequency/int_freq*((float)(*sample));
	angle += phase/2.0;
	*sample += 1;

	if (cos(angle) >= 0.0)
		angle = asin(sin(angle))/M_PI;
	else
		angle = -asin(sin(angle))/M_PI;

	angle *= (amp_p - amp_n);
	angle += (amp_p + amp_n)/2.0;

	return(angle);
}

//Pulse generator
float pulse(const float amplitude, float duty, const float frequency, const float phase, long *const sample, const float int_freq)
{
	float sample_offset = phase/(2.0*M_PI*frequency)*int_freq;

	if(duty > 1.0)
		duty = 1.0;

	if(duty < 0.0)
		duty = 0.0;

	*sample += 1;

	if(*sample >= int_freq/frequency + sample_offset)
		*sample = sample_offset;

	if(*sample >= int_freq/frequency*duty + sample_offset)
		return 0.0;
	else
		return amplitude;
}

//Clarke transformation (abc to alpha beta)
//alpha:					Alpha "phase" after Clarke transformation
//beta:						Beta "phase" after Clarke transformation
//a:						Phase a before Clarke transformation
//b:						Phase b before Clarke transformation
//c:						Phase c before Clarke transformation
void Clarke(float *const alpha, float *const beta, const float a, const float b, const float c)
{
	*alpha = 0.6667*(a - 0.5*b - 0.5*c);
	*beta = 0.5773*(b - c);
}

//Clarke transformation (abc to alpha beta) for a balanced system (a + b + c = 0)
//alpha:					Alpha "phase" after Clarke transformation
//beta:						Beta "phase" after Clarke transformation
//a:						Phase a before Clarke transformation
//b:						Phase b before Clarke transformation
void Clarke_balanced(float *const alpha, float *const beta, const float a, const float b)
{
	*alpha = a;
	*beta = 0.57735*a + 1.1547*b;
}

//Inverse Clarke transformation (ab to abc)
//alpha:					Alpha "phase" before inverse Clarke transformation
//beta:						Beta "phase" before inverse Clarke transformation
//a:						Phase a after inverse Clarke transformation
//b:						Phase b after inverse Clarke transformation
//c:						Phase c after inverse Clarke transformation
void Clarke_inv(const float alpha, const float beta, float *const a, float *const b, float *const c)
{
	*a = alpha;
	*b = -0.5*alpha + 0.866*beta;
	*c = -0.5*alpha - 0.866*beta;
}

//Park transformation (alpha beta to dq)
//alpha:					Alpha "phase" before Park transformation
//beta:						Beta "phase" before Park transformation
//d:						d "phase" after Park transformation
//q:						q "phase" after Park transformation
//phi:						Flux angle for Park transformation (0...2*pi)
void Park(const float alpha, const float beta, float *const d, float *const q, const float phi)
{
	//Variables
	float sinphi = 0.0, cosphi = 0.0;

	//Calculate cos and sin of flux angle only once to save calculation time
	sinphi = sin(phi);
	cosphi = cos(phi);

	*d =  alpha*cosphi + beta*sinphi;
	*q = -alpha*sinphi + beta*cosphi;
}

//Inverse Park transformation (dq to alpha beta)
//alpha:					Alpha "phase" before inverse Park transformation
//beta:						Beta "phase" before inverse Park transformation
//d:						d "phase" after inverse Park transformation
//q:						q "phase" after inverse Park transformation
//phi:						Flux angle for inverse Park transformation (0...2*pi)
void Park_inv(float *const alpha, float *const beta, const float d, const float q, const float phi)
{
	//Inverse Park transformation is just the same as the "normal" Park transformation
	//BUT: phi for inverse Park transformation is the negative angle compared to the "normal" Park transformation

	//Variables
	float sinphi, cosphi;

	//Calculate cos and sin of flux angle only once to save calculation time
	sinphi = sin(phi);
	cosphi = cos(phi);

	*alpha = d*cosphi - q*sinphi;
	*beta  = d*sinphi + q*cosphi;
}

//PI controller with anti windup and output limitation
//error:			Control error (reference - actual value)
//error_sum:		Pointer to storage variable for the summed error
//anti_windup:		Pointer anti-windup flag: 0: no output saturation and anti-windup; 1: output saturation and anti-windup
//Kp:				Proportional gain of the controller
//Ki:				Integral gain of the controller
//output_limit:		Output limit for the controller (if in output saturation then anti-windup for integral part)
//Tsampling:		Sampling time of the PI controller in seconds
//return value:		PI controller output
float PI_Controller(const float error, float *const error_sum, int *const anti_windup, const float Kp, const float Ki, const float output_limit, const float TSampling)
{
	//Variables
	float out = 0.0;

	//Sum control deviation (only if the anti-windup flag is not set)
	if(*anti_windup == 0)
		*error_sum += error;

	//Controller output
	out = Kp*error + Ki*TSampling*(*error_sum);

	//Output limitation (if yes, anti-windup has to be activated)
	if(out > output_limit)
	{
		out = output_limit;
		*anti_windup = 1;
	}
	else if(out < -output_limit)
	{
		out = -output_limit;
		*anti_windup = 1;
	}
	else	//No output limitation => set back anti-windup flag
		*anti_windup = 0;

	return out;
}

//Get magnitude and angle of a 2D vector
void karth_polar(float *const magn, float *const angle, const float x, const float y)
{
	//Magnitude
	*magn = sqrt(x*x+y*y);

	//Angle
	*angle = atan2(y, x);
}

/* 1st order Low Pass Filter */
//input:			signal that you want to be filtered
//in_mem:			Pointer to storage variable
//out_mem:			Pointer to storage variable
//Fs:				sampling frequency of the low-pass filter
//Fc:				crossover frequency of the low-pass filter
//return value:		filtered signal
float LPF1(const float input, float *const in_mem, float *const out_mem, const float Fs, const float Fc)
{
	float P1;
	float K1;
	float K2;
	float output;

	P1 =M_PI*Fc/Fs;
	K1 = P1/(P1+1);
	K2 = (P1-1)/(P1+1);

	output = (*out_mem)*(-K2);
	output += K1*(input + *in_mem);
	*in_mem = input;
	*out_mem = output;

	return output;
}

/* 1st order Low Pass Filter */
//input:			signal that you want to be filtered
//in_mem:			Pointer to storage variable
//out_mem:			Pointer to storage variable
//Fs:				sampling frequency of the low-pass filter
//Fc:				crossover frequency of the low-pass filter
//return value:		filtered signal
float HPF1(const float input, float *const in_mem, float *const out_mem, const float Fs, const float Fc)
{
	float P1;
	float K1;
	float K2;
	float output;

	P1 =M_PI*Fc/Fs;
	K1 = P1/(P1+1);
	K2 = (P1-1)/(P1+1);

	output = (*out_mem)*(-K2);
	output += K1*(input + *in_mem);
	*in_mem = input;
	*out_mem = output;

	output = input-output;

	return output;
}

