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
#include "../uz/uz_spwm/uz_spwm.h"
#include "../uz/uz_Space_Vector_Modulation_6ph/uz_Space_Vector_Modulation_6ph.h"

// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;

static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);


//Offset from Valentin
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
#define PHASE_CURRENT_OFFSET_C1	-0.1f
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
#define MAX_PHASE_CURRENT_AMP  15.0f
#define MAX_PHASE_CURRENT_LAST_AMP 30.0f
#define MAX_DC_VOLT 50.0f
#define MAX_TEMP_DEG 90.0f



enum ControllerApplication ConApplication;
enum ControllerSelection ConSelection;

platform_state_t current_state;

bool ext_clamping = false;

float ts = 1.0f/UZ_PWM_FREQUENCY;
float Observation[17] = {0};

//Stepprofile stuff
extern bool StepProfile;
bool start_angle_found = false;
bool change_speed = false;
uint64_t old_uptime=0U;
uint32_t setpoint_index=0U;
float id_setpoints[50]={
#include "id_setpoints_50.csv"
};
float iq_setpoints[50]={
#include "iq_setpoints_50.csv"
};
float ix_setpoints[50]={
#include "ix_setpoints_50.csv"
};
float iy_setpoints[50]={
#include "iy_setpoints_50.csv"
};
//====================
//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
static float TEMP_VSI_largest(float H1, float L1, float H2, float L2, float H3, float L3);
void ISR_Control(void *data)
{

    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();

    switch(ConApplication) {
    case CIL:
    	uz_pmsmModel_6ph_dqxy_trigger_input_strobe(Global_Data.objects.pmsm_model);
    	uz_pmsmModel_6ph_dqxy_trigger_output_strobe(Global_Data.objects.pmsm_model);
    	Global_Data.av.pmsm_outputs 		= uz_pmsmModel_6ph_dqxy_get_outputs(Global_Data.objects.pmsm_model);
    	Global_Data.av.i_dqxy.d 			= Global_Data.av.pmsm_outputs.i_d_A;
    	Global_Data.av.i_dqxy.q 			= Global_Data.av.pmsm_outputs.i_q_A;
    	Global_Data.av.i_dqxy.x 			= Global_Data.av.pmsm_outputs.i_x_A;
    	Global_Data.av.i_dqxy.y 			= Global_Data.av.pmsm_outputs.i_y_A;
    	Global_Data.av.omega_mech 			= Global_Data.av.pmsm_outputs.omega_mech_1_s;
    	Global_Data.av.mechanicalRotorSpeed = Global_Data.av.omega_mech * 30.0f / UZ_PIf;
    	Global_Data.av.omega_elec 			= Global_Data.av.omega_mech * Global_Data.av.pmsm_config_Pruef_dq.polePairs;
    	Global_Data.av.v_dc1				= Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
    	break;

    case REAL:
    	Global_Data.av.resolver_outputs_d4_Last = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Last);
    	Global_Data.av.resolver_outputs_d4_Pruef = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Pruef);
    	Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
    	Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
    	Global_Data.av.inverter_outputs_d3 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d3);

        // Read out and convert ADC readings to currents in Amps
        Global_Data.av.i_abc.a1 	= Global_Data.aa.A1.me.ADC_A4 * PHASE_CURRENT_CONV_A1 +PHASE_CURRENT_OFFSET_A1;
        Global_Data.av.i_abc.b1 	= Global_Data.aa.A1.me.ADC_A3 * PHASE_CURRENT_CONV_B1 +PHASE_CURRENT_OFFSET_B1;
        Global_Data.av.i_abc.c1 	= Global_Data.aa.A1.me.ADC_A2 * PHASE_CURRENT_CONV_C1 +PHASE_CURRENT_OFFSET_C1;
        Global_Data.av.i_dc1 		= Global_Data.aa.A1.me.ADC_B5 * PHASE_CURRENT_CONV;
        Global_Data.av.i_abc.a2 	= Global_Data.aa.A2.me.ADC_A4 * PHASE_CURRENT_CONV_A2 +PHASE_CURRENT_OFFSET_A2;
        Global_Data.av.i_abc.b2 	= Global_Data.aa.A2.me.ADC_A3 * PHASE_CURRENT_CONV_B2 +PHASE_CURRENT_OFFSET_B2;
        Global_Data.av.i_abc.c2 	= Global_Data.aa.A2.me.ADC_A2 * PHASE_CURRENT_CONV_C2 +PHASE_CURRENT_OFFSET_C2;
        Global_Data.av.i_dc2 		= Global_Data.aa.A2.me.ADC_B5 * PHASE_CURRENT_CONV;
        Global_Data.av.i_abc_Last.a = Global_Data.aa.A3.me.ADC_A4 * PHASE_CURRENT_CONV_A2 +PHASE_CURRENT_OFFSET_A2;
        Global_Data.av.i_abc_Last.b = Global_Data.aa.A3.me.ADC_A3 * PHASE_CURRENT_CONV_B2 +PHASE_CURRENT_OFFSET_B2;
        Global_Data.av.i_abc_Last.c = Global_Data.aa.A3.me.ADC_A2 * PHASE_CURRENT_CONV_C2 +PHASE_CURRENT_OFFSET_C2;
        Global_Data.av.i_dc_Last 	= Global_Data.aa.A3.me.ADC_B5 * PHASE_CURRENT_CONV;

        // Read out and convert ADC readings to voltages
        Global_Data.av.v_dc1 		= Global_Data.aa.A1.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_abc.a1 	= Global_Data.aa.A1.me.ADC_B8 * PHASE_VOLT_CONV_A1 +PHASE_VOLT_OFFSET_A1;
        Global_Data.av.v_abc.b1 	= Global_Data.aa.A1.me.ADC_B7 * PHASE_VOLT_CONV_B1 +PHASE_VOLT_OFFSET_B1;
        Global_Data.av.v_abc.c1 	= Global_Data.aa.A1.me.ADC_B6 * PHASE_VOLT_CONV_C1 +PHASE_VOLT_OFFSET_C1;
        Global_Data.av.v_dc2 		= Global_Data.aa.A2.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_abc.a2 	= Global_Data.aa.A2.me.ADC_B8 * PHASE_VOLT_CONV_A2 +PHASE_VOLT_OFFSET_A2;
        Global_Data.av.v_abc.b2 	= Global_Data.aa.A2.me.ADC_B7 * PHASE_VOLT_CONV_B2 +PHASE_VOLT_OFFSET_B2;
        Global_Data.av.v_abc.c2 	= Global_Data.aa.A2.me.ADC_B6 * PHASE_VOLT_CONV_C2 +PHASE_VOLT_OFFSET_C2;
        Global_Data.av.v_dc_Last 	= Global_Data.aa.A3.me.ADC_A1 * PHASE_VOLT_CONV;
        Global_Data.av.v_abc_Last.a = Global_Data.aa.A3.me.ADC_B8 * PHASE_VOLT_CONV_A2 +PHASE_VOLT_OFFSET_A2;
        Global_Data.av.v_abc_Last.b = Global_Data.aa.A3.me.ADC_B7 * PHASE_VOLT_CONV_B2 +PHASE_VOLT_OFFSET_B2;
        Global_Data.av.v_abc_Last.c = Global_Data.aa.A3.me.ADC_B6 * PHASE_VOLT_CONV_C2 +PHASE_VOLT_OFFSET_C2;

        //Read out inverter temp
        Global_Data.av.temp_VSI_1 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L1,
        		Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L2,
				Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d1.ChipTempDegreesCelsius_L3);
        Global_Data.av.temp_VSI_2 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L1,
        		Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L2,
           			Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d2.ChipTempDegreesCelsius_L3);
        Global_Data.av.temp_VSI_3 = TEMP_VSI_largest(Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_H1, Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_L1,
        		Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_H2, Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_L2,
				Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_H3, Global_Data.av.inverter_outputs_d3.ChipTempDegreesCelsius_L3);

        // check current limit
        if(fabs(Global_Data.av.i_abc.a1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc.b1) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc.c1) > MAX_PHASE_CURRENT_AMP ||
        		fabs(Global_Data.av.i_abc.a2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc.b2) > MAX_PHASE_CURRENT_AMP || fabs(Global_Data.av.i_abc.c2) > MAX_PHASE_CURRENT_AMP||
				fabs(Global_Data.av.i_abc_Last.a) > MAX_PHASE_CURRENT_LAST_AMP || fabs(Global_Data.av.i_abc_Last.b) > MAX_PHASE_CURRENT_LAST_AMP || fabs(Global_Data.av.i_abc_Last.c) > MAX_PHASE_CURRENT_LAST_AMP) {
        		ultrazohm_state_machine_set_stop(true);
        		Global_Data.av.error = 1;
                }
        // check DC Bus
        if(fabs(Global_Data.av.v_dc1) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc2) > MAX_DC_VOLT || fabs(Global_Data.av.v_dc_Last) > MAX_DC_VOLT) {
        	ultrazohm_state_machine_set_stop(true);
        	Global_Data.av.error = 2;
        }
        // check inverter temp
        if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG || fabs(Global_Data.av.temp_VSI_3) > MAX_TEMP_DEG) {
     	   ultrazohm_state_machine_set_stop(true);
     	  Global_Data.av.error = 3;
        }

        //Angle
        Global_Data.av.theta_elec 					= Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi;
        Global_Data.av.theta_mech 					= Global_Data.av.resolver_outputs_d4_Pruef.position_mech_2pi;
        Global_Data.av.omega_mech 					= Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s;
        Global_Data.av.omega_elec 					= Global_Data.av.omega_mech * Global_Data.av.pmsm_config_Pruef_dq.polePairs;
        Global_Data.av.theta_elec_Last 				= Global_Data.av.resolver_outputs_d4_Last.position_el_2pi;
        Global_Data.av.theta_mech_Last 				= Global_Data.av.resolver_outputs_d4_Last.position_mech_2pi;
        Global_Data.av.omega_mech_Last 				= Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s;
        Global_Data.av.omega_elec_Last 				= Global_Data.av.omega_mech_Last * Global_Data.av.pmsm_config_Pruef_dq.polePairs;
        Global_Data.av.theta_elec_advanced 			= Global_Data.av.theta_elec + ((1.5f * Global_Data.av.omega_elec) / UZ_PWM_FREQUENCY);
        Global_Data.av.mechanicalRotorSpeed 		= Global_Data.av.omega_mech * 30.0f / UZ_PIf;
        Global_Data.av.mechanicalRotorSpeed_Last 	= Global_Data.av.omega_mech_Last * 30.0f / UZ_PIf;

        //VSD-Transformation
        Global_Data.av.i_dqxy = uz_transformation_asym30deg_6ph_abc_to_dq_xy(Global_Data.av.i_abc, Global_Data.av.theta_elec, (-1.0f * Global_Data.av.theta_elec));
        Global_Data.av.v_dqxy = uz_transformation_asym30deg_6ph_abc_to_dq_xy(Global_Data.av.v_abc, Global_Data.av.theta_elec, (-1.0f * Global_Data.av.theta_elec));

        //dq-Transformation
        Global_Data.av.i_dq_Last = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_Last, Global_Data.av.theta_elec_Last);
        Global_Data.av.v_dq_Last = uz_transformation_3ph_abc_to_dq(Global_Data.av.v_abc_Last, Global_Data.av.theta_elec_Last);


    	break;
    default:
    	break;
    }
 	current_state = ultrazohm_state_machine_get_state();


    // if "STOP"
    if (current_state==idle_state)
    {
    	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance_Pruef);
    	uz_CurrentControl_reset(Global_Data.objects.CC_xy_instance_Pruef);
    	uz_CurrentControl_reset(Global_Data.objects.CC_dq_instance_Last);
    	uz_SpeedControl_reset(Global_Data.objects.speed_ctrl_Last);
    	StepProfile = false;
    	change_speed = false;
    	setpoint_index = 0U;
    	start_angle_found = false;
    	Global_Data.av.n_ref_Last = 0.0f;
    	Global_Data.av.i_dqxy_integrated_error.d = 0.0f;
    	Global_Data.av.i_dqxy_integrated_error.q = 0.0f;
    	Global_Data.av.i_dqxy_integrated_error.x = 0.0f;
    	Global_Data.av.i_dqxy_integrated_error.y = 0.0f;
    	switch(ConApplication) {
    	    case CIL:
    	    	uz_pmsmModel_6ph_dqxy_reset(Global_Data.objects.pmsm_model);
    	    	break;

    	    case REAL:
    	    	// disable inverters
    	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
    	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);

    	    	// write zero dutycycle
    	    	Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge6DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
    	    	Global_Data.rasv.halfBridge9DutyCycle = 0.0f;
    	    	break;

    	    default:
    	    	break;
    	}
    }

   // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
    	switch(ConApplication) {
    	    case CIL:
    	    	//CODE
    	    	break;

    	    case REAL:
    	    	Global_Data.av.error = 0;
    	    	// disable inverters
    	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);
    	    	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);

    	    	break;

    	    default:
    	    	break;
    	}
    }

    // if "ENABLE CONTROL"
    if (current_state==control_state) {
        //Automatic evaluation profile
        if( (StepProfile) ){
        	uint64_t current_uptime=uz_SystemTime_GetInterruptCounter();
        	if (((((Global_Data.av.theta_elec_old - Global_Data.av.theta_elec) > UZ_PIf) || (Global_Data.av.mechanicalRotorSpeed < 10.0f)) || ConApplication==CIL)&& (!start_angle_found)) {
        		if(current_uptime>(old_uptime + 4360)) {
        			start_angle_found = true;
        			old_uptime=current_uptime;
        		}
        	}
        	if (start_angle_found) {
        		// step throught the array
#if DEPENGINE==1
        		if((current_uptime>(old_uptime + 140) && (!change_speed)) ){
#else
        		if((current_uptime>(old_uptime + 36) && (!change_speed)) ){
#endif
        			old_uptime=current_uptime;
        			Global_Data.av.start_marker=1.0f;
            		Global_Data.av.i_dqxy_ref.d=id_setpoints[setpoint_index] * Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
            		Global_Data.av.i_dqxy_ref.q=iq_setpoints[setpoint_index] * Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
            		Global_Data.av.i_dqxy_ref.x=ix_setpoints[setpoint_index] * Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
            		Global_Data.av.i_dqxy_ref.y=iy_setpoints[setpoint_index] * Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
        			if(setpoint_index<50){
        				setpoint_index++;
        			}else{
        				setpoint_index = 0U;
        				Global_Data.av.start_marker = 0.0f;
        				change_speed = true;
        			}

        		}
        		if (change_speed) {
    				Global_Data.av.i_dqxy_ref.d = 0.0f;
    				Global_Data.av.i_dqxy_ref.q = 0.0f;
    				Global_Data.av.i_dqxy_ref.x = 0.0f;
    				Global_Data.av.i_dqxy_ref.y = 0.0f;
        			if(current_uptime>(old_uptime + 360)) {
        				if(ConApplication == CIL) {
        					Global_Data.av.n_ref_Last = Global_Data.av.n_ref_Last + 100.0f;
        				} else {
        					Global_Data.av.n_ref_Last = Global_Data.av.n_ref_Last - 100.0f;
        				}
        				change_speed = false;
        				start_angle_found = false;
        				//StepProfile = false;
        			}
        		}
        		if(fabs(Global_Data.av.n_ref_Last) > Global_Data.av.pmsm_config_Pruef_dq.n_rated_rpm) {
        			StepProfile = false;
        			Global_Data.av.n_ref_Last = 0.0f;
    				Global_Data.av.i_dqxy_ref.d = 0.0f;
    				Global_Data.av.i_dqxy_ref.q = 0.0f;
    				Global_Data.av.i_dqxy_ref.x = 0.0f;
    				Global_Data.av.i_dqxy_ref.y = 0.0f;
        		}
        	}

        }
        Global_Data.av.theta_elec_old = Global_Data.av.theta_elec;
    	if(ConApplication == REAL && ConSelection != manual) {
    		//Only use load machine when REAL
    	    float n_ref_Last_filtered = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_prefilter_Last, Global_Data.av.n_ref_Last);
    	    //Approximates required torque based on dq-Setpoints of DUT machine
    	    Global_Data.av.M_vor_Last = 3.0f * Global_Data.av.pmsm_config_Pruef_dq.polePairs * (Global_Data.av.pmsm_config_Pruef_dq.Psi_PM_Vs * Global_Data.av.i_dqxy_ref.q +
    	    		(Global_Data.av.pmsm_config_Pruef_dq.Ld_Henry - Global_Data.av.pmsm_config_Pruef_dq.Lq_Henry) * Global_Data.av.i_dqxy_ref.q * Global_Data.av.i_dqxy_ref.d);
    	    Global_Data.av.M_ref_Last = uz_SpeedControl_sample(Global_Data.objects.speed_ctrl_Last, Global_Data.av.omega_mech_Last, n_ref_Last_filtered);
    	    Global_Data.av.M_ref_Last += Global_Data.av.M_vor_Last;
    	    Global_Data.av.i_dq_Last_ref = uz_SetPoint_sample(Global_Data.objects.setpoint_ctrl_Last, Global_Data.av.omega_mech_Last, Global_Data.av.M_ref_Last, Global_Data.av.v_dc_Last, Global_Data.av.i_dq_Last);
    	    Global_Data.av.v_dq_Last_ref = uz_CurrentControl_sample(Global_Data.objects.CC_dq_instance_Last, Global_Data.av.i_dq_Last_ref, Global_Data.av.i_dq_Last, Global_Data.av.v_dc_Last, Global_Data.av.omega_elec_Last);
    	    Global_Data.av.DutyCycle_Last = uz_Space_Vector_Modulation(Global_Data.av.v_dq_Last_ref, Global_Data.av.v_dc_Last, Global_Data.av.theta_elec_Last);
    	    Global_Data.rasv.halfBridge7DutyCycle = Global_Data.av.DutyCycle_Last.DutyCycle_A;
    	    Global_Data.rasv.halfBridge8DutyCycle = Global_Data.av.DutyCycle_Last.DutyCycle_B;
    	    Global_Data.rasv.halfBridge9DutyCycle = Global_Data.av.DutyCycle_Last.DutyCycle_C;
    	}
    	switch(ConSelection) {
    	case CC_FOC:
    		uz_3ph_dq_t i_dq_ref = {0};
    		uz_3ph_dq_t i_dq = {0};
    		uz_3ph_dq_t i_xy_ref = {0};
    		uz_3ph_dq_t i_xy = {0};
    		i_dq.d		= Global_Data.av.i_dqxy.d;
    		i_dq.q		= Global_Data.av.i_dqxy.q;
    		i_xy.d		= Global_Data.av.i_dqxy.x;
    		i_xy.q		= Global_Data.av.i_dqxy.y;
    		i_dq_ref.d 	= Global_Data.av.i_dqxy_ref.d;
    		i_dq_ref.q 	= Global_Data.av.i_dqxy_ref.q;
    		i_xy_ref.d 	= Global_Data.av.i_dqxy_ref.x;
    		i_xy_ref.q 	= Global_Data.av.i_dqxy_ref.y;
    		uz_3ph_dq_t v_dq_non_limited = uz_CurrentControl_sample_no_Limit(Global_Data.objects.CC_dq_instance_Pruef, i_dq_ref, i_dq, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
    		uz_3ph_dq_t v_xy_non_limited = uz_CurrentControl_xy_sample_no_Limit(Global_Data.objects.CC_xy_instance_Pruef, i_xy_ref, i_xy, Global_Data.av.v_dc1, Global_Data.av.omega_elec);
    		Global_Data.av.v_dqxy_non_limited.d = v_dq_non_limited.d;
    		Global_Data.av.v_dqxy_non_limited.q = v_dq_non_limited.q;
    		Global_Data.av.v_dqxy_non_limited.x = v_xy_non_limited.d;
    		Global_Data.av.v_dqxy_non_limited.y = v_xy_non_limited.q;
    		Global_Data.av.v_dqxy_ref = uz_6ph_Space_Vector_Limitation(Global_Data.av.v_dqxy_non_limited, Global_Data.av.v_dc1, 0.5f, Global_Data.av.omega_elec, Global_Data.av.i_dqxy_ref, &ext_clamping);
	    	Global_Data.av.v_abc_ref =  uz_transformation_asym30deg_6ph_dq_xy_to_abc(Global_Data.av.v_dqxy_ref, Global_Data.av.theta_elec_advanced, (-1.0f * Global_Data.av.theta_elec_advanced));
	    	Global_Data.av.DutyCycle = uz_spwm_abc_6ph(Global_Data.av.v_abc_ref, Global_Data.av.v_dc1);
    		break;

    	case RL:
    		if(ext_clamping == false) {
    			Global_Data.av.i_dqxy_integrated_error.d = (Global_Data.av.i_dqxy_integrated_error.d + (Global_Data.av.i_dqxy_error.d * ts)); // use Forward-Euler with error of previous timestep for integration
    			Global_Data.av.i_dqxy_integrated_error.q = (Global_Data.av.i_dqxy_integrated_error.q + (Global_Data.av.i_dqxy_error.q * ts));
    			Global_Data.av.i_dqxy_integrated_error.x = (Global_Data.av.i_dqxy_integrated_error.x + (Global_Data.av.i_dqxy_error.x * ts));
    			Global_Data.av.i_dqxy_integrated_error.y = (Global_Data.av.i_dqxy_integrated_error.y + (Global_Data.av.i_dqxy_error.y * ts));
    		} else {
    			Global_Data.av.i_dqxy_integrated_error.d += 0.0f;
    			Global_Data.av.i_dqxy_integrated_error.q += 0.0f;
    			Global_Data.av.i_dqxy_integrated_error.x += 0.0f;
    			Global_Data.av.i_dqxy_integrated_error.y += 0.0f;
    		}
    		Global_Data.av.i_dqxy_error.d = (Global_Data.av.i_dqxy_ref.d - Global_Data.av.i_dqxy.d) / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
    		Global_Data.av.i_dqxy_error.q = (Global_Data.av.i_dqxy_ref.q - Global_Data.av.i_dqxy.q) / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
    		Global_Data.av.i_dqxy_error.x = (Global_Data.av.i_dqxy_ref.x - Global_Data.av.i_dqxy.x) / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
    		Global_Data.av.i_dqxy_error.y = (Global_Data.av.i_dqxy_ref.y - Global_Data.av.i_dqxy.y) / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
       		Observation[0] = Global_Data.av.i_dqxy_error.d;
       		Observation[1] = Global_Data.av.i_dqxy_integrated_error.d * UZ_PWM_FREQUENCY;
       		Observation[2] = Global_Data.av.i_dqxy_error.q;
       		Observation[3] = Global_Data.av.i_dqxy_integrated_error.q * UZ_PWM_FREQUENCY;
       		Observation[4] = Global_Data.av.i_dqxy.d / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
       		Observation[5] = Global_Data.av.i_dqxy.q / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
       		Observation[6] = Global_Data.av.mechanicalRotorSpeed / Global_Data.av.pmsm_config_Pruef_dq.n_rated_rpm;
#if DEPENGINE==1
       		Observation[7] = Global_Data.av.v_dqxy_ref.d * 2.0f / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
       		Observation[8] = Global_Data.av.v_dqxy_ref.q * 2.0f / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
#else
       		Observation[7] = Global_Data.av.v_dqxy_ref.d * sqrtf(3) / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
       		Observation[8] = Global_Data.av.v_dqxy_ref.q * sqrtf(3) / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
#endif
       		Observation[9] = Global_Data.av.i_dqxy_error.x;
       		Observation[10] = Global_Data.av.i_dqxy_integrated_error.x * UZ_PWM_FREQUENCY;
       		Observation[11] = Global_Data.av.i_dqxy_error.y;
       		Observation[12] = Global_Data.av.i_dqxy_integrated_error.y * UZ_PWM_FREQUENCY;
       		Observation[13] = Global_Data.av.i_dqxy.x / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
       		Observation[14] = Global_Data.av.i_dqxy.y / Global_Data.av.pmsm_config_Pruef_dq.I_rated_Ampere;
#if DEPENGINE==1
       		Observation[15] = Global_Data.av.v_dqxy_ref.x * 2.0f / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
       		Observation[16] = Global_Data.av.v_dqxy_ref.y * 2.0f / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
#else
       		Observation[15] = Global_Data.av.v_dqxy_ref.x * sqrtf(3) / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
       		Observation[16] = Global_Data.av.v_dqxy_ref.y * sqrtf(3) / Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts;
#endif
       		for (uint32_t i = 0; i < 17; i++) {
       			uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_acc,Observation[i],0U,i);
       		}
            uz_NN_acc_ff_blocking(Global_Data.objects.NN_acc_Instance);
            //May need adjusting
#if DEPENGINE==1
            uz_matrix_multiply_by_scalar(Global_Data.objects.matrix_output_acc,Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts/sqrtf(3.0f)); // scaling layer of nn
#else
            uz_matrix_multiply_by_scalar(Global_Data.objects.matrix_output_acc,Global_Data.av.pmsm_config_Pruef_dq.V_DC_Volts/2.0f); // scaling layer of nn
#endif
            Global_Data.av.v_dqxy_non_limited.d = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,0U);
            Global_Data.av.v_dqxy_non_limited.q = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,1U);
            Global_Data.av.v_dqxy_non_limited.x = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,2U);
            Global_Data.av.v_dqxy_non_limited.y = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,3U);
            Global_Data.av.v_dqxy_ref = uz_6ph_Space_Vector_Limitation(Global_Data.av.v_dqxy_non_limited, Global_Data.av.v_dc1, 0.57735f, Global_Data.av.omega_elec, Global_Data.av.i_dqxy_ref, &ext_clamping);
	    	Global_Data.av.v_abc_ref =  uz_transformation_asym30deg_6ph_dq_xy_to_abc(Global_Data.av.v_dqxy_ref, Global_Data.av.theta_elec_advanced, (-1.0f * Global_Data.av.theta_elec_advanced));
	    	Global_Data.av.DutyCycle = uz_spwm_abc_6ph(Global_Data.av.v_abc_ref, Global_Data.av.v_dc1);
            break;

    	case MPC:
    		break;

    	case manual:
    		//Give DutyCycles of load machine manual via GUI
    		//Disable inverter of load machine
    		//uz_PWM_SS_2L_set_tristate(Global_Data.objects.pwm_d1_pin_12_to_17, true, true, true);
    		break;
    	}

    	switch(ConApplication) {
    		case CIL:
    	    	Global_Data.av.pmsm_inputs.v_d_V = Global_Data.av.v_dqxy_ref.d;
    	    	Global_Data.av.pmsm_inputs.v_q_V = Global_Data.av.v_dqxy_ref.q;
    	    	Global_Data.av.pmsm_inputs.v_x_V = Global_Data.av.v_dqxy_ref.x;
    	    	Global_Data.av.pmsm_inputs.v_y_V = Global_Data.av.v_dqxy_ref.y;
    	    	Global_Data.av.pmsm_inputs.omega_mech_1_s = Global_Data.av.n_ref_Last / 30.0f * UZ_PIf;
    	    	uz_pmsmModel_6ph_dqxy_set_inputs(Global_Data.objects.pmsm_model, Global_Data.av.pmsm_inputs);
    	    	break;

    	    case REAL:

    	    	Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.DutyCycle.system1.DutyCycle_A;
    	        Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.DutyCycle.system1.DutyCycle_B;
    	        Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.DutyCycle.system1.DutyCycle_C;
    	        Global_Data.rasv.halfBridge4DutyCycle = Global_Data.av.DutyCycle.system2.DutyCycle_A;
    	        Global_Data.rasv.halfBridge5DutyCycle = Global_Data.av.DutyCycle.system2.DutyCycle_B;
    	        Global_Data.rasv.halfBridge6DutyCycle = Global_Data.av.DutyCycle.system2.DutyCycle_C;
    	    	break;

    	    default:
    	    	break;
    	    }
    }

    // assign DutyCycles lastmaschine
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);

    // assign Duty Cycles pruef
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
    Status = Rpu_GicInit(&GIC_instance, INTERRUPT_ID_SCUG);
    if (Status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: GIC initialization failed\r\n");
        return XST_FAILURE;
    }

    // Enable interrupt on CPU level
    Xil_ExceptionEnable();

    return Status;
}


