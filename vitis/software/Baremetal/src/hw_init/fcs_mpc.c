#include "../include/fcs_mpc.h"
#include "../uz/uz_AXI.h"
#include "../uz/uz_global_configuration.h"
#include "../uz/uz_math_constants.h"
#include "../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "xparameters.h"

extern DS_Data Global_Data;

const float polepairs = 4.0f;

uint32_t wait_cnt = 0U;
float sw_cnt_avg_time_sec = 0.0f;
uint32_t mod_wait_cnt = 0U;
float f_mod_wait_cnt = 0.0f;
float passed_time_sec = 0.0f;
float pause_timer_sec = 0.0f;

const struct uz_PMSM_t AM8141_MPC = {
  .R_ph_Ohm = 0.51,
  .Ld_Henry = 0.002f,
  .Lq_Henry = 0.002f,
  .Psi_PM_Vs = 0.042f,
  .polePairs = 4.0f,
  .I_max_Ampere = 12.0f,
  .J_kg_m_squared = 0.000108
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

struct uz_fixedpoint_definition_t lambda_u_fp_def = { //ufix18_En19
		.is_signed = false,
		.integer_bits = 0,
		.fractional_bits = 19
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

// park transform output fixed point definition
struct uz_fixedpoint_definition_t park_fixedpoint_definition = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 24
};

// pu output fixed point definition
struct uz_fixedpoint_definition_t fixedpoint_definition = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 15
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

const float Ts = 1.0f/UZ_PWM_FREQUENCY_0;
//const float Ts = 1.0f/100.0e3f;

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

void fcs_mpc_real_or_debug_inputs(bool debug_or_real) {
	uz_axi_write_bool(XPAR_UZ_USER_FCS_MPC_0_UZ_DEBUG_IP_0_BASEADDR + real_or_debug_AXI_Data_uz_debug_ip, debug_or_real);
	uz_axi_write_bool(XPAR_UZ_USER_FCS_MPC_1_UZ_DEBUG_IP_0_BASEADDR + real_or_debug_AXI_Data_uz_debug_ip, debug_or_real);
}

void fcs_mpc_init_pu_conversion_ip(){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in0_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in1_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in2_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in3_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_voltage_conversion,  18));

	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in0_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in1_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in2_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_current_conversion,  18));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_UZ_PU_CON_IP_0_BASEADDR + AXI_pu_conv_in3_Data_uz_pu_con_ip, uz_convert_float_to_unsigned_fixed(pu_voltage_conversion,  18));
}

void fcs_mpc_init_park_transform(void){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_UZ_PARK_TRANSFORM_IP_0_BASEADDR + factor_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(1.0f,  14));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_UZ_PARK_TRANSFORM_IP_0_BASEADDR + offset_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(0.0f,  14));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_UZ_PARK_TRANSFORM_IP_0_BASEADDR + factor_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(1.0f,  14));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_UZ_PARK_TRANSFORM_IP_0_BASEADDR + offset_angle_el_AXI_Data_uz_park_transform_ip, uz_convert_float_to_sfixed(0.0f,  14));
}

void fcs_mpc_init_state_machine(uint32_t no_of_iterations){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_MPC_STATE_MA_IP_0_BASEADDR + AXI_no_of_iterations_Data_mpc_state_ma_ip, no_of_iterations);
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_MPC_STATE_MA_IP_0_BASEADDR + AXI_no_of_iterations_Data_mpc_state_ma_ip, no_of_iterations);
}

