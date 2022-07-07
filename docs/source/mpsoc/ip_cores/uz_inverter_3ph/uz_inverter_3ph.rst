.. _uz_inverter_3ph:

==============
Inverter Model
==============

- IP-Core of a 3 phase inverter
- Simulates the inverter on the FPGA
- Intended for controller-in-the-loop (CIL) on the UltraZohm
- IP-Core clock frequency **must** be :math:`f_{clk}=100\,MHz`!

Model Description
=================

The highest level of the inverter model is called ``uz_inverter_3ph.slx`` and contains the Simscape model of the inverter. 
The model is based around six N-channes MOSFET from the Simscape parts library. 
The power electronic is controller via the ``gate_ps`` or ``gate_pl`` input port, of which one can be selected as active input with the switch ``pspl_gate port``. 
The DC bus voltage can be set via the ``u_dc`` port. 
To find out the current output voltages, the ``u_abc_ps`` and ``u_abc_pl`` ports can be used. 
Note that the output voltages will be line-line voltages, meaning they are :math:`u_{ab},u_{bc},u_{ca}`. 
To keep the influence of the non-ideal switches in the non-physical modelled environment after the ip-core generation, the ``i_abc_ps`` or ``i_abc_pl`` ports are used to tell the ip-core the flowing currents at each time. 
The respective input can be selected via the "switch_pspl_abc" port. 
Note that the parameters of the switches are set inside the Simscape model and can no longer be changed after ip-core generation. 

.. csv-table:: Parameter Switch (MOSFET and body diode)
   :file: ./MOSFET_parameter.csv
   :widths: 50 50 50
   :header-rows: 1


..	figure:: ./inverter_overview.svg
   :width: 800
   :align: center

   Overview of Simscape inverter model.


IP-Core Interfaces
==================

.. csv-table:: IP-core Interfaces Switch
   :file: ./inverter_interfaces.csv
   :widths: 50 50 50 50
   :header-rows: 1


Driver Reference
================

.. doxygentypedef:: uz_inverter_3ph_t

.. doxygenstruct:: uz_inverter_3ph_config_t
  :members:

.. doxygenstruct:: uz_inverter_3ph_gate_ps_t
  :members:

.. doxygenfunction:: uz_inverter_3ph_init

.. doxygenfunction:: uz_inverter_3ph_get_u_abc_ps

.. doxygenfunction:: uz_inverter_3ph_set_i_abc_ps

.. doxygenfunction:: uz_inverter_3ph_set_gate_ps

.. doxygenfunction:: uz_inverter_3ph_trigger_u_abc_ps_strobe

.. doxygenfunction:: uz_inverter_3ph_trigger_i_abc_ps_strobe

.. doxygenfunction:: uz_inverter_3ph_trigger_gate_ps_strobe


Reference
=========

“Troubleshoot conversion of simscape permanent magnet synchronous motor to hdlcompatible simulink model.” [Online]. Available: https://de.mathworks.com/help/releases/R2021a/hdlcoder/ug/troubleshoot-generate-implementation-model-from-simscape-pmsm.html