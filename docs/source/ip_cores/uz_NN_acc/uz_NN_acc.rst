.. _uz_NN_acc:

=========
uz_NN_acc
=========

This IP-Core implements a three layer MLP network.
The implementation and nomenclature follows the principles outlined in :ref:`uz_nn`.

.. Attention:: 
  - Hard coded to have **3 hidden layer** with :ref:`activation_function_relu` activation function for hidden layers.
  - Output in the IP-Core is hard coded to us :ref:`activation_function_linear` activation. A different activation function for the output layer is done via software.
  - Number of neurons in the hidden layers is fixed to **64**.
  - Variable number of up to **24 Observations**
  - Variable number of up to **12 Actions**
  
.. figure:: uz_NN_acc_layers.svg
   :align: center
   :width: 500px



Features
--------
- Feedforward calculation in **floating point**
- Bias and weights are written to the IP-Core during initialization
- Fully compatible with uz_nn to use IP-Core as an accelerator
- Uses Matrix math as input and outputs
- IP-Core is configured and triggerd by the PS exclusively 
- Correct size of the observation, weights, bias and action arrays will be asserted
- Execution time for 20 observations and 4 actions roughly takes **~22µs**



Functionality
=============

The usage of the IP-Core driver depends heavily on :ref:`uz_nn`.
First, an instance of the software network has to be initialized, e.g., by loading parameters from a header.
Additionally, an array for the output data of the IP-Core has to be declared (see :ref:`uz_matrix`).
The ``uz_NN_acc_init`` function writes all addresses in memory of the arrays for weights & bias to the IP-Core.
Following, the IP-Core reads all the data for the weights & bias data from system memory. 
The weights & bias data is only read once during initialization of the IP-Core.
During runtime the weights & bias are stored in BRAM and are fixed.
During execution, only the observation and action data are read respectively written when ``uz_NN_acc_ff_blocking`` is called. 
Note that the :ref:`global_configuration` has to be adjusted to include at least one uz_NN_acc IP-Core driver instance, :ref:`one software network<uz_nn>` and :ref:`four layers<uz_nn_layer>`.

Usage
=====
First, an instance of the software network has to be initialized, e.g., by loading parameters from a header.
Additionally, an array for the output data of the IP-Core has to be declared (see :ref:`uz_matrix`).

.. warning::
    Every array and uz_matrix_t object has to be declared with the **MEMORY_ALIGN** attribute.
    It aligns the arrays (and therefore its pointers) to 32byte.
    Otherwise undefined behavior regarding the read/write process of the IP-Core can occur.

In the ``globalData.h`` file add the following code to the ``object_pointers_t`` struct:

.. code-block:: c
 :caption: Code for ``globalData.h`` file

 #include "uz/uz_nn/uz_nn.h"
 #include "uz/uz_matrix/uz_matrix.h"
 #include "IP_Cores/uz_NN_acc/uz_NN_acc.h"
 ...
 typedef struct{
 ...
 uz_matrix_t* matrix_input_acc;
 uz_matrix_t* matrix_output_acc;
 uz_nn_t* nn_layer_acc;
 uz_NN_acc_t* NN_acc_Instance;
 }object_pointers_t;


Create a initialization c-file (e.g. ``init_network_ip_core.c``) and a corresponding header file (``init_network_ip_core.h``) for the ``init_network`` function:

