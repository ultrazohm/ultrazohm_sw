#include "../include/fcs_mpc.h"
#include "../uz/uz_AXI.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "xparameters.h"

extern DS_Data Global_Data;

const float polepairs = 4.0f;

const struct uz_PMSM_t AM8141_MPC = {
  .R_ph_Ohm = 0.51,
  .Ld_Henry = 0.002f,
  .Lq_Henry = 0.002f,
  .Psi_PM_Vs = 0.042f,
  .polePairs = 4.0f,
  .I_max_Ampere = 12.0f
};//these parameters are only needed if linear decoupling is selected

struct uz_fixedpoint_definition_t delay_comp_fp_def = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 15
};

struct uz_fixedpoint_definition_t cost_fp_def = {
		.is_signed = false,
		.integer_bits = 1,
		.fractional_bits = 17
};

struct uz_fixedpoint_definition_t i_max_fp_def = {
		.is_signed = false,
		.integer_bits = 3,
		.fractional_bits = 15
};

struct uz_fixedpoint_definition_t i_setpoint_fp_def = {
		.is_signed = true,
		.integer_bits = 7,
		.fractional_bits = 11
};

typedef struct rated_val_t {
	float VR;
	float IR;
	float nR;
}rated_val_t;

typedef struct base_val_t {
	float VB;
	float IB;
	float omegaB;
	float ZB;
	float LB;
	float psiB;
}base_val_t;

typedef struct pre_calc_val_t {
	float Rs_over_ZB;
	float Ts_times_ZB_over_Ld;
	float Ts_times_ZB_over_Lq;
	float Ld_over_LB;
	float Lq_over_LB;
	float psi_pm_over_psiB;
}pre_calc_val_t;

typedef struct pre_calc_val_fixedpoint_t {
	int32_t Rs_over_ZB;
	int32_t Ts_times_ZB_over_Ld;
	int32_t Ts_times_ZB_over_Lq;
	int32_t Ld_over_LB;
	int32_t Lq_over_LB;
	int32_t psi_pm_over_psiB;
}pre_calc_val_fixedpoint_t;

// rated values of Beckhoff_AM8141
const rated_val_t rated_values={
		.IR=8.0f,
		.VR=48.0f/sqrt(2),
		.nR=1000.0f
};

// per unit base values
const base_val_t base_val={
		.VB=sqrt(2.0f/3.0f)*rated_values.VR,
		.IB=sqrt(2.0f)*rated_values.IR,
		.omegaB=rated_values.nR*2.0f*UZ_PIf/60.0f*polepairs,
		.ZB=(sqrt(2.0f/3.0f)*rated_values.VR)/(sqrt(2.0f)*rated_values.IR),
		.LB=(sqrt(2.0f/3.0f)*rated_values.VR)/(sqrt(2.0f)*rated_values.IR)/(rated_values.nR*2.0f*UZ_PIf/60.0f*polepairs),
		.psiB=(sqrt(2.0f/3.0f)*rated_values.VR)/(rated_values.nR*2.0f*UZ_PIf/60.0f*polepairs)
};

const float Ts = 1.0f/UZ_PWM_FREQUENCY;

//pre-calculated factors for delay compensation and prediction model
const pre_calc_val_t pre_calc_val={
		.Rs_over_ZB = AM8141_MPC.R_ph_Ohm/base_val.ZB,
		.Ts_times_ZB_over_Ld = Ts*base_val.ZB/AM8141_MPC.Ld_Henry,
		.Ts_times_ZB_over_Lq = Ts*base_val.ZB/AM8141_MPC.Lq_Henry,
		.Ld_over_LB = AM8141_MPC.Ld_Henry/base_val.LB,
		.Lq_over_LB = AM8141_MPC.Lq_Henry/base_val.LB,
		.psi_pm_over_psiB = AM8141_MPC.Psi_PM_Vs/base_val.psiB
};


float pu_current_conversion = 1.0f/base_val.IB;
float pu_voltage_conversion = 1.0f/base_val.VB;
float pu_omega_m_conversion = 1.0f/base_val.omegaB;

void fcs_mpc_select_current_source(bool right_or_left) {
	uz_axi_write_bool(XPAR_UZ_USER_UZ_SEL_CURRENTS_0_BASEADDR + right_or_left_AXI_Data_uz_sel_currents, right_or_left);
}

void fcs_mpc_select_resolver_source(bool right_or_left) {
	uz_axi_write_bool(XPAR_UZ_USER_UZ_SEL_RESOLVER_0_BASEADDR + right_or_left_AXI_Data_uz_sel_resolver, right_or_left);
}

