#include "uz_NN_acc.h"


void uz_NN_acc(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_4_Weights_input, float *L_5_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_4_Bias_input, float *L_5_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag) {
#pragma HLS INTERFACE m_axi port=Observation_Input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_1_Weights_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_2_Weights_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_3_Weights_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_4_Weights_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_5_Weights_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_Output_Weights_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_1_Bias_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_2_Bias_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_3_Bias_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_4_Bias_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_5_Bias_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=L_Output_Bias_input bundle=arrays depth=32
#pragma HLS INTERFACE m_axi port=Action_output bundle=arrays depth=32
#pragma HLS INTERFACE s_axilite mode=ap_none port=Observation_size_input
#pragma HLS INTERFACE s_axilite mode=ap_none port=Action_size_input
#pragma HLS INTERFACE s_axilite mode=ap_none port=copy_mats_flag
#pragma HLS INTERFACE s_axilite mode=ap_none port=copy_flag_out
#pragma HLS INTERFACE s_axilite mode=ap_none port=matrices_updated_out
#pragma HLS INTERFACE s_axilite mode=ap_none port=compute_flag
#pragma HLS INTERFACE mode=ap_ctrl_hs port=return

#if Hidden_Layers==1
	uz_1_layers(Observation_Input, L_1_Weights_input, L_Output_Weights_input, Action_output, L_1_Bias_input, L_Output_Bias_input, copy_mats_flag, Observation_size_input, Action_size_input, copy_flag_out, matrices_updated_out, compute_flag);
#elif Hidden_Layers==2
	uz_2_layers(Observation_Input, L_1_Weights_input, L_2_Weights_input, L_Output_Weights_input, Action_output, L_1_Bias_input, L_2_Bias_input, L_Output_Bias_input, copy_mats_flag, Observation_size_input, Action_size_input, copy_flag_out, matrices_updated_out, compute_flag);
#elif Hidden_Layers==3
	uz_3_layers(Observation_Input, L_1_Weights_input, L_2_Weights_input, L_3_Weights_input, L_Output_Weights_input, Action_output, L_1_Bias_input, L_2_Bias_input, L_3_Bias_input, L_Output_Bias_input, copy_mats_flag, Observation_size_input, Action_size_input, copy_flag_out, matrices_updated_out, compute_flag);
#elif Hidden_Layers==4
	uz_4_layers(Observation_Input, L_1_Weights_input, L_2_Weights_input, L_3_Weights_input, L_4_Weights_input, L_Output_Weights_input, Action_output, L_1_Bias_input, L_2_Bias_input, L_3_Bias_input, L_4_Bias_input, L_Output_Bias_input, copy_mats_flag, Observation_size_input, Action_size_input, copy_flag_out, matrices_updated_out, compute_flag);
#elif Hidden_Layers==5
	uz_5_layers(Observation_Input, L_1_Weights_input, L_2_Weights_input, L_3_Weights_input, L_4_Weights_input, L_5_Weights_input, L_Output_Weights_input, Action_output, L_1_Bias_input, L_2_Bias_input, L_3_Bias_input, L_4_Bias_input, L_5_Bias_input, L_Output_Bias_input, copy_mats_flag, Observation_size_input, Action_size_input, copy_flag_out, matrices_updated_out, compute_flag);
#endif
}
