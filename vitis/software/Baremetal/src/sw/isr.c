/******************************************************************************
 * Copyright 2021 Eyke Liegmann, Tobias Schindler, Sebastian Wendel
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and limitations under the License.
 ******************************************************************************/

#include "../include/isr.h"
#include "../defines.h"
#include "../main.h"
#include "../include/ipc_ARM.h"
#include <math.h>
#include <xtmrctr.h>
#include "../include/javascope.h"
#include "../include/pwm_3L_driver.h"
#include "../include/adc.h"
#include "../IP_Cores/mux_axi_ip_addr.h"
#include "xtime_l.h"
#include "../uz/uz_SystemTime/uz_SystemTime.h"
#include "../uz/uz_math_constants.h"
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_fixedpoint/uz_fixedpoint.h"
#include "../IP_Cores/uz_pu_conversion/uz_pu_conversion_hwAddresses.h"
#include "../IP_Cores/uz_vsd_6ph_30deg/uz_vsd_6ph_30deg_hwAddresses.h"
#include "../IP_Cores/uz_park_transform/uz_park_transform_hwAddresses.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Initialize the Timer structure
XTmrCtr Timer_Interrupt;

// Data for determination of mechanical resolver angle
float theta_mech_old=0.0f;
int32_t cnt = 0U;
bool cnt_reset = 0;
float cnt_float=0.0f;
float cnt_reset_float=0.0f;
float theta_mech_calc_from_resolver = 0.0f;
float theta_m_max = 0.0f;
float theta_m_min = 0.0f;

uz_6ph_abc_t six_ph_currents = {0.0f};
uz_6ph_alphabeta_t six_ph_alphabeta = {0.0f};
uz_3ph_alphabeta_t three_ph_alphabeta = {0.0f};
uz_3ph_dq_t rotating_dq = {0};

uz_3ph_dq_t i_dq_ref = {0.0f};
uz_3ph_dq_t i_dq_actual = {0.0f};
uz_3ph_dq_t u_dq_ref = {0.0f};
uz_3ph_alphabeta_t alphabeta_ref_volts = {0.0f};
uz_6ph_alphabeta_t vsd_ref_volts = {0.0f};
uz_6ph_abc_t phase_ref_volts = {0.0f};

uz_3ph_abc_t input1 = {0.0f};
uz_3ph_abc_t input2 = {0.0f};
struct uz_DutyCycle_t output1 = {0};
struct uz_DutyCycle_t output2 = {0};

uz_3ph_dq_t speed_ctrl_ref_currents = {0.0f};


// Global variable structure
extern DS_Data Global_Data;

// conversion defines for ADC readings
//#define PHASE_CURRENT_CONV	16.75f
#define PHASE_CURRENT_CONV	11.65f
//#define DC_VOLT_CONV_1	140.27f
#define DC_VOLT_CONV_1		99.35f
//#define DC_VOLT_OFF_1		450.25f
#define DC_VOLT_OFF_1		450.25f
//#define DC_VOLT_CONV_2	141.28f
#define DC_VOLT_CONV_2		99.35f
#define DC_VOLT_OFF_2		450.25f
#define TORQUE_CONV			20.0f // 20Nm/V
// software current limit
#define MAX_PHASE_CURRENT_AMP  12.0f
#define MAX_DC_VOLT 590.0f




// pu output fixed point definition
struct uz_fixedpoint_definition_t fixedpoint_definition = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 15
};

// vsd output fixed point definition
struct uz_fixedpoint_definition_t vsd_fixedpoint_definition = {
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

// delay comp output fixed point definition
struct uz_fixedpoint_definition_t delay_fixedpoint_definition = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 24
};

// pu voltages vsd output fixed point definition
struct uz_fixedpoint_definition_t pu_volts_vsd_fixedpoint_definition = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 24
};

struct uz_fixedpoint_definition_t i_setpoint_isr_fp_def = {
		.is_signed = true,
		.integer_bits = 7,
		.fractional_bits = 11
};


bool first_ISR = false;


//=============================================================================
// MPC IP core pre calculations

