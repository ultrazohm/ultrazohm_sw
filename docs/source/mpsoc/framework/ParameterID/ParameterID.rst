.. _uz_ParameterID:

===========
ParameterID
===========

Toolbox for different code-generated stateflows to identify common parameters of a permanent magnet synchronous motor. This page deals with the setup in the UltraZohm workspace. 
For a more in depth explanation of the ParameterID please visit :ref:`uz_PID_general_information`, :ref:`uz_ParameterID_Data_structs` and :ref:`uz_PID_new_ID_state`.

Further information
===================

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

During this step, the struct of the type ``uz_ParameterID_Data_t`` is initialized as well. This struct carrys, among other things, the configuration values of the ParameterID.
To ease the setup of the ParameterID, this struct is initialized with default values. 
To configure the ParameterID to your needs, change the values inside the ``uz_ParameterID_initialize_data_structs`` function. 
Especially the configuration of the motor-related parameters is important. If they are not known, they can be left at 0.0f. In this case however, these parameters have to be identified first by using the :ref:`uz_ElectricalID` state. 
The ID-state specific configuration values can later be configured via the uz_GUI. 

.. literalinclude:: ../../../../../vitis/software/Baremetal/src/uz/uz_ParameterID/uz_ParameterID.c
    :lines: 434-526
    :linenos:
    :language: c

General information & explanation
*********************************

Further documentation which explains the structure of the ParameterID in detail.

..  toctree::
    :maxdepth: 1
    
    general_information/general_information
    general_information/ParameterID_structs
    general_information/create_new_id_state
  
Stateflows
**********

Listed are the individual states which are part of the ParameterID.

..  toctree::
    :maxdepth: 1
    
    stateflows/uz_AutoRefCurrents
    stateflows/uz_ElectricalID
    stateflows/uz_FluxMapID
    stateflows/uz_FrictionID
    stateflows/uz_OnlineID
    stateflows/uz_TwoMassID
    
.. doxygentypedef:: uz_ParameterID_t


.. doxygenfunction:: uz_ParameterID_init
.. doxygenfunction:: uz_ParameterID_step
.. doxygenfunction:: uz_ParameterID_generate_DutyCycle
.. doxygenfunction:: uz_ParameterID_Controller
.. doxygenfunction:: uz_ParameterID_CleanPsiArray
.. doxygenfunction:: uz_ParameterID_CalcFluxMaps

.. doxygentypedef:: real32_T
.. doxygentypedef:: boolean_T
.. doxygentypedef:: uint16_T
.. doxygentypedef:: uint8_T