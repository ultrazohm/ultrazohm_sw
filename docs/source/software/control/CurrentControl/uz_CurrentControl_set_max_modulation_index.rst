.. _uz_CurrentControl_set_max_modulation_index:

============================
Set new max modulation index
============================

.. doxygenfunction:: uz_CurrentControl_set_max_modulation_index

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the max modulation index. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     float max_modulation_index = 1.0f/sqrtf(3.0f);
     uz_CurrentControl_set_max_modulation_index(CC_instance, max_modulation_index);
  }

Description
===========

Gives the option to change the max modulation index during runtime. 
This is necessary for the included :ref:`uz_spacevectorlimiation` .
The new value will be asserted and should be larger than 0.0f. 