// 2x3ph PMSM parameters
const uz_PMSM_6ph_t dengine={
		.R_ph_Ohm=0.27f,
		.Ld_Henry=0.0017f,
		.Lq_Henry=0.0038f,
		.Lx_Henry=0.0024f,
		.Ly_Henry=0.0025f,
		.polePairs=5.0f,
		.Psi_PM_Vs=0.19f,
		.I_max_Ampere=18.0f
};

// 2x3ph PMSM rated values
const rated_val_t rated_val={
		.VR=400.0f,
		.IR=7.071f,
//		.IR=14.142f,
		.nR=3000.0f
};

// p.u. base values
const base_val_t base_val={
		.VB=sqrt(2.0f/3.0f)*rated_val.VR,
		.IB=sqrt(2.0f)*rated_val.IR,
		.omegaB=rated_val.nR*2.0f*UZ_PIf/60.0f*dengine.polePairs,
		.ZB=(sqrt(2.0f/3.0f)*rated_val.VR)/(sqrt(2.0f)*rated_val.IR),
		.LB=(sqrt(2.0f/3.0f)*rated_val.VR)/(sqrt(2.0f)*rated_val.IR)/(rated_val.nR*2.0f*UZ_PIf/60.0f*dengine.polePairs),
		.psiB=(sqrt(2.0f/3.0f)*rated_val.VR)/(rated_val.nR*2.0f*UZ_PIf/60.0f*dengine.polePairs)
};

const float Ts = 1.0f/UZ_PWM_FREQUENCY;

//pre-calculated factors for delay compensation and prediction model
const pre_calc_val_t pre_calc_val={
		.Rs_over_ZB = dengine.R_ph_Ohm/base_val.ZB,
		.Ts_times_ZB_over_Ld = Ts*base_val.ZB/dengine.Ld_Henry,
		.Ts_times_ZB_over_Lq = Ts*base_val.ZB/dengine.Lq_Henry,
		.Ts_times_ZB_over_Lx = Ts*base_val.ZB/dengine.Lx_Henry,
		.Ts_times_ZB_over_Ly = Ts*base_val.ZB/dengine.Ly_Henry,
		.Ld_over_LB = dengine.Ld_Henry/base_val.LB,
		.Lq_over_LB = dengine.Lq_Henry/base_val.LB,
		.psi_pm_over_psiB = dengine.Psi_PM_Vs/base_val.psiB
};

float sw_cnt_avg_time_sec = 0.0f;
uint32_t isr_cnt = 0U;
uint32_T wait_cnt = 0U;
uint32_t mod_wait_cnt = 0U;
float f_mod_wait_cnt = 0.0f;
uint32_t switchNumb = 0U;
float passed_time_sec = 0.0f;
float pause_timer_sec = 0.0f;
float f_sw_avg_Hz = 0.0f;



//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    Global_Data.av.pl_interface = uz_resolver_pl_interface_get_outputs(Global_Data.objects.pl_interface);
    //read resolver PL interface IP
    Global_Data.av.theta_elec_rad_ip = Global_Data.av.pl_interface.position_el_2pi;
    Global_Data.av.theta_mech_rad_ip = Global_Data.av.pl_interface.position_mech_2pi;
    Global_Data.av.mechanicalRotorSpeedRPM_ip = Global_Data.av.pl_interface.n_mech_rpm;
    Global_Data.av.mechanicalRotorSpeedRADpS_ip = Global_Data.av.pl_interface.omega_mech_rad_s;
    Global_Data.av.electricalRotorSpeedRPM = Global_Data.av.mechanicalRotorSpeedRPM_ip*Global_Data.av.polepairs;
    Global_Data.av.electricalRotorSpeedRADpS = Global_Data.av.mechanicalRotorSpeedRADpS_ip*Global_Data.av.polepairs;



    // read resolver
    Global_Data.av.posVel_mech = uz_resolverIP_readMechanicalPositionAndVelocity(Global_Data.objects.resolver_d5_1);
    Global_Data.av.posVel_el = uz_resolverIP_readElectricalPositionAndVelocity(Global_Data.objects.resolver_d5_1);

    //read pu IP currents
