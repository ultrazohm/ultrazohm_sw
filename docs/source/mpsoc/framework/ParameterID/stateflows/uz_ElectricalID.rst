.. _uz_ElectricalID:

============
ElectricalID
============

This state includes an automated identification process for typical parameters of a PMSM. 
It is based on [[#Hoerner_ProjectReport2]_] and has been modified to fit into the ParameterID library of the UltraZohm.
This includes the identification of the polepairs, theta_offset of a incremental encoder, Rs, Ld, Lq, Psi_PM and J. 
The control parameters of a FOC will be calculated with the identified parameters and are therefore tuned for the used machine. 
This state requires some sort of speed control.

This state does require multiple ACCEPT flags to continue, since for the identification of Lq a manual operation on the motor has to be done.

After ``activeState`` equals 141, the ElectricalID is waiting for another ACCEPT. Before the ACCEPT flag is given, the user has to decide if he wants to identify Lq. 
If Lq should not be identified, the algorithm will treat Lq equal to Ld and continue with the identification of Psi_PM after the ACCEPT is given. 

If Lq should be identified however, the rotor has to be locked before giving the ACCEPT signal.
After Lq has been identified, the rotor has to be unlocked again. After pressing ACCEPT again, the algorithm will continue with the identification of Psi_PM. 

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

Sources
-------

.. [#Hoerner_ProjectReport2] Automated parameter identification of fractional horsepower permanent magnet synchronous motors, Michael Hoerner, 2017