/**
 * @brief Initialize the R5 GIC and connect/enable the PL-to-PS interrupt used by the RPU.
 *
 * @param[in,out] GIC_instance_ptr Pointer to an XScuGic instance to initialize.
 * @param[in]     DeviceId    GIC device ID (typically XPAR_SCUGIC_0_DEVICE_ID).
 *
 * @return XST_SUCCESS on success. This implementation asserts on failures.
 */
int Rpu_GicInit(XScuGic *GIC_instance_ptr, u16 DeviceId)
{
    XScuGic_Config *GIC_config;
    int status;

    // Disable all interrupts
    Xil_ExceptionDisable();

    GIC_config = XScuGic_LookupConfig(DeviceId);

    uz_assert_not_NULL(GIC_config);

    status = XScuGic_CfgInitialize(GIC_instance_ptr, GIC_config, GIC_config->CpuBaseAddress);
	uz_assert(status == XST_SUCCESS);

    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, GIC_instance_ptr);

    // Clear latched active interrupt register - for UZ warm start
    uz_r5_gic_reset_active_pl_interrupts(GIC_instance_ptr);

    // Configure trigger/priority
    // XScuGic_SetPriorityTriggerType(XScuGic *InstancePtr, u32 Int_Id, u8 Priority, u8 Trigger)
    XScuGic_SetPriorityTriggerType(GIC_instance_ptr, Interrupt_ISR_ID, 0x0, 0b11); // Trigger 0b11 = rising-edge, Trigger 0b01 = active-high

    // Connect handler
    status = XScuGic_Connect(GIC_instance_ptr,
                             Interrupt_ISR_ID,
                             (Xil_ExceptionHandler)ISR_Control,
                             NULL);
	uz_assert(status == XST_SUCCESS);

    // Enable only the connected interrupt
    XScuGic_Enable(GIC_instance_ptr, Interrupt_ISR_ID);

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
    XIpiPsu_Config *IPI_config;
    int status;

    // Interrupt controller configuration
    IPI_config = XIpiPsu_LookupConfig(DeviceId);
    if (IPI_config == NULL)
    {
        xil_printf("RPU: Error: Ipi Init failed\r\n");
        return XST_FAILURE;
    }

    // Interrupt controller initialization
    status = XIpiPsu_CfgInitialize(&IPI_instance, IPI_config, IPI_config->BaseAddress);
    if (status != XST_SUCCESS)
    {
        xil_printf("RPU: Error: IPI Config failed\r\n");
        return XST_FAILURE;
    }

    XIpiPsu_InterruptEnable(&IPI_instance, XPAR_XIPIPS_TARGET_PSU_CORTEXR5_0_CH0_MASK);

    xil_printf("RPU: Rpu_IpiInit: Done\r\n");
    return XST_SUCCESS;
}

