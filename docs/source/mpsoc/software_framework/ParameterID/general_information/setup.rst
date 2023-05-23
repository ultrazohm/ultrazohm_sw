.. _uz_ParaID_setup:

======================================
Setup and functions of the ParameterID
======================================

This page details the steps to setup the ParameterID in the UltraZohm software project. 

Setup
=====

.. code-block:: c
  :linenos:
  :emphasize-lines: 7,13,40-41
  :caption: Example to initialize the ParameterID. The ParameterID must be initialized before the Javascope is initialized. 
    
  #include "uz/uz_ParameterID/uz_ParameterID.h"
  #include "uz/uz_math_constants.h"

  //ParameterID Code
  uz_ParameterID_t* ParameterID = NULL;
  uz_ParameterID_Data_t ParaID_Data = { 0 };
  //Objects below are only needed, if the uz_FOC is used as the controller
  uz_CurrentControl_t* CC_instance = NULL;
  uz_SpeedControl_t* SC_instance = NULL;
  uz_SetPoint_t* SP_instance = NULL;

  int main(void) {
      ParameterID = uz_ParameterID_init(&ParaID_Data);
     //Code below is only needed, if the uz_FOC is used as the controller 
     struct uz_PI_Controller_config config_id = { 
          .Kp = ParaID_Data.GlobalConfig.Kp_id, 
          .Ki = ParaID_Data.GlobalConfig.Ki_id, 
          .samplingTime_sec = 0.0001f, 
          .upper_limit = 15.0f,
          .lower_limit = -15.0f };
     struct uz_PI_Controller_config config_iq = { 
          .Kp = ParaID_Data.GlobalConfig.Kp_iq, 
          .Ki = ParaID_Data.GlobalConfig.Ki_iq, 
          .samplingTime_sec = 0.0001f, 
          .upper_limit = 15.0f,
          .lower_limit = -15.0f };
     struct uz_SpeedControl_config config_SC = {
          .config_controller.Kp = ParaID_Data.GlobalConfig.Kp_n,
          .config_controller.Ki = ParaID_Data.GlobalConfig.Ki_n, 
          .config_controller.samplingTime_sec = 0.0001f, 
          .config_controller.upper_limit = 10.0f,
          .config_controller.lower_limit = -10.0f };
     struct uz_CurrentControl_config config_CC = {
          .config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
          .config_id = config_id, 
          .config_iq = config_iq,
          .max_modulation_index = 1.0f/sqrtf(3.0f) }; //for SpaceVectorModulation
     struct uz_SetPoint_config config_SP = {
	   .config_PMSM = ParaID_Data.GlobalConfig.PMSM_config,
	   .control_type = FOC,
	   .id_ref_Ampere = 0.0f,
	   .is_field_weakening_enabled = false,
	   .motor_type = SMPMSM };
     CC_instance = uz_CurrentControl_init(config_CC);
     SC_instance = uz_SpeedControl_init(config_SC);
     SP_instance = uz_SetPoint_init(config_SP);
     //....
     JavaScope_initalize(&Global_Data);
  }

In the ``uz_ParameterID_init`` function, the struct of the type ``uz_ParameterID_Data_t`` is initialized as well. 
This struct carries, among other things, the configuration values of the ParameterID.
To ease the setup of the ParameterID, this struct is initialized with default values. 
To configure the ParameterID to your needs, change the values inside the ``uz_ParameterID_initialize_data_structs`` function. 
Especially the configuration of the motor-related parameters is important. 
If they are not known, they can be left at 0.0f. In this case however, these parameters have to be identified first by using the :ref:`uz_ElectricalID` state. 
The ID-state specific configuration values can later be configured via the uz_GUI. 

.. literalinclude:: ../../../../../../vitis/software/Baremetal/src/uz/uz_ParameterID/uz_ParameterID.c
    :caption: Code to initialize ``uz_ParameterID_Data_t``. Important parts are highlighted.
    :lines: 447-538
    :linenos:
    :emphasize-lines: 13,16-31
    :language: c

