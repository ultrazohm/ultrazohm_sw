===================
Wrap angle function
===================

.. doxygenfunction:: uz_signals_wrap

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call wrap an angle to the range of 0 to :math:`2\pi`

  #include "uz_signals.h"
  int main(void) {
     theta = 13.0f;
     float theta_wrapped = uz_signals_wrap(theta, 2*UZ_PIf);
  }

Description
===========

Wraps the input number to the range of :math:`[0, limit]` by using the ``remainderf`` function.
Only limits greater than 0 are allowed!
If the number is already in the range, it will be unchanged.
If it is not in the range, ``remainderf`` will be applied.
if the result is positive, it is in the range and will be returned.
Otherwise, the limit is added to the remainder and returned.