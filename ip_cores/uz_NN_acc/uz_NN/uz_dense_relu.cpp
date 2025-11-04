#include "uz_dense_relu.h"
#include "uz_MMult_MaxSize.h"

//Input 1xM, Weights MxM, Output 1xM, Bias 1xM
void uz_dense_relu(const float *input, const float *weights, const float *bias, float *output,
                const uint_fast32_t input_columns, const uint_fast32_t output_columns) {
#pragma HLS INLINE
    dense_relu_out: for (int j = 0; j < output_columns; j++) {
    #pragma HLS PIPELINE II=Performance_Target
        float acc = 0.0f;
        dense_relu_in: for (int i = 0; i < input_columns; i++) {
        #pragma HLS UNROLL
            acc += input[i] * weights[i * output_columns + j];
        }
        acc += bias[j];
        // ReLU
        output[j] = (acc > 0.0f) ? acc : 0.0f;
    }
}
