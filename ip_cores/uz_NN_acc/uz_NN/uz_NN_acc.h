#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "uz_MMult_MaxSize.h"
#include "uz_dense_relu.h"
#include "uz_dense.h"
#include "uz_copy_L_Output_Weights.h"
#include "uz_layers.h"

void uz_NN_acc(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_4_Weights_input, float *L_5_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_4_Bias_input, float *L_5_Bias_input, float *L_Output_Bias_input,
		volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag);