static void ReadAllADC()
{
    ADC_readCardALL(&Global_Data);
};




static inline bool uz_gic_is_active_id(XScuGic *Gic, u32 IntId)
{
    /* Active status is in Distributor ACTIVE banked registers */
    const u32 reg = XSCUGIC_EN_DIS_OFFSET_CALC(XSCUGIC_ACTIVE_OFFSET, IntId); /* ACTIVE + (IntId/32)*4 */
    const u32 bit = (u32)1U << (IntId % 32U);

    const u32 act = XScuGic_DistReadReg(Gic, reg);
    return ((act & bit) != 0U);
}


/**
 * @brief Clears stuck ACTIVE PL interrupts by writing GICC_EOIR (End Of Interrupt Register)
 * with the active interrupt ID, to enable soft restart without resetting entire system.
 *
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) <intid>
 *
 * Call during GIC init, before enabling IRQ delivery on the R5.
 *
 */
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic)
{
	// list of all PL Interrupt IDs
	const uint16_t uz_fpga_spi_ids[] = {
	    XPS_FPGA0_INT_ID,  XPS_FPGA1_INT_ID,  XPS_FPGA2_INT_ID,  XPS_FPGA3_INT_ID,
	    XPS_FPGA4_INT_ID,  XPS_FPGA5_INT_ID,  XPS_FPGA6_INT_ID,  XPS_FPGA7_INT_ID,
	    XPS_FPGA8_INT_ID,  XPS_FPGA9_INT_ID,  XPS_FPGA10_INT_ID, XPS_FPGA11_INT_ID,
	    XPS_FPGA12_INT_ID, XPS_FPGA13_INT_ID, XPS_FPGA14_INT_ID, XPS_FPGA15_INT_ID
	};

	uz_assert_not_NULL(Gic);
	uz_assert_not_NULL(Gic->Config);

    // iterate over all PL interrupts
	for (uint32_t i = 0U; i < (uint32_t)(sizeof(uz_fpga_spi_ids)/sizeof(uz_fpga_spi_ids[0])); ++i)
	{
		const uint32_t id = (uint32_t)uz_fpga_spi_ids[i];

		// check if id-interrupt is stuck on active
		if (uz_gic_is_active_id(Gic, id)) {

			/* Writing IntId to EOIR to clear the stuck ACTIVE state */
			XScuGic_CPUWriteReg(Gic, XSCUGIC_EOI_OFFSET, (id & XSCUGIC_EOI_INTID_MASK));
			uz_printf("RPU GIC: Cleared ACTIVE for PL interrupt ID %u\r\n", (unsigned long)id);

		}
    }
}



