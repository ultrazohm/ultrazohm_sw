.. _uz_AutoRefCurrents:

=====================================
Automatic reference current generator
=====================================

Description
===========

This state is not an identification state. It merely assists the :ref:`uz_OnlineID` state.
It gives out reference currents of a circular determined current map to quickly cycle through different operating points and therefore identify flux map values over a wide operating point.
It has an input for the speed, so that only the appropriate q-current to the rotation direction is set. This prevents the DC-source from having to deal with feed back. 
It already is embedded in the :ref:`uz_ParaID_OnlineID_object`.


Necessary measurement values
============================

* omega_m

.. _uz_ParaID_AutoRefCurrents_object:

AutoRefCurrents object
======================

.. doxygentypedef:: uz_ParaID_AutoRefCurrents_t

.. _uz_ParaID_AutoRefCurrentsConfig:

AutoRefCurrents config
======================

.. doxygenstruct:: uz_ParaID_AutoRefCurrentsConfig_t
  :members: 

.. _uz_ParaID_AutoRefCurrentsoutput:

AutoRefCurrents output
======================

.. doxygenstruct:: uz_ParaID_AutoRefCurrents_output_t
  :members:

.. _uz_ParaID_AutoRefCurrents_functions:

AutoRefCurrents functions
=========================

.. doxygenfunction:: uz_AutoRefCurrents_init
.. doxygenfunction:: uz_AutoRefCurrents_step
.. doxygenfunction:: uz_AutoRefCurrents_set_Config
.. doxygenfunction:: uz_AutoRefCurrents_set_ActualValues
.. doxygenfunction:: uz_AutoRefCurrents_set_GlobalConfig
.. doxygenfunction:: uz_AutoRefCurrents_set_ControlFlags
.. doxygenfunction:: uz_AutoRefCurrents_get_output


