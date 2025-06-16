#ifndef UZ_MMULT_MAXSIZE_H
#define UZ_MMULT_MAXSIZE_H


//User define
#define Neurons_per_HiddenLayer 64
#define Hidden_Layers 3 //max 5
#define Performance_Target 1//Range of 1->Neurons_per_HiddenLayer. Higher number=slower ip-core, but less resources. Adjust, if ==1 is too large for your FPGA


//Auto-Settings for synthesis

#define max_Observations 24
#define max_Actions 12

#define Observation_max_rows 1
#define Observation_max_columns max_Observations

#define L_1_Weights_max_rows max_Observations
#define L_1_Weights_max_columns Neurons_per_HiddenLayer
#define y1_max_rows 1
#define y1_max_columns Neurons_per_HiddenLayer

#define L_2_Weights_max_rows Neurons_per_HiddenLayer
#define L_2_Weights_max_columns Neurons_per_HiddenLayer
#define y2_max_rows 1
#define y2_max_columns Neurons_per_HiddenLayer

#define L_3_Weights_max_rows Neurons_per_HiddenLayer
#define L_3_Weights_max_columns Neurons_per_HiddenLayer
#define y3_max_rows 1
#define y3_max_columns Neurons_per_HiddenLayer

#define L_4_Weights_max_rows Neurons_per_HiddenLayer
#define L_4_Weights_max_columns Neurons_per_HiddenLayer
#define y4_max_rows 1
#define y4_max_columns Neurons_per_HiddenLayer

#define L_5_Weights_max_rows Neurons_per_HiddenLayer
#define L_5_Weights_max_columns Neurons_per_HiddenLayer
#define y5_max_rows 1
#define y5_max_columns Neurons_per_HiddenLayer

#define L_Output_Weights_max_rows Neurons_per_HiddenLayer
#define L_Output_Weights_max_columns max_Actions
#define Action_max_rows 1
#define Action_max_columns max_Actions

#endif
