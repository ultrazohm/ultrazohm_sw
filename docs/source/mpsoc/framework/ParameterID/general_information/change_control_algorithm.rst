.. _uz_PID_new_control_algorithm:

========================================
Change control algorithm for ParameterID
========================================

The ParameterID does not have its own control algorithm. This is done externally, as shown in :numref:`PID_overview_schematic`.
In the ParameterID library standard functions with the :ref:`uz_FOC` and :ref:`uz_SpeedControl` are included. 
If it is desired to change the used controller, these functions have to be adjusted.

Following is the code of the function ``uz_ParameterID_Controller``, with the function calls to the ``uz_FOC`` and ``uz_SpeedController`` removed. 
This can be used as an template to include your new controller.

.. code-block:: c
  :linenos:
  :caption: template code to include your own controller
    
  uz_3ph_dq_t uz_ParameterID_Controller(uz_ParameterID_Data_t* Data, uz_FOC* FOC_instance, uz_PI_Controller* Speed_instance) {
  uz_3ph_dq_t v_dq_Volts = { 0 };
  uz_3ph_dq_t i_SpeedControl_reference_Ampere = { 0 };
  bool ext_clamping = false;

  if (Data->Controller_Parameters.enableFOC_speed == true) {
	//Add your speedcontroller here. Should output dq-currents in the uz_3ph_dq_t system
	i_SpeedControl_reference_Ampere = ....
	//Create sine excitation for J-Identification
	if (Data->Controller_Parameters.VibOn_out == true) {
        float sine_excitation = uz_wavegen_sine(Data->Controller_Parameters.VibAmp_out, Data->Controller_Parameters.VibFreq_out);
        i_SpeedControl_reference_Ampere.q += sine_excitation;}
    else {
        i_SpeedControl_reference_Ampere.q += Data->Controller_Parameters.PRBS_out;}}
  if (Data->Controller_Parameters.enableFOC_current == true || Data->Controller_Parameters.enableFOC_speed == true) {
    //Add your currentcontroller here. Should output dq-currents in the uz_3ph_dq_t system
    if (Data->Controller_Parameters.enableFOC_current == true) {
        //If CurrentControl is active, use Data->Controller_Parameters.i_dq_ref as input reference currents
        v_dq_Volts = ....
    } else if (Data->Controller_Parameters.enableFOC_speed == true) {
        //If SpeedControl is active, use i_SpeedControl_reference_Ampere as input reference currents
        v_dq_Volts = ....
    }
  }
  if (Data->Controller_Parameters.resetIntegrator == true) {
    //Reset integrators, if necessary
    ....
  }
  if (Data->ControlFlags->transNr == 1U || Data->ControlFlags->transNr == 2U) {
    if (Data->Controller_Parameters.activeState == 144U) {
        //Change decoupling method, if needed
        ....
    } else if (Data->Controller_Parameters.activeState == 170U) {
        //Change decoupling method and update the used motor parameters with the identified ones, if needed
        ....
    }
    //During identification, if an FOC is used, update the controll-parameters (Kp,Ki) here
    ....
  }

  if (Data->ControlFlags->finished_all_Offline_states == true) {
	uz_3ph_dq_t Online_current_ref = Data->GlobalConfig.i_dq_ref;
	if (Data->OnlineID_Output->IdControlFlag == true) {
		if (Data->AutoRefCurrents_Config.enableCRS == true) {
			Online_current_ref.d = Data->GlobalConfig.i_dq_ref.d + Data->OnlineID_Output->id_out + Data->AutoRefCurrents_Output.d;
			Online_current_ref.q = Data->GlobalConfig.i_dq_ref.q + Data->AutoRefCurrents_Output.q;
		} else {
			Online_current_ref.d = Data->GlobalConfig.i_dq_ref.d + Data->OnlineID_Output->id_out;
		}
	} else {
		if (Data->AutoRefCurrents_Config.enableCRS == true) {
			Online_current_ref.d = Data->GlobalConfig.i_dq_ref.d + Data->AutoRefCurrents_Output.d;
			Online_current_ref.q = Data->GlobalConfig.i_dq_ref.q + Data->AutoRefCurrents_Output.q;
		}
	}
	if (Data->PID_Control_Selection == Current_Control || Data->PID_Control_Selection == Speed_Control) {
		if (Data->PID_Control_Selection == Speed_Control) {
			//Add your speedcontroller here. Should output dq-currents in the uz_3ph_dq_t system. If OnlineID is used, the i_d-injection signal has to be written onto the d-axis reference current
            i_SpeedControl_reference_Ampere = ....
		}
		if (Data->PID_Control_Selection == Current_Control || Data->PID_Control_Selection == Speed_Control) {
			if (Data->PID_Control_Selection == Current_Control) {
                //If CurrentControl is active, use Online_current_ref as input reference currents
			    v_dq_Volts = ....			
			} else {
                //If SpeedControl is active, use i_SpeedControl_reference_Ampere as input reference currents
			    v_dq_Volts = ....
			}
		}
	} else {
	    v_dq_Volts.d = 0.0f;
		v_dq_Volts.q = 0.0f;
		v_dq_Volts.zero = 0.0f;
	}
  }
  return (v_dq_Volts);
  }

The function ``uz_ParameterID_generate_DutyCycle``, can be adjusted as well. It uses a continuous sinusoidal PWM (SPWM) modulation from :ref:`uz_FOC_DutyCycle` to generate the DutyCycles.

.. code-block:: c
  :linenos:
  :caption: template code to generate DutyCycles

  struct uz_DutyCycle_t uz_ParameterID_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_3ph_dq_t v_dq_Volts, uz_PWM_SS_2L_t* PWM_Module) {
	struct uz_DutyCycle_t output_DutyCycle = { 0 };
	if (Data->Controller_Parameters.activeState >= 110 && Data->Controller_Parameters.activeState <= 143) {
		uz_PWM_SS_2L_set_tristate(PWM_Module, Data->ElectricalID_Output->enable_TriState[0], Data->ElectricalID_Output->enable_TriState[1], Data->ElectricalID_Output->enable_TriState[2]);
		output_DutyCycle.DutyCycle_U = Data->ElectricalID_Output->PWM_Switch_0;
		output_DutyCycle.DutyCycle_V = Data->ElectricalID_Output->PWM_Switch_2;
		output_DutyCycle.DutyCycle_W = Data->ElectricalID_Output->PWM_Switch_4;
	} else if ((Data->Controller_Parameters.enableFOC_current == true || Data->Controller_Parameters.enableFOC_speed == true)
	                || (Data->ControlFlags->finished_all_Offline_states == true && (Data->PID_Control_Selection == Current_Control || Data->PID_Control_Selection == Speed_Control))) {
		uz_3ph_abc_t V_UVW_Volts = uz_dq_inverse_transformation(v_dq_Volts, Data->ActualValues.theta_el);
        //Use your own function to generate DutyCycles here, if the control-algorithms are used
		output_DutyCycle = ....
	} else {
		output_DutyCycle.DutyCycle_U = 0.0f;
		output_DutyCycle.DutyCycle_V = 0.0f;
		output_DutyCycle.DutyCycle_W = 0.0f;
	}
	if (Data->Controller_Parameters.resetIntegrator == true) {
		output_DutyCycle.DutyCycle_U = 0.0f;
		output_DutyCycle.DutyCycle_V = 0.0f;
		output_DutyCycle.DutyCycle_W = 0.0f;
	}
	return (output_DutyCycle);
}
