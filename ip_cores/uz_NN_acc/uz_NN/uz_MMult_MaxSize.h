#ifndef UZ_MMULT_MAXSIZE_H
#define UZ_MMULT_MAXSIZE_H


//User define
#define Hidden_Layers 3 //max 5
#define Neurons_1st_Hidden_Layer 64
#define Neurons_2nd_Hidden_Layer 64
#define Neurons_3rd_Hidden_Layer 64
#define Neurons_4th_Hidden_Layer 64
#define Neurons_5th_Hidden_Layer 64

#define Performance_Target 1//Range of 1->min(Neurons_per_HiddenLayer). Higher number=slower ip-core, but less resources. Adjust, if ==1 is too large for your FPGA

//Auto-Settings for synthesis

#define max_Observations 24
#define max_Actions 12

#define Observation_max_rows 1
#define Observation_max_columns max_Observations

#define L_1_Weights_max_rows max_Observations
#define L_1_Weights_max_columns Neurons_1st_Hidden_Layer
#define y1_max_rows 1
#define y1_max_columns Neurons_1st_Hidden_Layer

#define L_2_Weights_max_rows Neurons_1st_Hidden_Layer
#define L_2_Weights_max_columns Neurons_2nd_Hidden_Layer
#define y2_max_rows 1
#define y2_max_columns Neurons_2nd_Hidden_Layer

#define L_3_Weights_max_rows Neurons_2nd_Hidden_Layer
#define L_3_Weights_max_columns Neurons_3rd_Hidden_Layer
#define y3_max_rows 1
#define y3_max_columns Neurons_3rd_Hidden_Layer

#define L_4_Weights_max_rows Neurons_3rd_Hidden_Layer
#define L_4_Weights_max_columns Neurons_4th_Hidden_Layer
#define y4_max_rows 1
#define y4_max_columns Neurons_4th_Hidden_Layer

#define L_5_Weights_max_rows Neurons_4th_Hidden_Layer
#define L_5_Weights_max_columns Neurons_5th_Hidden_Layer
#define y5_max_rows 1
#define y5_max_columns Neurons_5th_Hidden_Layer

#if Hidden_Layers==1
	#define L_Output_Weights_max_rows Neurons_1st_Hidden_Layer
#elif Hidden_Layers==2
	#define L_Output_Weights_max_rows Neurons_2nd_Hidden_Layer
#elif Hidden_Layers==3
	#define L_Output_Weights_max_rows Neurons_3rd_Hidden_Layer
#elif Hidden_Layers==4
	#define L_Output_Weights_max_rows Neurons_4th_Hidden_Layer
#elif Hidden_Layers==5
	#define L_Output_Weights_max_rows Neurons_5th_Hidden_Layer
#endif

#define L_Output_Weights_max_columns max_Actions
#define Action_max_rows 1
#define Action_max_columns max_Actions

#endif
