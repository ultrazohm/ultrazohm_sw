.. _uz_ParaID_new_control_algorithm:

========================================
Change control algorithm for ParameterID
========================================

The ParameterID does not have its own control algorithm. This is done externally, as shown in :numref:`ParaID_overview_schematic`.
In the ParameterID library standard functions with the :ref:`uz_CurrentControl` and :ref:`uz_SpeedControl` are included. 
If it is desired to change the used controller, these functions have to be adjusted.

Following is the code of the function ``uz_ParameterID_Controller``, with the function calls to the ``uz_FOC`` and ``uz_SpeedController`` removed. 
This can be used as an template to include your new controller.

.. code-block:: c
  :linenos:
  :emphasize-lines: 11-13,18-19,24-25,27-29,33-34,38-39,41-42,44-45,52-54,56-57,76-77
  :caption: template code to include your own controller
    
  uz_3ph_dq_t uz_ParameterID_Controller(uz_ParameterID_Data_t* Data, uz_CurrentControl_t* CC_instance, uz_SpeedControl_t* SC_instance, uz_SetPoint_t* SP_instance) {
    uz_assert_not_NULL(Data);
    uz_assert_not_NULL(CC_instance);
    uz_assert_not_NULL(SC_instance);
    uz_assert_not_NULL(SP_instance);
    uz_3ph_dq_t v_dq_Volts = { 0 };
    uz_3ph_dq_t i_SpeedControl_reference_Ampere = { 0 };
    float SpeedControl_reference_torque = 0.0f;

    if (Data->Controller_Parameters.enableFOC_speed) {
      //Add your speedcontroller here. Should output reference-dq-currents in the uz_3ph_dq_t system or a reference-torque for a subsequent setpoint module.
      //In the later case the setpoint module has to output the reference dq-currents.
      i_SpeedControl_reference_Ampere = ....
      //ADD PRBS excitation for TwoMassID
      i_SpeedControl_reference_Ampere.q += Data->TwoMassID_Output->PRBS_out;
    }
    if (Data->Controller_Parameters.enableFOC_torque) {
      //Add your setpoint module here which calculates dq-currents based on a reference torque.
      i_SpeedControl_reference_Ampere = ....
	  }
    if (Data->Controller_Parameters.enableFOC_current || Data->Controller_Parameters.enableFOC_speed || Data->Controller_Parameters.enableFOC_torque) {
      //Add your currentcontroller here. Should output dq-currents in the uz_3ph_dq_t system
      if (Data->Controller_Parameters.enableFOC_current) {
        //If CurrentControl is active, use Data->Controller_Parameters.i_dq_ref as input reference currents
        v_dq_Volts = ....
      } else if (Data->Controller_Parameters.enableFOC_torque || Data->Controller_Parameters.enableFOC_speed)  {
        //If SpeedControl or TorqueControl is active, use i_SpeedControl_reference_Ampere as input reference currents.
        //The controller should output reference voltages for the SVM in the dq-plane.
        v_dq_Volts = ....
      }
    }
    if (Data->Controller_Parameters.resetIntegrator) {
      //Reset integrators, if necessary
      ....
    }
    if (Data->ControlFlags->transNr > 0U && Data->ControlFlags->transNr <= 4U) {
      if (Data->Controller_Parameters.activeState == 144U) {
        //Change decoupling method, if needed
        ....
      } else if (Data->Controller_Parameters.activeState == 170U) {
        //Change decoupling method, if needed
        ....
      }
      //During identification, if an FOC is used, update the control-parameters (Kp,Ki) here
      ....
    }
    //This is the setup for the Controller for Online-ID-states
    if (Data->ControlFlags->finished_all_Offline_states) {
      uz_3ph_dq_t Online_current_ref = {0};
      if (Data->ParaID_Control_Selection == Current_Control || Data->ParaID_Control_Selection == Speed_Control || Data->ParaID_Control_Selection == Torque_Control) {
        if (Data->ParaID_Control_Selection == Speed_Control) {
          //Add your speedcontroller here. Should output reference-dq-currents in the uz_3ph_dq_t system or a reference-torque for a subsequent setpoint module.
          //In the later case the setpoint module has to output the reference dq-currents.
          Online_current_ref = ....		
        } else if (Data->ParaID_Control_Selection == Torque_Control) {
          //Add your setpoint module here which calculates dq-currents based on a reference torque.
          Online_current_ref = ....
        } else {
          //Use the manual reference currents
          Online_current_ref = Data->GlobalConfig.i_dq_ref;
        }
      }
      if (Data->OnlineID_Output->IdControlFlag == true) {
        if (Data->AutoRefCurrents_Config.enableCRS == true && Data->ParaID_Control_Selection == Current_Control) {//Overwrite dq-ref-currents when AutoRefCurrents is active
          Online_current_ref.d = Data->OnlineID_Output->id_out + Data->AutoRefCurrents_Output.i_dq_ref.d;
          Online_current_ref.q = Data->AutoRefCurrents_Output.i_dq_ref.q;
        } else {
          Online_current_ref.d = Data->GlobalConfig.i_dq_ref.d + Data->OnlineID_Output->id_out;
        }
      } else {
        if (Data->AutoRefCurrents_Config.enableCRS == true && Data->ParaID_Control_Selection == Current_Control) {
          Online_current_ref.d = Data->AutoRefCurrents_Output.i_dq_ref.d;
          Online_current_ref.q = Data->AutoRefCurrents_Output.i_dq_ref.q;
        }
      }
      //Add your CurrentController here. The controller should output reference voltages for the SVM in the dq-plane.
      v_dq_Volts = ....	
    }
    return (v_dq_Volts);
  }

