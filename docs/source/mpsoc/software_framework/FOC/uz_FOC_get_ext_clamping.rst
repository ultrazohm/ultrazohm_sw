.. _uz_FOC_get_ext_clamping:

===========================
Get external clamping value
===========================

.. doxygenfunction:: uz_FOC_get_ext_clamping

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to get the ext_clamping value. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     float ext_clamping = uz_FOC_get_ext_clamping(FOC_instance);
  }

Description
===========

Returns the latest value of the ext_clamping value of the FOC_instance. 