.. _uz_ParameterID_Data_structs:

============================
Structs for ParameterID_Data
============================

Explains the global structs, which are not specific to one individual

.. doxygenenum:: uz_PID_Control_selection

.. _uz_ParameterID_Data_struct:

Global ParameterID Data struct
==============================

This struct is used to communicate with the ParameterID object. It is therefore intended as the data-out- and -input of the ParameterID.
The ParameterID will check for updated config-values during runtime and adjust itself accordingly.
During each step of the ParameterID the members of each output-struct are automatically updated to the latest values. 
In order to safe execution time the output-structs of the ``ID-states`` are realized as pointers, since some ``ID-states`` have large arrays as part of their output-struct. 
Using ``memcpy`` is therefore not performant enough. 

.. doxygenstruct:: uz_ParameterID_Data_t
  :members: 

.. _uz_Actual_values_struct:

Actual values struct
====================

This struct carries all the measurement data needed for the ParameterID. They are passed to the ParameterID object through the :ref:`ParameterID_Data struct<uz_ParameterID_Data_struct>`. 
Some states may not need every measurement value listed below. For further details on this, check the individual pages of the existing :ref:`uz_PID_ID_states`.

.. doxygenstruct:: uz_PID_ActualValues_t
  :members:

.. _uz_Global_config_struct:

Global config struct
====================

.. doxygenstruct:: uz_PID_GlobalConfig_t
  :members: 

.. _uz_Control_flags_struct:

Control flags struct
====================

.. doxygenstruct:: uz_PID_ControlFlags_t
  :members:

.. _uz_Controller_parameters_struct:

Controller parameters struct
============================

.. doxygenstruct:: uz_PID_Controller_Parameters_output_t
  :members:

.. _uz_FluxMap_data_struct:

FluxMap data struct
===================

.. doxygenstruct:: uz_PID_FluxMapsData_t
