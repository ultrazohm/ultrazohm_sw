#ifndef _TEST_DATA_PL_H_
#define _TEST_DATA_PL_H_

#include <stdio.h>
//#include <stdint.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ap_fixed.h>

#define ap_fixed_wordlength 32 
#define ap_fixed_integerbits 20
#define NUM_TRANS 50

typedef struct test_data_pl_t test_data_pl_t;
typedef ap_fixed<ap_fixed_wordlength, ap_fixed_integerbits> test_data_apFixed;

void test_data_signals(float sample_frequency_Hz, float amplitude, float frequency, int period,
								int *counter_int, float *sine_float, float *square_float, float *triangle_float, test_data_apFixed *sine_apFixed, test_data_apFixed *square_apFixed, test_data_apFixed *triangle_apFixed);

#endif
