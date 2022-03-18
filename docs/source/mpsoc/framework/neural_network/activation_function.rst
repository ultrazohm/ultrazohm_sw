.. _nn_activation_function:

===================
Activation function
===================

The following activation functions are implemented.

.. _activation_function_linear:

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

.. _activation_function_relu:

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

Sigmoid logistic based on e-function
====================================

.. tikz::
    
    \begin{axis}[
        xmin=-5.5, xmax=5.5,
        ymin=-0.5, ymax=1.0,
        axis lines=center,
        axis on top=true,
        domain=-5.5:5.5,
        ylabel=$y$,
        xlabel=$x$,
        ]
        \addplot [mark=none,draw=red,thick] {1/(1+e^-x)};
    \end{axis}

Calculates the logistic function (which is a special case of the sigmoid function).
Calculation is based on the e-function.

Activation function ([#intelligente_verfahren]_ page 76.):

.. math::

    f(x)=\frac{1}{1+e^{-x}}

Derivative ([#intelligente_verfahren]_ page 76.):

.. math::

    f'(x)=f(x)(1-f(x))

.. doxygenfunction:: uz_nn_activation_function_sigmoid_logistic

.. doxygenfunction:: uz_nn_activation_function_sigmoid_logistic_derivative

Sigmoid logistic based on tanh
==============================

.. tikz::
    
    \begin{axis}[
        xmin=-5.5, xmax=5.5,
        ymin=-0.5, ymax=1.0,
        axis lines=center,
        axis on top=true,
        domain=-5.5:5.5,
        ylabel=$y$,
        xlabel=$x$,
        ]
        \addplot [mark=none,draw=red,thick] {0.5+0.5*tanh(0.5*x)};
    \end{axis}

Calculates the logistic function (which is a special case of the sigmoid function).
Calculation is based on the tanh-function.

.. note:: This function is slower than the version based on the e-function!

Activation function ([#intelligente_verfahren]_ page 76.):

.. math::

    f(x)=0.5+0.5 \tanh(\frac{x}{2})

Derivative([#intelligente_verfahren]_ page 76.):

.. math::

    f'(x)=f(x)(1-f(x))

.. doxygenfunction:: uz_nn_activation_function_sigmoid2_logistic

.. doxygenfunction:: uz_nn_activation_function_sigmoid2_logistic_derivative

tanh
====

.. tikz::
    
    \begin{axis}[
        xmin=-2.5, xmax=2.5,
        ymin=-1.5, ymax=1.5,
        axis lines=center,
        axis on top=true,
        domain=-2.5:2.5,
        ylabel=$y$,
        xlabel=$x$,
        ]
        \addplot [mark=none,draw=red,thick] {tanh(\x)};
    \end{axis}

Calculates tanh activation function.

Activation ([#intelligente_verfahren]_ page 76.):

.. math::

    f(x)=tanh(x)

Derivative ([#intelligente_verfahren]_ page 76.):

.. math::

    f'(x)=1-f(x)^2

.. doxygenfunction:: uz_nn_activation_function_tanh

.. doxygenfunction:: uz_nn_activation_function_tanh_derivative

Sources
=======

.. [#intelligente_verfahren] Schröder, Dierk, "Intelligente Verfahren", Springer, 2010.