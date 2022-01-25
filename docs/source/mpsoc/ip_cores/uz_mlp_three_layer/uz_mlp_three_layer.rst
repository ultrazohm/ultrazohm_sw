.. _uz_mlp_three_layer:

==================
uz_mlp_three_layer
==================

IP-Core for a MLP network.
Follows the principles outlined in :ref:`uz_nn`.

Features:

- Feedforward calculation in fixed point (32bit, 14 fractional)
- Precision: 6.1e-5
- Max values: +/- 131072
- Variable number of inputs can be configured by software from 2 to 16
- Variable number of outputs can be configured by software (2,4,6,8).
- Number of hidden layer is fixed to 3!
- Number of neurons in each hidden layer is fixed to 64!
- Activation function is ReLU for all hidden layer
- Activation function is linear for output layer
- Bias and Weights can be written to the network at runtime


Configuration
=============

enable_nn

  Calculates one feedforward pass of network with the current inputs on a rising edge of this signal

use_axi_input

  Network uses the FPGA inputs for the feedforward pass if this is FALSE and the inputs from the AXI signals if this is TRUE.

axi_number_of_inputs

  Sets the number of inputs of the network.
  Can be set to any value between 2 and 16.
  Has to be consistent with the values that are stored in the IP-Cores

axi_output_number_configuration

  Sets the number of outputs of the network.
  The network can have 2,4,6, or 8 outputs.
  The value in this config register has to be set to``number_of_outputs/2-1``.

Output scheme
=============

The output is always a vector with 8 elements, independent of the actual number of outputs of the network.
Due to the parallel calculation of the result, the following output mapping is used.

For 8 outputs:

.. math::

   y=\begin{bmatrix} y_1 & y_2 & y_3 & y_4 & y_5 &  y_6 &  y_7 & y_8 \end{bmatrix} 

For 6 outputs:

.. math::

   y=\begin{bmatrix} y_1 & y_2 & y_3 & 0 & y_4 &  y_5 &  y_6 & 0 \end{bmatrix} 

For 4 outputs:

.. math::

   y=\begin{bmatrix} y_1 & y_2 & 0 & 0 & y_3 &  y_4 &  0 & 0 \end{bmatrix} 

For 2 outputs:

.. math::

   y=\begin{bmatrix} y_1 & 0 & 0 & 0 & y_2 &  0 & 0 & 0 \end{bmatrix} 



Parallel calculation
====================

The calculation of the network is split up and done in parallel to speed it up.
The split up is done on a neuron basis in each layer, i.e., with a parallelization of 4, the layer uses for parallel MAC units.
These calculate 1/4 of the output independent of each other.

Example:

.. math::

    x &=\begin{bmatrix} 1 & 2 & 3 & 4 \end{bmatrix} \\
    w &=\begin{bmatrix}  \color{red} 1 &  \color{red} 2 & 3 & 4 & \color{green}5 & \color{green}6 & 7 & 8\\ \color{red} 9 & \color{red} 10 & 11 & 12 & \color{green}13 &\color{green} 14 & 15 & 16  \\  \color{red}17 &  \color{red}18 & 19 & 20 & \color{green}21 & \color{green}22 & 23 & 24 \\  \color{red}25 &  \color{red}26 & 27 & 28 & \color{green} 29 & \color{green}30 & 31 & 32 \end{bmatrix} \\
    b &=\begin{bmatrix} 1 & 2 & 3 & 4 \end{bmatrix}

The multiplication :math:`xw` is split up by splitting :math:`w` into (e.g.) 4 parts.

.. math::

    w_1 &= \begin{bmatrix}  \color{red}1 &  \color{red}2 \\  \color{red}9 &  \color{red}10 \\  \color{red}17 &  \color{red}18 \\  \color{red}25 &  \color{red}26 \end{bmatrix} \\
    w_2 &= \begin{bmatrix} 3 & 4 \\ 11 & 12 \\ 19 & 20 \\ 27 & 28 \end{bmatrix} \\
    w_3 &= \begin{bmatrix} \color{green} 5 & \color{green}6 \\ \color{green}13 &\color{green} 14 \\ \color{green}21 & \color{green}22 \\ \color{green}29 &\color{green} 30 \end{bmatrix} \\
    w_4 &= \begin{bmatrix} 7 & 8 \\ 15 & 16 \\ 23 & 24 \\ 31 & 32 \end{bmatrix} \\

The results are calculated by:

.. math::

    y_1 &= x w_1=\begin{bmatrix} 170  & 180 \end{bmatrix}\\ 
    y_2 &= x w_2=\begin{bmatrix} 190  & 200 \end{bmatrix}\\
    y_3 &= x w_3=\begin{bmatrix} 210  & 220 \end{bmatrix}\\
    y_4 &= x w_4=\begin{bmatrix} 230  & 240 \end{bmatrix} \\
    y &= \begin{bmatrix} 170 & 180 & 190 & 200 & 210 & 220 & 230 & 240 \end{bmatrix}

Write parameters to network
===========================



Usage
=====


Interfaces
==========

.. csv-table:: Interfaces of three layer MLP IP-Core
   :file: ./uz_mlp_interfaces.csv
   :widths: 50 50 50 50 200
   :header-rows: 1

