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
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_Transformation/uz_Transformation.h"
#include "../uz/uz_spwm/uz_spwm.h"
#include "../uz/uz_math_constants.h"
#include "../include/FOC.h"
#include "../uz/uz_signals/uz_signals.h"
#include "../uz/uz_wavegen/uz_wavegen.h"
#include "../include/encoder.h"
#include "../uz/uz_CurrentControl/uz_space_vector_limitation.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;
extern base_val_t inverse_base_val;


uz_6ph_abc_t six_ph_currents = {0.0f};
uz_6ph_abc_t six_ph_voltages = {0.0f};
uz_6ph_alphabeta_t six_ph_alphabeta = {0.0f};
uz_6ph_alphabeta_t six_ph_alphabeta_volts = {0.0f};
uz_3ph_alphabeta_t three_ph_alphabeta = {0.0f};
uz_3ph_dq_t rotating_dq = {0};
uz_3ph_dq_t rotating_xy = {0};
uz_6ph_dq_t six_ph_dq = {0};
uz_6ph_dq_t six_ph_dq_volts = {0};
uz_6ph_dq_t six_ph_dq_volts_compensated = {0};
uz_6ph_dq_t v_pre_limits_volts = {0.0f};
uz_6ph_dq_t v_post_limits_volts = {0.0f};
uz_6ph_dq_t i_ref_Ampere ={0.0f};
bool dualsvm_clamped = false;

uz_3ph_dq_t i_dq_ref = {0.0f};
uz_3ph_dq_t i_dq_r2_ref = {0.0f};
uz_3ph_dq_t i_dq_actual = {0.0f};
uz_3ph_dq_t i_xy_ref = {0.0f};
uz_3ph_dq_t i_xy_r2_ref = {0.0f};
uz_3ph_dq_t i_xy_r6_ref = {0.0f};
uz_3ph_dq_t i_xy_actual = {0.0f};
uz_3ph_dq_t u_dq_ref = {0.0f};
uz_3ph_dq_t u_dq_r2_ref = {0.0f};
uz_3ph_dq_t u_xy_ref = {0.0f};
uz_3ph_dq_t u_xy_r2_ref = {0.0f};
uz_3ph_dq_t u_xy_r6_ref = {0.0f};
uz_3ph_alphabeta_t alphabeta_ref_volts = {0.0f};
uz_3ph_alphabeta_t XY_ref_volts = {0.0f};
uz_6ph_alphabeta_t vsd_ref_volts = {0.0f};
uz_6ph_abc_t phase_ref_volts = {0.0f};
uz_3ph_abc_t input1 = {0.0f};
uz_3ph_abc_t input2 = {0.0f};
struct uz_DutyCycle_t output1_spwm = {0};
struct uz_DutyCycle_t output2_spwm = {0};
struct uz_DutyCycle_t output1_dualsvm = {0};
struct uz_DutyCycle_t output2_dualsvm = {0};
struct uz_DutyCycle_t output1 = {0};
struct uz_DutyCycle_t output2 = {0};

uz_3ph_dq_t dq_ref_volts_1 = {0.0f};
uz_3ph_dq_t dq_ref_volts_2 = {0.0f};

// Data for determination of mechanical resolver angle
float theta_mech_old=0.0f;
int32_t cnt = 0U;
bool cnt_reset = 0;
float cnt_float=0.0f;
float cnt_reset_float=0.0f;
float theta_m_max = 0.0f;
float theta_m_min = 0.0f;
bool first_ISR = true;
void calc_angle_from_resolver_IP();


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
#define MAX_PHASE_CURRENT_AMP  20.0f
#define MAX_DC_VOLT 590.0f

bool start = false;
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
    update_speed_and_position_of_encoder_on_D3(&Global_Data);
    //get resolver data
//    Global_Data.av.resolver_pl_interface = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_interface);
//    Global_Data.av.theta_elec_rad_ip = Global_Data.av.resolver_pl_interface.position_el_2pi;
//    Global_Data.av.theta_mech_rad_ip = Global_Data.av.resolver_pl_interface.position_mech_2pi;
//    Global_Data.av.mechanicalRotorSpeedRPM_ip = Global_Data.av.resolver_pl_interface.n_mech_rpm;
//    Global_Data.av.mechanicalRotorSpeedRADpS_ip = Global_Data.av.resolver_pl_interface.omega_mech_rad_s;

    //get incremental encoder data
    Global_Data.av.mechanicalRotorSpeedRADpS = Global_Data.av.mechanicalRotorSpeed_incre;
    Global_Data.av.mechanicalRotorSpeedRPM = Global_Data.av.mechanicalRotorSpeedRADpS * 9.54930f; // 9.54930f = 30/pi
    Global_Data.av.electricalRotorSpeedRADpS = Global_Data.av.mechanicalRotorSpeedRADpS*Global_Data.av.polepairs;
  	Global_Data.av.pos_elec = Global_Data.av.theta_elec_incre;

  	//compensate angle delay for FOC and MPC and for the different turning directions of the angle
  	float angle_lead_FOC = Global_Data.av.angle_lead_factor_FOC * Global_Data.av.electricalRotorSpeedRADpS * UZ_TIME_ISR;
  	float angle_lead_MPC = Global_Data.av.angle_lead_factor_MPC * Global_Data.av.electricalRotorSpeedRADpS * UZ_TIME_ISR;

  	Global_Data.av.theta_el_pos_FOC = uz_signals_wrap(Global_Data.av.pos_elec + angle_lead_FOC, 2.0f*UZ_PIf);
  	Global_Data.av.theta_el_pos_MPC = uz_signals_wrap(Global_Data.av.pos_elec + angle_lead_MPC, 2.0f*UZ_PIf);
  	Global_Data.av.theta_el_neg_FOC = uz_signals_wrap(2.0f*UZ_PIf - Global_Data.av.pos_elec - angle_lead_FOC, 2.0f*UZ_PIf);
  	Global_Data.av.theta_el_neg_MPC = uz_signals_wrap(2.0f*UZ_PIf - Global_Data.av.pos_elec - angle_lead_MPC, 2.0f*UZ_PIf);

    //get ADC data
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


    // check current limit
	if(fabs(Global_Data.av.i_a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c1) > MAX_PHASE_CURRENT_AMP ||
			fabs(Global_Data.av.i_a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_c2) > MAX_PHASE_CURRENT_AMP) {
		ultrazohm_state_machine_set_stop(true);
	}

	// check fast fpga current limit violation
	if (uz_axi_read_bool(XPAR_UZ_USER_UZ_CUR_LIM_0_BASEADDR + 0x108) == true) {
		ultrazohm_state_machine_set_stop(true);
		Global_Data.av.overcurrent_FPGA = true;
		Global_Data.av.overcurrent_FPGA_fl = 1.0f;
	} else {
		Global_Data.av.overcurrent_FPGA = false;
		Global_Data.av.overcurrent_FPGA_fl = 0.0f;
	}

	// check DC Bus voltage limit
	if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT) {
			ultrazohm_state_machine_set_stop(true);
	}

	// check inverter fault
