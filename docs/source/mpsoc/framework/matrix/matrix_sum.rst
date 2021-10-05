.. _matrix_sum:

=============
uz_matrix_sum
=============


Calculates :math:`\boldsymbol{C}=\boldsymbol{A} + \boldsymbol{B}` if dimensions of :math:`\boldsymbol{A}`, :math:`\boldsymbol{B}` and :math:`\boldsymbol{C}` are equal.

.. warning:: Do not call this function with A and B having the same pointer to prevent aliasing issues.

.. doxygenfunction:: uz_matrix_sum


Example
-------

.. math::

    \begin{bmatrix}
    1 & 2\\
    3 & 4
    \end{bmatrix} +
    \begin{bmatrix}
    1 & 2\\
    3 & 4
    \end{bmatrix} =
    \begin{bmatrix}
    2 & 4\\
    6 & 8
    \end{bmatrix}

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_matrix/test_uz_matrix_matrix_add.c
    :lines: 1-
    :linenos:
    :language: c