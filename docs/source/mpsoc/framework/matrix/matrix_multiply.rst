.. _matrix_multiply:

===============
matrix_multiply
===============

Matrix multiplication :math:`\boldsymbol{C}=\boldsymbol{A} \boldsymbol{B}` of the matrix :math:`\boldsymbol{A}` with dimension :math:`m \times n` and :math:`\boldsymbol{B}` with dimension :math:`n \times p` results in matrix :math:`\boldsymbol{C}` with dimension :math:`m \times p`.
For matrix multiplication, the number of columns :math:`n` in :math:`\boldsymbol{A}` must be equal to the number of rows of matrix :math:`\boldsymbol{B}`.

.. math::

    \boldsymbol{C}=\boldsymbol{A} \boldsymbol{B}

.. math::

    \begin{bmatrix}
   a_{11} & a_{12} & \cdots & a_{1n} \\
   a_{21} & a_{22} & \cdots & a_{2n} \\
   \vdots & \vdots & \ddots & \vdots \\
   a_{m1} & a_{m2} & \cdots & a_{mn}
   \end{bmatrix}
   \begin{bmatrix}
   b_{11} & b_{12} & \cdots & b_{1p} \\
   b_{21} & b_{22} & \cdots & b_{2p} \\
   \vdots & \vdots & \ddots & \vdots \\
   b_{n1} & b_{n2} & \cdots & b_{np}
   \end{bmatrix}
   =
   \begin{bmatrix}
    c_{11} & c_{12} & \cdots & c_{1p} \\
    c_{21} & c_{22} & \cdots & c_{2p} \\
    \vdots & \vdots & \ddots & \vdots \\
    c_{m1} & c_{m2} & \cdots & c_{mp}
    \end{bmatrix}

.. doxygenfunction:: uz_matrix_multiply


Example
=======

.. math::

    \begin{bmatrix}
    1 & 2\\
    3 & 4 \\
    5 & 6 
    \end{bmatrix}
    \begin{bmatrix}
    2 & 1\\
    8 & 5
    \end{bmatrix} =
    \begin{bmatrix}
    18 & 11\\
    38 & 23\\
    58 & 35
    \end{bmatrix}

.. code-block:: c

   void test_uz_matrix_matrix_multiply(void){
       float A_data[6]={1,2,3,4,5,6};
       float B_data[4]={2,1,8,5};
       float C_data[6]={5};
       uz_matrix_t* A=uz_matrix_init(A_data,UZ_MATRIX_SIZE(A_data),3, 2 );
       TEST_ASSERT_EQUAL_FLOAT(1,get_matrix_element_zero_based(A,0,0));
       TEST_ASSERT_EQUAL_FLOAT(2,get_matrix_element_zero_based(A,0,1));
       TEST_ASSERT_EQUAL_FLOAT(3,get_matrix_element_zero_based(A,1,0));
   
       uz_matrix_t* B=uz_matrix_init(B_data,UZ_MATRIX_SIZE(B_data),2, 2 );
       uz_matrix_t* C=uz_matrix_init(C_data,UZ_MATRIX_SIZE(C_data),3, 2 );
       // C=A * B
       matrix_multiply(A,B, C);
       TEST_ASSERT_EQUAL_FLOAT(18,get_matrix_element_zero_based(C,0,0) );
       TEST_ASSERT_EQUAL_FLOAT(11,get_matrix_element_zero_based(C,0,1) );
       TEST_ASSERT_EQUAL_FLOAT(38,get_matrix_element_zero_based(C,1,0) );
       TEST_ASSERT_EQUAL_FLOAT(23,get_matrix_element_zero_based(C,1,1) );
       TEST_ASSERT_EQUAL_FLOAT(58,get_matrix_element_zero_based(C,2,0) );
       TEST_ASSERT_EQUAL_FLOAT(35,get_matrix_element_zero_based(C,2,1) );
   }