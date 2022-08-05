.. _uz_newton_raphson_derivate:

===============================
Polynomial derivate calculation
===============================

This function calculates the derivate :math:`f'(x)` of the original function :math:`f(x)`.

.. doxygenfunction:: uz_newton_raphson_derivate

Example
=======

.. code-block:: c

    #include "../uz/uz_newton_raphson/uz_newton_raphson.h"
    int main(void) {
        float poly_coefficients_data[5] = {1.0f, 1.0f, 1.0f, 0.0f, 1.0f};
        float derivate_poly_coefficients_data[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        uz_array_float_t poly_coefficients = {
          .length = UZ_ARRAY_SIZE(poly_coefficients_data),
          .data = &poly_coefficients_data[0],
        };
        uz_array_float_t derivate_poly_coefficients = {
          .length = UZ_ARRAY_SIZE(derivate_poly_coefficients_data),
          .data = &derivate_poly_coefficients_data[0],
        };
        uz_newton_raphson_derivate(poly_coefficients, derivate_poly_coefficients);
    }

Description
===========

For proper memory handling, the derivate array has to be pre-initialized.
The values can be left at 0, since they will be overwritten by the function anyway.
The derivate array has to be of the size of the original array minus 1. 
Otherwise an assertion triggers.
This function assumes, that all powers of the polynomial are a positive natural value (i.e. 0,1,2,3.....).
This means, this function can't be used to calculate the derivate of e.g. a square-root.

Considering the following equation:

.. math::

  f(x) &= x^4 - 5x^2 - 20.5x + 2\\
  f'(x) &= 4x^3 - 10x - 20.5\\

After the function finished, the derivate-array would look like this:

.. code-block:: c

    derivate_poly_coefficients[4] = {-20.5f, -10.0f, 0.0f, 4.0f};