void fcs_mpc_init_pu_voltages(bool index_from_axi_or_pl, bool v_dc_from_axi_or_pl, float v_dc_axi, float Ts_minus_Td_over_Ts, float Td_over_Ts, bool deadtime_comp_onoff){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_VSD_0_BASEADDR + index_select_AXI_Data_pu_voltages_dq, index_from_axi_or_pl);
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_VSD_0_BASEADDR + v_dc_select_AXI_Data_pu_voltages_dq, v_dc_from_axi_or_pl);
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_VSD_0_BASEADDR + v_DC_pu_AXI_Data_pu_voltages_dq, uz_convert_float_to_sfixed(v_dc_axi/base_val.VB, 15));

	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_PU_VOLTAGES_VSD_0_BASEADDR + index_select_AXI_Data_pu_voltages_dq, index_from_axi_or_pl);
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_PU_VOLTAGES_VSD_0_BASEADDR + v_dc_select_AXI_Data_pu_voltages_dq, v_dc_from_axi_or_pl);
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_PU_VOLTAGES_VSD_0_BASEADDR + v_DC_pu_AXI_Data_pu_voltages_dq, uz_convert_float_to_sfixed(v_dc_axi/base_val.VB, 15));
//	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_DQ_0_BASEADDR + index_select_AXI_Data_pu_voltages_dq, index_from_axi_or_pl);
//	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_DQ_0_BASEADDR + v_dc_select_AXI_Data_pu_voltages_dq, v_dc_from_axi_or_pl);
//	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_DQ_0_BASEADDR + v_DC_pu_AXI_Data_pu_voltages_dq, uz_convert_float_to_sfixed(v_dc_axi/base_val.VB, 15));
//	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_DQ_0_BASEADDR + Ts_minus_Td_over_Ts_AXI_Data_pu_voltages_dq, uz_convert_float_to_unsigned_fixed(Ts_minus_Td_over_Ts, 18));
//	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_DQ_0_BASEADDR + Td_over_Ts_AXI_Data_pu_voltages_dq, uz_convert_float_to_unsigned_fixed(Td_over_Ts, 18));
//	uz_axi_write_bool(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_DQ_0_BASEADDR + deadtime_comp_onoff_AXI_Data_pu_voltages_dq, deadtime_comp_onoff);
}

void fcs_mpc_write_i_ref_to_pu_voltages(void) {
//	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_DQ_0_BASEADDR + id_ref_pu_AXI_Data_pu_voltages_dq, Global_Data.rasv.i_dq_ref_left.d * pu_current_conversion,  i_setpoint_fp_def);
//	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_DQ_0_BASEADDR + iq_ref_pu_AXI_Data_pu_voltages_dq, Global_Data.rasv.i_dq_ref_left.q * pu_current_conversion,  i_setpoint_fp_def);
}

void fcs_mpc_init_omega_m_pu_conversion(void){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_PU_OMEGA_M_0_BASEADDR + AXI_pu_conv_in_Data_pu_omega_m, uz_convert_float_to_unsigned_fixed(pu_omega_m_conversion, 18));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_PU_OMEGA_M_0_BASEADDR + AXI_pu_conv_in_Data_pu_omega_m, uz_convert_float_to_unsigned_fixed(pu_omega_m_conversion, 18));
}

void fcs_mpc_init_delay_comp(void){
	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + Rs_over_ZB_AXI_Data_delay_comp, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + Ts_times_ZB_over_Ld_AXI_Data_delay_comp, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + Ts_times_ZB_over_Lq_AXI_Data_delay_comp, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + Ld_over_LB_AXI_Data_delay_comp, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + Lq_over_LB_AXI_Data_delay_comp, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + psi_pm_over_psiB_AXI_Data_delay_comp, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
    uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + polepairs_AXI_Data_delay_comp, (uint32_t)(polepairs));

	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + Rs_over_ZB_AXI_Data_delay_comp, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + Ts_times_ZB_over_Ld_AXI_Data_delay_comp, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + Ts_times_ZB_over_Lq_AXI_Data_delay_comp, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + Ld_over_LB_AXI_Data_delay_comp, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + Lq_over_LB_AXI_Data_delay_comp, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + psi_pm_over_psiB_AXI_Data_delay_comp, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
    uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + polepairs_AXI_Data_delay_comp, (uint32_t)(polepairs));
}