//    Global_Data.av.i_c1_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out0_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_b1_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out1_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_a1_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out2_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_c2_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out8_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_b2_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out9_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.i_a2_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out10_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
    //read pu IP voltages
//    Global_Data.av.v_dc1_ip = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out3_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
//    Global_Data.av.v_dc2_ip = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out11_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
    // read VSD IP
    Global_Data.av.i_alpha_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + alpha_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
    Global_Data.av.i_beta_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + beta_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
    Global_Data.av.i_X_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + x_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
    Global_Data.av.i_Y_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + y_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
    Global_Data.av.i_0p_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + z1_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
    Global_Data.av.i_0n_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + z2_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);

    // read park transform ip
    Global_Data.av.i_d_ip = uz_fixedpoint_axi_read(XPAR_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y1_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);
    Global_Data.av.i_q_ip = uz_fixedpoint_axi_read(XPAR_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y2_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);

    Global_Data.av.i_d_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x104, delay_fixedpoint_definition);
    Global_Data.av.i_q_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x108, delay_fixedpoint_definition);
    Global_Data.av.i_x_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x10C, delay_fixedpoint_definition);
    Global_Data.av.i_y_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_1_BASEADDR + 0x110, delay_fixedpoint_definition);

//    //DEBUG write index to pu_voltages ip via AXI
//    uz_axi_write_uint32(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x100, 0U);

    // read pu_voltages_vsd ip
//    Global_Data.av.vd_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x108, pu_volts_vsd_fixedpoint_definition);
//    Global_Data.av.vq_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x10C, pu_volts_vsd_fixedpoint_definition);
//    Global_Data.av.vx_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x110, pu_volts_vsd_fixedpoint_definition);
//    Global_Data.av.vy_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x114, pu_volts_vsd_fixedpoint_definition);
//
//    // save raw angles to variables
//    Global_Data.av.theta_mech_rad = Global_Data.av.posVel_mech.position;
//    Global_Data.av.theta_elec_rad = Global_Data.av.posVel_el.position;
//
//    Global_Data.av.theta_mech_calculated = theta_mech_calc_from_resolver-Global_Data.av.theta_mech_offset_rad;
//
//    // save speeds in rad/s to variables
//    Global_Data.av.mechanicalRotorSpeedRADpS = Global_Data.av.posVel_mech.velocity;
//    Global_Data.av.electricalRotorSpeedRADpS = Global_Data.av.posVel_el.velocity;
//
//    // calculate speeds in rpm
//    Global_Data.av.mechanicalRotorSpeedRPM = Global_Data.av.mechanicalRotorSpeedRADpS * 30.0f/UZ_PIf;
//    Global_Data.av.electricalRotorSpeedRPM = Global_Data.av.electricalRotorSpeedRADpS * 30.0f/UZ_PIf;

    // convert ADC readings to currents in Amps
    Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_CURRENT_CONV;
    Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
    Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV;
    Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV;
    Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_CURRENT_CONV;
    Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
    // convert ADC readings to voltages
    Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A4 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * DC_VOLT_CONV_1 + DC_VOLT_OFF_1;
    Global_Data.av.v_dc2 =Global_Data.aa.A2.me.ADC_A4 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * DC_VOLT_CONV_2 + DC_VOLT_OFF_2;
    // convert ADC reading to torque
