/******************************************************************************
* UltraZohm - Test Data in PL for evaluation of Data Logging
*
* Designer: Simon Manuel Lukas
* Organization: TUM HLU (Eyke Liegmann)
* Date: 05/2022
******************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include <cmath>
#include "hls_math.h"
#define _USE_MATH_DEFINES
//#include <math.h>
#include <ap_fixed.h>
#include "test_data_pl.h"


// INITIALIZATIONS
static float sample_frequency_Hz_float = 1e4f;										//change value
static test_data_apFixed sample_frequency_Hz_apFixed = (test_data_apFixed)(1e4);	//change value


// FUNCTIONS FOR DATA GENERATION EQUIVALENT TO SIGNAL GENERATOR

void testData_counter(int counter_out) {
	counter_out += 1;
}

void testData_get_sine_signal_float(float *testData_amplitude, float *testData_frequency, int test_data_time, float *sine_out){
	float testData_phase_f = (2.0f * (float)(M_PI) * *testData_frequency / sample_frequency_Hz_float);
	float testData_sine_input_f = testData_phase_f * (float)(test_data_time);
	// testData_sine_input_f = fmodf(testData_phase_f * (float)(*test_data_time), 2.0f * (float)(M_PI)); // phase*time in [0,2pi] period
	*sine_out = *testData_amplitude * sinf(testData_sine_input_f);
}

void testData_get_sine_signal_apFixed(test_data_apFixed testData_amplitude, test_data_apFixed testData_frequency, int test_data_time, test_data_apFixed *sine_out) {
	test_data_apFixed testData_phase_a = ((test_data_apFixed)(2.0 * M_PI) * (testData_frequency / sample_frequency_Hz_apFixed));
	test_data_apFixed testData_sine_input_a = testData_phase_a * test_data_time;
	//testData_sine_input_a = (testData_phase_a * (test_data_apFixed)(*test_data_time)) % ((test_data_apFixed)(2.0) * (test_data_apFixed)(M_PI));
	*sine_out = testData_amplitude * (test_data_apFixed)(hls::sin(testData_sine_input_a));
}

void testData_get_square_signal_float(float *testData_amplitude, int *testData_period, int test_data_time, float *square_out){
	static bool square_high_low = 0;
	if( (square_high_low == 0) && (test_data_time % (*testData_period/2) == 0) ) {
		*square_out = *testData_amplitude;
		square_high_low = 1;
	}
	else if ( (square_high_low == 1) && (test_data_time % (*testData_period/2) == 0) ) {
		*square_out = 0.0f;
		square_high_low = 0;
	}
}

void testData_get_square_signal_apFixed(test_data_apFixed testData_amplitude, int *testData_period, int test_data_time, test_data_apFixed *square_out){
	static bool square_high_low = 0;
	if( (square_high_low == 0) && (test_data_time % (*testData_period/2) == 0) ) {
		*square_out = testData_amplitude;
		square_high_low = 1;
	}
	else if ( (square_high_low == 1) && (test_data_time % (*testData_period/2) == 0) ) {
		*square_out = 0.0;
		square_high_low = 0;
	}
}

void testData_get_triangle_signal_float(float *testData_amplitude, int *testData_period, int test_data_time, float *triangle_out) {
	float half_period = *testData_period/2;
	int time_mod_period = test_data_time%(*testData_period);
	if(test_data_time%(*testData_period) < *testData_period/2) {
		*triangle_out = *testData_amplitude * (float)(time_mod_period/half_period);
	}
	else if ( (test_data_time%(*testData_period) >= *testData_period/2) && (test_data_time%(*testData_period) < *testData_period) ) {
		*triangle_out = *testData_amplitude * (2 - (float)(time_mod_period/half_period)) ;
	}
}

void testData_get_triangle_signal_apFixed(test_data_apFixed testData_amplitude, int *testData_period, int test_data_time, test_data_apFixed *triangle_out) {
	test_data_apFixed half_period = *testData_period/2;
	int time_mod_period = test_data_time%(*testData_period);
	if(test_data_time%(*testData_period) < *testData_period/2) {
		*triangle_out = testData_amplitude * ((test_data_apFixed)(time_mod_period)/half_period);
	}
	else if ( (test_data_time%(*testData_period) >= *testData_period/2) && (test_data_time%(*testData_period) < *testData_period) ) {
		*triangle_out = testData_amplitude * ((test_data_apFixed)(2.0) - ((test_data_apFixed)(time_mod_period)/half_period));
	}
}


// GENERALIZED FUNCTIONS FOR TEST DATA

void test_data_signals(float sample_frequency_Hz, float amplitude, float frequency, int period,
								int *counter_int, float *sine_float, float *square_float, float *triangle_float, test_data_apFixed *sine_apFixed, test_data_apFixed *square_apFixed, test_data_apFixed *triangle_apFixed) {

	//#pragma HLS interface s_axilite port=data_in bundle=data
	//#pragma HLS interface s_axilite port=data_out bundle=data
	//#pragma HLS DISAGGREGATE variable=data_in
	//#pragma HLS DISAGGREGATE variable=data_out

	#pragma HLS INTERFACE s_axilite port=return bundle=data_in
	#pragma HLS interface s_axilite port=sample_frequency_Hz bundle=data_in //-name sample_frequency
	#pragma HLS interface s_axilite port=amplitude bundle=data_in //-name amplitude
	#pragma HLS interface s_axilite port=frequency bundle=data_in //-name frequency
	#pragma HLS interface s_axilite port=period bundle=data_in //-name period

	//#pragma HLS interface register port=counter_int
	#pragma HLS interface ap_none register port=sine_float
	#pragma HLS interface ap_none register port=square_float
	#pragma HLS interface ap_none register port=triangle_float
	#pragma HLS interface ap_none register port=sine_apFixed
	#pragma HLS interface ap_none register port=square_apFixed
	#pragma HLS interface ap_none register port=triangle_apFixed

	#pragma HLS PIPELINE

	static int counter_internal = 0;

	test_data_apFixed amplitude_apFixed = (test_data_apFixed)amplitude;
	test_data_apFixed frequency_apFixed = (test_data_apFixed)frequency;

	testData_get_sine_signal_float(&amplitude, &frequency, counter_internal, sine_float);
	testData_get_square_signal_float(&amplitude, &period, counter_internal, square_float);
	testData_get_triangle_signal_float(&amplitude, &period, counter_internal, triangle_float);
	testData_get_sine_signal_apFixed(amplitude_apFixed, frequency_apFixed, counter_internal, sine_apFixed);
	testData_get_square_signal_apFixed(amplitude_apFixed, &period, counter_internal, square_apFixed);
	testData_get_triangle_signal_apFixed(amplitude_apFixed, &period, counter_internal, triangle_apFixed);

	*counter_int = counter_internal++;
	if(counter_internal == 100){
		counter_internal = 0;
	}
}
