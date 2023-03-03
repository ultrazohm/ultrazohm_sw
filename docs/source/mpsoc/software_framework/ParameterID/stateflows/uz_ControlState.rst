.. _uz_ControlState:

============
ControlState
============

Description
===========

This state controls all the other states. 
It decides, based on user input, which state is executed and in which order. 
This is done via ControlFlags and finished/entered Flags of the individual states. 
If multiple ``ID-states`` are requested, the ControlState will start the next one after the previous one has finished and the ACCEPT button has been pressed. 
This is an integral part of the ParameterID and must always be implemented. 

.. _uz_ParaID_ControlState_object:

ControlState object
===================

.. doxygentypedef:: uz_ParaID_ControlState_t

.. _uz_ParaID_ControlState_functions:

ControlState functions
======================

.. doxygenfunction:: uz_ControlState_init
.. doxygenfunction:: uz_ControlState_step
.. doxygenfunction:: uz_ControlState_set_finishedFrictionID
.. doxygenfunction:: uz_ControlState_set_finishedElectricalID
.. doxygenfunction:: uz_ControlState_set_finishedTwoMassID
.. doxygenfunction:: uz_ControlState_set_finishedFluxMapID
.. doxygenfunction:: uz_ControlState_set_enteredFrictionID
.. doxygenfunction:: uz_ControlState_set_enteredFluxMapID
.. doxygenfunction:: uz_ControlState_set_enteredTwoMassID
.. doxygenfunction:: uz_ControlState_set_enteredElectricalID
.. doxygenfunction:: uz_ControlState_set_enteredOnlineID
.. doxygenfunction:: uz_ControlState_set_ElectricalID_output
.. doxygenfunction:: uz_ControlState_set_GlobalConfig
.. doxygenfunction:: uz_ControlState_set_ElectricalID_FOC_output
.. doxygenfunction:: uz_ControlState_get_GlobalConfig
.. doxygenfunction:: uz_ControlState_get_ControlFlags