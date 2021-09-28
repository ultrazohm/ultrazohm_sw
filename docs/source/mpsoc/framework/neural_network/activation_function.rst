.. _activation_function:

===================
Activation function
===================

The following activation functions are implemented.

Linear
======

.. tikz::

    \draw [->] (-3,0) -- (3,0) node [above left]  {$x$};
    \draw [->] (0,-3) -- (0,3) node [below right] {$y$};
    \foreach \n in {-2,...,-1,1,2}{%
    \draw (\n,-3pt) -- (\n,3pt)   node [above] {$\n$};
    \draw (-3pt,\n) -- (3pt,\n)   node [right] {$\n$};
    }
    \draw[-,red,thick] (-3,-3) -- (0,0) -- (3,3);

Activation function:

.. math::

    f(x)=x

Derivative:

.. math::

    f'(x)=1

.. doxygenfunction:: uz_nn_activation_function_linear

.. doxygenfunction:: uz_nn_activation_function_linear_derivative

.. _activation_functon_relu:

ReLU
====

Rectified linear unit

.. tikz::

    \draw [->] (-3,0) -- (3,0) node [above left]  {$x$};
    \draw [->] (0,-3) -- (0,3) node [below right] {$y$};
    \foreach \n in {-2,...,-1,1,2}{%
    \draw (\n,-3pt) -- (\n,3pt)   node [above] {$\n$};
    \draw (-3pt,\n) -- (3pt,\n)   node [right] {$\n$};
    }
    \draw[-,red,thick] (-3,0) -- (0,0) -- (3,3);


Activation function:

.. math::

    f(x) =
    \begin{cases}
      0 & \text{if $x \leq 0$}\\
      x & \text{if $x > 0$}\\
    \end{cases} 

Derivative:

.. math::

    f'(x) =
    \begin{cases}
      0 & \text{if $x \leq 0$}\\
      1 & \text{if $x > 0$}\\
    \end{cases}

.. doxygenfunction:: uz_nn_activation_function_relu

.. doxygenfunction:: uz_nn_activation_function_relu_derivative

Leaky ReLU
==========

Leaky Rectified linear unit

.. tikz::

    \draw [->] (-3,0) -- (3,0) node [above left]  {$x$};
    \draw [->] (0,-3) -- (0,3) node [below right] {$y$};
    \foreach \n in {-2,...,-1,1,2}{%
    \draw (\n,-3pt) -- (\n,3pt)   node [above] {$\n$};
    \draw (-3pt,\n) -- (3pt,\n)   node [right] {$\n$};
    }
    \draw[-,red,thick] (-3,-0.1) -- (0,0) node[midway, below] {$\alpha$} -- (3,3);

Activation function:

.. math::

    f(x) =
    \begin{cases}
    \alpha x & \text{if $x \leq 0$}\\
     x & \text{if $x > 0$}\\
    \end{cases} 

Derivative:

.. math::

    f'(x) =
    \begin{cases}
      \alpha & \text{if $x \leq 0$}\\
      1 & \text{if $x > 0$}\\
    \end{cases}

.. doxygenfunction:: uz_nn_activation_function_leaky_relu

.. doxygenfunction:: uz_nn_activation_function_leaky_relu_derivative