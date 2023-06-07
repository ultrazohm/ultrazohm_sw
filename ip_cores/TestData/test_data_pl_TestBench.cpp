/************************************************************************************
* UltraZohm - Dummy Data Generation in PL for Evaluation of Data Logging -  TESTBENCH
*
* Designer: Simon Manuel Lukas
* Organization: TUM HLU (Eyke Aufderheide)
* Date: 05/2022
************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_data_pl.h"

int main() {

	// Initialization of parameters
	// Inputs
	float	amplitude_TB = 2.0f;
	float 	frequency_TB = 5e-2f;
	int 	period_TB 	 = 16;
	// Outputs
	int 	counter_TB = 0;
	float 	sine_float_TB = 0.0f;
	float 	square_float_TB = 0.0f;
	float 	triangle_float_TB = 0.0f;
	dummy_data_apFixed sine_apFixed_TB 	= 0.0;
	dummy_data_apFixed square_apFixed_TB = 0.0f;
	dummy_data_apFixed triangle_apFixed_TB = 0.0;

	// Misc
	int i;
	int retval = 0;
	float ref_tmp, diff;
	FILE *reference;

	// Data storage
	static float cmp[NUM_TRANS*NUM_DATA_OUT];
	static float dummy_data[NUM_TRANS*NUM_DATA_OUT];

	printf("amplitude: %f\n", amplitude_TB);
	printf("frequency: %f\n", frequency_TB);
	printf("period: %d\n\n", period_TB);

	// Load input data from reference file golden.results.dat
	reference = fopen("golden.results.dat", "r");
	for (i=0; i<NUM_TRANS*NUM_DATA_OUT; i++){
		fscanf(reference, "%f", &ref_tmp);
		cmp[i]=ref_tmp;
	}

	//FILE *result;
	//result = fopen("result.dat");
	std::ofstream result("results.dat");
	//std::ofstream result;
	//result.open("result.txt");
	result << std::right << std::fixed << std::setbase(10) << std::setprecision(12);

	result << "counter";
	result << "\t"	 << std::setw(15) << "sine_float";
	result << "\t\t" << std::setw(15) << "sine_apFixed";
	result << "\t\t" << std::setw(15) << "square_float";
	result << "\t\t" << std::setw(15) << "square_apFixed";
	result << "\t\t" << std::setw(15) << "triangle_float";
	result << "\t\t" << std::setw(16) << "triangle_apFixed";
	result << std::endl << std::endl;

	printf("Calculating counter, sine, square and triangle signals:	 %d iterations\n", NUM_TRANS);
	printf("Processing ...\n\n");

	// Execute the function multiple times and store outputs in dummy_data[] array
	for (i=0; i<NUM_TRANS; i++)
	{
		dummy_data_generator(amplitude_TB, frequency_TB, period_TB, &counter_TB, &sine_float_TB, &square_float_TB, &triangle_float_TB, &sine_apFixed_TB, &square_apFixed_TB, &triangle_apFixed_TB);

		float sine_apFixed_to_float_TB = (float)(sine_apFixed_TB);

		result << std::setw(2) << counter_TB;
		result << "\t\t" 		<< std::setw(15) << sine_float_TB;
		result << "\t\t" 		<< std::setw(15) << sine_apFixed_to_float_TB;
		result << "\t\t"		<< std::setw(15) << square_float_TB;
		result << "\t\t\t\t\t"  << std::setw(2)  << square_apFixed_TB;
		result << "\t\t" 		<< std::setw(15) << triangle_float_TB;
		result << "\t\t\t\t\t" 	<< std::setw(1)  << triangle_apFixed_TB;
		result << std::endl;

		dummy_data[NUM_DATA_OUT*i]		= counter_TB;
		dummy_data[NUM_DATA_OUT*i+1] 	= sine_float_TB;
		dummy_data[NUM_DATA_OUT*i+2] 	= sine_apFixed_to_float_TB;
		dummy_data[NUM_DATA_OUT*i+3] 	= square_float_TB;
		dummy_data[NUM_DATA_OUT*i+4] 	= square_apFixed_TB;
		dummy_data[NUM_DATA_OUT*i+5] 	= triangle_float_TB;
		dummy_data[NUM_DATA_OUT*i+6] 	= triangle_apFixed_TB;
	}
	result.close();

	// Check outputs against expected cmp values with an accuracy of 1/1000
	for (i=0; i<NUM_TRANS*NUM_DATA_OUT; i++){
		diff = cmp[i]-dummy_data[i];
		if(diff < -0.001f || diff > 0.001f){
			int column = i%NUM_DATA_OUT + 1; // number of column in generated file
			printf("Data incorrect! Mismatch at iteration %i \t in column %i \n", i, column);
			retval = 1;
		}
	}

	// Compare the "results.dat" file with the "golden.results.dat" file
	// retval = system("diff --brief -w results.dat golden_results.dat"); 										// unix
	// retval = system("fc /c results.dat C:\\UltraZohm\\ultrazohm_sw\\ip_cores\\TestData\\golden.results.dat");	// windows

	// Print Results
	if (retval == 0) {
		printf("****************\n");
		printf("Results are good \n");
		printf("****************\n\n");
	} else {
		printf("****************\n");
		printf("Mismatch: retval = %d \n", retval);
		printf("****************\n\n");
	}

	// Return 0 if outputs are correct
	return retval;

}
