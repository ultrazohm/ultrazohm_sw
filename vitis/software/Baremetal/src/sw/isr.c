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
#include "../include/encoder.h"
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


// Global variable structuref
extern DS_Data Global_Data;

//Changes
#define NUMBER_OF_INPUTS_15N 15U
#define NUMBER_OF_INPUTS_17N 17U
uz_matrix_t* matrix_output_15n;
uz_matrix_t* matrix_output_17n;
struct uz_pmsm_model6ph_dq_outputs_general_t CIL_out_general = {0};
uz_6ph_dq_t v_dqxy_limited_volts = {0};
uz_3ph_dq_t v_dq_limited_volts = {0};
uz_3ph_dq_t v_xy_limited_volts = {0};
uz_3ph_dq_t v_dq_non_limited_volts = {0};
uz_3ph_dq_t v_xy_non_limited_volts = {0};
uz_6ph_dq_t v_dqxy_limited_volts_k_old = {0};
uz_6ph_dq_t v_dqxy_non_limited_volts = {0};
uz_6ph_abc_t REAL_i_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_meas = {0};
uz_6ph_abc_t REAL_v_abc_ref = {0};
uz_6ph_dq_t REAL_i_dqxy_meas = {0};
uz_6ph_dq_t REAL_v_dqxy_meas = {0};
uz_6ph_dq_t i_dqxy_integrated_error = {0};
uz_6ph_dq_t i_dqxy_error = {0};
uz_3ph_dq_t REAL_v_dq_reference = {0};
uz_3ph_dq_t REAL_v_xy_reference = {0};
uz_3ph_dq_t REAL_v_z1z2_reference = {0};
uz_3ph_dq_t i_dq_reference = {0};
uz_3ph_dq_t i_xy_reference = {0};
uz_3ph_dq_t i_z1z2_reference = {0};
uz_3ph_dq_t REAL_i_dq_meas= {0};
uz_3ph_dq_t REAL_i_xy_meas = {0};
uz_3ph_dq_t REAL_i_z1z2_meas = {0};

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

struct uz_DutyCycle_2x3ph_t DutyCycle_output = {0};

float max_modulation_index = (1.0f / 2.0f) * 0.707106781f;
float ts = 1.0f / UZ_ISR_FREQUENCY;
const float V_DC_Volts = 12.0f;
float U_max = (V_DC_Volts / 2.0f) * 0.707106781f;
float Voltage_Scaling = 1.0f / (V_DC_Volts / 2.0f);
const float rated_current = 18.0f/sqrt(2); // RMS value
const float polepairs = 5.0f;
const float rated_Speed_rpm = 1100.0f;
float speed_weight = 1.0f / 1100.0f;
bool ext_clamping_dq = false;
bool ext_clamping_xy = false;

int reset = 0U;
//Offset from Valentin
float theta_offset = 5.4843f;
#define PHASE_CURRENT_CONV 12.5f
#define PHASE_VOLT_CONV	12.0f

#define PHASE_CURRENT_CONV_A1	12.803f
#define PHASE_CURRENT_CONV_B1	12.663f
#define PHASE_CURRENT_CONV_C1	12.652f
#define PHASE_CURRENT_CONV_A2	12.67f
#define PHASE_CURRENT_CONV_B2	12.69f
#define PHASE_CURRENT_CONV_C2	12.643f

#define PHASE_CURRENT_OFFSET_A1	0.012f
#define PHASE_CURRENT_OFFSET_B1	0.004f
#define PHASE_CURRENT_OFFSET_C1	0.006f
#define PHASE_CURRENT_OFFSET_A2	-0.012f
#define PHASE_CURRENT_OFFSET_B2	-0.01f
#define PHASE_CURRENT_OFFSET_C2	0.019f

#define PHASE_VOLT_CONV_A1	11.963f
#define PHASE_VOLT_CONV_B1	11.959f
#define PHASE_VOLT_CONV_C1	11.954f
#define PHASE_VOLT_CONV_A2	11.959f
#define PHASE_VOLT_CONV_B2	11.959f
#define PHASE_VOLT_CONV_C2	11.961f