//    Global_Data.av.torque = Global_Data.aa.A3.me.ADC_A1 * TORQUE_CONV;

    // write measured dc_link voltage to pu_voltages ip
    uz_axi_write_uint32(XPAR_MPC_PAR_PU_VOLTS_VSD_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(Global_Data.av.v_dc1/base_val.VB, 15));

    // check current limit
	if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {
//		uz_assert(0);
		ultrazohm_state_machine_set_stop(true);
	}

	// check fast fpga current limit violation
	if (uz_axi_read_bool(XPAR_PU_CONVERSION_UZ_CUR_LIM_0_BASEADDR + 0x108) == true) {
		ultrazohm_state_machine_set_stop(true);
		Global_Data.av.overcurrent_FPGA = true;
		Global_Data.av.overcurrent_FPGA_fl = 1.0f;
		uz_axi_write_bool(XPAR_PU_CONVERSION_UZ_CUR_LIM_0_BASEADDR + 0x104, false); //clear reset flag for current limit violation
	} else {
		Global_Data.av.overcurrent_FPGA = false;
		Global_Data.av.overcurrent_FPGA_fl = 0.0f;
	}

	// check DC Bus
	if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {
//			uz_assert(0);
			ultrazohm_state_machine_set_stop(true);
	}

	// read temperature values from inverters
	Global_Data.av.tempPWMoutputs1 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.tempMeasurement1);
	Global_Data.av.tempPWMoutputs2 = uz_PWM_duty_freq_detection_get_outputs(Global_Data.objects.tempMeasurement2);
	Global_Data.av.temperature_inv_1 = Global_Data.av.tempPWMoutputs1.TempDegreesCelsius;
	Global_Data.av.temperature_inv_2 = Global_Data.av.tempPWMoutputs2.TempDegreesCelsius;

    // transform phase currents
    six_ph_currents.a1 = Global_Data.av.i_a1;
    six_ph_currents.b1 = Global_Data.av.i_b1;
    six_ph_currents.c1 = Global_Data.av.i_c1;
    six_ph_currents.a2 = Global_Data.av.i_a2;
    six_ph_currents.b2 = Global_Data.av.i_b2;
    six_ph_currents.c2 = Global_Data.av.i_c2;
    six_ph_alphabeta = uz_transformation_asym30deg_6ph_abc_to_alphabeta(six_ph_currents);

    three_ph_alphabeta.alpha = six_ph_alphabeta.alpha;
    three_ph_alphabeta.beta = six_ph_alphabeta.beta;
    Global_Data.av.i_alpha = three_ph_alphabeta.alpha;
    Global_Data.av.i_beta = three_ph_alphabeta.beta;
    Global_Data.av.i_x = six_ph_alphabeta.x;
    Global_Data.av.i_y = six_ph_alphabeta.y;
    rotating_dq = uz_transformation_3ph_alphabeta_to_dq(three_ph_alphabeta, Global_Data.av.theta_elec_rad_ip);
    Global_Data.av.i_d = rotating_dq.d;
    Global_Data.av.i_q = rotating_dq.q;

    i_dq_actual.d = Global_Data.av.i_d;
    i_dq_actual.q = Global_Data.av.i_q;

	i_dq_ref.d = Global_Data.av.i_d_ref;
	i_dq_ref.q = Global_Data.av.i_q_ref;


	// write reference values to mpc ip
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);

    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);

    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);

    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);

    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);

    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);

    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);

    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
