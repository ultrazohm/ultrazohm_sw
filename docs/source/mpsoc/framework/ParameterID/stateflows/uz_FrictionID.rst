.. _uz_FrictionID:

==========
FrictionID
==========
This state includes an automated identification process for different friction/torque parameters. 
It is based on [[#Gebhardt_ProjectReport1]_] and has been modified to fit into the ParameterID library of the UltraZohm.
The breakaway torque, coloumb torque and viscous friction torque will be identified. 
This state requires some sort of speed control. 

.. doxygentypedef:: uz_PID_FrictionID_t


.. doxygenstruct:: uz_PID_FrictionIDConfig_t
  :members: 

.. doxygenstruct:: uz_PID_FrictionID_output_t
  :members:

.. doxygenfunction:: uz_FrictionID_init
.. doxygenfunction:: uz_FrictionID_step

Sources
-------

.. [#Gebhardt_ProjectReport1] Automatic identification of the frictional behaviour of permanent magnet synchronous machines, Philipp Gebhardt, 2018