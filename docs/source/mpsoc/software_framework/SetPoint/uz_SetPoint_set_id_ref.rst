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

Sets a new value for the manual :math:`I_{d,manual}` input current. This value will be added on top of the :math:`I_{d,MTPA}` current.
In FW operation, this value will be ignored.
