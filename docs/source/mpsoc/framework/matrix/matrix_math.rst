.. _matrix_math:

===========
Matrix math
===========

..	toctree::
    :maxdepth: 2
    :hidden:
    :glob:

    *

The matrix math functions use the matrix definition:

.. math::

    \begin{array}{cc}
    & \text{Columns $n$ } \\
    \text{Rows $m$ } &
    \begin{bmatrix}
        a_{11} & a_{12} & \cdots & a_{1n} \\
        a_{21} & a_{22} & \cdots & a_{2n} \\
        \vdots & \vdots & \ddots & \vdots \\
        a_{m1} & a_{m2} & \cdots & a_{mn}
    \end{bmatrix}
    \end{array}
    
.. warning:: Keep in mind that in C everything is 0-indexed


uz_matrix_init
==============

.. doxygenfunction:: uz_matrix_init

Each matrix has to be initialized with ``uz_matrix_init``:

.. literalinclude:: ../../../../../vitis/software/Baremetal/test/uz/uz_matrix/test_uz_matrix.c
   :lines: 1-
   :linenos:
   :language: c

.. doxygentypedef:: uz_matrix_t

Dimensions
**********

A pointer to the actual data has to be supplied as the first argument to ``uz_matrix_init``.
The vector has to be of length :math:`m \times n`.
The dimension :math:`n` (``columns``) can be one to generate a column vector :math:`m \times 1`.

.. math::

    x= \begin{bmatrix}
    x_{11} \\
    x_{21} \\
    \vdots \\
    x_{m1}
    \end{bmatrix}

The dimension :math:`n` can be one to generate a row vector :math:`1 \times n`.

.. math::

    x= \begin{bmatrix}
    x_{11} & x_{12} & \cdots & x_{1n}
    \end{bmatrix}

Internally, the matrix is always stored as an array in the following way (zero indexing internally):

.. math::

    \begin{bmatrix}
    \color{red} x_{11} & \color{red} x_{12} & \color{red} x_{13}\\
    \color{blue} x_{21} & \color{blue} x_{22} &  \color{blue} x_{23}\\
    \color{green} x_{31} & \color{green} x_{32} & \color{green} x_{33}
    \end{bmatrix} = 
    \begin{bmatrix}
    \color{red} x_{11} & \color{red} x_{12} & \color{red} x_{13} &
    \color{blue} x_{21} & \color{blue} x_{22} &  \color{blue} x_{23} &
    \color{green} x_{31} & \color{green} x_{32} & \color{green} x_{33}
    \end{bmatrix} \\ 
    =
    \begin{bmatrix}
    x_{0} & x_{1} & x_{2} &
    x_{3} & x_{4} & x_{5} &
    x_{6} & x_{7} & x_{8}
    \end{bmatrix}

Set & Get functions
*******************

.. doxygenfunction:: uz_matrix_get_number_of_rows

.. doxygenfunction:: uz_matrix_get_number_of_columns
