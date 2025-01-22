.. _uz_CurrentControl_get_ext_clamping:

===========================
Get external clamping value
===========================

.. doxygenfunction:: uz_CurrentControl_get_ext_clamping

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to get the ext_clamping value. CurrentControl-Instance via :ref:`init-function <uz_CurrentControl_init>`

  int main(void) {
     float ext_clamping = uz_CurrentControl_get_ext_clamping(CC_instance);
  }

Description
===========

Returns the latest value of the ext_clamping value of the CurrentControl_instance. 