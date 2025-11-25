.. _neural_network:

==============
Neural network
==============

The following describes the basic theory and definitions for `multilayer perceptron networks <https://en.wikipedia.org/wiki/Multilayer_perceptron>`_, a class of feedforward neutral networks.
The software module :ref:`uz_nn` is based on the definitions on this page.

Network and dimension definition
================================

A neural network consists of an input layer, one or multiple hidden layer, and an output layer.
Each layer has one or multiple neurons (also called perceptorn or nodes). 
A network with one input layer, one hidden layer and one output layer has :math:`l=2` layers (hidden layer +1, input layer is not counted).
A network can have a different number of inputs and outputs, e.g., two inputs and one output.
Each hidden layer has a defined number of neurons in the layer.

The weight connecting the first input :math:`x_1` to the first neuron of the first hidden layer is called :math:`w^{(1)}_{11}`.
From the first input to the second neuron :math:`w^{(1)}_{12}` and from the second input to the first neuron of the first hidden layer :math:`w^{(1)}_{21}`.
Generalized:

.. math::

   w^{(l)}_{i,j}

The index of the layer :math:`l` is counted by a superscript (:math:`w^{(l)}`).
Therefore, :math:`w^{(1)}` is the complete matrix with all weights of the layer :math:`l=1`.
The row of the weight matrix is defined by the number of connections which end in the layer.
That is, the number of rows (:math:`m`) is equal to the number of inputs in first hidden layer (:math:`w^{(1)}`) and for all other hidden layer (:math:`l>1`) the number of rows (:math:`m`) is equal to the number of neurons of the previous hidden layer (:math:`l-1`).
Each neuron in a hidden layer :math:`l` has one connection to every neuron of the following layer :math:`l+1` (*fully connected*).

The weight matrix has the following generic dimensions:

.. figure:: img/weights.svg
   :align: center

   Dimensions of weight matrix

For each layer :math:`l` there is a weight and a bias matrix.
The matrix is numbered by the layer :math:`l` of which the weight belongs to (= the layer to which the weight connects to / where the arrow ends).
The first subscript :math:`i` notes the number (counted from up to down in the layer) of the starting neuron (or the input).
The second subscript :math:`j` notes the number of the neuron where the connection ends.

.. _simple_nn_twolayer:

.. figure:: img/simple_nn_twolayer.svg
   :align: center

   Simple neural network with naming scheme of weights

The weights and bias of the network in :numref:`simple_nn_twolayer` are represented by the following equations.

.. math::

   w^{(1)}_{ij}=\left[ \begin{array}{rr} w_{11} & w_{12} \\ w_{21} & w_{22} \\ \end{array}\right]

.. math::

   w^{(2)}_{ij}=\left[ \begin{array}{rr} w_{11} \\ w_{21} \\ \end{array}\right]

The bias are not shown but represented as following:

.. math::
   
   b^{(1)}_{j}=\left[ \begin{array}{rr} b_{1} & b_{2} \\ \end{array}\right]

.. math::
   
   b^{(2)}_{j}=\left[ \begin{array}{rr} b_{1}\\ \end{array}\right]

.. note:: The notation across the literature and different other software implementations (e.g., Tensorflow, Pytorch, Matlab) is not consistent. The definition of inputs, weights, and bias can be transposed and the calculation of :math:`s` rearranged (:math:`w^T y` instead of :math:`yw`) without changing the function of the network. Having the inputs as column or row vector is used by differend software modules, see this `article <https://medium.com/from-the-scratch/deep-learning-deep-guide-for-all-your-matrix-dimensions-and-calculations-415012de1568>`_ for example. 

Neurons
=======

.. _nn_neuron_definition:

.. figure:: img/neuron.svg
   :align: center

   First neuron :math:`j=1` of layer :math:`l` with inputs :math:`y^l`, weights :math:`w^l_{i,j}`, bias :math:`b^l_j` and output :math:`y^l_j` (definition according to [#intelligente_verfahren]_)

Neurons are the basic building block of neural networks.
A neuron sums over its weighted input values as well as the bias and calculates the output based on an arbitrary activation function :math:`\mathcal{F}(\cdot)`.
The notation of this software module denotes the number of the layer with the superscript :math:`l` for all parameters.
The weight connecting the output :math:`y^{l-1}_i` of the :math:`i`-th neuron of the previous layer :math:`l-1` with the input of the :math:`j`-th neuron of the layer :math:`l` is denoted by :math:`w^l_{i,j}`.
The following equation calculates the dot product of the weight vector :math:`\boldsymbol{w}^l_j` and the input vector :math:`\boldsymbol{y}^l_j` of the :math:`j`th neuron of layer :math:`l` with the length :math:`n` and adds the bias :math:`b^l_j` to yield the sum :math:`s^l_j` of the neuron inputs.

.. math::

   s^l_j =\sum^n_{i=1} y^{l-1}_{ij} w^l_{ij} + b^l_j


The output value :math:`y^l_j` of the neuron is calculated by the activation function for all hidden layers.

.. math::

   y^l_j = \mathcal{F}(s^l_j)


Network example
===============

MLP are implemented with the following definition and representation of the neural network.
The neural network has a number of layers which consists of the input layer, the output layer, and the number of hidden layer :math:`l`).
Each layer has a number of neurons.

.. _nn_structure:

.. figure:: img/nn_structure.svg
   :align: center

   Structure of a neural network

The MLP shown in :numref:`nn_structure` has two inputs, two hidden layer with three neurons each, and one output.
The input is defined as:

.. math::

    x &=y^{(0)}=\left[ \begin{array}{rr} x_{1} & x_{2} \\ \end{array}\right] \\
    x &=y^{(0)}=\left[ \begin{array}{rr} 1 & 2 \\ \end{array}\right] 

The output is defined as:

.. math::

    y^{(3)}=\left[ \begin{array}{rr} y_{1} \\ \end{array}\right]

The weights and bias matrices for each layer with example values are given n the following.
For the first hidden layer:

.. math::

   w^{(1)} &=\left[ \begin{array}{rr} w_{11} & w_{12} &  w_{13} \\ w_{21} & w_{22} & w_{23} \\ \end{array}\right] \\
   w^{(1)} &=\left[ \begin{array}{rr} 1 & 2 &  3 \\ 4 & 5 & 6 \\ \end{array}\right] \\
   b^{(1)} &=\left[ \begin{array}{rr} b_1 & b_2 &  b_3 \\ \end{array}\right] \\
   b^{(1)} &=\left[ \begin{array}{rr} 1 & 2 & 3 \\ \end{array}\right]

For the second hidden layer:

.. math::

   w^{(2)} &=\left[ \begin{array}{rr} w_{11} & w_{12} &  w_{13} \\ w_{21} & w_{22} & w_{23} \\ w_{31} & w_{32} & w_{33} \end{array}\right] \\
   w^{(2)} &=\left[ \begin{array}{rr} -7 & -8 &  -9 \\ -10 & -11 & -12 \\ 13 & 14 & -15 \\ \end{array}\right] \\
   b^{(2)} &=\left[ \begin{array}{rr} b_1 & b_2 &  b_3 \\ \end{array}\right] \\
   b^{(2)} &=\left[ \begin{array}{rr} 4 & 5 & 6 \\ \end{array}\right]

For the output layer:

.. math::

   w^{(3)} &=\left[ \begin{array}{rr} w_{11} \\ w_{21} \\ w_{31} \end{array}\right] \\
   w^{(3)} &=\left[ \begin{array}{rr} 16 \\ 17 \\ -18 \end{array}\right] \\
   b^{(3)} &=\left[ \begin{array}{rr} b_1 \\ \end{array}\right] \\
   b^{(3)} &=\left[ \begin{array}{rr} 7 \\ \end{array}\right]

The activation function of the hidden layer is set to ReLU, the output activation function to linear.
The following section calculates all steps and intermediate results in the network.

First layer
***********

.. math::

   \boldsymbol{x} \boldsymbol{w^{(1)}} + \boldsymbol{b^{(1)}} &= \boldsymbol{s^{(1)}} \\  
   \left[ \begin{array}{rr} 1 & 2 \\ \end{array}\right]
   \left[ \begin{array}{rr} 1 & 2 &  3 \\ 4 & 5 & 6 \\ \end{array}\right] 
   +
   \left[ \begin{array}{rr} 1 & 2 & 3 \\ \end{array}\right]
   &= 
   \left[ \begin{array}{rr} 9 & 12 & 15 \\ \end{array}\right]

Activation function:

.. math::

      y^{1} &= ReLU(\boldsymbol{s^{(1)}}) \\
      y^{1} &= ReLU(   \left[ \begin{array}{rr} 10 & 14 & 18 \\ \end{array}\right])\\
      &=  \left[ \begin{array}{rr} 10 & 14 & 18 \\ \end{array}\right]

Second layer
************

The input of the second hidden layer is the output of the first hidden layer :math:`y^{(1)}`:

.. math::

   \boldsymbol{y^{(1)}} \boldsymbol{w^{(2)}} + \boldsymbol{b^{(2)}} &= \boldsymbol{s^{(2)}} \\  
   \left[ \begin{array}{rr} 10 & 14 & 18 \\ \end{array}\right]
   \left[ \begin{array}{rr} -7 & -8 & -9 \\ -10 & -11 & -12 \\ 13 & 14 & -15 \\ \end{array}\right] 
   +
   \left[ \begin{array}{rr} 4 & 5 & 6 \\ \end{array}\right]
   &= 
   \left[ \begin{array}{rr} 28 & 23 & -522 \\ \end{array}\right]

Activation function:

.. math::

      y^{2} &= ReLU(\boldsymbol{s^{(2)}}) \\
      y^{2} &= ReLU(   \left[ \begin{array}{rr} 28 & 23 & -522 \\ \end{array}\right])\\
      &=  \left[ \begin{array}{rr} 28 & 23 & 0 \\ \end{array}\right]

Output layer
************

The input of the output layer is the output of the second hidden layer :math:`y^{(2)}`:

.. math::

   \boldsymbol{y^{(2)}} \boldsymbol{w^{(3)}} + \boldsymbol{b^{(3)}} &= \boldsymbol{s^{(3)}} \\  
   \left[ \begin{array}{rr} 28 & 23 & 0 \\ \end{array}\right]
   \left[ \begin{array}{rr} 16 \\ 17 \\ -18 \end{array}\right] 
   +
   \left[ \begin{array}{rr} 7 \\ \end{array}\right]
   &= 
   \left[ \begin{array}{rr} 846 \\ \end{array}\right]

Activation function:

.. math::

      y^{3} &= linear(\boldsymbol{s^{(3)}}) \\
      y^{3} &= linear(   \left[ \begin{array}{rr} 846 \\ \end{array}\right])\\
      &=  \left[ \begin{array}{rr} 846 \\ \end{array}\right]

Sources
=======

.. [#intelligente_verfahren] Schröder, Dierk, "Intelligente Verfahren", Springer, 2010.
.. [#realTimeInference] T. Schindler and A. Dietz, "Real-Time Inference of Neural Networks on FPGAs for Motor Control Applications," 2020 10th International Electric Drives Production Conference (EDPC), 2020, pp. 1-6, doi: 10.1109/EDPC51184.2020.9388185.

Software implementation
=======================

..	toctree::
    :maxdepth: 2
    :hidden:
    :glob:

    uz_nn
    uz_nn_layer
    activation_function
    uz_nn_ip_core