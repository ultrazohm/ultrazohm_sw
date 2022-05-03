.. _uz_SpeedControl_set_field_weak:

===================
Set field weakening
===================

.. doxygenfunction:: uz_SpeedControl_set_field_weakening

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SpeedControl_init>`.

  int main(void) {
  bool field_weakening = true;
     uz_SpeedControl_set_field_weakening(SpeedControl_instance, field_weakening);
  }

Description
===========

Activates or disables the field weakening of the SpeedControl. 
Since the object could've been initialized with the members of the ``uz_PMSM_t`` struct set to 0, all members of this struct will be asserted as well.
 