If the FluxMaps identification of the :ref:`uz_OnlineID` state will be used, the following code has to be implemented inside the ``infinite_loop`` case of the switch case in the ``main.c`` . 
These functions are to compute heavy to be executed in the ISR.

.. code-block:: c
  :linenos:
  :caption: Code to calculate FluxMaps inside the ``infinite_loop`` case of the switch case in the ``main.c`` .

  //....
  case infinite_loop:
     ultrazohm_state_machine_step();  
     if (ParaID_Data.OnlineID_Output->clean_array) {
          uz_ParameterID_CleanPsiArray(ParameterID, &ParaID_Data);
     }
     if (ParaID_Data.calculate_flux_maps) {
          uz_ParameterID_CalcFluxMaps(ParameterID, &ParaID_Data);
          ParaID_Data.calculate_flux_maps = false;
     }
     break;
  //....

In the ``isr.c``  the members of the :ref:`uz_Actual_values_struct` struct inside the :ref:`uz_ParameterID_Data_struct` have to be assigned with the measurement values needed for the identification. 
Furthermore, the ``uz_ParameterID_step`` function needs to be called as well. Two functions ``uz_ParameterID_Controller`` and ``uz_ParameterID_generate_DutyCycle`` are used in the code below as well.
These exemplary functions are included in the ParameterID-library, to ease the use of it. They include the uz_FOC and a function to generate the DutyCycles for the halfbridges.
They are technically not required for the ParameterID and can, if desired, be replaced by your own control algorithm.

.. code-block:: c
  :linenos:
  :emphasize-lines: 3,29
  :caption: Changes in the isr.c

  extern uz_ParameterID_Data_t ParaID_Data;
  extern uz_ParameterID_t* ParameterID;
  //Next lines only needed, if the uz_FOC is used as the controller
  extern uz_CurrentControl_t* CC_instance;
  extern uz_SpeedControl_t* SC_instance;
  extern uz_SetPoint_t* SP_instance;
  uz_3ph_dq_t ParaID_v_dq = { 0 };
  struct uz_DutyCycle_t ParaID_DutyCycle = { 0 };

  void ISR_Control(void *data) {  
     ParaID_Data.ActualValues.I_abc.a = ....;
	ParaID_Data.ActualValues.I_abc.b = ....;
	ParaID_Data.ActualValues.I_abc.c = ....;
	ParaID_Data.ActualValues.V_DC = ....;
	ParaID_Data.ActualValues.V_abc.a = ....;
	ParaID_Data.ActualValues.V_abc.b = ....;
	ParaID_Data.ActualValues.V_abc.c = ....;

	ParaID_Data.ActualValues.omega_m = ....;
	ParaID_Data.ActualValues.omega_el = ....;
	ParaID_Data.ActualValues.theta_el = ....;

	//Calculate missing ActualValues
	ParaID_Data.ActualValues.i_dq = uz_transformation_3ph_abc_to_dq(ParaID_Data.ActualValues.I_abc, ParaID_Data.ActualValues.theta_el);
	ParaID_Data.ActualValues.v_dq = uz_transformation_3ph_abc_to_dq(ParaID_Data.ActualValues.V_abc, ParaID_Data.ActualValues.theta_el);
	ParaID_Data.ActualValues.theta_m = ....;

     if (ultrazohm_state_machine_get_state() == control_state) {
          uz_ParameterID_step(ParameterID, &ParaID_Data);
          //Next lines only needed, if the uz_FOC is used as the controller
          ParaID_v_dq = uz_ParameterID_Controller(&ParaID_Data, CC_instance, SC_instance, SP_instance);
          ParaID_DutyCycle = uz_ParameterID_generate_DutyCycle(&ParaID_Data, ParaID_v_dq, Global_Data.objects.pwm_d1_pin_0_to_5);
          Global_Data.rasv.halfBridge1DutyCycle = ParaID_DutyCycle.DutyCycle_A;
          Global_Data.rasv.halfBridge2DutyCycle = ParaID_DutyCycle.DutyCycle_B;
          Global_Data.rasv.halfBridge3DutyCycle = ParaID_DutyCycle.DutyCycle_C;
	} else {
          Global_Data.rasv.halfBridge1DutyCycle = 0.0f;
          Global_Data.rasv.halfBridge2DutyCycle = 0.0f;
          Global_Data.rasv.halfBridge3DutyCycle = 0.0f;
     }
    }

