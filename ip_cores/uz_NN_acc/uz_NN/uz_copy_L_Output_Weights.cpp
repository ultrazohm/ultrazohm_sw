#include "uz_copy_L_Output_Weights.h"

void uz_copy_L_Output_Weights(float* padded_array, float* non_padded_array, const uint_fast32_t padded_array_columns, const uint_fast32_t padded_array_rows, const uint_fast32_t non_padded_array_columns) {
	//Order values in temp array properly in memory for uz_dense function
	//For 4 actions out of max 12 arrange array
	//From 1 2 3 4 5 6 7 8 9 10 11 12 -> 1 2 3 4 0 0 0 0 0 0 0 0 5 6 7 8 0....
#pragma HLS INLINE
	copy_L_Output_Weights:
	for (int i = 0; i < padded_array_rows * padded_array_columns; i++) {
	    #pragma HLS PIPELINE off
		uint_fast32_t row = i / padded_array_columns;
		uint_fast32_t col = i % padded_array_columns;
	    if (col < non_padded_array_columns) {
	    	padded_array[i] = non_padded_array[row * non_padded_array_columns + col];
	    } else {
	    	padded_array[i] = 0.0f;
		    }
		}
}