#define PHASE_VOLT_OFFSET_A1	-0.09f
#define PHASE_VOLT_OFFSET_B1	0.002f
#define PHASE_VOLT_OFFSET_C1	-0.065f
#define PHASE_VOLT_OFFSET_A2	-0.038f
#define PHASE_VOLT_OFFSET_B2	-0.049f
#define PHASE_VOLT_OFFSET_C2	-0.02f


// software limits
#define MAX_PHASE_CURRENT_AMP  30.0f
const float max_phase_current_ = MAX_PHASE_CURRENT_AMP;

#define MAX_DC_VOLT 50.0f
#define MAX_TEMP_DEG 90.0f
//neutral config
#define NEUTRAL_CONFIG 2U //1U: 1N, 2U: 2N
float u_n1 = 0.0f;
float u_n2 = 0.0f;
float u_a1c1 = 0.0f;
float u_a2c2 = 0.0f;


float start_marker=0.0f;

// pu output fixed point definition
struct uz_fixedpoint_definition_t fixedpoint_definition = {
		.is_signed = true,
		.integer_bits = 3,
		.fractional_bits = 15
};


// pu omega output fixed point definition
struct uz_fixedpoint_definition_t omega_fixedpoint_definition = {
		.is_signed = true,
		.integer_bits = 13,
		.fractional_bits = 11
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


//=============================================================================
// MPC IP core pre calculations

// 2x3ph PMSM parameters
const uz_PMSM_6ph_t dengine={
		.R_ph_Ohm=0.0643f,
		.Ld_Henry=0.00012516f,
		.Lq_Henry=0.00012595f,
		.Lx_Henry=0.000039374f,
		.Ly_Henry=0.000034854f,
		.polePairs=polepairs,
		.Psi_PM_Vs= 0.0047f,
		.I_max_Ampere=MAX_PHASE_CURRENT_AMP
};


// 2x3ph PMSM rated values da modificare
const rated_val_t rated_val={
		.VR=sqrt(3.0f/2.0f)*V_DC_Volts/2.0f, // RMS, line-line Vdc/2*sqrt(3/2)
		.IR=rated_current, // RMS according to previous data
		.nR=rated_Speed_rpm
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

const float Ts = 1.0f/UZ_PWM_FREQUENCY; //  100 e3 ?

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

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static void ReadAllADC();

static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3);

void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    i_dq_reference.d = Global_Data.av.i_d_ref;
   	i_dq_reference.q = Global_Data.av.i_q_ref;
   	i_xy_reference.d = 0;
   	i_xy_reference.q = 0;

    //Take measurements independent of control_state
        //Read out speed&position
        Global_Data.av.theta_elec = Global_Data.av.theta_elec - theta_offset;
        Global_Data.av.omega_mech = (Global_Data.av.mechanicalRotorSpeed / 60.0f) * (2.0f * UZ_PIf);
        Global_Data.av.omega_elec = Global_Data.av.omega_mech * polepairs;

