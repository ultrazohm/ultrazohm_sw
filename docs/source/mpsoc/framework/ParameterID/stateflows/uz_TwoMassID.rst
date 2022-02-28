.. _uz_TwoMassID:

=========
TwoMassID
=========
This state includes an automated identification process for typical parameters of a two mass system. 
This state is based on [[#Gebhardt_ProjectReport2]_], but has been modified slightly to fit into the ParameterID library of the UltraZohm.
This includes the inertia of the motor and load side, as well as the stiffness and damping of the system. 
This state requires some sort of speed control. 


.. doxygentypedef:: uz_PID_TwoMassID_t

.. doxygenstruct:: uz_PID_TwoMassIDConfig_t
  :members: 

.. doxygenstruct:: uz_PID_TwoMassID_output_t
  :members:

.. doxygenfunction:: uz_TwoMassID_init
.. doxygenfunction:: uz_TwoMassID_step

Sources
-------

.. [#Gebhardt_ProjectReport2] Automatisierte Identifikation mechanischer Parameter in elektrisch angetriebenen Antriebssträngen, Philipp Gebhardt, 2019