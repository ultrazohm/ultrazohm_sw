.. _uz_OnlineID:

========
OnlineID
========

This stateflow is used to detect special transient states and to gather measuring data in these states. 
It is based on [[#Gebhardt_Masterthesis]_ , [#Hufnagel_Masterthesis]_ ] and has been modified to fit into the ParameterID library of the UltraZohm.
It functions as an indefinite loop and continuously identifies its parameters. 
This is done to identify the parameters of the linear pmsm model. 
This includes Rs, Ld, Lq and Psi_PM. The flux maps can be identified aswell. 
With each new operating point the relevant signals are measured and the flux in the specific operating point is calculated. 
Up to 100 unique values will be stored in an array, which will later be cleaned up with external functions. 
In contrast to the FluxMapID state, this state does not actively control the machine via reference currents(except the addition of a injection signal with low amplitude/frequency on top of the reference d-axis current).
Thus it measures and calculates the flux in the operating points. 

To assist the identification of the fluxmaps an :ref:`uz_AutoRefCurrents` does exist. It is an external stateflow purposefully designed for the OnlineID state. 
It gives out reference currents of a circular determined current map to quickly cycle through different operating points and therefore identify fluxmap values over a wide operating point.

.. doxygentypedef:: uz_PID_OnlineID_t

.. doxygenstruct:: uz_PID_OnlineIDConfig_t
  :members: 

.. doxygenstruct:: uz_PID_OnlineID_output_t
  :members:

.. doxygenfunction:: uz_OnlineID_init
.. doxygenfunction:: uz_OnlineID_step

Sources
-------

.. [#Gebhardt_Masterthesis] Automatisierte Online-Identifikation von Systemparametern permanenterregter Synchronmaschinen zur Nachführung im geregelten Betrieb, Philipp Gebhardt, 2020
.. [#Hufnagel_Masterthesis] Optimierte Online-Identifizierung von Flusskennfeldernbei nichtlinearen PMSM über einen weiten Betriebsbereich, Dennis Hufnagel, 2021