.. _uz_ElectricalID:

============
ElectricalID
============

This state includes an automated identification process for typical parameters of a PMSM. 
This includes the identification of the polepairs, theta_offset of a incremental encoder, Rs, Ld, Lq, Psi_PM and J. 
The control parameters of a FOC will be calculated with the identified parameters and are therefore tuned for the used machine. 
This state requires some sort of speed control.

ElectricalID object
====================

.. doxygentypedef:: uz_PID_ElectricalID_t

.. _uz_PID_ElectricalIDConfig:

ElectricalID config
===================

.. doxygenstruct:: uz_PID_ElectricalIDConfig_t
  :members: 

.. _uz_PID_ElectricalIDoutput:

ElectricalID output
===================

.. doxygenstruct:: uz_PID_ElectricalID_output_t
  :members: 

.. doxygenfunction:: uz_ElectricalID_init
.. doxygenfunction:: uz_ElectricalID_step