The function ``uz_ParameterID_generate_DutyCycle``, can be adjusted as well. It uses a continuous sinusoidal PWM (SPWM) modulation from `blank` to generate the DutyCycles.

.. code-block:: c
  :linenos:
  :emphasize-lines: 12,13
  :caption: template code to generate DutyCycles

  struct uz_DutyCycle_t uz_ParameterID_generate_DutyCycle(uz_ParameterID_Data_t* Data, uz_3ph_dq_t v_dq_Volts, uz_PWM_SS_2L_t* PWM_Module) {
    uz_assert_not_NULL(Data);
    uz_assert_not_NULL(PWM_Module);
    struct uz_DutyCycle_t output_DutyCycle = { 0 };
    if (Data->Controller_Parameters.activeState >= 110 && Data->Controller_Parameters.activeState <= 143) {
      uz_PWM_SS_2L_set_tristate(PWM_Module, Data->ElectricalID_Output->enable_TriState[0], Data->ElectricalID_Output->enable_TriState[1], Data->ElectricalID_Output->enable_TriState[2]);
      output_DutyCycle.DutyCycle_U = Data->ElectricalID_Output->PWM_Switch_0;
      output_DutyCycle.DutyCycle_V = Data->ElectricalID_Output->PWM_Switch_2;
      output_DutyCycle.DutyCycle_W = Data->ElectricalID_Output->PWM_Switch_4;
    } else if ((Data->Controller_Parameters.enableFOC_current || Data->Controller_Parameters.enableFOC_speed || Data->Controller_Parameters.enableFOC_torque)
	                || (Data->ControlFlags->finished_all_Offline_states && (Data->ParaID_Control_Selection == Current_Control || Data->ParaID_Control_Selection == Speed_Control || Data->ParaID_Control_Selection == Torque_Control))) {
      //Use your own function to generate DutyCycles here, if the control-algorithms are used
      output_DutyCycle = ....
    } else {
      output_DutyCycle.DutyCycle_U = 0.0f;
      output_DutyCycle.DutyCycle_V = 0.0f;
      output_DutyCycle.DutyCycle_W = 0.0f;
    }
    if (Data->Controller_Parameters.resetIntegrator) {
      output_DutyCycle.DutyCycle_U = 0.0f;
      output_DutyCycle.DutyCycle_V = 0.0f;
      output_DutyCycle.DutyCycle_W = 0.0f;
    }
  return (output_DutyCycle);
  }
