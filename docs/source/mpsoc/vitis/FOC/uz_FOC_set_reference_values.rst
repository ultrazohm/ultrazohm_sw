.. _uz_FOC_set_ref_values:

========================
Set new reference values
========================

.. doxygenfunction:: uz_FOC_set_id_ref

.. doxygenfunction:: uz_FOC_set_iq_ref

.. doxygenfunction:: uz_FOC_set_n_ref

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the reference values. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     float id_ref = 0.058f;
     uz_FOC_set_id_ref(FOC_instance, float id_ref);
     float iq_ref = 4.0f;
     uz_FOC_set_iq_ref(FOC_instance, float iq_ref);
     float n_ref_rpm = 400.0f;
     uz_FOC_set_n_ref(FOC_instance, float n_ref_rpm);
  }

Description
===========

Gives the option to change the reference values for CurrentControl or SpeedControl during runtime. 