void fcs_mpc_real_or_debug_inputs(bool debug_or_real) {
	uz_axi_write_bool(XPAR_UZ_USER_FCS_MPC_3PH_UZ_DEBUG_IP_0_BASEADDR + real_or_debug_AXI_Data_uz_debug_ip, debug_or_real);
}

void fcs_mpc_init_pu_conversion_ip(){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in0_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18)); //i_a
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in1_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18)); //i_b
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in2_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18)); //i_c
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in3_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_voltage_conversion,  18)); //v_dc
}

void fcs_mpc_init_park_transform(void){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_UZ_PARK_TRANSFORM_IP_0_BASEADDR + factor_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(1.0f,  14));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_UZ_PARK_TRANSFORM_IP_0_BASEADDR + offset_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(0.0f,  14));
}

void fcs_mpc_init_state_machine(uint32_t no_of_iterations){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_MPC_STATE_MA_IP_0_BASEADDR + AXI_no_of_iterations_Data_mpc_state_ma_ip, no_of_iterations);
}

void fcs_mpc_init_pu_voltages(bool index_from_axi_or_pl, bool v_dc_from_axi_or_pl, float v_dc_axi){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_VSD_0_BASEADDR + index_select_AXI_Data_pu_voltages_vsd, index_from_axi_or_pl);
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_VSD_0_BASEADDR + v_dc_select_AXI_Data_pu_voltages_vsd, v_dc_from_axi_or_pl);
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_VSD_0_BASEADDR + v_DC_pu_AXI_Data_pu_voltages_vsd, uz_convert_float_to_sfixed(v_dc_axi/base_val.VB, 15));
}

void fcs_mpc_init_omega_m_pu_conversion(void){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_OMEGA_M_0_BASEADDR + AXI_pu_conv_in_Data_pu_omega_m, uz_convert_float_to_unsigned_fixed(pu_omega_m_conversion, 18));
}

void fcs_mpc_init_delay_comp(void){
	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_DELAY_COMP_0_BASEADDR + Rs_over_ZB_AXI_Data_delay_comp, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_DELAY_COMP_0_BASEADDR + Ts_times_ZB_over_Ld_AXI_Data_delay_comp, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_DELAY_COMP_0_BASEADDR + Ts_times_ZB_over_Lq_AXI_Data_delay_comp, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_DELAY_COMP_0_BASEADDR + Ld_over_LB_AXI_Data_delay_comp, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_DELAY_COMP_0_BASEADDR + Lq_over_LB_AXI_Data_delay_comp, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_DELAY_COMP_0_BASEADDR + psi_pm_over_psiB_AXI_Data_delay_comp, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
    uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_DELAY_COMP_0_BASEADDR + polepairs_AXI_Data_delay_comp, (uint32_t)(polepairs));
}

void fcs_mpc_init_prediction_model(){
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_PREDICTION_0_BASEADDR + Rs_over_ZB_AXI_Data_prediction, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_PREDICTION_0_BASEADDR + Ts_times_ZB_over_Ld_AXI_Data_prediction, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_PREDICTION_0_BASEADDR + Ts_times_ZB_over_Lq_AXI_Data_prediction, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_PREDICTION_0_BASEADDR + Ld_over_LB_AXI_Data_prediction, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_PREDICTION_0_BASEADDR + Lq_over_LB_AXI_Data_prediction, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_PREDICTION_0_BASEADDR + psi_pm_over_psiB_AXI_Data_prediction, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
    uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PREDICTION_0_BASEADDR + polepairs_AXI_Data_prediction, (uint32_t)(polepairs));
}

void fcs_mpc_init_cost_function(){
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_COST_OPT_0_BASEADDR + max_current_pu_AXI_Data_cost_opt, 1.0f, i_max_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_COST_OPT_0_BASEADDR + lambda_d_AXI_Data_cost_opt, Global_Data.av.lambda_d, cost_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_COST_OPT_0_BASEADDR + lambda_q_AXI_Data_cost_opt, Global_Data.av.lambda_q, cost_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_COST_OPT_0_BASEADDR + lambda_u_AXI_Data_cost_opt, Global_Data.av.lambda_u, cost_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_COST_OPT_0_BASEADDR + id_ref_pu_AXI_Data_cost_opt, 0.0f/base_val.IB, i_setpoint_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_3PH_COST_OPT_0_BASEADDR + iq_ref_pu_AXI_Data_cost_opt, 0.0f/base_val.IB, i_setpoint_fp_def);
}

void fcs_mpc_write_axi_v_dc(){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_VSD_0_BASEADDR + v_DC_pu_AXI_Data_pu_voltages_vsd, uz_convert_float_to_sfixed(Global_Data.av.v_dc_right/base_val.VB, 15));

}
