.. _elementwise_product:

===================
elementwise_product
===================

.. doxygenfunction:: uz_matrix_elementwise_product

Calculates the elementwise product / Hadamard product.
Multiplies every element of :math:`\boldsymbol{A}` with the respective element of :math:`\boldsymbol{B}` if dimensions of :math:`\boldsymbol{A}`, :math:`\boldsymbol{B}` and :math:`\boldsymbol{C}` are equal.

.. math::

    \boldsymbol{C}=\boldsymbol{A} \odot \boldsymbol{B}

.. math::

    \begin{bmatrix}
    a_{11} \cdot b_{11} & a_{12} \cdot b_{12} & a_{1n} \cdot b_{1n} \\
    a_{21} \cdot b_{21} & a_{22} \cdot b_{22} & a_{2n} \cdot b_{2n} \\
    a_{m1} \cdot b_{m1} & a_{m2} \cdot b_{m2} & a_{mn} \cdot b_{mn}
    \end{bmatrix}
   =
   \begin{bmatrix}
   a_{11} & a_{12} & a_{1n} \\
   a_{21} & a_{22} & a_{2n} \\
   a_{m1} & a_{m2} & a_{mn}
   \end{bmatrix}
   \begin{bmatrix}
   b_{11} & b_{12} & b_{1n} \\
   b_{21} & b_{22} & b_{2n} \\
   b_{m1} & b_{m2} & b_{mn}
   \end{bmatrix}

Column vector Example
---------------------

.. math::

   \begin{bmatrix}
   1 \\
   2 \\
   3    \end{bmatrix}
   \odot
   \begin{bmatrix}
   1 \\
   2 \\
   3    \end{bmatrix}
   =
   \begin{bmatrix}
   1 \\
   4 \\
   9    \end{bmatrix}

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_matrix/test_uz_matrix_elementwise.c
   :lines: 15-29
   :linenos:
   :language: c


Row vector Example
------------------

.. math::

   \begin{bmatrix}
   1 & 2 & 3 & 4
   \end{bmatrix}
   \odot
   \begin{bmatrix}
   1 & 2 & 3 & 4
   \end{bmatrix}
   =
   \begin{bmatrix}
   1 & 4 & 9 & 16
   \end{bmatrix}

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_matrix/test_uz_matrix_elementwise.c
   :lines: 50-65
   :linenos:
   :language: c

Matrix Example
---------------

.. math::

   \begin{bmatrix}
   1 & 2 \\
    3 & 4
   \end{bmatrix}
   \odot
   \begin{bmatrix}
   1 & 2 \\
   3 & 4
   \end{bmatrix}
   =
   \begin{bmatrix}
   1 & 4 \\
   9 & 16
   \end{bmatrix}

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_matrix/test_uz_matrix_elementwise.c
   :lines: 31-48
   :linenos:
   :language: c