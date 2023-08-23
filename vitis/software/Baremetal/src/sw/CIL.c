#include "../include/CIL.h"

uz_9ph_abc_t uz_CIL_phase_currents(struct CIL_objects objects){
	uz_9ph_abc_t out = uz_pmsm9ph_transformation_get_currents(objects.transformation);
	return out;
}

void uz_CIL_read_direction(struct CIL_objects objects, DS_Data* Data){
	struct uz_pmsm_model9ph_dq_outputs_general_t pmsmout = uz_pmsm_model9ph_dq_get_outputs_general(objects.pmsm);
	Data->av.rotational_position.position_el_2pi = pmsmout.theta_el;
	Data->av.omega_el = pmsmout.theta_el;
}

void uz_CIL_misc(struct CIL_objects objects, DS_Data* Data){
	struct uz_pmsm_model9ph_dq_outputs_general_t pmsmout = uz_pmsm_model9ph_dq_get_outputs_general(objects.pmsm);
	Data->av.torque_Nm_raw = pmsmout.torque;
	Data->av.torque_Nm_filtered = pmsmout.torque;
	Data->av.U_ZK1 = UDC_CIL;
	Data->av.U_ZK2 = UDC_CIL;
	Data->av.U_ZK3 = UDC_CIL;
	Data->av.U_ZK = UDC_CIL;

}
