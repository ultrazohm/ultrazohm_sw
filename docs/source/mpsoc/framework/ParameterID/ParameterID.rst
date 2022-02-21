.. _uz_ParameterID:

===========
ParameterID
===========

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
  
Global structs
==============

The following structs are all shared between the different ID-states.

..  toctree::
    :maxdepth: 1
    
    Global_structs/ParameterID_structs

Stateflows
==========

The following structs are all shared between the different ID-states.

..  toctree::
    :maxdepth: 1
    
    stateflows/uz_AutoRefCurrents
    stateflows/uz_ElectricalID
    stateflows/uz_FluxMapID
    stateflows/uz_FrictionID
    stateflows/uz_OnlineID
    stateflows/uz_TwoMassID
    
