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
        float coefficients_data[5] = {2.0f, -20.5f, -5.0f, 0.0f, 1.0f};
        float derivate_poly_coefficients_data[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        struct uz_newton_raphson_config config = {
            .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
            .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
            .coefficients.length = UZ_ARRAY_SIZE(coefficients),
            .coefficients.data = &coefficients[0],
            .initial_value = 5.0f,
            .iterations = 5U,
        };
        uz_newton_raphson_derivate(config);
    }

Description
===========

For proper memory handling, the derivate array has to be pre-initialized.
The values can be left at 0, since they will be overwritten by the function anyway.
The derivate array has to be of the size of the original array minus 1. 
Otherwise an assertion triggers.
This function assumes, that all powers of the polynomial are a positive natural value (i.e. 0,1,2,3.....).
This means, this function can't be used to calculate the derivate of e.g. a square-root.

The input is wrapped in the :ref:`uz_newton_raphson_config struct <uz_newton_raphson>`.
This function only calculates the derivate part, i.e. the factor from the derivate calculation (x^4 -> ``4`` x^3). 
The coefficients (a0,a1,a2,a3,a4,etc.) are stored separately in the coefficients array. 

Considering the following equation:

.. math::

  f(x) &= x^4 - 5x^2 - 20.5x + 2\\
  f'(x) &= 4x^3 - 10x - 20.5\\

After the function finished, the derivate-array would look like this:

.. code-block:: c

    derivate_poly_coefficients[4] = {1.0f, 2.0f, 0.0f, 4.0f};
