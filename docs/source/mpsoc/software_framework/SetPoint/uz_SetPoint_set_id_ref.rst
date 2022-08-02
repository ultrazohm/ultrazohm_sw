.. _uz_SetPoint_set_id_ref:

=================================
Set :math:`i_d` reference current
=================================

.. doxygenfunction:: uz_SetPoint_set_id_ref

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SetPoint_init>`.

  int main(void) {
    float id_ref_Ampere = 2.5f;
    uz_SetPoint_set_id_ref(instance, id_ref_Ampere);
  }


Description
===========

Sets a new value for the reference :math:`i_d` current. This will overwrite, if possible, the MTPA and field-weakening :math:`i_d` current.