In the ``javascope.c`` the measurement values from ``ActualValues`` struct should be assigned to the ``js_ch_observable`` array.

.. code-block:: c
  :linenos:
  :caption: changes to javascope.c

  extern uz_ParameterID_Data_t ParaID_Data;  
  
  int JavaScope_initalize(DS_Data* data) {
     ....
     js_ch_observable[JSO_Speed_rpm]		= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_ia] = &ParaID_Data.ActualValues.I_abc.a;
	js_ch_observable[JSO_ib] = &ParaID_Data.ActualValues.I_abc.b;
	js_ch_observable[JSO_ic] = &ParaID_Data.ActualValues.I_abc.c;
	js_ch_observable[JSO_ua] = &ParaID_Data.ActualValues.V_abc.a;
	js_ch_observable[JSO_ub] = &ParaID_Data.ActualValues.V_abc.b;
	js_ch_observable[JSO_uc] = &ParaID_Data.ActualValues.V_abc.c;
	js_ch_observable[JSO_iq] = &ParaID_Data.ActualValues.i_dq.q;
	js_ch_observable[JSO_id] = &ParaID_Data.ActualValues.i_dq.d;
	js_ch_observable[JSO_Theta_el] = &ParaID_Data.ActualValues.theta_el;
	js_ch_observable[JSO_theta_mech] = &ParaID_Data.ActualValues.theta_m;
	js_ch_observable[JSO_ud] = &ParaID_Data.ActualValues.v_dq.d;
	js_ch_observable[JSO_uq] = &ParaID_Data.ActualValues.v_dq.q;
     ....
     }  

The ParameterID is now setup and can be controlled via the debugger window. Since this is not a practical task, the :ref:`Javascope` has a separate panel to control the ParmaeterID. 
The additional setup steps are detailed in :ref:`uz_ParaID_GUI_setup`.

Functions
=========

.. doxygenfunction:: uz_ParameterID_init

This function inits the ParameterID itself and all subsequent states. 
Even though not all states my be used by the user, they will be initialized anyway. 
This is done to ensure data integrity and to guarantee, that every member of the :ref:`uz_ParameterID_Data_struct` is declared. 
Furthermore the :ref:`uz_ParameterID_Data_struct` itself is initialized here as well.  

.. doxygenfunction:: uz_ParameterID_step

This function steps the ParameterID once per cycle. It implements everything necessary shown in the blue block in :numref:`ParaID_overview_schematic`. 
To eliminate unnecessary function calls and improve the execution time of this function, only the :ref:`uz_ControlState` will always be stepped. 
Every other ``ID-state`` is guarded behind if-statements. Furthermore it determines, which :ref:`uz_Controller_parameters_struct` will be written to the output. 

.. doxygenfunction:: uz_ParameterID_generate_DutyCycle
.. doxygenfunction:: uz_ParameterID_Controller
.. doxygenfunction:: uz_ParameterID_CleanPsiArray
.. doxygenfunction:: uz_ParameterID_CalcFluxMaps
.. doxygenfunction:: uz_ParameterID_update_transmit_values

References
==========

.. doxygentypedef:: uz_ParameterID_t
.. doxygentypedef:: real32_T
.. doxygentypedef:: boolean_T
.. doxygentypedef:: uint16_T