.. code-block:: c
 :caption: Code for ``init_network_ip_core.c`` for initialization of network and IP-core

 #include "../uz/uz_nn/uz_nn.h"
 #include "../IP_Cores/uz_NN_acc/uz_NN_acc.h"
 #include "../../main.h"
 extern DS_Data Global_Data;

 #define NUMBER_OF_INPUTS 13U
 #define NUMBER_OF_NEURONS_IN_FIRST_LAYER 64U
 #define NUMBER_OF_NEURONS_IN_SECOND_LAYER 64U
 #define NUMBER_OF_NEURONS_IN_THIRD_LAYER 64U
 #define NUMBER_OF_OUTPUTS 4
 #define NUMBER_OF_HIDDEN_LAYER 3
 
 float x[NUMBER_OF_INPUTS] MEMORY_ALIGN = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f};
 float w_1[NUMBER_OF_INPUTS * NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
 #include "layer1_weights.csv"
 };
 float b_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {
 #include "layer1_bias.csv"
 };
 float y_1[NUMBER_OF_NEURONS_IN_FIRST_LAYER] MEMORY_ALIGN = {0};
 
 float w_2[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
 #include "layer2_weights.csv"
 };
 float b_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
 #include "layer2_bias.csv"
 };
 float y_2[NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {0};
 
 float w_3[NUMBER_OF_NEURONS_IN_FIRST_LAYER * NUMBER_OF_NEURONS_IN_SECOND_LAYER] MEMORY_ALIGN = {
 #include "layer2_weights.csv"
 };
 float b_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] MEMORY_ALIGN = {
 #include "layer3_bias.csv"
 };
 float y_3[NUMBER_OF_NEURONS_IN_THIRD_LAYER] MEMORY_ALIGN = {0};
 
 float w_4[NUMBER_OF_NEURONS_IN_THIRD_LAYER * NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
 #include "layer4_weights.csv"
 };
 float b_4[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {
 #include "layer4_bias.csv"
 };
 float y_4[NUMBER_OF_OUTPUTS] MEMORY_ALIGN = {0};

 struct uz_nn_layer_config software_nn_config[4] = {
     [0] = {
         .activation_function = activation_ReLU,
         .number_of_neurons = NUMBER_OF_NEURONS_IN_FIRST_LAYER,
         .number_of_inputs = NUMBER_OF_INPUTS,
         .length_of_weights = UZ_MATRIX_SIZE(w_1),
         .length_of_bias = UZ_MATRIX_SIZE(b_1),
         .length_of_output = UZ_MATRIX_SIZE(y_1),
         .weights = w_1,
         .bias = b_1,
         .output = y_1},
     [1] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_SECOND_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_2), .length_of_bias = UZ_MATRIX_SIZE(b_2), .length_of_output = UZ_MATRIX_SIZE(y_2), .weights = w_2, .bias = b_2, .output = y_2},
     [2] = {.activation_function = activation_ReLU, .number_of_neurons = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_3), .length_of_bias = UZ_MATRIX_SIZE(b_3), .length_of_output = UZ_MATRIX_SIZE(y_3), .weights = w_3, .bias = b_3, .output = y_3},
     //Note:Although IP-Core is hardcoded to activation_linear for the output the specified activation function for the last layer will be applied in software
     [3] = {.activation_function = activation_tanh, .number_of_neurons = NUMBER_OF_OUTPUTS, .number_of_inputs = NUMBER_OF_NEURONS_IN_THIRD_LAYER, .length_of_weights = UZ_MATRIX_SIZE(w_4), .length_of_bias = UZ_MATRIX_SIZE(b_4), .length_of_output = UZ_MATRIX_SIZE(y_4), .weights = w_4, .bias = b_4, .output = y_4}};

 struct uz_matrix_t input_matrix MEMORY_ALIGN={0};
 struct uz_matrix_t output_matrix MEMORY_ALIGN={0};

 void init_network(void){
    Global_Data.objects.matrix_input_acc=uz_matrix_init(&input_matrix,x,UZ_MATRIX_SIZE(x),1U,NUMBER_OF_INPUTS);
	Global_Data.objects.matrix_output_acc=uz_matrix_init(&output_matrix,y_4,UZ_MATRIX_SIZE(y_4),1U,NUMBER_OF_OUTPUTS);
	Global_Data.objects.nn_layer_acc = uz_nn_init(software_nn_config, 4U); //Warning is a GCC 11 bug

    struct uz_NN_acc_config_t IP_config = {
			.software_network = Global_Data.objects.nn_layer_acc,
			.base_address = XPAR_UZ_USER_UZ_NN_ACC_0_S_AXI_CONTROL_BASEADDR
	};
    Global_Data.objects.NN_acc_Instance = uz_NN_acc_init(IP_config, Global_Data.objects.matrix_input_acc, Global_Data.objects.matrix_output_acc);
    uz_mlp_three_layer_ff_blocking(mlp_ip_instance, p_input_data, p_output_data);
  }

After including your header file (``init_network_ip_core.h``) in the ``main.h`` add the init function to the main.c file:

