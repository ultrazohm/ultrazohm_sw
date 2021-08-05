.. _uz_FOC_set_polePairs:

=================
Set new polePairs
=================

.. doxygenfunction:: uz_FOC_set_polePairs

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call to change the polePair value. FOC-Instance via :ref:`init-function <uz_FOC_init>`

  int main(void) {
     float polePairs = 5.0f;
     uz_FOC_set_polePairs(FOC_instance, float polePairs);
  }

Description
===========

Gives the option to change the ``polePairs`` value during runtime and asserts the input. 
Input value must be greater than 0.0f and is not allowed to have decimal points (i.e. no 2.5f).