//    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x104, Global_Data.av.i_q_ref_PI_out_pu, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x108, Global_Data.av.i_x_ref/base_val.IB, i_setpoint_isr_fp_def);
    uz_fixedpoint_axi_write(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x10C, Global_Data.av.i_y_ref/base_val.IB, i_setpoint_isr_fp_def);


    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==idle_state)
    {
    	uz_FOC_reset(Global_Data.objects.foc_current);
    	uz_axi_write_bool(XPAR_MPC_PAR_MPC_ENB_0_BASEADDR + 0x17C, false);

    	uz_PI_Controller_reset(Global_Data.objects.MPC_setpoint_PI);
    	Global_Data.av.i_q_ref_PI_out_pu = Global_Data.av.i_q_ref_pu;

    }

    if (current_state==control_state)
    {
//		uz_PWM_SS_2L_hw_SetMode(Global_Data.objects.pwm_d1_pin_0_to_5, direct_control_via_FPGA);
//		uz_PWM_SS_2L_hw_SetMode(Global_Data.objects.pwm_d1_pin_6_to_11, direct_control_via_FPGA);
        // Start: Control algorithm - only if ultrazohm is in control state
    	if (Global_Data.av.debug_ip_off == true) {
    	uz_axi_write_bool(XPAR_MPC_PAR_MPC_ENB_0_BASEADDR + 0x17C, true);
    	uz_axi_write_bool(XPAR_PU_CONVERSION_UZ_CUR_LIM_0_BASEADDR + 0x104, true); //reset current limit violation
    	}

    	Global_Data.av.i_q_ref_PI_out_pu = uz_PI_Controller_sample(Global_Data.objects.MPC_setpoint_PI, Global_Data.av.i_q_ref_pu , Global_Data.av.i_q_ip , false);


    	//    	speed_ctrl_ref_currents = uz_SpeedControl_sample(Global_Data.objects.foc_speed, Global_Data.av.mechanicalRotorSpeed*3.1415/30.0f*Global_Data.av.polepairs,Global_Data.av.rpm_ref_filt, Global_Data.av.U_ZK_filt, Global_Data.av.i_d_ref, config_PMSM1, false);

    	//    	u_dq_ref = uz_FOC_sample(Global_Data.objects.foc_current, speed_ctrl_ref_currents, i_dq_actual, Global_Data.av.U_ZK_filt, Global_Data.av.mechanicalRotorSpeed*3.1415/30.0f*Global_Data.av.polepairs);
    	    	u_dq_ref = uz_FOC_sample(Global_Data.objects.foc_current, i_dq_ref, i_dq_actual, Global_Data.av.v_dc1, Global_Data.av.electricalRotorSpeedRADpS);
    	    	alphabeta_ref_volts = uz_transformation_3ph_dq_to_alphabeta(u_dq_ref, Global_Data.av.theta_elec_rad_ip);
    	    	vsd_ref_volts.alpha = alphabeta_ref_volts.alpha;
    	    	vsd_ref_volts.beta = alphabeta_ref_volts.beta;
    	    	phase_ref_volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(vsd_ref_volts);

    	    	input1.a = phase_ref_volts.a1;
    	    	input1.b = phase_ref_volts.b1;
    	    	input1.c = phase_ref_volts.c1;
    	    	input2.a = phase_ref_volts.a2;
    	    	input2.b = phase_ref_volts.b2;
    	    	input2.c = phase_ref_volts.c2;

    	    	output1 = uz_FOC_generate_DutyCycles(input1, Global_Data.av.v_dc1);
    	    	output2 = uz_FOC_generate_DutyCycles(input2, Global_Data.av.v_dc2);

    	    	Global_Data.rasv.halfBridge1DutyCycle = output1.DutyCycle_U;
    	    	Global_Data.rasv.halfBridge2DutyCycle = output1.DutyCycle_V;
    	    	Global_Data.rasv.halfBridge3DutyCycle = output1.DutyCycle_W;
    	    	Global_Data.rasv.halfBridge4DutyCycle = output2.DutyCycle_U;
    	    	Global_Data.rasv.halfBridge5DutyCycle = output2.DutyCycle_V;
    	    	Global_Data.rasv.halfBridge6DutyCycle = output2.DutyCycle_W;
    }





    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
