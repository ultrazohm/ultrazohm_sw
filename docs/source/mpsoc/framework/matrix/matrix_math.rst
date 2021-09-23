.. _matrix_math:

===========
Matrix math
===========

..	toctree::
    :maxdepth: 2
    :hidden:
    :glob:

    *

The matrix math software module provides an easy way to use matrixes.
It uses an opaque data type ``uz_matrix_t`` that boxes important information about the matrix (e.g., number of rows and colums) together with the data.
The module provides common functions, e.g., matrix multiplication, which are called with matrixes of the data type ``uz_matrix_t``, allowing error checking regarding dimensions.
The module does not hold the data of the matrix internally but uses an pointer to the data instead.
Therefore, the variable holding the data has to be initialized outside of the module.
The number of matrix instances has to be configured in :ref:`global_configuration`.

.. warning:: Take the `storage duration of variables <https://iso-9899.info/wiki/Storage_Duration>`_ into account that are pointed to in the the init function! Most of the time, use ``static`` storage duration.

.. note:: The matrix software module has similarities to the :ref:`uz_array` module but features math functions instead of a box for arrays including their length for different data types.

Matrix definition
=================

The following matrix definition with the number of columns :math:`n` and number of rows :math:`m` is used:

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
    
.. note:: Keep in mind that in C everything is 0-indexed while the matrix definitions still use 1-based indexing to be consistent with common math convetions! Thus, :math:`a_{11}` is the element with index :math:`[0,0]` in c-code!

Dimensions
==========

A pointer to the actual data array has to be supplied as the first argument to ``uz_matrix_init``.
The array has to be of length :math:`m \times n`.
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

The provided array is always an vector with :math:`m \times n` elements.
The array is split up according to the provided dimensions.
It is treated as an matrix in the following way (zero indexing internally):

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

.. note:: Keep this in mind when initializing the data array or initialize all elements of the array to zero and use the set functions.


Example
=======

Each matrix has to be initialized with ``uz_matrix_init``.
To initialize the following :math:`3 \times 3` matrix:

.. math::

    \begin{bmatrix}
    \color{red} 1 & \color{red} 2 & \color{red} 3\\
    \color{blue} 4 & \color{blue} 5 &  \color{blue} 6\\
    \color{green} 7 & \color{green} 8 & \color{green} 9
    \end{bmatrix} = 
    \begin{bmatrix}
    \color{red} 1 & \color{red} 2 & \color{red} 3 &
    \color{blue} 4 & \color{blue} 5 &  \color{blue} 6 &
    \color{green} 7 & \color{green} 8 & \color{green} 9
    \end{bmatrix} \\ 

.. code-block:: c
    :caption: Initialize a :math:`3 \times 3` matrix:

    // declare data array static outside of a function to ensure static storage duration and file scope. 
    static float mat[9]={1,2,3,4,5,6,7,8,9};

    void uz_matrix_init_3_times_3_matrix(void){
        int rows=3; // Row and columns can be automatic storage duration since they are not required after initialization (stored in the module)
        int columns=3;
        uz_matrix_t* my_matrix=uz_matrix_init(mat,UZ_MATRIX_SIZE(mat),rows,columns);
    }

Reference
=========

.. doxygentypedef:: uz_matrix_t

.. doxygenfunction:: uz_matrix_init

.. doxygenfunction:: uz_matrix_get_number_of_rows

.. doxygenfunction:: uz_matrix_get_number_of_columns

.. doxygenfunction:: uz_matrix_get_element_zero_based


Performance estimation
======================

The following performance is measured when the functions are called in the, expect for the test code and ``uz_SystemTime_ISR_Tic()`` functions, empty ISR of the R5.

.. code-block:: c
    :caption: Test code for performance estimation

    void ISR_Control(void *data)
    {
    	uz_SystemTime_ISR_Tic();
    	for(size_t i=0U;i<10;i++){
    		function_under_test(A,B,C ); //
    	}
    	uz_SystemTime_ISR_Toc();
    }
 
Testing is conducted with compiler optimization set to -O2.

- Empty ISR: 2.7 us
- Add a 3x3 matrix, code executed 10 times: 5.5 us
- elementwise_product of two 10x10 matrix, code executed 10 times: 18 us
- matrix_multiply 10x10 matrix, code executed 1 time: 23 us
- matrix_multiply 3x3 matrix, code executed 10 times: 14 us
- matrix_multiply 10x10 matrix with double data type (not implemented in the software module!), code executed 1 time: 52.8 us

Rough estimation:

- Adding a 3x3 matrix takes 0.3 us
- Multiplication of a 3x3 matrix takes 1us, of a 10x10 matrix 12 us.
- Multiplication of a 10x10 matrix takes 12 us.