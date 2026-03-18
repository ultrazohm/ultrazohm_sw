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
#include "../uz/uz_wavegen/uz_wavegen.h"

#include "../uz/uz_more_pwm_6ph/uz_zero_injection_dual_3ph_pwm.h"
#include "../uz/uz_6ph_SVPWM/uz_6ph_SVPWM_opt.h"
#include "../uz/uz_6ph_SVPWM/uz_6ph_SVPWM.h"
#include "../uz/uz_6ph_SVPWM/uz_pwm_help_functions.h"



// Initialize the Interrupt structure
XScuGic GIC_instance;
XIpiPsu IPI_instance;

// Global variable structure
extern DS_Data Global_Data;


// software limits
#define MAX_PHASE_CURRENT_AMP_LAST  30.0f
#define MAX_PHASE_CURRENT_AMP_PRUEF 15.0f
#define MAX_DC_VOLT 50.0f
#define MAX_TEMP_DEG 90.0f

#define NEUTRAL_CONFIG 2U //1U: 1N, 2U: 2N
float u_n1 = 0.0f;
float u_n2 = 0.0f;
float u_n3 = 0.0f;

#define POLPAIRS_6PH_MACHINE 5
#define POLPAIRS_3PH_MACHINE 5

#define RAD_TO_DEG (180.0f/M_PI)









static void ReadAllADC();
static void uz_r5_gic_reset_active_pl_interrupts(XScuGic *Gic);