//    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);


    // state machine for automated trade-off curve measurement
    if(Global_Data.av.pause_timer_sec >= Global_Data.av.pause_time_sec) {
    	wait_cnt = 0U;
    	mod_wait_cnt++;
    	if(mod_wait_cnt > 2U) {
    		mod_wait_cnt=0U;
    	}

    }


    // count switching actions of 2L-sixphase inverter
    if(Global_Data.av.mechanicalRotorSpeedRADpS_ip > 1.0f) {
    sw_cnt_avg_time_sec = 1.0f/(Global_Data.av.mechanicalRotorSpeedRPM_ip / 60.0f * dengine.polePairs) * 20.0f; //calculate averaging time window according to 20x fundamental electric period
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
        	switchNumb = uz_axi_read_uint32(XPAR_MPC_TWO_LEVEL_SIXPHASE_F_0_BASEADDR + 0x104);
        	uz_axi_write_bool(XPAR_MPC_TWO_LEVEL_SIXPHASE_F_0_BASEADDR + 0x100, true);	// reset counter = true
        	isr_cnt = 0;
        	Global_Data.av.f_sw_avg_Hz = switchNumb * 0.041667f / passed_time_sec; // 0.041667 = 1/(12*2); 12 switches and each transition is counted (*2)
        	uz_axi_write_bool(XPAR_MPC_TWO_LEVEL_SIXPHASE_F_0_BASEADDR + 0x100, false); // reset counter false
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
        		Global_Data.av.lambda_u = Global_Data.rasv.lambda_u_now;
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    			uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
        	}
        }

    f_mod_wait_cnt = (float)mod_wait_cnt;

    if(Global_Data.rasv.cnt_lambda_u > Global_Data.rasv.cnt_lambda_u_end) {
    	Global_Data.av.start_trade_off_measurement = false;
    	Global_Data.rasv.cnt_lambda_u = 1U;
    	Global_Data.rasv.f_cnt_lambda_u = 1.0f;
		Global_Data.rasv.lambda_u_now = Global_Data.rasv.lambda_u_start;
		Global_Data.av.lambda_u = Global_Data.rasv.lambda_u_now;
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_0_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_1_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_2_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_3_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_4_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_5_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_6_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
		uz_axi_write_int32(XPAR_MPC_PAR_COST_OPT_7_BASEADDR + 0x124, uz_convert_float_to_unsigned_fixed(Global_Data.av.lambda_u, 17));
    }

        isr_cnt++;
        wait_cnt++;

        passed_time_sec = isr_cnt * 1.0f/(UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE);
        Global_Data.av.pause_timer_sec = wait_cnt * 1.0f/(UZ_PWM_FREQUENCY/INTERRUPT_ADC_TO_ISR_RATIO_USER_CHOICE);

    // Set duty cycles for three-level modulator
//    PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
//                        Global_Data.rasv.halfBridge2DutyCycle,
//                        Global_Data.rasv.halfBridge3DutyCycle);
    JavaScope_update(&Global_Data);

//    // Determine mechanical angle of resolver
//    if(theta_mech_old-Global_Data.av.theta_mech_rad > 4.0f) {
//    	cnt++;
//    	cnt_float=(float)cnt;
//    } else if (theta_mech_old-Global_Data.av.theta_mech_rad < -4.0f) {
//    	cnt--;
//    	cnt_float=(float)cnt;
//    }
//
//    if(cnt > 1 || cnt < -1) {
//    	cnt = 0;
//    	cnt_float = 0.0f;
//    }
//
//    if(cnt_reset == 1) {
//    	cnt = 0;
//    	cnt_float = 0;
//    	cnt_reset = 0;
//    	cnt_reset_float=0;
//    }
//
//
//    if(cnt >= 0){
//    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech_rad/uz_resolverIP_getResolverPolePairs(Global_Data.objects.resolver_d5_1) + cnt*2*UZ_PIf/2.0f;
//    } else {
//    	theta_mech_calc_from_resolver = Global_Data.av.theta_mech_rad/2.0f + (2+cnt)*2*UZ_PIf/2.0f;
//    }
//
//    theta_mech_old = Global_Data.av.theta_mech_rad;
//
//    // reset SW and FPGA resolver calculation counter for having defined init state
//	if (first_ISR == true) {
//		cnt = 0;
//		cnt_float = 0.0f;
//		first_ISR = false;
//	}
//
//    if (Global_Data.av.theta_mech_rad <= theta_m_min) {
//    	theta_m_min = Global_Data.av.theta_mech_rad;
//    }
//
//    if (Global_Data.av.theta_mech_rad >= theta_m_max) {
//    	theta_m_max = Global_Data.av.theta_mech_rad;
//    }

    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();
}

