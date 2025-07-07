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
#include "../include/uz_platform_state_machine.h"
#include "../Codegen/uz_codegen.h"
#include "../include/mux_axi.h"
#include "../IP_Cores/uz_PWM_SS_2L/uz_PWM_SS_2L.h"
#include "../uz/uz_spwm/uz_spwm.h"
#include "../include/isr_support_functions.h"

// Initialize the Interrupt structure
XScuGic INTCInst;     // Interrupt handler -> only instance one -> responsible for ALL interrupts of the GIC!
XIpiPsu INTCInst_IPI; // Interrupt handler -> only instance one -> responsible for ALL interrupts of the IPI!

// Global variable structure
extern DS_Data Global_Data;


// software limits
#define MAX_PHASE_CURRENT_AMP_LAST  16.0f
#define MAX_PHASE_CURRENT_AMP_PRUEF 7.0f
#define MAX_DC_VOLT 50.0f
#define MAX_TEMP_DEG 90.0f

#define NEUTRAL_CONFIG 2U //1U: 1N, 2U: 2N
float u_n1 = 0.0f;
float u_n2 = 0.0f;
float u_n3 = 0.0f;

#define POLPAIRS_6PH_MACHINE 5
#define POLPAIRS_3PH_MACHINE 5

#define RAD_TO_DEG (180.0f/M_PI)


