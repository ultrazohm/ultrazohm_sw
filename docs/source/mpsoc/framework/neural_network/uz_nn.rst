.. _uz_nn:

=====
uz_nn
=====

The neural network software implementation follows the definitions outlined in :ref:`neural_network`.
The module is based on the :ref:`uz_nn_layer` and the :ref:`uz_matrix` module.

Features and limitations:

- Multiplayer perceptron
- No recurrent connections
- Configurable number of outputs
- Configurable number of inputs
- Configurable number of neurons per layer
- Configurable number of hidden layer (min. 1, max. 9)
- Configurable activation function per layer

Software
========

- The internal struct of the uz_nn object holds an array of pointer to layers
- This array is always of length ``UZ_NN_MAX_LAYER``, which is arbitrarily set to 10.
- The define can be changed, which changes the size of the array for all instances of uz_nn
- This solution makes it possible to have different number of layers for different instances of uz_nn
- uz_nn_init uses the config struct of :ref:`uz_nn_layer`
- Compared to other modules (see :ref:`software_development_guidelines`), the initialization function (``uz_nn_init``) takes an array of pointers to the config struct of each layer instead of one config structure
- This allows for individual configuration of each layer with a variable amount of layers
- The number of outputs is automatically determined based on the number of neurons in the last layer
- The arrays that hold the actual data (weights, bias, outputs of each layer) have to be allocated manually (see :ref:`uz_matrix`)

Initialization of config struct
*******************************

- Initialization of the config struct uses an array of config structs
- Each element of the config struct has to be initialized with designated initializers
- The first element (zero index ``[0]``!) of the config struct configures the first hidden layer
- The following elements define the subsequent hidden layers
- The last element of the config struct configures the output layer
- Arrays for the data (weight, bias, output) have to be provided for each layer

.. tip:: Use defines to setup the dimensions of the data arrays

Dimensions of arrays
********************

- Care has to be taken regarding the dimensions of the arrays that hold weights, bias, and outputs of the layer
- The array that holds the weights of the first hidden layer has to be of length ``NUMBER_OF_INPUTS`` * ``NUMBER_OF_NEURONS_IN_FIRST_HIDDEN_LAYER``
- The array that holds the weights of any other hidden layer has to be of length ``NUMBER_OF_NEURONS_IN_PREVIOUS_LAYER`` * ``NUMBER_OF_NEURONS_IN_THIS_HIDDEN_LAYER``
- The array that holds the bias of a hidden layer has to be equal to the number of neurons in the respective layer
- The array that holds the bias of the output layer has to be equal to the number of outputs
- The array that holds the output of a layer is of the same dimension as the array of the array that holds the bias values

Example initialization
**********************

The following shows an example initialization of a ``uz_nn`` that implements the example network of :ref:`neural_network` and that is used in the unit test ``test_uz_nn_ff``.

.. code-block::
    :caption: Initialization of config struct for uz_nn and forward calculation

    #define NUMBER_OF_INPUTS 2
    #define NUMBER_OF_OUTPUTS 1
    #define NUMBER_OF_NEURONS_IN_HIDDEN_LAYER 3

    static float x[NUMBER_OF_INPUTS] = {1, 2};
    static float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {1, 2, 3, 4, 5, 6};
    static float b_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {1, 2, 3};
    static float y_1[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
    static float w_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {-7, -8, -9, -10, -11, -12, 13, 14, -15};
    static float b_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {4, 5, 6};
    static float y_2[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER] = {0};
    static float w_3[NUMBER_OF_NEURONS_IN_HIDDEN_LAYER * NUMBER_OF_OUTPUTS] = {16, 17, -18};
    static float b_3[NUMBER_OF_OUTPUTS] = {7};
    static float y_3[NUMBER_OF_OUTPUTS] = {0};

    struct uz_nn_layer_config config[3] = {
    [0] = {
        .activation_function = ReLU,
        .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
        .number_of_inputs = NUMBER_OF_INPUTS,
        .length_of_weights = UZ_MATRIX_SIZE(w_1),
        .length_of_bias = UZ_MATRIX_SIZE(b_1),
        .length_of_output = UZ_MATRIX_SIZE(y_1),
        .weights = w_1,
        .bias = b_1,
        .output = y_1},
    [1] = {.activation_function = ReLU,
            .number_of_neurons = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
            .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
            .length_of_weights = UZ_MATRIX_SIZE(w_2),
            .length_of_bias = UZ_MATRIX_SIZE(b_2),
            .length_of_output = UZ_MATRIX_SIZE(y_2),
            .weights = w_2,
            .bias = b_2,
            .output = y_2},
    [2] = {.activation_function = linear,
           .number_of_neurons = NUMBER_OF_OUTPUTS,
           .number_of_inputs = NUMBER_OF_NEURONS_IN_HIDDEN_LAYER,
           .length_of_weights = UZ_MATRIX_SIZE(w_3),
           .length_of_bias = UZ_MATRIX_SIZE(b_3),
           .length_of_output = UZ_MATRIX_SIZE(y_3),
           .weights = w_3,
           .bias = b_3,
           .output = y_3}
    };

    void test_uz_nn_ff(void)
    {
        struct uz_matrix_t input_matrix={0};
        uz_matrix_t* input=uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1,2);
        uz_nn_t *test = uz_nn_init(config, 3);
        uz_nn_ff(test,input);
        float expected_result_first_layer[3]={10, 14, 18};
        float expected_result_second_layer[3]={28, 23, 0};
        float expected_result_output_layer[1]={846};

        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_first_layer,y_1,UZ_MATRIX_SIZE(expected_result_first_layer));
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_second_layer,y_2,UZ_MATRIX_SIZE(expected_result_second_layer));
        TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected_result_output_layer,y_3,UZ_MATRIX_SIZE(expected_result_output_layer));

        float expected_result=846;
        uz_matrix_t* output=uz_nn_get_output_data(test);
        float result=uz_matrix_get_element_zero_based(output,0,0);
        TEST_ASSERT_EQUAL_FLOAT(expected_result,result);
    }


Initialization of pretrained network
************************************

To ease the declaration of weight and bias arrays, initialization based on ``.csv`` data can be used, like so:

.. code-block::

    static float weights[]=
    {
        #include "weights.csv"
    };

The weights have to be a ``.csv`` with the separator set to ``comma``.
Furthermore, for the weights, the first :math:`n` elements correspond to the first row of weights with :math:`n` representing the number of neurons in the layer.
Effectively, each row is attached to the columns one by one.
See :ref:`uz_matrix` for details regarding the transformation of matrix to vector dimensions and :ref:`neural_network` regarding the dimension definition of the network.

.. tip:: Use the declaration and defines shown in the examples and unit tests and adjust them to specific networks.

Full example
============

The following example is based on a basic `Matlb Example <https://de.mathworks.com/help/deeplearning/ug/train-and-apply-multilayer-neural-networks.html>`_.
A network with 13 inputs, two hidden layer (50 neurons in the first, 20 neurons in the second), ReLU activatin and one output is trained on a existing data set.
Note that this example is not concerned with the accuracy of the network, it is just used to showcase the initialization of the network and as a test-case.
The Matlab script ``uz_nn_full_example_script.m`` in ``~/ultrazohm_sw/vitis/software/Baremetal/test/uz/uz_nn`` trains the network and writes the weights and bias to a ``.csv`` file.
Be aware that the Matlab neural network definition differs from the network definition used in :ref:`neural_network`, thus the data is transposed and reshaped before the write operation. 
See the file ``test_uz_nn_full_example.c`` in ``~/ultrazohm_sw/vitis/software/Baremetal/test/uz/uz_nn`` for the code.


Execution time on R5
====================

The following lists the expected execution time for different networks with the feedforward calculation in the *empty* (expect for required code for system function) ISR of the R5 processors (takes 2.6 us without feedforward calculation).

- 2 inputs, 1 output, 3 neurons, two hidden layer with ReLU takes 5.0 us
- 2 inputs, 1 output, 3 neurons, two hidden layer with ReLU ten times takes 25.5 us
- (5.0us-2.6us)*10+2.6us is approx. 25.5us, which means that the calculation is actually happening 10 times (compiler does not optimize it away)
- 4 inputs, 8 outputs, 64 neurons, two hidden layer with ReLU takes 89 us.
- 4 inputs, 8 outputs, 64 neurons, one hidden layer with ReLU takes 24.7 us.
- 4 inputs, 8 outputs, 128 neurons, one hidden layer with ReLU takes 44 us.
- 7 inputs, 2 outputs, 100 neurons ReLU, 30.2 us.
- 5 inputs, 8 outputs, three hidden layer with 64 neurons, ReLU, takes 200 us.
- 13 inputs, 1 output, one hidden layer with 20 neurons ReLU, takes 11 us.
- 13 inputs, 1 output, two hidden layer (50 neurons in the first, 20 neurons in the second hidden layer) with 

Optimization
************

All timing above was done with -O2 flag.
Testing with ``-funroll-all-loops`` leads to worse performance (4 inputs, 8 outputs, 64 neurons, two hidden layer with ReLU takes 94 us with the flag compared to 89 us without).
Testing with ``-funroll-loops`` results in 92 us.
Most time in the program is spent on multiplying the inputs of a layer with the weight matrix (as expected).

See:

- https://gcc.gnu.org/onlinedocs/gcc-3.4.4/gcc/Optimize-Options.html
- https://stackoverflow.com/questions/24196076/is-gcc-loop-unrolling-flag-really-effective


Reference
=========

.. doxygentypedef:: uz_nn_t

.. doxygenfunction:: uz_nn_init

.. doxygenfunction:: uz_nn_get_output_data

.. doxygendefine:: UZ_NN_MAX_LAYER