//==============================================================================================================================================================
//----------------------------------------------------
// INTERRUPT HANDLER FUNCTIONS
// - triggered from PL
// - start of the control period
//----------------------------------------------------
void ISR_Control(void *data)
{
    uz_SystemTime_ISR_Tic(); // Reads out the global timer, has to be the first function in the isr
    ReadAllADC();
    update_speed_and_position_of_encoder_on_D5(&Global_Data);


    uz_wavegen_2_sample(Global_Data.objects.wavegen2_1);
	uz_wavegen_2_sample(Global_Data.objects.wavegen2_2);
	uz_wavegen_2_sample(Global_Data.objects.wavegen2_theta);


    Global_Data.av.resolver_outputs_d4_Pruef = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Pruef);
    Global_Data.av.resolver_outputs_d4_Last = uz_resolver_pl_interface_get_outputs(Global_Data.objects.resolver_pl_d4_Last);

    Global_Data.av.theta_el_Last_deg = Global_Data.av.resolver_outputs_d4_Last.position_el_2pi * RAD_TO_DEG;
    Global_Data.av.theta_mech_Last_deg = Global_Data.av.resolver_outputs_d4_Last.position_mech_2pi * RAD_TO_DEG;
    Global_Data.av.theta_el_Pruef_deg = Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi * RAD_TO_DEG;
    Global_Data.av.theta_mech_Pruef_deg = Global_Data.av.resolver_outputs_d4_Pruef.position_mech_2pi * RAD_TO_DEG;



    Global_Data.av.testvar4 = uz_wavegen_sawtooth_return_float_with_offset_and_amplitude(Global_Data.objects.wavegen2_1);

    Global_Data.av.testvar5 = uz_wavegen_triangle_return_float_with_offset_and_amplitude(Global_Data.objects.wavegen2_1);

    Global_Data.av.testvar6 = uz_wavegen_pulse_return_float(Global_Data.objects.wavegen2_1);

    //Global_Data.rasv.theta_el_rad_ref_JS = uz_wavegen_sawtooth(2.0f*UZ_PIf, Global_Data.rasv.freq_el_Hz_ref_JS);

    Global_Data.rasv.theta_el_rad_ref_JS = uz_wavegen_pulse_return_float(Global_Data.objects.wavegen2_theta);



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


    Global_Data.av.i_dqxy_6ph_Pruef_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(Global_Data.av.i_abc_6ph_Pruef_meas, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi, -Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
	Global_Data.av.i_dq_3ph_Last_meas = uz_transformation_3ph_abc_to_dq(Global_Data.av.i_abc_3ph_Last_meas, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);

	Global_Data.av.u_dqxy_6ph_Pruef_meas = uz_transformation_asym30deg_6ph_abc_to_dq_xy(Global_Data.av.u_abc_6ph_Pruef_meas, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi, -Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
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
      	// Disable inverters
       	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
       	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);
       	uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);

       	// Reset control variables
       	Global_Data.rasv.speed_control_3ph_Last = false;
       	Global_Data.rasv.speed_control_6ph_Pruef = false;
       	Global_Data.rasv.current_control_3ph_Last = false;
       	Global_Data.rasv.current_control_6ph_Pruef = false;

       	// Reset reference values
       	Global_Data.rasv.n_mech_Last_soll = 0;
       	Global_Data.rasv.n_mech_Pruef_soll = 0;
       	Global_Data.rasv.i_dq_3ph_Last_soll = (uz_3ph_dq_t) { .d = 0, .q = 0, .zero = 0 };
       	Global_Data.rasv.i_dqxy_6ph_Pruef_soll = (uz_6ph_dq_t) { .d = 0, .q = 0, .x = 0, .y = 0, .z1 = 0, .z2 = 0 };

       	// Reset controllers
       	uz_CurrentControl_reset(Global_Data.objects.current_control_dq_6ph_Pruef);
       	uz_CurrentControl_reset(Global_Data.objects.current_control_xy_6ph_Pruef);
       	uz_CurrentControl_reset(Global_Data.objects.current_control_3ph_Last);
       	uz_SpeedControl_reset(Global_Data.objects.speed_control_3ph_Last);
       	uz_SpeedControl_reset(Global_Data.objects.speed_control_6ph_Pruef);

    	// Write zero dutycycle
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
    	// Start: Control algorithm - only if Ultrazohm is in control state

    	//Global_Data.rasv.current_control_3ph_Last = true;

    	/*=============== Last Start ===============*/
    	if(Global_Data.rasv.speed_control_3ph_Last) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);

    		float n_mech_Last_soll_filtered = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_prefilter_Last, Global_Data.rasv.n_mech_Last_soll);
    		Global_Data.rasv.M_Last_soll = uz_SpeedControl_sample(Global_Data.objects.speed_control_3ph_Last, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s, n_mech_Last_soll_filtered);
    		Global_Data.rasv.i_dq_3ph_Last_soll = uz_SetPoint_sample(Global_Data.objects.torque_to_current_dq_3ph_Last, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s, Global_Data.rasv.M_Last_soll, Global_Data.av.u_dc3, Global_Data.av.i_dq_3ph_Last_meas);

    		if((Global_Data.rasv.i_dq_3ph_Last_soll.q * Global_Data.rasv.i_dq_3ph_Last_soll.q + Global_Data.rasv.i_dq_3ph_Last_soll.d * Global_Data.rasv.i_dq_3ph_Last_soll.d) > (MAX_PHASE_CURRENT_AMP_LAST * MAX_PHASE_CURRENT_AMP_LAST)) {
    			float alpha = atan2f(Global_Data.rasv.i_dq_3ph_Last_soll.q, Global_Data.rasv.i_dq_3ph_Last_soll.d);
    			Global_Data.rasv.i_dq_3ph_Last_soll.d = MAX_PHASE_CURRENT_AMP_LAST * 0.95f * cosf(alpha);
				Global_Data.rasv.i_dq_3ph_Last_soll.q = MAX_PHASE_CURRENT_AMP_LAST * 0.95f * sinf(alpha);
    		}

    		Global_Data.rasv.u_dq_3ph_Last_soll = uz_CurrentControl_sample(Global_Data.objects.current_control_3ph_Last, Global_Data.rasv.i_dq_3ph_Last_soll, Global_Data.av.i_dq_3ph_Last_meas, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s * POLPAIRS_3PH_MACHINE);
    		Global_Data.rasv.duty_cycles_3ph_Last = uz_spwm_dq(Global_Data.rasv.u_dq_3ph_Last_soll, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);

    		Global_Data.rasv.halfBridge7DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_A;
    		Global_Data.rasv.halfBridge8DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_B;
    		Global_Data.rasv.halfBridge9DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_C;

    	} else if(Global_Data.rasv.current_control_3ph_Last) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, true);

    		Global_Data.rasv.u_dq_3ph_Last_soll = uz_CurrentControl_sample(Global_Data.objects.current_control_3ph_Last, Global_Data.rasv.i_dq_3ph_Last_soll, Global_Data.av.i_dq_3ph_Last_meas, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.omega_mech_rad_s * POLPAIRS_3PH_MACHINE);
    		Global_Data.rasv.duty_cycles_3ph_Last = uz_spwm_dq(Global_Data.rasv.u_dq_3ph_Last_soll, Global_Data.av.u_dc3, Global_Data.av.resolver_outputs_d4_Last.position_el_2pi);

    		Global_Data.rasv.halfBridge7DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_A;
    		Global_Data.rasv.halfBridge8DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_B;
    		Global_Data.rasv.halfBridge9DutyCycle = Global_Data.rasv.duty_cycles_3ph_Last.DutyCycle_C;

    	} else { // control is turned off
    		Global_Data.rasv.halfBridge7DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge8DutyCycle = 0.0f;
    		Global_Data.rasv.halfBridge9DutyCycle = 0.0f;

    		uz_CurrentControl_reset(Global_Data.objects.current_control_3ph_Last);
    		uz_SpeedControl_reset(Global_Data.objects.speed_control_3ph_Last);

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d3, false);

    		Global_Data.rasv.i_dq_3ph_Last_soll.d = 0.0f;
    		Global_Data.rasv.i_dq_3ph_Last_soll.q = 0.0f;
    		Global_Data.rasv.n_mech_Last_soll = 0.0f;
    	}

    	/*=============== Last End --- Pruef Start ===============*/
    	if(Global_Data.rasv.speed_control_6ph_Pruef) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);

    		float n_mech_Pruef_soll_filtered = uz_signals_IIR_Filter_sample(Global_Data.objects.speed_prefilter_Pruef, Global_Data.rasv.n_mech_Pruef_soll);
    		Global_Data.rasv.M_Pruef_soll = uz_SpeedControl_sample(Global_Data.objects.speed_control_6ph_Pruef, Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s, n_mech_Pruef_soll_filtered);

    		float u_dc_6ph = (Global_Data.av.u_dc1 + Global_Data.av.u_dc2) / 2.0f;
    		struct uz_3ph_dq_t i_dq_3ph_Pruef_meas = (uz_3ph_dq_t) { .d = Global_Data.av.i_dqxy_6ph_Pruef_meas.d, .q = Global_Data.av.i_dqxy_6ph_Pruef_meas.q };


			struct uz_3ph_dq_t i_dq_3ph_Pruef_soll = uz_SetPoint_sample(Global_Data.objects.torque_to_current_dq_6ph_Pruef, Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s, Global_Data.rasv.M_Pruef_soll, u_dc_6ph, i_dq_3ph_Pruef_meas);
    		if((i_dq_3ph_Pruef_soll.q * i_dq_3ph_Pruef_soll.q + i_dq_3ph_Pruef_soll.d * i_dq_3ph_Pruef_soll.d) > (MAX_PHASE_CURRENT_AMP_PRUEF * MAX_PHASE_CURRENT_AMP_PRUEF)) {
    			float alpha = atan2f(i_dq_3ph_Pruef_soll.q, i_dq_3ph_Pruef_soll.d);
    		    i_dq_3ph_Pruef_soll.d = MAX_PHASE_CURRENT_AMP_PRUEF * cosf(alpha);
    		    i_dq_3ph_Pruef_soll.q = MAX_PHASE_CURRENT_AMP_PRUEF * sinf(alpha);
    		}
    		Global_Data.rasv.i_dqxy_6ph_Pruef_soll = (uz_6ph_dq_t) {.d = i_dq_3ph_Pruef_soll.d, .q = i_dq_3ph_Pruef_soll.q, .x = 0, .y = 0, .z1 = 0, .z2 = 0};


    		Global_Data.rasv.u_dqxy_6ph_Pruef_soll =
    				uz_CurrentControl_sample_6ph(
    					Global_Data.objects.current_control_dq_6ph_Pruef, Global_Data.objects.current_control_xy_6ph_Pruef,
    		    		Global_Data.rasv.i_dqxy_6ph_Pruef_soll, Global_Data.av.i_dqxy_6ph_Pruef_meas,
    					Global_Data.av.u_dc1, Global_Data.av.u_dc2,
    					Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s * POLPAIRS_6PH_MACHINE
    				);

    		Global_Data.rasv.duty_cycles_6ph_Pruef = uz_spwm_dqxy_6ph(Global_Data.rasv.u_dqxy_6ph_Pruef_soll, u_dc_6ph, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi, -Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);

    		Global_Data.rasv.halfBridge1DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_A;
    		Global_Data.rasv.halfBridge2DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_B;
    		Global_Data.rasv.halfBridge3DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_C;
    		Global_Data.rasv.halfBridge4DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_A;
    		Global_Data.rasv.halfBridge5DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_B;
    		Global_Data.rasv.halfBridge6DutyCycle = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_C;

    	} else if(Global_Data.rasv.current_control_6ph_Pruef) {

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);


			// Begrenzung der I soll eingabe, xy wird dabei stupide auf 0 gesetzt, evtl. bessere Lösung
			if((Global_Data.rasv.i_dqxy_6ph_Pruef_soll.q * Global_Data.rasv.i_dqxy_6ph_Pruef_soll.q + Global_Data.rasv.i_dqxy_6ph_Pruef_soll.d * Global_Data.rasv.i_dqxy_6ph_Pruef_soll.d + Global_Data.rasv.i_dqxy_6ph_Pruef_soll.x * Global_Data.rasv.i_dqxy_6ph_Pruef_soll.x + Global_Data.rasv.i_dqxy_6ph_Pruef_soll.y * Global_Data.rasv.i_dqxy_6ph_Pruef_soll.y) > (MAX_PHASE_CURRENT_AMP_PRUEF * MAX_PHASE_CURRENT_AMP_PRUEF)) {
				float alpha = atan2f(Global_Data.rasv.i_dqxy_6ph_Pruef_soll.q, Global_Data.rasv.i_dqxy_6ph_Pruef_soll.d);
				Global_Data.rasv.i_dqxy_6ph_Pruef_soll.d = MAX_PHASE_CURRENT_AMP_PRUEF * cosf(alpha);
				Global_Data.rasv.i_dqxy_6ph_Pruef_soll.q = MAX_PHASE_CURRENT_AMP_PRUEF * sinf(alpha);
				Global_Data.rasv.i_dqxy_6ph_Pruef_soll.x = 0.0f;
				Global_Data.rasv.i_dqxy_6ph_Pruef_soll.y = 0.0f;
			}


    		Global_Data.rasv.u_dqxy_6ph_Pruef_soll =
    			uz_CurrentControl_sample_6ph(
					Global_Data.objects.current_control_dq_6ph_Pruef, Global_Data.objects.current_control_xy_6ph_Pruef,
    				Global_Data.rasv.i_dqxy_6ph_Pruef_soll, Global_Data.av.i_dqxy_6ph_Pruef_meas,
					Global_Data.av.u_dc1, Global_Data.av.u_dc2,
					Global_Data.av.resolver_outputs_d4_Pruef.omega_mech_rad_s * POLPAIRS_6PH_MACHINE
				);

    		float u_dc_6ph = (Global_Data.av.u_dc1 + Global_Data.av.u_dc2) / 2.0f;
    		Global_Data.rasv.duty_cycles_6ph_Pruef = uz_spwm_dqxy_6ph(Global_Data.rasv.u_dqxy_6ph_Pruef_soll, u_dc_6ph, Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi, -Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);

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

    		uz_CurrentControl_reset(Global_Data.objects.current_control_dq_6ph_Pruef);
    		uz_CurrentControl_reset(Global_Data.objects.current_control_xy_6ph_Pruef);
    		uz_SpeedControl_reset(Global_Data.objects.speed_control_6ph_Pruef);

    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, false);
    		uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, false);

    		Global_Data.rasv.i_dqxy_6ph_Pruef_soll.d = 0.0f;
    		Global_Data.rasv.i_dqxy_6ph_Pruef_soll.q = 0.0f;
    		Global_Data.rasv.i_dqxy_6ph_Pruef_soll.x = 0.0f;
    		Global_Data.rasv.i_dqxy_6ph_Pruef_soll.y = 0.0f;
    		Global_Data.rasv.n_mech_Pruef_soll = 0.0f;

    	}
    	/*=============== Pruef End ===============*/
    }





    if (Global_Data.av.More_PWM_active)
    {
    	/*=============== PWM Test Bereich ===============*/

    	// Decode Settings:

    /*
    	1:
    	bool dual_3ph_PWM_selected;

    	2:
    	bool SVPWM_4active_selected;

    	3:
    	bool SVPWM_5active_selected;

    	4:
    	bool SVPWM_4active_opt_selected;

    	5:
    	bool SVPWM_4active_opt_selected;
    	bool is_scaled;

    	6:
    	bool SVPWM_4active_opt_selected;
    	bool d_opt_selected;

    	7:
    	bool SVPWM_5active_opt_selected;

    	8:
    	bool SVPWM_5active_opt_selected;
    	bool is_scaled;
	*/

    	if(Global_Data.rasv.PWM_Settings == 1){
    		// Dual 3ph-Verfahren
    			Global_Data.av.dual_3ph_PWM_selected 		= true;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= false;
				Global_Data.av.is_scaled					= false;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= false;
    	}
    	else if(Global_Data.rasv.PWM_Settings == 2){
    		// SVPWM 4 aktive SV
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= true;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= false;
				Global_Data.av.is_scaled					= false;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= false;
		}
    	else if(Global_Data.rasv.PWM_Settings == 3){
    		 // SVPWM 5 aktive SV
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= true;
				Global_Data.av.SVPWM_4active_opt_selected	= false;
				Global_Data.av.is_scaled					= false;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= false;
			}
    	else if(Global_Data.rasv.PWM_Settings == 4){
    		 // SVPWM Opt 4 active SV z1z2
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= true;
				Global_Data.av.is_scaled					= false;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= false;
			}
    	else if(Global_Data.rasv.PWM_Settings == 5){
    		 // SVPWM Opt 4 active SV z1z2 scaled
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= true;
				Global_Data.av.is_scaled					= true;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= false;
			}
    	else if(Global_Data.rasv.PWM_Settings == 6){
			// SVPWM Opt 4 active SV d opt
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= true;
				Global_Data.av.is_scaled					= false;
				Global_Data.av.d_opt_selected				= true;
				Global_Data.av.SVPWM_5active_opt_selected	= false;
			}
    	else if(Global_Data.rasv.PWM_Settings == 7){
			 // SVPWM Opt 5 active SV z1z2
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= false;
				Global_Data.av.is_scaled					= false;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= true;
			}
    	else if(Global_Data.rasv.PWM_Settings == 8){
			// SVPWM Opt 4 active SV z1z2 scaled
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= false;
				Global_Data.av.is_scaled					= true;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= true;
			}
		else{
    			Global_Data.av.dual_3ph_PWM_selected 		= false;
				Global_Data.av.SVPWM_4active_selected		= false;
				Global_Data.av.SVPWM_5active_selected		= false;
				Global_Data.av.SVPWM_4active_opt_selected	= false;
				Global_Data.av.is_scaled					= false;
				Global_Data.av.d_opt_selected				= false;
				Global_Data.av.SVPWM_5active_opt_selected	= false;
    	}

    	// in float umwandeln fürs JavaScope
    	Global_Data.av.temp_float_scaled		= (float)(Global_Data.av.is_scaled);
    	Global_Data.av.temp_float_dual_3ph		= (float)(Global_Data.av.dual_3ph_PWM_selected);
    	Global_Data.av.temp_float_4_act			= (float)(Global_Data.av.SVPWM_4active_selected);
    	Global_Data.av.temp_float_5_act			= (float)(Global_Data.av.SVPWM_5active_selected);
    	Global_Data.av.temp_float_4_opt			= (float)(Global_Data.av.SVPWM_4active_opt_selected);
    	Global_Data.av.temp_float_5_opt			= (float)(Global_Data.av.SVPWM_5active_opt_selected);
    	Global_Data.av.temp_float_d_opt			= (float)(Global_Data.av.d_opt_selected);
    	Global_Data.av.temp_float_More_PWM		= (float)(Global_Data.av.More_PWM_active);


    	Global_Data.av.Selected_Dual_3ph_PWMVerfahren = (int)Global_Data.rasv.PWM_Versionsnummer;
		if((int)Global_Data.rasv.PWM_Versionsnummer < 0 || (int)Global_Data.rasv.PWM_Versionsnummer > 13-1){
			Global_Data.av.Selected_Dual_3ph_PWMVerfahren = 0;
		}

		Global_Data.av.selected_4active_PWM_version = (int)Global_Data.rasv.PWM_Versionsnummer;
		if((int)Global_Data.rasv.PWM_Versionsnummer < 0 || (int)Global_Data.rasv.PWM_Versionsnummer > 18-1){
			Global_Data.av.selected_4active_PWM_version = 0;
		}

		Global_Data.av.selected_5active_PWM_version = (int)Global_Data.rasv.PWM_Versionsnummer;
		if((int)Global_Data.rasv.PWM_Versionsnummer < 0 || (int)Global_Data.rasv.PWM_Versionsnummer > 16-1){
			Global_Data.av.selected_5active_PWM_version = 0;
		}

    	// Input mit Regelung
    	if (current_state==control_state){

    		Global_Data.rasv.u_ref_6ph_alphabeta = uz_transformation_asym30deg_6ph_dq_xy_to_alphabeta_XY(Global_Data.rasv.u_dqxy_6ph_Pruef_soll,Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi, -Global_Data.av.resolver_outputs_d4_Pruef.position_el_2pi);
    		Global_Data.av.V_DC_Volts = (Global_Data.av.u_dc1 + Global_Data.av.u_dc2) / 2.0f;

    	}
    	else{ // Input ohne Regelung

			Global_Data.rasv.u_ref_6ph_alphabeta = uz_transformation_asym30deg_6ph_dq_xy_to_alphabeta_XY(Global_Data.rasv.u_dqxy_6ph_ref_JS, Global_Data.rasv.theta_el_rad_ref_JS, -Global_Data.rasv.theta_el_rad_ref_JS);
			Global_Data.av.V_DC_Volts = Global_Data.rasv.V_DC_Volts_ref_JS;

    	}

    	Global_Data.av.sector24 = (float)getSector24(Global_Data.rasv.theta_el_rad_ref_JS);

    	// switch zwischen den Verschiedenen Varianten
    	// PWM-Verfahren Switch-Case



       	if(Global_Data.av.dual_3ph_PWM_selected){

       	switch(Global_Data.av.Selected_Dual_3ph_PWMVerfahren){

       	case Dual_PWM_THI_1_4_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_PWM_THI_1_4_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_PWM_THI_1_6_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_PWM_THI_1_6_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_SVM_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_SVM_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_GDPWM_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_GDPWM_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.phi_rad, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_GDPWM_alphabeta_6ph_V2:
			Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_GDPWM_alphabeta_6ph_V2(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.phi_rad, Global_Data.av.V_DC_Volts);
			break;
       	case Dual_DPWM0_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM0_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_DPWM1_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM1_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_DPWM1PHI_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM1PHI_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_DPWM2_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM2_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_DPWM3_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM3_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_DPWM3PHI_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM3PHI_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_DPWM_MAX_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM_MAX_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
       	case Dual_DPWM_MIN_alphabeta_6ph:
    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_Dual_DPWM_MIN_alphabeta_6ph(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts);
    		break;
		default:
   			Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A = 0.0f;
   			Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B = 0.0f;
   			Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C = 0.0f;
   			Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_A = 0.0f;
   			Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_B = 0.0f;
   			Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_C = 0.0f;
			break;

       	}
       	Global_Data.av.testvar1 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A;
       	Global_Data.av.testvar2 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B;
       	Global_Data.av.testvar3 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C;
       	Global_Data.av.testvar4 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A;
       	Global_Data.av.testvar5 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B;
       	Global_Data.av.testvar6 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C;

       	}else if(Global_Data.av.SVPWM_4active_selected){
    		// SVPWM 4 active
    		Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output = uz_6ph_SVPWM_24_4_active_SV_alphabeta(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts, Global_Data.av.selected_4active_PWM_version, Global_Data.av.CD1D2);
    		Global_Data.av.PWM_6ph_DutyCycle_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.Dutycles;
    		Global_Data.av.PhaseShift_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.phaseshiftoption;

       	}else if(Global_Data.av.SVPWM_5active_selected){

    		// SVPWM 5 active

       		if (Global_Data.av.selected_5active_PWM_version == CSVPWM_24_2L_1ML_2M_M23_SV_SEQUENCE || Global_Data.av.selected_5active_PWM_version == CSVPWM_24_3L_2M_M32_SV_SEQUENCE || Global_Data.av.selected_5active_PWM_version == CSVPWM_24_2L_3M_L13_M123_SV_SEQUENCE || Global_Data.av.selected_5active_PWM_version == CSVPWM_24_1L_1ML_3M_L2_M132_SV_SEQUENCE){
        		Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output = uz_6ph_SVPWM_24_5_active_SV_alphabeta(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts, Global_Data.av.selected_5active_PWM_version, Global_Data.av.CD1D2);
        		Global_Data.av.PWM_6ph_DutyCycle_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.Dutycles;
        		Global_Data.av.PhaseShift_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.phaseshiftoption;
       		}else{
       			Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A = 0.0f;
       			Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B = 0.0f;
       			Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C = 0.0f;
       			Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_A = 0.0f;
       			Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_B = 0.0f;
       			Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_C = 0.0f;
       			Global_Data.av.PhaseShift_output = 0;
       		}




       	}else if(Global_Data.av.SVPWM_4active_opt_selected){

       		if(Global_Data.av.d_opt_selected){
        		Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output = uz_6ph_SVPWM_24_4_active_SV_opt_d_alphabeta(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts, Global_Data.av.selected_4active_PWM_version, Global_Data.av.kappa);
        		Global_Data.av.PWM_6ph_DutyCycle_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.Dutycles;
        		Global_Data.av.PhaseShift_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.phaseshiftoption;
       		}else{
        		Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output = uz_6ph_SVPWM_24_4_active_SV_opt_z1z2_alphabeta(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts, Global_Data.av.selected_4active_PWM_version, Global_Data.av.kappa, Global_Data.av.is_scaled);
        		Global_Data.av.PWM_6ph_DutyCycle_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.Dutycles;
        		Global_Data.av.PhaseShift_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.phaseshiftoption;


        		u_z1z2 u_z1z2_result = {0};
        		int test_sector = getSector24(Global_Data.rasv.theta_el_rad_ref_JS);


        		u_z1z2_result = return_svpwm_4active_optz1z2(0, Global_Data.rasv.theta_el_rad_ref_JS,1.0f, 0.5, test_sector, 1.0f);

        		Global_Data.av.testvar1 = u_z1z2_result.u_z1;
				Global_Data.av.testvar2 = u_z1z2_result.u_z2;
				Global_Data.av.testvar3 = test_sector;


       		}

       	}else if(Global_Data.av.SVPWM_5active_opt_selected){

    		// SVPWM 5 active // CD1D2 und z1z2, scaled, opt d als parameter
    		Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output = uz_6ph_SVPWM_24_5_active_SV_opt_z1z2_alphabeta(Global_Data.rasv.u_ref_6ph_alphabeta, Global_Data.av.V_DC_Volts, Global_Data.av.selected_5active_PWM_version, Global_Data.av.kappa, Global_Data.av.CD1D2, Global_Data.av.is_scaled);
    		Global_Data.av.PWM_6ph_DutyCycle_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.Dutycles;
    		Global_Data.av.PhaseShift_output = Global_Data.av.PWM_6ph_DutyCycle_PhaseShift_output.phaseshiftoption;


       	}else{

    		Global_Data.av.PWM_6ph_DutyCycle_output = uz_spwm_abc_6ph(uz_transformation_asym30deg_6ph_alphabeta_to_abc(Global_Data.rasv.u_ref_6ph_alphabeta), Global_Data.av.V_DC_Volts);

       	}

    	// An die Umrichter Schreiben
/* TODO, noch einfügen
		Global_Data.rasv.halfBridge1DutyCycle = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A;
		Global_Data.rasv.halfBridge2DutyCycle = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B;
		Global_Data.rasv.halfBridge3DutyCycle = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C;
		Global_Data.rasv.halfBridge4DutyCycle = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A;
		Global_Data.rasv.halfBridge5DutyCycle = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B;
		Global_Data.rasv.halfBridge6DutyCycle = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C;
*/
		// Umrichter aktivieren
		//uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d1, true);
		//uz_inverter_adapter_set_PWM_EN(Global_Data.objects.inverter_d2, true);

       	// Test-Outputs für Javascope
		// VSD:

		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.a1 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.b1 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.c1 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.a2 = Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_A;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.b2 = Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_B;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.c2 = Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_C;

		Global_Data.av.PWM_6ph_DutyCycle_VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output);




       	// Umrichter-Phase-Shift hier einfügen

		Global_Data.av.carrier_shift_val = uz_svm_6ph_calc_carrier_shift_value(Global_Data.av.PhaseShift_output);
	    Global_Data.av.shift_system_1 = Global_Data.av.carrier_shift_val.carrier_shift_1;
		Global_Data.av.shift_system_2 = Global_Data.av.carrier_shift_val.carrier_shift_2;




    }else{
		Global_Data.av.carrier_shift_val.carrier_shift_1 = 0.0f;
		Global_Data.av.carrier_shift_val.carrier_shift_2 = 0.0f;
	    Global_Data.av.shift_system_1 = 0.0f;;
		Global_Data.av.shift_system_2 = 0.0f;
		Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_A;
		Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_B;
		Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C = Global_Data.rasv.duty_cycles_6ph_Pruef.system1.DutyCycle_C;
		Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_A = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_A;
		Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_B = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_B;
		Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_C = Global_Data.rasv.duty_cycles_6ph_Pruef.system2.DutyCycle_C;

		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.a1 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_A;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.b1 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_B;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.c1 = Global_Data.av.PWM_6ph_DutyCycle_output.system1.DutyCycle_C;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.a2 = Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_A;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.b2 = Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_B;
		Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output.c2 = Global_Data.av.PWM_6ph_DutyCycle_output.system2.DutyCycle_C;

		Global_Data.av.PWM_6ph_DutyCycle_VSD_output = uz_transformation_asym30deg_6ph_abc_to_alphabeta(Global_Data.av.PWM_6ph_DutyCycle_abc1abc2_output);


    }
    /*=============== PWM Test Bereich End ===============*/



    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.rasv.halfBridge1DutyCycle, Global_Data.rasv.halfBridge2DutyCycle, Global_Data.rasv.halfBridge3DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.rasv.halfBridge4DutyCycle, Global_Data.rasv.halfBridge5DutyCycle, Global_Data.rasv.halfBridge6DutyCycle);
    uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_12_to_17, Global_Data.rasv.halfBridge7DutyCycle, Global_Data.rasv.halfBridge8DutyCycle, Global_Data.rasv.halfBridge9DutyCycle);
    // uz_PWM_SS_2L_set_duty_cycle(Global_Data.objects.pwm_d1_pin_18_to_23, Global_Data.rasv.halfBridge10DutyCycle, Global_Data.rasv.halfBridge11DutyCycle, Global_Data.rasv.halfBridge12DutyCycle);



    uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_0_to_5, Global_Data.av.shift_system_1, Global_Data.av.shift_system_1, Global_Data.av.shift_system_1);
    uz_PWM_SS_2L_set_triangle_shift(Global_Data.objects.pwm_d1_pin_6_to_11, Global_Data.av.shift_system_2, Global_Data.av.shift_system_2, Global_Data.av.shift_system_2); //offset PWM verfahren


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
 * Equivalent to XSCT: mwr (CpuBaseAddress + 0x10) intid
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



