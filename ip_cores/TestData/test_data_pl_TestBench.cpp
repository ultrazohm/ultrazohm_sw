/******************************************************************************
* UltraZohm - Test Data in PL for evaluation of Data Logging -  TESTBENCH
*
* Designer: Simon Manuel Lukas
* Organization: TUM HLU (Eyke Liegmann)
* Date: 05/2022
******************************************************************************/

#include <stdio.h>
//#include<string.h> //
#include <stdlib.h>
#include <stdbool.h>
#include "test_data_pl.h"

int main() {

	// INPUTS
	float sample_frequency_Hz_TB = 1e4f;
	float amplitude_TB = 2.0f;
	float frequency_TB = 5e2f;
	int period_TB = 16;

	// OUTPUTS
	int counter_TB = 0;
	float sine_float_TB = 0.0f;
	float square_float_TB = 0.0f;
	float triangle_float_TB = 0.0f;
	test_data_apFixed sine_apFixed_TB = 0.0;
	test_data_apFixed square_apFixed_TB = 0.0f;
	test_data_apFixed triangle_apFixed_TB = 0.0;

	int retval = 0;
	int i;

	printf("sample_frequency: %f\n", sample_frequency_Hz_TB);
	printf("amplitude: %f\n", amplitude_TB);
	printf("frequency: %f\n", frequency_TB);
	printf("period: %d\n\n", period_TB);

	//FILE *result;
	//result = fopen("result.dat");
	std::ofstream result("results.dat");
	//std::ofstream result;
	//result.open("result.txt");
	result << std::right << std::fixed << std::setbase(10) << std::setprecision(12);

	result << std::setw(3)	<< "i";
	result << std::setw(15) << "counter";
	result << std::setw(30) << "sine_float";
	result << std::setw(30) << "sine_apFixed";
	result << std::setw(30) << "square_float";
	result << std::setw(29) << "square_apFixed";
	result << std::setw(30) << "triangle_float";
	result << std::setw(29) << "triangle_apFixed";
	result << std::endl << std::endl;

	printf("Calculating counter, sine, square and triangle signals:	 %d iterations\n", NUM_TRANS);
	printf("Processing ...\n\n");

	for (i = 0; i < NUM_TRANS; i++)
	{
		test_data_signals(sample_frequency_Hz_TB, amplitude_TB, frequency_TB, period_TB, &counter_TB, &sine_float_TB, &square_float_TB, &triangle_float_TB, &sine_apFixed_TB, &square_apFixed_TB, &triangle_apFixed_TB);

		float sine_apFixed_to_float_TB = (float)(sine_apFixed_TB) ;

		result << std::setw(3)	<< i;
		result << std::setw(15) << counter_TB;
		result << std::setw(30) << sine_float_TB;
		result << std::setw(30) << sine_apFixed_to_float_TB;
		result << std::setw(30) << square_float_TB;
		result << std::setw(15) << square_apFixed_TB;
		result << std::setw(30) << triangle_float_TB;
		result << std::setw(15) << triangle_apFixed_TB;
		result << std::endl;
	}
	result.close();

	// Compare the "results.dat" file with the "golden.results.dat" file
	// retval = system("diff --brief -w results.dat golden_results.dat"); 										// unix
	//retval = system("fc /c results.dat C:\\UltraZohm\\ultrazohm_sw\\ip_cores\\TestData\\golden.results.dat");	// windows

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
