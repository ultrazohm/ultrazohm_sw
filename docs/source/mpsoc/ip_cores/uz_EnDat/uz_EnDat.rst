.. _ipCore_EnDat:

=======
EnDat22
=======

The EnDat22 IP-Core (``EnDat``) evaluates signals of an EnDat22 based absolute singleturn encoders and is compatible to :ref:`dig_encoder_v1`.
It features the positional and speed calculation. 

Position
  Positional information for the actual and the two values before is available. The actual position can also provide its age. The position is available in radiant inside the driver environment and in raw values in the FPGA environment. 

Time difference
  The time difference between two positional information is available in the FPGA and the SOC Part. It is used to calculate the rotational speed and useful to have an estimation of the frequency for new positional values.

Positional difference
  The raw positional difference is available solely inside the SOC Part and facilitates the calculation of rotational speed.

Rotational Speed
  The speed is calculated in the driver and can be output with RPM or RAD/s and ca n be filtered by a configurable filter. 


IP-Core Hardware
================

The IP-Core is generated using Matlab/Simulink HDL-Coder based on the model ``UZ_EnDat.slx`` (in ``ultrazohm_sw/ip_cores/uz_EnDat_IPCore/Simulink_Model/UZ_EnDat.slx``).


Vivado integration
------------------

.. figure:: uz_EnDat_vivado.png
  :align: center

  Vivado block design of EnDat22 IP-Core.

.. warning:: The IP-Core (IPCORE_CLK) has to be sourced by a clock with :math:`100 MHz`! The auxialliary clock (CLK50MHZ) has to be fed with a :math:`50 MHz` Signal


Table *Interfaces of the EnDat22 IP-Core* lists all input and output ports (AXI and external port) that are present in the IP-Core.

.. csv-table:: Interfaces of the EnDat22 IP-Core
   :file: uz_EnDat_register_mapping.csv
   :widths: 50 50 50 50 200
   :header-rows: 1
   :align: center


Software driver
===============

The software driver for the IP-Core has multiple use cases - with the configuration and calculation beeing the most important ones. 

Init Functions
---------------
.. doxygentypedef:: uz_EnDat_t
.. doxygentypedef:: controlword
.. c:type:: uint8_t

.. doxygenfunction:: uz_EnDat_IP_core_init

This function initializes a 25-Bit EnDat22 sensor with default settings. The IP-Core has to be named "uz_EnDat_0" in Vivado and have an operating frequency of 100 MHz.
Use this function to initialize the sensortype ECN125 without further adjustment necessary. Generally this method is not advised to be used due to its inflexibility.

.. doxygenfunction:: uz_EnDat_IP_core_custom_init

This function initializes a EnDat22 sensor using settings and supporting various sensor resolutions. The IP-Core has to be named "uz_Endat_0" in Vivado and have an operating frequency of 100 MHz.
For adjusting the configuration of the EnDat22 sensor, please edit the file ``uz_EnDat_IP_core_init.c``. Changes during runtime are prohibited.

.. doxygenfunction:: uz_EnDat_IP_core_expert_init

This function is the most flexible one when it comes to configuration of the IP-Core since every parameter is handed over by the call function. The name of the IP-Core the frequency are adjustable and multiple instances are possible.
You should not deviate from the 100 MHz Clock however. Keep in mind that using this Init-Method no default values are provided and one must carefully set every setting manually. 

Control Functions
-----------------

There are multiple functions and settings used to control the IP-Core. The most basic way of controlling the IP-Core is the controlword.

Table *Controlword* shows the content of the controlword to the IP-Core.

.. csv-table:: EnDat22 IP-Core controlword
   :file: uz_EnDat_controlword.csv
   :widths: 25 25 75 50
   :header-rows: 1
   :align: center

An exemplary control word would look like this: *0xB407* for an 25-Bit EnDat22 Sensor.

The sensor operating frequency is set by a divider variable.

.. doxygenenum:: uz_EnDat_frequency_selector

