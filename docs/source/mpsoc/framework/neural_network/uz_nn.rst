.. _uz_nn:

=====
uz_nn
=====

The neural network software implementation follows the definitions outlined in :ref:`neural_network`.
The module is based on the :ref:`uz_nn_layer` and :ref:`matrix_math` module.

Features and limitations:

- Multiplayer perceptron
- No recurrent connections
- Configurable number of outputs
- Configurable number of inputs
- Configurable number of neurons per layer
- Configurable number of hidden layer (min. 1, max. 10)
- Configurable activation function per layer

Software
========

- The internal struct of the uz_nn object holds an array of pointer to layers
- This array is always of length ``UZ_NN_MAX_LAYER``, which is arbitrarily set to 10.
- The define can be changed, which changes the size of the array for all instances of uz_nn
- This solution makes it possible to have different number of layers for different instances of uz_nn
- uz_nn_init uses the config struct of :ref:`uz_nn_layer`
- Compared to other modules (see :ref:`software_development_guidelines`), the initialization function (``uz_nn_init``) takes an array of pointers to the config structure instead of one config structure
- This allows for individual configuration of each layer with a variable amount of layers
- The number of outputs is automatically determined based on the number of neurons in the last layer
- The arrays of data have to be allocated manually (see :ref:`matrix_math`)

Initialization of config struct
*******************************

- Initialization of the config struct uses an array of config structs
- Each element of the config struct has to be initialized with designated initializers
- The first element (zero index ``[0]``!) of the config struct configures the first hidden layer
- The following elements define the subsequent hidden layers
- The last element of the config struct configures the output layer
- Arrays for the data (weight, bias, output) have to be provided for each layer
- Use defines to setup the arrays

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
        uz_matrix_t* input=uz_matrix_init(x,UZ_MATRIX_SIZE(x),1,2);
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

- To ease the declaration of weight and bias arrays, initialization based on ``.csv`` data can be used

.. code-block::

    static float weights[]=
    {
        #include "weights.csv"
    };

Note that the weights have 

Reference
=========

.. doxygentypedef:: uz_nn_t

.. doxygenfunction:: uz_nn_init

.. doxygenfunction:: uz_nn_get_output_data