void fcs_mpc_init_prediction_model(){
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PREDICTION_0_BASEADDR + Rs_over_ZB_AXI_Data_prediction, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PREDICTION_0_BASEADDR + Ts_times_ZB_over_Ld_AXI_Data_prediction, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PREDICTION_0_BASEADDR + Ts_times_ZB_over_Lq_AXI_Data_prediction, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PREDICTION_0_BASEADDR + Ld_over_LB_AXI_Data_prediction, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PREDICTION_0_BASEADDR + Lq_over_LB_AXI_Data_prediction, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_PREDICTION_0_BASEADDR + psi_pm_over_psiB_AXI_Data_prediction, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
    uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_PREDICTION_0_BASEADDR + polepairs_AXI_Data_prediction, (uint32_t)(polepairs));

    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_PREDICTION_0_BASEADDR + Rs_over_ZB_AXI_Data_prediction, pre_calc_val.Rs_over_ZB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_PREDICTION_0_BASEADDR + Ts_times_ZB_over_Ld_AXI_Data_prediction, pre_calc_val.Ts_times_ZB_over_Ld, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_PREDICTION_0_BASEADDR + Ts_times_ZB_over_Lq_AXI_Data_prediction, pre_calc_val.Ts_times_ZB_over_Lq, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_PREDICTION_0_BASEADDR + Ld_over_LB_AXI_Data_prediction, pre_calc_val.Ld_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_PREDICTION_0_BASEADDR + Lq_over_LB_AXI_Data_prediction, pre_calc_val.Lq_over_LB, delay_comp_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_PREDICTION_0_BASEADDR + psi_pm_over_psiB_AXI_Data_prediction, pre_calc_val.psi_pm_over_psiB, delay_comp_fp_def);
    uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_PREDICTION_0_BASEADDR + polepairs_AXI_Data_prediction, (uint32_t)(polepairs));
}

void fcs_mpc_init_cost_function(){
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + max_current_pu_AXI_Data_cost_opt, Global_Data.av.i_max_mpc, i_max_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + lambda_d_AXI_Data_cost_opt, Global_Data.av.lambda_d, cost_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + lambda_q_AXI_Data_cost_opt, Global_Data.av.lambda_q, cost_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + lambda_u_AXI_Data_cost_opt, Global_Data.av.lambda_u, lambda_u_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + id_ref_pu_AXI_Data_cost_opt, 0.0f/base_val.IB, i_setpoint_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + iq_ref_pu_AXI_Data_cost_opt, 0.0f/base_val.IB, i_setpoint_fp_def);

    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + max_current_pu_AXI_Data_cost_opt, Global_Data.av.i_max_mpc, i_max_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + lambda_d_AXI_Data_cost_opt, Global_Data.av.lambda_d, cost_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + lambda_q_AXI_Data_cost_opt, Global_Data.av.lambda_q, cost_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + lambda_u_AXI_Data_cost_opt, Global_Data.av.lambda_u, lambda_u_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + id_ref_pu_AXI_Data_cost_opt, 0.0f/base_val.IB, i_setpoint_fp_def);
    uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + iq_ref_pu_AXI_Data_cost_opt, 0.0f/base_val.IB, i_setpoint_fp_def);
}

void fcs_mpc_write_axi_v_dc(){
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_VSD_0_BASEADDR + v_DC_pu_AXI_Data_pu_voltages_dq, uz_convert_float_to_sfixed(Global_Data.av.v_dc_d1/base_val.VB, 15));
	uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_1_PU_VOLTAGES_VSD_0_BASEADDR + v_DC_pu_AXI_Data_pu_voltages_dq, uz_convert_float_to_sfixed(Global_Data.av.v_dc_d2/base_val.VB, 15));

}

void fcs_mpc_enable_0(bool enable){
	uz_axi_write_bool(XPAR_UZ_USER_FCS_MPC_0_MPC_ENABLE_0_BASEADDR + AXI_mpc_enb_Data_mpc_enable, enable);
}

void fcs_mpc_enable_1(bool enable){
	uz_axi_write_bool(XPAR_UZ_USER_FCS_MPC_1_MPC_ENABLE_0_BASEADDR + AXI_mpc_enb_Data_mpc_enable, enable);
}

void fcs_mpc_write_setpoint_0(){
	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + id_ref_pu_AXI_Data_cost_opt, Global_Data.rasv.i_dq_ref_0.d * pu_current_conversion, i_setpoint_fp_def);
	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + iq_ref_pu_AXI_Data_cost_opt, Global_Data.rasv.i_dq_ref_0.q * pu_current_conversion, i_setpoint_fp_def);
}

void fcs_mpc_write_setpoint_1(){
	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + id_ref_pu_AXI_Data_cost_opt, Global_Data.rasv.i_dq_ref_1.d * pu_current_conversion, i_setpoint_fp_def);
	uz_fixedpoint_axi_write(XPAR_UZ_USER_FCS_MPC_1_COST_OPT_0_BASEADDR + iq_ref_pu_AXI_Data_cost_opt, Global_Data.rasv.i_dq_ref_1.q * pu_current_conversion, i_setpoint_fp_def);
}

