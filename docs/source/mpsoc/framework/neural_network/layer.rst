.. _layer:

=====
Layer
=====

A layer in a neural network multiplies the input of the layer with the weight matrix and adds the bias.
The result of the multiplication + bias is fed to the activation function of the layer.

- https://datascience.stackexchange.com/questions/75855/what-types-of-matrix-multiplication-are-used-in-machine-learning-when-are-they

.. note:: The results for all examples with numbers are calculated using matlab and ``single`` precision!

.. math::

    \boldsymbol{x}=\begin{bmatrix} x_1 & x_2 & x_3 \end{bmatrix}

.. math::

    \begin{bmatrix} x_1 & x_2 & x_3 \end{bmatrix}
    \begin{bmatrix}
    w_{1,1} & w_{1,2} & w_{1,3} & w_{1,4} \\
    w_{2,1} & w_{2,2} & w_{2,3} & w_{2,4} \\
    w_{3,1} & w_{3,2} & w_{3,3} & w_{3,4}
    \end{bmatrix}
    =
    \begin{bmatrix} h_1 & h_2 & h_3 & h_4 \end{bmatrix}

.. math::

    \boldsymbol{s}
    =
    \begin{bmatrix} h_1 & h_2 & h_3 & h_4 \end{bmatrix}
    +
    \begin{bmatrix} b_1 & b_2 & b_3 & b_4 \end{bmatrix}

.. math::

    \begin{bmatrix} 1 & 2 & 3 \end{bmatrix}
    \begin{bmatrix}
    0.5377 &  1.8339 & -2.2588 & 0.8622 \\
    0.3188 & -1.3077 & -0.4336 & 0.3426 \\
    3.5784 &  2.7694 & -1.3499 & 3.0349 
    \end{bmatrix}
    =
    \begin{bmatrix} 11.9105 &   7.5267 &  -7.1757 &  10.6521 \end{bmatrix}

Add bias:

.. math::

    \boldsymbol{s}
    =
    \begin{bmatrix} 11.9104 & 7.5268 & -7.1757 & 10.6522 \end{bmatrix}
    +
    \begin{bmatrix} 1 & -2 & 3 & -4 \end{bmatrix}
    \\
    =
    \begin{bmatrix} 12.9105 & 5.5267 & -4.1757 & 6.6521 \end{bmatrix}



Feed output through activation function:

.. math::

    \boldsymbol{y}=f(h)

With Relu:

.. math::

    \begin{bmatrix} 12.9105 & 5.5267 & 0.0 & 6.6521 \end{bmatrix}

Reference
=========

.. doxygenenum:: activation_function

.. doxygentypedef:: uz_nn_layer
    
.. doxygenfunction:: uz_nn_layer_init

.. doxygenfunction:: uz_nn_layer_ff

.. doxygenfunction:: uz_nn_layer_get_output_data