//	if(uz_axi_gpio_read_pin_zero_based(Global_Data.objects.inv_fault_in, 0U) == true || uz_axi_gpio_read_pin_zero_based(Global_Data.objects.inv_fault_in, 1U) == true) {
//		ultrazohm_state_machine_set_stop(true);
//	}

    // VSD transform phase currents
    six_ph_currents.a1 = Global_Data.av.i_a1;
    six_ph_currents.b1 = Global_Data.av.i_b1;
    six_ph_currents.c1 = Global_Data.av.i_c1;
    six_ph_currents.a2 = Global_Data.av.i_a2;
    six_ph_currents.b2 = Global_Data.av.i_b2;
    six_ph_currents.c2 = Global_Data.av.i_c2;
    six_ph_alphabeta = uz_transformation_asym30deg_6ph_abc_to_alphabeta(six_ph_currents);

    Global_Data.av.i_alpha = six_ph_alphabeta.alpha;
    Global_Data.av.i_beta = six_ph_alphabeta.beta;
    Global_Data.av.i_X = six_ph_alphabeta.x;
    Global_Data.av.i_Y = six_ph_alphabeta.y;

    // VSD transform phase voltages
    six_ph_voltages.a1 = Global_Data.av.v_a1;
    six_ph_voltages.b1 = Global_Data.av.v_b1;
    six_ph_voltages.c1 = Global_Data.av.v_c1;
    six_ph_voltages.a2 = Global_Data.av.v_a2;
    six_ph_voltages.b2 = Global_Data.av.v_b2;
    six_ph_voltages.c2 = Global_Data.av.v_c2;
    six_ph_alphabeta_volts = uz_transformation_asym30deg_6ph_abc_to_alphabeta(six_ph_voltages);

    // Park transform alpha/beta currents with positive turning, and XY currents with negative turning angle
    six_ph_dq = uz_transformation_asym30deg_6ph_alphabeta_XY_to_dq_xy(six_ph_alphabeta, Global_Data.av.pos_elec, 2*UZ_PIf-Global_Data.av.pos_elec);
    Global_Data.av.i_d = six_ph_dq.d;
    Global_Data.av.i_q = six_ph_dq.q;
    Global_Data.av.i_x = six_ph_dq.x;
    Global_Data.av.i_y = six_ph_dq.y;

    // Park transform alpha/beta voltages with positive turning, and XY voltages with negative turning angle
    six_ph_dq_volts = uz_transformation_asym30deg_6ph_alphabeta_XY_to_dq_xy(six_ph_alphabeta_volts, Global_Data.av.pos_elec, 2*UZ_PIf-Global_Data.av.pos_elec);
    Global_Data.av.v_d = six_ph_dq_volts.d;
    Global_Data.av.v_q = six_ph_dq_volts.q;
    Global_Data.av.v_x = six_ph_dq_volts.x;
    Global_Data.av.v_y = six_ph_dq_volts.y;

    // p.u. convert currents for control
    Global_Data.av.i_d_pu = Global_Data.av.i_d*inverse_base_val.IB;
    Global_Data.av.i_q_pu = Global_Data.av.i_q*inverse_base_val.IB;
    Global_Data.av.i_x_pu = Global_Data.av.i_x*inverse_base_val.IB;
    Global_Data.av.i_y_pu = Global_Data.av.i_y*inverse_base_val.IB;
    Global_Data.av.omega_mech_pu = Global_Data.av.mechanicalRotorSpeedRADpS*inverse_base_val.omegaB;
    Global_Data.av.omega_el_pu = Global_Data.av.electricalRotorSpeedRADpS*inverse_base_val.omegaB;
    Global_Data.av.i_d_ref_pu = Global_Data.av.i_d_ref*inverse_base_val.IB;
    Global_Data.av.i_q_ref_pu = Global_Data.av.i_q_ref*inverse_base_val.IB;
    Global_Data.av.i_x_ref_pu = Global_Data.av.i_x_ref*inverse_base_val.IB;
    Global_Data.av.i_y_ref_pu = Global_Data.av.i_y_ref*inverse_base_val.IB;
    Global_Data.av.v_dc1_pu = Global_Data.av.v_dc1*inverse_base_val.VB;

    // assign to structs
    i_dq_actual.d = Global_Data.av.i_d;
    i_dq_actual.q = Global_Data.av.i_q;
    i_xy_actual.d = Global_Data.av.i_x;
    i_xy_actual.q = Global_Data.av.i_y;

	i_dq_ref.d = Global_Data.av.i_d_ref;
	i_dq_ref.q = Global_Data.av.i_q_ref;
	i_xy_ref.d = Global_Data.av.i_x_ref;
	i_xy_ref.q = Global_Data.av.i_y_ref;




    platform_state_t current_state=ultrazohm_state_machine_get_state();
    if (current_state==idle_state)
    {
    	uz_CurrentControl_reset(Global_Data.objects.foc_current_dq);
    	uz_subspace_resonant_control_reset(Global_Data.objects.resonant_dq2);
		uz_CurrentControl_reset(Global_Data.objects.foc_current_xy);
		uz_subspace_resonant_control_reset(Global_Data.objects.resonant_xy2);
		uz_subspace_resonant_control_reset(Global_Data.objects.resonant_xy6);

    	Global_Data.rasv.halfBridge1DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge2DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge3DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge4DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge5DutyCycle = 0.5f;
    	Global_Data.rasv.halfBridge6DutyCycle = 0.5f;
    }

    if (current_state==control_state)
    {
    	if (Global_Data.rasv.a53_ctrl_off_on == false)
    	{
        // Start: Control algorithm - only if ultrazohm is in control state
//    	Global_Data.av.speed_ref_rpm_filt = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_ref_filt, Global_Data.av.speed_ref_rpm);
//    	Global_Data.av.M_ref = uz_SpeedControl_sample(Global_Data.objects.speed_control, Global_Data.av.mechanicalRotorSpeedRADpS_ip, Global_Data.av.speed_ref_rpm_filt);
//    	i_dq_ref = uz_SetPoint_sample(Global_Data.objects.setpoint, Global_Data.av.mechanicalRotorSpeedRADpS_ip, Global_Data.av.M_ref, Global_Data.av.v_dc1, i_dq_actual);

    	// dq PI current control
    		//ATTENTION: commenteed out SV Linitation in CurrentControl!!!!
    	u_dq_ref = uz_CurrentControl_sample(Global_Data.objects.foc_current_dq, i_dq_ref, i_dq_actual, Global_Data.av.v_dc1, Global_Data.av.electricalRotorSpeedRADpS);
    	Global_Data.av.u_dq_ref = u_dq_ref;


    	// dqxy PI-R CONTROL
    	if (Global_Data.rasv.current_ctrl_select == PI_R_FOC) {
    	// dq R2 current control
    	u_dq_r2_ref = uz_subspace_resonant_control_step_dq(Global_Data.objects.resonant_dq2, i_dq_r2_ref, i_dq_actual, Global_Data.av.electricalRotorSpeedRADpS);
    	// sum up all dq reference voltages
    	Global_Data.av.u_dq_ref.d = u_dq_ref.d + u_dq_r2_ref.d;
    	Global_Data.av.u_dq_ref.q = u_dq_ref.q + u_dq_r2_ref.q;
    	// xy PI current control
    	u_xy_ref = uz_CurrentControl_sample(Global_Data.objects.foc_current_xy, i_xy_ref, i_xy_actual, Global_Data.av.v_dc1, Global_Data.av.electricalRotorSpeedRADpS);
    	// xy R2 current control
    	u_xy_r2_ref = uz_subspace_resonant_control_step_dq(Global_Data.objects.resonant_xy2, i_xy_r2_ref, i_xy_actual, Global_Data.av.electricalRotorSpeedRADpS);
    	// xy R6 current control
    	u_xy_r6_ref = uz_subspace_resonant_control_step_dq(Global_Data.objects.resonant_xy6, i_xy_r6_ref, i_xy_actual, Global_Data.av.electricalRotorSpeedRADpS);
    	// sum up all xy reference voltages
    	Global_Data.av.u_xy_ref.d = u_xy_ref.d + u_xy_r2_ref.d + u_xy_r6_ref.d;
    	Global_Data.av.u_xy_ref.q = u_xy_ref.q + u_xy_r2_ref.q + u_xy_r6_ref.q;

    	//debug
    	Global_Data.av.xy_r6_v_d_ref = u_xy_r6_ref.d;
    	Global_Data.av.xy_r6_v_q_ref = u_xy_r6_ref.q;

    	} else { //no subspace PI-R control
    		uz_CurrentControl_reset(Global_Data.objects.foc_current_xy);
    		uz_subspace_resonant_control_reset(Global_Data.objects.resonant_dq2);
    		uz_subspace_resonant_control_reset(Global_Data.objects.resonant_xy2);
    		uz_subspace_resonant_control_reset(Global_Data.objects.resonant_xy6);
    		vsd_ref_volts.x = 0.0f;
    		vsd_ref_volts.y = 0.0f;
    		Global_Data.av.u_xy_ref.d = 0.0f;
    		Global_Data.av.u_xy_ref.q = 0.0f;
    	}


    	// 6ph space vector limitation
    	v_pre_limits_volts.d = Global_Data.av.u_dq_ref.d;
    	v_pre_limits_volts.q = Global_Data.av.u_dq_ref.q;
    	v_pre_limits_volts.x = Global_Data.av.u_xy_ref.d;
    	v_pre_limits_volts.y = Global_Data.av.u_xy_ref.q;

    	i_ref_Ampere.d = i_dq_ref.d;
    	i_ref_Ampere.q = i_dq_ref.q;
    	i_ref_Ampere.x = i_xy_ref.d;
    	i_ref_Ampere.y = i_xy_ref.q;

    	v_post_limits_volts = uz_6ph_Space_Vector_Limitation(v_pre_limits_volts, Global_Data.av.v_dc1, 0.577350, Global_Data.av.electricalRotorSpeedRADpS, i_ref_Ampere, &dualsvm_clamped);
    	Global_Data.av.dualsvm_clamped = dualsvm_clamped;
    	Global_Data.av.dualsvm_clamped_f = (float)dualsvm_clamped;
    	//my hacky clamping set function to force external clamping of current controllers
    	uz_CurrentControl_set_ext_clamping(Global_Data.objects.foc_current_dq, dualsvm_clamped);
    	uz_CurrentControl_set_ext_clamping(Global_Data.objects.foc_current_xy, dualsvm_clamped);

    	Global_Data.av.u_dq_ref.d = v_post_limits_volts.d;
    	Global_Data.av.u_dq_ref.q = v_post_limits_volts.q;
    	Global_Data.av.u_xy_ref.d = v_post_limits_volts.x;
    	Global_Data.av.u_xy_ref.q = v_post_limits_volts.y;


    	// Transform Ref voltages
    	alphabeta_ref_volts = uz_transformation_3ph_dq_to_alphabeta(Global_Data.av.u_dq_ref, Global_Data.av.theta_el_pos_FOC);
    	vsd_ref_volts.alpha = alphabeta_ref_volts.alpha;
    	vsd_ref_volts.beta = alphabeta_ref_volts.beta;
    	XY_ref_volts = uz_transformation_3ph_dq_to_alphabeta(Global_Data.av.u_xy_ref, Global_Data.av.theta_el_neg_FOC);
    	vsd_ref_volts.x = XY_ref_volts.alpha;
    	vsd_ref_volts.y = XY_ref_volts.beta;

    	phase_ref_volts = uz_transformation_asym30deg_6ph_alphabeta_to_abc(vsd_ref_volts);

    	input1.a = phase_ref_volts.a1;
    	input1.b = phase_ref_volts.b1;
    	input1.c = phase_ref_volts.c1;
    	input2.a = phase_ref_volts.a2;
    	input2.b = phase_ref_volts.b2;
    	input2.c = phase_ref_volts.c2;

    	// Dual SVM
    	dq_ref_volts_1 = uz_transformation_3ph_abc_to_dq(input1, Global_Data.av.theta_el_pos_FOC);
    	dq_ref_volts_2 = uz_transformation_3ph_abc_to_dq(input2, Global_Data.av.theta_el_pos_FOC+0.5235987756f); // +pi/6

    	output1_dualsvm = uz_Space_Vector_Modulation(dq_ref_volts_1, Global_Data.av.v_dc1, Global_Data.av.theta_el_pos_FOC);
    	output2_dualsvm = uz_Space_Vector_Modulation(dq_ref_volts_2, Global_Data.av.v_dc2, Global_Data.av.theta_el_pos_FOC+0.5235987756f);

    	// SPWM
    	output1_spwm = uz_spwm_abc(input1, Global_Data.av.v_dc1);
    	output2_spwm = uz_spwm_abc(input2, Global_Data.av.v_dc2);

    	// SPWM or DualSVM
    	//output1 = output1_spwm;
    	//output2 = output2_spwm;
    	output1 = output1_dualsvm;
    	output2 = output2_dualsvm;

    	} // END if a53_ctrl_off_on

    	if(Global_Data.rasv.current_ctrl_select == IMPL_MOD) {
    		uz_CurrentControl_reset(Global_Data.objects.foc_current_dq);
    		// ATTENTION those are actually 1 minus dutycyc, see javascope.c
    	    Global_Data.rasv.halfBridge1DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[0], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge2DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[1], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge3DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[2], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge4DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[3], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge5DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[4], 1.0f, 0.0f);
    	    Global_Data.rasv.halfBridge6DutyCycle = uz_signals_saturation(Global_Data.av.dutycyc[5], 1.0f, 0.0f);
    		// END ATTENTION

    	} else {
    		Global_Data.rasv.halfBridge1DutyCycle = output1.DutyCycle_A;
    		Global_Data.rasv.halfBridge2DutyCycle = output1.DutyCycle_B;
    		Global_Data.rasv.halfBridge3DutyCycle = output1.DutyCycle_C;
    		Global_Data.rasv.halfBridge4DutyCycle = output2.DutyCycle_A;
    		Global_Data.rasv.halfBridge5DutyCycle = output2.DutyCycle_B;
    		Global_Data.rasv.halfBridge6DutyCycle = output2.DutyCycle_C;
    	}

    }
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);

    JavaScope_update(&Global_Data);
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


float SawTooth(float ampl, float freq, float isr_time)
{
	static uint32_t sample_tick = 1U;
	float sample = 0.0f;

	sample = fmodf(sample_tick*isr_time, 1.0f/freq);
	sample_tick += 1U;
	if(sample_tick > (1.0f/freq/isr_time)) {
		sample_tick = 1U;
	}

	return(ampl*sample*freq);
}