//====================
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
    update_speed_and_position_of_encoder_on_D5(&Global_Data);

    Global_Data.av.resolver_outputs_d4_Pruef = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Pruef);
    Global_Data.av.resolver_outputs_d4_Last = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Last);

    Global_Data.av.theta_el_Last_deg = Global_Data.av.resolver_outputs_d4_Last.position_el_2pi * RAD_TO_DEG;
    Global_Data.av.theta_mech_Last_deg = Global_Data.av.resolver_outputs_d4_Last.position_mech_2pi * RAD_TO_DEG;
    Global_Data.av.theta_el_Pruef_deg = Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi * RAD_TO_DEG;
    Global_Data.av.theta_mech_Pruef_deg = Global_Data.av.resolver_outputs_d4_Pruef.position_mech_2pi * RAD_TO_DEG;

    Global_Data.av.inverter_outputs_d1 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d1);
    Global_Data.av.inverter_outputs_d2 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d2);
    Global_Data.av.inverter_outputs_d3 = uz_inverter_adapter_get_outputs(Global_Data.objects.inverter_d3);


    // Read out and convert ADC readings to currents in Amps
    update_current_measurements(&Global_Data.aa, &Global_Data.av.i_abc_inverter1, &Global_Data.av.i_abc_inverter2, &Global_Data.av.i_abc_inverter3);
    update_dc_current_measurements(&Global_Data.aa, &Global_Data.av.i_dc1, &Global_Data.av.i_dc2, &Global_Data.av.i_dc3);

    // Read out and convert ADC readings to voltages
    update_voltage_measurements(&Global_Data.aa, &Global_Data.av.u_abc_inverter1, &Global_Data.av.u_abc_inverter2, &Global_Data.av.u_abc_inverter3);
    update_dc_voltage_measurements(&Global_Data.aa, &Global_Data.av.u_dc1, &Global_Data.av.u_dc2, &Global_Data.av.u_dc3);

    //Read out inverter temperature
    Global_Data.av.temp_VSI_1 = read_highest_inverter_temperature(&Global_Data.av.inverter_outputs_d1);
    Global_Data.av.temp_VSI_2 = read_highest_inverter_temperature(&Global_Data.av.inverter_outputs_d2);
    Global_Data.av.temp_VSI_3 = read_highest_inverter_temperature(&Global_Data.av.inverter_outputs_d3);


	// check current limit
    if(fabs(Global_Data.av.i_abc_inverter1.a) > MAX_PHASE_CURRENT_AMP_PRUEF || fabs(Global_Data.av.i_abc_inverter1.b) > MAX_PHASE_CURRENT_AMP_PRUEF || fabs(Global_Data.av.i_abc_inverter1.c) > MAX_PHASE_CURRENT_AMP_PRUEF
    || fabs(Global_Data.av.i_abc_inverter2.a) > MAX_PHASE_CURRENT_AMP_PRUEF || fabs(Global_Data.av.i_abc_inverter2.b) > MAX_PHASE_CURRENT_AMP_PRUEF || fabs(Global_Data.av.i_abc_inverter2.c) > MAX_PHASE_CURRENT_AMP_PRUEF
	|| fabs(Global_Data.av.i_abc_inverter3.a) > MAX_PHASE_CURRENT_AMP_LAST || fabs(Global_Data.av.i_abc_inverter3.b) > MAX_PHASE_CURRENT_AMP_LAST || fabs(Global_Data.av.i_abc_inverter3.c) > MAX_PHASE_CURRENT_AMP_LAST)
    {
        ultrazohm_state_machine_set_stop(true);
        Global_Data.av.error = 1;
    }

    // check DC Bus
    if(fabs(Global_Data.av.u_dc1) > MAX_DC_VOLT
    || fabs(Global_Data.av.u_dc2) > MAX_DC_VOLT
	|| fabs(Global_Data.av.u_dc3) > MAX_DC_VOLT)
    {
    	ultrazohm_state_machine_set_stop(true);
    	Global_Data.av.error = 2;
    }

    // check inverter temperature
    if(fabs(Global_Data.av.temp_VSI_1) > MAX_TEMP_DEG
    || fabs(Global_Data.av.temp_VSI_2) > MAX_TEMP_DEG
	|| fabs(Global_Data.av.temp_VSI_3) > MAX_TEMP_DEG)
    {
  	   ultrazohm_state_machine_set_stop(true);
  	   Global_Data.av.error = 3;
    }

    // calculate neutral voltage
    switch(NEUTRAL_CONFIG){
    case 1U:{
    	u_n1 = (Global_Data.av.u_abc_inverter1.a + Global_Data.av.u_abc_inverter1.b + Global_Data.av.u_abc_inverter1.c + Global_Data.av.u_abc_inverter2.a + Global_Data.av.u_abc_inverter2.b + Global_Data.av.u_abc_inverter2.c) / 6.0f;
        u_n2 = u_n1;
        break;
    }
    case 2U:{
        u_n1 = (Global_Data.av.u_abc_inverter1.a + Global_Data.av.u_abc_inverter1.b + Global_Data.av.u_abc_inverter1.c)/3.0f;
        u_n2 = (Global_Data.av.u_abc_inverter2.a + Global_Data.av.u_abc_inverter2.b + Global_Data.av.u_abc_inverter2.c)/3.0f;
        break;
    }
    default: break;
    }

    u_n3 = (Global_Data.av.u_abc_inverter3.a + Global_Data.av.u_abc_inverter3.b + Global_Data.av.u_abc_inverter3.c)/3.0f;

    // calculate phase voltages with neutral voltage
    Global_Data.av.u_abc_6ph_Pruef_meas.a1 = Global_Data.av.u_abc_inverter1.a - u_n1;
    Global_Data.av.u_abc_6ph_Pruef_meas.b1 = Global_Data.av.u_abc_inverter1.b - u_n1;
    Global_Data.av.u_abc_6ph_Pruef_meas.c1 = Global_Data.av.u_abc_inverter1.c - u_n1;
    Global_Data.av.u_abc_6ph_Pruef_meas.a2 = Global_Data.av.u_abc_inverter2.a - u_n2;
    Global_Data.av.u_abc_6ph_Pruef_meas.b2 = Global_Data.av.u_abc_inverter2.b - u_n2;
    Global_Data.av.u_abc_6ph_Pruef_meas.c2 = Global_Data.av.u_abc_inverter2.c - u_n2;

    Global_Data.av.u_abc_3ph_Last_meas.a = Global_Data.av.u_abc_inverter3.a - u_n3;
    Global_Data.av.u_abc_3ph_Last_meas.b = Global_Data.av.u_abc_inverter3.b - u_n3;
    Global_Data.av.u_abc_3ph_Last_meas.c = Global_Data.av.u_abc_inverter3.c - u_n3;

    Global_Data.av.i_abc_6ph_Pruef_meas.a1 = Global_Data.av.i_abc_inverter1.a;
    Global_Data.av.i_abc_6ph_Pruef_meas.b1 = Global_Data.av.i_abc_inverter1.b;
    Global_Data.av.i_abc_6ph_Pruef_meas.c1 = Global_Data.av.i_abc_inverter1.c;
    Global_Data.av.i_abc_6ph_Pruef_meas.a2 = Global_Data.av.i_abc_inverter2.a;
    Global_Data.av.i_abc_6ph_Pruef_meas.b2 = Global_Data.av.i_abc_inverter2.b;
    Global_Data.av.i_abc_6ph_Pruef_meas.c2 = Global_Data.av.i_abc_inverter2.c;

    Global_Data.av.i_abc_3ph_Last_meas.a = Global_Data.av.i_abc_inverter3.a;
    Global_Data.av.i_abc_3ph_Last_meas.b = Global_Data.av.i_abc_inverter3.b;
    Global_Data.av.i_abc_3ph_Last_meas.c = Global_Data.av.i_abc_inverter3.c;


    Global_Data.av.i_dq_6ph_Pruef_meas = uz_transformation_asym30deg_6ph_abc_to_dq(Global_Data.av.i_abc_6ph_Pruef_meas, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
	Global_Data.av.i_dq_3ph_Last_meas = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_3ph_Last_meas, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);

	Global_Data.av.u_dq_6ph_Pruef_meas = uz_transformation_asym30deg_6ph_abc_to_dq(Global_Data.av.u_abc_6ph_Pruef_meas, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
	Global_Data.av.u_dq_3ph_Last_meas = uz_transformation_3ph_abc_to_dq(Global_Data.av.u_abc_3ph_Last_meas, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);


    /*
    Global_Data.av.Ud_6ph = Global_Data.av.u_dq_6ph_Pruef_meas.d;
    Global_Data.av.Uq_6ph = Global_Data.av.u_dq_6ph_Pruef_meas.q;
    Global_Data.av.Ux_6ph = Global_Data.av.u_dq_6ph_Pruef_meas.x;
    Global_Data.av.Uy_6ph = Global_Data.av.u_dq_6ph_Pruef_meas.y;

    Global_Data.av.Ud_3ph = Global_Data.av.u_dq_3ph_Last_meas.d;
    Global_Data.av.Uq_3ph = Global_Data.av.u_dq_3ph_Last_meas.q;
    */

    platform_state_t current_state = ultrazohm_state_machine_get_state();

    // if "STOP"
    if (current_state==idle_state)
    {
      	// disable inverters
       	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
       	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
       	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);

       	Global_Data.rasv.speed_control_3ph_Last = false;
       	Global_Data.rasv.speed_control_6ph_Pruef = false;
       	Global_Data.rasv.current_control_3ph_Last = false;
       	Global_Data.rasv.current_control_6ph_Pruef = false;

       	Global_Data.rasv.n_mech_Last_soll = 0;
       	Global_Data.rasv.n_mech_Pruef_soll = 0;
       	Global_Data.rasv.i_dq_3ph_Last_soll = (uz_3ph_dq_t) { .d = 0, .q = 0, .zero = 0 };
       	Global_Data.rasv.i_dq_6ph_Pruef_soll = (uz_6ph_dq_t) { .d = 0, .q = 0, .x = 0, .y = 0, .z1 = 0, .z2 = 0 };

       	// Reset controllers
       	uz_CurrentControl_reset(Global_Data.objects.current_control_dq_6ph_Pruef_object);
       	uz_CurrentControl_reset(Global_Data.objects.current_control_xy_6ph_Pruef_object);
       	uz_CurrentControl_reset(Global_Data.objects.current_control_3ph_Last_object);
       	uz_SpeedControl_reset(Global_Data.objects.speed_control_3ph_Last_object);
       	uz_SpeedControl_reset(Global_Data.objects.speed_control_6ph_Pruef_object);

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
    	// Global_Data.rasv.halfBridge10DutyCycle = 0.0f;
    	// Global_Data.rasv.halfBridge11DutyCycle = 0.0f;
    	// Global_Data.rasv.halfBridge12DutyCycle = 0.0f;
    }

    // if "ENABLE SYSTEM"
    if (current_state==running_state)
    {
      	Global_Data.av.error = 0;
    }

    if (current_state==control_state)
    {
		// Start: Control algorithm - only if ultrazohm is in control state

    	if(Global_Data.rasv.speed_control_3ph_Last) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);

    		float n_mech_Last_soll_filtered = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_prefilter_Last, Global_Data.rasv.n_mech_Last_soll);
    		Global_Data.rasv.M_Last_soll = uz_SpeedControl_sample(Global_Data.objects.speed_control_3ph_Last_object, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s, n_mech_Last_soll_filtered);
    		Global_Data.rasv.i_dq_3ph_Last_soll = uz_SetPoint_sample(Global_Data.objects.torque_to_current_dq_3ph_Last_object, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s, Global_Data.rasv.M_Last_soll, Global_Data.av.u_dc3, Global_Data.av.i_dq_3ph_Last_meas);

    		if((Global_Data.rasv.i_dq_3ph_Last_soll.q * Global_Data.rasv.i_dq_3ph_Last_soll.q + Global_Data.rasv.i_dq_3ph_Last_soll.d * Global_Data.rasv.i_dq_3ph_Last_soll.d) > (MAX_PHASE_CURRENT_AMP_LAST * MAX_PHASE_CURRENT_AMP_LAST)) {
    			float alpha = atan2f(Global_Data.rasv.i_dq_3ph_Last_soll.q, Global_Data.rasv.i_dq_3ph_Last_soll.d);
    			Global_Data.rasv.i_dq_3ph_Last_soll.d = MAX_PHASE_CURRENT_AMP_LAST * 0.95f * cosf(alpha);
				Global_Data.rasv.i_dq_3ph_Last_soll.q = MAX_PHASE_CURRENT_AMP_LAST * 0.95f * sinf(alpha);
    		}

    		Global_Data.rasv.u_dq_3ph_Last_soll = uz_CurrentControl_sample(Global_Data.objects.current_control_3ph_Last_object, Global_Data.rasv.i_dq_3ph_Last_soll, Global_Data.av.i_dq_3ph_Last_meas, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s * POLPAIRS_3PH_MACHINE);
    		Global_Data.rasv.duty_cycles_3ph_Last = uz_spwm_dq(Global_Data.rasv.u_dq_3ph_Last_soll, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);

    		Global_Data.rasv.halfBridge7DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_A;
    		Global_Data.rasv.halfBridge8DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_B;
    		Global_Data.rasv.halfBridge9DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_C;

    	} else if(Global_Data.rasv.current_control_3ph_Last) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);

    		Global_Data.rasv.u_dq_3ph_Last_soll = uz_CurrentControl_sample(Global_Data.objects.current_control_3ph_Last_object, Global_Data.rasv.i_dq_3ph_Last_soll, Global_Data.av.i_dq_3ph_Last_meas, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s * POLPAIRS_3PH_MACHINE);
    		Global_Data.rasv.duty_cycles_3ph_Last = uz_spwm_dq(Global_Data.rasv.u_dq_3ph_Last_soll, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);

    		Global_Data.rasv.halfBridge7DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_A;
    		Global_Data.rasv.halfBridge8DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_B;
    		Global_Data.rasv.halfBridge9DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_C;

    	} else { // control is turned off
    		Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge9DutyCycle = 0.0f;

    		uz_CurrentControl_reset(Global_Data.objects.current_control_3ph_Last_object);
    		uz_SpeedControl_reset(Global_Data.objects.speed_control_3ph_Last_object);

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);

    		Global_Data.rasv.i_dq_3ph_Last_soll.d = 0.0f;
    		Global_Data.rasv.i_dq_3ph_Last_soll.q = 0.0f;
    		Global_Data.rasv.n_mech_Last_soll = 0.0f;
    	}



    	if(Global_Data.rasv.speed_control_6ph_Pruef) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);

    		float n_mech_Pruef_soll_filtered = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_prefilter_Pruef, Global_Data.rasv.n_mech_Pruef_soll);
    		Global_Data.rasv.M_Pruef_soll = uz_SpeedControl_sample(Global_Data.objects.speed_control_6ph_Pruef_object, Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s, n_mech_Pruef_soll_filtered);

    		float u_dc_6ph = (Global_Data.av.u_dc1 + Global_Data.av.u_dc2) / 2.0f;
    		struct uz_3ph_dq_t i_dq_3ph_Pruef_meas = (uz_3ph_dq_t) { .d = Global_Data.av.i_dq_6ph_Pruef_meas.d, .q = Global_Data.av.i_dq_6ph_Pruef_meas.q };
    		struct uz_3ph_dq_t i_dq_3ph_Pruef_soll = uz_SetPoint_sample(Global_Data.objects.torque_to_current_dq_6ph_Pruef_object, Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s, Global_Data.rasv.M_Pruef_soll, u_dc_6ph, i_dq_3ph_Pruef_meas);

    		if((i_dq_3ph_Pruef_soll.q * i_dq_3ph_Pruef_soll.q + i_dq_3ph_Pruef_soll.d * i_dq_3ph_Pruef_soll.d) > (MAX_PHASE_CURRENT_AMP_LAST * MAX_PHASE_CURRENT_AMP_LAST)) {
    			float alpha = atan2f(i_dq_3ph_Pruef_soll.q, i_dq_3ph_Pruef_soll.d);
    		    i_dq_3ph_Pruef_soll.d = MAX_PHASE_CURRENT_AMP_LAST * cosf(alpha);
    		    i_dq_3ph_Pruef_soll.q = MAX_PHASE_CURRENT_AMP_LAST * sinf(alpha);
    		}
    		Global_Data.rasv.i_dq_6ph_Pruef_soll = (uz_6ph_dq_t) {.d = i_dq_3ph_Pruef_soll.d, .q = i_dq_3ph_Pruef_soll.q, .x = 0, .y = 0, .z1 = 0, .z2 = 0};

    		Global_Data.rasv.u_dq_6ph_Pruef_soll =
    				uz_CurrentControl_sample_6ph(
    					Global_Data.objects.current_control_dq_6ph_Pruef_object, Global_Data.objects.current_control_xy_6ph_Pruef_object,
    		    		Global_Data.rasv.i_dq_6ph_Pruef_soll, Global_Data.av.i_dq_6ph_Pruef_meas,
    					Global_Data.av.u_dc1, Global_Data.av.u_dc2,
    					Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s * POLPAIRS_6PH_MACHINE
    				);

    		Global_Data.rasv.duty_cycles_6ph_Pruef = uz_spwm_dq_6ph(Global_Data.rasv.u_dq_6ph_Pruef_soll, u_dc_6ph, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);

    		Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_A;
    		Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_B;
    		Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_C;
    		Global_Data.rasv.halfBridge4DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_A;
    		Global_Data.rasv.halfBridge5DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_B;
    		Global_Data.rasv.halfBridge6DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_C;

    	} else if(Global_Data.rasv.current_control_6ph_Pruef) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);

    		Global_Data.rasv.u_dq_6ph_Pruef_soll =
    			uz_CurrentControl_sample_6ph(
					Global_Data.objects.current_control_dq_6ph_Pruef_object, Global_Data.objects.current_control_xy_6ph_Pruef_object,
    				Global_Data.rasv.i_dq_6ph_Pruef_soll, Global_Data.av.i_dq_6ph_Pruef_meas,
					Global_Data.av.u_dc1, Global_Data.av.u_dc2,
					Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s * POLPAIRS_6PH_MACHINE
				);

    		float u_dc_6ph = (Global_Data.av.u_dc1 + Global_Data.av.u_dc2) / 2.0f;
    		Global_Data.rasv.duty_cycles_6ph_Pruef = uz_spwm_dq_6ph(Global_Data.rasv.u_dq_6ph_Pruef_soll, u_dc_6ph, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);

    		Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_A;
    		Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_B;
    		Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_C;
    		Global_Data.rasv.halfBridge4DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_A;
    		Global_Data.rasv.halfBridge5DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_B;
    		Global_Data.rasv.halfBridge6DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_C;

    	} else { // control is turned off

    		Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge4DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge5DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge6DutyCycle = 0.0f;

    		uz_CurrentControl_reset(Global_Data.objects.current_control_dq_6ph_Pruef_object);
    		uz_CurrentControl_reset(Global_Data.objects.current_control_xy_6ph_Pruef_object);
    		uz_SpeedControl_reset(Global_Data.objects.speed_control_6ph_Pruef_object);

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);

    		Global_Data.rasv.i_dq_6ph_Pruef_soll.d = 0.0f;
    		Global_Data.rasv.i_dq_6ph_Pruef_soll.q = 0.0f;
    		Global_Data.rasv.i_dq_6ph_Pruef_soll.x = 0.0f;
    		Global_Data.rasv.i_dq_6ph_Pruef_soll.y = 0.0f;
    		Global_Data.rasv.n_mech_Pruef_soll = 0.0f;

    	}

    }

    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    // uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);

    // uz_PWM_SS_2L_set_triangle_shift(self, triangle_shift_HB1, triangle_shift_HB2, triangle_shift_HB3)

    // Set duty cycles for three-level modulator
    // PWM_3L_SetDutyCycle(Global_Data.rasv.halfBridge1DutyCycle,
    //                     Global_Data.rasv.halfBridge2DutyCycle,
    //                     Global_Data.rasv.halfBridge3DutyCycle);

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






