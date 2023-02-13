.. _uz_complex:

=======
Complex
=======

Several functions for complex mathematical operations are implemented here.
The functions are implemented for complex numbers in cartesian form.
Transformation function from and to the exponential form are implemented as well.
If only one part of the complex number is used (only real, only imaginary or only magnitude), the other part should still be set to zero!!


Reference
=========

.. doxygenstruct:: uz_complex_cartesian_t
  :members:

.. doxygenstruct:: uz_complex_exponential_t
  :members:

.. doxygenfunction:: uz_complex_addition
  :members:

.. doxygenfunction:: uz_complex_multiplication
  :members:

.. doxygenfunction:: uz_complex_division
  :members:

.. doxygenfunction:: uz_complex_cartesian_to_exponential
  :members:

.. doxygenfunction:: uz_complex_exponential_to_cartesian
  :members:
