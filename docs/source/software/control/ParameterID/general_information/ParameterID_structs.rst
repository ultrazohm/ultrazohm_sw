.. _uz_ParameterID_Data_structs:

============================
Structs for ParameterID_Data
============================

Every used struct, which is unique to the ParameterID, is declared in a separate header ``uz_ParameterID_data.h``. This includes the global structs and individual structs of each ``ID-state``. 
They are all declared in the common header to ensure data integrity over each separate ``ID-state``.
Listed below are the global structs, which are not specific to one individual state.

.. doxygenenum:: uz_ParaID_Control_selection

.. _uz_ParameterID_Data_struct:

Global ParameterID Data struct
==============================

This struct is used to communicate with the ParameterID object. It is therefore intended as the data-out- and -input of the ParameterID.
The ParameterID will check for updated config values during runtime and adjust itself accordingly.
During each step of the ParameterID, the members of each output struct are automatically updated to the latest values. 
In order to save execution time, the output structs of the ``ID-states`` are realized as pointers since some ``ID-states`` have large arrays as part of their output struct. 
Using ``memcpy`` is therefore not performant enough. 

.. doxygenstruct:: uz_ParameterID_Data_t
  :members: 

.. _uz_Actual_values_struct:

Actual values struct
====================

This struct carries all the measurement data needed for the ParameterID. They are passed to the ParameterID object through the :ref:`ParameterID_Data struct<uz_ParameterID_Data_struct>`. 
Some states may not need every measurement value listed below. For further details on this, check the individual pages of the existing :ref:`uz_ParaID_ID_states`.

.. doxygenstruct:: uz_ParaID_ActualValues_t
  :members:

.. _uz_Global_config_struct:

Global config struct
====================

This struct carries all configuration values of the ParameterID, which affect multiple states. It consists of request flags for the individual ``ID-states``, initial controller configuration and motor configuration values,
ACCEPT and RESET flags, etc. Depending on the setup, some configuration values can be left at 0. For further information, check each struct member's description.

.. doxygenstruct:: uz_ParaID_GlobalConfig_t
  :members: 

.. _uz_Control_flags_struct:

Control flags struct
====================

This struct carries the enable signals for the individual ``ID-states``. 

.. doxygenstruct:: uz_ParaID_ControlFlags_t
  :members:

.. _uz_Controller_parameters_struct:

Controller parameters struct
============================

This struct bundles all the necessary commands and values for the external control algorithm. 
Some variables are geared toward a FOC-controller and, therefore, can be ignored if another control algorithm is used.

.. doxygenstruct:: uz_ParaID_Controller_Parameters_output_t
  :members:

.. _uz_FluxMap_data_struct:

FluxMap data struct
===================

This struct bundles all necessary information for the flux maps of the OnlineID state.

.. doxygenstruct:: uz_ParaID_FluxMapsData_t
  :members:

Controller objects struct
=========================

This struct bundles all necessary controller pointers for the external controller algorithm.

.. doxygenstruct:: uz_ParameterID_controller
  :members: