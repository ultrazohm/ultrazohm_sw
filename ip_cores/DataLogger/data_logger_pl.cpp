/******************************************************************************
* UltraZohm - Data Logging in PL (transmission of internal system data from FPGA to PC)
*
* Designer: Simon Manuel Lukas
* Organization: TUM HLU (Eyke Liegmann)
* Date: 07/2022
******************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cmath> // used in Visual Studio
//#include "hls_math.h" // used in Vitis HLS
#define _USE_MATH_DEFINES
//#include <math.h>
#include <ap_fixed.h>
#include "data_logger_pl.h"

#define CONTROL_MASK 0x00000001
#define FIRST_BIT_SET 0x00000001
#define SECOND_BIT_SET 0x00000002

// Top Function

//void uz_log_data(int *value_1, float *value_2, din_apf_t *value_3,  float *value_4, din_apf_t *value_5, float *value_6, din_apf_t *value_7, float *dlog_1) {
//OCM:
//void uz_log_data(uint32_t *value_1, uint32_t *value_2, uint32_t *value_3,  uint32_t *value_4, uint32_t *value_5, uint32_t *value_6, uint32_t *value_7, uint32_t *control_1, uint32_t *control_2, float *dlog_1) {
//BRAM:
void uz_log_data(uint32_t *value_1, uint32_t *value_2, uint32_t *value_3,  uint32_t *value_4, uint32_t *value_5, uint32_t *value_6, uint32_t *value_7, uint32_t *control_1, uint32_t *control_2, float buff[7]) {

	//#pragma HLS INTERFACE m_axi port=return bundle=data_out
	//#pragma HLS INTERFACE m_axi port=logging_output bundle=data_out

	#pragma HLS INTERFACE s_axilite port=return bundle=control_in
	#pragma HLS INTERFACE s_axilite port=control_1 bundle=control_in
	#pragma HLS INTERFACE s_axilite port=control_2 bundle=control_in

	#pragma HLS INTERFACE ap_vld register port=value_1 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value_2 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value_3 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value_4 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value_5 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value_6 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value_7 bundle=data_in

	//OCM:
	//#pragma HLS INTERFACE m_axi port=dlog_1 bundle=logging_output depth=7 offset=slave//While depth is usually an option, it is required for m_axi interfaces. offset=slave
	//BRAM:
	#pragma HLS INTERFACE bram port=buff

	//config_interface -register_io(scalar_in)

	// memcpy a float buffer -> works
	//float buff[7];


	uint32_t input_buff[7] = {*value_1, *value_2, *value_3,  *value_4, *value_5, *value_6, *value_7};

	int temp_value_int=0;

	for(int i=0; i<7; i++){ //32
		//uint32_t actual_c1_bit = ((*control_1 << 31-i)>>31-i)==1;
		//uint32_t actual_c2_bit = ((*control_2 << 31-i)>>31-i)==1;
		//uint32_t c1_xor_c1_bit = actual_c1_bit ^ actual_c2_bit;

		int actual_c1_bit = 0;
		int actual_c2_bit = 0;
		if((*control_1 & (CONTROL_MASK<<i)) != 0){
			actual_c1_bit = FIRST_BIT_SET;
		}
		if((*control_2 & (CONTROL_MASK<<i)) != 0){
			actual_c2_bit = SECOND_BIT_SET;
		}
		ap_uint<2> type_control = actual_c1_bit | actual_c2_bit;

		switch(type_control){
		case 0: buff[i] = (float)(input_buff[i]); 		// unsigned int (00)
				break;
		case 1: temp_value_int = input_buff[i]; 	// signed int (01)
				buff[i] = temp_value_int;
				break;
		case 2: buff[i] = *((float *) &input_buff[i]); 	// float (10)
				break;
		case 3: temp_value_int = input_buff[i]; 	// apfixed (11)
				buff[i] = temp_value_int*pow(2, (ap_fixed_integerbits-ap_fixed_wordlength));
				break;
		default: printf("error: no data type conversion completed") ;
				break;
		}

		/* if(c1_xor_c1_bit==1){
			if(actual_c1_bit==1){ 								// if c1='1', c2='0' : INT
				//int temp_value_int = static_cast<int>(*input_buff[i]);
				//int temp_value_int = (int)(*value_1);
				int temp_value_int = *input_buff[i];
				buff[i] = temp_value_int; // same as (float)(temp_value_int)

			} else{ 											// if c1='0', c2='1' : FLOAT
				//float temp_value_float = static_cast<float>(*input_buff[i]);
				float temp_value_float = *((float *) &input_buff[i]);
				buff[i] = temp_value_float;
			}
		} */
	//	else{ 													// if c1='1', c2='1' : UINT_32
	//		if(actual_c1_bit==1){
	//				buff[i] = static_cast<float>(*input_buff[i]);
	//		} else{												// if c1='0', c2='0' : ?
	//			buff[i] = static_cast<float>(*input_buff[i]); //change!
	//		}
	//	}
	}



/*	if((*control_1 & BUF0_VAL1_MASK)==BUF0_VAL1_MASK){ //if first bit is '1'
		buff[0] = (int)*value_1;
		}
	else{
		buff[0] = *value_1;
		}

	if((*control_1 & BUF1_VAL2_MASK)==BUF1_VAL2_MASK){ //if second bit is '1'
		buff[1] = (int)*value_2;
		}
	else{
		buff[1] = *value_2;
		}

	if((*control_1 & BUF2_VAL3_MASK)==BUF2_VAL3_MASK){ //if third bit is '1'
		buff[2] = (int)*value_3;
		}
	else{
		buff[2] = *value_3;
		}

	if((*control_1 & BUF3_VAL4_MASK)==BUF3_VAL4_MASK){ //if fourth bit is '1'
		buff[3] = (int)*value_4;
		}
	else{
		buff[3] = *value_4;
		}

	if((*control_1 & BUF4_VAL5_MASK)==BUF4_VAL5_MASK){ //if fifth bit is '1'
		buff[4] = (int)*value_5;
		}
	else{
		buff[4] = *value_5;
		}

	if((*control_1 & BUF5_VAL6_MASK)==BUF5_VAL6_MASK){ //if sixth bit is '1'
		buff[5] = (int)*value_6;
		}
	else{
		buff[5] = *value_6;
		}

	if((*control_1 & BUF6_VAL7_MASK)==BUF6_VAL7_MASK){ //if seventh bit is '1'
		buff[6] = (int)*value_7;
		}
	else{
			buff[6] = *value_7;
		}
	*/

	// auf OCM (DDR) schreiben
	// burst memory write process (loop;memcpy))
	//memcpy(dlog_1,  (const float*) buff, 7*sizeof(float));


	//AT FIRST:
	// *dlog_1 = *value_1;
	// *dlog_2 = *value_2;
	// *dlog_3 = *value_3;
	//SECOND:
	//  buff[0] = (float*)(&value_1);

	//buff[i] = *(float*)(&temp_value_int);

}
