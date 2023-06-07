/******************************************************************************
* UltraZohm - Data Aggregation in PL
* transmission of internal system data from FPGA to BRAM
*
* Designer: Simon Manuel Lukas
* Organization: TUM HLU (Eyke Aufderheide)
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

//OCM:
//void uz_log_data(uint32_t *value_1, uint32_t *value_2, uint32_t *value_3,  uint32_t *value_4, uint32_t *value_5, uint32_t *value_6, uint32_t *value_7, uint32_t *control_1, uint32_t *control_2, float *dlog_1) {
//BRAM:
void data_aggregator(uint32_t *value1,  uint32_t *value2,  uint32_t *value3,  uint32_t *value4, uint32_t *value5, uint32_t *value6,
				 uint32_t *value7,  uint32_t *value8,  uint32_t *value9, uint32_t *value10, uint32_t *value11, uint32_t *value12,
				 uint32_t *value13, uint32_t *value14, uint32_t *value15, uint32_t *value16,
				 uint32_t *control1, uint32_t *control2, float buff[NUM_DATA_IN]) {

	//#pragma HLS INTERFACE m_axi port=return bundle=data_out
	//#pragma HLS INTERFACE m_axi port=logging_output bundle=data_out

	#pragma HLS INTERFACE s_axilite port=return bundle=control_in
	#pragma HLS INTERFACE s_axilite port=control1 bundle=control_in
	#pragma HLS INTERFACE s_axilite port=control2 bundle=control_in

	#pragma HLS INTERFACE ap_vld register port=value1  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value2  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value3  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value4  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value5  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value6  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value7  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value8  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value9  bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value10 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value11 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value12 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value13 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value14 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value15 bundle=data_in
	#pragma HLS INTERFACE ap_vld register port=value16 bundle=data_in

	//OCM:
	//#pragma HLS INTERFACE m_axi port=dlog_1 bundle=logging_output depth=7 offset=slave//While depth is usually an option, it is required for m_axi interfaces. offset=slave
	//BRAM:
	#pragma HLS INTERFACE bram port=buff

	//config_interface -register_io(scalar_in)

	// memcpy a float buffer -> works
	//float buff[7];


	uint32_t input_buff[NUM_DATA_IN] = {*value1, *value2, *value3,   *value4,  *value5,  *value6,  *value7, *value8,
										*value9, *value10,  *value11, *value12, *value13, *value14, *value15, *value16};

	int temp_value_int=0;

	for(int i=0; i<NUM_DATA_IN; i++){ //32
		//uint32_t actual_c1_bit = ((*control_1 << 31-i)>>31-i)==1;
		//uint32_t actual_c2_bit = ((*control_2 << 31-i)>>31-i)==1;
		//uint32_t c1_xor_c1_bit = actual_c1_bit ^ actual_c2_bit;

		int actual_c1_bit = 0;
		int actual_c2_bit = 0;
		if((*control1 & (CONTROL_MASK<<i)) != 0){
			actual_c1_bit = FIRST_BIT_SET;
		}
		if((*control2 & (CONTROL_MASK<<i)) != 0){
			actual_c2_bit = SECOND_BIT_SET;
		}
		ap_uint<2> type_control = actual_c1_bit | actual_c2_bit;

		switch(type_control){
		case 0: buff[i] = (float)input_buff[i]; 		// unsigned int (00)
				break;
		case 1: //temp_value_int = input_buff[i]; 	// signed int (01)
				//buff[i] = temp_value_int;
			buff[i] = (int)input_buff[i];
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
