.. _uz_newton_raphson:

============================
Newton Raphson approximation
============================

The Newton Raphson approximation is an approach for finding the roots of nonlinear equations. 
This is a relative simple, but fast approach, which results in a relative slim computational effort. 
Solving a 20th order polynomial with 20 iterations takes roughly 20µs.
This approach needs the original function :math:`f(x)` as well as the derivate :math:`f'(x)`.
To automatically calculate the derivate, refer to :ref:`uz_newton_raphson_derivate`.
Furthermore it approximates the true roots of the polynomial. 
If there are not enough iterations for the approach to converge to the true roots, the results can be inaccurate.
A balance between computational effort (i.e. number of iterations) and accuracy of the results have to be made by the user.
Your milage may wary. 

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

Usage cases
-----------

Depending on the user selection of ``use_separate_coefficients``, there are two possible scenarios. 
The result will be the same. Only the setup will differ. Consider this equation:

.. math::

  f(x) &= x^4 - 5x^2 - 20.5x + 2\\
  f'(x) &= 4x^3 - 10x - 20.5\\


This can be represented in a different way:

.. math::

  f(x) &= a \cdot x^4 - c \cdot x^2 + d \cdot x + e\\
  f'(x) &= a \cdot 4x^3 - c \cdot 2x + d\\


Case ``use_separate_coefficients = true``
*****************************************

In this case, the coefficients of the polynomial are separated. 
There is a dedicated array for the coefficients (a,b,c,d etc.) and another one for the polynomial itself, nominated to 0/1.
The derivate carries only the polynomial again, but obviously with the derivate factors.
This can be of advantage, if the polynomial and the derivate stay the same, but the coefficients do change.
In this case, the derivate can stay the same and doesn't need to be recalculated.

The corresponding arrays would look like this:

.. code-block:: c

    float poly_coefficients[5] = {1.0f, 1.0f, 1.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[4] = {1.0f, 2.0f, 0.0f, 4.0f};
    float coefficients[5] = {2.0f, -20.5f, -5.0f, 0.0f, 1.0f};

Case ``use_separate_coefficients = false``
******************************************

In this case the coefficients of the polynomial are merged together. This means however, that if a coefficient (a,b,c...) changes, the derivate has to be recalculated.

Using the equation from above, the corresponding arrays would look like this:

.. code-block:: c

    float poly_coefficients[5] = {2.0f, -20.5f, -5.0f, 0.0f, 1.0f};
    float derivate_poly_coefficients[4] = {-20.5f, -10.0f, 0.0f, 4.0f};

Example
=======

.. code-block:: c

    #include "../uz/uz_newton_raphson/uz_newton_raphson.h"
    int main(void) {
        float poly_coefficients[5] = {1.0f, 1.0f, 1.0f, 0.0f, 1.0f};
        float derivate_poly_coefficients[4] = {1.0f, 2.0f, 0.0f, 4.0f};
        float coefficients[5] = {2.0f, -20.5f, -5.0f, 0.0f, 1.0f};
        struct uz_newton_raphson_config config = {
            .poly_coefficients.length = UZ_ARRAY_SIZE(poly_coefficients),
            .poly_coefficients.data = &poly_coefficients[0],
            .derivate_poly_coefficients.length = UZ_ARRAY_SIZE(derivate_poly_coefficients),
            .derivate_poly_coefficients.data = &derivate_poly_coefficients[0],
            .coefficients.length = UZ_ARRAY_SIZE(coefficients),
            .coefficients.data = &coefficients[0],
            .use_separate_coefficients = true,
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