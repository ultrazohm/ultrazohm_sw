.. _uz_nn_layer:

===========
uz_nn_layer
===========

The uz_nn_layer is used by the :ref:`uz_nn` and is based on :ref:`matrix_math` as well as :ref:`nn_activation_function`.
A layer in a neural network consists of a configurable number of neurons and an activation function.
A layer multiplies the input :math:`\boldsymbol{x}` of the layer with the weight matrix :math:`\boldsymbol{w}` of the layer and adds the bias :math:`\boldsymbol{b}` to calculate :math:`\boldsymbol{s}`.
The output of the layer :math:`\boldsymbol{y}` is the result of feeding the sum :math:`\boldsymbol{s}` into the activation function of the layer.

- The input :math:`\boldsymbol{x}` is a vector with dimension :math:`1 \times n` with the number of inputs :math:`n`.
- The output :math:`\boldsymbol{y}` is a vector with dimension :math:`1 \times p` with the number of neurons :math:`p`.
- The bias :math:`\boldsymbol{b}` is of dimension :math:`1 \times p` with the number of neurons :math:`p`.
- The weights :math:`\boldsymbol{w}` is of dimension :math:`n \times p` with the number of inputs :math:`n` and number of neurons :math:`p`.
- All neurons in one layer have the same activation function

Example
=======

The following example is calculated using Matlab and ``single`` precision.
It is used in the unit tests of the module.
The example layer has three inputs, four neurons and :ref:`activation_function_relu` activation function.
Four neurons result in four output values of the layer.

Input :math:`\boldsymbol{x}` with three input values:

.. math::

    \boldsymbol{x} &=\begin{bmatrix} x_1 & x_2 & x_3 \end{bmatrix} \\
    \boldsymbol{x} &=\begin{bmatrix} 1 & 2 & 3 \end{bmatrix}

Input values are multiplied with the weight matrix :math:`\boldsymbol{b} \boldsymbol{w}`:

.. math::

    \begin{bmatrix} x_1 & x_2 & x_3 \end{bmatrix}
    \begin{bmatrix}
    w_{1,1} & w_{1,2} & w_{1,3} & w_{1,4} \\
    w_{2,1} & w_{2,2} & w_{2,3} & w_{2,4} \\
    w_{3,1} & w_{3,2} & w_{3,3} & w_{3,4}
    \end{bmatrix}
    =
    \begin{bmatrix} h_1 & h_2 & h_3 & h_4 \end{bmatrix} \\

.. math::

    \begin{bmatrix} 1 & 2 & 3 \end{bmatrix}
    \begin{bmatrix}
    0.5377 &  1.8339 & -2.2588 & 0.8622 \\
    0.3188 & -1.3077 & -0.4336 & 0.3426 \\
    3.5784 &  2.7694 & -1.3499 & 3.0349 
    \end{bmatrix}
    =
    \begin{bmatrix} 11.9105 &   7.5267 &  -7.1757 &  10.6521 \end{bmatrix}

Add bias to sum:

.. math::

    \boldsymbol{s}
    =
    \begin{bmatrix} h_1 & h_2 & h_3 & h_4 \end{bmatrix}
    +
    \begin{bmatrix} b_1 & b_2 & b_3 & b_4 \end{bmatrix} \\

.. math::

    \boldsymbol{s}
    &=
    \begin{bmatrix} 11.9104 & 7.5268 & -7.1757 & 10.6522 \end{bmatrix}
    +
    \begin{bmatrix} 1 & -2 & 3 & -4 \end{bmatrix}
    \\
    &=
    \begin{bmatrix} 12.9105 & 5.5267 & -4.1757 & 6.6521 \end{bmatrix}



Feed output through activation function:

.. math::

    \boldsymbol{y}=\mathcal{F}( \boldsymbol{h})

With :ref:`activation_function_relu` activation function:

.. math::

    \boldsymbol{y}=\begin{bmatrix} 12.9105 & 5.5267 & 0.0 & 6.6521 \end{bmatrix}

Software and Example
====================

One ``uz_nn_layer_t`` instance uses three ``uz_matrix_t`` (:ref:`matrix_math`) instances!
Take this into account in the :ref:`global_configuration`.
The usage of a layer requires the user to pass pointer to arrays for the weights, bias, and output of the layer to the init function.
The init function initializes the required matrices and passes the pointer to the arrays to the initialization function of :ref:`matrix_math` (``uz_matrix_init``).

The following shows an example initialization and feedforward calculation of one layer.

- ``length_of_weights``, ``length_of_bias``, and ``length_of_output`` have to be calculated by ``UZ_MATRIX_SIZE`` makro
- three pointer to three arrays have to be provided in the config struct
- ``number_of_neurons`` and ``number_of_inputs`` are freely configurable but have to be consistent with the dimensions of the provided arrays
- ``activation_function`` determines the activation function of the layer
- Note that ``uz_nn_layer`` operates directly on the data that the arrays hold. Therefore, never access or change the data in the array directly (as is the case with :ref:`matrix_math`)!

.. code-block:: c
    :caption: Initialization and feedforward calculation of one layer

    #define NUMBER_OF_INPUTS 3
    #define NUMBER_OF_NEURONS_IN_LAYER 4

    static float x[NUMBER_OF_INPUTS] = {1, 2, 3};
    static float w[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_LAYER] = {0.5377, 1.8339, -2.2588, 0.8622,
                                                                     0.3188, -1.3077, -0.4336, 0.3426,
                                                                     3.5784, 2.7694, -1.3499, 3.0349};
    static float b[NUMBER_OF_NEURONS_IN_LAYER] = {1, -2, 3, -4};
    static float out[NUMBER_OF_NEURONS_IN_LAYER] = {0};

    void test_uz_nn_layer_ff_relu(void)
    {
        uz_matrix_t *input = uz_matrix_init(x, UZ_MATRIX_SIZE(x), 1, NUMBER_OF_INPUTS);
        float b0[4] = {1, -2, 3, -4};
        struct uz_nn_layer_config config = {
            .activation_function = ReLU,
            .number_of_neurons = NUMBER_OF_NEURONS_IN_LAYER,
            .number_of_inputs = NUMBER_OF_INPUTS,
            .length_of_weights = UZ_MATRIX_SIZE(w),
            .length_of_bias = UZ_MATRIX_SIZE(b0),
            .length_of_output = UZ_MATRIX_SIZE(out),
            .weights = w,
            .bias = b0,
            .output = out
        };

        uz_nn_layer_t *layer = uz_nn_layer_init(config);
        float expected[4] = {12.9105, 5.5267 , 0.0 , 6.6521};
        uz_nn_layer_ff(layer, input);
        uz_matrix_t *result = uz_nn_layer_get_output_data(layer);
        for (size_t i = 0; i < 4; i++)
        {
        TEST_ASSERT_EQUAL_FLOAT(expected[i], uz_matrix_get_element_zero_based(result, 0, i));
        }
    }

Reference
=========

The enum ``activation_function`` and the struct ``uz_nn_layer_config`` are directly used by :ref:`uz_nn` and have to be passed to its initialization function.

.. doxygenenum:: activation_function

.. doxygenstruct:: uz_nn_layer_config
    :members:

.. note:: The following functions are not independent for direct use but are the basis of :ref:`uz_nn`.

.. doxygentypedef:: uz_nn_layer_t
    
.. doxygenfunction:: uz_nn_layer_init

.. doxygenfunction:: uz_nn_layer_ff

.. doxygenfunction:: uz_nn_layer_get_output_data

Sources
=======

- https://datascience.stackexchange.com/questions/75855/what-types-of-matrix-multiplication-are-used-in-machine-learning-when-are-they
