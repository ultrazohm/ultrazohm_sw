/******************************************************************************
* UltraZohm - Test Data in PL for evaluation of Data Logging -  TESTBENCH
*
* Designer: Simon Manuel Lukas
* Organization: TUM HLU (Eyke Liegmann)
* Date: 05/2022
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "data_logger_pl.h"

int main() {

	// INPUTS
	//float counter_TB = 0;
	/*float sine_float_TB = 0.0f;
	float square_float_TB = 0.0f;
	float triangle_float_TB = 0.0f;
	din_apf_t sine_apFixed_TB = 0.0;
	din_apf_t square_apFixed_TB = 0.0;
	din_apf_t triangle_apFixed_TB = 0.0;*/

	// changed from all float to all uint32_t
	uint32_t counter_TB = 0;
	uint32_t sine_float_TB = 0.0f;
	uint32_t square_float_TB = 0.0f;
	uint32_t triangle_float_TB = 0.0f;
	uint32_t sine_apFixed_TB = 0.0f;
	uint32_t square_apFixed_TB = 0.0f;
	uint32_t triangle_apFixed_TB = 0.0f;
	uint32_t control_1_TB = 0b00000000000000000000000000000000;
	uint32_t control_2_TB = 0b00000000000000000000000000000000;

	// OUTPUTS
	//float dlog_1_TB =  0.0f;
	float buff_TB[7] =  {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};


	int retval = 0;
	int i;
	float temp_value_float;

	printf("Starting Logging process ...\n");

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


	//for (i = 0; i < 7; i++) //NUM_TRANS
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
		uz_log_data(&counter_TB, &sine_float_TB, &sine_apFixed_TB, &square_float_TB, &square_apFixed_TB, &triangle_float_TB, &triangle_apFixed_TB, &control_1_TB, &control_2_TB, buff_TB);

	//}

	// Compare the results file with the golden results
	//retval = system("diff --brief -w results.dat golden_results.dat");

	// Print Results
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
