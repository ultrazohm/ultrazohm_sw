===================
Get clamping signal
===================

.. doxygenfunction:: uz_SetPoint_get_clamping

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call. Init of instance via :ref:`init-function <uz_SetPoint_init>`.

  int main(void) {
     bool clamping = uz_SetPoint_get_clamping(instance);
  }

Description
===========

If the SetPoint module operates in the field-weakening territory of the machine and :math:`i_q` current is limited, this function will return true.
This signal can be given to e.g. a SpeedControl.
This prevents the integrator in e.g. the SpeedControl from continuously rising.