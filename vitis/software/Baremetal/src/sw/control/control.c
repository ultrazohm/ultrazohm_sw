#include "control.h"


void subspace_park_transform(DS_Data* Data){
	Data->av.currents_xy1 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY1, 3.0f*Data->av.rotational_position.position_el_2pi + PHASE_PSI_PM_3);
	Data->av.currents_xy2 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY2, 5.0f*Data->av.rotational_position.position_el_2pi + PHASE_PSI_PM_5);
	Data->av.currents_xy3 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY3, 7.0f*Data->av.rotational_position.position_el_2pi + PHASE_PSI_PM_7);
}

uz_9ph_dq_t check_ref_volt_isnan_and_neutral_config(uz_9ph_dq_t input, int neutral){
	uz_9ph_dq_t output = input;
	if(isnan(output.d)){
		output.d = 0.0f;
	}
	if(isnan(output.q)){
		output.q = 0.0f;
	}
	if(isnan(output.x1)){
		output.x1 = 0.0f;
	}
	if(isnan(output.y1)){
		output.y1 = 0.0f;
	}
	if(isnan(output.x2)){
		output.x2 = 0.0f;
	}
	if(isnan(output.y2)){
		output.y2 = 0.0f;
	}
	if(isnan(output.x3)){
		output.x3 = 0.0f;
	}
	if(isnan(output.y3)){
		output.y3 = 0.0f;
	}
	if(isnan(output.zero)){
		output.zero = 0.0f;
	}
	if(neutral == 3U){
		output.x1 = 0.0f;
		output.y1 = 0.0f;
	}
	return output;
}