//==============================================================================================================================================================

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE & SET THE INTERRUPTs and ISRs
//----------------------------------------------------
int Initialize_ISR()
{

    int Status = 0;

    // Initialize interrupt controller for the IPI -> Initialize RPU IPI
    Status = Rpu_IpiInit(INTERRUPT_ID_IPI);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI initialization failed\r\n");
        return XST_FAILURE;
    }

    // Initialize interrupt controller for the GIC
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG, &Timer_Interrupt);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable uz_mux_axi for triggering the ADCs and the ISR
//    uz_mux_axi_hw_enable_IP_core(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR);
//    uz_mux_axi_hw_set_mux(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
//    uz_mux_axi_hw_set_n_th_interrupt(XPAR_INTERRUPT_MUX_AXI_IP_1_BASEADDR, 1);
    //uz_mux_axi_enable(Global_Data.objects.mux_axi);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// INITIALIZE AXI-TIMER FOR ISRs
// - "TIMER_LOAD_VALUE" sets the counter-end-value in order to set the ISR-frequency f_c
// - "Con_TIMER_DEVICE_ID" uses the Device-ID of the used timer in Vivado
// - "Timer_Interrupt" is the used timer structure instance
// - "XTC_INT_MODE_OPTION" activates the Interrupt function
// - "XTC_AUTO_RELOAD_OPTION" activates an automatic reload of the timer
// - By default, the counter counts up
//----------------------------------------------------
int Initialize_Timer()
{

    int Status;

    // SETUP THE TIMER 1 for Interrupts
    Status = XTmrCtr_Initialize(&Timer_Interrupt, XPAR_UZ_SYSTEM_INTERRUPT_TRIGGER_F_CC_DEVICE_ID);
    if (Status != XST_SUCCESS)
        return XST_FAILURE;
    // XTmrCtr_SetHandler(&Timer_Interrupt, ISR_Control, &Timer_Interrupt);
    XTmrCtr_SetOptions(&Timer_Interrupt, 0, XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
    XTmrCtr_SetResetValue(&Timer_Interrupt, 0, TIMER_LOAD_VALUE);
    XTmrCtr_Reset(&Timer_Interrupt, 0);
    XTmrCtr_Start(&Timer_Interrupt, 0);

    return Status;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId, XTmrCtr *Timer_Interrupt_InstancePtr)
{
    XScuGic_Config *IntcConfig;
    int status;

    // Interrupt controller initialization
    IntcConfig = XScuGic_LookupConfig(DeviceId);
    status = XScuGic_CfgInitialize(IntcInstPtr, IntcConfig, IntcConfig->CpuBaseAddress);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Connect the interrupt controller interrupt handler to the hardware interrupt handling logic in the processor
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntcInstPtr);

    /* Enable interrupts in the processor */
    Xil_ExceptionEnable(); // Enable interrupts in the ARM

    // setting interrupt trigger sensitivity
    // b01	Active HIGH level sensitive
    // b11 	Rising edge sensitive
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(IntcInstPtr, Interrupt_ISR_ID, 0x0, 0b11); // rising-edge
    // XScuGic_SetPriorityTriggerType(&INTCInst, Interrupt_ISR_ID, 0x0, 0b01); // active-high - default case

    // Make the connection between the IntId of the interrupt source and the
    // associated handler that is to run when the interrupt is recognized.
    status = XScuGic_Connect(IntcInstPtr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             (void *)IntcInstPtr);
    if (status != XST_SUCCESS)
        return XST_FAILURE;

    // Enable GPIO and timer interrupts in the controller
    XScuGic_Enable(IntcInstPtr, Interrupt_ISR_ID);
    XScuGic_Enable(IntcInstPtr, INTC_IPC_Shared_INTERRUPT_ID);

    xil_printf("RPU: Rpu_GicInit: Done\r\n");
    return XST_SUCCESS;
}

//==============================================================================================================================================================
//----------------------------------------------------
// Rpu_IpiInit() - This function initializes RPU IPI and enables IPI interrupts
//
// @IpiInstPtr		Pointer to the IPI instance
//----------------------------------------------------
u32 Rpu_IpiInit(u16 DeviceId)
{
    XIpiPsu_Config *IntcConfig_IPI;
    int status;

    // Interrupt controller configuration
    IntcConfig_IPI = XIpiPsu_LookupConfig(DeviceId);
    if (IntcConfig_IPI == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&INTCInst_IPI, IntcConfig_IPI, IntcConfig_IPI->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&INTCInst_IPI, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: RPU_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};
