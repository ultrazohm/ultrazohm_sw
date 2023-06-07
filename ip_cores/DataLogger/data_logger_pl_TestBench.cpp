/******************************************************************************
* UltraZohm - Test Data in PL for evaluation of Data Logging -  TESTBENCH
*
* Designer: Simon Manuel Lukas
* Organization: TUM HLU (Eyke Aufderheide)
* Date: 05/2022
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_logger_pl.h"

int main() {

	// Initialization of parameters
	// Inputs
	uint32_t control1_TB = 0b00000000000000000000000000000000;
	uint32_t control2_TB = 0b00000000000000000000000000000000;
	// Outputs
	float buff_TB[NUM_DATA_IN] =  {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
								   0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

	// Misc
	int retval = 0;
	int i;
	float diff;

	printf("Starting aggregation process ...\n");

	// Set control parameters for correct data type conversion
	control1_TB = 0b00000000000000000011110000111100;
	control2_TB = 0b00000000000000000011111111000000;

	// CASE 1: conversion of multiple input parameters
	/*
	uint32_t test_uint_FE  = 4294967294; // 0xFFFFFFFE
	uint32_t test_uint_F0  = 4026531840; // 0xF0000000
	int test_int_2p  = +2;				 // 0x00000002
	int test_int_2n  = -2; 				 // 0xFFFFFFFE
	int test_int_10p = +10;				 // 0x0000000A
	int test_int_10n = -10; 			 // 0xFFFFFFF6
	float test_float_2p  = +2.2222f;	 // 0x400e3886
	float test_float_2n  = -2.2222f; 	 // 0xc00e3886
	float test_float_10p = +10.000f; 	 // 0x41200000
	float test_float_10n = -10.000f; 	 // 0xC1200000
	din_apf_t test_fixed_2p  = +2.2222f; // 0x0000238E
	din_apf_t test_fixed_2n  = -2.2222f; // 0xFFFFDC72
	din_apf_t test_fixed_10p = +10.000f; // 0x0000A000
	din_apf_t test_fixed_10n = -10.000f; // 0xFFFF6000

	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("  CONVERT MULTI-TYPE INPUTS -> UINT32 -> FLOAT: \n");

	uz_log_data(&(*(unsigned int*)&test_uint_FE), &(*(unsigned int*)&test_uint_F0),
				&(*(unsigned int*)&test_int_2p), &(*(unsigned int*)&test_int_2n), &(*(unsigned int*)&test_int_10p), &(*(unsigned int*)&test_int_10n),
				&(*(unsigned int*)&test_float_2p), &(*(unsigned int*)&test_float_2n), &(*(unsigned int*)&test_float_10p), &(*(unsigned int*)&test_float_10n),
				&(*(unsigned int*)&test_fixed_2p), &(*(unsigned int*)&test_fixed_2n), &(*(unsigned int*)&test_fixed_10p), &(*(unsigned int*)&test_fixed_10n),
				&control_1_TB, &control_2_TB, buff_TB);

	for(int i=0; i<NUM_DATA_IN; i++){
		printf("\n 32 bit float hex: %#X  value: %f", *(unsigned int*)&buff_TB[i], buff_TB[i]);
	}
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	*/


	// CASE 2: conversion of uint32_t input parameters

	uint32_t test_in_u_FE  = 0xFFFFFFFE; // 4294967294
	uint32_t test_in_u_F0  = 0xF0000000; // 4026531840
	uint32_t test_in_s_2p  = 0x00000002; // +2
	uint32_t test_in_s_2n  = 0xFFFFFFFE; // -2
	uint32_t test_in_s_10p = 0x0000000A; // +10
	uint32_t test_in_s_10n = 0xFFFFFFF6; // -10
	uint32_t test_in_f_2p  = 0x400e3886; // +2.2222f
	uint32_t test_in_f_2n  = 0xc00e3886; // -2.2222f
	uint32_t test_in_f_10p = 0x41200000; // +10.000f
	uint32_t test_in_f_10n = 0xC1200000; // -10.000f
	uint32_t test_in_a_2p  = 0x0000238E; // +2.2222f
	uint32_t test_in_a_2n  = 0xFFFFDC72; // -2.2222f
	uint32_t test_in_a_10p = 0x0000A000; // +10.000f
	uint32_t test_in_a_10n = 0xFFFF6000; // -10.000f
	uint32_t test_in_u_00  = 0x00000000; // 0

	// golden reference: comparative values
	float reference_TB[NUM_DATA_IN] = {4294967294.0, 4026531840.0, 2.0, -2.0, 10.0, -10.0, 2.2222, -2.2222, 10.0, -10.0, 2.2222, -2.2222, 10.0, -10.0, 0.0, 0.0};

	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("     CONVERT UINT32 INPUTS TO FLOAT TYPE: \n");

	data_aggregator(&test_in_u_FE, &test_in_u_F0,
				&test_in_s_2p, &test_in_s_2n, &test_in_s_10p, &test_in_s_10n,
				&test_in_f_2p, &test_in_f_2n, &test_in_f_10p, &test_in_f_10n,
				&test_in_a_2p, &test_in_a_2n, &test_in_a_10p, &test_in_a_10n,
				&test_in_u_00, &test_in_u_00,
				&control1_TB, &control2_TB, buff_TB);

	for(i=0; i<NUM_DATA_IN; i++){
		printf("\n 32 bit float hex: %#X  value: %f", *(unsigned int*)&buff_TB[i], buff_TB[i]);
		diff = buff_TB[i] - reference_TB[i];
		if(diff < -0.0001f || diff > 0.0001f){  // accuracy margin because of apFixed type
			printf("\n Mismatch!");
			retval = 1;
		}
	}
	printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

	/*
	//case 1: int representation
	control_1_TB = 0b00000000000000000000000000101111;
	control_2_TB = 0b00000000000000000000000000101100;
	counter_TB = 0xFFFFFFFE; // int -2
	sine_float_TB = 2.2222f;
	printf("UINT32 TO INT CONVERSION: \n");
	printf("counter unsigned int: %X bzw. %u \n", counter_TB, counter_TB);
	int temp_value_int_TB = counter_TB;
	temp_value_float = (temp_value_int_TB);
	printf("counter signed int: %X bzw. %d \n", temp_value_int_TB, temp_value_int_TB);
	printf("counter test float: %X bzw. %f \n\n", *(unsigned int*)&temp_value_float, temp_value_float);
	control_1_TB = 0b00000000000000000000000000101100;
	control_2_TB = 0b00000000000000000000000000101111;
	counter_TB = 0xC1200000; //float -10
	sine_float_TB = 2.2222f;
	printf("UINT32 TO FLOAT CONVERSION: \n");
	printf("counter unsigned int: %X bzw. %u \n", counter_TB, counter_TB);
	float temp_value_float_zw = *((float *) &counter_TB);
	temp_value_float = (float)temp_value_float_zw;
	printf("counter float Zwischenergebnis: %X bzw. %f \n", *(unsigned int*)&temp_value_float_zw, temp_value_float_zw);
	printf("counter final float: %X bzw. %f \n", *(unsigned int*)&temp_value_float, temp_value_float);


	//for (i = 0; i < NUM_DATA_IN; i++) //NUM_TRANS
	//{
		control_1_TB = 0b00000000000000000000000001000111;
		control_2_TB = 0b00000000000000000000000001001000;

		//counter_TB += 1;
		counter_TB = 0xFFFFFFFE;
		//sine_float_TB = sinf((float)(counter_TB)*2.0f*M_PI);
		sine_float_TB = 0x000063D4; // 25556 (int);
		sine_apFixed_TB = 3.3333f;
		square_float_TB = 0x408E353F; //4.444f
		square_apFixed_TB = 0xF0000000; // 4026531840 (uint, else negativ)
		triangle_float_TB = 6.666f;
		//triangle_apFixed_TB = 0x40F8DD2F; //7.777f
		//triangle_apFixed_TB = 0x00004000; // uint: 16384, apfixed: 4, float:0x40800000
		triangle_apFixed_TB = 0x00001800; // 1.5
		// call top function
		uz_log_data(&counter_TB, &sine_float_TB, &sine_apFixed_TB, &square_float_TB, &square_apFixed_TB, &triangle_float_TB, &triangle_apFixed_TB,
					&counter_TB, &sine_float_TB, &sine_apFixed_TB, &square_float_TB, &square_apFixed_TB, &triangle_float_TB, &triangle_apFixed_TB,
					&control_1_TB, &control_2_TB, buff_TB);

	//} */

	// Compare the results file with the golden results
	//retval = system("diff --brief -w results.dat golden_results.dat");

	// Print Results
	printf("\n");
	if (retval == 0) {
		printf("****************\n");
		printf("Results are good \n");
		printf("****************\n\n");
	}
	else {
		printf("****************\n");
		printf("Mismatch: retval = %d \n", retval);
		printf("****************\n\n");
	}
	// Return 0 if outputs are correct
	return retval;

}