void fcs_mpc_calc_f_sw_avg(){
	static float sw_cnt_avg_time_sec = 0.0f;
	static uint32_t isr_cnt = 0U;
	static uint32_t switchNumb_0 = 0U;
	static uint32_t switchNumb_1 = 0U;
	static float passed_time_sec = 0.0f;

    // state machine for automated trade-off curve measurement
    if(Global_Data.av.pause_timer_sec >= Global_Data.av.pause_time_sec) {
    	wait_cnt = 0U;
    	mod_wait_cnt++;
    	if(mod_wait_cnt > 2U) {
    		mod_wait_cnt=0U;
    	}

    }

    if(fabs(Global_Data.av.speed_rpm_d5_1) > 1.0f) {
    sw_cnt_avg_time_sec = 1.0f/(fabs(Global_Data.av.speed_rpm_d5_1) / 60.0f * AM8141_MPC.polePairs) * 20.0f; //calculate averaging time window according to 20x fundamental electric period
    } else  {
    	sw_cnt_avg_time_sec = 1.0f;
    }

    // assign pause time between automated measurements
    Global_Data.av.pause_time_sec = 10.0f*sw_cnt_avg_time_sec;

    if(Global_Data.av.start_trade_off_measurement == true && Global_Data.av.measure_flag == false) {
    	Global_Data.rasv.req_measure_flag = true;
    }

    // calculate average switching frequency and control the measure flag
    if(passed_time_sec >= sw_cnt_avg_time_sec) {
        	switchNumb_0 = uz_axi_read_uint32(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_COUNT_F_SW_0_BASEADDR + switchNumb_AXI_Data_count_f_sw);
        	switchNumb_1 = uz_axi_read_uint32(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_COUNT_F_SW_1_BASEADDR + switchNumb_AXI_Data_count_f_sw);
        	uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_COUNT_F_SW_0_BASEADDR + bResetAXI_Data_count_f_sw, true);	// reset counter = true
        	uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_COUNT_F_SW_1_BASEADDR + bResetAXI_Data_count_f_sw, true);
        	isr_cnt = 0;
        	Global_Data.av.f_sw_avg_Hz_0 = switchNumb_0 * 0.083333f / passed_time_sec; // 0.083333 = 1/(6*2); 6 switches and each transition is counted (*2)
        	Global_Data.av.f_sw_avg_Hz_1 = switchNumb_1 * 0.083333f / passed_time_sec;
        	uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_COUNT_F_SW_0_BASEADDR + bResetAXI_Data_count_f_sw, false); // reset counter false
        	uz_axi_write_bool(XPAR_UZ_DIGITAL_ADAPTER_D1_ADAPTER_GATES_COUNT_F_SW_1_BASEADDR + bResetAXI_Data_count_f_sw, false);
        	Global_Data.av.f_sw_measure_flag = !Global_Data.av.f_sw_measure_flag; //toggle every time f_sw is measured
        	Global_Data.av.f_f_sw_measure_flag = (float)Global_Data.av.f_sw_measure_flag;
        	// control the measuring flag
        	if (Global_Data.rasv.req_measure_flag == true && Global_Data.av.f_sw_measure_flag == false && mod_wait_cnt == 2) {
        	Global_Data.av.measure_flag = true;
        	Global_Data.av.f_measure_flag = 1.0f;
        	mod_wait_cnt=0U;
        	}
        	if (Global_Data.av.f_sw_measure_flag == true && Global_Data.av.measure_flag == true) {
        		// clear the measure and req_measure flags
        		Global_Data.rasv.req_measure_flag = false;
        		Global_Data.rasv.f_req_measure_flag = 0.0f;
        		Global_Data.av.measure_flag = false;
        		Global_Data.av.f_measure_flag = 0.0f;
        		// increase measuring point counter
        		Global_Data.rasv.cnt_lambda_u++;
        		Global_Data.rasv.f_cnt_lambda_u = (float)Global_Data.rasv.cnt_lambda_u;
        		// set next lamda_u
        		Global_Data.rasv.lambda_u_now = Global_Data.rasv.lambda_u_now + Global_Data.rasv.lambda_u_step;
//        		Global_Data.av.lambda_u = Global_Data.rasv.lambda_u_now;
        		Global_Data.av.lambda_u = Global_Data.rasv.lambda_u_LUT[Global_Data.rasv.cnt_lambda_u];
        		Global_Data.av.lambda_u_e5 = Global_Data.av.lambda_u*1e5f;
        		uz_axi_write_int32(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 19));
        	}
        }

    f_mod_wait_cnt = (float)mod_wait_cnt;

    if(Global_Data.rasv.cnt_lambda_u > Global_Data.rasv.cnt_lambda_u_end) {
    	Global_Data.av.start_trade_off_measurement = false;
    	Global_Data.rasv.cnt_lambda_u = 1U;
    	Global_Data.rasv.f_cnt_lambda_u = 1.0f;
		Global_Data.rasv.lambda_u_now = Global_Data.rasv.lambda_u_start;
		Global_Data.av.lambda_u = Global_Data.rasv.lambda_u_now;
		uz_axi_write_int32(XPAR_UZ_USER_FCS_MPC_0_COST_OPT_0_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 19));
    }

    isr_cnt++;
    wait_cnt++;

    passed_time_sec = isr_cnt * 1.0f/(UZ_PWM_FREQUENCY_0/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE_0);
    Global_Data.av.pause_timer_sec = wait_cnt * 1.0f/(UZ_PWM_FREQUENCY_0/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE_0);
}

