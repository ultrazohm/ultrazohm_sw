#include "fault_control.h"

void fault_control_set_tristate(DS_Data* Data, uz_9ph_abc_t indices){
	int n_OPF = uz_vsd_opf_9ph_get_n_fault(indices);
	bool syst1 = false;
	bool syst2 = false;
	bool syst3 = false;
	if(n_OPF == 2){
		syst1 = ((indices.a1 == 1.0f)&&(indices.b1 == 1.0f)) || ((indices.a1 == 1.0f)&&(indices.c1 == 1.0f)) || ((indices.b1 == 1.0f)&&(indices.c1 == 1.0f));
		syst2 = ((indices.a2 == 1.0f)&&(indices.b2 == 1.0f)) || ((indices.a2 == 1.0f)&&(indices.c2 == 1.0f)) || ((indices.b2 == 1.0f)&&(indices.c2 == 1.0f));
		syst3 = ((indices.a3 == 1.0f)&&(indices.b3 == 1.0f)) || ((indices.a3 == 1.0f)&&(indices.c3 == 1.0f)) || ((indices.b3 == 1.0f)&&(indices.c3 == 1.0f));
	}else if(n_OPF == 3){
		syst1 = (indices.a1 == 1.0f)&&(indices.b1 == 1.0f)&&(indices.c1 == 1.0f);
		syst1 = (indices.a2 == 1.0f)&&(indices.b2 == 1.0f)&&(indices.c2 == 1.0f);
		syst1 = (indices.a3 == 1.0f)&&(indices.b3 == 1.0f)&&(indices.c3 == 1.0f);
	}
	if(n_OPF>=2){
		uz_PWM_SS_2L_set_tristate(Data->objects.pwm_d1_pin_0_to_5, syst1, syst1, syst1);
		uz_PWM_SS_2L_set_tristate(Data->objects.pwm_d1_pin_6_to_11 , syst2, syst2, syst2);
		uz_PWM_SS_2L_set_tristate(Data->objects.pwm_d1_pin_12_to_17 , syst3, syst3, syst3);
	}
}


uz_9ph_alphabeta_t step_controllers_fault_control(DS_Data* Data, struct pointers_fault_control objects, uz_9ph_MLMT_kparameter_t k_param){
	uz_3ph_alphabeta_t alphabeta_setpoint = uz_transformation_3ph_dq_to_alphabeta(Data->rasv.dq_setpoints, Data->av.rotational_position.position_el_2pi);
	uz_3ph_alphabeta_t XY1_ref = {
		.alpha = k_param.k_X1a * alphabeta_setpoint.alpha + k_param.k_X1b * alphabeta_setpoint.beta,
		.beta =  k_param.k_Y1a * alphabeta_setpoint.alpha + k_param.k_Y1b * alphabeta_setpoint.beta,
	};
	uz_3ph_alphabeta_t XY2_ref = {
		.alpha = k_param.k_X2a * alphabeta_setpoint.alpha + k_param.k_X2b * alphabeta_setpoint.beta,
		.beta =  k_param.k_Y2a * alphabeta_setpoint.alpha + k_param.k_Y2b * alphabeta_setpoint.beta,
	};
	uz_3ph_alphabeta_t XY3_ref = {
		.alpha = k_param.k_X3a * alphabeta_setpoint.alpha + k_param.k_X3b * alphabeta_setpoint.beta,
		.beta =  k_param.k_Y3a * alphabeta_setpoint.alpha + k_param.k_Y3b * alphabeta_setpoint.beta,
	};

	Data->av.currents_xy1 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY1, Data->av.rotational_position.position_el_2pi);
	Data->av.currents_xy2 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY2, Data->av.rotational_position.position_el_2pi);
	Data->av.currents_xy3 = uz_transformation_3ph_alphabeta_to_dq(Data->av.currents_XY3, Data->av.rotational_position.position_el_2pi);

	// step controllers
	Data->av.debug_pi_xy1 = uz_CurrentControl_sample(objects.xy1, uz_transformation_3ph_alphabeta_to_dq(XY1_ref, Data->av.rotational_position.position_el_2pi), Data->av.currents_xy1, Data->av.U_ZK, Data->av.omega_el);
	Data->av.debug_pi_xy2 = uz_CurrentControl_sample(objects.xy2, uz_transformation_3ph_alphabeta_to_dq(XY2_ref, Data->av.rotational_position.position_el_2pi), Data->av.currents_xy2, Data->av.U_ZK, Data->av.omega_el);
	Data->av.debug_pi_xy3 = uz_CurrentControl_sample(objects.xy3, uz_transformation_3ph_alphabeta_to_dq(XY3_ref, Data->av.rotational_position.position_el_2pi), Data->av.currents_xy3, Data->av.U_ZK, Data->av.omega_el);

	// inverse Park transform subsystems
	uz_3ph_alphabeta_t u_ref_XY1 = uz_transformation_3ph_dq_to_alphabeta(Data->av.debug_pi_xy1, Data->av.rotational_position.position_el_2pi);
	uz_3ph_alphabeta_t u_ref_XY2 = uz_transformation_3ph_dq_to_alphabeta(Data->av.debug_pi_xy2, Data->av.rotational_position.position_el_2pi);
	uz_3ph_alphabeta_t u_ref_XY3 = uz_transformation_3ph_dq_to_alphabeta(Data->av.debug_pi_xy3, Data->av.rotational_position.position_el_2pi);

	// out
	uz_9ph_alphabeta_t out_ab = {
		.alpha = 0.0f,
		.beta = 0.0f,
		.x1 = u_ref_XY1.alpha,
		.y1 = u_ref_XY1.beta,
		.x2 = u_ref_XY2.alpha,
		.y2 = u_ref_XY2.beta,
		.x3 = u_ref_XY3.alpha,
		.y3 = u_ref_XY3.beta,
		.zero = 0.0f};
	return out_ab;
}

