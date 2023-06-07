#ifndef _TEST_DATA_PL_H_
#define _TEST_DATA_PL_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ap_fixed.h>

#define ap_fixed_wordlength 32
#define ap_fixed_integerbits 20
#define NUM_DATA_OUT 7
#define NUM_TRANS 50

typedef ap_fixed<ap_fixed_wordlength, ap_fixed_integerbits> dummy_data_apFixed;

void dummy_data_generator(float amplitude, float frequency, int period,
								int *counter_int,
								float *sine_float, float *square_float, float *triangle_float,
								dummy_data_apFixed *sine_apFixed, dummy_data_apFixed *square_apFixed, dummy_data_apFixed *triangle_apFixed);

#endif