.. code-block:: c
 :caption: Code for main.c

 ...
 switch (initialization_chain)
    {
    ....
    case init_ip_cores:
        ...
        init_network();
        ...
        initialization_chain = print_msg;
        break;
    case print_msg:
    ....

To use the IP-Core in the ISR add the following code to the ``isr.c`` :

.. code-block:: c
 :caption: Code example for blocking operation ``isr.c`` 

 float Action[4] = {0};
 float Observation[12] = {0};
 ...
 void ISR_Control(void *data)
 {
 ...
 Observation[0] = ...;
 Observation[1] = ...;
 Observation[2] = ...;
 Observation[3] = ...;
 Observation[4] = ...;
 Observation[5] = ...;
 Observation[6] = ...;
 Observation[7] = ...;
 Observation[8] = ...;
 Observation[9] = ...;
 Observation[10] = ...;
 Observation[11] = ...;
 Observation[12] = ...;
 if (current_state==control_state) {
    for (uint32_t i = 0; i < 13U; i++) {
    	uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_acc,Observation[i],0U,i);
    }
    uz_NN_acc_ff_blocking(Global_Data.objects.NN_acc_Instance);
    Output[0] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,0U);
    Output[1] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,1U);
    Output[2] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,2U);
    Output[3] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,3U);
 }
 ...

.. code-block:: c
 :caption: Code example for non-blocking operation ``isr.c`` 

 float Action[4] = {0};
 float Observation[12] = {0};
 ...
 void ISR_Control(void *data)
 {
 ...
 Observation[0] = ...;
 Observation[1] = ...;
 Observation[2] = ...;
 Observation[3] = ...;
 Observation[4] = ...;
 Observation[5] = ...;
 Observation[6] = ...;
 Observation[7] = ...;
 Observation[8] = ...;
 Observation[9] = ...;
 Observation[10] = ...;
 Observation[11] = ...;
 Observation[12] = ...;
 if (current_state==control_state) {
    for (uint32_t i = 0; i < 13U; i++) {
    	uz_matrix_set_element_zero_based(Global_Data.objects.matrix_input_acc,Observation[i],0U,i);
    }
    uz_NN_acc_ff_non_blocking(Global_Data.objects.NN_acc_Instance);
    //do something else here
    uz_NN_acc_get_result_blocking(Global_Data.objects.NN_acc_Instance);
    Output[0] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,0U);
    Output[1] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,1U);
    Output[2] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,2U);
    Output[3] = uz_matrix_get_element_zero_based(Global_Data.objects.matrix_output_acc,0U,3U);
 }
 ...

Execution
=========

The regular calculation with the IP-Core using the software driver and writing the inputs and waiting for the output is a **blocking** operation.
The driver triggers the calculation and waits until it is finished.
The processor can not do any other tasks.

.. code-block::

    uz_NN_acc_ff_blocking(instance);                         // Takes 22us (example)
    uz_sleep_useconds(10);                                   // Takes 10us
                                                             // Takes 32us total

.. mermaid::

   sequenceDiagram
       participant Processor
       participant Driver
       Processor->>Driver: uz_NN_acc_ff_blocking
       Driver->>IP-Core: Write input
       Driver->>IP-Core: Trigger calculation
       loop
           Driver->>IP-Core: Read valid output
           Driver->>Driver: Valid output true?
       end
       Driver->>IP-Core: Read output
       Driver->>Processor: Return output values

An alternative to the blocking calculation is a concurrent approach.
In this, the IP-Core calculation is triggered, the processor is free to do other tasks, and the data is fetched after the calculation is finished.
This way the calculation between trigger and get result does not add to the total required time if the task in between takes less time than the IP-Core calculation.
Note that this means the actual calculation time of network without the communication overhead of the read/write operations. 

.. code-block::

    uz_NN_acc_ff_non_blocking(instance);                            // Takes 22us (example)
    uz_sleep_useconds(10);                                          // Takes 10us 
    uz_NN_acc_get_result_blocking(instance);                        // Takes 4us
                                                                    // Takes 26us total

.. mermaid::

   sequenceDiagram
       participant Processor
       participant Driver
       Processor->>Driver: uz_NN_acc_ff_non_blocking
       Driver->>IP-Core: Write input
       Driver->>IP-Core: Trigger calculation
       Processor->>Software: Do something else
       Software->>Processor: return
       Processor->>Driver: uz_NN_acc_get_result_blocking
       loop
           Driver->>IP-Core: Read valid output
           Driver->>Driver: Valid output true?
       end
       Driver->>IP-Core: Read output
       Driver->>Processor: Return output values

Further improvements
====================

Further improvements are planed for the IP-core and in development:

- variable neuron & layer setup
- improved resource utilization

Driver reference
================

.. doxygentypedef:: uz_NN_acc_t

.. doxygenstruct:: uz_NN_acc_config_t
    :members:

.. doxygenfunction:: uz_NN_acc_init

.. doxygenfunction:: uz_NN_acc_ff_blocking

.. doxygenfunction:: uz_NN_acc_ff_non_blocking

.. doxygenfunction:: uz_NN_acc_get_result_blocking