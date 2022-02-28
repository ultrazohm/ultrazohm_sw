.. _uz_FluxMapID:

=========
FluxMapID
=========

This state includes an process for FluxMap identification. 
It is based on [[#Hoerner_Masterthesis]_] and has been modified to fit into the ParameterID library of the UltraZohm.
The desired range of the identified flux maps can be set in the d- and q-axis, with an input for the stepsize as well. 
From these input parameters, this state will create a rectangular grid. 
Each point of this grid will be set and reference currents will be given to an external current controller. 
This state needs some sort of current controller to work properly. 
It does NOT measure the needed signals to calculate the flux maps in each point. 
It only controls the triggering of the operating points. 
The necessary measurement vales can either be captured via the :ref:`JavaScope` or an external measurement device.
For this purpose a trigger, when appropriate, signals the point of time, at which the measurement of this operating point can take place. 


.. doxygentypedef:: uz_PID_FluxMapID_t


.. doxygenstruct:: uz_PID_FluxMapIDConfig_t
  :members: 

.. doxygenstruct:: uz_PID_FluxMapID_output_t
  :members:

.. doxygenfunction:: uz_FluxMapID_init
.. doxygenfunction:: uz_FluxMapID_step

Sources
-------

.. [#Hoerner_Masterthesis] Automatisierte Identifikation nichtlinearer Flusskennfelder permanenterregter Synchronmaschinen, Michael Hoerner, 2018