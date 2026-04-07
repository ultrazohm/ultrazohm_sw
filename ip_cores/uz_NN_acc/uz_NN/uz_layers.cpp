#include "uz_layers.h"
#include "uz_dense.h"
#include "uz_dense_relu.h"
#include "uz_MMult_MaxSize.h"
#include "uz_copy_L_Output_Weights.h"

void uz_1_layers(float *Observation_Input, float *L_1_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag) {

#pragma HLS INLINE
	//Read compute flag first to set it at the start of the ip-core
	bool intern_compute_flag = *compute_flag;

	//First Layer
	float Observation[Observation_max_rows*Observation_max_columns] = {0};
	float static L_1_Weights[L_1_Weights_max_rows*L_1_Weights_max_columns] = {0};
#pragma HLS ARRAY_PARTITION variable=L_1_Weights type=block factor=L_1_Weights_max_rows/Performance_Target
	float static L_1_Bias[y1_max_rows*y1_max_columns] = {0};
	float y1[y1_max_rows*y1_max_columns] = {0};


	//Output Layer
	float static L_Output_Weights[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};
#pragma HLS ARRAY_PARTITION variable=L_Output_Weights type=block factor=L_Output_Weights_max_rows/Performance_Target
	float static L_Output_Weights_temp[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};
	float static L_Output_Bias[Action_max_rows*Action_max_columns] = {0};
	float static Actions[Action_max_rows*Action_max_columns] = {0};

//Array Bind_Storage
#pragma HLS BIND_STORAGE variable=L_1_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights_temp type= ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_1_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Bias type=ram_1p impl=bram


	bool matrices_updated = false;
	*matrices_updated_out = false;

	if (*copy_mats_flag == 1) {
		*copy_flag_out = true;

		//Only read as many values, as specified by user via Observation_size_input.
		//Rest of L_1_Weights array if (Observation_size_input < L_1_Weights_max_rows) will be set to 0
		burst_L_1_Weights:for(int i=0; i < (Observation_size_input*L_1_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=(L_1_Weights_max_rows*L_1_Weights_max_columns)
			L_1_Weights[i] = L_1_Weights_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Weights array if (Action_size_input < L_Output_Weights_max_columns) will be set to 0
		burst_L_Output_Weights:for(int i=0; i < (L_Output_Weights_max_rows*Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=L_Output_Weights_max_rows max=(L_Output_Weights_max_rows*L_Output_Weights_max_columns)
			L_Output_Weights_temp[i] = L_Output_Weights_input[i];
		}

		uz_copy_L_Output_Weights(L_Output_Weights, L_Output_Weights_temp, L_Output_Weights_max_columns, L_Output_Weights_max_rows, Action_size_input);

		burst_L_1_Bias:for(int i=0; i < (y1_max_rows*y1_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_1_Bias[i] = L_1_Bias_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Bias array if (Action_size_input < Action_max_columns) will be set to 0
		burst_L_Output_Bias:for(int i=0; i < (Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
			L_Output_Bias[i] = L_Output_Bias_input[i];
		}
		matrices_updated = true;
		*matrices_updated_out = matrices_updated;
	} else {
		*copy_flag_out = false;
	}
if(intern_compute_flag) {
	//Burst read input
	//Only read as many values, as specified by user via Observation_size_input.
	//Rest of Observation array if (Observation_size_input < Observation_max_columns) will be set to 0
	burst_Observation:for(int i=0; i < Observation_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Observation_max_columns
		Observation[i] = Observation_Input[i];
	}

	//First Layer
	uz_dense_relu(Observation, L_1_Weights, L_1_Bias, y1, Observation_max_columns, y1_max_columns);

	//Output Layer
	uz_dense(y1,L_Output_Weights,L_Output_Bias,Actions,y1_max_columns,Action_max_columns);

}

	//Burst write output
	//Only write as many values, as specified by user via Action_size_input.
	//Rest of Action array if (Action_size_input < Action_max_columns) will be ignored
	burst_Action:for(int i=0; i < Action_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
		Action_output[i] = Actions[i];
	}

}

void uz_2_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input,float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag) {

#pragma HLS INLINE
	//Read compute flag first to set it at the start of the ip-core
	bool intern_compute_flag = *compute_flag;

	//First Layer
	float Observation[Observation_max_rows*Observation_max_columns] = {0};  	//1x20
	float static L_1_Weights[L_1_Weights_max_rows*L_1_Weights_max_columns] = {0};	//20x64
#pragma HLS ARRAY_PARTITION variable=L_1_Weights type=block factor=L_1_Weights_max_rows/Performance_Target
	float static L_1_Bias[y1_max_rows*y1_max_columns] = {0};//1x64
	float y1[y1_max_rows*y1_max_columns] = {0};		//1x64

	//Second Layer
	float static L_2_Weights[L_2_Weights_max_rows*L_2_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_2_Weights type=block factor=L_2_Weights_max_rows/Performance_Target
	float static L_2_Bias[y2_max_rows*y2_max_columns] = {0};//1x64
	float y2[y2_max_rows*y2_max_columns] = {0};		//1x64

	//Output Layer
	float static L_Output_Weights[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
#pragma HLS ARRAY_PARTITION variable=L_Output_Weights type=block factor=L_Output_Weights_max_rows/Performance_Target
	float static L_Output_Weights_temp[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
	float static L_Output_Bias[Action_max_rows*Action_max_columns] = {0};//1x12
	float static Actions[Action_max_rows*Action_max_columns] = {0};

//Array Bind_Storage
#pragma HLS BIND_STORAGE variable=L_1_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights_temp type= ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_1_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Bias type=ram_1p impl=bram


	bool matrices_updated = false;
	*matrices_updated_out = false;

	if (*copy_mats_flag == 1) {
		*copy_flag_out = true;

		//Only read as many values, as specified by user via Observation_size_input.
		//Rest of L_1_Weights array if (Observation_size_input < L_1_Weights_max_rows) will be set to 0
		burst_L_1_Weights:for(int i=0; i < (Observation_size_input*L_1_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=(L_1_Weights_max_rows*L_1_Weights_max_columns)
			L_1_Weights[i] = L_1_Weights_input[i];
		}

		burst_L_2_Weights:for(int i=0; i < (L_2_Weights_max_rows*L_2_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Weights[i] = L_2_Weights_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Weights array if (Action_size_input < L_Output_Weights_max_columns) will be set to 0
		burst_L_Output_Weights:for(int i=0; i < (L_Output_Weights_max_rows*Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=L_Output_Weights_max_rows max=(L_Output_Weights_max_rows*L_Output_Weights_max_columns)
			L_Output_Weights_temp[i] = L_Output_Weights_input[i];
		}

		uz_copy_L_Output_Weights(L_Output_Weights, L_Output_Weights_temp, L_Output_Weights_max_columns, L_Output_Weights_max_rows, Action_size_input);

		burst_L_1_Bias:for(int i=0; i < (y1_max_rows*y1_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_1_Bias[i] = L_1_Bias_input[i];
		}
		burst_L_2_Bias:for(int i=0; i < (y2_max_rows*y2_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Bias[i] = L_2_Bias_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Bias array if (Action_size_input < Action_max_columns) will be set to 0
		burst_L_Output_Bias:for(int i=0; i < (Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
			L_Output_Bias[i] = L_Output_Bias_input[i];
		}
		matrices_updated = true;
		*matrices_updated_out = matrices_updated;
	} else {
		*copy_flag_out = false;
	}
if(intern_compute_flag) {
	//Burst read input
	//Only read as many values, as specified by user via Observation_size_input.
	//Rest of Observation array if (Observation_size_input < Observation_max_columns) will be set to 0
	burst_Observation:for(int i=0; i < Observation_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Observation_max_columns
		Observation[i] = Observation_Input[i];
	}

	//First Layer
	uz_dense_relu(Observation, L_1_Weights, L_1_Bias, y1, Observation_max_columns, y1_max_columns);

	//Second Layer
	uz_dense_relu(y1, L_2_Weights, L_2_Bias, y2, y1_max_columns, y2_max_columns);

	//Output Layer
	uz_dense(y2,L_Output_Weights,L_Output_Bias,Actions,y2_max_columns,Action_max_columns);

}

	//Burst write output
	//Only write as many values, as specified by user via Action_size_input.
	//Rest of Action array if (Action_size_input < Action_max_columns) will be ignored
	burst_Action:for(int i=0; i < Action_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
		Action_output[i] = Actions[i];
	}

}

void uz_3_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag) {

#pragma HLS INLINE
	//Read compute flag first to set it at the start of the ip-core
	bool intern_compute_flag = *compute_flag;

	//First Layer
	float Observation[Observation_max_rows*Observation_max_columns] = {0};  	//1x20
	float static L_1_Weights[L_1_Weights_max_rows*L_1_Weights_max_columns] = {0};	//20x64
#pragma HLS ARRAY_PARTITION variable=L_1_Weights type=block factor=L_1_Weights_max_rows/Performance_Target
	float static L_1_Bias[y1_max_rows*y1_max_columns] = {0};//1x64
	float y1[y1_max_rows*y1_max_columns] = {0};		//1x64

	//Second Layer
	float static L_2_Weights[L_2_Weights_max_rows*L_2_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_2_Weights type=block factor=L_2_Weights_max_rows/Performance_Target
	float static L_2_Bias[y2_max_rows*y2_max_columns] = {0};//1x64
	float y2[y2_max_rows*y2_max_columns] = {0};		//1x64



	//Third Layer
	float static L_3_Weights[L_3_Weights_max_rows*L_3_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_3_Weights type=block factor=L_3_Weights_max_rows/Performance_Target
	float static L_3_Bias[y3_max_rows*y3_max_columns] = {0};//1x64
	float y3[y3_max_rows*y3_max_columns] = {0};		//1x64

	//Output Layer
	float static L_Output_Weights[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
#pragma HLS ARRAY_PARTITION variable=L_Output_Weights type=block factor=L_Output_Weights_max_rows/Performance_Target
	float static L_Output_Weights_temp[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
	float static L_Output_Bias[Action_max_rows*Action_max_columns] = {0};//1x12
	float static Actions[Action_max_rows*Action_max_columns] = {0};

//Array Bind_Storage
#pragma HLS BIND_STORAGE variable=L_1_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_3_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights_temp type= ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_1_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_3_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Bias type=ram_1p impl=bram


	bool matrices_updated = false;
	*matrices_updated_out = false;

	if (*copy_mats_flag == 1) {
		*copy_flag_out = true;

		//Only read as many values, as specified by user via Observation_size_input.
		//Rest of L_1_Weights array if (Observation_size_input < L_1_Weights_max_rows) will be set to 0
		burst_L_1_Weights:for(int i=0; i < (Observation_size_input*L_1_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=(L_1_Weights_max_rows*L_1_Weights_max_columns)
			L_1_Weights[i] = L_1_Weights_input[i];
		}

		burst_L_2_Weights:for(int i=0; i < (L_2_Weights_max_rows*L_2_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Weights[i] = L_2_Weights_input[i];
		}
		burst_L_3_Weights:for(int i=0; i < (L_3_Weights_max_rows*L_3_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_3_Weights[i] = L_3_Weights_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Weights array if (Action_size_input < L_Output_Weights_max_columns) will be set to 0
		burst_L_Output_Weights:for(int i=0; i < (L_Output_Weights_max_rows*Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=L_Output_Weights_max_rows max=(L_Output_Weights_max_rows*L_Output_Weights_max_columns)
			L_Output_Weights_temp[i] = L_Output_Weights_input[i];
		}

		uz_copy_L_Output_Weights(L_Output_Weights, L_Output_Weights_temp, L_Output_Weights_max_columns, L_Output_Weights_max_rows, Action_size_input);

		burst_L_1_Bias:for(int i=0; i < (y1_max_rows*y1_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_1_Bias[i] = L_1_Bias_input[i];
		}
		burst_L_2_Bias:for(int i=0; i < (y2_max_rows*y2_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Bias[i] = L_2_Bias_input[i];
		}
		burst_L_3_Bias:for(int i=0; i < (y3_max_rows*y3_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_3_Bias[i] = L_3_Bias_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Bias array if (Action_size_input < Action_max_columns) will be set to 0
		burst_L_Output_Bias:for(int i=0; i < (Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
			L_Output_Bias[i] = L_Output_Bias_input[i];
		}
		matrices_updated = true;
		*matrices_updated_out = matrices_updated;
	} else {
		*copy_flag_out = false;
	}
if(intern_compute_flag) {
	//Burst read input
	//Only read as many values, as specified by user via Observation_size_input.
	//Rest of Observation array if (Observation_size_input < Observation_max_columns) will be set to 0
	burst_Observation:for(int i=0; i < Observation_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Observation_max_columns
		Observation[i] = Observation_Input[i];
	}

	//Input Layer
	uz_dense_relu(Observation, L_1_Weights, L_1_Bias, y1, Observation_max_columns, y1_max_columns);

	//First Layer
	uz_dense_relu(y1, L_2_Weights, L_2_Bias, y2, y1_max_columns, y2_max_columns);


	//Second Layer
	uz_dense_relu(y2, L_3_Weights, L_3_Bias, y3, y2_max_columns, y3_max_columns);

	//Third Layer
	uz_dense(y3,L_Output_Weights,L_Output_Bias,Actions,y3_max_columns,Action_max_columns);

}

	//Burst write output
	//Only write as many values, as specified by user via Action_size_input.
	//Rest of Action array if (Action_size_input < Action_max_columns) will be ignored
	burst_Action:for(int i=0; i < Action_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
		Action_output[i] = Actions[i];
	}

}

void uz_4_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_4_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_4_Bias_input, float *L_Output_Bias_input, volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag) {

#pragma HLS INLINE
	//Read compute flag first to set it at the start of the ip-core
	bool intern_compute_flag = *compute_flag;

	//First Layer
	float Observation[Observation_max_rows*Observation_max_columns] = {0};  	//1x20
	float static L_1_Weights[L_1_Weights_max_rows*L_1_Weights_max_columns] = {0};	//20x64
#pragma HLS ARRAY_PARTITION variable=L_1_Weights type=block factor=L_1_Weights_max_rows/Performance_Target
	float static L_1_Bias[y1_max_rows*y1_max_columns] = {0};//1x64
	float y1[y1_max_rows*y1_max_columns] = {0};		//1x64

	//Second Layer
	float static L_2_Weights[L_2_Weights_max_rows*L_2_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_2_Weights type=block factor=L_2_Weights_max_rows/Performance_Target
	float static L_2_Bias[y2_max_rows*y2_max_columns] = {0};//1x64
	float y2[y2_max_rows*y2_max_columns] = {0};		//1x64



	//Third Layer
	float static L_3_Weights[L_3_Weights_max_rows*L_3_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_3_Weights type=block factor=L_3_Weights_max_rows/Performance_Target
	float static L_3_Bias[y3_max_rows*y3_max_columns] = {0};//1x64
	float y3[y3_max_rows*y3_max_columns] = {0};		//1x64

	//Fourth Layer
	float static L_4_Weights[L_4_Weights_max_rows*L_4_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_4_Weights type=block factor=L_4_Weights_max_rows/Performance_Target
	float static L_4_Bias[y4_max_rows*y4_max_columns] = {0};//1x64
	float y4[y4_max_rows*y4_max_columns] = {0};		//1x64

	//Output Layer
	float static L_Output_Weights[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
#pragma HLS ARRAY_PARTITION variable=L_Output_Weights type=block factor=L_Output_Weights_max_rows/Performance_Target
	float static L_Output_Weights_temp[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
	float static L_Output_Bias[Action_max_rows*Action_max_columns] = {0};//1x12
	float static Actions[Action_max_rows*Action_max_columns] = {0};

//Array Bind_Storage
#pragma HLS BIND_STORAGE variable=L_1_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_3_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_4_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights_temp type= ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_1_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_3_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_4_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Bias type=ram_1p impl=bram


	bool matrices_updated = false;
	*matrices_updated_out = false;

	if (*copy_mats_flag == 1) {
		*copy_flag_out = true;

		//Only read as many values, as specified by user via Observation_size_input.
		//Rest of L_1_Weights array if (Observation_size_input < L_1_Weights_max_rows) will be set to 0
		burst_L_1_Weights:for(int i=0; i < (Observation_size_input*L_1_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=(L_1_Weights_max_rows*L_1_Weights_max_columns)
			L_1_Weights[i] = L_1_Weights_input[i];
		}

		burst_L_2_Weights:for(int i=0; i < (L_2_Weights_max_rows*L_2_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Weights[i] = L_2_Weights_input[i];
		}
		burst_L_3_Weights:for(int i=0; i < (L_3_Weights_max_rows*L_3_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_3_Weights[i] = L_3_Weights_input[i];
		}
		burst_L_4_Weights:for(int i=0; i < (L_4_Weights_max_rows*L_4_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_4_Weights[i] = L_4_Weights_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Weights array if (Action_size_input < L_Output_Weights_max_columns) will be set to 0
		burst_L_Output_Weights:for(int i=0; i < (L_Output_Weights_max_rows*Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=L_Output_Weights_max_rows max=(L_Output_Weights_max_rows*L_Output_Weights_max_columns)
			L_Output_Weights_temp[i] = L_Output_Weights_input[i];
		}

		uz_copy_L_Output_Weights(L_Output_Weights, L_Output_Weights_temp, L_Output_Weights_max_columns, L_Output_Weights_max_rows, Action_size_input);

		burst_L_1_Bias:for(int i=0; i < (y1_max_rows*y1_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_1_Bias[i] = L_1_Bias_input[i];
		}
		burst_L_2_Bias:for(int i=0; i < (y2_max_rows*y2_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Bias[i] = L_2_Bias_input[i];
		}
		burst_L_3_Bias:for(int i=0; i < (y3_max_rows*y3_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_3_Bias[i] = L_3_Bias_input[i];
		}
		burst_L_4_Bias:for(int i=0; i < (y4_max_rows*y4_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_4_Bias[i] = L_4_Bias_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Bias array if (Action_size_input < Action_max_columns) will be set to 0
		burst_L_Output_Bias:for(int i=0; i < (Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
			L_Output_Bias[i] = L_Output_Bias_input[i];
		}
		matrices_updated = true;
		*matrices_updated_out = matrices_updated;
	} else {
		*copy_flag_out = false;
	}
if(intern_compute_flag) {
	//Burst read input
	//Only read as many values, as specified by user via Observation_size_input.
	//Rest of Observation array if (Observation_size_input < Observation_max_columns) will be set to 0
	burst_Observation:for(int i=0; i < Observation_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Observation_max_columns
		Observation[i] = Observation_Input[i];
	}

	//First Layer
	uz_dense_relu(Observation, L_1_Weights, L_1_Bias, y1, Observation_max_columns, y1_max_columns);

	//Second Layer
	uz_dense_relu(y1, L_2_Weights, L_2_Bias, y2, y1_max_columns, y2_max_columns);

	//Third Layer
	uz_dense_relu(y2, L_3_Weights, L_3_Bias, y3, y2_max_columns, y3_max_columns);

	//Fourth Layer
	uz_dense_relu(y3, L_4_Weights, L_4_Bias, y4, y3_max_columns, y4_max_columns);

	//Output Layer
	uz_dense(y4,L_Output_Weights,L_Output_Bias,Actions,y4_max_columns,Action_max_columns);

}

	//Burst write output
	//Only write as many values, as specified by user via Action_size_input.
	//Rest of Action array if (Action_size_input < Action_max_columns) will be ignored
	burst_Action:for(int i=0; i < Action_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
		Action_output[i] = Actions[i];
	}

}

void uz_5_layers(float *Observation_Input, float *L_1_Weights_input, float *L_2_Weights_input, float *L_3_Weights_input, float *L_4_Weights_input, float *L_5_Weights_input, float *L_Output_Weights_input, float *Action_output,
		float *L_1_Bias_input, float *L_2_Bias_input, float *L_3_Bias_input, float *L_4_Bias_input, float *L_5_Bias_input, float *L_Output_Bias_input,
		volatile bool *copy_mats_flag, uint_fast32_t Observation_size_input, uint_fast32_t Action_size_input,
		volatile bool *copy_flag_out, volatile bool *matrices_updated_out, volatile bool *compute_flag) {

#pragma HLS INLINE
	//Read compute flag first to set it at the start of the ip-core
	bool intern_compute_flag = *compute_flag;

	//First Layer
	float Observation[Observation_max_rows*Observation_max_columns] = {0};  	//1x20
	float static L_1_Weights[L_1_Weights_max_rows*L_1_Weights_max_columns] = {0};	//20x64
#pragma HLS ARRAY_PARTITION variable=L_1_Weights type=block factor=L_1_Weights_max_rows/Performance_Target
	float static L_1_Bias[y1_max_rows*y1_max_columns] = {0};//1x64
	float y1[y1_max_rows*y1_max_columns] = {0};		//1x64

	//Second Layer
	float static L_2_Weights[L_2_Weights_max_rows*L_2_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_2_Weights type=block factor=L_2_Weights_max_rows/Performance_Target
	float static L_2_Bias[y2_max_rows*y2_max_columns] = {0};//1x64
	float y2[y2_max_rows*y2_max_columns] = {0};		//1x64

	//Third Layer
	float static L_3_Weights[L_3_Weights_max_rows*L_3_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_3_Weights type=block factor=L_3_Weights_max_rows/Performance_Target
	float static L_3_Bias[y3_max_rows*y3_max_columns] = {0};//1x64
	float y3[y3_max_rows*y3_max_columns] = {0};		//1x64

	//Fourth Layer
	float static L_4_Weights[L_4_Weights_max_rows*L_4_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_4_Weights type=block factor=L_4_Weights_max_rows/Performance_Target
	float static L_4_Bias[y4_max_rows*y4_max_columns] = {0};//1x64
	float y4[y4_max_rows*y4_max_columns] = {0};		//1x64

	//Fifth Layer
	float static L_5_Weights[L_5_Weights_max_rows*L_5_Weights_max_columns] = {0};	//64x64
#pragma HLS ARRAY_PARTITION variable=L_5_Weights type=block factor=L_5_Weights_max_rows/Performance_Target
	float static L_5_Bias[y5_max_rows*y5_max_columns] = {0};//1x64
	float y5[y5_max_rows*y5_max_columns] = {0};		//1x64

	//Output Layer
	float static L_Output_Weights[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
#pragma HLS ARRAY_PARTITION variable=L_Output_Weights type=block factor=L_Output_Weights_max_rows/Performance_Target
	float static L_Output_Weights_temp[L_Output_Weights_max_rows*L_Output_Weights_max_columns] = {0};	//64x12
	float static L_Output_Bias[Action_max_rows*Action_max_columns] = {0};//1x12
	float static Actions[Action_max_rows*Action_max_columns] = {0};

//Array Bind_Storage
#pragma HLS BIND_STORAGE variable=L_1_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_3_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_4_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_5_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Weights_temp type= ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_1_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_2_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_3_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_4_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_5_Bias type=ram_1p impl=bram
#pragma HLS BIND_STORAGE variable=L_Output_Bias type=ram_1p impl=bram


	bool matrices_updated = false;
	*matrices_updated_out = false;

	if (*copy_mats_flag == 1) {
		*copy_flag_out = true;

		//Only read as many values, as specified by user via Observation_size_input.
		//Rest of L_1_Weights array if (Observation_size_input < L_1_Weights_max_rows) will be set to 0
		burst_L_1_Weights:for(int i=0; i < (Observation_size_input*L_1_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=(L_1_Weights_max_rows*L_1_Weights_max_columns)
			L_1_Weights[i] = L_1_Weights_input[i];
		}

		burst_L_2_Weights:for(int i=0; i < (L_2_Weights_max_rows*L_2_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Weights[i] = L_2_Weights_input[i];
		}
		burst_L_3_Weights:for(int i=0; i < (L_3_Weights_max_rows*L_3_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_3_Weights[i] = L_3_Weights_input[i];
		}
		burst_L_4_Weights:for(int i=0; i < (L_4_Weights_max_rows*L_4_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_4_Weights[i] = L_4_Weights_input[i];
		}
		burst_L_5_Weights:for(int i=0; i < (L_5_Weights_max_rows*L_5_Weights_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_5_Weights[i] = L_5_Weights_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Weights array if (Action_size_input < L_Output_Weights_max_columns) will be set to 0
		burst_L_Output_Weights:for(int i=0; i < (L_Output_Weights_max_rows*Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=L_Output_Weights_max_rows max=(L_Output_Weights_max_rows*L_Output_Weights_max_columns)
			L_Output_Weights_temp[i] = L_Output_Weights_input[i];
		}

		uz_copy_L_Output_Weights(L_Output_Weights, L_Output_Weights_temp, L_Output_Weights_max_columns, L_Output_Weights_max_rows, Action_size_input);

		burst_L_1_Bias:for(int i=0; i < (y1_max_rows*y1_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_1_Bias[i] = L_1_Bias_input[i];
		}
		burst_L_2_Bias:for(int i=0; i < (y2_max_rows*y2_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_2_Bias[i] = L_2_Bias_input[i];
		}
		burst_L_3_Bias:for(int i=0; i < (y3_max_rows*y3_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_3_Bias[i] = L_3_Bias_input[i];
		}
		burst_L_4_Bias:for(int i=0; i < (y4_max_rows*y4_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_4_Bias[i] = L_4_Bias_input[i];
		}
		burst_L_5_Bias:for(int i=0; i < (y5_max_rows*y5_max_columns); i++) {
		#pragma HLS PIPELINE II=1
			L_5_Bias[i] = L_5_Bias_input[i];
		}
		//Only read as many values, as specified by user via Action_size_input.
		//Rest of L_Output_Bias array if (Action_size_input < Action_max_columns) will be set to 0
		burst_L_Output_Bias:for(int i=0; i < (Action_size_input); i++) {
		#pragma HLS PIPELINE II=1
		#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
			L_Output_Bias[i] = L_Output_Bias_input[i];
		}
		matrices_updated = true;
		*matrices_updated_out = matrices_updated;
	} else {
		*copy_flag_out = false;
	}
if(intern_compute_flag) {
	//Burst read input
	//Only read as many values, as specified by user via Observation_size_input.
	//Rest of Observation array if (Observation_size_input < Observation_max_columns) will be set to 0
	burst_Observation:for(int i=0; i < Observation_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Observation_max_columns
		Observation[i] = Observation_Input[i];
	}

	//First Layer
	uz_dense_relu(Observation, L_1_Weights, L_1_Bias, y1, Observation_max_columns, y1_max_columns);

	//Second Layer
	uz_dense_relu(y1, L_2_Weights, L_2_Bias, y2, y1_max_columns, y2_max_columns);

	//Third Layer
	uz_dense_relu(y2, L_3_Weights, L_3_Bias, y3, y2_max_columns, y3_max_columns);

	//Fourth Layer
	uz_dense_relu(y3, L_4_Weights, L_4_Bias, y4, y3_max_columns, y4_max_columns);

	//Fifth Layer
	uz_dense_relu(y4, L_5_Weights, L_5_Bias, y5, y4_max_columns, y5_max_columns);

	//Output Layer
	uz_dense(y5,L_Output_Weights,L_Output_Bias,Actions,y5_max_columns,Action_max_columns);

}

	//Burst write output
	//Only write as many values, as specified by user via Action_size_input.
	//Rest of Action array if (Action_size_input < Action_max_columns) will be ignored
	burst_Action:for(int i=0; i < Action_size_input; i++) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LOOP_TRIPCOUNT min=1 max=Action_max_columns
		Action_output[i] = Actions[i];
	}

}