uz_9ph_alphabeta_t reduce_controller_freedom_degrees(uz_9ph_alphabeta_t ref, int n_OPF){
	uz_9ph_alphabeta_t out = ref;
	switch(n_OPF){
	case 6:
		out.x1 = 0.0f;
	case 5:
		out.y1 = 0.0f;
	case 4:
		out.x2 = 0.0f;
	case 3:
		out.y2 = 0.0f;
	case 2:
		out.x3 = 0.0f;
	case 1:
		out.y3 = 0.0f;
		break;
	default:
		break;
	}
	return out;
}

uz_9ph_dq_t combine_setpoints(uz_9ph_dq_t normal_controller, uz_9ph_alphabeta_t fault_controller){
	uz_9ph_dq_t combined = {
		.d = normal_controller.d,
		.q = normal_controller.q,
		.x1 = normal_controller.x1 + fault_controller.x1,
		.y1 = normal_controller.y1 + fault_controller.y1,
		.x2 = normal_controller.x2 + fault_controller.x2,
		.y2 = normal_controller.y2 + fault_controller.y2,
		.x3 = normal_controller.x3 + fault_controller.x3,
		.y3 = normal_controller.y3 + fault_controller.y3};
	return combined;
}

uz_9ph_alphabeta_t reset_controllers_fault_control_and_tristate(struct pointers_fault_control objects, DS_Data* Data){
	uz_CurrentControl_reset(objects.xy1);
	uz_CurrentControl_reset(objects.xy2);
	uz_CurrentControl_reset(objects.xy3);
	uz_PWM_SS_2L_set_tristate(Data->objects.pwm_d1_pin_0_to_5, false, false, false);
	uz_PWM_SS_2L_set_tristate(Data->objects.pwm_d1_pin_6_to_11 , false, false, false);
	uz_PWM_SS_2L_set_tristate(Data->objects.pwm_d1_pin_12_to_17 , false, false, false);
	uz_9ph_alphabeta_t out = {0};
	return out;
}

void derate_dq_setpoints(DS_Data* Data, float derating, int n_OPF){
	if(n_OPF > 0){
		Data->rasv.dq_setpoints.d = derating * Data->rasv.dq_setpoints_user_input.d;
		Data->rasv.dq_setpoints.q = derating * Data->rasv.dq_setpoints_user_input.q;
	}
}
