.. _uz_complex:

====================
Complex math library
====================

The complex math library implements functions for mathematical operations on complex numbers.
The functions are implemented for complex numbers in cartesian form.
Transformation functions to and from the polar form are provided.
If only one part of the complex number is used (only real, only imaginary or only magnitude), the other part should still be set to zero!!


Reference
=========

.. doxygentypedef:: uz_complex_cartesian_t

.. doxygentypedef:: uz_complex_polar_t

.. doxygenfunction:: uz_complex_addition

.. doxygenfunction:: uz_complex_subtraction

.. doxygenfunction:: uz_complex_multiplication

.. doxygenfunction:: uz_complex_division

.. doxygenfunction:: uz_complex_cartesian_to_polar

.. doxygenfunction:: uz_complex_polar_to_cartesian