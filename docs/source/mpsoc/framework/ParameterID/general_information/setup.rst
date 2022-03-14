.. _uz_PID_setup:

======================================
Setup and functions of the ParameterID
======================================

This page details the steps to setup the ParameterID in the UltraZohm software project. 

Setup
=====

.. code-block:: c
  :linenos:
  :emphasize-lines: 6,12
  :caption: Example to initialize the ParameterID
    
  #include "uz/uz_ParameterID/uz_ParameterID.h"

  //ParameterID Code
  uz_ParameterID_t* ParameterID = NULL;
  uz_ParameterID_Data_t PID_Data = { 0 };
  //Objects below are only needed, if the uz_FOC is used as the controller
  uz_FOC* FOC_instance = NULL;
  uz_PI_Controller* SpeedControl_instance = NULL;

  int main(void) {
      ParameterID = uz_ParameterID_init(&PID_Data);
   //Code below is only needed, if the uz_FOC is used as the controller 
     struct uz_PI_Controller_config config_id = { 
          .Kp = PID_Data.GlobalConfig.Kp_id,
          .Ki = PID_Data.GlobalConfig.Ki_id, 
          .samplingTime_sec = 0.00005f, 
          .upper_limit = 15.0f,
			    .lower_limit = -15.0f };
     struct uz_PI_Controller_config config_iq = { 
          .Kp = PID_Data.GlobalConfig.Kp_iq, 
          .Ki = PID_Data.GlobalConfig.Ki_iq, 
          .samplingTime_sec = 0.00005f, 
          .upper_limit = 15.0f,
			    .lower_limit = -15.0f };
     struct uz_PI_Controller_config config_n = {
          .Kp = PID_Data.GlobalConfig.Kp_n, 
          .Ki = PID_Data.GlobalConfig.Ki_n, 
          .samplingTime_sec = 0.00005f, 
          .upper_limit = 10.0f,
          .lower_limit = -10.0f };
     struct uz_FOC_config config_FOC = {
          .config_PMSM = PID_Data.GlobalConfig.PMSM_config,
          .config_id = config_id, 
          .config_iq = config_iq };
     FOC_instance = uz_FOC_init(config_FOC);
     SpeedControl_instance = uz_SpeedControl_init(config_n);
  }

In the ``uz_ParameterID_init`` function, the struct of the type ``uz_ParameterID_Data_t`` is initialized as well. This struct carries, among other things, the configuration values of the ParameterID.
To ease the setup of the ParameterID, this struct is initialized with default values. 
To configure the ParameterID to your needs, change the values inside the ``uz_ParameterID_initialize_data_structs`` function. 
Especially the configuration of the motor-related parameters is important. If they are not known, they can be left at 0.0f. In this case however, these parameters have to be identified first by using the :ref:`uz_ElectricalID` state. 
The ID-state specific configuration values can later be configured via the uz_GUI. 

.. literalinclude:: ../../../../../../vitis/software/Baremetal/src/uz/uz_ParameterID/uz_ParameterID.c
    :lines: 426-515
    :linenos:
    :emphasize-lines: 12,15-29
    :language: c

If the FluxMaps identification of the :ref:`uz_OnlineID` state will be used, the following code has to be implemented inside the ``while(1) loop`` of the ``main.c``:

.. code-block:: c
  :linenos:
  :caption: Code to calculate FluxMaps inside main.c while(1)-loop
    
  if (PID_Data.OnlineID_Output->clean_array == true) {
	uz_ParameterID_CleanPsiArray(ParameterID, &PID_Data);
  }
  if (PID_Data.calculate_flux_maps == true) {
	uz_ParameterID_CalcFluxMaps(ParameterID, &PID_Data);
	PID_Data.calculate_flux_maps = false;
  }


In the ``isr.c``  the members of the :ref:`uz_Actual_values_struct` struct inside the :ref:`uz_ParameterID_Data_struct` have to be assigned with the measurement values needed for the identification. 
Furthermore, the ``uz_ParameterID_step`` function needs to be called as well. Two functions ``uz_ParameterID_Controller`` and ``uz_ParameterID_generate_DutyCycle`` are used in the code below as well.
These exemplary functions are included in the ParameterID-library, to ease the use of it. They include the uz_FOC and a function to generate the DutyCycles for the halfbridges.
They are technically not required for the ParameterID and can be replaced by your own control algorithm, if desired.