void fcs_mpc_debug(void){
    // read park transform ip
    Global_Data.av.i_d_ip = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y1_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);
    Global_Data.av.i_q_ip = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y2_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);
//    Global_Data.av.i_d_ip = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y1_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);
//    Global_Data.av.i_q_ip = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y2_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);
    //read pu IP currents
    Global_Data.av.i_a_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_UZ_PU_CON_IP_0_BASEADDR + out0_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
    Global_Data.av.i_b_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_UZ_PU_CON_IP_0_BASEADDR + out1_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
    Global_Data.av.i_c_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_UZ_PU_CON_IP_0_BASEADDR + out2_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_a_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_UZ_PU_CON_IP_0_BASEADDR + out0_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_b_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_UZ_PU_CON_IP_0_BASEADDR + out1_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_c_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_UZ_PU_CON_IP_0_BASEADDR + out2_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
    //read pu voltages
    Global_Data.av.vd_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_VSD_0_BASEADDR + pu_vd_AXI_Data_pu_voltages_dq, park_fixedpoint_definition);
    Global_Data.av.vq_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_PU_VOLTAGES_VSD_0_BASEADDR + pu_vq_AXI_Data_pu_voltages_dq, park_fixedpoint_definition);
//    Global_Data.av.vd_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_PU_VOLTAGES_VSD_0_BASEADDR + pu_vd_AXI_Data_pu_voltages_dq, park_fixedpoint_definition);
//    Global_Data.av.vq_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_PU_VOLTAGES_VSD_0_BASEADDR + pu_vq_AXI_Data_pu_voltages_dq, park_fixedpoint_definition);

    //read delaycomp_currents
    Global_Data.av.id_delay_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + id_delay_pu_AXI_Data_delay_comp, park_fixedpoint_definition);
    Global_Data.av.iq_delay_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_0_DELAY_COMP_0_BASEADDR + iq_delay_pu_AXI_Data_delay_comp, park_fixedpoint_definition);
//    Global_Data.av.id_delay_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + id_delay_pu_AXI_Data_delay_comp, park_fixedpoint_definition);
//    Global_Data.av.iq_delay_pu = uz_fixedpoint_axi_read(XPAR_UZ_USER_FCS_MPC_1_DELAY_COMP_0_BASEADDR + iq_delay_pu_AXI_Data_delay_comp, park_fixedpoint_definition);
    //write pu voltage debug values
//    uz_axi_write_uint32(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_VSD_0_BASEADDR + index_AXI_Data_pu_voltages_vsd, Global_Data.av.idx_AXI);
}

void fcs_mpc_deadtime_comp_onoff(bool onoff){
//	uz_axi_write_bool(XPAR_UZ_USER_FCS_MPC_3PH_PU_VOLTAGES_DQ_0_BASEADDR + deadtime_comp_onoff_AXI_Data_pu_voltages_dq, onoff);
}
