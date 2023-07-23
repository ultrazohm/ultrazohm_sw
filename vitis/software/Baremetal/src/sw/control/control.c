#include "control.h"


void subspace_park_transform(DS_Data* Data){
	Data->av.currents_xy1 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY1, 3.0f*Data->av.rotational_position.position_el_2pi - PHASE_PSI_PM_3);
	Data->av.currents_xy2 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY2, 5.0f*Data->av.rotational_position.position_el_2pi - PHASE_PSI_PM_5);
	Data->av.currents_xy3 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY3, 7.0f*Data->av.rotational_position.position_el_2pi - PHASE_PSI_PM_7);
}