        //read pu IP currents
		Global_Data.av.i_c1_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out0_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
		Global_Data.av.i_b1_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out1_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
		Global_Data.av.i_a1_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out2_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
		Global_Data.av.i_c2_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out8_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
		Global_Data.av.i_b2_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out9_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
		Global_Data.av.i_a2_pu = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out10_AXI_Data_uz_pu_con_ip, fixedpoint_definition);

		//read pu IP speed
		Global_Data.av.omega_ip = uz_fixedpoint_axi_read(XPAR_PU_OMEGA_M_0_BASEADDR + 0x1FC, omega_fixedpoint_definition);

		//read pu IP voltages
		Global_Data.av.v_dc1_ip = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out3_AXI_Data_uz_pu_con_ip, fixedpoint_definition);
		Global_Data.av.v_dc2_ip = uz_fixedpoint_axi_read(XPAR_PU_CONVERSION_UZ_PU_CON_IP_0_BASEADDR + out11_AXI_Data_uz_pu_con_ip, fixedpoint_definition);

		// read VSD IP
		Global_Data.av.i_alpha_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + alpha_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
		Global_Data.av.i_beta_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + beta_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
		Global_Data.av.i_X_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + x_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
		Global_Data.av.i_Y_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + y_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
		Global_Data.av.i_0p_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + z1_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);
		Global_Data.av.i_0n_ip = uz_fixedpoint_axi_read(XPAR_VSD_6PH_IP_0_BASEADDR + z2_AXI_Data_VSD_6ph_ip, vsd_fixedpoint_definition);

	   //read park transform ip
	   Global_Data.av.i_d_ip = uz_fixedpoint_axi_read(XPAR_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y1_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);
	   Global_Data.av.i_q_ip = uz_fixedpoint_axi_read(XPAR_UZ_PARK_TRANSFORM_IP_0_BASEADDR + y2_AXI_Data_uz_park_transform_ip, park_fixedpoint_definition);

	   //delay compensation ip
	   Global_Data.av.i_d_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x104, delay_fixedpoint_definition);
	   Global_Data.av.i_q_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x108, delay_fixedpoint_definition);
	   Global_Data.av.i_x_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x10C, delay_fixedpoint_definition);
	   Global_Data.av.i_y_delay = uz_fixedpoint_axi_read(XPAR_MPC_DELAY_COMP_0_BASEADDR + 0x110, delay_fixedpoint_definition);

	   //predicted currents ip
	   Global_Data.av.i_d_pred = uz_fixedpoint_axi_read(XPAR_MPC_PREDICTION_0_BASEADDR + 0x104, delay_fixedpoint_definition);
	   Global_Data.av.i_q_pred = uz_fixedpoint_axi_read(XPAR_MPC_PREDICTION_0_BASEADDR + 0x108, delay_fixedpoint_definition);
	   Global_Data.av.i_x_pred = uz_fixedpoint_axi_read(XPAR_MPC_PREDICTION_0_BASEADDR + 0x10C, delay_fixedpoint_definition);
	   Global_Data.av.i_y_pred = uz_fixedpoint_axi_read(XPAR_MPC_PREDICTION_0_BASEADDR + 0x110, delay_fixedpoint_definition);

	   // read pu_voltages_vsd ip
	   Global_Data.av.vd_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x108, pu_volts_vsd_fixedpoint_definition);
	   Global_Data.av.vq_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x10C, pu_volts_vsd_fixedpoint_definition);
	   Global_Data.av.vx_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x110, pu_volts_vsd_fixedpoint_definition);
	   Global_Data.av.vy_pu = uz_fixedpoint_axi_read(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x114, pu_volts_vsd_fixedpoint_definition);

	   // Read out and convert ADC readings to currents in Amps
	   Global_Data.av.i_a1 = Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV_A1 +PHASE_CURRENT_OFFSET_A1;
	   Global_Data.av.i_b1 = Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV_B1 +PHASE_CURRENT_OFFSET_B1;
	   Global_Data.av.i_c1 = Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV_C1 +PHASE_CURRENT_OFFSET_C1;
	   Global_Data.av.i_dc1 = Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
	   Global_Data.av.i_a2 = Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_A2 +PHASE_CURRENT_OFFSET_A2;
	   Global_Data.av.i_b2 = Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_B2 +PHASE_CURRENT_OFFSET_B2;
	   Global_Data.av.i_c2 = Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_C2 +PHASE_CURRENT_OFFSET_C2;
	   Global_Data.av.i_dc2 = Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;

	   // Read out and convert ADC readings to voltages
	   Global_Data.av.v_dc1 = Global_Data.aa.A1.me.ADC_A1 * PHASE_VOLT_CONV;
	   Global_Data.av.v_a1 = Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_A1 +PHASE_VOLT_OFFSET_A1;
	   Global_Data.av.v_b1 = Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_B1 +PHASE_VOLT_OFFSET_B1;
	   Global_Data.av.v_c1 = Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_C1 +PHASE_VOLT_OFFSET_C1;
	   Global_Data.av.v_dc2 = Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
	   Global_Data.av.v_a2 = Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_A2 +PHASE_VOLT_OFFSET_A2;
	   Global_Data.av.v_b2 = Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_B2 +PHASE_VOLT_OFFSET_B2;
	   Global_Data.av.v_c2 = Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_C2 +PHASE_VOLT_OFFSET_C2;

	   // write measured dc_link voltage to pu_voltages ip
	   uz_axi_write_uint32(XPAR_MPC_PU_VOLTAGES_VSD_0_BASEADDR + 0x118, uz_convert_float_to_sfixed(Global_Data.av.v_dc1/base_val.VB, 15));

		//Read out inverter temp
		Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
		Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
		Global_Data.av.temp_VSI_1 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L1,
				Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L2,
				Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L3);
		Global_Data.av.temp_VSI_2 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L1,
				Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L2,
				Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L3);

		// check current limit
		if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {
					//uz_assert(0);
					ultrazohm_state_machine_set_stop(true);
		}

	   // check DC Bus
	   if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {
		   //			uz_assert(0);
					ultrazohm_state_machine_set_stop(true);
	   }
	   // check inverter temp
	   if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG) {
		   uz_assert(0);
	   }


	// write reference values to mpc ip
		uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x100, Global_Data.av.i_d_ref_pu, i_setpoint_isr_fp_def);
		uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x104, Global_Data.av.i_q_ref_pu, i_setpoint_isr_fp_def);
		uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x108, 0/base_val.IB, i_setpoint_isr_fp_def);
		uz_fixedpoint_axi_write(XPAR_MPC_COST_OPT_0_BASEADDR + 0x10C, 0/base_val.IB, i_setpoint_isr_fp_def);

   //write to structs
   REAL_i_abc_meas.a1 = Global_Data.av.i_a1;
   REAL_i_abc_meas.b1 = Global_Data.av.i_b1;
   REAL_i_abc_meas.c1 = Global_Data.av.i_c1;
   REAL_i_abc_meas.a2 = Global_Data.av.i_a2;
   REAL_i_abc_meas.b2 = Global_Data.av.i_b2;
   REAL_i_abc_meas.c2 = Global_Data.av.i_c2;

   // calc u neutral voltage
   switch(NEUTRAL_CONFIG){
   case 1U:{
	u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1 + Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2) / 6.0f;
	u_n2 = u_n1;
	break;
   }
   case 2U:{
	u_n1 = (Global_Data.av.v_a1 + Global_Data.av.v_b1 + Global_Data.av.v_c1)/3.0f;
	u_n2 = (Global_Data.av.v_a2 + Global_Data.av.v_b2 + Global_Data.av.v_c2)/3.0f;
	break;
   }
   default: break;
   }

   // calc phase voltages with neutral voltage
   REAL_v_abc_meas.a1 = Global_Data.av.v_a1 - u_n1;
   REAL_v_abc_meas.b1 = Global_Data.av.v_b1 - u_n1;
   REAL_v_abc_meas.c1 = Global_Data.av.v_c1 - u_n1;
   REAL_v_abc_meas.a2 = Global_Data.av.v_a2 - u_n2;
   REAL_v_abc_meas.b2 = Global_Data.av.v_b2 - u_n2;
   REAL_v_abc_meas.c2 = Global_Data.av.v_c2 - u_n2;

   //VSD-Transformation
   REAL_i_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(REAL_i_abc_meas, Global_Data.av.theta_elec);
   Global_Data.av.I_d = REAL_i_dqxy_meas.d;
   Global_Data.av.I_q = REAL_i_dqxy_meas.q;
   Global_Data.av.I_X = REAL_i_dqxy_meas.x;
   Global_Data.av.I_Y = REAL_i_dqxy_meas.y;

   REAL_v_dqxy_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(REAL_v_abc_meas, Global_Data.av.theta_elec);
   Global_Data.av.U_d = v_dqxy_limited_volts.d;
   Global_Data.av.U_q = v_dqxy_limited_volts.q;
   Global_Data.av.U_X = v_dqxy_limited_volts.x;
   Global_Data.av.U_Y = v_dqxy_limited_volts.y;


   	  platform_state_t current_state=ultrazohm_state_machine_get_state();

   //-----------------------------------------------------------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
   //-------------------------------------------CONTROL---------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
   //-----------------------------------------------------------------------------------------------------------------------------//
       if (current_state==control_state)
       {
    	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    	   uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);

    	    //uz_axi_write_bool(XPAR_MPC_MPC_ENB_0_BASEADDR + 0x17C, true);

           	REAL_i_dq_meas.d = REAL_i_dqxy_meas.d;
           	REAL_i_dq_meas.q = REAL_i_dqxy_meas.q;
           	REAL_i_xy_meas.d = REAL_i_dqxy_meas.x;
           	REAL_i_xy_meas.q = REAL_i_dqxy_meas.y;
           	REAL_i_z1z2_meas.d = REAL_i_dqxy_meas.z1;
           	REAL_i_z1z2_meas.q = REAL_i_dqxy_meas.z2;

            v_dq_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance, i_dq_reference, REAL_i_dq_meas, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
           	v_xy_limited_volts = uz_CurrentControl_sample(Global_Data.objects.CC_xy_instance, i_xy_reference, REAL_i_xy_meas, Global_Data.av.v_dc1, Global_Data.av.omega_elec);

           	v_dqxy_limited_volts.d = v_dq_limited_volts.d;
           	v_dqxy_limited_volts.q = v_dq_limited_volts.q;
           	v_dqxy_limited_volts.x = v_xy_limited_volts.d;
           	v_dqxy_limited_volts.y = v_xy_limited_volts.q;
           	v_dqxy_limited_volts.z1 = 0.0f;
           	v_dqxy_limited_volts.z2 = 0.0f;
           	REAL_v_abc_ref = uz_transformation_asym30deg_6ph_dq_xy_to_abc(v_dqxy_limited_volts, Global_Data.av.theta_elec);
           	DutyCycle_output = uz_spwm_abc_6ph(REAL_v_abc_ref, V_DC_Volts);
           	Global_Data.rasv.halfBridge1DutyCycle = DutyCycle_output.system1.DutyCycle_A;
           	Global_Data.rasv.halfBridge2DutyCycle = DutyCycle_output.system1.DutyCycle_B;
           	Global_Data.rasv.halfBridge3DutyCycle = DutyCycle_output.system1.DutyCycle_C;
           	Global_Data.rasv.halfBridge4DutyCycle = DutyCycle_output.system2.DutyCycle_A;
           	Global_Data.rasv.halfBridge5DutyCycle = DutyCycle_output.system2.DutyCycle_B;
           	Global_Data.rasv.halfBridge6DutyCycle = DutyCycle_output.system2.DutyCycle_C;

	}

       else {
		   // uz_axi_write_bool(XPAR_MPC_MPC_ENB_0_BASEADDR + 0x17C, false);
		    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
		    uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
			uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance);
			uz_CurrentControl_reset(Global_Data.objects.CC_xy_instance);
			ext_clamping_dq = false;
			ext_clamping_xy = false;
			v_dq_limited_volts.d = 0.0f;
			v_dq_limited_volts.q = 0.0f;
			v_xy_limited_volts.d = 0.0f;
			v_xy_limited_volts.q = 0.0f;
			i_dqxy_integrated_error.d = 0.0f;
			i_dqxy_integrated_error.q = 0.0f;
			i_dqxy_integrated_error.x = 0.0f;
			i_dqxy_integrated_error.y = 0.0f;
			Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
			Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
	}


    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);


    JavaScope_update(&Global_Data);
    // Read the timer value at the very end of the ISR to minimize measurement error
    // This has to be the last function executed in the ISR!
    uz_SystemTime_ISR_Toc();

}


static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3){
    float output;
    output = H1;
    if(L1 > output){
    	output = L1;
    }
    if(H2 > output){
       	output = H2;
    }
    if(L2 > output){
       	output = L2;
    }
    if(H3 > output){
       	output = H3;
    }
    if(L3 > output){
       	output = L3;
    }
    return output;
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
    Status = Rpu_GicInit(&INTCInst, INTERRUPT_ID_SCUG);
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
// Rpu_GicInit() - This function initializes RPU GIC and connects
// 					interrupts with the associated handlers
// @IntcInstPtr		Pointer to the GIC instance
// @IntId			Interrupt ID to be connected and enabled
// @Handler			Associated handler for the Interrupt ID
// @PeriphInstPtr	Connected interrupt's Peripheral instance pointer
//----------------------------------------------------
int Rpu_GicInit(XScuGic *IntcInstPtr, u16 DeviceId)
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
