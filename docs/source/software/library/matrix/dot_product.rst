.. _dot_product:

===========
dot_product
===========

Calculates the dot product of two vectors and returns the result (scalar).
The dot product is the sum over the product of the elements.

.. doxygenfunction:: uz_matrix_dot_product


Vector Example
--------------

.. math::

   \begin{bmatrix}
   1 & 2 &  3   
   \end{bmatrix}
   \cdot
   \begin{bmatrix}
   1 & 2 & 3 \end{bmatrix}
   &=
   (1 \cdot 1) + (2 \cdot 2) + (3 \cdot 3) \\
   &=
   14

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_matrix/test_uz_matrix_dot_product.c
   :lines: 15-24
   :linenos:
   :language: c
