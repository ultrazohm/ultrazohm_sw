.. _uz_newton_raphson:

=================================
Newton Raphson root approximation
=================================

The Newton Raphson approximation is an approach for finding the (real-valued) roots of nonlinear equations. 
This is a relative simple, but fast approach. 
The original function :math:`f(x)` as well as the derivate :math:`f'(x)` is required.
This implementation is designed to only work with polynomial functions, i.e., functions that are built from the addition of the exponentiation of variables to a non-negative integer power:
I.e., functions :math:`P(x)` with the following definition

.. math::

  \sum^n_{k=0} a_k x^k=a_n x^n+a_{n-1}x^{n-1}+\dots + a_2 x^2 + a_1 x+a_0

with the coefficients :math:`a_k` and the variable :math:`x`. 
To automatically calculate the derivate, refer to :ref:`uz_newton_raphson_derivate`.
If there are not enough iterations for the approach to converge to the root, the results can be inaccurate.
A balance between computational effort (i.e., number of iterations) and accuracy of the results have to be made by the user.
Solving a 20th order polynomial with 20 iterations takes roughly 20µs.

.. note:: The basic Newton-Raphson method as implemented in this software module returns only one of the (potentially) multiple roots of the polynomial. Which root is returned depends on the polynomial and the initial guess for :math:`x`, i.e., ``initial_value`` of the ``uz_newton_raphson_config`` struct.


Reference
=========

.. doxygenstruct:: uz_newton_raphson_config
  :members:

.. doxygenfunction:: uz_newton_raphson

Description
===========

This function uses the arrays from the UltraZohm :ref:`uz_array` library. 
This algorithm uses the Newton Raphson[[#newton]_] approach to approximate the roots, with :math:`x_0` being the initial guess.

.. math::

  r &= x_0 + h \approx x_0 - \frac{f(x_0)}{f'(x_0)}\\
  x_1 &= x_0 - \frac{f(x_0)}{f'(x_0)}\\
  x_2 &= x_1 - \frac{f(x_1)}{f'(x_1)}\\
  x_3 &= x_2 - \frac{f(x_2)}{f'(x_2)}

Consider this equation:

.. math::

  f(x) &= x^4 - 5x^2 - 20.5x + 2\\
  f'(x) &= 4x^3 - 10x - 20.5\\


This can be represented differently:

.. math::

  f(x) &= a \cdot x^4 - c \cdot x^2 + d \cdot x + e\\
  f'(x) &= a \cdot 4x^3 - c \cdot 2x + d\\

There is a dedicated array for the coefficients (a,b,c,d, etc.) and another one for the polynomial itself, scaled to 0/1.
The derivate carries only the polynomial again, but obviously with the derivate factors.
If the coefficients change during runtime, only they have to be updated. The rest can stay the same.

The corresponding arrays would look like this:

.. code-block:: c

    //float coefficients[5] = {e, d, c, b, a};
    //float derivate_poly_coefficients[4] = {1*x0, 2*x1, 3*x2, 4*x3};
    
    float coefficients[5] = {2.0f, -20.5f, -5.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[4] = {1.0f, 2.0f, 0.0f, 4.0f};

Example
=======

.. code-block:: c

    #include "../uz/uz_newton_raphson/uz_newton_raphson.h"
    int main(void) {
        float derivate_poly_coefficients[4] = {1.0f, 2.0f, 0.0f, 4.0f};
        float coefficients[5] = {2.0f, -20.5f, -5.0f, 0.0f, 1.0f};
        struct uz_newton_raphson_config config = {
            .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
            .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
            .coefficients.length = UZ_ARRAY_SIZE(coefficients),
            .coefficients.data = &coefficients[0],
            .initial_value = 5.0f,
            .iterations = 5U,
        };
        float output = uz_newton_raphson(config);
    }

Sources
=======

.. [#newton] `Newton's Method for Finding Equation Roots, A. Schlegel <https://aaronschlegel.me/newtons-method-equation-roots.html>`_

Functions
=========

..  toctree::
    :maxdepth: 1
    :glob:
  
    *