.. _uz_SetPoint_set_field_weak:

===================
Set field weakening
===================

.. doxygenfunction:: uz_SetPoint_set_field_weakening

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SetPoint_init>`.

  int main(void) {
    bool field_weakening = true;
    uz_SetPoint_set_field_weakening(instance, field_weakening);
  }


Description
===========

Activates or disables the field weakening of the SetPoint module. 
