/******************************************************************************
 *
 * control_toolbox.h
 *
 * Copyright (C) 2019 TUM EAL, All rights reserved.
 *
 *  Created on: 21.07.2019
 *      Author: Peter Stolze (PS) & Eyke Liegmann (EL)
 *
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
float sinewave(float amplitude, float frequency, float phase, long* sample, float int_freq);

//Blockwave generator
float blockwave(float amp_p, float amp_n, float frequency, float phase, long* sample, float int_freq);

//Periodic Ramp generator
float rampwave(float amp_p, float amp_n, float frequency, float phase, long* sample, float int_freq);

//Pulse generator
float pulse(float amplitude, float duty, float frequency, float phase, long* sample, float int_freq);

//Clarke transformation (abc to alpha beta)
//alpha:					Alpha "phase" after Clarke transformation
//beta:						Beta "phase" after Clarke transformation
//a:						Phase a before Clarke transformation
//b:						Phase b before Clarke transformation
//c:						Phase c before Clarke transformation
void Clarke(float* alpha, float* beta, float a, float b, float c);

//Clarke transformation (abc to alpha beta) for a balanced system (a + b + c = 0)
//alpha:					Alpha "phase" after Clarke transformation
//beta:						Beta "phase" after Clarke transformation
//a:						Phase a before Clarke transformation
//b:						Phase b before Clarke transformation
void Clarke_balanced(float* alpha, float* beta, float a, float b);

//Inverse Clarke transformation (alpha beta to abc)
//alpha:					Alpha "phase" before inverse Clarke transformation
//beta:						Beta "phase" before inverse Clarke transformation
//a:						Phase a after inverse Clarke transformation
//b:						Phase b after inverse Clarke transformation
//c:						Phase c after inverse Clarke transformation
void Clarke_inv(float alpha, float beta, float* a, float* b, float* c);

//Park transformation (alpha beta to dq)
//alpha:					Alpha "phase" before Park transformation
//beta:						Beta "phase" before Park transformation
//d:						d "phase" after Park transformation
//q:						q "phase" after Park transformation
//phi:						Flux angle for Park transformation (0...2*pi)
void Park(float alpha, float beta, float* d, float* q, float phi);

//Inverse Park transformation (dq to alpha beta)
//alpha:					Alpha "phase" before inverse Park transformation
//beta:						Beta "phase" before inverse Park transformation
//d:						d "phase" after inverse Park transformation
//q:						q "phase" after inverse Park transformation
//phi:						Flux angle for inverse Park transformation (0...2*pi)
void Park_inv(float* alpha, float* beta, float d, float q, float phi);

//PI controller with anti windup and output limitation
//error:			Control error (reference - actual value)
//error_sum:		Pointer to storage variable for the summed error
//anti_windup:		Pointer anti-windup flag: 0: no output saturation and anti-windup; 1: output saturation and anti-windup
//Kp:				Proportional gain of the controller
//Ki:				Integral gain of the controller
//output_limit:		Output limit for the controller (if in output saturation then anti-windup for integral part)
//return value:		PI controller output
float PI_Controller(float error, float* error_sum, int* anti_windup, float Kp, float Ki, float output_limit, float TSampling);

//Get magnitude and angle of a 2D vector
void karth_polar(float *magn, float *angle, float x, float y);

/* 1st order Low Pass Filter */
//input:			signal that you want to be filtered
//in_mem:			Pointer to storage variable
//out_mem:			Pointer to storage variable
//Fs:				sampling frequency of the low-pass filter
//Fc:				crossover frequency of the low-pass filter
//return value:		filtered signal
float LPF1(float input,float* in_mem,float* out_mem, float Fs,float Fc);

/* 1st order High Pass Filter */
//input:			signal that you want to be filtered
//in_mem:			Pointer to storage variable
//out_mem:			Pointer to storage variable
//Fs:				sampling frequency of the low-pass filter
//Fc:				crossover frequency of the low-pass filter
//return value:		filtered signal
float HPF1(float input,float* in_mem,float* out_mem, float Fs,float Fc);

