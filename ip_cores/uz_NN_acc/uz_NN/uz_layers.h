#ifndef UZ_LAYERS_H
#define UZ_LAYERS_H

#include <stdio.h>
#include <stdint.h>

void uz_1_layers(float *Observation_Input, float *L_1_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag);

void uz_2_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input,float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag);

void uz_3_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag);

void uz_4_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_4_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_4_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag);

void uz_5_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_4_Weights_input, float *L_5_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_4_Bias_input, float *L_5_Bias_input, float *L_Output_Bias_input,
		volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag);
#endif
