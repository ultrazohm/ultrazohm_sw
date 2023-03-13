===================
Wrap angle function
===================

.. doxygenfunction:: uz_wrap_to_2pi

Example
=======

.. code-block:: c
  :linenos:
  :caption: Example function call wrap an angle to the range of 0 to :math:`2\pi`

  #include "uz_signals.h"
  int main(void) {
     theta = 13.0f;
     float theta_wrapped = uz_wrap_to_2pi(theta);
  }

Description
===========

Wraps the input angle to the range of 0 to :math:`2\pi` by using recursion.
If the angle is already in the range, it will be unchanged.
If it is grater than :math:`2\pi`, the function call reduces the angle by :math:`2\pi` and calls itself again, until the angle is smaller than :math:`2\pi`.
If the angle is negative, the functions adds :math:`2\pi` and calls itself again, until the angle is positive.