.. code-block:: c
  :linenos:
  :emphasize-lines: 3,29
  :caption: Changes in the isr.c

  extern uz_ParameterID_Data_t PID_Data;
  extern uz_ParameterID_t* ParameterID;
  //Next lines only needed, if the uz_FOC is used as the controller
  extern uz_FOC* FOC_instance;
  extern uz_PI_Controller* SpeedControl_instance;
  struct uz_dq_t PID_v_dq = { 0 };
  struct uz_DutyCycle_t PID_DutyCycle = { 0 };

  void ISR_Control(void *data) {  
  PID_Data.ActualValues.I_UVW.U = ....;
	PID_Data.ActualValues.I_UVW.V = ....;
	PID_Data.ActualValues.I_UVW.W = ....;
	PID_Data.ActualValues.V_DC = ....;
	PID_Data.ActualValues.V_UVW.U = ....;
	PID_Data.ActualValues.V_UVW.V = ....;
	PID_Data.ActualValues.V_UVW.W = ....;

	PID_Data.ActualValues.omega_m = ....;
	PID_Data.ActualValues.omega_el = ....;
	PID_Data.ActualValues.theta_el = ....;

	//Calculate missing ActualValues
	PID_Data.ActualValues.i_dq = uz_dq_transformation(PID_Data.ActualValues.I_UVW, PID_Data.ActualValues.theta_el);
	PID_Data.ActualValues.v_dq = uz_dq_transformation(PID_Data.ActualValues.V_UVW, PID_Data.ActualValues.theta_el);
	PID_Data.ActualValues.theta_m = ....;

	if (ultrazohm_state_machine_get_state() == control_state) {
          uz_ParameterID_step(ParameterID, &PID_Data);
		//Next lines only needed, if the uz_FOC is used as the controller
          PID_v_dq = uz_ParameterID_Controller(&PID_Data, FOC_instance, SpeedControl_instance);
		PID_DutyCycle = uz_ParameterID_generate_DutyCycle(&PID_Data, PID_v_dq, Global_Data.objects.pwm_d1);
		Global_Data.rasv.halfBridge1DutyCycle = PID_DutyCycle.DutyCycle_U;
		Global_Data.rasv.halfBridge2DutyCycle = PID_DutyCycle.DutyCycle_V;
		Global_Data.rasv.halfBridge3DutyCycle = PID_DutyCycle.DutyCycle_W;
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

  extern uz_ParameterID_Data_t PID_Data;  
  
  int JavaScope_initalize(DS_Data* data) {
     ....
     js_ch_observable[JSO_Speed_rpm]		= &data->av.mechanicalRotorSpeed;
	js_ch_observable[JSO_ia] = &PID_Data.ActualValues.I_UVW.U;
	js_ch_observable[JSO_ib] = &PID_Data.ActualValues.I_UVW.V;
	js_ch_observable[JSO_ic] = &PID_Data.ActualValues.I_UVW.W;
	js_ch_observable[JSO_ua] = &PID_Data.ActualValues.V_UVW.U;
	js_ch_observable[JSO_ub] = &PID_Data.ActualValues.V_UVW.V;
	js_ch_observable[JSO_uc] = &PID_Data.ActualValues.V_UVW.W;
	js_ch_observable[JSO_iq] = &PID_Data.ActualValues.i_dq.q;
	js_ch_observable[JSO_id] = &PID_Data.ActualValues.i_dq.d;
	js_ch_observable[JSO_Theta_el] = &PID_Data.ActualValues.theta_el;
	js_ch_observable[JSO_theta_mech] = &PID_Data.ActualValues.theta_m;
	js_ch_observable[JSO_ud] = &PID_Data.ActualValues.v_dq.d;
	js_ch_observable[JSO_uq] = &PID_Data.ActualValues.v_dq.q;
     ....
     }  

The ParameterID is now setup and can be controlled via the debugger window. Since this is not a practical task, a modified uz_GUI is distributed. The additional setup steps are detailed in :ref:`uz_PID_GUI_setup`
Functions
=========

.. doxygenfunction:: uz_ParameterID_init

This function inits the ParameterID itself and all subsequent states. 
Even though not all states my be used by the user, they will be initialized anyway. 
This is done to ensure data integrity and to guarantee, that every member of the :ref:`uz_ParameterID_Data_struct` is declared. 
Furthermore the :ref:`uz_ParameterID_Data_struct` itself is initialized here as well.  

.. doxygenfunction:: uz_ParameterID_step

This function steps the ParameterID once per cycle. It implements everything necessary shown in the blue block in :numref:`PID_overview_schematic`. 
To eliminate unnecessary function calls and improve the execution time of this function, only the :ref:`uz_ControlState` will always be stepped. 
Every other ``ID-state`` is guarded behind if-statements. Furthermore it determines, which :ref:`uz_Controller_parameters_struct` will be written to the output. 

.. doxygenfunction:: uz_ParameterID_generate_DutyCycle
.. doxygenfunction:: uz_ParameterID_Controller
.. doxygenfunction:: uz_ParameterID_CleanPsiArray
.. doxygenfunction:: uz_ParameterID_CalcFluxMaps

References
==========

.. doxygentypedef:: uz_ParameterID_t
.. doxygentypedef:: real32_T
.. doxygentypedef:: boolean_T
.. doxygentypedef:: uint16_T
.. doxygentypedef:: uint8_T
