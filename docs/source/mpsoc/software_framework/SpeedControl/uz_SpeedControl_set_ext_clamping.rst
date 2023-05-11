.. _uz_SpeedControl_set_ext_clamping:

============================
Set external clamping signal
============================

.. doxygenfunction:: uz_SpeedControl_set_ext_clamping

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SpeedControl_init>`.

  int main(void) {
  bool ext_clamping = true;
     uz_SpeedControl_set_ext_clamping(SC_instance, ext_clamping);
  }

Description
===========

Sets the external clamping signal of the PI-Controller to the input value.
If the input is true, the external clamping of the underlying PI-Controller will be activated.