.. _uz_ssi_interface:

=============
SSI Interface
=============

In the event that the quotient of the IP-core clock frequency and two times the SSI 
clock frequency is not an integer number, the resulting clock divider will be rounded 
up to the next larger integer. This will result in a slightly lower SSI clock frequency 
without notification to the user.

One can chose between two ways of getting the output values. First, simply call update_all_outputs if you dont care about isr time, 
second for each output there exists an own get function which only gives the respective return value, and employs only the specific 
necessary AXI4 read operation. This safes isr time, e.g., when you only need two values instead of five.

Driver reference
----------------

.. doxygentypedef:: uz_ssi_interface_t

.. doxygenstruct:: uz_ssi_interface_config_t
  :members:

.. doxygenstruct:: uz_ssi_interface_outputs_t
  :members:  

.. doxygenfunction:: uz_ssi_interface_init