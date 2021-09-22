.. _add_to_matrix:

=============
add_to_matrix
=============

.. doxygenfunction:: uz_matrix_add

Calculates :math:`\boldsymbol{C}= \boldsymbol{C} + \boldsymbol{A}` if dimensions of :math:`\boldsymbol{A}` and :math:`\boldsymbol{C}` are equal.

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

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_matrix/test_uz_matrix_add_to_matrix.c
    :lines: 45-58
    :linenos:
    :language: c